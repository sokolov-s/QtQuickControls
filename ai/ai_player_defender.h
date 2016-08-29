#ifndef AIPLAYERDEFENDER_H
#define AIPLAYERDEFENDER_H

#include "iplayer.h"

namespace ai {

class AIPlayerDefender : public IPlayer
{
public:
    AIPlayerDefender();
    ~AIPlayerDefender();
    bool IsHuman() const override {return false;}
private:
    void CalculateTurn(unsigned int *x, unsigned int *y) const override;
};

} //namespace ai
#endif // AIPLAYERDEFENDER_H
