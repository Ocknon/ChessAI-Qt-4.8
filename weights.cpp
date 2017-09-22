#include "weights.h"

Weights::Weights()
{

}

int Weights::GetBoardWeight(Piece::pieceType type, QPoint position, Piece::playerColor color)
{
    switch (type)
    {
    case Piece::PAWN:
        if (color == Piece::WHITE)
            return PawnBoardWeight[position.x()][position.y()];
        else
            return PawnMirrorBoardWeight[position.x()][position.y()];
        break;
    case Piece::ROOK:
        if (color == Piece::WHITE)
            return RookBoardWeight[position.x()][position.y()];
        else
            return RookMirrorBoardWeight[position.x()][position.y()];
        break;
    case Piece::KNIGHT:
        if (color == Piece::WHITE)
            return KnightBoardWeight[position.x()][position.y()];
        else
            return KnightMirrorBoardWeight[position.x()][position.y()];
        break;
    case Piece::BISHOP:
        if (color == Piece::WHITE)
            return BishopBoardWeight[position.x()][position.y()];
        else
            return BishopMirrowBoardWeight[position.x()][position.y()];
        break;
    case Piece::QUEEN:
        if (color == Piece::WHITE)
            return QueenBoardWeight[position.x()][position.y()];
        else
            return QueenMirrorBoardWeight[position.x()][position.y()];
        break;
    case Piece::KING:
        if (!endGame)
        {
            if (color == Piece::WHITE)
                return KingBoardWeight[position.x()][position.y()];
            else
                return KingMirrorBoardWeight[position.x()][position.y()];
        }
        else
        {
            if (color == Piece::WHITE)
                return KingEndBoardWeight[position.x()][position.y()];
            else
                return KingEndMirrorBoardWeight[position.x()][position.y()];
        }
        break;
    default:
        break;
    }
}

int Weights::GetPieceWeight(Piece::pieceType type)
{
    switch (type)
    {
    case Piece::PAWN:
        return 1;
        break;
    case Piece::ROOK:
        return 5;
        break;
    case Piece::KNIGHT:
        return 3;
        break;
    case Piece::BISHOP:
        return 3;
        break;
    case Piece::QUEEN:
        return 9;
        break;
    case Piece::KING:
        return 1000000;
        break;
    default:
        break;
    }
}
