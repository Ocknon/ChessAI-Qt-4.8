#ifndef MOVE_H
#define MOVE_H

#include "piece.h"
#include "tile.h"
#include <QPoint>
class Move
{
private:
    Tile* firstPosition;
    QPoint secondPosition;
    Piece* pieceMoved;
    Piece::pieceType pieceKilled = Piece::ERROR;
    Piece::playerColor killedColor;
    Piece::playerColor player;

public:
    Move();
    int score = -100000000;
    bool hasMoved = false;
    bool killedHasMoved = false;
    Tile* GetFirstPosition() { return firstPosition; }
    void SetFirstPosition(Tile* move) { firstPosition = move; }
    QPoint GetSecondPosition() { return secondPosition; }
    void SetSecondPosition(QPoint move) { secondPosition = move; }
    Piece* GetPieceMoved() { return pieceMoved; }
    void SetPieceMoved(Piece* type) { pieceMoved = type; }
    Piece::pieceType GetPieceKilled() { return pieceKilled; }
    void SetPieceKilled(Piece::pieceType type) { pieceKilled = type; }
    Piece::playerColor GetPlayerColor() { return player; }
    void SetPlayerColor(Piece::playerColor color) { player = color; }
    Piece::playerColor GetKilledPlayerColor() { return killedColor; }
    void SetPlayerKilledColor(Piece::playerColor color) { killedColor = color; }

    QString ToString();

};

#endif // MOVE_H
