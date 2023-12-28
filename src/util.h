#ifndef __UTIL_H__
#define __UTIL_H__

#include <optional>
#include <string>

std::optional<std::string> LoadTextFile(const std::string &filename);

#endif // __UTIL_H__