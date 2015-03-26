#include "window.h"

void Window::onAddShape()
{
    int index = shapeCombo->currentIndex();
    QGraphicsItem *item;
    int xpos = !pos_edits[0]->text().isEmpty() ? pos_edits[0]->text().toInt() : 0;
    int ypos = !pos_edits[1]->text().isEmpty() ? pos_edits[1]->text().toInt() : 0;
    switch(index) {
    case 0:
        item = new QGraphicsRectItem(xpos, ypos, 100, 100);
        ((QGraphicsRectItem*)item)->setBrush(QBrush(QColor(rand() % 255, rand() % 255, rand() % 255)));
        break;
    case 1:
        item = new QGraphicsEllipseItem(xpos, ypos, 100, 100);
        ((QGraphicsEllipseItem*)item)->setBrush(QBrush(QColor(rand() % 255, rand() % 255, rand() % 255)));
        break;
    case 2:
        item = new QGraphicsLineItem(xpos, ypos, 100, 100);
        break;
    default:
        return;
    }
    scene->addItem(item);
    item->setFlag(item->ItemIsMovable, true);
    item->setFlag(item->ItemIsFocusable, true);
    item->show();
    ++item_num;
    item_num_label->setText(QString("Elements: ") + QString().setNum(item_num));
}

void Window::onDeleteShape()
{
    if(scene->focusItem() == 0) {
        return;
    }
    QGraphicsItem *item = scene->focusItem();
    scene->removeItem(item);
    delete item;
    --item_num;
    item_num_label->setText(QString("Elements: ") + QString().setNum(item_num));
}

void Window::onGotoFocusItem()
{
    if(scene->focusItem() == 0) {
        return;
    }
    view->centerOn(scene->focusItem());
}

void Window::deleteShape()
{

}

Window::Window()
{
    this->setMinimumSize(640, 480);
    layout = new QGridLayout(this);
    setLayout(layout);
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    layout->addWidget(view, 0, 0, 2, 0);
    shapeCombo = new QComboBox();
    shapeCombo->addItem("Rectangle");
    shapeCombo->addItem("Circle");
    shapeCombo->addItem("Line");
    layout->addWidget(shapeCombo, 2, 0);
    addShapeButton = new QPushButton("Add");
    connect(addShapeButton, SIGNAL(pressed()), this, SLOT(onAddShape()));
    deleteShapeButton = new QPushButton("Delete");
    connect(deleteShapeButton, SIGNAL(pressed()), this, SLOT(onDeleteShape()));
    layout->addWidget(addShapeButton, 2, 1);
    layout->addWidget(deleteShapeButton, 2, 2);
    QHBoxLayout *positionLayout = new QHBoxLayout();
    layout->addLayout(positionLayout, 3, 0, Qt::AlignLeft);
    for(int i = 0; i < 2; i++) {
        pos_edits[i] = new QLineEdit();
        pos_edits[i]->setMaximumWidth(80);
        pos_info[i] = new QLabel();
        positionLayout->addWidget(pos_info[i]);
        positionLayout->addWidget(pos_edits[i]);
    }
    pos_info[0]->setText("x:");
    pos_info[1]->setText("y:");
    item_num_label = new QLabel("Elements: 0");
    gotoFocusItem = new QPushButton("Focus Item");
    layout->addWidget(gotoFocusItem, 3, 1);
    connect(gotoFocusItem, SIGNAL(pressed()), this, SLOT(onGotoFocusItem()));
    layout->addWidget(item_num_label, 3, 2);
    item_num = 0;
}

Window::~Window() {
    delete addShapeButton;
    delete deleteShapeButton;
    delete view;
    delete shapeCombo;
    delete scene;
    delete gotoFocusItem;
    delete addShapeButton;
    delete deleteShapeButton;
    delete layout;
}
