#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <QString>
#include <memory>
#include "model/model.h"
#include "model/cell.h"

class ViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ViewModel(QObject *parent = 0);
    
signals:
    void generateFieldInQml(unsigned int size);
    void changeCellState(unsigned int x, unsigned int y, const QString & stateString);
    void playerWin(model::Model::ePlayer player);
public slots:
    void NewGame(unsigned int size);
    void OnCellCliced(unsigned int x, unsigned int y);

private:
    QString GetStateString(const model::Cell::eState state);
private:
    std::unique_ptr<model::Model> model_;
};

#endif // VIEWMODEL_H
