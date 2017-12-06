
#include <QApplication>

#include "base/consts.h"
#include "ui/main_window.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  app.setApplicationVersion(installer::kAppVersion);

  installer::MainWindow window;
  window.fullscreen();

  return app.exec();
}