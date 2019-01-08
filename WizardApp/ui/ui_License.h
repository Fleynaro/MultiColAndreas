/********************************************************************************
** Form generated from reading UI file 'License.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LICENSE_H
#define UI_LICENSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_licenseWidget
{
public:
    QVBoxLayout *licenseLayout;
    QLabel *licenseLabel;
    QSpacerItem *verticalSpacer;
    QTextEdit *licenseContainer;
    QSpacerItem *licenseSpacer;
    QRadioButton *licenseAcceptRadio;
    QRadioButton *licenseRejectRadio;

    void setupUi(QWidget *licenseWidget)
    {
        if (licenseWidget->objectName().isEmpty())
            licenseWidget->setObjectName(QStringLiteral("licenseWidget"));
        licenseWidget->resize(480, 419);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(licenseWidget->sizePolicy().hasHeightForWidth());
        licenseWidget->setSizePolicy(sizePolicy);
        licenseLayout = new QVBoxLayout(licenseWidget);
        licenseLayout->setSpacing(0);
        licenseLayout->setObjectName(QStringLiteral("licenseLayout"));
        licenseLayout->setContentsMargins(0, 0, 0, 0);
        licenseLabel = new QLabel(licenseWidget);
        licenseLabel->setObjectName(QStringLiteral("licenseLabel"));
        licenseLabel->setTextFormat(Qt::PlainText);

        licenseLayout->addWidget(licenseLabel);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        licenseLayout->addItem(verticalSpacer);

        licenseContainer = new QTextEdit(licenseWidget);
        licenseContainer->setObjectName(QStringLiteral("licenseContainer"));
        licenseContainer->setFocusPolicy(Qt::NoFocus);
        licenseContainer->setDocumentTitle(QStringLiteral(""));
        licenseContainer->setReadOnly(true);
        licenseContainer->setHtml(QLatin1String("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Oxygen-Sans'; font-size:10pt;\"><br /></p></body></html>"));

        licenseLayout->addWidget(licenseContainer);

        licenseSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        licenseLayout->addItem(licenseSpacer);

        licenseAcceptRadio = new QRadioButton(licenseWidget);
        licenseAcceptRadio->setObjectName(QStringLiteral("licenseAcceptRadio"));
        licenseAcceptRadio->setFocusPolicy(Qt::NoFocus);
        licenseAcceptRadio->setChecked(false);

        licenseLayout->addWidget(licenseAcceptRadio);

        licenseRejectRadio = new QRadioButton(licenseWidget);
        licenseRejectRadio->setObjectName(QStringLiteral("licenseRejectRadio"));
        licenseRejectRadio->setFocusPolicy(Qt::NoFocus);
        licenseRejectRadio->setChecked(true);

        licenseLayout->addWidget(licenseRejectRadio);


        retranslateUi(licenseWidget);

        QMetaObject::connectSlotsByName(licenseWidget);
    } // setupUi

    void retranslateUi(QWidget *licenseWidget)
    {
        licenseWidget->setWindowTitle(QApplication::translate("licenseWidget", "Form", Q_NULLPTR));
        licenseLabel->setText(QApplication::translate("licenseWidget", "Please read the following License Agreement.\n"
"You must accept the terms of this agreement before using this software.", Q_NULLPTR));
        licenseAcceptRadio->setText(QApplication::translate("licenseWidget", "I accept the agree&ment.", Q_NULLPTR));
        licenseRejectRadio->setText(QApplication::translate("licenseWidget", "I do not accept the agreement.", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class licenseWidget: public Ui_licenseWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LICENSE_H
