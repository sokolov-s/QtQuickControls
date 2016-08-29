#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "iplayer.h"

namespace ai {

class HumanPlayer : public IPlayer
{
public:
    HumanPlayer(){}
    ~HumanPlayer(){}
    bool IsHuman() const override {return true;}
private:
    void CalculateTurn(unsigned int *, unsigned int *) const override {}
};

} //namespace ai
#endif // HUMANPLAYER_H
