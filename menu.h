#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace Ui {
class menu;
}

class MainWindow;

class menu : public QDialog
{
    Q_OBJECT

public:
    //explicit menu(QWidget *parent = nullptr);
    explicit menu(MainWindow *mainWindow = nullptr);
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
