/********************************************************************************
** Form generated from reading UI file 'ssrpluginsettingui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SSRPLUGINSETTINGUI_H
#define SSRPLUGINSETTINGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SSRPluginSettingUI
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *HLayout_ScreenBlock;
    QLabel *label_ScreenBlock;
    QComboBox *comboBox_ScreenBlock;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *HLayout_RecordingSource;
    QLabel *label_Source;
    QComboBox *comboBox_Source;
    QHBoxLayout *HLayout_NameSourceFile;
    QLabel *label_SourceFile;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QHBoxLayout *HLayout_CamID;
    QLabel *label_CamID;
    QComboBox *comboBox_CamID;

    void setupUi(QDialog *SSRPluginSettingUI)
    {
        if (SSRPluginSettingUI->objectName().isEmpty())
            SSRPluginSettingUI->setObjectName(QString::fromUtf8("SSRPluginSettingUI"));
        SSRPluginSettingUI->resize(822, 459);
        gridLayout = new QGridLayout(SSRPluginSettingUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        HLayout_ScreenBlock = new QHBoxLayout();
        HLayout_ScreenBlock->setObjectName(QString::fromUtf8("HLayout_ScreenBlock"));
        label_ScreenBlock = new QLabel(SSRPluginSettingUI);
        label_ScreenBlock->setObjectName(QString::fromUtf8("label_ScreenBlock"));

        HLayout_ScreenBlock->addWidget(label_ScreenBlock);

        comboBox_ScreenBlock = new QComboBox(SSRPluginSettingUI);
        comboBox_ScreenBlock->setObjectName(QString::fromUtf8("comboBox_ScreenBlock"));
        comboBox_ScreenBlock->setEnabled(true);
        comboBox_ScreenBlock->setEditable(false);

        HLayout_ScreenBlock->addWidget(comboBox_ScreenBlock);


        gridLayout->addLayout(HLayout_ScreenBlock, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SSRPluginSettingUI);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        gridLayout->addWidget(buttonBox, 4, 0, 1, 2);

        HLayout_RecordingSource = new QHBoxLayout();
        HLayout_RecordingSource->setObjectName(QString::fromUtf8("HLayout_RecordingSource"));
        label_Source = new QLabel(SSRPluginSettingUI);
        label_Source->setObjectName(QString::fromUtf8("label_Source"));

        HLayout_RecordingSource->addWidget(label_Source);

        comboBox_Source = new QComboBox(SSRPluginSettingUI);
        comboBox_Source->setObjectName(QString::fromUtf8("comboBox_Source"));

        HLayout_RecordingSource->addWidget(comboBox_Source);


        gridLayout->addLayout(HLayout_RecordingSource, 0, 0, 1, 1);

        HLayout_NameSourceFile = new QHBoxLayout();
        HLayout_NameSourceFile->setObjectName(QString::fromUtf8("HLayout_NameSourceFile"));
        label_SourceFile = new QLabel(SSRPluginSettingUI);
        label_SourceFile->setObjectName(QString::fromUtf8("label_SourceFile"));

        HLayout_NameSourceFile->addWidget(label_SourceFile);

        lineEdit = new QLineEdit(SSRPluginSettingUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        HLayout_NameSourceFile->addWidget(lineEdit);

        pushButton = new QPushButton(SSRPluginSettingUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        HLayout_NameSourceFile->addWidget(pushButton);


        gridLayout->addLayout(HLayout_NameSourceFile, 3, 0, 1, 1);

        HLayout_CamID = new QHBoxLayout();
        HLayout_CamID->setObjectName(QString::fromUtf8("HLayout_CamID"));
        label_CamID = new QLabel(SSRPluginSettingUI);
        label_CamID->setObjectName(QString::fromUtf8("label_CamID"));

        HLayout_CamID->addWidget(label_CamID);

        comboBox_CamID = new QComboBox(SSRPluginSettingUI);
        comboBox_CamID->setObjectName(QString::fromUtf8("comboBox_CamID"));
        comboBox_CamID->setEditable(true);

        HLayout_CamID->addWidget(comboBox_CamID);


        gridLayout->addLayout(HLayout_CamID, 1, 0, 1, 1);


        retranslateUi(SSRPluginSettingUI);
        QObject::connect(buttonBox, SIGNAL(accepted()), SSRPluginSettingUI, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SSRPluginSettingUI, SLOT(reject()));
        QObject::connect(comboBox_ScreenBlock, SIGNAL(currentTextChanged(QString)), SSRPluginSettingUI, SLOT(update()));

        comboBox_CamID->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(SSRPluginSettingUI);
    } // setupUi

    void retranslateUi(QDialog *SSRPluginSettingUI)
    {
        SSRPluginSettingUI->setWindowTitle(QCoreApplication::translate("SSRPluginSettingUI", "Dialog", nullptr));
        label_ScreenBlock->setText(QCoreApplication::translate("SSRPluginSettingUI", "\345\261\217\345\271\225\345\214\272\345\237\237", nullptr));
        label_Source->setText(QCoreApplication::translate("SSRPluginSettingUI", "\345\275\225\345\210\266\346\235\245\346\272\220", nullptr));
        label_SourceFile->setText(QCoreApplication::translate("SSRPluginSettingUI", "\345\220\215\347\247\260\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        pushButton->setText(QCoreApplication::translate("SSRPluginSettingUI", "\346\265\217\350\247\210...", nullptr));
        label_CamID->setText(QCoreApplication::translate("SSRPluginSettingUI", "\347\233\270\346\234\272\347\274\226\345\217\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SSRPluginSettingUI: public Ui_SSRPluginSettingUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SSRPLUGINSETTINGUI_H
