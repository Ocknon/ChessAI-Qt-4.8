#ifndef ALPHABETA_H
#define ALPHABETA_H

#include <QPoint>
#include <QList>
#include "move.h"
#include "board.h"
#include "weights.h"
#include "movefactory.h"
#include <QStack>

class AlphaBeta
{
private:
    QList<Move*> moves;
    QList<Tile*> tilesWithPieces;
    QList<Tile*> blackPieces;
    QList<Tile*> whitePieces;
    QList<Move*> firstMoves;
    Move* bestMove;
    Move* worstMove;
    int maxDepth = 4;

    QList<Tile*> boardState;
    int AB(int depth, int alpha, int beta, bool blackPlayer);
    int blackScore = 0;
    int whiteScore = 0;

    Tile* localBoard[8][8];
    Move* newMove;
    Board* b;
    Weights weight;
    QStack<Move*> moveStack;

    void DoFakeMove(Tile *currentTile, Tile *targetTile);
    void UndoFakeMove();
    int Evaluate();

    Move* CreateMove(Tile* tile, QPoint move, Piece::playerColor color, Piece::playerColor killedColor);
    QList<Move *> GetMoves(Piece::playerColor color);
public:
    AlphaBeta(Board* mainBoard);
    void GetBoardState();
    void DebugBoardState();
    Move *getMove();
};

#endif // ALPHABETA_H
