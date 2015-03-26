#include "findwindow.h"

Fwindow::Fwindow(Phonebook *phonebook, QWidget *parent) : QWidget(parent)
{
    findButton = new QPushButton("Find");
    addFilterButton = new QPushButton("Add Filter");
    removeFilterButton = new QPushButton("Remove Filter");
    filterList = new QListWidget();
    peopleList = new QListWidget();
    mainLayout = new QHBoxLayout(this);
    buttonLayout = new QVBoxLayout();
    listLayout = new QHBoxLayout();

    connect(addFilterButton, SIGNAL(pressed()), this, SLOT(onAddFilterClick()));
    connect(removeFilterButton, SIGNAL(pressed()), this, SLOT(onRemoveFilterClick()));
    connect(findButton, SIGNAL(pressed()), this, SLOT(onFindClick()));

    buttonLayout->addWidget(addFilterButton);
    buttonLayout->addWidget(removeFilterButton);
    buttonLayout->addWidget(findButton);

    listLayout->addWidget(filterList);
    mainLayout->addLayout(buttonLayout);

    this->phonebook = phonebook;
}

void Fwindow::onAddFilterClick()
{
    AddFilterWindow *w = new AddFilterWindow();
    connect(w, SIGNAL(FilterSignal(QMap<QString,QString>&)), this, SLOT(onFilterAddSignal(QMap<QString,QString>&)));
    w->show();
}

void Fwindow::onRemoveFilterClick()
{
    QListWidgetItem *p = filterList->takeItem(filterList->currentRow());
    qDebug(p->text().left(p->text().indexOf(':')).toStdString().c_str());
    findParams.remove(p->text().left(p->text().indexOf(':')));
}

void Fwindow::onFindClick()
{
    QList<Person> findResults;
    Person p;
    bool correct;
    QString date_temp;
    for(int i = 0; i < phonebook->getCount(); i++) {
        p = (*phonebook)[i];
        QString *strings[] = {
            &p.lastName, &p.firstName, &p.secondName, &date_temp, &p.email
        };
        correct = false;
        date_temp = p.birthday.toString("dd.MM.yyyy");
        for(int j = 0; j < findParams.count(); j++) {
            if(findParams.keys()[j] == filter_names[filter_names_count - 1]) {
                bool phoneFinded = false;
                for(int k = 0; k < p.phones.count(); k++) {
                    if(p.phones[k] == findParams.values()[j]) {
                        phoneFinded = true;
                        break;
                    }
                }
                if(phoneFinded == true) {
                    correct = true;
                }
            } else {
                for(int k = 0; k < filter_names_count - 1; k++) {
                    if(filter_names[k] == findParams.keys()[j]) {
                        if(*strings[k] == findParams.values()[j]) {
                            correct = true;
                            break;
                        }
                    }
                }
            }
        }
        if(correct == true) {
            findResults.append(p);
        }
    }
}

void Fwindow::onFilterAddSignal(QMap<QString, QString> &params)
{
    qDebug("Sig Opened");
    findParams.unite(params);
    filterList->addItem(params.keys()[0] + QString(": ") + params.values()[0]);
}
