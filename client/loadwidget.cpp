#include "loadwidget.h"


LoadWidget::LoadWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlag(Qt::FramelessWindowHint, true);
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet(QString("background-color: rgba(20, 20, 20, 20%);"));
    setFixedSize(parent->size());
    parent->installEventFilter(this);
    parent->setEnabled(false);
    m_layout = new QGridLayout(this);
    m_label = new QLabel();
    m_label->setStyleSheet("background-color: transparent;");
    m_movie = new QMovie(":/loading.gif");
    m_layout->addWidget(m_label, 1,1,Qt::AlignCenter);
    m_label->setMovie(m_movie);
    m_movie->start();
    raise();
    show();
}

LoadWidget::~LoadWidget(){
    parentWidget()->setEnabled(true);
}

bool LoadWidget::eventFilter(QObject *target, QEvent *event){
    if (target == parent() && event->type() == QEvent::Resize){
        setFixedSize(parentWidget()->size());
    }
    return QWidget::eventFilter(target, event);
}
