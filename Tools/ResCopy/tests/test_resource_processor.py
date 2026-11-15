from __future__ import annotations

import io
import struct
import sys
import tempfile
import unittest
from pathlib import Path

from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from resource_processor import (  # noqa: E402
    ResourceProcessingError,
    _encode_mpng,
    _encode_resource_index,
    _process_shader,
    _process_strings,
    _read_precompiled_font,
    process_resources,
)


class SharedResourceProcessorTests(unittest.TestCase):
    def test_mpng_mip_chain_and_dimensions(self) -> None:
        image = Image.new("RGBA", (3, 5), (10, 20, 30, 255))
        encoded = _encode_mpng(image)
        signature, width, height, count = struct.unpack_from("<4sHHH", encoded)
        self.assertEqual((signature, width, height), (b"MPNG", 3, 5))
        self.assertEqual(count, 3)
        levels = [
            struct.unpack_from("<HHII", encoded, 10 + index * 12)
            for index in range(count)
        ]
        self.assertEqual(
            [(level[0], level[1]) for level in levels],
            [(4, 8), (2, 4), (1, 2)],
        )
        self.assertEqual(levels[0][2], 10 + count * 12)

    def test_unstretched_mpng_is_padded_and_has_no_mips(self) -> None:
        image = Image.new("RGBA", (3, 2))
        image.putpixel((0, 0), (255, 0, 0, 255))
        image.putpixel((0, 1), (0, 0, 255, 255))
        encoded = _encode_mpng(image, no_stretch=True)
        _, width, height, count = struct.unpack_from("<4sHHH", encoded)
        self.assertEqual((width, height, count), (3, 2, 1))
        _, _, offset, size = struct.unpack_from("<HHII", encoded, 10)
        with Image.open(io.BytesIO(encoded[offset:offset + size])) as texture:
            self.assertEqual(texture.getpixel((0, 0)), (0, 0, 255, 255))

    def test_strings_keep_duplicate_values_utf8_and_colons(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            source = Path(temporary) / "strings.str"
            source.write_text("key:first:value\nkey:привет\n", encoding="utf-8")
            encoded = _process_strings(source)
        self.assertEqual(struct.unpack_from("<i", encoded)[0], 1)
        self.assertIn(b"first:value", encoded)
        self.assertIn("привет".encode("utf-8"), encoded)

    def test_shader_includes_and_cycles(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            (root / "common.glsl").write_text("float included;\n", encoding="utf-8")
            shader = root / "shader.ms"
            shader.write_text(
                '#include "common.glsl"\nvertex\n-----\nfragment\n',
                encoding="utf-8",
            )
            encoded = _process_shader(shader)
            self.assertEqual(struct.unpack_from("<I", encoded)[0], 0x5FA6B220)
            self.assertIn(b"float included;\nvertex", encoded)
            shader.write_text('#include "shader.ms"\n', encoding="utf-8")
            with self.assertRaises(ResourceProcessingError):
                _process_shader(shader)

    def test_precompiled_font_sidecar_checks_alphabet_and_texture(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            descriptor = root / "font.mf"
            descriptor.write_text(
                '<Font Name="missing.ttf" Size="16" Alphabet="A" />',
                encoding="utf-8",
            )
            texture = struct.pack("<4sHHH", b"MPNG", 1, 1, 1)
            font = (
                b"MGFNT"
                + struct.pack("<fI", 1.0, 1)
                + struct.pack("<H8f", ord("A"), *([0.0] * 8))
                + struct.pack("<I", len(texture))
                + texture
            )
            sidecar = descriptor.with_suffix(".mgfnt")
            sidecar.write_bytes(font)

            self.assertEqual(_read_precompiled_font(descriptor, "A"), font)
            with self.assertRaises(ResourceProcessingError):
                _read_precompiled_font(descriptor, "B")

    def test_custom_converter_and_game_image_options(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source = root / "source"
            output = root / "output"
            source.mkdir()
            (source / "special.bin").write_bytes(b"game")
            (source / "icon.nn.png").write_bytes(
                _png_bytes(Image.new("RGBA", (3, 2), (1, 2, 3, 255)))
            )

            resources = process_resources(
                source,
                output,
                converters={
                    ".bin": lambda _source, destination: destination.write_bytes(b"converted")
                },
                no_stretch_images=True,
            )

            self.assertEqual(resources, ["icon.nn.png", "special.bin"])
            self.assertEqual((output / "special.bin").read_bytes(), b"converted")
            _, width, height, count = struct.unpack_from(
                "<4sHHH", (output / "icon.nn.png").read_bytes()
            )
            self.assertEqual((width, height, count), (3, 2, 1))

    def test_resource_index_sorting_stale_cleanup_and_safe_paths(self) -> None:
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            source = root / "source"
            destination = root / "output"
            source.mkdir()
            (source / "z.txt").write_text("z", encoding="utf-8")
            (source / "a.txt").write_text("a", encoding="utf-8")
            destination.mkdir()
            (destination / "stale.txt").write_text("stale", encoding="utf-8")
            (destination / "unmanaged.txt").write_text("keep", encoding="utf-8")
            (destination / "ResList.bin").write_bytes(
                _encode_resource_index(["stale.txt"])
            )

            resources = process_resources(source, destination)

            self.assertEqual(resources, ["a.txt", "z.txt"])
            self.assertFalse((destination / "stale.txt").exists())
            self.assertEqual((destination / "unmanaged.txt").read_text(), "keep")
            self.assertEqual((destination / "ResList.bin").read_bytes(),
                             _encode_resource_index(resources))

            (destination / "ResList.bin").write_bytes(
                _encode_resource_index(["../outside.txt"])
            )
            with self.assertRaises(ResourceProcessingError):
                process_resources(source, destination)


def _png_bytes(image: Image.Image) -> bytes:
    output = io.BytesIO()
    image.save(output, format="PNG")
    return output.getvalue()


if __name__ == "__main__":
    unittest.main()
