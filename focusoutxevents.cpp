#include "focusoutxevents.h"


FocusOutXEvents::FocusOutXEvents(xcb_focus_out_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    window=event->event;
}

FocusOutXEvents::FocusOutXEvents(xcb_generic_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    xcb_focus_out_event_t* _event=reinterpret_cast<xcb_focus_out_event_t*>(event);

    window=_event->event;
}
