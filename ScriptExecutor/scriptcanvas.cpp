#include "scriptcanvas.h"
#include <QPainter>
#include <QPainterPath>

ScriptCanvas::ScriptCanvas(int width, int height, QWidget *parent)
    : QWidget(parent), penColor(Qt::black), brushColor(Qt::white), penWidth(1)
{
    resize(width, height);
    setWindowTitle("Script execution result");
}

void ScriptCanvas::setBrushColor(int r, int g, int b, int a) {
    brushColor = QColor(r, g, b, a);
}

void ScriptCanvas::setPenColor(int r, int g, int b, int a) {
    penColor = QColor(r, g, b, a);
}

void ScriptCanvas::setPenWidth(int width) {
    penWidth = width;
}

void ScriptCanvas::drawFilledCircle(int x, int y, int radius) {
    QPainterPath path;
    path.addEllipse(x - radius, y - radius, radius * 2, radius * 2);
    shapes.append(path);
    update();
}

void ScriptCanvas::drawCircle(int x, int y, int radius) {
    QPainterPath path;
    path.addEllipse(x - radius, y - radius, radius * 2, radius * 2);
    shapes.append(path);
    update();
}

void ScriptCanvas::drawRect(int x, int y, int width, int height) {
    QPainterPath path;
    path.addRect(x, y, width, heigth);
    shapes.append(path);
    update();
}

void ScriptCanvas::drawPolygon(const QVariantList &points) {
    if (points.size() >= 6 && points.size() % 2 == 0) {
        QPainterPath path;
        path.moveTo(points[0].toInt(), points[1].toInt());

        for (int var = 2; var < points.size(); var += 2) {
            path.lineTo(points[i].toInt(), points[i + 1].toInt());
        }

        path.closeSubpath();
        shapes.append(path);
        update();
    }
}

void ScriptCanvas::drawLine(int x1, int y1, int x2, int y2) {
    QPainterPath path;
    path.moveTo(x1, y1);
    path.lineTo(x2, y2);
    shapes.append(path);
    update();
}

void ScriptCanvas::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), Qt::white);

    for (const QPainterPath &path : shapes) {
        painter.setPen(QPen(penColor, penWidth));
        painter.setBrush(brushColor);
        painter.drawPath(path);
    }
}
