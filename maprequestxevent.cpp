#include "maprequestxevent.h"


MapRequestXEvent::MapRequestXEvent(xcb_map_request_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    parent=event->parent;

    window=event->window;
}

MapRequestXEvent::MapRequestXEvent(xcb_generic_event_t *event)
    : QEvent(TYPE),
      XEventsTemplate(event->response_type)
{
    xcb_map_request_event_t *map=reinterpret_cast<xcb_map_request_event_t*>(event);

    parent=map->parent;

    window=map->window;
}
