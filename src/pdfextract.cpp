
#include <filesystem>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page-renderer.h>
#include <poppler/cpp/poppler-page.h>

#include "pdfextract.h"

using namespace clippy;

PdfExtract::PdfExtract() {}

PdfExtract::~PdfExtract() {}

std::vector<cv::Mat> PdfExtract::extract(std::filesystem::path path) {
  auto doc = std::unique_ptr<poppler::document>{
      poppler::document::load_from_file(path.string())};

  if (doc == nullptr) {
    throw std::runtime_error("Couldn't extract path ''" + path.string() +
                             "'. ");
  }

  auto page_renderer = poppler::page_renderer{};
  page_renderer.set_render_hints(poppler::page_renderer::antialiasing |
                                 poppler::page_renderer::text_antialiasing);
  page_renderer.set_image_format(poppler::image::format_bgr24);

  auto images = std::vector<cv::Mat>{};

  for (auto i = 0; i < doc->pages(); i++) {
    std::cout << "Extracting page " << i << "\n";
    auto page = std::unique_ptr<poppler::page>{doc->create_page(i)};
    if (page == nullptr) {
      std::cerr << "Failed to extract page " << i << ". Skipping\n";
      continue;
    }

    std::cout << "Rendering page " << i << "\n";

    auto img = page_renderer.render_page(page.get(), 120, 120);
    if (!img.is_valid()) {
      std::cerr << "Failed to extract page " << i << ". Skipping\n";
      continue;
    }

    auto cvimg = cv::Mat{img.height(), img.width(), CV_8UC3, img.data(),
                         (size_t)img.bytes_per_row()};

    images.push_back(cvimg);

    if (i == 10) {
      break;
    }
  }

  return images;
}
