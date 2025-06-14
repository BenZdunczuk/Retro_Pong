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
    QString translationFileName = "pong_pl_PL.qm";

    QTranslator *translatorMain = new QTranslator;
    if (translatorMain->load(translationFileName)){
        a.installTranslator(translatorMain);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
