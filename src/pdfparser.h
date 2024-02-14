
#pragma once

#include <filesystem>
#include <iostream>

class PdfParser {
public:
  PdfParser();
  ~PdfParser();
  void parse(std::filesystem::path path);
};
