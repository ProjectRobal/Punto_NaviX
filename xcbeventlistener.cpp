#include "xcbeventlistener.h"
#include <QX11Info>
#include <QApplication>

XcbEventListener::XcbEventListener(QObject* _target)
{
    target=_target;
}

XcbEventListener::~XcbEventListener()
{

}

bool XcbEventListener::nativeEventFilter(const QByteArray &eventType, void *message, long *)
    {
    if(eventType=="xcb_generic_error_t")
    {
    qDebug()<<"Some errors!";
    }
     else   if (eventType == "xcb_generic_event_t") {
            xcb_generic_event_t* ev = static_cast<xcb_generic_event_t *>(message);
            //qDebug()<<ev->response_type;
           /*if((XCB_EVENT_RESPONSE_TYPE(ev)==XCB_MAP_REQUEST)||(XCB_EVENT_RESPONSE_TYPE(ev)==XCB_DESTROY_NOTIFY))
            {
                qDebug()<<xcb_event_get_label(ev->response_type)<<" "<<XCB_EVENT_RESPONSE_TYPE(ev);

                //QApplication::postEvent(target,new XEvents(ev),Qt::HighEventPriority);
            }*/

            switch(XCB_EVENT_RESPONSE_TYPE(ev))
            {
                case XCB_MAP_REQUEST:

                QApplication::postEvent(target,new MapRequestXEvent(ev),Qt::HighEventPriority);

                break;

                case XCB_DESTROY_NOTIFY:

                QApplication::postEvent(target,new DestroyNotifyXEvents(ev),Qt::HighEventPriority);

                break;

            case XCB_FOCUS_IN:

                QApplication::postEvent(target,new FocusInXEvents(ev),Qt::HighEventPriority);

                break;

            case XCB_FOCUS_OUT:

                QApplication::postEvent(target,new FocusOutXEvents(ev),Qt::HighEventPriority);

                break;

             case XCB_ENTER_NOTIFY:

                QApplication::postEvent(target,new EnterNotifyXEvents(ev),Qt::HighEventPriority);

                break;
            }

           // return true;

        }
        return false;
}

void XcbEventListener::reconfigure_window()
{
    uint32_t values[3];
    xcb_connection_t * dpy;
    xcb_screen_t * scre;

    values[0] = XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT
            | XCB_EVENT_MASK_STRUCTURE_NOTIFY
            | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY
            | XCB_EVENT_MASK_PROPERTY_CHANGE;

    dpy=QX11Info::connection();

    scre = xcb_setup_roots_iterator(xcb_get_setup(dpy)).data;

    xcb_change_window_attributes_checked(dpy, scre->root,
            XCB_CW_EVENT_MASK, values);


}

void XcbEventListener::make_window_listen(xcb_window_t w)
{
    uint32_t values[3];
    xcb_connection_t * dpy;
    xcb_screen_t * scre;

    dpy=QX11Info::connection();

    scre = xcb_setup_roots_iterator(xcb_get_setup(dpy)).data;

    values[0] = XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_FOCUS_CHANGE;
        xcb_change_window_attributes_checked(dpy, w,
                                             XCB_CW_EVENT_MASK, values);
}

void XcbEventListener::set_input_focus(xcb_window_t w)
{
    xcb_set_input_focus(QX11Info::connection(), XCB_INPUT_FOCUS_POINTER_ROOT, w,
                XCB_CURRENT_TIME);
}
