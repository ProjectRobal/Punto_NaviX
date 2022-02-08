#include "xwidget.h"
#include <QDebug>

#define BORDER_WIDTH 3
#define BORDER_COLOR 0xff0000
#define BG_COLOR 0x0000ff

void XWidget::createWindow()
{


if(win!=NULL)
{

    layout->addWidget(createWindowContainer(win,this));

}

}

bool XWidget::isWindowCreated()
{
    return create_window;
}

void XWidget::removeWindow()
{

}

XWidget::XWidget(Display* _d,Window _client,QWidget *parent) : QWidget(parent)
{
    create_window=false;

    d=_d;

    client=_client;

    win=NULL;


     win = QWindow::fromWinId(client);

     layout=new QGridLayout(this);

     this->setLayout(layout);

    this->show();

}

void XWidget::resizeEvent(QResizeEvent *event)
{
    if(win!=NULL)
    {
    win->resize(event->size());
    }
}

void XWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if(!create_window)
    {
        createWindow();

        create_window=true;
   }


}



XWidget::~XWidget()
{

}
