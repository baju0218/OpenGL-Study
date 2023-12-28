#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <memory>
#include <string>

class Image {
public:
  static std::unique_ptr<Image> Create(int width, int height,
                                       int channelCount = 4);

  static std::unique_ptr<Image> Create(const std::string &filepath);

  ~Image();

  const uint8_t *GetData() const;

  int GetWidth() const;

  int GetHeight() const;

  int GetChannelCount() const;

  void SetCheckImage(int gridX, int gridY);

private:
  Image() = default;

  bool Allocate(int width, int height, int channelCount);

  bool Load(const std::string &filepath);

private:
  int m_width{0};
  int m_height{0};
  int m_channelCount{0};
  uint8_t *m_data{nullptr};
};

#endif // __IMAGE_H__