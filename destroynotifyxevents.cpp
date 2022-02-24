#include "destroynotifyxevents.h"


DestroyNotifyXEvents::DestroyNotifyXEvents(xcb_destroy_notify_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    event_window=event->event;
    window=event->window;
}

DestroyNotifyXEvents::DestroyNotifyXEvents(xcb_generic_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    xcb_destroy_notify_event_t *destroy=reinterpret_cast<xcb_destroy_notify_event_t*>(event);

    event_window=destroy->event;
    window=destroy->window;
}
