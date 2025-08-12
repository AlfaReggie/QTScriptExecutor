#include "scriptcanvaswidget.h"
#include <QPainter>
#include <QDebug>

ScriptCanvasWidget::ScriptCanvasWidget(QWidget *parent) : QWidget(parent), penColor(Qt::black), brushColor(Qt::white), penWidth(1) {
    setMinimumSize(800, 600);
}

void ScriptCanvasWidget::clear() {
    shapes.clear();
    update();
}

void ScriptCanvasWidget::setBrushColor(int r, int g, int b, int a) {
    brushColor = QColor(r, g, b, a);
}

void ScriptCanvasWidget::setPenColor(int r, int g, int b, int a) {
    penColor = QColor(r, g, b, a);
}

void ScriptCanvasWidget::setPenWidth(int width) {
    penWidth = width;
}

void ScriptCanvasWidget::drawFilledCircle(int x, int y, int radius) {
    QPainterPath path;
    path.addEllipse(x - radius, y - radius, radius * 2, radius * 2);
    shapes.append(path);
    update();
}

void ScriptCanvasWidget::drawCircle(int x, int y, int radius) {
    QPainterPath path;
    path.addEllipse(x - radius, y - radius, radius * 2, radius * 2);
    shapes.append(path);
    update();
}

void ScriptCanvasWidget::drawRect(int x, int y, int width, int height) {
    QPainterPath path;
    path.addRect(x, y, width, height);
    shapes.append(path);
    update();
}

void ScriptCanvasWidget::drawPolygon(const QVariantList &points) {
    if (points.size() >= 6 && points.size() % 2 == 0) {
        QPainterPath path;
        path.moveTo(points[0].toInt(), points[1].toInt());

        for (int i = 2; i < points.size(); i += 2) {
            path.lineTo(points[i].toInt(), points[i + 1].toInt());
        }

        path.closeSubpath();
        shapes.append(path);
        update();
    }
}

void ScriptCanvasWidget::drawLine(int x1, int y1, int x2, int y2) {
    QPainterPath path;
    path.moveTo(x1, y1);
    path.lineTo(x2, y2);
    shapes.append(path);
    update();
}

void ScriptCanvasWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);

    for (const QPainterPath &path : qAsConst(shapes)) {
        painter.setPen(QPen(penColor, penWidth));
        painter.setBrush(brushColor);
        painter.drawPath(path);
    }
}
