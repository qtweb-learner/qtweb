#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>

namespace Ui {
class MessageWidget;
}

class MessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageWidget(QWidget *parent = nullptr);
    ~MessageWidget();
    void ShowMsg(const QString & msg);
protected:
    virtual bool eventFilter(QObject *target, QEvent *event) override;
private slots:
    void on_m_ok_clicked();

private:
    Ui::MessageWidget *ui;
};

#endif // MESSAGEWIDGET_H
