#include "board.h"

Board::Board()
{

}

Board::~Board()
{

}

void Board::SetupBoard()
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            board[x][y] = new Tile(x, y);
            scene()->addItem(board[x][y]);
        }
    }
}

Tile* Board::GetTileFromBoard(QPoint point)
{
    return board[point.x()][point.y()];
}

Piece::pieceType Board::GetPieceFromBoard(QPoint point)
{
    return board[point.x()][point.y()]->currentPiece->type;
}
