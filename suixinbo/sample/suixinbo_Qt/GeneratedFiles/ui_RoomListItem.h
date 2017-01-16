/********************************************************************************
** Form generated from reading UI file 'RoomListItem.ui'
**
** Created: Mon Jan 16 17:30:12 2017
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOMLISTITEM_H
#define UI_ROOMLISTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoomListItem
{
public:
    QLabel *lbType;
    QLabel *lbName;
    QLabel *lbTitle;
    QLabel *lbBorder;
    QPushButton *btnPic;
    QLabel *lbRoomMemNum;
    QLabel *lbPraiseNum;

    void setupUi(QWidget *RoomListItem)
    {
        if (RoomListItem->objectName().isEmpty())
            RoomListItem->setObjectName(QStringLiteral("RoomListItem"));
        RoomListItem->resize(215, 263);
        lbType = new QLabel(RoomListItem);
        lbType->setObjectName(QStringLiteral("lbType"));
        lbType->setGeometry(QRect(120, 230, 71, 21));
        lbName = new QLabel(RoomListItem);
        lbName->setObjectName(QStringLiteral("lbName"));
        lbName->setGeometry(QRect(10, 230, 91, 21));
        lbTitle = new QLabel(RoomListItem);
        lbTitle->setObjectName(QStringLiteral("lbTitle"));
        lbTitle->setGeometry(QRect(20, 10, 181, 20));
        lbBorder = new QLabel(RoomListItem);
        lbBorder->setObjectName(QStringLiteral("lbBorder"));
        lbBorder->setGeometry(QRect(0, 0, 215, 261));
        lbBorder->setStyleSheet(QStringLiteral("border: 1px solid red"));
        btnPic = new QPushButton(RoomListItem);
        btnPic->setObjectName(QStringLiteral("btnPic"));
        btnPic->setGeometry(QRect(10, 40, 191, 151));
        lbRoomMemNum = new QLabel(RoomListItem);
        lbRoomMemNum->setObjectName(QStringLiteral("lbRoomMemNum"));
        lbRoomMemNum->setGeometry(QRect(10, 200, 91, 16));
        lbPraiseNum = new QLabel(RoomListItem);
        lbPraiseNum->setObjectName(QStringLiteral("lbPraiseNum"));
        lbPraiseNum->setGeometry(QRect(120, 200, 81, 16));
        lbBorder->raise();
        lbTitle->raise();
        lbType->raise();
        lbName->raise();
        btnPic->raise();
        lbRoomMemNum->raise();
        lbPraiseNum->raise();

        retranslateUi(RoomListItem);

        QMetaObject::connectSlotsByName(RoomListItem);
    } // setupUi

    void retranslateUi(QWidget *RoomListItem)
    {
        RoomListItem->setWindowTitle(QApplication::translate("RoomListItem", "Form", 0));
        lbType->setText(QApplication::translate("RoomListItem", "\347\261\273\345\236\213", 0));
        lbName->setText(QApplication::translate("RoomListItem", "\344\270\273\346\222\255\345\220\215", 0));
        lbTitle->setText(QApplication::translate("RoomListItem", "\346\240\207\351\242\230", 0));
        lbBorder->setText(QString());
        btnPic->setText(QString());
        lbRoomMemNum->setText(QApplication::translate("RoomListItem", "\344\272\272\346\225\260:", 0));
        lbPraiseNum->setText(QApplication::translate("RoomListItem", "\347\202\271\350\265\236:", 0));
    } // retranslateUi

};

namespace Ui {
    class RoomListItem: public Ui_RoomListItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOMLISTITEM_H
