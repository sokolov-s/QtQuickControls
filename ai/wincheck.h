#ifndef FIELDANALIZER_H
#define FIELDANALIZER_H
#include "../model/field.h"
#include "../model/cell.h"
namespace ai {

enum class eTrend {
    kX2Positive,
    kX2Negative,
    kY2Positve,
    kY2Negative,
    kX2PositiveY2Positive,
    kX2PositiveY2Negative,
    kX2NegativeY2Positive,
    kX2NegativeY2Negative
};
bool IsWin(const model::Field &field, const model::Cell::eState state, const size_t count2win);

/**
 * @brief CheckHorizontal - check horizontal line from position to end or begin of field (depends of trend).
 * @param field - link to current field
 * @param state - what kind of player we need to check
 * @param position - start position
 * @param count2win - count of continuous values of cell in field for the victory
 * @param trend - Direction for x. Can be only kX2Positive or kX2Negative. Function generate EWrongParameter exeption
 * if trend !=  kX2Positive or kX2Negative.
 * @return - 0 if trend has victorious line. In otherwise return a number of needed  cells to win
 */
size_t CheckHorizontal(const model::Field &field, const model::Cell::eState state,
                       const model::Cell::Position &position, const size_t count2win,
                       const eTrend trend = eTrend::kX2Positive);

/**
 * @brief CheckVertical - check vertical line from position to end or begin of field (depends of trend).
 * @param field - link to current field
 * @param state - what kind of player we need to check
 * @param position - start position
 * @param count2win - count of continuous values of cell in field for the victory
 * @param trend - Direction for y. Can be only kY2Positve or kY2Negative. Function generate EWrongParameter exeption
 * if trend !=  kY2Positve or kY2Negative.
 * @return - 0 if trend has victorious line. In otherwise return a number of needed  cells to win
 */
size_t CheckVertical(const model::Field &field, const model::Cell::eState state,
                     const model::Cell::Position &position, const size_t count2win,
                     const eTrend trend = eTrend::kY2Positve);

/**
 * @brief CheckVertical - check vertical line from position to end or begin of field (depends of trend).
 * @param field - link to current field
 * @param state - what kind of player we need to check
 * @param position - start position
 * @param count2win - count of continuous values of cell in field for the victory
 * @param trend - Direction for x and y. Can be only kX2PositiveY2Positive, kX2PositiveY2Negative, kX2NegativeDownY or kX2NegativeY2Negative.
 * Function generate EWrongParameter exeption if trend !=  kX2PositiveY2Positive, kX2PositiveY2Negative,
 * kX2NegativeY2Positive or kX2NegativeY2Negative.
 * @return - 0 if trend has victorious line. In otherwise return a number of needed  cells to win
 */
size_t CheckDiagonal(const model::Field &field, const model::Cell::eState state,
                   const model::Cell::Position &position,
                   const size_t count2win, const eTrend trend);

} //namespace ai
#endif // FIELDANALIZER_H
