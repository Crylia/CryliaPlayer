#pragma once

#include <QString>

class CliArgHandler {
public:
  static CliArgHandler &getInstance() {
    static CliArgHandler instance;
    return instance;
  }

private:
  CliArgHandler() = default;

public:
  ~CliArgHandler() = default;
  CliArgHandler(CliArgHandler const &) = delete;
  void operator=(CliArgHandler const &) = delete;

  void setInputFile(QString _inputFile) { m_inputFile = _inputFile; }
  const QString getInputFile() const { return m_inputFile; }

  QString m_inputFile;
};
