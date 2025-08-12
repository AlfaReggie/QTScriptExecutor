#include "scriptexecutor.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ScriptExecutor executor;
    executor.show();

    return app.exec();
}
