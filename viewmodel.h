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
    enum ePlayer {
        kHuman,
        kAi1,
        kAi2
    };

signals:
    void generateFieldInQml(unsigned int size);
    void changeCellState(unsigned int x, unsigned int y, const QString & stateString);
    void playerWin(const QString & player);
    void playerCanged(const QString & player);
    void standoff();
public slots:
    void NewGame(int player, unsigned int filedSize);
    void OnCellCliced(unsigned int x, unsigned int y);

private:
    QString GetStateString(const model::Cell::eState state);
    QString GetPlayerString(const model::Model::ePlayer player);
private:
    std::unique_ptr<model::Model> model_;
    bool gameEnd_ = true;
};

#endif // VIEWMODEL_H
