#include "movefactory.h"

MoveFactory::MoveFactory(Piece* piece, Board *_board)
{
    currentPiece = piece;
    board = _board;
}

MoveFactory::~MoveFactory()
{

}

QList<QPoint> MoveFactory::GetMoves(Piece::pieceType type, Piece::playerColor _player, QPoint point)
{
    player = _player;
    xPos = point.x();
    yPos = point.y();
    switch (type)
    {
    case Piece::PAWN:
        GetPawnMoves();
        break;
    case Piece::ROOK:
        GetRookMoves();
        break;
    case Piece::KNIGHT:
        GetKnightMoves();
        break;
    case Piece::BISHOP:
        GetBishopMoves();
        break;
    case Piece::QUEEN:
        GetRookMoves();
        GetBishopMoves();
        break;
    case Piece::KING:
        GetKingMoves();
        break;
    default:
        break;
    }
    return moves;
}

void MoveFactory::GetPawnMoves()
{
    if (player == Piece::BLACK)
    {
        int limit = currentPiece->hasMoved ? 2 : 3;
        GenerateLongMove(limit, QPoint(0, 1));

        QPoint diagLeft = QPoint(xPos - 1, yPos + 1);
        QPoint diagRight = QPoint(xPos + 1, yPos + 1);

        if (ContainsPiece(diagLeft) && IsEnemy(diagLeft))
            CheckAndStoreMove(diagLeft);
        if (ContainsPiece(diagRight) && IsEnemy(diagRight))
            CheckAndStoreMove(diagRight);
    }
    else if (player == Piece::WHITE)
    {
        int limit = currentPiece->hasMoved ? 2 : 3;
        GenerateLongMove(limit, QPoint(0, -1));

        QPoint diagLeft = QPoint(xPos - 1, yPos - 1);
        QPoint diagRight = QPoint(xPos + 1, yPos - 1);

        if (ContainsPiece(diagLeft) && IsEnemy(diagLeft))
            CheckAndStoreMove(diagLeft);
        if (ContainsPiece(diagRight) && IsEnemy(diagRight))
            CheckAndStoreMove(diagRight);
    }
}

void MoveFactory::GetRookMoves()
{
    GenerateLongMove(9, QPoint(0, 1));
    GenerateLongMove(9, QPoint(0, -1));
    GenerateLongMove(9, QPoint(1, 0));
    GenerateLongMove(9, QPoint(-1, 0));
}

void MoveFactory::GetKnightMoves()
{
    QPoint move;
    move = QPoint(xPos + 2, yPos + 1);
    CheckAndStoreMove(move);
    move = QPoint(xPos + 2, yPos - 1);
    CheckAndStoreMove(move);
    move = QPoint(xPos - 2, yPos + 1);
    CheckAndStoreMove(move);
    move = QPoint(xPos - 2, yPos - 1);
    CheckAndStoreMove(move);

    move = QPoint(xPos + 1, yPos + 2);
    CheckAndStoreMove(move);
    move = QPoint(xPos + 1, yPos - 2);
    CheckAndStoreMove(move);
    move = QPoint(xPos - 1, yPos + 2);
    CheckAndStoreMove(move);
    move = QPoint(xPos - 1, yPos - 2);
    CheckAndStoreMove(move);
}

void MoveFactory::GetBishopMoves()
{
    GenerateLongMove(9, QPoint(1, 1));
    GenerateLongMove(9, QPoint(-1, -1));
    GenerateLongMove(9, QPoint(1, -1));
    GenerateLongMove(9, QPoint(-1, 1));
}

void MoveFactory::GetKingMoves()
{
    Castle();
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
                continue;

            CheckAndStoreMove(QPoint(xPos + x, yPos + y));
        }
    }
}

void MoveFactory::Castle()
{
    if(currentPiece->player == Piece::WHITE)
    {
        bool failed;
        Tile* leftRook = board->GetTileFromBoard(QPoint(0, 7));
        Tile* rightRook = board->GetTileFromBoard(QPoint(7, 7));
        if (leftRook->currentPiece && !leftRook->currentPiece->hasMoved && !currentPiece->hasMoved)
        {
            for (int i = 0; i < 3; i++)
            {
                if(board->GetTileFromBoard(QPoint(i + 1, 7))->currentPiece != NULL)
                    failed = true;
            }
            if (!failed)
            {
                moves.append(QPoint(2, 7));
            }
        }
        failed = false;
        if(rightRook->currentPiece && !rightRook->currentPiece->hasMoved && !currentPiece->hasMoved)
        {
            for (int i = 0; i < 2; i++)
            {
                if(board->GetTileFromBoard(QPoint(i + 5, 7))->currentPiece != NULL)
                    failed = true;
            }
            if (!failed)
            {
                moves.append(QPoint(6, 7));
            }
        }
    }
    else
    {
        bool failed;
        Tile* leftRook = board->GetTileFromBoard(QPoint(0, 0));
        Tile* rightRook = board->GetTileFromBoard(QPoint(7, 0));
        if (leftRook->currentPiece && !leftRook->currentPiece->hasMoved && !currentPiece->hasMoved)
        {
            for (int i = 0; i < 3; i++)
            {
                if(board->GetTileFromBoard(QPoint(i + 1, 0))->currentPiece != NULL)
                    failed = true;
            }
            if (!failed)
            {
                moves.append(QPoint(2, 0));
            }
        }
        failed = false;
        if(rightRook->currentPiece && !rightRook->currentPiece->hasMoved && !currentPiece->hasMoved)
        {
            for (int i = 0; i < 2; i++)
            {
                if(board->GetTileFromBoard(QPoint(i + 5, 0))->currentPiece != NULL)
                    failed = true;
            }
            if (!failed)
            {
                moves.append(QPoint(6, 0));
            }
        }
    }
}

void MoveFactory::GenerateLongMove(int limit, QPoint direction)
{
    QPoint move;
    for (int i = 1; i < limit; i++)
    {
        ResetMove(&move);
        move += direction * i;
        if (ContainsPiece(move))
        {
            if(IsEnemy(move) && currentPiece->type != Piece::PAWN)
            {
                CheckAndStoreMove(move);
            }
            break;
        }
        CheckAndStoreMove(move);
    }
}

bool MoveFactory::IsEnemy(QPoint point)
{
    Tile* tile = board->GetTileFromBoard(point);
    if(player != tile->currentPiece->player)
    {
        return true;
    }
    return false;
}

void MoveFactory::CheckAndStoreMove(QPoint point)
{
    if (IsOnBoard(point) && (!ContainsPiece(point) || IsEnemy(point)))
    {
        moves.append(point);
    }
}

bool MoveFactory::IsOnBoard(QPoint point)
{
    if (point.x() >= 0 && point.y() >= 0 && point.x() < 8 && point.y() < 8)
        return true;
    else
        return false;
}

bool MoveFactory::ContainsPiece(QPoint point)
{
    if (!IsOnBoard(point))
        return false;
    Tile* tile = board->GetTileFromBoard(point);
    if (tile->currentPiece)
        return true;
    else
        return false;
}

void MoveFactory::ResetMove(QPoint* move)
{
    move->setX(xPos);
    move->setY(yPos);
}
