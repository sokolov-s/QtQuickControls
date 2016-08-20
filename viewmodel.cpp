#include "viewmodel.h"
#include <QQmlEngine>
#include <QQmlComponent>

ViewModel::ViewModel(QObject *parent) : QObject(parent)
{
//    qmlRegisterType<ViewModel>("com.TicTacToe.ViewModel", 1, 0, "ViewModel");
}

void ViewModel::NewGame(unsigned int size)
{
    model_.reset(new model::Model(this));
    model_->CreateField(size);
    emit generateFieldInQml(size);
}
