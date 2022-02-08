#ifndef XEVENTS_H
#define XEVENTS_H

extern "C"
{
 #include <X11/Xlib.h>
}

#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted


#include <QThread>
#include <QString>


class XEvents : public QThread
{
    Q_OBJECT

    XEvent e;

    //char *event_str;

    Display* display;

    void run() override;



public:
    XEvents(Display *_display,QObject* parent=nullptr);

    static QString EventToString(const XEvent &e);

signals:

    // basic x window events

    void onCreateNotify(const XCreateWindowEvent& e);

    void onDestroyNotify(const XDestroyWindowEvent& e);

    void onReparentNotify(const XReparentEvent& e);

    void onMapNotify(const XMapEvent& e);

    void onUnmapNotify(const XUnmapEvent& e);

    void onConfigureNotify(const XConfigureEvent& e);

    void onMapRequest(const XMapRequestEvent& e);

    void onConfigureRequest(const XConfigureRequestEvent& e);

    void onButtonPress(const XButtonEvent& e);

    void onButtonRelease(const XButtonEvent& e);

    void onMotionNotify(const XMotionEvent& e);

    void onKeyPress(const XKeyEvent& e);

    void onKeyRelease(const XKeyEvent& e);



};



#endif // XEVENTS_H
