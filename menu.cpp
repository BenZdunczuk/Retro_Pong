#include "mainwindow.h"
#include "test.h"
#include "menu.h"
#include "ui_menu.h"

menu::menu(MainWindow *parent)
    : QDialog(parent)
    , ui(new Ui::menu)
    , mainWindowPtr(parent)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_buttonGoBack_clicked()
{
    menu::close();
}


void menu::on_buttonExit_clicked()
{
    menu::close();
    mainWindowPtr->closeMainWindow();
}


void menu::on_buttonNewGame_clicked()
{
    menu::close();
    //reset gry
}


void menu::on_buttonTest_clicked()
{
    test pTest(this);

    pTest.exec();
}

