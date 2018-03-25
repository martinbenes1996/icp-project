
#include <iostream>

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    std::cout << "Ahoj!\n";
    QApplication app (argc, argv);

    QPushButton button ("Hello world !");
    button.show();

    return app.exec();
}