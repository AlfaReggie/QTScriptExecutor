#ifndef SCRIPTEXECUTOR_H
#define SCRIPTEXECUTOR_H

#include <QObject>
#include <QMainWindow>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>
#include <QMessageBox>
#include <QHostAddress>

QT_BEGIN_NAMESPACE namespace Ui {
    class ScriptExecutor;
}
QT_END_NAMESPACE

class ScriptCanvas;

class ScriptExecutor : public QMainWindow {
    Q_OBJECT

public:
    ScriptExecutor(QWidget *parent = nullptr);
    ~ScriptExecutor() = default;

private slots:
    void on_startButton_clicked();
    void readPendingDatagrams();

private:
    Ui::ScriptExecutor *ui;
    QUdpSocket *udpSocket;
    ScriptCanvas *canvas;

    QString senderIP;
    quint16 senderPort;

    void executeScript(const QString &script);
    void sendResult(const QString &result, bool success);
};

#endif // SCRIPTEXECUTOR_H
