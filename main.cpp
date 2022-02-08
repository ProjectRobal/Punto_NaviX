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
    XcbEventListener xcb;

    uint32_t values[3];
    xcb_connection_t * dpy;
    xcb_screen_t * scre;

    values[0] = XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT
            | XCB_EVENT_MASK_STRUCTURE_NOTIFY
            | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY
            | XCB_EVENT_MASK_PROPERTY_CHANGE;




    QApplication a(argc, argv);



    MainWindow w;
    w.resize(1024,720);
    w.show();



    dpy=QX11Info::connection();

    scre = xcb_setup_roots_iterator(xcb_get_setup(dpy)).data;

    xcb_change_window_attributes_checked(dpy, scre->root,
            XCB_CW_EVENT_MASK, values);

    a.installNativeEventFilter(&xcb);

    return a.exec();
}
