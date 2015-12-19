#include <QVBoxLayout>
#include <QTimer>
#include <QPainter>

#include "randomnumberswidget.h"


RandomNumbersWidget::RandomNumbersWidget(QWidget *parent) :
    QWidget(parent),
    m_timer(new QTimer),
    m_widget(new QWidget),
    m_label(new QLabel),
    m_currentFrame(nullptr)
{
    /// set up the label
    QFont font("Arial", 60, 10);
    m_label->setFont(font);

    /// set upt the renderization widget layout
    QVBoxLayout * widgetMainLayout = new QVBoxLayout;
    QHBoxLayout * widgetSecondaryLayout = new QHBoxLayout;

    widgetSecondaryLayout->addStretch();
    widgetSecondaryLayout->addWidget(m_label);
    widgetSecondaryLayout->addStretch();

    widgetMainLayout->addStretch();
    widgetMainLayout->addLayout(widgetSecondaryLayout);
    widgetMainLayout->addStretch();

    /// set up the renderization widget
    m_widget->resize(size());
    m_widget->setLayout(widgetMainLayout);

    /// define the renderization trigger timer
    m_timer->setInterval(500);

    QObject::connect(
        m_timer, &QTimer::timeout,
        this, [&](){
            quint8 randomNumber = qrand() % 10;
            m_label->setText(QString::number(randomNumber));

            if (m_cache.contains(randomNumber)) {
                /// if the number was already rendered then use the cache
                m_currentFrame = m_cache[randomNumber];
            } else {
                /// if the number was not rendered then render it with m_widget
                m_currentFrame = new QPixmap(m_widget->size());
                m_widget->render(m_currentFrame);
                m_cache.insert(randomNumber, m_currentFrame);
            }

            update();
        }
    );

    m_timer->start();
}

RandomNumbersWidget::~RandomNumbersWidget()
{
    /// clean-up pointer members
    delete m_label;
    delete m_timer;
    delete m_widget;

    /// clear the cache
    foreach(QPixmap *pmap, m_cache.values()) {
        delete pmap;
    }
}

void RandomNumbersWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    if (m_currentFrame == nullptr)
        return;

    /// draw the current frame pixmap
    QPainter painter(this);
    QSize frameSize(m_currentFrame->size());
    QRect frameRectangle(0, 0, frameSize.width(), frameSize.height());
    painter.drawPixmap(frameRectangle, *m_currentFrame);
}

void RandomNumbersWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    /// handle renderization widget size on parent widget resize
    m_widget->resize(size());
}
