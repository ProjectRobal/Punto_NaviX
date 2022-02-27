#ifndef UNMAPNOTIFYXEVENTS_H
#define UNMAPNOTIFYXEVENTS_H

#include "xeventstemplate.h"

class UnmapNotifyXEvents : public QEvent, public XEventsTemplate
{
protected:

xcb_window_t parent;
xcb_window_t window;

public:
    const static Type TYPE = static_cast<Type>(XEVENTS::UNMAP_NOTIFY);
    UnmapNotifyXEvents(xcb_unmap_notify_event_t *event);

    UnmapNotifyXEvents(xcb_generic_event_t *event);

   xcb_window_t getRoot()
   {
       return parent;
   }

   xcb_window_t getClient()
   {
       return window;
   }
};

#endif // UNMAPNOTIFYXEVENTS_H
