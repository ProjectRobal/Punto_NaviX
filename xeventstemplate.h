#ifndef XEVENTSTEMPLATE_H
#define XEVENTSTEMPLATE_H

#include <xcb/xcb.h>
#include <xcb/xcb_util.h>
#include <QEvent>

#define XEVENT_ID QEvent::User+0x10

enum XEVENTS
{
    GENERAL=XEVENT_ID,
    MAP_REQUEST,
    DESTROY_NOTIFY,
    FOCUS_IN,
    FOCUS_OUT,
    ENTER_NOTIFY
};

class XEventsTemplate
{
protected:

    uint8_t response_type;

public:
    XEventsTemplate(uint8_t response);

    uint8_t responseType()
    {
        return response_type &  XCB_EVENT_RESPONSE_TYPE_MASK;
    }

    const char* ResponseString()
    {
        return xcb_event_get_label(response_type);
    }
};

#endif // XEVENTSTEMPLATE_H
