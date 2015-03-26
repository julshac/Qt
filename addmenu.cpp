#include "addmenu.h"


AddWindow::AddWindow(QWidget *parrent, Phonebook *phonebook)
{
    prnt = parrent;
    phnbk = phonebook;
    setWindowTitle("Add person");

    mainAdd = new QVBoxLayout;

    lastNameLbl = new QLabel;
    lastNameLbl->setText("Last Name:");
    mainAdd->addWidget(lastNameLbl);
    lastNameTxt = new QLineEdit;
    lastNameTxt->setMaximumHeight(25);
    mainAdd->addWidget(lastNameTxt);

    firstNameLbl = new QLabel;
    firstNameLbl->setText("First name*:");
    mainAdd->addWidget(firstNameLbl);
    firstNameTxt = new QLineEdit;
    firstNameTxt->setMaximumHeight(25);
    mainAdd->addWidget(firstNameTxt);

    secondNameLbl = new QLabel;
    secondNameLbl->setText("Second name:");
    mainAdd->addWidget(secondNameLbl);
    secondNameTxt = new QLineEdit;
    secondNameTxt->setMaximumHeight(25);
    mainAdd->addWidget(secondNameTxt);

    emailLbl = new QLabel;
    emailLbl->setText("Email");
    mainAdd->addWidget(emailLbl);
    emailTxt = new QLineEdit;
    emailTxt->setMaximumHeight(25);
    mainAdd->addWidget(emailTxt);

    birthdayLbl = new QLabel;
    birthdayLbl->setText("Birthday:");
    mainAdd->addWidget(birthdayLbl);
    QDate a;
    a.setDate(1901,1,1);
    birthdayTxt = new QDateEdit(a);
    birthdayTxt->setMaximumHeight(25);
    mainAdd->addWidget(birthdayTxt);

    phonesLayout = new QVBoxLayout;
    phonesLbl = new QLabel;
    phonesLbl->setText("Phone numbers*:");
    countPhones = 1;
    phoneTxt = new QLineEdit*[countPhones];
    phoneTxt[0] = new QLineEdit;
    phoneTxt[0]->setMaximumHeight(25);
    phonesLayout->addWidget(phonesLbl);
    phonesLayout->addWidget(phoneTxt[0]);
    mainAdd->addLayout(phonesLayout);
    addField = new QPushButton("Add number");
    mainAdd->addWidget(addField);

    buttonsLayout = new QHBoxLayout;
    cancelButton = new QPushButton("Cancel");
    OKButton = new QPushButton("OK");
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(OKButton);
    mainAdd->addLayout(buttonsLayout);

    connect(cancelButton, SIGNAL(pressed()), this, SLOT(onCancelClick()));
    connect(addField, SIGNAL(pressed()), this, SLOT(onAddPhoneClick()));
    connect(OKButton, SIGNAL(pressed()), this, SLOT(onOKClick()));

    parrent->setEnabled(false);

    setLayout(mainAdd);
}

void AddWindow::closeEvent(QCloseEvent *event)
{
    if(editmode == true && editmodeokcall == false) {
        onOKClick();
    }
    prnt->setEnabled(true);
    event->accept();
}

void AddWindow::editPerson(Person &p)
{
    editmode = true;
    lastNameTxt->setText(p.lastName);
    firstNameTxt->setText(p.firstName);
    secondNameTxt->setText(p.secondName);
    birthdayTxt->setDate(p.birthday);
    emailTxt->setText(p.email);
    phoneTxt[0]->setText(p.phones[0]);
    for(int i = 1; i < p.phones.length(); i++) {
        onAddPhoneClick();
        phoneTxt[i]->setText(p.phones[i]);
    }
}

void AddWindow::onOKClick()
{
    editmodeokcall = true;

    QRegExp RegLastName("([a-zA-Zа-яА-ЯёЁ]){1}([a-zA-Zа-яА-ЯёЁ0-9-.]){,30}([a-zA-Zа-яА-ЯёЁ0-9]){1}");
    QRegExp RegFirstName("([a-zA-Zа-яА-ЯёЁ]){1}([a-zA-Zа-яА-ЯёЁ0-9-.]){,30}([a-zA-Zа-яА-ЯёЁ0-9]){1}");
    QRegExp RegSecondName("([a-zA-Zа-яА-ЯёЁ]){1}([a-zA-Zа-яА-ЯёЁ0-9-.]){,30}([a-zA-Zа-яА-ЯёЁ0-9]){1}");
    QRegExp RegPhoneNumber("([+]){1}([0-9]){1,4}([(]){1}([0-9]){,5}([)]){1}([0-9]){7}");
    QRegExp RegEmail("([a-z]{1})+([_-a-z0-9]{,20})+@+([a-z.]{,10})+([a-z]{1})");
    Person x;
    if (firstNameTxt->text().length() == 0)
    {
        incorrectnm* a = new incorrectnm(this, "first name");
        a->show();
        return;
    }
    else
    {
         if (!RegFirstName.exactMatch(firstNameTxt->text()))
         {
             incorrectnm* a = new incorrectnm(this, "first name");
             a->show();
             return;
         }
    }
    x.firstName = firstNameTxt->text();
    if (secondNameTxt->text().length() != 0)
    {
        if (!RegSecondName.exactMatch(secondNameTxt->text()))
        {
            {
                incorrectnm* a = new incorrectnm(this, "second name");
                a->show();
                return;
            }
        }
    }
    x.secondName = secondNameTxt->text();
    if (lastNameTxt->text().length() != 0)
    {
        if (!RegLastName.exactMatch(lastNameTxt->text()))
        {
            incorrectnm* a = new incorrectnm(this, "last name");
            a->show();
            return;
        }
    }
    x.lastName = lastNameTxt->text();
    if (birthdayTxt->date() >= QDate::currentDate())
    {
        incorrectnm* a = new incorrectnm(this, "birthday");
        a->show();
        return;
    }
    x.birthday = birthdayTxt->date();
    if (emailTxt->text().length() != 0)
    {
        if (!RegEmail.exactMatch(emailTxt->text()))
        {
            incorrectnm* a = new incorrectnm(this, "email");
            a->show();
            return;
        }
    }
    x.email = emailTxt->text();

    QQueue<int> indexes;
    int tmpIndex;
    for (int i = 0; i < countPhones; i++)
    {
        if (phoneTxt[i]->text().length() != 0)
        {
            indexes.enqueue(i);
        }
    }
    if (indexes.count() == 0)
    {
        incorrectnm* a = new incorrectnm(this, "phone numbers");
        a->show();
        return;
    }
     else
    {
        while (indexes.length() != 0)
        {
            tmpIndex = indexes.dequeue();
            if (!RegPhoneNumber.exactMatch(phoneTxt[tmpIndex]->text()))
            {

                incorrectnm* a = new incorrectnm(this, "phone numbers");
                a->show();
                return;
            }
            else
            {
                x.phones.append(phoneTxt[tmpIndex]->text());
            }
        }
    }

    phnbk->addPerson(x);

    connect(this, SIGNAL(sayShowBook()), prnt, SLOT(showBook()));
    emit sayShowBook();
    prnt->setEnabled(true);
    this->close();

}

void AddWindow::onAddPhoneClick()
{
    QLineEdit** tmp;
    tmp = new QLineEdit*[countPhones];
    for (int i = 0; i < countPhones; i++)
    {
        tmp[i] = phoneTxt[i];
    }
    delete[] phoneTxt;
    phoneTxt = new QLineEdit*[countPhones + 1];
    for (int i = 0; i < countPhones; i++)
    {
        phoneTxt[i] = tmp[i];
    }
    phoneTxt[countPhones] = new QLineEdit;
    phoneTxt[countPhones]->setMaximumHeight(25);
    phonesLayout->addWidget(phoneTxt[countPhones]);
    delete[] tmp;
    countPhones++;
}

void AddWindow::onCancelClick()
{
    prnt->setEnabled(true);
    this->close();
}

