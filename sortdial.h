#ifndef SORTDIAL_H
#define SORTDIAL_H

#include <QtCore>
#include <QtWidgets>


enum SignalType {
    LastName_Sort = 0, FirstName_Sort, Birthday_Sort, Email_Sort
};

class SortDial : public QWidget
{
    Q_OBJECT
public:
    explicit SortDial(QWidget *parent = 0);
    QPushButton *okButton;
    QComboBox *chooseBox;
    QVBoxLayout *layout;
signals:
    void SortSignal(int);
public slots:
    void onOkClick();
};

#endif // SORTDIAL_H
