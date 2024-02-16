
#pragma once

#include <filesystem>
#include <iostream>

namespace clippy {
class PdfParser {
public:
  PdfParser();
  ~PdfParser();
  std::filesystem::path parse(std::filesystem::path path);
};
} // namespace clippy
