#ifndef INCORRECTNM_H
#define INCORRECTNM_H
#pragma once
#include <QWidget>
#include "addmenu.h"

class incorrectnm : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* layout;
    QWidget* prnt;
    QLabel* lbl;
public:
    incorrectnm(QWidget* parrent, QString a);
    void closeEvent(QCloseEvent *event);
signals:

public slots:

};

#endif // INCORRECTNM_H
