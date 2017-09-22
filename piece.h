#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QDebug>

class Piece : public QObject
{
    Q_OBJECT


public:
    enum pieceType { KING, QUEEN, BISHOP, ROOK, KNIGHT, PAWN, ERROR = -1 };
    enum playerColor { BLACK, WHITE, UNKNOWN = -1 };

    Piece(pieceType _type, playerColor _player);
    ~Piece();

    bool hasMoved = false;

    QString GetImage();

    pieceType type;
    playerColor player;

private:
    void SetupPiece();
    QString imageAddress;

signals:

public slots:
};

#endif // PIECE_H
