#include "workerform.h"
#include <QSplitter>
#include <QHBoxLayout>
#include <QToolBox>
#include <QTextEdit>

WorkerForm::WorkerForm(QWidget *parent)
    : QWidget{parent}
{
    auto playout = new QHBoxLayout(this);
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    playout->addWidget(splitter);

    auto ptoolbox = new QToolBox();
    ptoolbox->addItem(new QWidget, "page 1");
    ptoolbox->addItem(new QWidget, "page 2");
    ptoolbox->addItem(new QWidget, "page 3");
    ptoolbox->addItem(new QWidget, "page 4");
    ptoolbox->addItem(new QWidget, "page 5");

    auto ptextedit = new QTextEdit();

    splitter->addWidget(ptoolbox);
    splitter->addWidget(ptextedit);

}
