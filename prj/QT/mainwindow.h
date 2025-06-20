#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QTranslator>
#include "ponging.h"
#include "menu.h"
#include "connection.h"

#pragma once

/**
* \file
* \brief Definicja metody klasy MainWindow
*
* Zawiera definicję metod klasy MainWindow.
*/

// class PongWidget;
class test;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Klasa MainWindow reprezentuje główne okno aplikacji Pong.
 *
 * Zawiera interfejs graficzny oparty na QMainWindow, który integruje komponent do gry Pong
 * oraz przycisk sterujący pauzowaniem gry.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy MainWindow.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy MainWindow.
     */
    ~MainWindow();

    /**
     * @brief Metoda zamykająca główne okno aplikacji.
     */
    void closeMainWindow();

    /**
     * @brief Przełącza stan gry (pomiędzy stanami: gra włączona i zatrzymana).
     */
    void togglePause();

    /**
     * @brief Zmienna stan logiczny zmiennej informującej o otwartym oknie testu
     */
    void toggleTestOpen();

    /**
     * @brief Metoda typu getter zwracająca wartość zmiennej isTestOpen
     */
    bool getTestOpen();

    /**
     * @brief Zmienna przechowująca wskaźnik do obiektu połączenia
     */
    connection* connectMain;

    /**
     * @brief Zmienna przechowująca wskaźnik do obiektu testowania połączenia
     */
    test* pTest;

    /**
     * @brief Zmienna przechowująca wskaźnik do obiektu menu
     */
    menu* pMenu;

    /**
     * @brief Zmienna wskaźnikowa przechowująca obiekt tłumacza
     */
    QTranslator *translatorMainWindow;

    /**
     * @brief Metoda zmieniająca język całej aplikacji
     */
    void switchLanguage(const QString &languageCode);

    /**
     * @brief Metoda typu setter ustawiająca obiekt tłumacza
     */
    void setTranslator(QTranslator *newTranslator);


private slots:
    /**
     * @brief Metoda obsługująca kliknięcie przycisku pauzy.
     */
    void on_buttonPause_clicked();

private:
    /**
     * @brief Wskaźnik do obiektu interfejsu użytkownika.
     */
    Ui::MainWindow *ui;

    /**
     * @brief Wskaźnik do widżetu gry Pong.
     */
    PongWidget *pongGame;

    /**
     * @brief Flaga informująca, czy gra jest obecnie zatrzymana.
     */
    bool isPaused;

    /**
     * @brief Zmienna boolowska określająca czy otworzone jest okno testu
     */
    bool isTestOpen;

public slots:
    /**
     * @brief Slot wznawiający grę
     */
    void resumedGame();

    /**
     * @brief Slot resetujący grę
     */
    void restartedGame();

    /**
     * @brief Slot obsługujący zamknięcie okna test
     */
    void testClosed();

    /**
     * @brief Slot otwierający okienko testu
     */
    void openTest();

    /**
     * @brief Slot odblokowujący przycisk pauzy
     */
    void unlockPauseButton();

signals:
    /**
     * @brief Sygnał wznawiający grę
     *
     * Zostaje wysyłany w slocie resumedGame() i odbierany przez klasę widgetu gry Pong
     */
    void resumed();

    /**
     * @brief Sygnał resetujący grę
     *
     * Zostaje wysyłany w slocie restartedGame() i odbierany przez klasę widgetu gry Pong
     */
    void restarted();
};

#endif // MAINWINDOW_H
