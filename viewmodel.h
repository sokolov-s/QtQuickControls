#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <memory>
#include "model/model.h"

class ViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ViewModel(QObject *parent = 0);
    
signals:
    void generateFieldInQml(unsigned int size);
    
public slots:
    void NewGame(unsigned int size);
    
private:
    std::unique_ptr<model::Model> model_;
};

#endif // VIEWMODEL_H
