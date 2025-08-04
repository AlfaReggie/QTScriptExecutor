#include "scriptexecutor.h"
#include "ui_scriptexecutor.h"
#include "scriptcanvas.h"
#include <QMessageBox>
#include <QDateTime>
#include <QJSEngine>

ScriptExecutor::ScriptExecutor(QWidget *parent) : QMainWindow(parent), ui(new Ui::ScriptExecutor), canvas(nullptr) {
    ui ->setupUi(this);

    udpSocket = new QUdpSocket(this);

    connect(udpSocket, &QUdpSocket::readyRead, this, &ScriptExecutor::readPendingDatagrams);

    ui -> logDisplay -> append(QString("[%1] Script Executor is ready to start").arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
}

void ScriptExecutor::on_startButton_clicked()
{
    QString portStr = ui->portInput->text();
    quint16 port = portStr.toUShort();

    if (port == 0) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Введите корректный порт"));
        return;
    }

    if (udpSocket->bind(QHostAddress::Any, port)) {
        ui->startButton->setEnabled(false);
        ui->portInput->setEnabled(false);
        ui->statusbar->showMessage(tr("Сервер запущен на порту %1").arg(port));
        ui->logDisplay->append(QString("[%1] Сервер запущен на порту %2")
                                   .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                   .arg(port));
    } else {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось запустить сервер"));
    }
}

void ScriptExecutor::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        senderIP = datagram.senderAddress().toString();
        senderPort = datagram.senderPort();

        QByteArray data = datagram.data();
        QDataStream in(&data, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_15);

        QString command;
        QString script;

        in >> command >> script;

        if (command == "EXECUTE_SCRIPT") {
            ui->logDisplay->append(QString("[%1] Получен скрипт от %2:%3")
                                       .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                       .arg(senderIP)
                                       .arg(senderPort));

            executeScript(script);
        }
    }
}

void ScriptExecutor::executeScript(const QString &script)
{
    ui->logDisplay->append(QString("[%1] Начинаю выполнение скрипта...")
                               .arg(QDateTime::currentDateTime().toString("hh:mm:ss")));

    try {
        // Создаем движок JavaScript
        QJSEngine engine;

        // Создаем и регистрируем Canvas объект
        if (canvas) {
            canvas->deleteLater();
        }

        canvas = new ScriptCanvas(800, 600);
        QJSValue canvasObject = engine.newQObject(canvas);
        engine.globalObject().setProperty("canvas", canvasObject);

        // Выполняем скрипт
        QJSValue result = engine.evaluate(script);

        if (result.isError()) {
            QString error = QString("Ошибка выполнения скрипта: %1")
                                .arg(result.toString());
            ui->logDisplay->append(QString("[%1] %2")
                                       .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                       .arg(error));
            sendResult(error, false);
        } else {
            QString successMsg = "Скрипт выполнен успешно";
            ui->logDisplay->append(QString("[%1] %2")
                                       .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                       .arg(successMsg));

            // Показываем холст с результатами
            if (canvas) {
                canvas->show();
            }

            sendResult(successMsg, true);
        }
    } catch (const std::exception &e) {
        QString error = QString("Исключение при выполнении скрипта: %1").arg(e.what());
        ui->logDisplay->append(QString("[%1] %2")
                                   .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                   .arg(error));
        sendResult(error, false);
    } catch (...) {
        QString error = "Неизвестная ошибка при выполнении скрипта";
        ui->logDisplay->append(QString("[%1] %2")
                                   .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                   .arg(error));
        sendResult(error, false);
    }
}

void ScriptExecutor::sendResult(const QString &result, bool success)
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << QString("SCRIPT_RESULT");
    out << success;
    out << result;

    udpSocket->writeDatagram(datagram, QHostAddress(senderIP), senderPort);
}
