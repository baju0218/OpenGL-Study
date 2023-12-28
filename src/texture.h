#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <memory>

class Image;

class Texture {
public:
  static std::unique_ptr<Texture> Create(const Image *image);

  ~Texture();

  const uint32_t Get() const;

  void SetFilter(uint32_t minFilter, uint32_t magFilter) const;

  void SetWrap(uint32_t sWrap, uint32_t tWrap) const;

private:
  Texture() = default;

  void Init(const Image *image);

private:
  uint32_t m_texture{0};
};

#endif // __TEXTURE_H__