#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include <QString>
#include <memory>
#include "model/model.h"
#include "model/cell.h"
#include "ai/iplayer.h"
#include <vector>

class ViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ViewModel(QObject *parent = 0);

signals:
    void generateFieldInQml(unsigned int size);
    void changeCellState(unsigned int x, unsigned int y, const QString & stateString);
    void playerWin(const QString & player);
    void playerCanged(const QString & player);
    void standoff();
public slots:
    void NewGame(int player, unsigned int filedSize);
    void OnCellClicked(unsigned int x, unsigned int y, bool force = false);

private:
    QString GetStateString(const model::Cell::eState state);
    QString GetPlayerString(const model::Model::ePlayer player);
    typedef std::unique_ptr<ai::IPlayer> Player;
    std::vector<ViewModel::Player>::iterator GetCurrentPlayer();
private:
    std::unique_ptr<model::Model> model_;
    bool gameEnd_ = true;
    std::vector<Player> players_;
};

#endif // VIEWMODEL_H
