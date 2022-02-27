#ifndef RELEASEKEYXEVENT_H
#define RELEASEKEYXEVENT_H

#include "xeventstemplate.h"
#include <QPoint>

class ReleaseKeyXEvent : public QEvent , public XEventsTemplate
{
protected:

xcb_window_t root;
xcb_window_t _event;

xcb_button_t keyCode;

uint16_t modifier;

QPoint root_pos;
QPoint local_pos;

public:
    const static Type TYPE = static_cast<Type>(XEVENTS::KEY_RELEASE);

    ReleaseKeyXEvent(xcb_key_release_event_t *event);

    ReleaseKeyXEvent(xcb_generic_event_t *event);

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

#endif // RELEASEKEYXEVENT_H
