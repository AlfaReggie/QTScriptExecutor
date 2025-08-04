#include "scriptexecutor.h"
#include <QApplication>

/**
 * @brief Точка входа в приложение исполнителя QTScript
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ScriptExecutor executor;
    executor.show();

    return app.exec();
}
