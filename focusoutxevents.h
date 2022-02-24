#ifndef FOCUSOUTXEVENTS_H
#define FOCUSOUTXEVENTS_H

#include "xeventstemplate.h"

class FocusOutXEvents : public QEvent, public XEventsTemplate
{
protected:

    xcb_window_t window;

public:
    const static Type TYPE = static_cast<Type>(XEVENTS::FOCUS_OUT);

    FocusOutXEvents(xcb_focus_out_event_t *event);

    FocusOutXEvents(xcb_generic_event_t *event);

    xcb_window_t getWindow()
    {
        return window;
    }
};

#endif // FOCUSOUTXEVENTS_H
