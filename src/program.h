#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "shader.h"

#include <memory>
#include <vector>

class Program {
public:
  static std::unique_ptr<Program>
  Create(const std::vector<std::shared_ptr<Shader>> &shaders);

  ~Program();

  uint32_t Get() const;

  void Use() const;

private:
  Program() = default;

  bool Link(const std::vector<std::shared_ptr<Shader>> &shaders);

private:
  uint32_t m_program{0};
};

#endif // __PROGRAM_H__