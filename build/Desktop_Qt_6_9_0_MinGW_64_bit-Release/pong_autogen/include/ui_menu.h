/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *labelMenu;
    QSpacerItem *verticalSpacer;
    QLabel *labelPrompt;
    QPushButton *buttonGoBack;
    QPushButton *buttonNewGame;
    QPushButton *buttonExit;
    QPushButton *buttonTest;

    void setupUi(QWidget *menu)
    {
        if (menu->objectName().isEmpty())
            menu->setObjectName("menu");
        menu->resize(327, 285);
        widget = new QWidget(menu);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(90, 20, 151, 221));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelMenu = new QLabel(widget);
        labelMenu->setObjectName("labelMenu");
        labelMenu->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(labelMenu);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        labelPrompt = new QLabel(widget);
        labelPrompt->setObjectName("labelPrompt");
        labelPrompt->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(labelPrompt);

        buttonGoBack = new QPushButton(widget);
        buttonGoBack->setObjectName("buttonGoBack");

        verticalLayout->addWidget(buttonGoBack);

        buttonNewGame = new QPushButton(widget);
        buttonNewGame->setObjectName("buttonNewGame");

        verticalLayout->addWidget(buttonNewGame);

        buttonExit = new QPushButton(widget);
        buttonExit->setObjectName("buttonExit");

        verticalLayout->addWidget(buttonExit);

        buttonTest = new QPushButton(widget);
        buttonTest->setObjectName("buttonTest");

        verticalLayout->addWidget(buttonTest);


        retranslateUi(menu);

        QMetaObject::connectSlotsByName(menu);
    } // setupUi

    void retranslateUi(QWidget *menu)
    {
        menu->setWindowTitle(QCoreApplication::translate("menu", "Form", nullptr));
        labelMenu->setText(QCoreApplication::translate("menu", "Menu", nullptr));
        labelPrompt->setText(QCoreApplication::translate("menu", "Wybierz opcj\304\231:", nullptr));
        buttonGoBack->setText(QCoreApplication::translate("menu", "Wzn\303\263w gr\304\231", nullptr));
        buttonNewGame->setText(QCoreApplication::translate("menu", "Nowa gra", nullptr));
        buttonExit->setText(QCoreApplication::translate("menu", "Wyjd\305\272 z gry", nullptr));
        buttonTest->setText(QCoreApplication::translate("menu", "Przetestuj po\305\202\304\205czenie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menu: public Ui_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
