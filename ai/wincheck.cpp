#include "wincheck.h"
#include <stdexcept>
#include "../model/model_exeptions.h"

bool ai::IsWin(const model::Field &field, const model::Cell::eState state, const size_t count2win)
{
    switch (field.GetSize()) {
    case 3:
        for(size_t y = 0; y < field.GetSize(); ++y) {
            for(size_t x = 0; x < field.GetSize(); ++x) {
                if (field.GetCell(x,y).GetState() == state) {
                    if(0 == x && 0 == y && CheckDiagonal(field, state, model::Cell::Position(x, y), count2win, eTrend::kX2PositiveY2Positive) == 0)
                        return true;
                    if(field.GetSize() - 1 == x && 0 == y && CheckDiagonal(field, state, model::Cell::Position(x, y), count2win, eTrend::kX2NegativeY2Positive) == 0)
                        return true;
                    if(0 == y && CheckVertical(field, state, model::Cell::Position(x,y), count2win) == 0)
                        return true;
                    if(0 == x && CheckHorizontal(field, state, model::Cell::Position(x,y), count2win) == 0)
                        return true;
                }
            }
        }
        break;

    default:
        break;
    }
    return false;
}

size_t ai::CheckHorizontal(const model::Field &field, const model::Cell::eState state,
                           const model::Cell::Position &position, const size_t count2win,
                           const eTrend trend)
{
    size_t cnt = 0;
    size_t x = position.x;
    switch(trend) {
    case eTrend::kX2Positive:
        for(; x < field.GetSize(); ++x) {
            try{
                if(field.GetCell(x, position.y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const std::invalid_argument &/*err*/) {
                break;
            }
        }
        break;

    case eTrend::kX2Negative:
        for(; true; --x) {
            try {
                if(field.GetCell(x, position.y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const std::invalid_argument &/*err*/) {
                break;
            }

        }
        break;

    default: throw std::invalid_argument("Trend must be set to kX2Positive or kX2Negative"); break;
    }
    return count2win - cnt;
}

size_t ai::CheckVertical(const model::Field &field, const model::Cell::eState state,
                         const model::Cell::Position &position, const size_t count2win,
                         const eTrend trend)
{
    size_t cnt = 0;
    size_t y = position.y;
    switch(trend) {
    case eTrend::kY2Positve:
        for(; y < field.GetSize(); ++y) {
            try {
                if(field.GetCell(position.x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const std::invalid_argument &/*err*/) {
                break;
            }
        }
        break;

    case eTrend::kY2Negative:
        for(; true; --y) {
            try {
                if(field.GetCell(position.x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const std::invalid_argument &/*err*/) {
                break;
            }
        }
        break;

    default: throw std::invalid_argument("Trend must be set to kY2Positve or kY2Negative"); break;
    }

    return count2win - cnt;
}

size_t ai::CheckDiagonal(const model::Field &field, const model::Cell::eState state,
                         const model::Cell::Position &position,
                         const size_t count2win, const eTrend trend)
{
    size_t cnt = 0;
    size_t x = position.x;
    size_t y = position.y;
    switch(trend) {
    case eTrend::kX2PositiveY2Positive:
        for(; x < field.GetSize() && y < field.GetSize(); ++x, ++y) {
            try {
                if(field.GetCell(x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const std::invalid_argument &/*err*/) {
                break;
            }
        }
        break;

    case eTrend::kX2PositiveY2Negative:
        for(; x < field.GetSize(); ++x, --y) {
            try {
                if(field.GetCell(x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const std::invalid_argument &/*err*/) {
                break;
            }
        }
        break;

    case eTrend::kX2NegativeY2Positive:
        for(; y < field.GetSize(); --x, ++y) {
            try {
                if(field.GetCell(x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const std::invalid_argument &/*err*/) {
                break;
            }
        }
        break;

    case eTrend::kX2NegativeY2Negative:
        for(; true; --x, --y) {
            try {
                if(field.GetCell(x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const std::invalid_argument &/*err*/) {
                break;
            }
        }
        break;

    default: throw std::invalid_argument("Trend must be set to kX2PositiveY2Positive, kX2PositiveY2Negative, kX2NegativeY2Positive or kX2NegativeY2Negative"); break;
    }

    return count2win - cnt;
}
