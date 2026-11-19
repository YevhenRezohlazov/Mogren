#!/usr/bin/env python3
"""Shared Python resource conversion for Mogren-based games."""

from __future__ import annotations

import io
import math
import os
import shutil
import struct
import tempfile
import xml.etree.ElementTree as ET
from pathlib import Path, PurePosixPath
from typing import Callable, Mapping

from PIL import Image, ImageDraw, ImageFont


SHADER_SIGNATURE = 0x5FA6B220


class ResourceProcessingError(ValueError):
    """An input asset cannot be converted into a valid Mogren resource."""


def _read_text(path: Path) -> str:
    try:
        return path.read_text(encoding="utf-8-sig")
    except UnicodeDecodeError as error:
        raise ResourceProcessingError(
            f"Unable to decode text resource {path}: {error}"
        ) from error


def _next_power_of_two(value: int) -> int:
    return 1 << (value - 1).bit_length()


def _encode_mpng(
    image: Image.Image,
    no_stretch: bool = False,
    resampling: Image.Resampling = Image.Resampling.BICUBIC,
) -> bytes:
    source = image.convert("RGBA")
    if source.width > 0xFFFF or source.height > 0xFFFF:
        raise ResourceProcessingError(
            f"Image dimensions exceed the MPNG format limit: {source.width}x{source.height}."
        )
    levels: list[tuple[int, int, bytes]] = []
    width = _next_power_of_two(source.width)
    height = _next_power_of_two(source.height)

    while True:
        if no_stretch:
            mip = Image.new("RGBA", (width, height), (0, 0, 0, 0))
            mip.paste(source, (0, height - source.height))
        else:
            mip = source.resize((width, height), resampling)
        mip = mip.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
        encoded = io.BytesIO()
        mip.save(encoded, format="PNG")
        levels.append((width, height, encoded.getvalue()))
        if no_stretch:
            break
        width >>= 1
        height >>= 1
        if width == 0 or height == 0:
            break

    header_size = 10 + 12 * len(levels)
    offset = header_size
    result = bytearray(struct.pack("<4sHHH", b"MPNG", source.width, source.height, len(levels)))
    for width, height, data in levels:
        result.extend(struct.pack("<HHII", width, height, offset, len(data)))
        offset += len(data)
    for _, _, data in levels:
        result.extend(data)
    return bytes(result)


def _process_image(
    source: Path,
    resampling: Image.Resampling,
    no_stretch: bool,
) -> bytes:
    with Image.open(source) as image:
        return _encode_mpng(
            image,
            no_stretch and source.name.lower().endswith(".nn.png"),
            resampling,
        )


def _load_shader_lines(path: Path, active: tuple[Path, ...] = ()) -> list[str]:
    path = path.resolve()
    if path in active:
        cycle = " -> ".join(str(item) for item in (*active, path))
        raise ResourceProcessingError(f"Circular shader include: {cycle}")
    lines: list[str] = []
    for line in _read_text(path).splitlines():
        if line.startswith("#include "):
            include_name = line[len("#include "):].strip(' "')
            if not include_name:
                raise ResourceProcessingError(f"Empty shader include in {path}")
            include_path = path.parent / include_name
            if not include_path.is_file():
                raise ResourceProcessingError(f"Shader include not found: {include_path}")
            lines.extend(_load_shader_lines(include_path, (*active, path)))
        else:
            lines.append(line.strip())
    return lines


def _process_shader(source: Path) -> bytes:
    lines = _load_shader_lines(source)
    try:
        split_index = lines.index("-----")
    except ValueError as error:
        raise ResourceProcessingError(
            f"{source}: vertex and fragment shaders must be split by '-----'"
        ) from error
    vertex = "\n".join(lines[:split_index])
    fragment = "\n".join(lines[split_index + 1:])
    if not vertex.strip() or not fragment.strip():
        raise ResourceProcessingError(f"{source}: vertex or fragment shader code is empty")
    fragment = (
        "#ifdef GL_ES\n"
        "#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
        "   // Default precision\n"
        "   precision highp float;\n"
        "#else\n"
        "   precision mediump float;\n"
        "#endif\n"
        "#endif\n"
        + fragment
    )
    vertex_bytes = vertex.encode("ascii", errors="replace")
    fragment_bytes = fragment.encode("ascii", errors="replace")
    return (
        struct.pack("<I", SHADER_SIGNATURE)
        + struct.pack("<I", len(vertex_bytes)) + vertex_bytes
        + struct.pack("<I", len(fragment_bytes)) + fragment_bytes
    )


def _process_strings(source: Path) -> bytes:
    localized: dict[str, list[str]] = {}
    for line in _read_text(source).splitlines():
        if ":" not in line:
            continue
        key, value = line.split(":", 1)
        localized.setdefault(key, []).append(value)
    output = bytearray(struct.pack("<I", len(localized)))
    for key, values in localized.items():
        encoded_key = key.encode("utf-8")
        output.extend(struct.pack("<I", len(encoded_key)))
        output.extend(encoded_key)
        output.extend(struct.pack("<I", len(values)))
        for value in values:
            encoded_value = value.encode("utf-8")
            output.extend(struct.pack("<I", len(encoded_value)))
            output.extend(encoded_value)
    return bytes(output)


def _font_description(path: Path) -> tuple[Path, str, int, str, bool]:
    try:
        root = ET.parse(path).getroot()
        name = root.attrib["Name"]
        style = root.attrib.get("Style", "Regular")
        size = int(root.attrib["Size"])
        alphabet = root.attrib["Alphabet"]
        no_mipmaps_value = root.attrib.get("NoMipMaps", "false").lower()
        if no_mipmaps_value not in ("true", "false"):
            raise ValueError("NoMipMaps must be true or false")
    except (ET.ParseError, OSError, KeyError, ValueError) as error:
        raise ResourceProcessingError(f"Invalid Mogren font definition {path}: {error}") from error
    if size <= 0 or not alphabet:
        raise ResourceProcessingError(
            f"{path}: font size and alphabet must both be non-empty."
        )
    if any(ord(character) > 0xFFFF for character in alphabet):
        raise ResourceProcessingError(
            f"{path}: MGFNT supports only UTF-16 BMP characters."
        )
    no_mipmaps = no_mipmaps_value == "true"
    return path.parent / name, style, size, alphabet, no_mipmaps


def _read_precompiled_font(source: Path, alphabet: str) -> bytes | None:
    precompiled_path = source.with_suffix(".mgfnt")
    if not precompiled_path.is_file():
        return None

    data = precompiled_path.read_bytes()
    if len(data) < 17 or data[:5] != b"MGFNT":
        raise ResourceProcessingError(f"Invalid precompiled font: {precompiled_path}")
    character_count = struct.unpack_from("<I", data, 9)[0]
    if character_count != len(alphabet) or len(data) < 17 + character_count * 34:
        raise ResourceProcessingError(
            f"Precompiled font does not match {source}: {precompiled_path}"
        )
    characters = [
        struct.unpack_from("<H", data, 13 + index * 34)[0]
        for index in range(character_count)
    ]
    if characters != [ord(character) for character in alphabet]:
        raise ResourceProcessingError(
            f"Precompiled font alphabet does not match {source}: {precompiled_path}"
        )

    map_offset = 13 + character_count * 34
    map_size = struct.unpack_from("<I", data, map_offset)[0]
    map_data = data[map_offset + 4:]
    if map_size != len(map_data) or len(map_data) < 10 or map_data[:4] != b"MPNG":
        raise ResourceProcessingError(
            f"Invalid precompiled font texture: {precompiled_path}"
        )
    return data


def _process_font(source: Path) -> bytes:
    font_path, style, size, alphabet, no_mipmaps = _font_description(source)
    precompiled = _read_precompiled_font(source, alphabet)
    if precompiled is not None:
        return precompiled
    if not font_path.is_file():
        raise ResourceProcessingError(f"Font file not found: {font_path}")
    if style.casefold() not in ("regular", "bold"):
        raise ResourceProcessingError(
            f"{source}: unsupported font style {style!r}; use Regular or Bold"
        )
    if any(ord(character) > 0xFFFF for character in alphabet):
        raise ResourceProcessingError(
            f"{source}: MGFNT supports only UTF-16 BMP characters"
        )

    try:
        font = ImageFont.truetype(str(font_path), size)
    except OSError as error:
        raise ResourceProcessingError(
            f"Unable to load font {font_path} referenced by {source}: {error}"
        ) from error
    stroke_width = max(1, round(size / 40)) if style.casefold() == "bold" else 0
    ascent, descent = font.getmetrics()
    font_height = ascent + descent
    side_bearing = font_height / 8
    container_height = font_height + round(size / 8)

    characters: list[dict[str, object]] = []
    for character in alphabet:
        advance = font.getlength(character)
        if character == " ":
            container_width = max(1, math.ceil(advance))
            bearing = 0.0
        else:
            container_width = max(
                1,
                math.ceil(advance + 2 * (side_bearing + stroke_width)),
            )
            bearing = side_bearing + stroke_width
        characters.append({
            "char": character,
            "width": container_width,
            "height": container_height,
            "advance": advance,
            "bearing": bearing,
            "position": (0, 0),
        })

    total_area = sum(int(char["width"]) * int(char["height"]) for char in characters)
    map_width = max(
        math.isqrt(total_area),
        max(int(char["width"]) for char in characters),
    )
    remaining = sorted(characters, key=lambda char: -int(char["width"]))
    x = y = line_height_max = map_width_used = map_height_used = 0
    while remaining:
        available = map_width - x
        fitting = next(
            (i for i, char in enumerate(remaining) if int(char["width"]) <= available),
            None,
        )
        if fitting is None:
            if line_height_max == 0:
                raise ValueError(f"{source}: character atlas cannot fit its widest glyph")
            y += line_height_max
            map_width_used = max(map_width_used, x)
            x = 0
            line_height_max = 0
            continue
        char = remaining.pop(fitting)
        char["position"] = (x, y)
        x += int(char["width"])
        line_height_max = max(line_height_max, int(char["height"]))
        map_height_used = max(map_height_used, y + int(char["height"]))
    map_width_used = max(map_width_used, x)

    atlas_width = _next_power_of_two(map_width_used)
    atlas_height = _next_power_of_two(map_height_used)
    atlas = Image.new("RGBA", (atlas_width, atlas_height), (0, 0, 0, 0))
    drawer = ImageDraw.Draw(atlas)
    for char in characters:
        px, py = char["position"]
        if char["char"] != " ":
            drawer.text(
                (px + side_bearing + stroke_width, py + ascent),
                str(char["char"]),
                font=font,
                fill=(255, 255, 255, 255),
                stroke_width=stroke_width,
                stroke_fill=(255, 255, 255, 255),
                anchor="ls",
            )

    output = bytearray(b"MGFNT")
    output.extend(struct.pack("<fI", font_height / atlas_height, len(characters)))
    for char in characters:
        px, py = char["position"]
        output.extend(struct.pack(
            "<H8f",
            ord(str(char["char"])),
            px / atlas_width,
            py / atlas_height,
            int(char["width"]) / atlas_width,
            int(char["height"]) / atlas_height,
            float(char["bearing"]) / atlas_width,
            0.0,
            float(char["advance"]) / atlas_width,
            font_height / atlas_height,
        ))
    encoded_map = _encode_mpng(atlas, no_mipmaps)
    output.extend(struct.pack("<I", len(encoded_map)))
    output.extend(encoded_map)
    return bytes(output)


def _convert_file(
    source: Path,
    image_resampling: Image.Resampling,
    no_stretch_images: bool,
) -> bytes | None:
    extension = source.suffix.lower()
    if extension in (".ttf", ".mgfnt"):
        return None
    if extension == ".png":
        return _process_image(source, image_resampling, no_stretch_images)
    if extension == ".ms":
        return _process_shader(source)
    if extension == ".str":
        return _process_strings(source)
    if extension == ".mf":
        return _process_font(source)
    return source.read_bytes()


def _safe_resource_path(root: Path, relative: str) -> Path:
    path = PurePosixPath(relative)
    if (
        path.is_absolute()
        or not path.parts
        or any(part in ("", ".", "..") for part in path.parts)
        or "\\" in relative
        or relative == "ResList.bin"
    ):
        raise ResourceProcessingError(
            f"Unsafe resource path in ResList.bin: {relative!r}"
        )

    target = root.joinpath(*path.parts)
    try:
        target.resolve().relative_to(root.resolve())
    except ValueError as error:
        raise ResourceProcessingError(
            f"Resource path escapes its output directory: {relative!r}"
        ) from error
    return target


def _read_previous_index(index_path: Path, destination: Path) -> list[str]:
    if not index_path.is_file():
        return []

    try:
        data = index_path.read_bytes()
        if len(data) < 4:
            raise ValueError("truncated resource count")
        count = struct.unpack_from("<i", data)[0]
        if count < 0:
            raise ValueError("negative resource count")
        offset = 4
        resources = []
        for _ in range(count):
            if offset + 4 > len(data):
                raise ValueError("truncated resource path length")
            length = struct.unpack_from("<i", data, offset)[0]
            offset += 4
            if length < 0 or offset + length > len(data):
                raise ValueError("invalid resource path length")
            resources.append(data[offset:offset + length].decode("utf-8"))
            offset += length
        if offset != len(data):
            raise ValueError("unexpected data at end of resource list")
        for resource in resources:
            _safe_resource_path(destination, resource)
        return resources
    except (OSError, ValueError, UnicodeDecodeError, struct.error) as error:
        raise ResourceProcessingError(
            f"Cannot safely update existing resource index {index_path}: {error}"
        ) from error


def _encode_resource_index(paths: list[str]) -> bytes:
    output = bytearray(struct.pack("<i", len(paths)))
    for relative in paths:
        encoded = relative.encode("utf-8")
        output.extend(struct.pack("<i", len(encoded)))
        output.extend(encoded)
    return bytes(output)


def process_resources(
    source: Path,
    destination: Path,
    converters: Mapping[str, Callable[[Path, Path], None]] | None = None,
    *,
    image_resampling: Image.Resampling = Image.Resampling.BICUBIC,
    no_stretch_images: bool = True,
) -> list[str]:
    source = source.resolve()
    destination = destination.resolve()
    if not source.is_dir():
        raise ResourceProcessingError(f"Source directory does not exist: {source}")
    if source == destination or source in destination.parents:
        raise ResourceProcessingError(
            "The output directory must not be inside the source directory."
        )
    if destination.exists() and not destination.is_dir():
        raise ResourceProcessingError(f"Output path is not a directory: {destination}")

    converters = {key.lower(): value for key, value in (converters or {}).items()}
    previous_resources = _read_previous_index(destination / "ResList.bin", destination)
    destination.parent.mkdir(parents=True, exist_ok=True)
    staging = Path(tempfile.mkdtemp(
        prefix=f".{destination.name}.staging-",
        dir=destination.parent,
    ))
    resources: list[str] = []
    try:
        for directory, subdirectories, filenames in os.walk(source):
            subdirectories.sort()
            filenames.sort()
            source_directory = Path(directory)
            relative_directory = source_directory.relative_to(source)

            for filename in filenames:
                input_path = source_directory / filename
                relative_path = relative_directory / filename
                relative_name = relative_path.as_posix()
                if relative_name == "ResList.bin":
                    raise ResourceProcessingError(
                        "ResList.bin is reserved for the generated resource index."
                    )

                extension = input_path.suffix.lower()
                if extension in (".ttf", ".mgfnt"):
                    continue
                output_path = staging / relative_path
                output_path.parent.mkdir(parents=True, exist_ok=True)
                converter = converters.get(extension)
                if converter:
                    converter(input_path, output_path)
                else:
                    converted = _convert_file(
                        input_path,
                        image_resampling,
                        no_stretch_images,
                    )
                    if converted is None:
                        continue
                    output_path.write_bytes(converted)
                resources.append(relative_name)

        resources.sort()
        casefolded = [resource.casefold() for resource in resources]
        if len(casefolded) != len(set(casefolded)):
            raise ResourceProcessingError(
                "Resource names that differ only by letter case cannot be packaged together."
            )
        (staging / "ResList.bin").write_bytes(_encode_resource_index(resources))

        for resource in resources:
            staged_path = staging.joinpath(*PurePosixPath(resource).parts)
            destination_path = _safe_resource_path(destination, resource)
            destination_path.parent.mkdir(parents=True, exist_ok=True)
            os.replace(staged_path, destination_path)

        current_resources = set(resources)
        for resource in previous_resources:
            if resource not in current_resources:
                obsolete = _safe_resource_path(destination, resource)
                if obsolete.is_file() or obsolete.is_symlink():
                    obsolete.unlink()

        destination.mkdir(parents=True, exist_ok=True)
        os.replace(staging / "ResList.bin", destination / "ResList.bin")
        return resources
    finally:
        shutil.rmtree(staging, ignore_errors=True)
