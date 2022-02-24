#ifndef XWIDGET_H
#define XWIDGET_H

#include <xcb/xcb.h>
#include <xcb/xcb_util.h>

#include <QWidget>
#include <QLayoutItem>
#include <QWindow>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QGridLayout>

class XWidget : public QWidget
{
    Q_OBJECT

    xcb_window_t client;
    QWindow *win;
    QGridLayout *layout;
    bool create_window;

protected slots:

    void set_active();


public:
    explicit XWidget(xcb_window_t _client,QWidget *parent=nullptr);

     void removeWindow();

      void createWindow();

      bool isWindowCreated();

    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent *event) override;


    void FocusIn();

    void FocusOut();

    void dropActive();

    xcb_window_t getClient()
    {
        return client;
    }



    ~XWidget() override;

signals:

};

#endif // XWIDGET_H
