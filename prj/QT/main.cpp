#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

/**
* \file
* \brief Plik main.cpp
*
* Zawiera inicjalizację QApllication, utworzenie i wymuszenie okna MainWidget
* zawierającego grę i dostęp do menu oraz uruchamia pętlę obsługi aplikacji
*
* Posiada moduł do tłumaczenia aplikacji z języka polskiego na język angielski
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLocale::setDefault(QLocale(QLocale::Polish, QLocale::Poland));
    // QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

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
