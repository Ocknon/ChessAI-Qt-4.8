#include "game.h"

Game::Game()
{
    scene = new QGraphicsScene();

    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    view->setFixedSize(800, 800);
    view->setSceneRect(0, 0, 800, 800);
    view->setBackgroundBrush(QBrush(QImage(":/Board.png")));

    this->grabMouse();

    board = new Board();
    scene->addItem(board);
    board->SetupBoard();

    alphaBeta = new AlphaBeta(board);
}

Game::~Game()
{

}

void Game::mousePressEvent(QMouseEvent *event)
{
    TurnOffOverlays();

    if (kingDead)
    {
        QApplication::quit();
        return;
    }

    QPoint offset;
    offset.setX(8);
    offset.setY(30);
    QPoint mousePosition = event->pos() - view->pos() - offset;
    int x = mousePosition.x() / 100;
    int y = mousePosition.y() / 100;
    QPoint localPoint(x, y);

    if (playerTurn == Piece::BLACK)
    {
        Move* move = alphaBeta->getMove();
        DoAIMove(move);
        playerTurn = Piece::WHITE;
    }
    selectedTile = FindTile(localPoint);
    if(selectedTile->currentPiece && selectedTile->currentPiece->player == playerTurn)
    {
        tempTile = selectedTile;
        FindMoves(localPoint);
    }
    else
    {
        foreach (Tile* tile, allowedMoves)
        {
            if (tile == selectedTile && tempTile && tempTile->currentPiece)
            {
                if (tempTile->currentPiece->type == Piece::KING && Castling())
                {
                    CastleMove();
                }
                else
                {
                    if (selectedTile->currentPiece && selectedTile->currentPiece->type == Piece::KING)
                    {
                        MovePiece(tempTile, selectedTile);
                        Winner(playerTurn);
                    }
                    else if (!kingDead)
                        MovePiece(tempTile, selectedTile);
                    //alphaBeta->GetBoardState();
                }
                if (playerTurn == Piece::WHITE)
                    playerTurn = Piece::BLACK;
                else
                    playerTurn = Piece::WHITE;
            }
        }
        tempTile = NULL;
    }
}

void Game::Winner(Piece::playerColor player)
{
    qDebug() << player;
    kingDead = true;
    QMessageBox box;
    if (player == Piece::WHITE)
        box.setText("WHITE WINS!");
    else
        box.setText("BLACK WINS!");
    box.exec();
}

void Game::DoAIMove(Move *move)
{
    Tile* firstPosition = move->GetFirstPosition();
    Tile* targetPosition = board->GetTileFromBoard(move->GetSecondPosition());

    if (!move->hasMoved && move->GetPieceMoved()->type == Piece::KING)
    {
        if (targetPosition->currentPiece->type == Piece::ROOK && !targetPosition->currentPiece->hasMoved)
        {
            AICastle(firstPosition, targetPosition);
        }
    }
    else
    {
        if (targetPosition->currentPiece && targetPosition->currentPiece->type == Piece::KING)
        {
            MovePiece(firstPosition, targetPosition);
            Winner(playerTurn);
        }
        else
            MovePiece(firstPosition, targetPosition);
    }
}

void Game::AICastle(Tile* firstPosition, Tile* targetPosition)
{
    if(targetPosition->XPos() == 2)
    {
        leftCastle = true;
    }
    else if (targetPosition->XPos() == 6)
    {
        leftCastle = false;
    }

    MovePiece(firstPosition, targetPosition);

    if (leftCastle)
    {
        Tile* temp1 = board->GetTileFromBoard(QPoint(0, selectedTile->YPos()));
        Tile* temp2 = board->GetTileFromBoard(QPoint(selectedTile->XPos() + 1, selectedTile->YPos()));
        MovePiece(temp1, temp2);
    }
    else
    {
        Tile* temp1 = board->GetTileFromBoard(QPoint(7, selectedTile->YPos()));
        Tile* temp2 = board->GetTileFromBoard(QPoint(selectedTile->XPos() - 1, selectedTile->YPos()));
        MovePiece(temp1, temp2);
    }
}

void Game::CastleMove()
{
    MovePiece(tempTile, selectedTile);
    if (leftCastle)
    {
        Tile* temp1 = board->GetTileFromBoard(QPoint(0, selectedTile->YPos()));
        Tile* temp2 = board->GetTileFromBoard(QPoint(selectedTile->XPos() + 1, selectedTile->YPos()));
        MovePiece(temp1, temp2);
    }
    else
    {
        Tile* temp1 = board->GetTileFromBoard(QPoint(7, selectedTile->YPos()));
        Tile* temp2 = board->GetTileFromBoard(QPoint(selectedTile->XPos() - 1, selectedTile->YPos()));
        MovePiece(temp1, temp2);
    }
}

bool Game::Castling()
{
    if (tempTile->pieceColor == playerTurn && !tempTile->currentPiece->hasMoved)
    {
        if(selectedTile->XPos() == 2 && selectedTile->YPos() == 7)
        {
            leftCastle = true;
            return true;
        }
        else if (selectedTile->XPos() == 6 && selectedTile->YPos() == 7)
        {
            leftCastle = false;
            return true;
        }
    }
    else if (!tempTile->currentPiece->hasMoved)
    {
        if(selectedTile->XPos() == 2 && selectedTile->YPos() == 7)
        {
            leftCastle = true;
            return true;
        }
        else if (selectedTile->XPos() == 6 && selectedTile->YPos() == 7)
        {
            leftCastle = false;
            return true;
        }
    }
    return false;
}

void Game::MovePiece(Tile* currentTile, Tile* targetTile)
{
    targetTile->SwapPieces(currentTile->currentPiece);
    currentTile->currentPiece = NULL;
    currentTile->setPixmap(QPixmap());
}

Tile* Game::FindTile(QPoint point)
{
    if (point.x() >= 0 && point.x() < 8 && point.y() >= 0 && point.y() < 8)
        selectedTile = board->GetTileFromBoard(point);

    return selectedTile;
}

void Game::FindMoves(QPoint point)
{
    allowedMoves.clear();

    MoveFactory moveFactory(selectedTile->currentPiece, board);
    QList<QPoint> moves;
    moves = moveFactory.GetMoves(selectedTile->currentPiece->type, selectedTile->currentPiece->player, point);
    foreach (QPoint move, moves)
    {
        Tile* tile = board->GetTileFromBoard(move);
        allowedMoves.append(tile);

        if (tile->currentPiece)
        {
            DrawOverlay(QColor(180, 43, 43, 128), tile->pos().x() - 19, tile->pos().y() - 19);
        }
        else
        {
            DrawOverlay(QColor(80, 80, 255, 128), tile->pos().x() - 19, tile->pos().y() - 19);
        }
    }
    DrawOverlay(QColor(172, 184, 5, 128), selectedTile->pos().x() - 19, selectedTile->pos().y() - 19);
}

void Game::DrawOverlay(QColor color, int x, int y)
{
    overlay = new Overlay(view);
    overlayList.append(overlay);
    overlay->setGeometry(x, y, 100, 100);
    overlay->SetColor(color);
    overlay->show();
}

void Game::TurnOffOverlays()
{
    foreach (Overlay* o, overlayList)
    {
        o->hide();
        o->deleteLater();
    }
    overlayList.clear();
}
