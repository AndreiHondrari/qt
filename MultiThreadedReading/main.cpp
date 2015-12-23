#include <QCoreApplication>
#include <QDebug>

#include "bigfiledatatransfer.h"

void message(const QString &taskId, const QString &msg) {
    qDebug() << QString("TASK %1 : %2").arg(taskId, msg);
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BigFileDataCopy dc("somebigfile.txt", "someoutputfile.txt");

    qDebug() << "START READING THE FILE";
    dc.transfer();

    qDebug() << "FINISHED !";

    return a.exec();
}


