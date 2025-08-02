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

void ScriptCanvas::drawPolygon(const QVariantList &points) {
    if (points.size() >= 6 && points.size() % 2 == 0) {
        QPainterPath path;
        path.moveTo(points[0].toInt(), points[1].toInt());

        for (int var = 2; var < points.size(); var += 2) {
            path.lineTo(points[i].toInt(), points[i + 1].toInt());
        }

        path.closeSubpath();
        shapes.append();
        update();
    }
}
