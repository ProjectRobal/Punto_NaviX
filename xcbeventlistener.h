#pragma once
#ifndef XCBEVENTLISTENER_H
#define XCBEVENTLISTENER_H

#include <xcb/xcb.h>
#include <xcb/xcb_util.h>
#include <xcb/xcb_keysyms.h>
#include <QObject>
#include <QDebug>
#include <QAbstractNativeEventFilter>
#include "xevents_list.h"

class XcbEventListener : public QAbstractNativeEventFilter
{
protected:

    QObject *target; // a reference to x11 window manager widget

public:
    XcbEventListener(QObject *_target);

    bool nativeEventFilter(const QByteArray &eventType, void *message, long *) override;

    // a function to reconfigure application's root window to recive appropriate x11 events
    // call after the application window has been created
    static void reconfigure_window();

    static xcb_window_t get_root();

    // make window w listen for focus and eneter events
    static void make_window_listen(xcb_window_t w);

    static void set_input_focus(xcb_window_t w);

    static void grab_key(xcb_window_t w,uint16_t modifiers, xcb_keysym_t key,uint8_t mode= XCB_GRAB_MODE_ASYNC);

    static void grab_key(uint16_t modifiers, xcb_keysym_t key,uint8_t mode= XCB_GRAB_MODE_ASYNC);

    static void ungrab_key(xcb_window_t w,uint16_t modifiers, xcb_keysym_t key);

    static void ungrab_key(uint16_t modifiers, xcb_keysym_t key);

    static void grab_button(xcb_window_t w,uint8_t button,uint16_t modifires,uint16_t event_mask=XCB_EVENT_MASK_BUTTON_PRESS |
            XCB_EVENT_MASK_BUTTON_RELEASE,uint8_t mode=XCB_GRAB_MODE_ASYNC,xcb_window_t confine_to=XCB_NONE,uint8_t pointer_mode=XCB_NONE);

    static void grab_button(uint8_t button,uint16_t modifires,uint16_t event_mask=XCB_EVENT_MASK_BUTTON_PRESS |
            XCB_EVENT_MASK_BUTTON_RELEASE,uint8_t mode=XCB_GRAB_MODE_ASYNC,xcb_window_t confine_to=XCB_NONE,uint8_t pointer_mode=XCB_NONE);


    static void ungrab_button(xcb_window_t w,uint8_t button,uint16_t modifires);

    static void ungrab_button(uint8_t button,uint16_t modifires);

    static xcb_keysym_t keyCode_to_keySysym(xcb_keycode_t key,uint16_t c);

    ~XcbEventListener();
};

#endif // XCBEVENTLISTENER_H
