#include <QCoreApplication>
#include <QThreadPool>
#include <QRunnable>
#include <QFile>
#include <QDebug>
#include <QMutex>

class FileTaskHandler : public QRunnable
{
public:
    explicit FileTaskHandler(QFile * input_file, QFile * output_file, QMutex * mutex);

    void run();

private:
    void message(QString msg);

private:
    QFile *m_input_file;
    QFile *m_output_file;
    QMutex *m_mutex;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<FileTaskHandler*> fileTasks;

    QMutex mutex;
    QFile input_file("somebigfile.txt");
    QFile output_file("someoutputfile.txt");

    input_file.open(QFile::ReadOnly);
    output_file.open(QFile::WriteOnly);

    for(ushort i = 0; i < 4; ++i) {
        FileTaskHandler *fileTaskhandler = new FileTaskHandler(
            &input_file,
            &output_file,
            &mutex
        );
        fileTasks.append(fileTaskhandler);
        QThreadPool::globalInstance()->start(fileTaskhandler);
    }

    QThreadPool::globalInstance()->waitForDone();
    input_file.close();
    output_file.close();
    qDebug() << "FINISHED !";

    return a.exec();
}

FileTaskHandler::FileTaskHandler(QFile * input_file, QFile * output_file, QMutex * mutex) :
    m_input_file(input_file),
    m_output_file(output_file),
    m_mutex(mutex)
{

}

void FileTaskHandler::run() {

    message("Started!");

    if(!m_input_file->exists()) {
        message(": File " + m_input_file->fileName() + " does not exist");
        return;
    }

    if(!m_output_file->exists()) {
        message(": File " + m_output_file->fileName() + " does not exist");
        return;
    }

    if(!m_input_file->isOpen() || m_input_file->openMode() != QFile::ReadOnly) {
        message(": File " + m_input_file->fileName() + " is not opened in read-only mode");
        return;
    }

    if(!m_output_file->isOpen() || m_output_file->openMode() != QFile::WriteOnly) {
        message(": File " + m_output_file->fileName() + " is not opened in write-only mode");
        return;
    }

    message("Ended !");
}

void FileTaskHandler::message(QString msg)
{
    m_mutex->lock();
    qDebug().noquote() << QStringLiteral("THREAD ") << QString("%1").arg((quintptr)QThread::currentThreadId()).rightJustified(4) << ": " << msg;
    m_mutex->unlock();
}
