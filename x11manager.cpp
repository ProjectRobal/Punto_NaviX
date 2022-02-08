#include "x11manager.h"
#include <QDebug>
#include <QLabel>

X11Manager::X11Manager(QWidget *parent) :
    QWidget(parent)
{
isCreated=false;
    setFocusPolicy(Qt::StrongFocus);
    //wm_detected=false;

   // client=NULL;

    //display = XOpenDisplay(NULL);

    layout=new TableLayout(2,2,this);

    layout->setSizeConstraint(QLayout::SetNoConstraint);

    this->setLayout(layout);

    QLabel *label=new QLabel(this);

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

    layout->addItem(label4,4);



}

void X11Manager::createWindow()
{
    if(!isCreated)
    {
   // XSync(display, false);


 // event_loop->start();
    isCreated=true;
    }
}

// resize the window when needed
void X11Manager::resizeEvent(QResizeEvent *event)
{

}

void X11Manager::paintEvent(QPaintEvent *event)
{
    createWindow();
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

void X11Manager::Frame(Window w, bool was_created_before_window_manager)
{
    // Visual properties of the frame to create.
      //const unsigned int BORDER_WIDTH = 3;
      //const unsigned long BORDER_COLOR = 0xff0000;
      //const unsigned long BG_COLOR = 0x0000ff;

    qDebug()<<"Frame window!";

      // We shouldn't be framing windows we've already framed.
      if(layout->hasWindow(w))
      {
          return;
      }

   /*   // 1. Retrieve attributes of window to frame.
      XWindowAttributes x_window_attrs;
      XGetWindowAttributes(display, w, &x_window_attrs);

      // 2. If window was created before window manager started, we should frame
      // it only if it is visible and doesn't set override_redirect.
      if (was_created_before_window_manager) {
        if (x_window_attrs.override_redirect ||
            x_window_attrs.map_state != IsViewable) {
          return;
        }
      }*/

     qDebug()<<"Assiginig window";


    //XWidget *wid=new XWidget(display,w,this);


    //layout->addItem(wid,w);


  }

void X11Manager::Unframe(Window w) {
  if(!layout->hasWindow(w))
  {
      return;
  }

  layout->removeWindow(w);


}

int X11Manager::onWMDetected(Display *display, XErrorEvent *e)
{
    Q_UNUSED(display);
    Q_UNUSED(e);

    //wm_detected=true;
    qDebug()<<"Another Window manager detected!";

    return 0;
}

int X11Manager::onXError(Display *display, XErrorEvent *e)
{
    const int MAX_ERROR_TEXT_LENGTH = 1024;
      char error_text[MAX_ERROR_TEXT_LENGTH];
      XGetErrorText(display, e->error_code, error_text, sizeof(error_text));
      qDebug() << "Received X error:\n"
                 << "    Request: " << int(e->request_code)
                 << " - " << error_text << "\n"
                 << "    Error code: " << int(e->error_code)
                 << " - " << error_text << "\n"
                 << "    Resource ID: " << e->resourceid;

      return 0;
}


X11Manager::~X11Manager()
{


}

void X11Manager::OnCreateNotify(const XCreateWindowEvent &e)
{
// here is the issue


}

void X11Manager::OnDestroyNotify(const XDestroyWindowEvent &e)
{

}

void X11Manager::OnReparentNotify(const XReparentEvent &e)
{

}

void X11Manager::OnMapNotify(const XMapEvent &e)
{

}

void X11Manager::OnUnmapNotify(const XUnmapEvent &e)
{
    // If the window is a client window we manage, unframe it upon UnmapNotify. We
      // need the check because we will receive an UnmapNotify event for a frame
      // window we just destroyed ourselves.
    if(!layout->hasWindow(e.window))
    {

        qDebug() << "Ignore UnmapNotify for non-client window " << e.window;
        return;
      }

      // Ignore event if it is triggered by reparenting a window that was mapped
      // before the window manager started.
      //
      // Since we receive UnmapNotify events from the SubstructureNotify mask, the
      // event attribute specifies the parent window of the window that was
      // unmapped. This means that an UnmapNotify event from a normal client window
      // should have this attribute set to a frame window we maintain. Only an
      // UnmapNotify event triggered by reparenting a pre-existing window will have
      // this attribute set to the root window.
      if (e.event == this->winId()) {
        qDebug() << "Ignore UnmapNotify for reparented pre-existing window "
                  << e.window;
        return;
      }

      Unframe(e.window);
}

void X11Manager::OnConfigureNotify(const XConfigureEvent &e)
{

}

void X11Manager::OnMapRequest(const XMapRequestEvent &e)
{
    // 1. Frame or re-frame window.
      //Frame(e.window, false);
      // 2. Actually map window.
      //XMapWindow(display, e.window);

   /* if(_widgets.count(e.window)>0)
    {
        return;
    }*/

    Frame(e.window,false);

    this->update();

}

void X11Manager::OnConfigureRequest(const XConfigureRequestEvent &e)
{
 /*   XWindowChanges changes;
      changes.x = e.x;
      changes.y = e.y;
      changes.width = e.width;
      changes.height = e.height;
      changes.border_width = e.border_width;
      changes.sibling = e.above;
      changes.stack_mode = e.detail;
      if(!_widgets.count(e.window))
      {

        const Window frame = e.window;
        XConfigureWindow(display, frame, e.value_mask, &changes);
        qDebug() << "Resize [" << frame << "] to " << QSize(e.width, e.height);
      }
      XConfigureWindow(display, e.window, e.value_mask, &changes);
      qDebug() << "Resize " << e.window << " to " << QSize(e.width, e.height);*/
}

void X11Manager::OnButtonPress(const XButtonEvent &e)
{
   /* if(!layout->hasWindow(e.window))
    {
        return;
    }

      const Window frame = e.window;

      // 1. Save initial cursor position.
      drag_start_pos_ = QPoint(e.x_root, e.y_root);

      // 2. Save initial window info.
      Window returned_root;
      int x, y;
      unsigned width, height, border_width, depth;
      XGetGeometry(
          display,
          frame,
          &returned_root,
          &x, &y,
          &width, &height,
          &border_width,
          &depth);
      drag_start_frame_pos_ = QPoint(x, y);
      drag_start_frame_size_ = QSize(width, height);

      // 3. Raise clicked window to top.
      XRaiseWindow(display, frame);*/
}

void X11Manager::OnButtonRelease(const XButtonEvent &e)
{

}

void X11Manager::OnMotionNotify(const XMotionEvent &e)
{
 /*   if(!layout->hasWindow(e.window))
    {
        return;
    }

    const Window frame = e.window;
      const QPoint drag_pos(e.x_root, e.y_root);
      const QPoint delta = drag_pos - drag_start_pos_;

      if (e.state & Button1Mask ) {
        // alt + left button: Move window.
        const QPoint dest_frame_pos = drag_start_frame_pos_ + delta;
        XMoveWindow(
            display,
            frame,
            dest_frame_pos.x(), dest_frame_pos.y());
      } else if (e.state & Button3Mask) {
        // alt + right button: Resize window.
        // Window dimensions cannot be negative.
        const QPoint size_delta(
            std::max(delta.x(), -drag_start_frame_size_.width()),
            std::max(delta.y(), -drag_start_frame_size_.height()));
        QSize dest_frame_size;
             dest_frame_size.setWidth(drag_start_frame_size_.width()+delta.x());
             dest_frame_size.setHeight(drag_start_frame_size_.height()+delta.y());
        // 1. Resize frame.
        XResizeWindow(
            display,
            frame,
            dest_frame_size.width(), dest_frame_size.height());
        // 2. Resize client window.
        XResizeWindow(
            display,
            e.window,
            dest_frame_size.width(), dest_frame_size.height());
      }
*/
}

void X11Manager::OnKeyPress(const XKeyEvent &e)
{

}

void X11Manager::OnKeyRelease(const XKeyEvent &e)
{

}
