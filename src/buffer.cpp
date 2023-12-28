#include "buffer.h"

#include <glad/glad.h>

#include <iostream>

std::unique_ptr<Buffer> Buffer::Create(uint32_t bufferType, uint32_t usage,
                                       const void *data, size_t dataSize) {
  auto buffer = std::unique_ptr<Buffer>(new Buffer());
  if (!buffer->Init(bufferType, usage, data, dataSize))
    return nullptr;

  return std::move(buffer);
}

Buffer::~Buffer() {
  if (m_buffer) {
    glDeleteBuffers(1, &m_buffer);
  }
}

uint32_t Buffer::Get() const { return m_buffer; }

bool Buffer::Init(uint32_t bufferType, uint32_t usage, const void *data,
                  size_t dataSize) {
  m_bufferType = bufferType;
  m_usage = usage;

  glGenBuffers(1, &m_buffer);
  glBindBuffer(m_bufferType, m_buffer);
  glBufferData(m_bufferType, dataSize, data, usage);

  return true;
}