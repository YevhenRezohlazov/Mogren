#pragma once

#include <Mogren/Framework/IO/InputStream.h>
#include <android/asset_manager.h>
#include <string>

namespace ResourceManagement
{
	class AssetStream : public IO::InputStream
	{
	public:
		///
		/// Initializes new instance of a AssetStream class opening asset at the specified path
		///
        explicit AssetStream(const std::string& assetPath);

        AssetStream(const AssetStream&) = delete;
        AssetStream& operator=(const AssetStream&) = delete;

    public:
		///
		/// Sets current position in the stream
		///
		virtual void setPosition(uint32_t position) override;

		///
		/// Gets the current position in the stream
		///
		virtual uint32_t getPosition() const override;

		///
		/// Gets the stream length
		///
		virtual uint32_t getLength() const override;

		///
		/// Returns true, if we can read from the stream
		///
		virtual bool canRead() const override;

		///
		/// Reads the data from the stream to the buffer
		/// \param buffer The buffer where the data will be stored
		/// \count Data size to be read (in bytes)
		/// \returns Count of bytes actually read.
		virtual uint32_t read(void *buffer, uint32_t size) override;

		virtual ~AssetStream();

	private:
		AAsset *mAsset;
		uint32_t mPosition;
	};
}
