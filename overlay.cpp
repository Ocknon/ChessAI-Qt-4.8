#include "overlay.h"

Overlay::Overlay(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void Overlay::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), color);
}

void Overlay::SetColor(QColor _color)
{
    color = _color;
}
