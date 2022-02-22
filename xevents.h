#ifndef XEVENTS_H
#define XEVENTS_H

#include "xeventstemplate.h"


class XEvents : public QEvent, public XEventsTemplate
{
protected:

    uint8_t response_type;

public:
    const static Type TYPE = static_cast<Type>(XEVENT_ID);
    explicit XEvents(xcb_generic_event_t *ev);




    ~XEvents();



};



#endif // XEVENTS_H
