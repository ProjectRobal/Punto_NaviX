#ifndef ENTERNOTIFYXEVENTS_H
#define ENTERNOTIFYXEVENTS_H

#include "xeventstemplate.h"
#include <QPoint>

class EnterNotifyXEvents : public QEvent, public XEventsTemplate
{
protected:

    QPoint root_pos; // root window pointer position
    QPoint window_pos; // window local pointer position

    xcb_window_t window;
    xcb_window_t child;

    xcb_window_t root;

public:
    const static Type TYPE = static_cast<Type>(XEVENTS::ENTER_NOTIFY);

    EnterNotifyXEvents(xcb_enter_notify_event_t *event);

    EnterNotifyXEvents(xcb_generic_event_t *event);

    xcb_window_t getWindow()
    {
        return window;
    }

    xcb_window_t getChild()
    {
        return child;
    }

    xcb_window_t getRoot()
    {
        return root;
    }

    QPoint globalPos()
    {
        return root_pos;
    }

    QPoint localPos()
    {
        return window_pos;
    }
};

#endif // ENTERNOTIFYXEVENTS_H
