#ifndef AIPLAYERRANDOM_H
#define AIPLAYERRANDOM_H

#include "iplayer.h"

namespace ai {

/**
 * @brief The AIPlayerRandom class
 * Create a bot which does not analyze any situation and just takes random empty cell from field and
 * makes a turn into this cell
 */
class AIPlayerRandom : public IPlayer
{
public:
    AIPlayerRandom(model::Model::ePlayer playerType);
    ~AIPlayerRandom();
    bool IsHuman() const override {return false;}
protected:
    void CalculateTurn(unsigned int *x, unsigned int *y) const override;
};

} //namespace ai
#endif // AIPLAYERRANDOM_H
