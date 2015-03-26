#include "incorrectnm.h"


incorrectnm::incorrectnm(QWidget *parrent, QString a)
{
    setWindowTitle("Error");
    layout = new QHBoxLayout;
    prnt = parrent;
    parrent->setEnabled(false);
    lbl = new QLabel;
    QString msg;
    msg = "Incorrect " + a + ". Please input " + a + " again";
    lbl->setText(msg);
    layout->addWidget(lbl);
    setLayout(layout);
}

void incorrectnm::closeEvent(QCloseEvent *event)
{
    prnt->setEnabled(true);
    event->accept();
}

