#pragma once
#ifndef X11MANAGER_H
#define X11MANAGER_H


#include <QWidget>
#include <QResizeEvent>
#include <unordered_map>
#include <vector>
#include <QBoxLayout>
#include <QAbstractEventDispatcher>
#include "xevents.h"
#include "xwidget.h"
#include "tablelayout.h"
#include "xcbeventlistener.h"
#include "maprequestxevent.h"

class X11Manager : public QWidget
{
    Q_OBJECT

// Display *display; // x window manager handle
// static bool wm_detected;

 bool isCreated;

 //const Window root_; // default root window

 TableLayout *layout; // a layout to store x widgets

 XcbEventListener *listener;


public:
    explicit X11Manager(QWidget *parent = nullptr);

    bool event(QEvent *event) override;

    void createWindow();

    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    // create a frame for the window
    void Frame(Window w, bool was_created_before_window_manager);

    // destroy the window
    void Unframe(Window w);

    static int onWMDetected(Display* display, XErrorEvent* e);

    static int onXError(Display* display, XErrorEvent* e);

 ~X11Manager();

public slots:


    // Event handlers.
      void OnCreateNotify(const XCreateWindowEvent& e);
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
      void OnKeyRelease(const XKeyEvent& e);

signals:

};

#endif // X11MANAGER_H
