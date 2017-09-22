#include "move.h"

Move::Move()
{

}

QString Move::ToString()
{
    QString pieceType;
    switch (pieceMoved->type)
    {
    case Piece::PAWN:
        pieceType = "Pawn";
        break;
    case Piece::ROOK:
        pieceType = "Rook";
        break;
    case Piece::KNIGHT:
        pieceType = "Knight";
        break;
    case Piece::BISHOP:
        pieceType = "Bishop";
        break;
    case Piece::QUEEN:
        pieceType = "Queen";
        break;
    case Piece::KING:
        pieceType = "King";
        break;
    default:
        break;
    }

    QString currentPlayer;
    switch (player)
    {
    case Piece::BLACK:
        currentPlayer = "Black";
        break;
    case Piece::WHITE:
        currentPlayer = "White";
        break;
    }
    QString start;
    QString temp;
    switch (firstPosition->XPos())
    {
    case 0:
        temp = "A";
        break;
    case 1:
        temp = "B";
        break;
    case 2:
        temp = "C";
        break;
    case 3:
        temp = "D";
        break;
    case 4:
        temp = "E";
        break;
    case 5:
        temp = "F";
        break;
    case 6:
        temp = "G";
        break;
    case 7:
        temp = "H";
        break;
    default:
        break;
    }

    start = temp + " " + QString::number(firstPosition->YPos());

    QString temp2;
    switch (secondPosition.x())
    {
    case 0:
        temp2 = "A";
        break;
    case 1:
        temp2 = "B";
        break;
    case 2:
        temp2 = "C";
        break;
    case 3:
        temp2 = "D";
        break;
    case 4:
        temp2 = "E";
        break;
    case 5:
        temp2 = "F";
        break;
    case 6:
        temp2 = "G";
        break;
    case 7:
        temp2 = "H";
        break;
    default:
        break;
    }


    QString end;
    end = temp2 + " " + QString::number(secondPosition.y());
    return currentPlayer + " " + pieceType + ": " + start + " to " + end + " score: " + QString::number(score);
}
