#include "focusinxevents.h"

FocusInXEvents::FocusInXEvents(xcb_focus_in_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    window=event->event;
}

FocusInXEvents::FocusInXEvents(xcb_generic_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    xcb_focus_in_event_t *_event=reinterpret_cast<xcb_focus_in_event_t*>(event);

    window=_event->event;
}
