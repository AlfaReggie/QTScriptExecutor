#include "scriptexecutor.h"
#include "ui_scriptexecutor.h"

ScriptExecutor::ScriptExecutor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ScriptExecutor)
{
    ui->setupUi(this);
}

ScriptExecutor::~ScriptExecutor()
{
    delete ui;
}
