#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "buffer.h"
#include "program.h"
#include "texture.h"
#include "vertex_layout.h"

#include <memory>

class Context {
public:
  static std::unique_ptr<Context> Create();

  void Render();

private:
  Context() = default;

  bool Init();

private:
  std::unique_ptr<Program> m_program;
  std::unique_ptr<VertexLayout> m_vertexLayout;
  std::unique_ptr<Buffer> m_vertexBuffer;
  std::unique_ptr<Buffer> m_indexBuffer;
  std::unique_ptr<Texture> m_texture;
  std::unique_ptr<Texture> m_texture2;
};

#endif // __CONTEXT_H__