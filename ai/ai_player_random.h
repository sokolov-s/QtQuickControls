#ifndef AIPLAYERRANDOM_H
#define AIPLAYERRANDOM_H

#include "iplayer.h"

namespace ai {

class AIPlayerRandom : public IPlayer
{
public:
    AIPlayerRandom();
    ~AIPlayerRandom();
    bool IsHuman() const override {return false;}
private:
    void CalculateTurn(unsigned int *x, unsigned int *y) const override;
};

} //namespace ai
#endif // AIPLAYERRANDOM_H
