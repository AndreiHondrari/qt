#include <QThreadPool>
#include <QDebug>

#include "bigfiledatatransfer.h"


BigFileDataCopy::BigFileDataCopy(const QString &inputFileName,
                                 const QString &outputFileName,
                                 quint64 numberOfTasks,
                                 QObject *parent) :
    QObject(parent),
    m_numberOfTasks(numberOfTasks),
    m_inputFile(new QFile(inputFileName)),
    m_outputFile(new QFile(outputFileName))
{
    // open files
    m_inputFile->open(QFile::ReadOnly);
    m_outputFile->open(QFile::WriteOnly);

    // create tasks
    for(ushort i = 0; i < m_numberOfTasks; ++i) {
        FileReadTask *fileReadTask = new FileReadTask(
            m_inputFile,
            &m_mutex,
            &m_dataList
        );
        fileReadTask->setAutoDelete(false);
        m_readTasks.append(fileReadTask);
    }
}

BigFileDataCopy::~BigFileDataCopy()
{
    m_inputFile->close();
    m_outputFile->close();

    delete m_inputFile;
    delete m_outputFile;

    foreach(FileReadTask* readTask, m_readTasks) {
        m_readTasks.removeAll(readTask);
        delete readTask;
    }
}

void BigFileDataCopy::transfer()
{
    while(!m_inputFile->atEnd()) {

        // start reading from the file
        foreach(FileReadTask* readTask, m_readTasks) {
            QThreadPool::globalInstance()->start(readTask);
        }

        QThreadPool::globalInstance()->waitForDone();

        // write into output file the buffered parts
        foreach(QByteArray data, m_dataList) {
            m_outputFile->write(data);
        }

        m_outputFile->flush();

        // clear data buffer after read/write
        m_dataList.clear();
    }


}
