#ifndef ADDMENU_H
#define ADDMENU_H
#pragma once
#include <QtCore>
#include <QtWidgets>
#include "maindial.h"
#include "incorrectnm.h"
#include "phonebook.h"

class AddWindow: public QWidget
{
    Q_OBJECT
private:
    int countPhones;
    Phonebook* phnbk;
    QWidget* prnt;
    QVBoxLayout* mainAdd;
    QLabel* lastNameLbl;
    QLineEdit* lastNameTxt;
    QLabel* firstNameLbl;
    QLineEdit* firstNameTxt;
    QLabel* secondNameLbl;
    QLabel* emailLbl;
    QLineEdit* emailTxt;
    QLineEdit* secondNameTxt;
    QLabel* birthdayLbl;
    QDateEdit* birthdayTxt;
    QVBoxLayout* phonesLayout;
    QLabel* phonesLbl;
    QLineEdit** phoneTxt;
    QHBoxLayout* buttonsLayout;
    QPushButton* cancelButton;
    QPushButton* OKButton;
    QPushButton* addField;
    bool editmode;
    bool editmodeokcall;
public:
    AddWindow(QWidget* parrent, Phonebook* phonebook);
    void closeEvent(QCloseEvent *event);
    void editPerson(Person &p);
signals:
    void sayShowBook();
public slots:
    void onOKClick();
    void onAddPhoneClick();
    void onCancelClick();

};

#endif // ADDMENU_H
