#include "program.h"

#include <spdlog/spdlog.h>

std::unique_ptr<Program>
Program::Create(const std::vector<std::shared_ptr<Shader>> &shaders) {
  auto program = std::unique_ptr<Program>(new Program());
  if (!program->Link(shaders))
    return nullptr;

  return std::move(program);
}

Program::~Program() {
  if (m_program) {
    glDeleteProgram(m_program);
  }
}

uint32_t Program::Get() const { return m_program; }

void Program::Use() const { glUseProgram(m_program); }

bool Program::Link(const std::vector<std::shared_ptr<Shader>> &shaders) {
  m_program = glCreateProgram();

  for (auto &shader : shaders)
    glAttachShader(m_program, shader->Get());

  glLinkProgram(m_program);
  int success = 0;
  glGetProgramiv(m_program, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[1024];
    glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
    SPDLOG_ERROR("failed to link program: {}", infoLog);
    return false;
  }

  return true;
}
