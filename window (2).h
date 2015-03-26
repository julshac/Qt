#ifndef WINDOW_H
#define WINDOW_H

#include <QtCore>
#include <QtWidgets>


class Window : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *layout;
    QComboBox *shapeCombo;
    QPushButton *addShapeButton;
    QPushButton *deleteShapeButton;
    QPushButton *gotoFocusItem;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QLabel *pos_info[2];
    QLineEdit *pos_edits[2];
    int item_num;
    QLabel *item_num_label;
public slots:
    void onAddShape();
    void onDeleteShape();
    void onGotoFocusItem();
    void deleteShape();
public:
    Window();
    ~Window();
};

#endif // WINDOW_H
