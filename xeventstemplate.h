#ifndef XEVENTSTEMPLATE_H
#define XEVENTSTEMPLATE_H


#define R_KEY 82

#define DELETE_KEY 0

#define BACKSPACE_KEY 8

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
    ENTER_NOTIFY,
    UNMAP_NOTIFY,
    BUTTON_PRESS,
    BUTTON_RELEASE,
    KEY_PRESS,
    KEY_RELEASE
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
