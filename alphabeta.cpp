#include "alphabeta.h"

AlphaBeta::AlphaBeta(Board *mainBoard)
{
    b = mainBoard;
}

Move* AlphaBeta::getMove()
{
    bestMove = CreateMove(b->GetTileFromBoard(QPoint(0, 0)), QPoint(0, 0), Piece::BLACK, Piece::WHITE);
    AB(maxDepth, -100000000, 1000000000, true);
    return bestMove;
}


int AlphaBeta::AB(int depth, int alpha, int beta, bool blackPlayer)
{
    GetBoardState();

    if (depth == 0)
    {
        return Evaluate();
    }
    if(blackPlayer)
    {
        int score = -10000000;
        QList<Move*> allMoves = GetMoves(Piece::BLACK);
        foreach (Move* move, allMoves)
        {
            moveStack.append(move);

            DoFakeMove(move->GetFirstPosition(), b->GetTileFromBoard(move->GetSecondPosition()));

            score = AB(depth - 1, alpha, beta, false);

            UndoFakeMove();

            if (score > alpha)
            {
                move->score = score;
                if (move->score > bestMove->score && depth == maxDepth)
                {
                    bestMove = move;
                }
                alpha = score;
            }
            if (score >= beta)
            {
                break;
            }
        }
        return alpha;
    }
    else
    {
        int score = 10000000;
        QList<Move*> allMoves = GetMoves(Piece::WHITE);
        foreach (Move* move, allMoves)
        {
            moveStack.append(move);

            DoFakeMove(move->GetFirstPosition(), b->GetTileFromBoard(move->GetSecondPosition()));

            score = AB(depth - 1, alpha, beta, true);

            UndoFakeMove();

            if (score < beta)
            {
                move->score = score;
                beta = score;
            }
            if (score <= alpha)
                break;
        }
        return beta;
    }
}

QList<Move*> AlphaBeta::GetMoves(Piece::playerColor color)
{
    QList<Move*> turnMove;
    QList<Tile*> pieces;

    if (color == Piece::BLACK)
        pieces = blackPieces;
    else
        pieces = whitePieces;

    foreach (Tile* tile, pieces)
    {
        MoveFactory factory(tile->currentPiece, b);
        QList<QPoint> pieceMoves = factory.GetMoves(tile->currentPiece->type, color, QPoint(tile->XPos(), tile->YPos()));

        foreach (QPoint move, pieceMoves)
        {
            if (color == Piece::WHITE)
                newMove = CreateMove(tile, move, color, Piece::BLACK);
            else
                newMove = CreateMove(tile, move, color, Piece::WHITE);

            turnMove.append(newMove);
        }

    }
    return turnMove;
}

Move* AlphaBeta::CreateMove(Tile *tile, QPoint move, Piece::playerColor color, Piece::playerColor killedColor)
{
    Move* tempMove = new Move();
    tempMove->SetFirstPosition(tile);
    tempMove->SetPieceMoved(tile->currentPiece);
    tempMove->SetSecondPosition(move);
    tempMove->SetPlayerColor(color);
    tempMove->hasMoved = tile->currentPiece->hasMoved;

    if (b->GetTileFromBoard(move)->currentPiece)
    {
        tempMove->SetPlayerKilledColor(killedColor);
        tempMove->SetPieceKilled(b->GetTileFromBoard(move)->currentPiece->type);
        tempMove->killedHasMoved = b->GetTileFromBoard(move)->currentPiece->hasMoved;
    }

    return tempMove;
}

int AlphaBeta::Evaluate()
{
    float pieceDifference = 0;
    float whiteWeight = 0;
    float blackWeight = 0;
    foreach (Tile* tile, whitePieces)
    {
        whiteWeight += weight.GetBoardWeight(tile->currentPiece->type, QPoint(tile->YPos(), tile->XPos()), Piece::WHITE);
    }
    foreach (Tile* tile, blackPieces)
    {
        blackWeight += weight.GetBoardWeight(tile->currentPiece->type, QPoint(tile->YPos(), tile->XPos()), Piece::BLACK);
    }
    pieceDifference = (blackScore + (blackWeight/100)) - (whiteScore + (whiteWeight/100));

    return pieceDifference * 100;
}

void AlphaBeta::GetBoardState()
{
    blackPieces.clear();
    whitePieces.clear();
    whiteScore = 0;
    blackScore = 0;
    tilesWithPieces.clear();

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            localBoard[x][y] = b->board[x][y];
            if (localBoard[x][y]->currentPiece != NULL && localBoard[x][y]->currentPiece->type != Piece::ERROR)
            {
                tilesWithPieces.append(localBoard[x][y]);
            }
        }
    }
    foreach (Tile* tile, tilesWithPieces)
    {
        if (tile->currentPiece->player == Piece::BLACK)
        {
            blackScore += weight.GetPieceWeight(tile->currentPiece->type);
            blackPieces.append(tile);
        }
        else
        {
            whiteScore += weight.GetPieceWeight(tile->currentPiece->type);
            whitePieces.append(tile);
        }
    }
    //DebugBoardState();
}

void AlphaBeta::UndoFakeMove()
{
    Move* tempMove = moveStack.pop();
    QPoint movedTo = tempMove->GetSecondPosition();
    Tile* movedFrom = tempMove->GetFirstPosition();
    Piece::pieceType pieceKilled = tempMove->GetPieceKilled();
    Piece* pieceMoved = tempMove->GetPieceMoved();
    Piece::playerColor color = tempMove->GetPlayerColor();
    Piece::playerColor killedColor = tempMove->GetKilledPlayerColor();

    movedFrom->currentPiece = new Piece(pieceMoved->type, color);
    movedFrom->currentPiece->hasMoved = tempMove->hasMoved;

    Tile* temp = b->GetTileFromBoard(movedTo);
    if (pieceKilled != Piece::ERROR)
    {
        temp->currentPiece = new Piece(pieceKilled, killedColor);
        temp->currentPiece->hasMoved = tempMove->killedHasMoved;
    }
    else
    {
        temp->type = Piece::ERROR;
        temp->pieceColor = Piece::UNKNOWN;
        temp->currentPiece = NULL;
    }
}

void AlphaBeta::DoFakeMove(Tile* currentTile, Tile* targetTile)
{
    targetTile->SwapFakePieces(currentTile->currentPiece);
    currentTile->currentPiece = NULL;
    currentTile->pieceColor = Piece::UNKNOWN;
    currentTile->type = Piece::ERROR;
}

void AlphaBeta::DebugBoardState()
{
    QString string;
    qDebug() << "   A B C D E F G H";
    qDebug() << "                  ";
    for (int y = 0; y < 8; y++)
    {
        string = QString::number(y) + "  ";
        for (int x = 0; x < 8; x++)
        {
            if (localBoard[x][y]->currentPiece != NULL)
            {
                switch (localBoard[x][y]->currentPiece->type) {
                case Piece::PAWN:
                    string += "P ";
                    break;
                case Piece::ROOK:
                    string += "R ";
                    break;
                case Piece::KNIGHT:
                    string += "k ";
                    break;
                case Piece::BISHOP:
                    string += "B ";
                    break;
                case Piece::QUEEN:
                    string += "Q ";
                    break;
                case Piece::KING:
                    string += "K ";
                    break;
                default:
                    break;
                }
            }
            else
                string += ". ";
        }
        qDebug().noquote() << string;
    }
}
