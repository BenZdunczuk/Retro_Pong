#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeMainWindow() {
    this->close();
}

void MainWindow::on_buttonPause_clicked()
{
    //menu *pMenu = new menu(this);
    menu pMenu(this);

    pMenu.exec();
}
