/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *centralLayout;
    QWidget *headerWidget;
    QHBoxLayout *headerLayout;
    QSpacerItem *headerSpacerL;
    QLabel *headerImage;
    QSpacerItem *headerSpacerR;
    QSpacerItem *mainSpacer;
    QWidget *contentWidget;
    QVBoxLayout *contentLayout;
    QWidget *buttonsWidget;
    QHBoxLayout *buttonsLayout;
    QSpacerItem *buttonsSpacerL;
    QPushButton *buttonBack;
    QSpacerItem *buttonsSpacer1;
    QPushButton *buttonNext;
    QSpacerItem *buttonsSpacer2;
    QPushButton *buttonCancel;
    QSpacerItem *buttonsSpacerR;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralLayout = new QVBoxLayout(centralWidget);
        centralLayout->setSpacing(0);
        centralLayout->setObjectName(QStringLiteral("centralLayout"));
        centralLayout->setContentsMargins(0, 0, 0, 0);
        headerWidget = new QWidget(centralWidget);
        headerWidget->setObjectName(QStringLiteral("headerWidget"));
        headerLayout = new QHBoxLayout(headerWidget);
        headerLayout->setSpacing(0);
        headerLayout->setObjectName(QStringLiteral("headerLayout"));
        headerLayout->setContentsMargins(0, 0, 0, 0);
        headerSpacerL = new QSpacerItem(92, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        headerLayout->addItem(headerSpacerL);

        headerImage = new QLabel(headerWidget);
        headerImage->setObjectName(QStringLiteral("headerImage"));
        headerImage->setMinimumSize(QSize(610, 80));
        headerImage->setAlignment(Qt::AlignCenter);

        headerLayout->addWidget(headerImage);

        headerSpacerR = new QSpacerItem(92, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        headerLayout->addItem(headerSpacerR);


        centralLayout->addWidget(headerWidget);

        mainSpacer = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Fixed);

        centralLayout->addItem(mainSpacer);

        contentWidget = new QWidget(centralWidget);
        contentWidget->setObjectName(QStringLiteral("contentWidget"));
        contentLayout = new QVBoxLayout(contentWidget);
        contentLayout->setObjectName(QStringLiteral("contentLayout"));

        centralLayout->addWidget(contentWidget);

        buttonsWidget = new QWidget(centralWidget);
        buttonsWidget->setObjectName(QStringLiteral("buttonsWidget"));
        buttonsLayout = new QHBoxLayout(buttonsWidget);
        buttonsLayout->setObjectName(QStringLiteral("buttonsLayout"));
        buttonsLayout->setContentsMargins(-1, 10, -1, -1);
        buttonsSpacerL = new QSpacerItem(40, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonsLayout->addItem(buttonsSpacerL);

        buttonBack = new QPushButton(buttonsWidget);
        buttonBack->setObjectName(QStringLiteral("buttonBack"));
        buttonBack->setFocusPolicy(Qt::NoFocus);

        buttonsLayout->addWidget(buttonBack);

        buttonsSpacer1 = new QSpacerItem(5, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        buttonsLayout->addItem(buttonsSpacer1);

        buttonNext = new QPushButton(buttonsWidget);
        buttonNext->setObjectName(QStringLiteral("buttonNext"));
        buttonNext->setFocusPolicy(Qt::NoFocus);

        buttonsLayout->addWidget(buttonNext);

        buttonsSpacer2 = new QSpacerItem(5, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        buttonsLayout->addItem(buttonsSpacer2);

        buttonCancel = new QPushButton(buttonsWidget);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setFocusPolicy(Qt::NoFocus);

        buttonsLayout->addWidget(buttonCancel);

        buttonsSpacerR = new QSpacerItem(10, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        buttonsLayout->addItem(buttonsSpacerR);


        centralLayout->addWidget(buttonsWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 30));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ColAndreas", Q_NULLPTR));
        headerImage->setText(QString());
        buttonBack->setText(QApplication::translate("MainWindow", "Back", Q_NULLPTR));
        buttonNext->setText(QApplication::translate("MainWindow", "Next", Q_NULLPTR));
        buttonCancel->setText(QApplication::translate("MainWindow", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
