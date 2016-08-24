#include "wincheck.h"
#include "ai_exeptions.h"
#include "../model/model_exeptions.h"

bool ai::IsWin(const model::Field &field, const model::Cell::eState state, const size_t count2win)
{
    switch (field.GetSize()) {
    case 3:
        for(size_t y = 0; y < field.GetSize(); ++y) {
            for(size_t x = 0; x < field.GetSize(); ++x) {
                if (field.GetCell(x,y).GetState() == state) {
                    if(0 == x && 0 == y && CheckDiagonal(field, state, model::Cell::Position(x, y), count2win, eTrend::kX2RightY2Down) == 0)
                        return true;
                    if(field.GetSize() - 1 == x && field.GetSize() - 1 == y && CheckDiagonal(field, state, model::Cell::Position(x, y), count2win, eTrend::kX2LeftY2Down) == 0)
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
    case eTrend::kX2Right:
        for(; x < field.GetSize(); ++x) {
            try{
                if(field.GetCell(x, position.y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const model::EWrongParameter &/*err*/) {
                break;
            }
        }
        break;

    case eTrend::kX2Left:
        for(; true; --x) {
            try {
                if(field.GetCell(x, position.y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const model::EWrongParameter &/*err*/) {
                break;
            }

        }
        break;

    default: throw EWrongParameter("Trend must be set to kX2Right or kX2Left"); break;
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
    case eTrend::kY2Up:
        for(; y < field.GetSize(); ++y) {
            try {
                if(field.GetCell(position.x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const model::EWrongParameter &/*err*/) {
                break;
            }
        }
        break;

    case eTrend::kY2Down:
        for(; true; --y) {
            try {
                if(field.GetCell(position.x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const model::EWrongParameter &/*err*/) {
                break;
            }
        }
        break;

    default: throw EWrongParameter("Trend must be set to kY2Up or kY2Down"); break;
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
    case eTrend::kX2RightY2Down:
        for(; x < field.GetSize() && y < field.GetSize(); ++x, ++y) {
            try {
                if(field.GetCell(x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const model::EWrongParameter &/*err*/) {
                break;
            }
        }
        break;

    case eTrend::kX2RightY2Up:
        for(; x < field.GetSize(); ++x, --y) {
            try {
                if(field.GetCell(x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const model::EWrongParameter &/*err*/) {
                break;
            }
        }
        break;

    case eTrend::kX2LeftY2Down:
        for(; y < field.GetSize(); --x, ++y) {
            try {
                if(field.GetCell(x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const model::EWrongParameter &/*err*/) {
                break;
            }
        }
        break;

    case eTrend::kX2LeftY2Up:
        for(; true; --x, --y) {
            try {
                if(field.GetCell(x, y).GetState() == state)
                    ++cnt;
                if(cnt >= count2win) return 0;
            } catch (const model::EWrongParameter &/*err*/) {
                break;
            }
        }
        break;

    default: throw EWrongParameter("Trend must be set to kX2RightY2Down, kX2RightY2Up, kX2LeftY2Down or kX2LeftY2Up"); break;
    }

    return count2win - cnt;
}
