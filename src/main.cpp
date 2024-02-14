
#include <iostream>

#include <argparse/argparse.hpp>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page-renderer.h>
#include <poppler/cpp/poppler-page.h>

int main(int argc, char *argv[]) {
  argparse::ArgumentParser program("clippy");

  program.add_argument("library").help("The library to use");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cout << err.what() << "\n";
    std::cout << program;
    return 1;
  }

  auto library = program.get<std::string>("library");

  std::cout << "Parsing library: " << library << "\n";

  auto filename = "tour-of-cpp.pdf";
  auto doc = poppler::document::load_from_file(filename);
  if (!doc) {
    std::cerr << "Failed to open '" << filename << "'\n";
    return 1;
  }

  if (doc->is_locked()) {
    std::cerr << "Document is encrypted\n";
    return 1;
  }

  auto pages = doc->pages();
  if (pages == 0) {
    std::cerr << "No pages in document\n";
    return 1;
  }

  std::cout << "Document '" << filename << "' has " << pages << " pages\n";
  std::cout << "Title: " << doc->get_title().to_latin1() << "\n";
  std::cout << "Author: " << doc->get_author().to_latin1() << "\n";
  std::cout << "Creator: " << doc->get_creator().to_latin1() << "\n";

  std::cout << "Tablc of contents:\n";
  auto page_renderer = poppler::page_renderer();
  page_renderer.set_render_hints(poppler::page_renderer::antialiasing |
                                 poppler::page_renderer::text_antialiasing);

  auto page = doc->create_page(20);

  if (!page) {
    std::cerr << "Failed to open page 0\n";
    return 1;
  }

  auto text = page->text();
  std::cout << "Text: " << text.to_latin1() << "\n";

  auto img = page_renderer.render_page(page, 300, 300);

  if (!img.is_valid()) {
    std::cerr << "Failed to render page 0\n";
    return 1;
  }

  img.save("page-0.png", "png");

  return 0;
}
