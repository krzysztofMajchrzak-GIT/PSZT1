#include "AI.h"
#include <vector>

AI::AI()
{
}

AI::~AI()
{

}

Position AI::makeMove(Table &t)
{
    Table newTable;
    int best = INT_MIN, score;
    Position bestPos;
    std::vector<Position> possibleMoves = t.makeAllPossibleMoves();
    for(Position p : possibleMoves)
    {
        newTable = t;
        newTable.makeAIMove(p);
        newTable.nextPlayer();
        newTable.makeProposalFor();
        score = minMaxAB(newTable, t.getMaxDepth(), false, INT_MIN, INT_MAX);
        if(score > best)
        {
            best = score;
            bestPos = p;
        }
    }
    return bestPos;
}

int AI::minMaxAB(Table &t, int depth, bool isMax, int alpha, int beta)
{
    if(!depth || t.isGameOver())
    {
        return t.retScoreDiff();
    }
    if(!t.canPlayerMove())
    {
        return minMaxAB(t, depth-1, !isMax, alpha, beta);
    }
    int best, score;
    Table newTable;
    if(isMax)
    {
        best = INT_MIN;
        std::vector<Position> possibleMoves = t.makeAllPossibleMoves();
        for(Position p : possibleMoves)
        {
            newTable = t;
            newTable.makeAIMove(p);
            newTable.nextPlayer();
            newTable.makeProposalFor();
            score = minMaxAB(newTable, depth-1, !isMax, INT_MIN, INT_MAX);
            if(score > best)
            {
                best = score;
            }
            if(best > alpha)
            {
                alpha = best;
            }
            if(beta <= alpha)
            {
                break;
            }
        }
    }
    else
    {
        best = INT_MAX;
        std::vector<Position> possibleMoves = t.makeAllPossibleMoves();
        for(Position p : possibleMoves)
        {
            newTable = t;
            newTable.makeAIMove(p);
            newTable.nextPlayer();
            newTable.makeProposalFor();
            score = minMaxAB(newTable, depth-1, isMax, INT_MIN, INT_MAX);
            if(score < best)
            {
                best = score;
            }
            if(best < beta)
            {
                beta = best;
            }
            if(beta <= alpha)
            {
                break;
            }
        }
    }
    return best;
}
