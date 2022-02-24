#include "x11manager.h"
#include <QDebug>
#include <QLabel>
#include <QX11Info>

X11Manager::X11Manager(QWidget *parent) :
    QWidget(parent)
{
    focus=NULL;

    XcbEventListener::reconfigure_window();

    setFocusPolicy(Qt::StrongFocus);

    this->setStyleSheet("#active {border: 3px solid red;}");

    listener=new XcbEventListener(this);

    QAbstractEventDispatcher::instance()->installNativeEventFilter(listener);

    //wm_detected=false;

   // client=NULL;

    //display = XOpenDisplay(NULL);

    layout=new TableLayout(2,2,this);

    layout->setSizeConstraint(QLayout::SetNoConstraint);

    this->setLayout(layout);

    setShortCuts();

    /*QLabel *label=new QLabel(this);

    label->setText("Hello World!");

    label->setStyleSheet("border: 5px solid red;");

    layout->addItem(label,0);

    QLabel *label1=new QLabel(this);

    label1->setText("Hello World!");

    label1->setStyleSheet("border: 5px solid blue;");

    layout->addItem(label1,1);

    QLabel *label2=new QLabel(this);

    label2->setText("Placki!");

    label2->setStyleSheet("border: 5px solid green;");

    layout->addItem(label2,2);

    QLabel *label3=new QLabel(this);

    label3->setText("Placki!");

    label3->setStyleSheet("border: 5px solid yellow;");

    layout->addItem(label3,3);

    QLabel *label4=new QLabel(this);

    label4->setText("Murzyn");

    label4->setStyleSheet("border: 5px solid black;");

    layout->addItem(label4,4);*/



}

bool X11Manager::event(QEvent *event)
{
    switch(event->type())
    {

        case MapRequestXEvent::TYPE:
    {
        MapRequestXEvent* x11=static_cast<MapRequestXEvent*>(event);

        qDebug()<<x11->ResponseString()<<" "<<x11->responseType();
        qDebug()<<"client: "<<x11->getClient();
        qDebug()<<"root: "<<x11->getRoot();

        Frame(x11->getClient());
    }

        break;

        case DestroyNotifyXEvents::TYPE:
    {

        DestroyNotifyXEvents* x11=static_cast<DestroyNotifyXEvents*>(event);

        qDebug()<<x11->ResponseString()<<" "<<x11->responseType();
        qDebug()<<"client: "<<x11->getClient();
        qDebug()<<"event: "<<x11->getEventWindow();
        Unframe(x11->getClient());
    }

        break;

    case FocusInXEvents::TYPE:
    {
        FocusInXEvents* x11=static_cast<FocusInXEvents*>(event);

        qDebug()<<x11->ResponseString()<<" "<<x11->responseType();
        qDebug()<<"client: "<<x11->getWindow();
       // setFocusColor(x11->getWindow());
    }
        break;

    case FocusOutXEvents::TYPE:
    {
        FocusOutXEvents* x11=static_cast<FocusOutXEvents*>(event);

        qDebug()<<x11->ResponseString()<<" "<<x11->responseType();
        qDebug()<<"client: "<<x11->getWindow();
       // removeFocusColor(x11->getWindow());
    }
        break;

    case EnterNotifyXEvents::TYPE:
    {
        EnterNotifyXEvents* x11=static_cast<EnterNotifyXEvents*>(event);

        qDebug()<<x11->ResponseString()<<" "<<x11->responseType();
        qDebug()<<"root: "<<x11->getRoot();
        qDebug()<<"client: "<<x11->getWindow();
        qDebug()<<"child: "<<x11->getChild();
        qDebug()<<"cursor: "<<x11->globalPos();
        setActive(x11->getWindow());
    }
        break;

    }

    return QWidget::event(event);
}


// resize the window when needed
void X11Manager::resizeEvent(QResizeEvent *event)
{

}

void X11Manager::paintEvent(QPaintEvent *event)
{

}

void X11Manager::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key::Key_Right)
    {
        layout->addColumn();
        qDebug()<<"Columns: "<<layout->getColumn();
        this->update();
    }

    if(event->key()==Qt::Key::Key_Left)
    {
        layout->popColumn();
        qDebug()<<"Columns: "<<layout->getColumn();
        this->update();
    }

}

void X11Manager::setShortCuts()
{
    QShortcut *win_del=new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_Delete),this,SLOT(RemoveWindow()));
}

void X11Manager::Frame(xcb_window_t w)
{
    // Visual properties of the frame to create.
      //const unsigned int BORDER_WIDTH = 3;
      //const unsigned long BORDER_COLOR = 0xff0000;
      //const unsigned long BG_COLOR = 0x0000ff;

    qDebug()<<"Frame window!";

      // We shouldn't be framing windows we've already framed.
      if(_widgets.count(w))
      {
          return;
      }

     qDebug()<<"Assiginig window";

    XWidget* _w=new XWidget(w,this);

    _widgets[w]=_w;

    layout->addItem(_w);

    //_w->makeActive();


  }

void X11Manager::Unframe(xcb_window_t w) {
  if(!_widgets.count(w))
  {
      return;
  }
  qDebug()<<"Unframe window!";

  delete _widgets[w];
  _widgets.erase(w);


}

void X11Manager::setActive(xcb_window_t w)
{
    if((focus!=NULL)&&(focus->getClient()==w))
    {
        return;
    }
    if(_widgets.count(w))
    {
        if(focus!=NULL)
        {
            focus->FocusOut();
        }
        focus=_widgets[w];
        focus->FocusIn();

        XcbEventListener::set_input_focus(w);
    }


}

void X11Manager::setFocusColor(xcb_window_t w)
{
    if(_widgets.count(w))
    {
        _widgets[w]->FocusIn();
        qDebug()<<"Focus IN: "<<_widgets[w]->styleSheet();
        this->update();
    }
}

void X11Manager::removeFocusColor(xcb_window_t w)
{
    if(_widgets.count(w))
    {
        _widgets[w]->FocusOut();
        qDebug()<<"Focus OUT: "<<_widgets[w]->styleSheet();
        this->update();
    }
}

void X11Manager::RemoveWindow()
{
    qDebug()<<"Remove";
    if(focus!=NULL)
    {
        layout->removeWidget(focus);
        _widgets.erase(focus->getClient());
        delete focus;
        focus=NULL;
        qDebug()<<"Window removed!";
    }
}

X11Manager::~X11Manager()
{

    for(auto w : _widgets)
    {
        delete  w.second;
    }

    _widgets.clear();

}



