#include "buttonpressxevents.h"


ButtonPressXEvents::ButtonPressXEvents(xcb_button_press_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    root=event->root;
    _event=event->event;

    keyCode=event->detail;

    modifier=event->state;

    root_pos=QPoint(event->root_x,event->root_y);

    local_pos=QPoint(event->event_x,event->event_y);
}

ButtonPressXEvents::ButtonPressXEvents(xcb_generic_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    xcb_button_press_event_t * button=reinterpret_cast<xcb_button_press_event_t*>(event);

    root=button->root;
    _event=button->event;

    keyCode=button->detail;

    modifier=button->state;

    root_pos=QPoint(button->root_x,button->root_y);

    local_pos=QPoint(button->event_x,button->event_y);
}
