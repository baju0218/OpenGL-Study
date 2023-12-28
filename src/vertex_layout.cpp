#include "vertex_layout.h"

#include <glad/glad.h>

std::unique_ptr<VertexLayout> VertexLayout::Create() {
  auto vertexLayout = std::unique_ptr<VertexLayout>(new VertexLayout());
  vertexLayout->Init();

  return std::move(vertexLayout);
}

VertexLayout::~VertexLayout() {
  if (m_vertexArrayObject) {
    glDeleteVertexArrays(1, &m_vertexArrayObject);
  }
}

uint32_t VertexLayout::Get() const { return m_vertexArrayObject; }

void VertexLayout::SetAttrib(uint32_t attribIndex, int count, uint32_t type,
                             bool normalized, size_t stride,
                             uint64_t offset) const {
  glEnableVertexAttribArray(attribIndex);
  glVertexAttribPointer(attribIndex, count, type, normalized, stride,
                        reinterpret_cast<const void *>(offset));
}

void VertexLayout::DisableAttrib(int attribIndex) const {
  glDisableVertexAttribArray(attribIndex);
}

void VertexLayout::Init() {
  glGenVertexArrays(1, &m_vertexArrayObject);
  glBindVertexArray(m_vertexArrayObject);
}