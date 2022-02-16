#pragma once

#include "opengl.h"

#include <cassert>

using VertexArrayID = GLuint;

struct VertexArray
{
    VertexArray()
    {
        glGenVertexArrays(1, &this->id);
        glBindVertexArray(this->id);
        glBindVertexArray(0);
    }

    ~VertexArray()
    {
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &this->id);
    }

    inline void Bind() const { glBindVertexArray(this->id); }

    inline void Unbind() const { glBindVertexArray(0); }

    VertexArrayID id;
};

using VertexBufferID = GLuint;

struct VertexBuffer
{

    VertexBuffer(const GLsizeiptr size, bool dynamic = false)
        : bufferCapacity(size)
        , currentBufferIndex(0)
    {
        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ARRAY_BUFFER, this->id);

        glBufferData(GL_ARRAY_BUFFER,
                     size,
                     0,
                     dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ~VertexBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &this->id);
    }

    inline void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, this->id); }

    inline void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    GLintptr BufferVertexData(const void* data, GLsizeiptr size)
    {
        assert(this->currentBufferIndex + size < (this->bufferCapacity + 1) &&
               "VertexBuffer capacity exceeded.");

        GLintptr dataBufferIndex = this->currentBufferIndex;

        glBufferSubData(GL_ARRAY_BUFFER, this->currentBufferIndex, size, data);

        this->currentBufferIndex += size;

        return dataBufferIndex;
    }

    inline void Reset() { this->currentBufferIndex = 0; }

    VertexBufferID id;

    const GLsizeiptr bufferCapacity;
    GLintptr         currentBufferIndex;
};

using IndexBufferID = GLuint;

struct IndexBuffer
{

    IndexBuffer(const GLsizeiptr size)
        : bufferCapacity(size)
        , currentBufferIndex(0)
    {
        glGenBuffers(1, &this->id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ~IndexBuffer()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &this->id);
    }

    inline void Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
    }

    inline void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    GLintptr BufferIndexData(const void* data, GLsizeiptr size)
    {
        assert(this->currentBufferIndex + size < (this->bufferCapacity + 1) &&
               "IndexBuffer capacity exceeded.");

        GLintptr dataBufferIndex = this->currentBufferIndex;

        glBufferSubData(
            GL_ELEMENT_ARRAY_BUFFER, this->currentBufferIndex, size, data);

        this->currentBufferIndex += size;

        return dataBufferIndex;
    }

    inline void Reset() { this->currentBufferIndex = 0; }

    IndexBufferID id;

    const GLsizeiptr bufferCapacity;
    GLintptr         currentBufferIndex;
};
