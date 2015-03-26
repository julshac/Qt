#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout();
    setLayout(layout);
}

Window::~Window()
{
    for(int i = 0; i < widgets.length(); i++)
    {
        delete widgets[i];
    }
    delete layout;
}

void Window::add(QString widgetName)
{
    QWidget *nWidget;
    if(widgetName == "QLabel")
    {
        nWidget = new QLabel();
    } else if(widgetName == "QSpinBox")
    {
        nWidget = new QSpinBox();
    } else if(widgetName == "QScrollBar")
    {
        nWidget = new QScrollBar();
    } else if(widgetName == "QSlider")
    {
        nWidget = new QSlider();
    } else
    {
        return;
    }
    layout->addWidget(nWidget);
    widgets.append(nWidget);
}

void Window::connect()
{
    for(int i = 0; i < widgets.length(); i++)
    {
        QString widgetName = widgets[i]->metaObject()->className();
        for(int j = i + 1; j < widgets.length(); j++)
        {
            QString nextWidgetName = widgets[j]->metaObject()->className();
            if(widgetName == "QSpinBox" || widgetName == "QScrollBar" || widgetName == "QSlider")
            {
                if(nextWidgetName == "QLabel")
                {
                    QObject::connect(widgets[i], SIGNAL(valueChanged(int)), widgets[j], SLOT(setNum(int)));
                    QObject::connect(widgets[j], SIGNAL(valueChanged(int)), widgets[i], SLOT(setNum(int)));
                } else
                {
                    QObject::connect(widgets[i], SIGNAL(valueChanged(int)), widgets[j], SLOT(setValue(int)));
                    QObject::connect(widgets[j], SIGNAL(valueChanged(int)), widgets[i], SLOT(setValue(int)));
                }
            }
        }

    }
}
