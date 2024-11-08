#include "view.hpp"

#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    View view;
    view.TEST();
    return app.exec();
}
