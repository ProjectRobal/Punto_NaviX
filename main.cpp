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

#include <xcb/xcb.h>

#include "mainwindow.h"

#include "xcbeventlistener.h"
#include <QX11Info>
#include <QApplication>

int main(int argc, char *argv[])
{
//    XcbEventListener xcb;





    QApplication a(argc, argv);



    MainWindow w;
    w.resize(1024,720);
    w.show();

    // let make mainwindow recive appropiet events
   // XcbEventListener::reconfigure_window();


   // a.installNativeEventFilter(&xcb);

    return a.exec();
}
