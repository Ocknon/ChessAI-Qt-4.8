#ifndef MOVEFACTORY_H
#define MOVEFACTORY_H

#include <QObject>
#include <QList>
#include <QPoint>
#include "tile.h"
#include "board.h"
#include "piece.h"

class MoveFactory : public QObject
{
    Q_OBJECT
private:
    QList<QPoint> moves;
    Board* board;
    int xPos;
    int yPos;
    Piece::playerColor player;
    Piece* currentPiece;

    bool IsOnBoard(QPoint point);
    bool ContainsPiece(QPoint point);
    void CheckAndStoreMove(QPoint point);
    void ResetMove(QPoint* point);
    void GenerateLongMove(int limit, QPoint direction);
    bool IsEnemy(QPoint point);
    void Castle();
    void GetPawnMoves();
    void GetRookMoves();
    void GetKnightMoves();
    void GetBishopMoves();
    void GetKingMoves();

public:
    MoveFactory(Piece* piece, Board* _board);
    ~MoveFactory();
    QList<QPoint> GetMoves(Piece::pieceType _type, Piece::playerColor _player, QPoint point);

signals:

public slots:
};

#endif // MOVEFACTORY_H
