#ifndef FOCUSINXEVENTS_H
#define FOCUSINXEVENTS_H

#include "xeventstemplate.h"


class FocusInXEvents : public QEvent, public XEventsTemplate
{
protected:

    xcb_window_t window;

public:
    const static Type TYPE = static_cast<Type>(XEVENTS::FOCUS_IN);

    FocusInXEvents(xcb_focus_in_event_t *event);

    FocusInXEvents(xcb_generic_event_t *event);

    xcb_window_t getWindow()
    {
        return  window;
    }
};

#endif // FOCUSINXEVENTS_H
