#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "viewmodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ViewModel viewmodel;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("viewmodel", &viewmodel);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}

