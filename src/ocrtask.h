
#pragma once

#include <filesystem>

namespace clippy {
class OcrTask {
public:
  OcrTask();
  ~OcrTask();
  void run(std::filesystem::path path);
};
} // namespace clippy
