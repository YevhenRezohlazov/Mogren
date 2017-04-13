#pragma once

#include <memory>

namespace Graphics
{
    class NativeIndexBuffer;
    
    ///
    /// Index buffer class.
    ///
    class IndexBuffer final
    {
    public:
        ///
        /// Initializes a new instance of the Buffer class.
        ///
        /// \param itemCount The count of elements in this buffer.
        /// \param isDynamic Set to true if buffer data will be updated frequently.
        explicit IndexBuffer(uint32_t itemCount, bool isDynamic = false);

        ///
        /// The INativeBuffer instance
        ///
        const NativeIndexBuffer& getNativeBuffer() const;

        ///
        /// Gets the count of elements in this buffer.
        ///
        int getItemCount() const;

        ///
        /// Gets a value indicating whether this buffer is dynamic.
        ///
        bool isDynamic() const;

        ///
        /// Sets the data to the buffer.
        ///
        /// \param items The pointer to the items data to be written to the buffer.
        /// \param countItems The count of the items to be written.
        /// \param offset Offset in the buffer where the data should be written (in items).
        void setData(const uint16_t *items, uint32_t countItems, uint32_t bufferOffset = 0);

        ~IndexBuffer();

    private:
        std::unique_ptr<NativeIndexBuffer> mNativeBuffer;
        uint32_t mItemCount;
        bool mIsDynamic;
    };
}

