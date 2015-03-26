#ifndef ADDFILTERWINDOW_H
#define ADDFILTERWINDOW_H

#include <QtWidgets>
#include <QtCore>

const int filter_names_count = 6;
const QString filter_names[] = {
  "LastName", "FirstName", "Second Name", "Birthday", "E-mail", "Phone"
};


class AddFilterWindow : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *filterLayout;
    QComboBox *filterChoose;
    QPushButton *addButton;
    QVBoxLayout *mainLayout;
    QWidget *filterWidget;
public:
    explicit AddFilterWindow(QWidget *parent = 0);

signals:
    void FilterSignal(QMap<QString, QString>&);
public slots:
    void onAddClick();
    void comboChanged(QString nname);
};

#endif // ADDFILTERWINDOW_H
