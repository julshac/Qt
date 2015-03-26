#include "addfilterwindow.h"

AddFilterWindow::AddFilterWindow(QWidget *parent) :
    QWidget(parent)
{
    addButton = new QPushButton("Add");
    filterChoose = new QComboBox();
    filterLayout = new QVBoxLayout();
    mainLayout = new QVBoxLayout(this);
    filterWidget = 0;

    connect(filterChoose, SIGNAL(currentIndexChanged(QString)), this, SLOT(comboChanged(QString)));
    connect(addButton, SIGNAL(pressed()), this, SLOT(onAddClick()));

    mainLayout->addLayout(filterLayout);
    filterLayout->addWidget(filterChoose);
    mainLayout->addWidget(addButton);

    filterChoose->addItem("Choose filter:");
    for(int i = 0; i < filter_names_count; i++) {
        filterChoose->addItem(filter_names[i]);
    }

    addButton->setDisabled(true);
}

void AddFilterWindow::onAddClick()
{
    QMap<QString, QString> *res_map = new QMap<QString, QString>();
    QString filter_result;
    filter_result = (!strcmp(filterWidget->metaObject()->className(), "QLineEdit")) ?
                ((QLineEdit*)filterWidget)->text() : ((QDateEdit*)filterWidget)->date().toString("dd.MM.yyyy");
    QString num; num.setNum(filterChoose->currentIndex() - 1);
    qDebug(num.toUtf8());
    res_map->insert(filter_names[filterChoose->currentIndex() - 1], filter_result);
    emit FilterSignal(*res_map);
    this->close();
}

void AddFilterWindow::comboChanged(QString nname)
{
    int index = -1;
    for(int i = 0; i < filter_names_count; i++) {
        if(filter_names[i] == nname) {
            index = i;
            break;
        }
    }
    QWidget *rm = filterWidget;
    if(rm) {
        filterLayout->removeWidget(rm);
        delete rm;
    }
    switch(index) {
    case 0: case 1: case 2: case 4: case 5:
        filterWidget = new QLineEdit(); break;
    case 3:
        filterWidget = new QDateEdit(); break;
    default:
        return;
    }
    filterLayout->addWidget(filterWidget);
    addButton->setDisabled(false);
}
