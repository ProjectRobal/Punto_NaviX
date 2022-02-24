#ifndef DESTROYNOTIFYXEVENTS_H
#define DESTROYNOTIFYXEVENTS_H

#include "xeventstemplate.h"

class DestroyNotifyXEvents : public QEvent, public XEventsTemplate
{
protected:

xcb_window_t event_window;
xcb_window_t window;

public:
const static Type TYPE = static_cast<Type>(XEVENTS::DESTROY_NOTIFY);

    DestroyNotifyXEvents(xcb_destroy_notify_event_t *event);

    DestroyNotifyXEvents(xcb_generic_event_t *event);

    xcb_window_t getEventWindow()
    {
        return event_window;
    }

    xcb_window_t getClient()
    {
        return window;
    }
};

#endif // DESTROYNOTIFYXEVENTS_H
