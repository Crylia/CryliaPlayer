#include "View/MainWindow.h"

#include <QApplication>
#include <filesystem>
#include <fmt/printf.h>
#include <iostream>
#include <memory>

#include "core/CliArgHandler/CliArgHandler.h"

// Checks if the given path leads to a valid audio formatted file. Does only do
// basic checks and not check the actual codec
bool CheckValidFile(std::filesystem::path path) {
  if (!std::filesystem::exists(path) ||
      !std::filesystem::is_regular_file(path)) {
    fprintf(stderr, "ERROR: Path or file doesn't exist / is valid");
    return false;
  }
  auto extension = path.extension().string();
  if (!(extension == ".mp3" || extension == ".flac")) {
    fprintf(
        stderr,
        "ERROR: Filetype is not supported, supported types are .mp3, .flac");
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  const QApplication a(argc, argv);

  // Add the song path to the cli singleton that will make it accessible for
  // other classes to use
  if (argc > 0 && CheckValidFile(argv[1]))
    CliArgHandler::getInstance().setInputFile(argv[1]);

  const auto w{std::make_unique<MainWindow>()};
  w->setMinimumHeight(600);
  w->show();
  return a.exec();
}
