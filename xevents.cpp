#include "xevents.h"
#include <QDebug>


void XEvents::run()
{
    while(1)
    {
        XNextEvent(display,&e);

        qDebug()<<"Recived event: "<<EventToString(e);

        switch (e.type) {
             case CreateNotify:
               emit onCreateNotify(e.xcreatewindow);
               break;
             case DestroyNotify:
               emit onDestroyNotify(e.xdestroywindow);
               break;
             case ReparentNotify:
               emit onReparentNotify(e.xreparent);
               break;
             case MapNotify:
               emit onMapNotify(e.xmap);
               break;
             case UnmapNotify:
               emit onUnmapNotify(e.xunmap);
               break;
             case ConfigureNotify:
               emit onConfigureNotify(e.xconfigure);
               break;
             case MapRequest:
               emit onMapRequest(e.xmaprequest);
               break;
             case ConfigureRequest:
               emit onConfigureRequest(e.xconfigurerequest);
               break;
             case ButtonPress:
               emit onButtonPress(e.xbutton);
               break;
             case ButtonRelease:
               emit onButtonRelease(e.xbutton);
               break;
             case MotionNotify:
               // Skip any already pending motion events.
               while (XCheckTypedWindowEvent(
                   display, e.xmotion.window, MotionNotify, &e)) {}
               emit onMotionNotify(e.xmotion);
               break;
             case 2/*KeyPress*/:
               emit onKeyPress(e.xkey);
               break;
             case 3 /*KeyRelease*/:
               emit onKeyRelease(e.xkey);
               break;
             default:
               qDebug() << "Ignored event";
           }
    }
}

XEvents::XEvents(Display *_display,QObject* parent)
    : QThread(parent)
{
    display=_display;
   // event_str=(char*)calloc(50,sizeof(char));
}

QString XEvents::EventToString(const XEvent &e)
{
    static const char* const X_EVENT_TYPE_NAMES[] = {
          "",
          "",
          "KeyPress",
          "KeyRelease",
          "ButtonPress",
          "ButtonRelease",
          "MotionNotify",
          "EnterNotify",
          "LeaveNotify",
          "FocusIn",
          "FocusOut",
          "KeymapNotify",
          "Expose",
          "GraphicsExpose",
          "NoExpose",
          "VisibilityNotify",
          "CreateNotify",
          "DestroyNotify",
          "UnmapNotify",
          "MapNotify",
          "MapRequest",
          "ReparentNotify",
          "ConfigureNotify",
          "ConfigureRequest",
          "GravityNotify",
          "ResizeRequest",
          "CirculateNotify",
          "CirculateRequest",
          "PropertyNotify",
          "SelectionClear",
          "SelectionRequest",
          "SelectionNotify",
          "ColormapNotify",
          "ClientMessage",
          "MappingNotify",
          "GeneralEvent",
      };

      return QString(X_EVENT_TYPE_NAMES[e.type]);
}
