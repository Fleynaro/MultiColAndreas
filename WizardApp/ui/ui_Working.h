/********************************************************************************
** Form generated from reading UI file 'Working.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKING_H
#define UI_WORKING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_workWidget
{
public:
    QVBoxLayout *workLayout;
    QPlainTextEdit *workMessages;
    QProgressBar *workProgress;

    void setupUi(QWidget *workWidget)
    {
        if (workWidget->objectName().isEmpty())
            workWidget->setObjectName(QStringLiteral("workWidget"));
        workWidget->resize(400, 300);
        workLayout = new QVBoxLayout(workWidget);
        workLayout->setObjectName(QStringLiteral("workLayout"));
        workMessages = new QPlainTextEdit(workWidget);
        workMessages->setObjectName(QStringLiteral("workMessages"));
        workMessages->setFocusPolicy(Qt::NoFocus);
        workMessages->setDocumentTitle(QStringLiteral("Progress"));
        workMessages->setUndoRedoEnabled(false);
        workMessages->setReadOnly(true);
        workMessages->setPlainText(QStringLiteral(""));

        workLayout->addWidget(workMessages);

        workProgress = new QProgressBar(workWidget);
        workProgress->setObjectName(QStringLiteral("workProgress"));
        workProgress->setMaximum(0);
        workProgress->setValue(0);
        workProgress->setTextVisible(true);
        workProgress->setInvertedAppearance(false);

        workLayout->addWidget(workProgress);


        retranslateUi(workWidget);

        QMetaObject::connectSlotsByName(workWidget);
    } // setupUi

    void retranslateUi(QWidget *workWidget)
    {
        workWidget->setWindowTitle(QApplication::translate("workWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class workWidget: public Ui_workWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKING_H
