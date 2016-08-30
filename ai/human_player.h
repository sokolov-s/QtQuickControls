#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "iplayer.h"

namespace ai {

/**
 * @brief The HumanPlayer class. It is a dummy for human player
 */
class HumanPlayer : public IPlayer
{
public:
    HumanPlayer(model::Model::ePlayer playerType): IPlayer(playerType) {}
    ~HumanPlayer(){}
    bool IsHuman() const override {return true;}
private:
    void CalculateTurn(unsigned int *, unsigned int *) const override {}
};

} //namespace ai
#endif // HUMANPLAYER_H
