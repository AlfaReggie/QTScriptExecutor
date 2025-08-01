#ifndef SCRIPTEXECUTOR_H
#define SCRIPTEXECUTOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ScriptExecutor;
}
QT_END_NAMESPACE

class ScriptExecutor : public QMainWindow
{
    Q_OBJECT

public:
    ScriptExecutor(QWidget *parent = nullptr);
    ~ScriptExecutor();

private:
    Ui::ScriptExecutor *ui;
};
#endif // SCRIPTEXECUTOR_H
