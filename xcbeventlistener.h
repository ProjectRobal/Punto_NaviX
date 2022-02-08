#ifndef XCBEVENTLISTENER_H
#define XCBEVENTLISTENER_H

#include <xcb/xcb.h>
#include <xcb/xcb_util.h>
#include <QObject>
#include <QDebug>
#include <QAbstractNativeEventFilter>

class XcbEventListener : public QAbstractNativeEventFilter
{
public:
    XcbEventListener();

    bool nativeEventFilter(const QByteArray &eventType, void *message, long *) override
        {
            if (eventType == "xcb_generic_event_t") {
                xcb_generic_event_t* ev = static_cast<xcb_generic_event_t *>(message);
                //qDebug()<<ev->response_type;
               /* if(XCB_EVENT_RESPONSE_TYPE(ev)==XCB_MAP_REQUEST)
                {
                    qDebug()<<"MapRequest";
                }*/

               qDebug()<<xcb_event_get_label(ev->response_type)<<" "<<XCB_EVENT_RESPONSE_TYPE(ev);

               // return true;

            }
            return false;
        }

    ~XcbEventListener();
};

#endif // XCBEVENTLISTENER_H
