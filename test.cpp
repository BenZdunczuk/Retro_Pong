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
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(wykres);
}

test::~test()
{
    delete ui;
}
