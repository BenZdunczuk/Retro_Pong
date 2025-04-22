#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QWidget>
#include <QMainWindow>

namespace Ui {
class menu;
}

class MainWindow;

/**
 * @brief Klasa menu reprezentuje menu aplikacji Pong.
 *
 * Zawiera interfejs graficzny oparty na QDialog, który umożliwia dostęp do 4 przycisków:
 * wznowienia gry, rozpoczęcia nowej gry, wyjścia z gry oraz uruchomienia benchmarku
 */
class menu : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy menu.
     * @param parent Opcjonalny wskaźnik do rodzica.
     */
    explicit menu(MainWindow *mainWindow = nullptr);

    /**
     * @brief Destruktor klasy MainWindow.
     */
    ~menu();

private slots:
    void on_buttonGoBack_clicked();
    void on_buttonExit_clicked();

    void on_buttonNewGame_clicked();

    void on_buttonTest_clicked();

private:
    Ui::menu *ui;
    MainWindow *mainWindowPtr;
};

#endif // MENU_H
