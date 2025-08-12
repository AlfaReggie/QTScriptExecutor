#ifndef SCRIPTCANVASWIDGET_H
#define SCRIPTCANVASWIDGET_H

#include <QWidget>
#include <QPainterPath>
#include <QVector>
#include <QColor>
#include <QVariantList>


class ScriptCanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptCanvasWidget(QWidget *parent = nullptr);

    Q_INVOKABLE void clear();
    Q_INVOKABLE void setBrushColor(int r, int g, int b, int a = 255);
    Q_INVOKABLE void setPenColor(int r, int g, int b, int a = 255);
    Q_INVOKABLE void setPenWidth(int width);
    Q_INVOKABLE void drawFilledCircle(int x, int y, int radius);
    Q_INVOKABLE void drawCircle(int x, int y, int radius);
    Q_INVOKABLE void drawRect(int x, int y, int width, int height);
    Q_INVOKABLE void drawPolygon(const QVariantList &points);
    Q_INVOKABLE void drawLine(int x1, int y1, int x2, int y2);

protected:

    void paintEvent(QPaintEvent *event) override;

private:
    QColor penColor;
    QColor brushColor;
    int penWidth;
    QVector<QPainterPath> shapes;
};

#endif
