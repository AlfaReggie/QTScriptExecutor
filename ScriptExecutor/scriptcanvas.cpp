#include "scriptcanvas.h"
#include <QPainter>
#include <QDebug>
#include <QDateTime>

ScriptCanvas::ScriptCanvas(int width, int height, QWidget *parent) : QWidget(parent), penColor(Qt::black), brushColor(Qt::white), penWidth(1) {
    resize(width, height);
    setWindowTitle("Результат выполнения скрипта");
    setAttribute(Qt::WA_DeleteOnClose, false);
    qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] Canvas создан с размерами:" << width << "x" << height;
}

void ScriptCanvas::clear() {
    shapes.clear();
    update();
    qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] Canvas очищен";
}

void ScriptCanvas::setBrushColor(int r, int g, int b, int a) {
    brushColor = QColor(r, g, b, a);
    qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] Установлен цвет заливки:" << r << g << b << a;
}

void ScriptCanvas::setPenColor(int r, int g, int b, int a) {
    penColor = QColor(r, g, b, a);
    qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] Установлен цвет пера:" << r << g << b << a;
}

void ScriptCanvas::setPenWidth(int width) {
    penWidth = width;
    qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] Установлена толщина пера:" << width;
}

void ScriptCanvas::drawFilledCircle(int x, int y, int radius) {
    QPainterPath path;
    path.addEllipse(x - radius, y - radius, radius * 2, radius * 2);
    shapes.append(path);
    qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] Добавлен залитый круг:" << x << y << radius;
    update();
}

void ScriptCanvas::drawCircle(int x, int y, int radius) {
    QPainterPath path;
    path.addEllipse(x - radius, y - radius, radius * 2, radius * 2);
    shapes.append(path);
    qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] Добавлен круг:" << x << y << radius;
    update();
}

void ScriptCanvas::drawRect(int x, int y, int width, int height) {
    QPainterPath path;
    path.addRect(x, y, width, height);
    shapes.append(path);
    qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] Добавлен прямоугольник:" << x << y << width << height;
    update();
}

void ScriptCanvas::drawPolygon(const QVariantList &points) {
    if (points.size() >= 6 && points.size() % 2 == 0) {
        QPainterPath path;
        path.moveTo(points[0].toInt(), points[1].toInt());

        for (int i = 2; i < points.size(); i += 2) {
            path.lineTo(points[i].toInt(), points[i + 1].toInt());
        }

        path.closeSubpath();
        shapes.append(path);
        qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] Добавлен полигон с точками:" << points;
        update();
    }
}

void ScriptCanvas::drawLine(int x1, int y1, int x2, int y2) {
    QPainterPath path;
    path.moveTo(x1, y1);
    path.lineTo(x2, y2);
    shapes.append(path);
    qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] Добавлена линия:" << x1 << y1 << "до" << x2 << y2;
    update();
}

void ScriptCanvas::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);
    qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] paintEvent: Начало отрисовки. Количество фигур:" << shapes.size();

    if (shapes.isEmpty()) {
        qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] paintEvent: Нет фигур для отрисовки.";
        return;
    }

    for (const QPainterPath &path : qAsConst(shapes)) {
        painter.setPen(QPen(penColor, penWidth));
        painter.setBrush(brushColor);
        painter.drawPath(path);
        qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] paintEvent: Нарисована одна фигура.";
    }
    qDebug() << "[" << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "] paintEvent: Отрисовка завершена.";
}
