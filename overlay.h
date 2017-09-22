#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
#include <QPainter>
#include <QDebug>


class Overlay : public QWidget
{
    Q_OBJECT
public:
    explicit Overlay(QWidget *parent = 0);
    void SetColor(QColor _color);
private:
    QColor color;
    void paintEvent(QPaintEvent *event);
};

#endif // OVERLAY_H
