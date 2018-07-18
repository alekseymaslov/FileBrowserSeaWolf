/********************************************************************************
** Form generated from reading UI file 'ui_mainform.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_6;
    QWidget *widget_4;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox_2;
    QComboBox *comboBox;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *treeWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QSlider *horizontalSlider;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(873, 641);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(MainForm->sizePolicy().hasHeightForWidth());
        MainForm->setSizePolicy(sizePolicy);
        MainForm->setMinimumSize(QSize(20, 20));
        MainForm->setCursor(QCursor(Qt::ArrowCursor));
        MainForm->setContextMenuPolicy(Qt::ActionsContextMenu);
        MainForm->setAcceptDrops(false);
        MainForm->setAutoFillBackground(false);
        horizontalLayout_2 = new QHBoxLayout(MainForm);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget_2 = new QWidget(MainForm);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(pushButton_2);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setBaseSize(QSize(0, 0));
        pushButton->setIconSize(QSize(16, 16));
        pushButton->setAutoRepeatInterval(100);

        horizontalLayout_3->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButton_6 = new QPushButton(widget_2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMaximumSize(QSize(98, 27));

        horizontalLayout_3->addWidget(pushButton_6);


        verticalLayout->addLayout(horizontalLayout_3);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        comboBox_2 = new QComboBox(widget_4);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(90);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy2);
        comboBox_2->setMinimumSize(QSize(180, 0));
        comboBox_2->setEditable(true);

        gridLayout_2->addWidget(comboBox_2, 0, 3, 1, 1);

        comboBox = new QComboBox(widget_4);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(199);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy3);
        comboBox->setMinimumSize(QSize(300, 27));
        comboBox->setMaximumSize(QSize(16777215, 16777215));
        comboBox->setSizeIncrement(QSize(1000, 27));
        comboBox->setBaseSize(QSize(1000, 27));
        comboBox->setLayoutDirection(Qt::LeftToRight);
        comboBox->setEditable(true);
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
        comboBox->setMinimumContentsLength(0);
        comboBox->setDuplicatesEnabled(true);
        comboBox->setFrame(true);

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);

        pushButton_4 = new QPushButton(widget_4);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 0, 0, 1, 1);

        pushButton_3 = new QPushButton(widget_4);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton_5 = new QPushButton(widget_4);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        gridLayout_2->addWidget(pushButton_5, 0, 4, 1, 1);


        verticalLayout->addWidget(widget_4);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        treeWidget = new QTreeWidget(widget_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("System"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        horizontalLayout->addWidget(treeWidget, 0, Qt::AlignLeft);

        scrollArea = new QScrollArea(widget_3);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 555, 464));
        scrollAreaWidgetContents->setLayoutDirection(Qt::LeftToRight);
        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);


        verticalLayout->addWidget(widget_3);

        horizontalSlider = new QSlider(widget_2);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider, 0, Qt::AlignRight);

        widget_3->raise();
        widget_4->raise();
        horizontalSlider->raise();

        horizontalLayout_2->addWidget(widget_2);


        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        pushButton_2->setText(QApplication::translate("MainForm", "<", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainForm", ">", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("MainForm", "Virtual Folder", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MainForm", "Up", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainForm", "Refresh", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MainForm", "Search", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainForm);
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
