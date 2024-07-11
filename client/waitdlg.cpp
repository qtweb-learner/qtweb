#include "waitdlg.h"


WaitDlg::WaitDlg(QWidget *parent)
    : QDialog{parent}
{
    setWindowFlag(Qt::FramelessWindowHint, true);
    auto pl = this->palette();
    pl.setColor(QPalette::Window, QColor(0,0,0,0));
    setPalette(pl);
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(true);
    m_layout = new QHBoxLayout(this);
    m_label = new QLabel();
    m_movie = new QMovie(":/loading.gif");
    m_label->setMovie(m_movie);
    m_layout->addWidget(m_label);
    m_movie->start();
    show();
}

WaitDlg::~WaitDlg(){
}
