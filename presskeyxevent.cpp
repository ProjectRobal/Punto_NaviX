#include "presskeyxevent.h"
#include "xcbeventlistener.h"


PressKeyXEvent::PressKeyXEvent(xcb_key_press_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    root=event->root;
    _event=event->event;

    keyCode=XcbEventListener::keyCode_to_keySysym(event->detail,(event->state != 0));

    modifier=event->state;

    root_pos=QPoint(event->root_x,event->root_y);

    local_pos=QPoint(event->event_x,event->event_y);
}

PressKeyXEvent::PressKeyXEvent(xcb_generic_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    xcb_key_press_event_t * button=reinterpret_cast<xcb_key_press_event_t*>(event);

    root=button->root;
    _event=button->event;

    keyCode=XcbEventListener::keyCode_to_keySysym(button->detail,(button->state != 0));

    modifier=button->state;

    root_pos=QPoint(button->root_x,button->root_y);

    local_pos=QPoint(button->event_x,button->event_y);
}
