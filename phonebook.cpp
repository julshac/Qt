#include "phonebook.h"
#include "exceptions.h"
const int N = 3;
const int dN = 2;

void Phonebook::_sortPersons(QString field, QString sortType)
{
    if (field == "lName")
    {
        if (sortType == "<")
        {
            for (int i = 0; i < _countPersons - 1; i++)
            {
                for (int j = i + 1; j < _countPersons; j++)
                {
                    if ((_arrPersons[i]->lastName) > (_arrPersons[j]->lastName))
                    {
                        _swap(i,j);
                    }
                }
            }
        }
        else
        {
            if (sortType == ">")
            {
                for (int i = 0; i < _countPersons - 1; i++)
                {
                    for (int j = i + 1; j < _countPersons; j++)
                    {
                        if ((_arrPersons[i]->lastName) < (_arrPersons[j]->lastName))
                        {
                            _swap(i,j);
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (field == "fName")
        {
            if (sortType == "<")
            {
                for (int i = 0; i < _countPersons - 1; i++)
                {
                    for (int j = i + 1; j < _countPersons; j++)
                    {
                        if ((_arrPersons[i]->firstName) > (_arrPersons[j]->firstName))
                        {
                            _swap(i,j);
                        }
                    }
                }
            }
            else
            {
                if (sortType == ">")
                {
                    for (int i = 0; i < _countPersons - 1; i++)
                    {
                        for (int j = i + 1; j < _countPersons; j++)
                        {
                            if ((_arrPersons[i]->firstName) < (_arrPersons[j]->firstName))
                            {
                                _swap(i,j);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (field == "birthday")
            {
                if (sortType == "<")
                {
                    for (int i = 0; i < _countPersons - 1; i++)
                    {
                        for (int j = i + 1; j < _countPersons; j++)
                        {
                            if ((_arrPersons[i]->birthday) > (_arrPersons[j]->birthday))
                            {
                                _swap(i,j);
                            }
                        }
                    }
                }
                else
                {
                    if (sortType == ">")
                    {
                        for (int i = 0; i < _countPersons - 1; i++)
                        {
                            for (int j = i + 1; j < _countPersons; j++)
                            {
                                if ((_arrPersons[i]->birthday) < (_arrPersons[j]->birthday))
                                {
                                    _swap(i,j);
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if (field == "email")
                {
                    if (sortType == "<")
                    {
                        for (int i = 0; i < _countPersons - 1; i++)
                        {
                            for (int j = i + 1; j < _countPersons; j++)
                            {
                                if ((_arrPersons[i]->email) > (_arrPersons[j]->email))
                                {
                                    _swap(i,j);
                                }
                            }
                        }
                    }
                    else
                    {
                        if (sortType == ">")
                        {
                            for (int i = 0; i < _countPersons - 1; i++)
                            {
                                for (int j = i + 1; j < _countPersons; j++)
                                {
                                    if ((_arrPersons[i]->email) < (_arrPersons[j]->email))
                                    {
                                        _swap(i,j);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Phonebook::_swap(int firstIndex, int secondIndex)
{
    Person* temp;
    temp = _arrPersons[firstIndex];
    _arrPersons[firstIndex] = _arrPersons[secondIndex];
    _arrPersons[secondIndex] = temp;
}

QString Phonebook::getValue(int index)
{
    QString tempString;
    tempString = _arrPersons[index]->lastName + "   " + _arrPersons[index]->firstName + "   " +
            _arrPersons[index]->secondName + "   " +
            QString::number(_arrPersons[index]->birthday.day()) + "." +
            QString::number(_arrPersons[index]->birthday.month()) +
            "." + QString::number(_arrPersons[index]->birthday.year()) +
            "    " + _arrPersons[index]->email;
    for (int i = 0; i < _arrPersons[index]->phones.count(); i++)
    {
        tempString = tempString + "    " + _arrPersons[index]->phones[i];
    }
    return tempString;
}

Phonebook::Phonebook()
{
    _maxPersons = N;
    _countPersons = 0;
    _arrPersons = new Person*[_maxPersons];
}

Phonebook::~Phonebook()
{
    for (int i = 0; i < _countPersons; i++)
    {
        delete _arrPersons[i];
    }
    delete[] _arrPersons;
}

void Phonebook::addPerson(Person x)
{
    if (_maxPersons == _countPersons)
    {
        Person** temp;
        temp = new Person*[_maxPersons];
        for (int i = 0; i < _maxPersons; i++)
        {
            temp[i] = _arrPersons[i];
        }
        delete[] _arrPersons;
        _arrPersons = new Person*[_maxPersons + dN];
        for (int i = 0; i < _maxPersons; i++)
        {
            _arrPersons[i] = temp[i];
        }
        delete[] temp;
        _maxPersons += dN;
    }
    _arrPersons[_countPersons] = new Person;
    *(_arrPersons[_countPersons]) = x;
    _countPersons++;
}

void Phonebook::deletePerson(int index)
{
    if (index >= _countPersons)
    {
        throw BadIndex();
    }
    Person* temp;
    temp = _arrPersons[index];

    for (int i = index; i < _countPersons - 1; i++)
    {
        _arrPersons[i] = _arrPersons[i + 1];
    }
    _arrPersons[_countPersons - 1] = temp;
    delete _arrPersons[_countPersons - 1];
    _countPersons--;

}

void Phonebook::sortByLastName(QString sortType)
{
    QString temp;
    temp = "lName";
    _sortPersons(temp, sortType);
}

void Phonebook::sortByFirstName(QString sortType)
{
    QString temp;
    temp = "fName";
    _sortPersons(temp, sortType);
}

void Phonebook::sortByBirthday(QString sortType)
{
    QString temp;
    temp = "birthday";
    _sortPersons(temp, sortType);
}

void Phonebook::sortByEmail(QString sortType)
{
    QString temp;
    temp = "email";
    _sortPersons(temp, sortType);
}

Person &Phonebook::operator [](int index)
{
    if (index >= _countPersons)
    {
        throw BadIndex();
    }
    return *(_arrPersons[index]);
}

int Phonebook::getCount()
{
    return _countPersons;
}
