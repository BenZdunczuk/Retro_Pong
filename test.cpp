#include "test.h"
#include "ui_test.h"
#include "chart.h"

#include <QWidget>
#include <QVBoxLayout>

test::test(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::test)
{
    // chart *wykres = new chart(ui->chartWidget);
    // wykres->show();

    ui->setupUi(this);

    chart *wykres = new chart(ui->chartWidget);
    QVBoxLayout *layout = new QVBoxLayout(ui->chartWidget);
    layout->addWidget(wykres);

    chart *wykres2 = new chart(ui->chartWidget2,10);
    QVBoxLayout *layout2 = new QVBoxLayout(ui->chartWidget2);
    layout2->addWidget(wykres2);
}

test::~test()
{
    delete ui;
}
