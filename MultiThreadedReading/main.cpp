#include <QCoreApplication>
#include <QThreadPool>
#include <QRunnable>
#include <QFile>
#include <QDebug>


class FileTaskHandler : public QRunnable
{
public:
    explicit FileTaskHandler(const QString &fileName, const QString &threadName);
    virtual ~FileTaskHandler();

    void run();

private:
    QFile *m_file;
    QString m_name;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<FileTaskHandler*> fileTasks;

    for(ushort i = 0; i < 4; ++i) {
        FileTaskHandler *fileTaskhandler = new FileTaskHandler("somefile.txt", QString("{0}{1}").arg("THREAD #", i));
        fileTasks.append(fileTaskhandler);
        QThreadPool::globalInstance()->start(fileTaskhandler);
    }

    return a.exec();
}

FileTaskHandler::FileTaskHandler(const QString &fileName, const QString &threadName) :
    m_file(new QFile(fileName)),
    m_name(threadName)
{

}

FileTaskHandler::~FileTaskHandler()
{
    delete m_file;
}

void FileTaskHandler::run() {
    qDebug() << m_name;
}
