#include "unmapnotifyxevents.h"



UnmapNotifyXEvents::UnmapNotifyXEvents(xcb_unmap_notify_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    parent=event->event;

    window=event->window;
}

UnmapNotifyXEvents::UnmapNotifyXEvents(xcb_generic_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    xcb_unmap_notify_event_t * _event=reinterpret_cast<xcb_unmap_notify_event_t*>(event);

    parent=_event->event;

    window=_event->window;
}
