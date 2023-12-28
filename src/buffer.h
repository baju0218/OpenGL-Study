#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <memory>

class Buffer {
public:
  static std::unique_ptr<Buffer> Create(uint32_t bufferType, uint32_t usage,
                                        const void *data, size_t dataSize);

  ~Buffer();

  uint32_t Get() const;

private:
  Buffer() = default;

  bool Init(uint32_t bufferType, uint32_t usage, const void *data,
            size_t dataSize);

private:
  uint32_t m_buffer{0};
  uint32_t m_bufferType{0};
  uint32_t m_usage{0};
};

#endif // __BUFFER_H__