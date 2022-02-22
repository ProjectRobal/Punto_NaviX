#pragma once
#ifndef XCBEVENTLISTENER_H
#define XCBEVENTLISTENER_H

#include <xcb/xcb.h>
#include <xcb/xcb_util.h>
#include <QObject>
#include <QDebug>
#include <QAbstractNativeEventFilter>
#include "xevents.h"
#include "maprequestxevent.h"


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

    ~XcbEventListener();
};

#endif // XCBEVENTLISTENER_H
