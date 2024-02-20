
#include <filesystem>
#include <iostream>

#include <argparse/argparse.hpp>
#include <fswatch/c++/monitor_factory.hpp>

#include "ocrtask.h"
#include "pdfparser.h"

void process_event(const std::vector<fsw::event> &events, void *context) {
  for (const auto &event : events) {
    auto path = std::filesystem::path{event.get_path()};
    std::cout << "Path '" << path << "' was changed at '" << event.get_time()
              << "'\n";

    if (path.extension().string() == ".pdf") {
      // process file
    }
  }

  // auto parser = clippy::PdfParser{};
  // auto ocrtask = clippy::OcrTask{};
  // for (const auto &entry : std::filesystem::directory_iterator{library_path})
  // {
  //   if (entry.is_regular_file()) {
  //     if (entry.path().extension().string() == ".pdf") {
  //       auto tempPath = parser.parse(entry.path());
  //       ocrtask.run(tempPath);
  //     }
  //   }
  // }
}

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

  std::vector<std::string> paths{library_path.string()};

  auto monitor = fsw::monitor_factory::create_monitor(
      fsw_monitor_type::system_default_monitor_type, paths, process_event,
      nullptr);

  monitor->start();

  return 0;
}
