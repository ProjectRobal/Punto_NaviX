#ifndef MAPREQUESTXEVENT_H
#define MAPREQUESTXEVENT_H

#include "QEvent"
#include "xeventstemplate.h"

class MapRequestXEvent : public QEvent,public XEventsTemplate
{
protected:

xcb_window_t parent;
xcb_window_t window;

public:
    const static Type TYPE = static_cast<Type>(XEVENTS::MAP_REQUEST);
    MapRequestXEvent(xcb_map_request_event_t *event);

    MapRequestXEvent(xcb_generic_event_t *event);

   xcb_window_t getRoot()
   {
       return parent;
   }

   xcb_window_t getClient()
   {
       return window;
   }
};

#endif // MAPREQUESTXEVENT_H
