#ifndef SCRIPTCANVAS_H
#define SCRIPTCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QVector>
#include <QColor>

class ScriptCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptCanvas(int width = 800, int height = 600, QWidget *parent = nullptr);

    Q_INVOKABLE void setBrushColor();
};

#endif // SCRIPTCANVAS_H
