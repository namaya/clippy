
#include <filesystem>
#include <iostream>

#include <argparse/argparse.hpp>
#include <fswatch/c++/monitor_factory.hpp>

#include "ocrtask.h"
#include "pdfextract.h"

struct AppContext {
  clippy::PdfExtract pdfextract;
  clippy::OcrTask ocrtask;
};

void process_event(const std::vector<fsw::event> &events, void *context) {
  auto &appctx = *static_cast<AppContext *>(context);

  for (const auto &event : events) {
    std::cout << "Event: " << event.get_path() << "\n";

    auto flags = event.get_flags();

    if (std::find(flags.begin(), flags.end(), fsw_event_flag::IsFile) !=
            flags.end() &&
        (std::find(flags.begin(), flags.end(), fsw_event_flag::Created) !=
             flags.end() ||
         std::find(flags.begin(), flags.end(), fsw_event_flag::Renamed) !=
             flags.end())) {

      auto path = std::filesystem::path{event.get_path()};

      if (std::filesystem::exists(path) &&
          path.extension().string() == ".pdf") {
        std::cout << "Extracting and recognizing " << path << "\n";
        auto images = appctx.pdfextract.extract(path);

        appctx.ocrtask.recognize(images);
      }
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
  auto program = argparse::ArgumentParser{"clippy"};

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

  auto paths = std::vector<std::string>{library_path.string()};

  auto appctx = AppContext{clippy::PdfExtract{}, clippy::OcrTask{}};

  auto fsmonitor = fsw::monitor_factory::create_monitor(
      fsw_monitor_type::system_default_monitor_type, paths, process_event,
      &appctx);

  fsmonitor->start();

  return 0;
}
