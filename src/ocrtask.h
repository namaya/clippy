
#pragma once

#include <filesystem>
#include <opencv2/core/mat.hpp>

namespace clippy {
class OcrTask {
public:
  OcrTask();
  ~OcrTask();
  void recognize(std::vector<cv::Mat> images);
};
} // namespace clippy
