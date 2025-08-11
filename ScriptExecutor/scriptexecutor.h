#ifndef SCRIPTEXECUTOR_H
#define SCRIPTEXECUTOR_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QDateTime>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class ScriptExecutor; }
QT_END_NAMESPACE

class ScriptCanvasWidget;
class QJSEngine;

class ScriptExecutor : public QMainWindow
{
    Q_OBJECT

public:

    ScriptExecutor(QWidget *parent = nullptr);
    ~ScriptExecutor();

private slots:

    void on_startButton_clicked();
    void readPendingDatagrams();

private:
    Ui::ScriptExecutor *ui;
    QUdpSocket *udpSocket;
    ScriptCanvasWidget *m_canvasWidget;

    QString senderIP;
    quint16 senderPort;

    void executeScript(const QString &script);
    void sendResult(const QString &result, bool success);
};

#endif // SCRIPTEXECUTOR_H
