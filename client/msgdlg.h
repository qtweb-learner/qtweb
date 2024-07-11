#ifndef MSGDLG_H
#define MSGDLG_H

#include <QDialog>

namespace Ui {
class msgdlg;
}

class msgdlg : public QDialog
{
    Q_OBJECT

public:
    explicit msgdlg(const QString & text, QWidget *parent = nullptr);
    ~msgdlg();
    void MessageBox(const QString & text);
private:
    Ui::msgdlg *ui;
};

#endif // MSGDLG_H
