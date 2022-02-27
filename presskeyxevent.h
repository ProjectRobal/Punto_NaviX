#ifndef PRESSKEYXEVENT_H
#define PRESSKEYXEVENT_H

#include "xeventstemplate.h"
#include "QPoint"

class PressKeyXEvent : public QEvent,public XEventsTemplate
{
protected:

xcb_window_t root;
xcb_window_t _event;

uint16_t modifier;

xcb_button_t keyCode;

QPoint root_pos;
QPoint local_pos;

public:
    const static Type TYPE = static_cast<Type>(XEVENTS::KEY_PRESS);

    PressKeyXEvent(xcb_key_press_event_t *event);

    PressKeyXEvent(xcb_generic_event_t *event);

    uint16_t getMod()
    {
        return modifier;
    }


    xcb_window_t getRoot()
    {
        return root;
    }

    xcb_window_t getEvent()
    {
        return _event;
    }

    xcb_button_t getKey()
    {
        return keyCode;
    }

    QPoint GlobalPos()
    {
        return root_pos;
    }

    QPoint LocalPos()
    {
        return local_pos;
    }
};

#endif // PRESSKEYXEVENT_H
