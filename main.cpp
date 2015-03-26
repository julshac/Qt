#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window window;
    window.add("QSpinBox");
    window.add("QScrollBar");
    window.add("QSlider");
    window.add("QLabel");
    window.connect();
    window.show();
    return a.exec();
}







