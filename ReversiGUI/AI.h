#ifndef AI_H_
#define AI_H_
#include "table.h"
#include "position.h"

class AI{
public:
    AI();
    ~AI();
    Position makeMove(Table &t);
private:
    int minMaxAB(Table &t, int depth, bool isMax, int alpha, int beta);
};


#endif // AI_H_
