#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "buffer.h"
#include "program.h"
#include "texture.h"
#include "vertex_layout.h"

#include <memory>

struct GLFWwindow;

class Context {
public:
  static std::unique_ptr<Context> Create();

  void Reshape(int width, int height);

  void ProcessInput(GLFWwindow *window);

  void MouseButton(int button, int action, double x, double y);

  void MouseMove(double x, double y);

  void Render();

private:
  Context() = default;

  bool Init();

private:
  int m_width{WINDOW_WIDTH};
  int m_height{WINDOW_HEIGHT};

  glm::vec3 m_cameraPos{glm::vec3(0.0f, 0.0f, 3.0f)};
  glm::vec3 m_cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)};
  glm::vec3 m_cameraUp{glm::vec3(0.0f, 1.0f, 0.0f)};

  float m_cameraPitch{0.0f};
  float m_cameraYaw{0.0f};

  bool m_cameraControl{false};
  glm::vec2 m_prevMousePos{glm::vec2(0.0f)};

  std::unique_ptr<Program> m_program;
  std::unique_ptr<VertexLayout> m_vertexLayout;
  std::unique_ptr<Buffer> m_vertexBuffer;
  std::unique_ptr<Buffer> m_indexBuffer;
  std::unique_ptr<Texture> m_texture;
  std::unique_ptr<Texture> m_texture2;

  glm::vec4 m_clearColor{glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)};
};

#endif // __CONTEXT_H__