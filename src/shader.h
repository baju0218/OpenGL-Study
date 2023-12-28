#ifndef __SHADER_H__
#define __SHADER_H__

#include <glad/glad.h>

#include <memory>
#include <string>

class Shader {
public:
  static std::unique_ptr<Shader> Create(const std::string &filename,
                                        GLenum shaderType);

  ~Shader();

  uint32_t Get() const;

private:
  Shader() = default;

  bool LoadFile(const std::string &filename, GLenum shaderType);

private:
  uint32_t m_shader{0};
};

#endif // __SHADER_H__