
#include <filesystem>
#include <iostream>

#include <argparse/argparse.hpp>

#include "pdfparser.h"

int main(int argc, char *argv[]) {
  argparse::ArgumentParser program{"clippy"};

  program.add_argument("library").help("The library to use");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cout << err.what() << "\n";
    std::cout << program;
    return 1;
  }

  auto library_arg = program.get<std::string>("library");
  auto library_path = std::filesystem::path{library_arg};

  std::cout << "Parsing library: " << library_path << "\n";

  if (!std::filesystem::exists(library_path) ||
      !std::filesystem::is_directory(library_path)) {
    std::cerr << "Couldn't index library. Path '" << library_path
              << "' does not exist or is not a directory\n";
    return 1;
  }

  auto parser = PdfParser{};

  for (const auto &entry : std::filesystem::directory_iterator(library_path)) {
    if (entry.is_regular_file()) {
      if (entry.path().extension().string() == ".pdf") {
        parser.parse(entry.path());
      }
    }
  }

  return 0;
}
