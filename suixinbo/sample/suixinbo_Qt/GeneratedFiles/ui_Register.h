/********************************************************************************
** Form generated from reading UI file 'Register.ui'
**
** Created: Mon Jan 16 17:30:12 2017
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QLabel *lbUserName;
    QLineEdit *leUserName;
    QLabel *lbPassword;
    QLineEdit *lePassword;
    QPushButton *btnRegister;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QStringLiteral("Register"));
        Register->resize(362, 223);
        lbUserName = new QLabel(Register);
        lbUserName->setObjectName(QStringLiteral("lbUserName"));
        lbUserName->setGeometry(QRect(40, 40, 54, 12));
        leUserName = new QLineEdit(Register);
        leUserName->setObjectName(QStringLiteral("leUserName"));
        leUserName->setGeometry(QRect(110, 40, 191, 20));
        lbPassword = new QLabel(Register);
        lbPassword->setObjectName(QStringLiteral("lbPassword"));
        lbPassword->setGeometry(QRect(40, 90, 54, 12));
        lePassword = new QLineEdit(Register);
        lePassword->setObjectName(QStringLiteral("lePassword"));
        lePassword->setGeometry(QRect(110, 90, 191, 20));
        btnRegister = new QPushButton(Register);
        btnRegister->setObjectName(QStringLiteral("btnRegister"));
        btnRegister->setGeometry(QRect(40, 150, 261, 41));

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QApplication::translate("Register", "\346\263\250\345\206\214", 0));
        lbUserName->setText(QApplication::translate("Register", "UserName:", 0));
        lbPassword->setText(QApplication::translate("Register", "Password:", 0));
        btnRegister->setText(QApplication::translate("Register", "\346\263\250\345\206\214", 0));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
