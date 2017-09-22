#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWidget>
#include <QList>
#include <QPoint>
#include "board.h"
#include <QApplication>
#include <QDesktopWidget>
#include "overlay.h"
#include "movefactory.h"
#include "alphabeta.h"
#include <QMessageBox>

class Game : public QWidget
{
    Q_OBJECT
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    Board* board;
    Tile* selectedTile;
    Overlay* overlay = NULL;
    QList<Tile*> allowedMoves;
    Tile* tempTile;
    QList<Overlay*> overlayList;
    bool leftCastle;
    bool Castling();
    void mousePressEvent(QMouseEvent* event);
    Tile *FindTile(QPoint point);
    void FindMoves(QPoint point);
    void CastleMove();
    void DrawOverlay(QColor color, int x, int y);
    void TurnOffOverlays();
    void MovePiece(Tile *currentTile, Tile *targetTile);
    void DoAIMove(Move* move);
    Piece::playerColor playerTurn = Piece::WHITE;
    AlphaBeta* alphaBeta;
    void AICastle(Tile *firstPosition, Tile *targetPosition);
    bool kingDead = false;
    void Winner(Piece::playerColor player);

public:
    Game();
    ~Game();
};

#endif // GAME_H
