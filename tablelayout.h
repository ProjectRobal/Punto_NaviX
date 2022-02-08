#ifndef TABLELAYOUT_H
#define TABLELAYOUT_H

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
#undef Status
#undef None
#undef Unsorted

#include <QObject>
#include <QLayout>
#include <unordered_map>
#include <xwidget.h>

class TableLayout : public QLayout
{
protected:

     std::unordered_map<Window,QLayoutItem*> _widgets;

     // store row and column count, width is columns , height is rows
     uint32_t columns;
     uint32_t rows;

     // vertical and horizontal spacing
     uint32_t m_hSpace;
     uint32_t m_vSpcae;


public:
    TableLayout(QWidget* parent);

    TableLayout(uint32_t _rows,uint32_t _columns,QWidget* parent);

    void addItem(QLayoutItem *item) override;

    void addItem(QLayoutItem *item,const Window id);

    void addItem(QWidget *widget,const Window id);

    bool hasWindow(const Window id);

    void removeWindow(const Window id);

    int horizontalSpacing() const;

    int verticalSpacing() const;

    Qt::Orientations expandingDirections() const override;

    bool hasHeightForWidth() const override;

    int heightForWidth(int) const override;

    int count() const override;

    QLayoutItem *itemAt(int index) const override;

    QSize minimumSize() const override;

    void setGeometry(const QRect &rect) override;

    uint32_t doLayout(const QRect &rect,bool testOnly) const;

    QSize sizeHint() const override;

    QLayoutItem *takeAt(int index) override;

    XWidget *fromWindow(const Window win);

    void addColumn();

    void popColumn();

    void addRow();

    void popRow();

    void setColumn(uint32_t c);

    void setRow(uint32_t r);

    void addColumns(uint32_t c);

    void addRows(uint32_t r);

    uint32_t getRow() const;

    uint32_t getColumn() const;



    ~TableLayout();

};

#endif // TABLELAYOUT_H
