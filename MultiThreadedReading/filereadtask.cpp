#include <QThread>
#include <QDebug>

#include "filereadtask.h"


FileReadTask::FileReadTask(QFile *inputFile, QMutex *inputMutex, QList<QByteArray> *dataList) :
    m_inputFile(inputFile),
    m_mutex(inputMutex),
    m_dataList(dataList)
{

}

FileReadTask::~FileReadTask()
{

}

void FileReadTask::run()
{
    // check if input file even exists
    if(!m_inputFile->exists()) {
        qDebug() << "FILE DOES NOT EXIST";
        return;
    }

    // check if the file is opened in ReadOnly mode
    if(!m_inputFile->isOpen() || m_inputFile->openMode() != QFile::ReadOnly) {
        qDebug() << "FILE IS NOT OPENED IN READ ONLY MODE";
        return;
    }

    while(!m_inputFile->atEnd() && (m_dataList->size() < MAXIMUM_MEMORY_SIZE)) {
        m_mutex->lock();
        QByteArray data = m_inputFile->read(BYTE_ARRAY_SIZE);
        m_dataList->append(data);
        m_mutex->unlock();
    }
}
