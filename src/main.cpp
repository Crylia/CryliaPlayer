#include "View/MainWindow.hpp"

#include <QApplication>
#include <filesystem>
#include <fmt/core.h>
#include <iostream>

bool CheckValidFile(std::filesystem::path path) {
  // Allow to start with a song
  if (!std::filesystem::exists(path) ||
      !std::filesystem::is_regular_file(path)) {
    fmt::print("ERROR: Path or file doesn't exist / is valid");
    return false;
  }
  std::string extension = path.extension().string();
  if (!(extension == ".mp3" || extension == ".flac")) {
    std::cerr
        << "ERROR: Filetype is not supported, supported types are .mp3, .flac"
        << std::endl;
    return false;
  }

  return true;
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow *w = argc > 1 && CheckValidFile(std::filesystem::path(argv[1]))
                      ? new MainWindow(/*std::filesystem::path(argv[1])*/)
                      : new MainWindow();
  w->setMinimumHeight(600);
  w->show();

  return a.exec();
}
