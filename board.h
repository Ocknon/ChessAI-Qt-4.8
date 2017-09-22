#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QGraphicsScene>
#include "tile.h"
#include <QWidget>

class Board : public QWidget, public QGraphicsPixmapItem
{
    Q_OBJECT
private:


public:
    Tile* board[8][8];
    Board();
    ~Board();
    void SetupBoard();
    Tile* GetTileFromBoard(QPoint point);
    Piece::pieceType GetPieceFromBoard(QPoint point);
};

#endif // BOARD_H
