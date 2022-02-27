#include "x11manager.h"
#include <QDebug>
#include <QLabel>
#include <QProcess>

X11Manager::X11Manager(QWidget *parent) :
    QWidget(parent)
{



    focus=NULL;

    XcbEventListener::reconfigure_window();



    // windows
    //XcbEventListener::grab_key(XCB_MOD_MASK_4,27);

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

    case UnmapNotifyXEvents::TYPE:
    {
        UnmapNotifyXEvents* x11=static_cast<UnmapNotifyXEvents*>(event);

        qDebug()<<x11->ResponseString()<<" "<<x11->responseType();
        qDebug()<<"client: "<<x11->getClient();
        qDebug()<<"root: "<<x11->getRoot();
        Unframe(x11->getClient());
    }
        break;

    case PressKeyXEvent::TYPE:
        {
            PressKeyXEvent* x11=static_cast<PressKeyXEvent*>(event);

            if(x11->getEvent()!=XcbEventListener::get_root())
            {
                //break;
            }

            qDebug()<<x11->ResponseString()<<" "<<x11->responseType();
            qDebug()<<"client: "<<x11->getEvent();
            qDebug()<<"root: "<<x11->getRoot();
            qDebug()<<"key: "<<x11->getKey();

            onPressKey(x11->getKey(),x11->getMod());
        }
            break;

        case ReleaseKeyXEvent::TYPE:
       {
           ReleaseKeyXEvent* x11=static_cast<ReleaseKeyXEvent*>(event);

           if(x11->getEvent()!=XcbEventListener::get_root())
           {
              break;
           }

           qDebug()<<x11->ResponseString()<<" "<<x11->responseType();
           qDebug()<<"client: "<<x11->getEvent();
           qDebug()<<"root: "<<x11->getRoot();
           qDebug()<<"key: "<<x11->getKey();

           onReleaseKey(x11->getKey(),x11->getMod());
       }
           break;

   /*  case ButtonPressXEvents::TYPE:
    {
        ButtonPressXEvents* x11=static_cast<ButtonPressXEvents*>(event);

        qDebug()<<x11->ResponseString()<<" "<<x11->responseType();
        qDebug()<<"client: "<<x11->getEvent();
        qDebug()<<"root: "<<x11->getRoot();
        qDebug()<<"key: "<<x11->getKey();
    }
        break;

    case ButtonReleaseXEvents::TYPE:
   {
       ButtonReleaseXEvents* x11=static_cast<ButtonReleaseXEvents*>(event);

       qDebug()<<x11->ResponseString()<<" "<<x11->responseType();
       qDebug()<<"client: "<<x11->getEvent();
       qDebug()<<"root: "<<x11->getRoot();
       qDebug()<<"key: "<<x11->getKey();
   }
       break;
       */

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
    /*
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
    */
}

void X11Manager::setShortCuts()
{
    // control + delete , remove selected window
    //QShortcut *win_del=new QShortcut(QKeySequence(Qt::META + Qt::SHIFT +Qt::Key_Delete),this,SLOT(RemoveWindow()));

    // window + run , open dialog run prompt
    //QShortcut *win_run=new QShortcut(QKeySequence(Qt::META + Qt::SHIFT + Qt::Key_R),this,SLOT(RunDialog()));

    XcbEventListener::ungrab_key(XCB_MOD_MASK_ANY,XCB_GRAB_ANY);

    // meta + shift + r , open dialog run prompt
    XcbEventListener::grab_key(XCB_MOD_MASK_4 | XCB_MOD_MASK_SHIFT,Qt::Key_R); //R button

    // meta + shift + d , remove selected window
    XcbEventListener::grab_key(XCB_MOD_MASK_4 | XCB_MOD_MASK_SHIFT,Qt::Key_D); //D button

    // meta + control + left , move selected window left
    XcbEventListener::grab_key(XCB_MOD_MASK_ANY,0xff51); //left button

    // meta + control + right , move selected window right
    XcbEventListener::grab_key(XCB_MOD_MASK_ANY,0xff53); //right button

    // meta + control + up , move selected window up
    XcbEventListener::grab_key(XCB_MOD_MASK_ANY,0xff52); //up button

    // meta + control + down , move selected window down
    XcbEventListener::grab_key(XCB_MOD_MASK_ANY,0xff54); //down button

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

    _w->setPtr(layout->end()-1,layout->get_index_of(layout->end()-1)); // last element of layout


  }

void X11Manager::Unframe(xcb_window_t w) {
  if(!_widgets.count(w))
  {
      return;
  }
  qDebug()<<"Unframe window!";
   layout->remove(_widgets[w]->getPtr());
  delete _widgets[w];
  _widgets.erase(w);

  this->update();


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

        this->update();
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

void X11Manager::onPressKey(xcb_keysym_t key, uint16_t mod)
{
    // meta + shift
    switch(mod )
    {
        case (XCB_MOD_MASK_4 | XCB_MOD_MASK_SHIFT):
    {
        switch (key) {

        case Qt::Key_R: //R

            RunDialog();

            break;

        case Qt::Key_D: //Delete

            RemoveWindow();

            break;

        }
    }
        break;

    default:
    {
        switch (key) {

        case 81: //Left arrow
        {
            if(focus==NULL)
            {
                break;
            }
            qDebug()<<"Swap left";



            TableLayout::layout_ptr ptr=layout->switch_left(focus->getPtr());

            TableLayout::layout_ptr prev=layout->get_ptr_on_right(ptr); // previous iterator
            if(ptr!=focus->getPtr())
            {

            reinterpret_cast<XWidget*>((*prev)->widget())->setPtr(prev,layout->get_index_of(prev));

                focus->setPtr(ptr,layout->get_index_of(ptr));
            }




           }
            break;

        case 83: //Right arrow
        {
            if(focus==NULL)
            {
                break;
            }
            qDebug()<<"Swap right";


            TableLayout::layout_ptr ptr=layout->switch_right(focus->getPtr());

            TableLayout::layout_ptr prev=layout->get_ptr_on_left(ptr); // previous iterator
            if(ptr!=focus->getPtr())
            {

            reinterpret_cast<XWidget*>((*prev)->widget())->setPtr(prev,layout->get_index_of(prev));

             focus->setPtr(ptr,layout->get_index_of(ptr));
            }


        }
            break;

        case 82: //Up arrow
        {
            if(focus==NULL)
            {
                break;
            }
            qDebug()<<"Swap up";


            TableLayout::layout_ptr ptr=layout->switch_up(focus->getPtr());

            TableLayout::layout_ptr prev=layout->get_ptr_on_down(ptr); // previous iterator

            qDebug()<<"new iterator";

            if(ptr!=focus->getPtr())
            {

            reinterpret_cast<XWidget*>((*prev)->widget())->setPtr(prev,layout->get_index_of(prev));

                focus->setPtr(ptr,layout->get_index_of(ptr));

            }
            qDebug()<<"new iterator1";


        }
            break;

        case 84: //Down arrow
        {
            if(focus==NULL)
            {
                break;
            }
            qDebug()<<"Swap down";


            TableLayout::layout_ptr ptr=layout->switch_down(focus->getPtr());

            TableLayout::layout_ptr prev=layout->get_ptr_on_up(ptr); // previous iterator

            qDebug()<<"new iterator";
            if(ptr!=focus->getPtr())
            {

            reinterpret_cast<XWidget*>((*prev)->widget())->setPtr(prev,layout->get_index_of(prev));

                focus->setPtr(ptr,layout->get_index_of(ptr));

            }

            qDebug()<<"new iterator1";


        }
            break;

        }
    }

        break;


    }
}

void X11Manager::onReleaseKey(xcb_keysym_t key, uint16_t mod)
{

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

void X11Manager::RunDialog()
{
    qDebug()<<"Run";
    bool ok;
    QInputDialog *run=new QInputDialog(this);

    QString prog=run->getText(this,tr("Run"),tr("Open: "),QLineEdit::Normal,"",&ok);

    if((ok)&&(!prog.isEmpty()))
    {
        if(QProcess::startDetached(prog,QStringList()))
        {
            qDebug()<<"Program started: "<<prog;
        }
        else
        {
            qDebug()<<prog<<" failed!";
        }
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



