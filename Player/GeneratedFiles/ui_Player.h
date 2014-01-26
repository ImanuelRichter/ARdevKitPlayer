/********************************************************************************
** Form generated from reading UI file 'Player.ui'
**
** Created: Fri 24. Jan 01:06:38 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYER_H
#define UI_PLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TemplateWindowClass
{
public:
    QAction *actionSome_menu_item;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuSome_menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TemplateWindowClass)
    {
        if (TemplateWindowClass->objectName().isEmpty())
            TemplateWindowClass->setObjectName(QString::fromUtf8("TemplateWindowClass"));
        TemplateWindowClass->resize(1024, 821);
        actionSome_menu_item = new QAction(TemplateWindowClass);
        actionSome_menu_item->setObjectName(QString::fromUtf8("actionSome_menu_item"));
        centralWidget = new QWidget(TemplateWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setFrameShape(QFrame::NoFrame);
        graphicsView->setFrameShadow(QFrame::Plain);
        graphicsView->setLineWidth(0);

        verticalLayout->addWidget(graphicsView);

        TemplateWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TemplateWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        menuSome_menu = new QMenu(menuBar);
        menuSome_menu->setObjectName(QString::fromUtf8("menuSome_menu"));
        TemplateWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TemplateWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TemplateWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TemplateWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TemplateWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuSome_menu->menuAction());
        menuSome_menu->addAction(actionSome_menu_item);

        retranslateUi(TemplateWindowClass);

        QMetaObject::connectSlotsByName(TemplateWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *TemplateWindowClass)
    {
        TemplateWindowClass->setWindowTitle(QApplication::translate("TemplateWindowClass", "ARdevKit - Player", 0, QApplication::UnicodeUTF8));
        actionSome_menu_item->setText(QApplication::translate("TemplateWindowClass", "Some menu item", 0, QApplication::UnicodeUTF8));
        menuSome_menu->setTitle(QApplication::translate("TemplateWindowClass", "Some menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TemplateWindowClass: public Ui_TemplateWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYER_H
