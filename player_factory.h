#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include <memory>
#include "ai/iplayer.h"

namespace factory {

class PlayerFactory
{
public:
    enum ePlayer {
        kHuman,
        kAiLevel1,
        kAiLevel2
    };
    static PlayerFactory &Instance();
    typedef std::unique_ptr<ai::IPlayer> Player;
    Player CreatePlayer(ePlayer player, model::Model::ePlayer playerType);
private:
    PlayerFactory(){}
    ~PlayerFactory(){}
    PlayerFactory(const PlayerFactory &) = delete;
    PlayerFactory & operator=(const PlayerFactory&) = delete;
private:

};

} //namespace factory
#endif // PLAYERFACTORY_H
