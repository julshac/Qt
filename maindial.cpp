#include "maindial.h"
#include "findwindow.h"

void MainDial::onAddClick()
{
    AddWindow* w = new AddWindow(this, phonebook);
    w->show();
}

void MainDial::onDeleteClick()
{
    int index = list->currentRow();
    QListWidgetItem *p = list->takeItem(index);
    delete p;
    phonebook->deletePerson(index);
}

void MainDial::onEditClick()
{
    AddWindow *w = new AddWindow(this, phonebook);
    w->show();
    w->setWindowTitle("Edit");
    int index = list->currentRow();
    Person savedcopy = phonebook->operator [](index);
    onDeleteClick();
    Person change = savedcopy;
    w->editPerson(change);

}

void MainDial::onFindClick()
{
    Fwindow *w = new Fwindow(phonebook);
    w->show();
}

void MainDial::onSortClick()
{
    SortDial *p = new SortDial();
    connect(p, SIGNAL(SortSignal(int)), this, SLOT(sortBook(int)));
    p->show();
}

void MainDial::onSaveClick()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("Save File"));
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    for(int i = 0; i < phonebook->getCount(); i++) {
        Person& p = phonebook->operator [](i);
        stream << formateString(p) << "\n";
    }
    stream.flush();
    file.close();
}

void MainDial::onLoadClick()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Load File"));
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString temp;
    qDebug("file opened");
    while(phonebook->getCount() > 0) {
        phonebook->deletePerson(0);
    }
    while(!stream.atEnd()) {
        temp = stream.readLine();
        phonebook->addPerson(formatePerson(temp));
    }
    file.close();
    showBook();
}

QString MainDial::formateString(Person &person)
{
    QString ret = person.firstName + "|" + person.lastName + "|" + person.secondName + "|" +
            person.birthday.toString("dd.MM.yyyy") + "|" + person.email + "|/";
    for(int i = 0; i < person.phones.length(); i++) {
        ret += person.phones[i] + "/";
    }
    return ret;
}

Person &MainDial::formatePerson(QString string)
{
    Person *ret = new Person();
    QString date_temp;
    QString *params[] = {
        &ret->firstName, &ret->lastName, &ret->secondName, &date_temp, &ret->email
    };
    int param_c = 0;
    int i = 0;
    while(string[i] != '/') {
        while(string[i] != '|') {
            *params[param_c] += string[i];
            ++i;
        }
        ++i;
        ++param_c;
    }
    qDebug("main params loaded");
    ++i;
    ret->birthday = QDate::fromString(date_temp, "dd.MM.yyyy");
    QString phone_temp;
    for(int j = string.indexOf('/') + 1; j < string.length(); j++) {
        if(string[j] == '/') {
            ret->phones.append(phone_temp);
            phone_temp = "";
            ++j;
        }
        phone_temp += string[j];
    }
    return *ret;
}

void MainDial::showBook()
{
    countPersons = phonebook->getCount();
    list->clear();
    QString tempString;
    for (int i = 0; i < phonebook->getCount(); i++)
    {
        tempString = phonebook->getValue(i);
        list->addItem(tempString);
    }
}

void MainDial::sortBook(int sorttype)
{
    switch(sorttype) {
    case LastName_Sort:
        phonebook->sortByLastName("<"); break;
    case FirstName_Sort:
        phonebook->sortByFirstName("<"); break;
    case Birthday_Sort:
        phonebook->sortByBirthday("<"); break;
    case Email_Sort:
        phonebook->sortByEmail("<"); break;
    default:
        qDebug("Sort Error");
    }
    showBook();
}

MainDial::MainDial()
{
    setWindowTitle("Phonebook");
    countPersons = 0;
    phonebook = new Phonebook;
    generalLayout = new QHBoxLayout((QWidget*) this);
    menuLayout = new QVBoxLayout((QWidget*) generalLayout);

    for(int i = 0; i < keysCount; i++)
    {
        buttons.insert(keys[i], new QPushButton(keys[i]));
        menuLayout->addWidget(buttons[keys[i]]);
        connect(buttons[keys[i]], SIGNAL(pressed()), this, SLOT(onAbstractClick()));
    }
    list = new QListWidget;
    generalLayout->addWidget(list);
    generalLayout->addLayout(menuLayout);
}

void MainDial::onAbstractClick()
{
    int buttonIndex;
    QPushButton *sender = (QPushButton*) this->sender();
    for(int i = 0; i < keysCount; i++) {
        if(buttons[keys[i]] == sender)
        {
            buttonIndex = i;
        }
    }
    switch(buttonIndex)
    {
    case 0:
        onAddClick();
        break;
    case 1:
        onDeleteClick();
        break;
    case 2:
        onEditClick();
        break;
    case 3:
        onFindClick();
        break;
    case 4:
        onSortClick();
        break;
    case 5:
        onSaveClick();
        break;
    case 6:
        onLoadClick();
        break;
    }
}



