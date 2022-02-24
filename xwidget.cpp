#include "xwidget.h"
#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include "xcbeventlistener.h"

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
    win->close();
}

void XWidget::set_active()
{
    qDebug()<<"Active change";
    if(win->isActive())
    {
        this->setProperty("cssClass","active");
        //this->setStyleSheet("border: 5px solid red;");
        qDebug()<<"Active";
    }
    else
    {
        this->setProperty("cssClass","");
        this->setStyleSheet("");
    }
}

XWidget::XWidget(xcb_window_t _client,QWidget *parent) : QWidget(parent)
{
    create_window=false;

    client=_client;

    win=NULL;


     win = QWindow::fromWinId(client);

     layout=new QGridLayout(this);

     this->setLayout(layout);

    this->show();

     QObject::connect(win,&QWindow::activeChanged,this,&XWidget::set_active);

    XcbEventListener::make_window_listen(client);

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

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);


}


void XWidget::FocusIn()
{

    setObjectName("active");
    setStyleSheet("border:5px solid red");

}

void XWidget::FocusOut()
{
    setObjectName("");
    setStyleSheet("");
}



XWidget::~XWidget()
{
    delete layout;
    removeWindow();
    delete win;
}
