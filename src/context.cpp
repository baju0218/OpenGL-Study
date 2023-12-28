#include "context.h"

#include "image.h"
#include "shader.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

// clang-format off
float g_vertices[] = {
  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
  -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

uint32_t g_indices[] = {
  0, 1, 3,
  1, 2, 3,
};
// clang-format on

std::unique_ptr<Context> Context::Create() {
  auto context = std::unique_ptr<Context>(new Context());
  if (!context->Init())
    return nullptr;

  return std::move(context);
}

bool Context::Init() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  m_vertexLayout = VertexLayout::Create();
  m_vertexBuffer = Buffer::Create(GL_ARRAY_BUFFER, GL_STATIC_DRAW, g_vertices,
                                  sizeof(g_vertices));
  m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
  m_vertexLayout->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                            sizeof(float) * 3);
  m_vertexLayout->SetAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
                            sizeof(float) * 6);
  m_indexBuffer = Buffer::Create(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW,
                                 g_indices, sizeof(g_indices));

  std::shared_ptr<Shader> vertShader =
      Shader::Create("./shader/simple.vs", GL_VERTEX_SHADER);
  std::shared_ptr<Shader> fragShader =
      Shader::Create("./shader/simple.fs", GL_FRAGMENT_SHADER);
  if (!vertShader || !fragShader)
    return false;
  SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
  SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

  m_program = Program::Create({fragShader, vertShader});
  if (!m_program)
    return false;
  SPDLOG_INFO("program id: {}", m_program->Get());

  // auto image = Image::Create(256, 256);
  // image->SetCheckImage(4, 4);
  auto image = Image::Create("./image/container.jpg");
  if (!image)
    return false;
  SPDLOG_INFO("image: {}x{}, {} channels", image->GetWidth(),
              image->GetHeight(), image->GetChannelCount());

  m_texture = Texture::Create(image.get());

  auto image2 = Image::Create("./image/awesomeface.png");
  if (!image2)
    return false;
  SPDLOG_INFO("image: {}x{}, {} channels", image2->GetWidth(),
              image2->GetHeight(), image2->GetChannelCount());

  m_texture2 = Texture::Create(image2.get());

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture->Get());
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_texture2->Get());

  m_program->Use();
  glUniform1i(glGetUniformLocation(m_program->Get(), "tex"), 0);
  glUniform1i(glGetUniformLocation(m_program->Get(), "tex2"), 1);

  return true;
}

void Context::Render() {
  glClear(GL_COLOR_BUFFER_BIT);

  m_program->Use();
  glDrawElements(GL_TRIANGLES, sizeof(g_indices) / sizeof(uint32_t),
                 GL_UNSIGNED_INT, 0);
}