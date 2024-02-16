
#include <filesystem>
#include <iostream>

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page-renderer.h>
#include <poppler/cpp/poppler-page.h>

#include "pdfparser.h"

using namespace clippy;

PdfParser::PdfParser() {}

PdfParser::~PdfParser() {}

std::filesystem::path PdfParser::parse(std::filesystem::path path) {
  auto doc = std::unique_ptr<poppler::document>{
      poppler::document::load_from_file(path.string())};

  if (doc == nullptr) {
    throw std::runtime_error("Couldn't parse path ''" + path.string() + "'. ");
  }

  auto page_renderer = poppler::page_renderer{};
  page_renderer.set_render_hints(poppler::page_renderer::antialiasing |
                                 poppler::page_renderer::text_antialiasing);

  for (auto i = 0; i < 10; i++) {
    auto page = std::unique_ptr<poppler::page>{doc->create_page(i)};
    if (page == nullptr) {
      std::cerr << "Failed to parse page " << i << ". Skipping\n";
      continue;
    }

    auto img = page_renderer.render_page(page.get(), 300, 300);
    if (!img.is_valid()) {
      std::cerr << "Failed to render page " << i << ". Skipping\n";
      continue;
    }

    img.save("page-" + std::to_string(i) + ".png", "png");
  }

  return path;
}
