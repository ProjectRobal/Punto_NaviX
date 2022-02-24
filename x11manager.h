#pragma once
#ifndef X11MANAGER_H
#define X11MANAGER_H


#include <QWidget>
#include <QResizeEvent>
#include <unordered_map>
#include <memory>
#include <vector>
#include <QBoxLayout>
#include <QAbstractEventDispatcher>
#include <QShortcut>
#include "xevents_list.h"
#include "xwidget.h"
#include "tablelayout.h"
#include "xcbeventlistener.h"

class X11Manager : public QWidget
{
    Q_OBJECT

// Display *display; // x window manager handle
// static bool wm_detected;

 //const Window root_; // default root window

 std::unordered_map<xcb_window_t,XWidget*> _widgets;

 TableLayout *layout; // a layout to store x widgets

 XcbEventListener *listener;

 // current active widget
 XWidget *focus;


public:
    explicit X11Manager(QWidget *parent = nullptr);

    bool event(QEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void setShortCuts();

    // create a frame for the window
    void Frame(xcb_window_t w);

    // destroy the window
    void Unframe(xcb_window_t w);

    void setActive(xcb_window_t w);

    void setFocusColor(xcb_window_t w);

    void removeFocusColor(xcb_window_t w);


 ~X11Manager();

public slots:

    void RemoveWindow();


    // Event handlers.
     /* void OnCreateNotify(const XCreateWindowEvent& e);
      void OnDestroyNotify(const XDestroyWindowEvent& e);
      void OnReparentNotify(const XReparentEvent& e);
      void OnMapNotify(const XMapEvent& e);
      void OnUnmapNotify(const XUnmapEvent& e);
      void OnConfigureNotify(const XConfigureEvent& e);
      void OnMapRequest(const XMapRequestEvent& e);
      void OnConfigureRequest(const XConfigureRequestEvent& e);
      void OnButtonPress(const XButtonEvent& e);
      void OnButtonRelease(const XButtonEvent& e);
      void OnMotionNotify(const XMotionEvent& e);
      void OnKeyPress(const XKeyEvent& e);
      void OnKeyRelease(const XKeyEvent& e);*/

signals:

};

#endif // X11MANAGER_H
