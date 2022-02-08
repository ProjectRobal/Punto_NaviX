#ifndef XWIDGET_H
#define XWIDGET_H

extern "C"
{
 #include <X11/Xlib.h>
}

#undef Bool
#undef CursorShape
#undef Expose
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange
#undef None
#undef Status
#undef Unsorted



#include <QWidget>
#include <QLayoutItem>
#include <QWindow>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QGridLayout>

class XWidget : public QWidget
{
    Q_OBJECT

    Window client;
    Display *d;
    QWindow *win;
    QGridLayout *layout;
    bool create_window;



public:
    explicit XWidget(Display* _d,Window _client,QWidget *parent=nullptr);

     void removeWindow();

      void createWindow();

      bool isWindowCreated();

    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent *event) override;



    ~XWidget() override;

signals:

};

#endif // XWIDGET_H
