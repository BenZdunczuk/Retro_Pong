#include "mainwindow.h"
#include "connection.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

/**
* \file
* \brief Plik main.cpp
*
* Zawiera inicjalizację QApllication, utworzenie i wymuszenie okna MainWidget
* zawierającego grę i dostęp do menu oraz uruchamia pętlę obsługi aplikacji
*
* Posiada moduł do tłumaczenia aplikacji na język angielski (aktualnie nieużywany)
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "pong_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();

    return a.exec();
}
