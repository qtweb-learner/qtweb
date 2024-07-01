#include "messagewidget.h"
#include "ui_messagewidget.h"

MessageWidget::MessageWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessageWidget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint, true);
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet(QString("background-color: rgba(255, 255, 255, 100%);"));
    setFixedSize(parent->size());
    parent->installEventFilter(this);
    hide();
}

MessageWidget::~MessageWidget()
{
    delete ui;
}

void MessageWidget::ShowMsg(const QString & msg){
    ui->m_text->setText(msg);
    ui->m_ok->setFocus();
    show();
}

bool MessageWidget::eventFilter(QObject *target, QEvent *event){
    if (target == parent() && event->type() == QEvent::Resize){
        setFixedSize(parentWidget()->size());
    }
    return QWidget::eventFilter(target, event);
}

void MessageWidget::on_m_ok_clicked()
{
    hide();
}

