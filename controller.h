#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <memory>
#include "model/model.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    
signals:
    void generateFieldInQml(unsigned int size);
    
public slots:
    void NewGame(unsigned int size);
    
private:
    std::unique_ptr<model::Model> model_;
};

#endif // CONTROLLER_H
