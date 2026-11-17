/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file LICENSE.rst or https://cmake.org/licensing for details.  */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  char const* argsFile = std::getenv("CMAKE_TEST_EXTRACTOR_ARGS");
  char const* mode = std::getenv("CMAKE_TEST_EXTRACTOR_MODE");
  if (!argsFile || !mode) {
    return 90;
  }
  std::ofstream record(argsFile, std::ios::app);
  record << "BEGIN\n";
  std::string output;
  int binlogs = 0;
  for (int i = 1; i < argc; ++i) {
    std::string const arg = argv[i];
    record << arg << '\n';
    if (arg == "--binlog" && i + 1 < argc) {
      std::ifstream log(argv[i + 1], std::ios::binary);
      if (!log || log.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Binlog is missing, empty, or still open by MSBuild\n";
        return 91;
      }
      ++binlogs;
    } else if (arg == "--output-file" && i + 1 < argc) {
      output = argv[i + 1];
    }
  }
  if (!record || !binlogs || output.empty()) {
    return 92;
  }
  int const result = std::atoi(mode);
  if (result == 0 || result == 2) {
    std::ofstream database(output);
    database << "from extractor\n";
    if (!database) {
      return 93;
    }
  }
  return result;
}
