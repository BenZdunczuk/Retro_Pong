/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test
{
public:
    QWidget *chartWidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QFormLayout *formLayout_5;
    QLabel *label;
    QLineEdit *lineEdit_7;
    QLabel *label_15;
    QLabel *label_8;
    QGridLayout *gridLayout_3;
    QLabel *label_12;
    QLineEdit *lineEdit_8;
    QLabel *label_13;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLabel *label_14;
    QGridLayout *gridLayout_2;
    QLabel *label_11;
    QLineEdit *lineEdit_4;
    QLabel *label_10;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_5;
    QLabel *label_9;
    QLabel *label_2;

    void setupUi(QWidget *test)
    {
        if (test->objectName().isEmpty())
            test->setObjectName("test");
        test->resize(316, 447);
        chartWidget = new QWidget(test);
        chartWidget->setObjectName("chartWidget");
        chartWidget->setGeometry(QRect(40, 210, 241, 211));
        chartWidget->setMaximumSize(QSize(241, 211));
        widget = new QWidget(test);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 10, 261, 151));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName("formLayout_5");
        label = new QLabel(widget);
        label->setObjectName("label");

        formLayout_5->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        lineEdit_7 = new QLineEdit(widget);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setReadOnly(true);

        formLayout_5->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEdit_7);


        gridLayout->addLayout(formLayout_5, 0, 0, 1, 2);

        label_15 = new QLabel(widget);
        label_15->setObjectName("label_15");

        gridLayout->addWidget(label_15, 2, 0, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 2, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        label_12 = new QLabel(widget);
        label_12->setObjectName("label_12");

        gridLayout_3->addWidget(label_12, 2, 0, 1, 1);

        lineEdit_8 = new QLineEdit(widget);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_8, 0, 1, 1, 1);

        label_13 = new QLabel(widget);
        label_13->setObjectName("label_13");

        gridLayout_3->addWidget(label_13, 1, 0, 1, 1);

        lineEdit_9 = new QLineEdit(widget);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_9, 2, 1, 1, 1);

        lineEdit_10 = new QLineEdit(widget);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setReadOnly(true);

        gridLayout_3->addWidget(lineEdit_10, 1, 1, 1, 1);

        label_14 = new QLabel(widget);
        label_14->setObjectName("label_14");

        gridLayout_3->addWidget(label_14, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 3, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label_11 = new QLabel(widget);
        label_11->setObjectName("label_11");

        gridLayout_2->addWidget(label_11, 2, 0, 1, 1);

        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_4, 0, 1, 1, 1);

        label_10 = new QLabel(widget);
        label_10->setObjectName("label_10");

        gridLayout_2->addWidget(label_10, 1, 0, 1, 1);

        lineEdit_6 = new QLineEdit(widget);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_6, 2, 1, 1, 1);

        lineEdit_5 = new QLineEdit(widget);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setReadOnly(true);

        gridLayout_2->addWidget(lineEdit_5, 1, 1, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");

        gridLayout_2->addWidget(label_9, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 3, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 2);


        retranslateUi(test);

        QMetaObject::connectSlotsByName(test);
    } // setupUi

    void retranslateUi(QWidget *test)
    {
        test->setWindowTitle(QCoreApplication::translate("test", "Form", nullptr));
        label->setText(QCoreApplication::translate("test", "Status po\305\202\304\205czenia:", nullptr));
        lineEdit_7->setText(QCoreApplication::translate("test", "offline", nullptr));
        label_15->setText(QCoreApplication::translate("test", "Akcelerometr:", nullptr));
        label_8->setText(QCoreApplication::translate("test", "\305\273yroskop:", nullptr));
        label_12->setText(QCoreApplication::translate("test", "Z:", nullptr));
        label_13->setText(QCoreApplication::translate("test", "Y:", nullptr));
        label_14->setText(QCoreApplication::translate("test", "X:", nullptr));
        label_11->setText(QCoreApplication::translate("test", "Z:", nullptr));
        label_10->setText(QCoreApplication::translate("test", "Y:", nullptr));
        label_9->setText(QCoreApplication::translate("test", "X:", nullptr));
        label_2->setText(QCoreApplication::translate("test", "Odczyty czujnik\303\263w:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test: public Ui_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
