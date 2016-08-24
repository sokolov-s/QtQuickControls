#ifndef FIELDANALIZER_H
#define FIELDANALIZER_H
#include "../model/field.h"
#include "../model/cell.h"
namespace ai {

enum class eTrend {
    kX2Right,
    kX2Left,
    kY2Up,
    kY2Down,
    kX2RightY2Down,
    kX2RightY2Up,
    kX2LeftY2Down,
    kX2LeftY2Up
};
bool IsWin(const model::Field &field, const model::Cell::eState state, const size_t count2win);

/**
 * @brief CheckHorizontal - check horizontal line from position to end or begin of field (depends of trend).
 * @param field - link to current field
 * @param state - what kind of player we need to check
 * @param position - start position
 * @param count2win - count of continuous values of cell in field for the victory
 * @param trend - Direction for x. Can be only kX2Right or kX2Left. Function generate EWrongParameter exeption
 * if trend !=  kX2Right or kX2Left.
 * @return - 0 if trend has victorious line. In otherwise return a number of needed  cells to win
 */
size_t CheckHorizontal(const model::Field &field, const model::Cell::eState state,
                       const model::Cell::Position &position, const size_t count2win,
                       const eTrend trend = eTrend::kX2Right);

/**
 * @brief CheckVertical - check vertical line from position to end or begin of field (depends of trend).
 * @param field - link to current field
 * @param state - what kind of player we need to check
 * @param position - start position
 * @param count2win - count of continuous values of cell in field for the victory
 * @param trend - Direction for y. Can be only kY2Up or kY2Down. Function generate EWrongParameter exeption
 * if trend !=  kY2Up or kY2Down.
 * @return - 0 if trend has victorious line. In otherwise return a number of needed  cells to win
 */
size_t CheckVertical(const model::Field &field, const model::Cell::eState state,
                     const model::Cell::Position &position, const size_t count2win,
                     const eTrend trend = eTrend::kY2Down);

/**
 * @brief CheckVertical - check vertical line from position to end or begin of field (depends of trend).
 * @param field - link to current field
 * @param state - what kind of player we need to check
 * @param position - start position
 * @param count2win - count of continuous values of cell in field for the victory
 * @param trend - Direction for x and y. Can be only kX2RightY2Down, kX2RightY2Up, kX2LeftDownY or kX2LeftY2Up.
 * Function generate EWrongParameter exeption if trend !=  kX2RightY2Down, kX2RightY2Up, kX2LeftY2Down or kX2LeftY2Up.
 * @return - 0 if trend has victorious line. In otherwise return a number of needed  cells to win
 */
size_t CheckDiagonal(const model::Field &field, const model::Cell::eState state,
                   const model::Cell::Position &position,
                   const size_t count2win, const eTrend trend);

} //namespace ai
#endif // FIELDANALIZER_H
