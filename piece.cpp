#include "piece.h"

Piece::Piece(pieceType _type, playerColor _player)
{
    type = _type;
    player = _player;
    SetupPiece();
}

Piece::~Piece()
{

}

void Piece::SetupPiece()
{
    switch (type)
    {
    case pieceType::PAWN:
        imageAddress = player == playerColor::BLACK ? ":/BlackPawn.png" : ":/WhitePawn.png";
        break;
    case pieceType::ROOK:
        imageAddress = player == playerColor::BLACK ? ":/BlackRook.png" : ":/WhiteRook.png";
        break;
    case pieceType::KNIGHT:
        imageAddress = player == playerColor::BLACK ? ":/BlackKnight.png" : ":/WhiteKnight.png";
        break;
    case pieceType::BISHOP:
        imageAddress = player == playerColor::BLACK ? ":/BlackBishop.png" : ":/WhiteBishop.png";
        break;
    case pieceType::QUEEN:
        imageAddress = player == playerColor::BLACK ? ":/BlackQueen.png" : ":/WhiteQueen.png";
        break;
    case pieceType::KING:
        imageAddress = player == playerColor::BLACK ? ":/BlackKing.png" : ":/WhiteKing.png";
        break;
    default:
        qDebug() << "Unknown Case Entered!";
        break;
    }
}

QString Piece::GetImage()
{
    return imageAddress;
}
