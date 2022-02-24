#include "enternotifyxevents.h"


EnterNotifyXEvents::EnterNotifyXEvents(xcb_enter_notify_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    root_pos.setX(event->root_x);
    root_pos.setY(event->root_y);

    window_pos.setX(event->event_x);
    window_pos.setY(event->event_y);

    window=event->event;
    root=event->root;
    child=event->child;
}

EnterNotifyXEvents::EnterNotifyXEvents(xcb_generic_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    xcb_enter_notify_event_t *_event=reinterpret_cast<xcb_enter_notify_event_t*>(event);

    root_pos.setX(_event->root_x);
    root_pos.setY(_event->root_y);

    window_pos.setX(_event->event_x);
    window_pos.setY(_event->event_y);

    window=_event->event;
    root=_event->root;
    child=_event->child;
}
