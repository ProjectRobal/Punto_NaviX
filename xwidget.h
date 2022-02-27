#pragma once
#ifndef XWIDGET_H
#define XWIDGET_H

#include <xcb/xcb.h>
#include <xcb/xcb_util.h>

#include <QWidget>
#include <QWindow>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QGridLayout>
#include <QLabel>
#include "tablelayout.h"



class XWidget : public QWidget
{
    Q_OBJECT

    xcb_window_t client;
    QWindow *win;
    QGridLayout *layout;
    bool create_window;
    bool active;
    TableLayout::layout_ptr ptr;
    QLabel *label;

protected slots:

    void set_active();


public:
    explicit XWidget(xcb_window_t _client,QWidget *parent=nullptr);

    void setPtr( TableLayout::layout_ptr _ptr);

    void setPtr(TableLayout::layout_ptr _ptr,uint32_t index);

     TableLayout::layout_ptr getPtr();

     void removeWindow();

      void createWindow();

      bool isWindowCreated();

    void paintEvent(QPaintEvent *event) override;


    void FocusIn();

    void FocusOut();

    void dropActive();

    xcb_window_t getClient()
    {
        return client;
    }



    ~XWidget() override;


};

Q_DECLARE_METATYPE(XWidget*);

#endif // XWIDGET_H
