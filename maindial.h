#ifndef MAINDIAL_H
#define MAINDIAL_H

#include "addmenu.h"
#include "sortdial.h"
#include "phonebook.h"
#include <QWidget>
#include <QtCore>
#include "findwindow.h"
#pragma once

const int keysCount = 7;
const QString keys[] =
{
  "Add", "Delete", "Edit", "Find", "Sort", "Save", "Load"
};

class MainDial : public QWidget
{
    Q_OBJECT
private:
    int countPersons;

    QMap<QString, QPushButton*> buttons;
    QHBoxLayout* generalLayout;
    QVBoxLayout* menuLayout;
    QListWidget* list;
    void onAddClick();
    void onDeleteClick();
    void onEditClick();
    void onFindClick();
    void onSortClick();
    void onSaveClick();
    void onLoadClick();
protected:
    QString formateString(Person &person);
    Person& formatePerson(QString string);
public:

    Phonebook* phonebook;
    MainDial();

signals:

public slots:
    void onAbstractClick();
    void showBook();
    void sortBook(int sorttype);
};
#endif // MAINDIAL_H
