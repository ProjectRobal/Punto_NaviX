#include <QX11Info>
#include <QApplication>
#include "xcbeventlistener.h"


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
            {*/
               // qDebug()<<xcb_event_get_label(ev->response_type)<<" "<<XCB_EVENT_RESPONSE_TYPE(ev);

                //QApplication::postEvent(target,new XEvents(ev),Qt::HighEventPriority);
           /* }*/

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

            case XCB_UNMAP_NOTIFY:

                QApplication::postEvent(target,new UnmapNotifyXEvents(ev),Qt::HighEventPriority);

                break;

              case XCB_BUTTON_PRESS:

                QApplication::postEvent(target,new ButtonPressXEvents(ev),Qt::HighEventPriority);

                break;

            case XCB_BUTTON_RELEASE:

              QApplication::postEvent(target,new ButtonReleaseXEvents(ev),Qt::HighEventPriority);

              break;

             case XCB_KEY_PRESS:

                QApplication::postEvent(target,new PressKeyXEvent(ev),Qt::HighEventPriority);

                break;

            case XCB_KEY_RELEASE:

               QApplication::postEvent(target,new ReleaseKeyXEvent(ev),Qt::HighEventPriority);

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

xcb_window_t XcbEventListener::get_root()
{
    xcb_connection_t * dpy;
    xcb_screen_t * scre;

    dpy=QX11Info::connection();

    scre = xcb_setup_roots_iterator(xcb_get_setup(dpy)).data;

    return scre->root;
}

void XcbEventListener::make_window_listen(xcb_window_t w)
{
    uint32_t values[3];
    xcb_connection_t * dpy;
    //xcb_screen_t * scre;

    dpy=QX11Info::connection();

   // scre = xcb_setup_roots_iterator(xcb_get_setup(dpy)).data;

    values[0] = XCB_EVENT_MASK_ENTER_WINDOW | XCB_EVENT_MASK_FOCUS_CHANGE;
        xcb_change_window_attributes_checked(dpy, w,
                                             XCB_CW_EVENT_MASK, values);
}

void XcbEventListener::set_input_focus(xcb_window_t w)
{
    xcb_set_input_focus(QX11Info::connection(), XCB_INPUT_FOCUS_POINTER_ROOT, w,
                        XCB_CURRENT_TIME);
}

void XcbEventListener::grab_key(xcb_window_t w, uint16_t modifiers, xcb_keysym_t key, uint8_t mode)
{
    xcb_connection_t *c=QX11Info::connection();

    xcb_key_symbols_t* sym=xcb_key_symbols_alloc(c);

    xcb_keycode_t *k=xcb_key_symbols_get_keycode(sym,key);

    xcb_grab_key(c,0,w,modifiers,k[0],XCB_GRAB_MODE_ASYNC,mode);

    xcb_key_symbols_free(sym);

    free(k);
}

void XcbEventListener::grab_key(uint16_t modifiers, xcb_keysym_t key, uint8_t mode)
{


    XcbEventListener::grab_key(XcbEventListener::get_root(),modifiers,key,mode);
}

void XcbEventListener::ungrab_key(xcb_window_t w, uint16_t modifiers, xcb_keysym_t key)
{
    xcb_connection_t *c=QX11Info::connection();

    xcb_key_symbols_t* sym=xcb_key_symbols_alloc(c);

    xcb_keycode_t *k=xcb_key_symbols_get_keycode(sym,key);

    xcb_ungrab_key(c,k[0],w,modifiers);

    xcb_key_symbols_free(sym);

    free(k);
}

void XcbEventListener::ungrab_key(uint16_t modifiers, xcb_keysym_t key)
{
    XcbEventListener::ungrab_key(XcbEventListener::get_root(),modifiers,key);
}

void XcbEventListener::grab_button(xcb_window_t w, uint8_t button, uint16_t modifires, uint16_t event_mask, uint8_t mode, xcb_window_t confine_to, uint8_t pointer_mode)
{
    xcb_grab_button(QX11Info::connection(),0,w,event_mask,pointer_mode,mode,confine_to,XCB_NONE,button,modifires);
}

void XcbEventListener::grab_button(uint8_t button, uint16_t modifires, uint16_t event_mask, uint8_t mode, xcb_window_t confine_to, uint8_t pointer_mode)
{
     XcbEventListener::grab_button(XcbEventListener::get_root(),button,modifires,event_mask,mode,confine_to,pointer_mode);
}

void XcbEventListener::ungrab_button(xcb_window_t w, uint8_t button, uint16_t modifires)
{
    xcb_ungrab_button(QX11Info::connection(),button,w,modifires);
}

void XcbEventListener::ungrab_button(uint8_t button, uint16_t modifires)
{
    XcbEventListener::ungrab_button(XcbEventListener::get_root(),button,modifires);
}

xcb_keysym_t XcbEventListener::keyCode_to_keySysym(xcb_keycode_t key,uint16_t c)
{
xcb_key_symbols_t * sym=xcb_key_symbols_alloc(QX11Info::connection());

xcb_keysym_t sym_key=xcb_key_symbols_get_keysym(sym,key,c);

xcb_key_symbols_free(sym);

return sym_key;

}
