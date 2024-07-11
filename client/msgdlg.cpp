#include "msgdlg.h"
#include "ui_msgdlg.h"

msgdlg::msgdlg( const QString & text, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::msgdlg)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->m_msg->setText(text);
}

msgdlg::~msgdlg()
{
    delete ui;
}
