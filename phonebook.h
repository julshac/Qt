#ifndef PHONEBOOK_H
#define PHONEBOOK_H
#pragma once
#include <QString>
#include <QDate>
#include <QList>

struct Person
{
    QString lastName;
    QString firstName;
    QString secondName;
    QDate birthday;
    QString email;
    QList<QString> phones;
};

class Phonebook
{
private:
    Person** _arrPersons;
    int _countPersons;
    int _maxPersons;
    void _sortPersons(QString field, QString sortType);
    void _swap(int firstIndex, int secondIndex);
public:
    QString getValue(int index);
    Phonebook();
    ~Phonebook();
    void addPerson(Person x);
    void deletePerson(int index);
    void sortByLastName(QString sortType);
    void sortByFirstName(QString sortType);
    void sortByBirthday(QString sortType);
    void sortByEmail(QString sortType);
    Person& operator [](int index);
    int getCount();
};

#endif // PHONEBOOK_H
