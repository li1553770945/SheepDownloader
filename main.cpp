#include "mainwindow.h"
#include "constant.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
Config* config = new Config;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "sheepdownloader_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
