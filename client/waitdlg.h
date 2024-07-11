#ifndef WAITDLG_H
#define WAITDLG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMovie>

class WaitDlg : public QDialog
{
    Q_OBJECT
public:
    explicit WaitDlg(QWidget *parent = nullptr);
    ~WaitDlg();
private:
    QHBoxLayout *m_layout;
    QLabel *m_label;
    QMovie *m_movie;
};

#endif // WAITDLG_H
