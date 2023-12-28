#ifndef __VERTEX_LAYOUT_H__
#define __VERTEX_LAYOUT_H__

#include <memory>

class VertexLayout {
public:
  static std::unique_ptr<VertexLayout> Create();

  ~VertexLayout();

  uint32_t Get() const;

  void SetAttrib(uint32_t attribIndex, int count, uint32_t type,
                 bool normalized, size_t stride, uint64_t offset) const;

  void DisableAttrib(int attribIndex) const;

private:
  VertexLayout() = default;

  void Init();

private:
  uint32_t m_vertexArrayObject{0};
};

#endif // __VERTEX_LAYOUT_H__