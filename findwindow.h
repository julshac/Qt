#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QtWidgets>
#include <QtCore>
#include "addfilterwindow.h"
#include "phonebook.h"

class Fwindow : public QWidget
{
    Q_OBJECT
private:
    QPushButton *findButton;
    QPushButton *addFilterButton;
    QPushButton *removeFilterButton;
    QHBoxLayout *mainLayout;
    QVBoxLayout *buttonLayout;
    QListWidget *filterList;
    QMap<QString, QString> findParams;
    Phonebook *phonebook;
    QListWidget *peopleList;
    QHBoxLayout* listLayout;
public:
    explicit Fwindow(Phonebook *phonebook, QWidget *parent = 0);
signals:

public slots:
    void onAddFilterClick();
    void onRemoveFilterClick();
    void onFindClick();
    void onFilterAddSignal(QMap<QString, QString> &params);
};

#endif // FINDWINDOW_H
