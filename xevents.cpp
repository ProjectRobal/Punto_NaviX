#include "xevents.h"
#include <QDebug>

XEvents::XEvents(xcb_generic_event_t *ev)
    : QEvent(TYPE),
      XEventsTemplate(ev->response_type)
{
    //event=(xcb_generic_event_t*)calloc(1,sizeof (xcb_generic_event_t));


}

XEvents::~XEvents()
{

}
