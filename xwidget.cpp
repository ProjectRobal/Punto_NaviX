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
    //setAutoFillBackground(true);
    //create_window=false;
    active=false;

    client=_client;

    win=NULL;


     win = QWindow::fromWinId(client);

     //win->setAutoFillBackground(true);

     layout=new QGridLayout(this);

     this->setLayout(layout);

    this->show();

     label=new QLabel(this);

     label->setText("Hello");

   layout->addWidget(label,1,1,1,1);

   layout->addWidget(createWindowContainer(win,this),2,1,4,1);

     QObject::connect(win,&QWindow::activeChanged,this,&XWidget::set_active);

    XcbEventListener::make_window_listen(client);

}

void XWidget::setPtr(TableLayout::layout_ptr _ptr)
{
    ptr=_ptr;

    //  label->setText("Layout index: "+QString());
}

void XWidget::setPtr(TableLayout::layout_ptr _ptr, uint32_t index)
{
    ptr=_ptr;

    label->setText("Layout index: "+QString::number(index));
}

TableLayout::layout_ptr XWidget::getPtr()
{
    return ptr;
}

void XWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

   /* if(!create_window)
    {
        createWindow();

        create_window=true;
   }*/

   /* QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
*/
    if(active)
    {

    QPainter p(this);

    QPen pen(Qt::red,10);
    p.setPen(pen);

    p.drawRect(QRect(QPoint(0,0),this->size()));

    }


}


void XWidget::FocusIn()
{

   // setObjectName("active");
    //setStyleSheet("border:5px solid red");
    active=true;

}

void XWidget::FocusOut()
{
   // setObjectName("");
   // setStyleSheet("");
    active=false;
}



XWidget::~XWidget()
{
    delete layout;
    removeWindow();
    delete win;
}
