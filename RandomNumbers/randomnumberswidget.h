#ifndef RANDOMNUMBERSWIDGET_H
#define RANDOMNUMBERSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHash>


/**
 * @brief The RandomNumbersWidget class
 */
class RandomNumbersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RandomNumbersWidget(QWidget *parent = 0);

    virtual ~RandomNumbersWidget();

private:

    /**
     * @brief Label widget representing the random number.
     */
    QLabel *m_label;

    /**
     * @brief Trigger timer for the new random number and cache handling.
     */
    QTimer *m_timer;

    /**
     * @brief Widget responsible for renderization of the pixmaps with the numbers.
     */
    QWidget *m_widget;

    /**
     * @brief The current frame to be drawn by the RandomNumbersWidget widget.
     */
    QPixmap *m_currentFrame;

    /**
     * @brief Cache with the generated pixmaps of the numbers.
     */
    QHash<quint8, QPixmap*> m_cache;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

};

#endif // RANDOMNUMBERSWIDGET_H
