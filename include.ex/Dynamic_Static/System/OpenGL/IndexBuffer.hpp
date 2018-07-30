
/*
==========================================
    Copyright 2017-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#if defined(DYNAMIC_STATIC_SYSTEM_OPENGL_ENABLED)

#include "Dynamic_Static/System/OpenGL/Buffer.hpp"
#include "Dynamic_Static/System/OpenGL/Defines.hpp"

#include <utility>

namespace Dynamic_Static {
namespace System {
namespace OpenGL {

    /*
    * Provides high level control over an OpenGL index buffer.
    */
    class IndexBuffer final
        : public Buffer
    {
    public:
        /*
        * Constructs an instance of IndexBuffer.
        */
        IndexBuffer()
            : Buffer(GL_ELEMENT_ARRAY_BUFFER)
        {
            set_name("IndexBuffer");
        }

        /*
        * Moves an instance of IndexBuffer.
        * @param [in] other The IndexBuffer to move from
        */
        IndexBuffer(IndexBuffer&& other)
        {
            *this = std::move(other);
        }

        /*
        * Moves an instance of IndexBuffer.
        * @param [in] other The IndexBuffer to move from
        * @return This IndexBuffer
        */
        IndexBuffer& operator=(IndexBuffer&& other)
        {
            if (this != &other) {
                Buffer::operator=(std::move(other));
            }
            return *this;
        }

    public:
        /*
        * Gets this IndexBuffer's index type.
        * @return This IndexBuffer's index type
        */
        GLenum get_type() const
        {
            switch (get_element_size()) {
                case sizeof(uint8_t): return GL_UNSIGNED_BYTE;
                case sizeof(uint16_t): return GL_UNSIGNED_SHORT;
                case sizeof(uint32_t): return GL_UNSIGNED_INT;
                default: return GL_UNSIGNED_INT;
            }
        }
    };

} // namespace OpenGL
} // namespace System
} // namespace Dynamic_Static

#endif // defined(DYNAMIC_STATIC_OPENGL_ENABLED)
