#include "controller.h"
#include <QQmlEngine>
#include <QQmlComponent>

Controller::Controller(QObject *parent) : QObject(parent)
{
    qmlRegisterType<Controller>("com.TicTacToe.controller", 1, 0, "Controller");
}

void Controller::NewGame(unsigned int size)
{
    model_.reset(new model::Model(this));
    model_->CreateField(size);
    emit generateFieldInQml(size);
}
