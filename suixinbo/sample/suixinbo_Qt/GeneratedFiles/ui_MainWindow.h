/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Mon Jan 16 17:30:12 2017
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tiLiveList;
    QPushButton *btnRefreshLiveList;
    QPushButton *btnLastPage;
    QPushButton *btnNextPage;
    QLabel *lbPageNum;
    QWidget *gridLayoutWidget;
    QGridLayout *layoutShowRoomList;
    QWidget *tiBeginLive;
    QLabel *lbBLTitle;
    QLineEdit *edBLTitle;
    QPushButton *btnBeginLive;
    QGroupBox *groupBox;
    QPushButton *btnLogin;
    QLineEdit *edPassword;
    QLabel *lbPassword;
    QLineEdit *edUserName;
    QLabel *lbUserName;
    QPushButton *btnRegister;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 720);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(20, 60, 1241, 611));
        QFont font;
        font.setPointSize(10);
        tabWidget->setFont(font);
        tiLiveList = new QWidget();
        tiLiveList->setObjectName(QStringLiteral("tiLiveList"));
        btnRefreshLiveList = new QPushButton(tiLiveList);
        btnRefreshLiveList->setObjectName(QStringLiteral("btnRefreshLiveList"));
        btnRefreshLiveList->setGeometry(QRect(1140, 10, 91, 41));
        btnLastPage = new QPushButton(tiLiveList);
        btnLastPage->setObjectName(QStringLiteral("btnLastPage"));
        btnLastPage->setEnabled(false);
        btnLastPage->setGeometry(QRect(1140, 60, 91, 41));
        btnNextPage = new QPushButton(tiLiveList);
        btnNextPage->setObjectName(QStringLiteral("btnNextPage"));
        btnNextPage->setEnabled(false);
        btnNextPage->setGeometry(QRect(1140, 110, 91, 41));
        lbPageNum = new QLabel(tiLiveList);
        lbPageNum->setObjectName(QStringLiteral("lbPageNum"));
        lbPageNum->setGeometry(QRect(1140, 170, 91, 31));
        lbPageNum->setAlignment(Qt::AlignCenter);
        gridLayoutWidget = new QWidget(tiLiveList);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 1121, 561));
        layoutShowRoomList = new QGridLayout(gridLayoutWidget);
        layoutShowRoomList->setObjectName(QStringLiteral("layoutShowRoomList"));
        layoutShowRoomList->setContentsMargins(0, 0, 0, 0);
        tabWidget->addTab(tiLiveList, QString());
        tiBeginLive = new QWidget();
        tiBeginLive->setObjectName(QStringLiteral("tiBeginLive"));
        lbBLTitle = new QLabel(tiBeginLive);
        lbBLTitle->setObjectName(QStringLiteral("lbBLTitle"));
        lbBLTitle->setGeometry(QRect(270, 140, 51, 31));
        lbBLTitle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edBLTitle = new QLineEdit(tiBeginLive);
        edBLTitle->setObjectName(QStringLiteral("edBLTitle"));
        edBLTitle->setGeometry(QRect(350, 140, 621, 31));
        btnBeginLive = new QPushButton(tiBeginLive);
        btnBeginLive->setObjectName(QStringLiteral("btnBeginLive"));
        btnBeginLive->setGeometry(QRect(270, 200, 711, 201));
        tabWidget->addTab(tiBeginLive, QString());
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(600, 10, 661, 51));
        btnLogin = new QPushButton(groupBox);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));
        btnLogin->setGeometry(QRect(490, 10, 75, 31));
        edPassword = new QLineEdit(groupBox);
        edPassword->setObjectName(QStringLiteral("edPassword"));
        edPassword->setGeometry(QRect(320, 10, 141, 31));
        edPassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        lbPassword = new QLabel(groupBox);
        lbPassword->setObjectName(QStringLiteral("lbPassword"));
        lbPassword->setGeometry(QRect(260, 10, 54, 31));
        lbPassword->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edUserName = new QLineEdit(groupBox);
        edUserName->setObjectName(QStringLiteral("edUserName"));
        edUserName->setGeometry(QRect(90, 10, 141, 31));
        lbUserName = new QLabel(groupBox);
        lbUserName->setObjectName(QStringLiteral("lbUserName"));
        lbUserName->setGeometry(QRect(20, 10, 54, 31));
        lbUserName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnRegister = new QPushButton(groupBox);
        btnRegister->setObjectName(QStringLiteral("btnRegister"));
        btnRegister->setGeometry(QRect(580, 10, 75, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(edUserName, edPassword);
        QWidget::setTabOrder(edPassword, btnLogin);
        QWidget::setTabOrder(btnLogin, btnRegister);
        QWidget::setTabOrder(btnRegister, tabWidget);
        QWidget::setTabOrder(tabWidget, btnRefreshLiveList);
        QWidget::setTabOrder(btnRefreshLiveList, btnLastPage);
        QWidget::setTabOrder(btnLastPage, btnNextPage);
        QWidget::setTabOrder(btnNextPage, edBLTitle);
        QWidget::setTabOrder(edBLTitle, btnBeginLive);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\351\232\217\345\277\203\346\222\255", 0));
        btnRefreshLiveList->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260\347\233\264\346\222\255\345\210\227\350\241\250", 0));
        btnLastPage->setText(QApplication::translate("MainWindow", "\344\270\212\344\270\200\351\241\265", 0));
        btnNextPage->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\351\241\265", 0));
        lbPageNum->setText(QApplication::translate("MainWindow", "0/0", 0));
        tabWidget->setTabText(tabWidget->indexOf(tiLiveList), QApplication::translate("MainWindow", "\347\233\264\346\222\255\345\210\227\350\241\250", 0));
        lbBLTitle->setText(QApplication::translate("MainWindow", "\346\240\207\351\242\230:", 0));
        edBLTitle->setText(QApplication::translate("MainWindow", "PC\351\232\217\345\277\203\346\222\255", 0));
        btnBeginLive->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\347\233\264\346\222\255", 0));
        tabWidget->setTabText(tabWidget->indexOf(tiBeginLive), QApplication::translate("MainWindow", "\346\210\221\350\246\201\347\233\264\346\222\255", 0));
        groupBox->setTitle(QString());
        btnLogin->setText(QApplication::translate("MainWindow", "\347\231\273\345\275\225", 0));
        edPassword->setText(QString());
        lbPassword->setText(QApplication::translate("MainWindow", "\345\257\206\347\240\201:", 0));
        edUserName->setText(QString());
        lbUserName->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215:", 0));
        btnRegister->setText(QApplication::translate("MainWindow", "\346\263\250\345\206\214", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
