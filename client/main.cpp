#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>
#include <emscripten/val.h>

std::string gethref(){
    emscripten::val location = emscripten::val::global("location");
    return location["href"].as<std::string>();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int fontID = QFontDatabase::addApplicationFont(":/ttf/test.ttf");
    if (fontID >= 0){
        auto fontFamilies = QFontDatabase::applicationFontFamilies(fontID);
        QFont font;
        font.setFamilies(fontFamilies);
        a.setFont(font);
    }
    std::string href = gethref();
    qInfo()<<href;
    MainWindow w;
    w.show();
    return a.exec();
}
