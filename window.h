#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <QApplication>
#include <QtCore>
#include <QtWidgets>

class Window : public QWidget
{
    Q_OBJECT
private:
    QList<QWidget*> widgets;
    QHBoxLayout *layout; // горизонтальное размещение виджетов
public:
    Window(QWidget *parent = 0);
    ~Window();
    void add(QString widgetName); //метод добавления элементов интерфейса в коллекцию
    void connect(); //метод для соединения между собой помещенных в коллекцию виджетов
};


#endif // WINDOW_H
