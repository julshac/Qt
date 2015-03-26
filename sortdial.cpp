#include "sortdial.h"

SortDial::SortDial(QWidget *parent) : QWidget(parent)
{
    qDebug("Sort");
    this->setFixedSize(320, 160);
    this->setWindowTitle("Choose Sort Type");
    layout = new QVBoxLayout(this);
    chooseBox = new QComboBox();
    chooseBox->addItem("Sort By Last Name");
    chooseBox->addItem("Sort By First Name");
    chooseBox->addItem("Sort By Birthday");
    chooseBox->addItem("Sort By E-mail");
    layout->addWidget(chooseBox);
    okButton = new QPushButton("Sort");
    layout->addWidget(okButton);
    connect(okButton, SIGNAL(pressed()), this, SLOT(onOkClick()));
}

void SortDial::onOkClick()
{
    emit SortSignal(chooseBox->currentIndex());
    this->close();
}
