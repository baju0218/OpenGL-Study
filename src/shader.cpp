#include "shader.h"

#include "util.h"

#include <spdlog/spdlog.h>

std::unique_ptr<Shader> Shader::Create(const std::string &filename,
                                       GLenum shaderType) {
  auto shader = std::unique_ptr<Shader>(new Shader());
  if (!shader->LoadFile(filename, shaderType))
    return nullptr;

  return std::move(shader);
}

Shader::~Shader() {
  if (m_shader) {
    glDeleteShader(m_shader);
  }
}

uint32_t Shader::Get() const { return m_shader; }

bool Shader::LoadFile(const std::string &filename, GLenum shaderType) {
  auto result = LoadTextFile(filename);
  if (!result.has_value())
    return false;

  const auto &code = result.value();
  const auto *codePtr = code.c_str();
  const int32_t codeLength = static_cast<const int32_t>(code.length());

  // create and compile shader
  m_shader = glCreateShader(shaderType);
  glShaderSource(m_shader, 1, static_cast<const GLchar *const *>(&codePtr),
                 &codeLength);
  glCompileShader(m_shader);

  // check compile error
  int success = 0;
  glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[1024];
    glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
    SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
    SPDLOG_ERROR("reason: {}", infoLog);
    return false;
  }

  return true;
}
