#ifndef BUTTONRELEASEXEVENTS_H
#define BUTTONRELEASEXEVENTS_H

#include "xeventstemplate.h"
#include <QPoint>

class ButtonReleaseXEvents : public QEvent, public XEventsTemplate
{
protected:

xcb_window_t root;
xcb_window_t _event;

xcb_button_t keyCode;

uint16_t modifier;

QPoint root_pos;
QPoint local_pos;

public:
    const static Type TYPE = static_cast<Type>(XEVENTS::BUTTON_RELEASE);

    ButtonReleaseXEvents(xcb_button_release_event_t *event);

    ButtonReleaseXEvents(xcb_generic_event_t *event);

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

#endif // BUTTONRELEASEXEVENTS_H
