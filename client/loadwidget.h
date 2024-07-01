#ifndef LOADWIDGET_H
#define LOADWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QMovie>

class LoadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoadWidget(QWidget *parent = nullptr);
    ~LoadWidget();
protected:
    virtual bool eventFilter(QObject *target, QEvent *event) override;
private:
    QGridLayout *m_layout;
    QLabel *m_label;
    QMovie *m_movie;
};

#endif // LOADWIDGET_H
