#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>

#include "filereadtask.h"


/**
 * @brief The BigFileDataCopy class
 */
class BigFileDataCopy : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief BigFileDataCopy
     * @param inputFileName
     * @param outputFileName
     * @param numberOfTasks
     * @param parent
     */
    explicit BigFileDataCopy(const QString &inputFileName,
                             const QString &outputFileName,
                             quint64 numberOfTasks = 4,
                             QObject *parent = 0);

    virtual ~BigFileDataCopy();

    /**
     * @brief Handles the copy between the input and the output
     */
    void transfer();

private:
    /**
     * @brief Number of tasks to be spawn for reading
     */
    quint64 m_numberOfTasks;

    /**
     * @brief The input file to be read
     */
    QFile *m_inputFile;

    /**
     * @brief The output file to copy the input file to
     */
    QFile *m_outputFile;

    /**
     * @brief Read mutex locker
     */
    QMutex m_mutex;

    /**
     * @brief Buffer for data between read from the input and write to the output
     */
    QList<QByteArray> m_dataList;

    /**
     * @brief The reading tasks instances
     */
    QList<FileReadTask*> m_readTasks;
};

#endif // FILEREADER_H
