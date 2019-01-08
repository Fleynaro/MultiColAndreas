/********************************************************************************
** Form generated from reading UI file 'Settings.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settingsWidget
{
public:
    QVBoxLayout *settingsLayout;
    QLabel *gameLabel;
    QWidget *gameWidget;
    QHBoxLayout *gameLayout;
    QLineEdit *gamePathDisplay;
    QPushButton *gameBrowseButton;
    QSpacerItem *settingsSpacer1;
    QLabel *outputLabel;
    QWidget *outputWidget;
    QHBoxLayout *outputLayout;
    QLineEdit *outputPathDisplay;
    QPushButton *outputBrowseButton;
    QSpacerItem *settingsSpacer2;
    QCheckBox *sampObjectsBox;
    QCheckBox *customObjectsBox;
    QSpacerItem *settingsSpacer3;

    void setupUi(QWidget *settingsWidget)
    {
        if (settingsWidget->objectName().isEmpty())
            settingsWidget->setObjectName(QStringLiteral("settingsWidget"));
        settingsWidget->resize(400, 300);
        settingsLayout = new QVBoxLayout(settingsWidget);
        settingsLayout->setObjectName(QStringLiteral("settingsLayout"));
        gameLabel = new QLabel(settingsWidget);
        gameLabel->setObjectName(QStringLiteral("gameLabel"));

        settingsLayout->addWidget(gameLabel);

        gameWidget = new QWidget(settingsWidget);
        gameWidget->setObjectName(QStringLiteral("gameWidget"));
        gameLayout = new QHBoxLayout(gameWidget);
        gameLayout->setObjectName(QStringLiteral("gameLayout"));
        gameLayout->setContentsMargins(10, -1, -1, -1);
        gamePathDisplay = new QLineEdit(gameWidget);
        gamePathDisplay->setObjectName(QStringLiteral("gamePathDisplay"));
        gamePathDisplay->setFocusPolicy(Qt::NoFocus);
        gamePathDisplay->setReadOnly(true);

        gameLayout->addWidget(gamePathDisplay);

        gameBrowseButton = new QPushButton(gameWidget);
        gameBrowseButton->setObjectName(QStringLiteral("gameBrowseButton"));
        gameBrowseButton->setFocusPolicy(Qt::NoFocus);

        gameLayout->addWidget(gameBrowseButton);


        settingsLayout->addWidget(gameWidget);

        settingsSpacer1 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        settingsLayout->addItem(settingsSpacer1);

        outputLabel = new QLabel(settingsWidget);
        outputLabel->setObjectName(QStringLiteral("outputLabel"));

        settingsLayout->addWidget(outputLabel);

        outputWidget = new QWidget(settingsWidget);
        outputWidget->setObjectName(QStringLiteral("outputWidget"));
        outputLayout = new QHBoxLayout(outputWidget);
        outputLayout->setObjectName(QStringLiteral("outputLayout"));
        outputLayout->setContentsMargins(10, -1, -1, -1);
        outputPathDisplay = new QLineEdit(outputWidget);
        outputPathDisplay->setObjectName(QStringLiteral("outputPathDisplay"));
        outputPathDisplay->setFocusPolicy(Qt::NoFocus);
        outputPathDisplay->setReadOnly(true);

        outputLayout->addWidget(outputPathDisplay);

        outputBrowseButton = new QPushButton(outputWidget);
        outputBrowseButton->setObjectName(QStringLiteral("outputBrowseButton"));
        outputBrowseButton->setFocusPolicy(Qt::NoFocus);

        outputLayout->addWidget(outputBrowseButton);


        settingsLayout->addWidget(outputWidget);

        settingsSpacer2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        settingsLayout->addItem(settingsSpacer2);

        sampObjectsBox = new QCheckBox(settingsWidget);
        sampObjectsBox->setObjectName(QStringLiteral("sampObjectsBox"));
        sampObjectsBox->setFocusPolicy(Qt::NoFocus);
        sampObjectsBox->setChecked(true);

        settingsLayout->addWidget(sampObjectsBox);

        customObjectsBox = new QCheckBox(settingsWidget);
        customObjectsBox->setObjectName(QStringLiteral("customObjectsBox"));
        customObjectsBox->setFocusPolicy(Qt::NoFocus);

        settingsLayout->addWidget(customObjectsBox);

        settingsSpacer3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        settingsLayout->addItem(settingsSpacer3);


        retranslateUi(settingsWidget);

        QMetaObject::connectSlotsByName(settingsWidget);
    } // setupUi

    void retranslateUi(QWidget *settingsWidget)
    {
        settingsWidget->setWindowTitle(QApplication::translate("settingsWidget", "Form", Q_NULLPTR));
        gameLabel->setText(QApplication::translate("settingsWidget", "Select your GTA:SA install directory:", Q_NULLPTR));
        gameBrowseButton->setText(QApplication::translate("settingsWidget", "Browse", Q_NULLPTR));
        outputLabel->setText(QApplication::translate("settingsWidget", "Choose where to save the ColAndreas file:", Q_NULLPTR));
        outputBrowseButton->setText(QApplication::translate("settingsWidget", "Browse", Q_NULLPTR));
        sampObjectsBox->setText(QApplication::translate("settingsWidget", "Include SA-MP objects.", Q_NULLPTR));
        customObjectsBox->setText(QApplication::translate("settingsWidget", "Include objects from CUSTOM.img", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class settingsWidget: public Ui_settingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
