#include "tile.h"

Tile::Tile(int _x, int _y)
{
    x = _x;
    y = _y;
    GetStartingPiece();
    this->setPos(x * 100 + 20, y * 100 + 20);
}

Tile::~Tile()
{

}

void Tile::SwapPieces(Piece *newPiece)
{
    currentPiece = newPiece;
    this->setPixmap(QPixmap(currentPiece->GetImage()));
    currentPiece->hasMoved = true;
    this->type = currentPiece->type;
    this->pieceColor = currentPiece->player;
}

void Tile::SwapFakePieces(Piece *newPiece)
{
    currentPiece = newPiece;
    currentPiece->hasMoved = newPiece->hasMoved;
    this->type = currentPiece->type;
    this->pieceColor = currentPiece->player;
}

void Tile::GetStartingPiece()
{
    if (y == 1)
    {
        pieceColor = Piece::BLACK;
        type = Piece::PAWN;
        currentPiece = new Piece(type, pieceColor);
        this->setPixmap(QPixmap(currentPiece->GetImage()));
    }
    else if (y == 6)
    {
        pieceColor = Piece::WHITE;
        type = Piece::PAWN;
        currentPiece = new Piece(type, pieceColor);
        this->setPixmap(QPixmap(currentPiece->GetImage()));
    }
    else if (y == 0)
    {
        pieceColor = Piece::BLACK;
        GetUniqueRow(Piece::BLACK);
    }
    else if (y == 7)
    {
        pieceColor = Piece::WHITE;
        GetUniqueRow(Piece::WHITE);
    }
}

void Tile::GetUniqueRow(Piece::playerColor color)
{
    if(x == 0 || x == 7)
    {
        type = Piece::ROOK;
        currentPiece = new Piece(Piece::ROOK, color);
        this->setPixmap(QPixmap(currentPiece->GetImage()));
    }
    else if (x == 1 || x == 6)
    {
        type = Piece::KNIGHT;
        currentPiece = new Piece(Piece::KNIGHT, color);
        this->setPixmap(QPixmap(currentPiece->GetImage()));
    }
    else if (x == 2 || x == 5)
    {
        type = Piece::BISHOP;
        currentPiece = new Piece(Piece::BISHOP, color);
        this->setPixmap(QPixmap(currentPiece->GetImage()));
    }
    else if (x == 3)
    {
        type = Piece::QUEEN;
        currentPiece = new Piece(Piece::QUEEN, color);
        this->setPixmap(QPixmap(currentPiece->GetImage()));
    }
    else if (x == 4)
    {
        type = Piece::KING;
        currentPiece = new Piece(Piece::KING, color);
        this->setPixmap(QPixmap(currentPiece->GetImage()));
    }
    else
    {
        qDebug() << "ERROR, PIECE NOT RECOGNIZED";
    }
}

int Tile::XPos()
{
    return x;
}

int Tile::YPos()
{
    return y;
}
