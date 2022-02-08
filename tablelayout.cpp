#include "tablelayout.h"
#include <QDebug>
#include <QWidgetItem>

TableLayout::TableLayout(QWidget* parent)
    : QLayout(parent)
{
    rows=1;
    columns=1;
    m_hSpace=0;
    m_vSpcae=0;
}

TableLayout::TableLayout(uint32_t _rows, uint32_t _columns, QWidget *parent)
: QLayout(parent)
{
    if(_rows>0)
    {
    rows=_rows;
    }
    else
    {
        rows=1;
    }
    if(_columns>0)
    {
    columns=_columns;
    }
    else
    {
        columns=1;
    }

    m_hSpace=0;
    m_vSpcae=0;
}

void TableLayout::addItem(QLayoutItem *item)
{
    Q_UNUSED(item);
    qDebug()<<"Use addItem(QLayoutItem*,const Window) instead!";
}

void TableLayout::addItem(QLayoutItem *item, const Window id)
{
    _widgets.insert(std::pair<Window,QLayoutItem*>(id,item));
}

void TableLayout::addItem(QWidget *widget, const Window id)
{
 _widgets.insert(std::pair<Window,QLayoutItem*>(id,new QWidgetItem(widget)));
}

bool TableLayout::hasWindow(const Window id)
{
    return _widgets.count(id)>0;
}

void TableLayout::removeWindow(const Window id)
{
    if(_widgets.count(id)>0)
    {

        _widgets.erase(id);
    }
}

int TableLayout::horizontalSpacing() const
{
    return m_hSpace;
}

int TableLayout::verticalSpacing() const
{
    return m_vSpcae;
}

Qt::Orientations TableLayout::expandingDirections() const
{
    return 0;
}

bool TableLayout::hasHeightForWidth() const
{
    return false;
}

int TableLayout::heightForWidth(int width) const
{
    return doLayout(QRect(0,0,width,0),true);
}

int TableLayout::count() const
{
    return _widgets.size();
}

QLayoutItem *TableLayout::itemAt(int index) const
{
    if((_widgets.size()==0)||(_widgets.size()>=index)||(index<0))
    {
        return NULL;
    }
    auto iter=_widgets.begin();

    for(int i=0;i<index;i++)
    {
        iter++;
    }

    return iter->second;
}

QSize TableLayout::minimumSize() const
{
   /* QSize size;
       for (auto item : _widgets)
       {
           size = size.expandedTo(item.second->minimumSize());
       }

       const QMargins margins = contentsMargins();
       size += QSize(margins.left() + margins.right(), margins.top() + margins.bottom());*/
       return QSize(0,0);
}

void TableLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);

    doLayout(rect,false);
}

uint32_t TableLayout::doLayout(const QRect &rect,bool testOnly) const
{
    if(testOnly)
    {
        return rect.width();
    }

    qDebug()<<rect;



    uint32_t _w=rect.width()/columns;

    uint32_t _h=rect.height()/rows;

    uint32_t x=0;

    uint32_t y=0;

    for(auto key : _widgets)
    {
        QLayoutItem * item=key.second;

        if(y<rows)
        {

        QRect i_rect=QRect(QPoint((x*_w)+m_hSpace,(y*_h)+m_vSpcae),QSize(_w,_h));

        qDebug()<<"elem: "<<x*y<<" "<<i_rect;

        item->setGeometry(i_rect);

        x++;

        if(x>=columns)
        {
        x=0;
        y++;
        }
        }
        else
        {
            item->setGeometry(QRect(0,0,0,0));

        }


    }


    return rect.width();
}

QSize TableLayout::sizeHint() const
{
    return minimumSize();
}

QLayoutItem *TableLayout::takeAt(int index)
{
    if((index<0)||(index>=_widgets.size()))
    {
        return NULL;
    }

    return itemAt(index);
}

XWidget *TableLayout::fromWindow(const Window win)
{
    return reinterpret_cast<XWidget*>(_widgets[win]);
}

void TableLayout::addColumn()
{
    addColumns(1);
}

void TableLayout::popColumn()
{
    addColumns(-1);
}

void TableLayout::addRow()
{
    addRows(1);
}

void TableLayout::popRow()
{
    addRows(-1);
}

void TableLayout::setColumn(uint32_t c)
{
    if(c>0)
    {
    columns=c;
    }
    else
       {
        columns=1;
    }
}

void TableLayout::setRow(uint32_t r)
{
    if(r>0)
    {
    rows=r;
    }
    else
    {
    rows=1;
    }
}

void TableLayout::addColumns(uint32_t c)
{

    columns+=c;

    if(columns<=0)
    {
        columns=1;
    }
}

void TableLayout::addRows(uint32_t r)
{

        rows+=r;

       if(rows<=0)
       {
        rows=1;
       }
}

uint32_t TableLayout::getRow() const
{
    return rows;
}

uint32_t TableLayout::getColumn() const
{
    return columns;
}

TableLayout::~TableLayout()
{
    _widgets.clear();
}
