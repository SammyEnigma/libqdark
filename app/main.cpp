
#include <QApplication>
#include <QDarkThemePlugin.h>
#include "example.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("libqdarkExampleApp");

    MainWindow mainWindow;
    mainWindow.show();

    QDarkThemePlugin darker;
    darker.initialize();

    return app.exec();
}
