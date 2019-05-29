#if 0
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Format.hpp"

#include <algorithm>
#include <vector>

namespace dst {
namespace sys {

    /*!
    TODO : Documentation
    */
    template <typename DataType = uint8_t>
    class ImageEx final
    {
    public:
        /*!
        TODO : Documentation
        */
        struct Info final
        {
            Format format { Format::Unknown };
            int width { 1 };
            int height { 1 };
        };

    public:
        /*!
        TODO : Documentation
        */
        ImageEx() = default;

        /*!
        TODO : Documentation
        */
        template <typename PixelType = uint8_t>
        inline ImageEx(
            const Info& info,
            const PixelType* data = nullptr
        )
        {
            reset<PixelType>(info, data);
        }

    public:
        /*!
        TODO : Documentation
        */
        const Info& get_info() const;

        /*!
        TODO : Documentation
        */
        template <typename PixelType = uint8_t>
        inline Span<const PixelType> get_pixels() const
        {
            auto data = !mManagedData.empty() ? mManagedData.data() : nullptr;
            auto count = size_bytes() / sizeof(PixelType);
            return Span<PixelType>(reinterpret_cast<PixelType*>(data), count);
        }

        /*!
        TODO : Documentation
        */
        template <typename PixelType = uint8_t>
        inline Span<PixelType> get_pixels()
        {
            auto data = !mManagedData.empty() ? mManagedData.data() : nullptr;
            auto count = size_bytes() / sizeof(PixelType);
            return Span<PixelType>(reinterpret_cast<PixelType*>(data), count);
        }

        /*!
        TODO : Documentation
        */
        template <typename PixelType = uint8_t>
        inline const PixelType& get_pixel(glm::ivec2 uv) const
        {
            uv.x = std::clamp(uv.x, 0, mInfo.width - 1);
            uv.y = std::clamp(uv.y, 0, mInfo.height - 1);
            return get_pixels<const PixelType>()[uv.y * mInfo.width + uv.x];
        }

        /*!
        TODO : Documentation
        */
        template <typename PixelType = uint8_t>
        inline PixelType& get_pixel(glm::ivec2 uv)
        {
            uv.x = std::clamp(uv.x, 0, mInfo.width - 1);
            uv.y = std::clamp(uv.y, 0, mInfo.height - 1);
            return get_pixels<PixelType>()[uv.y * mInfo.width + uv.x];
        }

        /*!
        TODO : Documentation
        */
        void resize(const Info& info);

        /*!
        TODO : Documentation
        */
        template <typename PixelType = uint8_t>
        inline void reset(
            const Info& info,
            const PixelType* data = nullptr
        )
        {
            resize(info);
            if (data) {
                memcpy(mManagedData.data(), data, size_bytes());
            }
        }

        /*!
        TODO : Documentation
        */
        void clear();

        /*!
        TODO : Documentation
        */
        size_t size_bytes() const;

        /*!
        TODO : Documentation
        */
        void read_png(
            const dst::filesystem::path& filePath,
            Format format = Format::R8G8B8A8_Unorm
        );

        /*!
        TODO : Documentation
        */
        static void write_png(
            const ImageEx& image,
            const dst::filesystem::path& filePath
        );

    private:
        Info mInfo { };
        DataType* mData { nullptr };
#if 0
        std::vector<uint8_t> mManagedData;
        uint8_t* mUnmanagedMutableData { nullptr };
        const uint8_t* mUnmanagedReadonlyData { nullptr };
#endif
    };

} // namespace sys
} // namespace dst
#endif