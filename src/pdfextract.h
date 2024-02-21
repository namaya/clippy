
#pragma once

#include <filesystem>
#include <iostream>
#include <opencv2/core/mat.hpp>

namespace clippy {
class PdfExtract {
public:
  PdfExtract();
  ~PdfExtract();
  std::vector<cv::Mat> extract(std::filesystem::path path);
};
} // namespace clippy
