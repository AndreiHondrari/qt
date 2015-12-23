#include <QRunnable>
#include <QMutex>
#include <QFile>

#ifndef FILEREADTASK_H
#define FILEREADTASK_H


/**
 * @brief The FileReadTask class
 */
class FileReadTask : public QRunnable
{
public:
    static const quint16 BYTE_ARRAY_SIZE = 100;
    static const quint32 MAXIMUM_MEMORY_SIZE = 100000;

private:
    /**
     * @brief m_inputFile
     */
    QFile *m_inputFile;

    /**
     * @brief m_mutex
     */
    QMutex *m_mutex;

    /**
     * @brief m_dataList
     */
    QList<QByteArray> *m_dataList;

public:
    /**
     * @brief FileReadTask
     * @param inputFile
     * @param inputMutex
     * @param dataList
     */
    FileReadTask(QFile * inputFile, QMutex *inputMutex, QList<QByteArray> *dataList);

    virtual ~FileReadTask();

    /**
     * @brief run
     */
    void run();
};

#endif // FILEREADTASK_H
