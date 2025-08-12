#include "scriptexecutor.h"
#include "ui_scriptexecutor.h"
#include "scriptcanvaswidget.h"
#include <QNetworkDatagram>
#include <QDataStream>
#include <QJSEngine>
#include <QJSValue>
#include <QVBoxLayout>
#include <QDateTime>

ScriptExecutor::ScriptExecutor(QWidget *parent) : QMainWindow(parent), ui(new Ui::ScriptExecutor), udpSocket(nullptr), m_canvasWidget(nullptr) {
    ui->setupUi(this);
    m_canvasWidget = new ScriptCanvasWidget(this);

    if (ui->centralwidget->layout() == nullptr) {
        QVBoxLayout *mainLayout = new QVBoxLayout(ui->centralwidget);
        QWidget *mainCentralWidget = new QWidget(this);
        QVBoxLayout *mainCentralLayout = new QVBoxLayout(mainCentralWidget);
        ui->verticalLayout->addWidget(m_canvasWidget);
        ui->verticalLayout->setStretchFactor(ui->logDisplay, 0);
        ui->verticalLayout->setStretchFactor(ui->horizontalLayout, 0);
        ui->verticalLayout->setStretchFactor(m_canvasWidget, 1);
    } else {
        ui->verticalLayout->addWidget(m_canvasWidget);
        ui->verticalLayout->setStretchFactor(m_canvasWidget, 1);
    }

    udpSocket = new QUdpSocket(this);
    connect(udpSocket, &QUdpSocket::readyRead, this, &ScriptExecutor::readPendingDatagrams);

    ui->logDisplay->append(QString("[%1] Script Executor готов к запуску").arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
}

ScriptExecutor::~ScriptExecutor() {
    delete ui;
}

void ScriptExecutor::on_startButton_clicked() {
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
        ui->logDisplay->append(QString("[%1] Сервер запущен на порту %2").arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(port));
    } else {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось запустить сервер: %1")
                                                     .arg(udpSocket->errorString()));
    }
}

void ScriptExecutor::readPendingDatagrams() {
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
            ui->logDisplay->append(QString("[%1] Получен скрипт от %2:%3").arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(senderIP).arg(senderPort));
            executeScript(script);
        }
    }
}

void ScriptExecutor::executeScript(const QString &script) {
    ui->logDisplay->append(QString("[%1] Начинаю выполнение скрипта...")
                               .arg(QDateTime::currentDateTime().toString("hh:mm:ss")));

    try {
        QJSEngine engine;

        QJSValue canvasObject = engine.newQObject(m_canvasWidget);
        engine.globalObject().setProperty("canvas", canvasObject);

        ui->logDisplay->append(QString("[%1] Canvas виджет зарегистрирован").arg(QDateTime::currentDateTime().toString("hh:mm:ss")));

        QJSValue result = engine.evaluate(script);

        if (result.isError()) {
            QString error = QString("Ошибка выполнения скрипта: %1\nСтрока: %2")
                                .arg(result.toString())
                                .arg(result.property("lineNumber").toInt());
            ui->logDisplay->append(QString("[%1] %2")
                                       .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                       .arg(error));
            sendResult(error, false);
        } else {
            QString successMsg = "Скрипт выполнен успешно";
            ui->logDisplay->append(QString("[%1] %2").arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(successMsg));
            m_canvasWidget->update();
            sendResult(successMsg, true);
        }
    } catch (const std::exception &e) {
        QString error = QString("Исключение при выполнении скрипта: %1").arg(e.what());
        ui->logDisplay->append(QString("[%1] %2").arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(error));
        sendResult(error, false);
    } catch (...) {
        QString error = "Неизвестная ошибка при выполнении скрипта";
        ui->logDisplay->append(QString("[%1] %2").arg(QDateTime::currentDateTime().toString("hh:mm:ss")).arg(error));
        sendResult(error, false);
    }
}

void ScriptExecutor::sendResult(const QString &result, bool success) {
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << QString("SCRIPT_RESULT");
    out << success;
    out << result;

    udpSocket->writeDatagram(datagram, QHostAddress(senderIP), senderPort);
}
