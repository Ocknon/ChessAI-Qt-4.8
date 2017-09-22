#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "piece.h"

class Tile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tile(int _x, int _y);
    ~Tile();
    Piece* currentPiece = NULL;
    Piece::pieceType type = Piece::ERROR;
    Piece::playerColor pieceColor = Piece::UNKNOWN;

    void SwapPieces(Piece* newPiece);
    void SwapFakePieces(Piece* newPiece);
    int XPos();
    int YPos();

private:
    void GetStartingPiece();
    void GetUniqueRow(Piece::playerColor color);
    int x;
    int y;
signals:

public slots:
};

#endif // TILE_H
