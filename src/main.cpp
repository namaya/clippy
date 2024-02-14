
#include <iostream>

#include <argparse/argparse.hpp>

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

  std::cout << "Library: " << library << "\n";

  return 0;
}
