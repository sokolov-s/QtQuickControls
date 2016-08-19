#ifndef CELL_H
#define CELL_H

namespace model {

class Cell
{
public:
    enum class eState {
        kZ,
        kX,
        kO
    };

    Cell();
    void SetState(const eState state);
    eState GetState() const;
private:
    eState state_ = eState::kZ;
};

} //namespace model
#endif // CELL_H
