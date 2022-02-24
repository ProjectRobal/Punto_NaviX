#include "tablelayout.h"
#include <QDebug>
#include <QWidgetItem>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

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

    if(_widgets.size()<(columns*rows))
    {

    _widgets.push_back(item);

    }
}

void TableLayout::addItem(QWidget *widget)
{
    if(_widgets.size()<(columns*rows))
    {

 _widgets.push_back(new QWidgetItem(widget));

    }
}

void TableLayout::removeWidget(QWidget *widget)
{
    auto item=std::find_if(_widgets.begin(),_widgets.end(),[widget](QLayoutItem *it)
    {
        return it->widget()==widget;

    });

    _widgets.erase(item);
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

    return _widgets.at(index);
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

    if(_widgets.empty())
    {
        return 0;
    }

    //qDebug()<<rect;

    const uint32_t count=_widgets.size();

    uint32_t col_c=std::min(count,columns); // columns count

    uint32_t row_c=(count/(columns+1))+1; // rows count

    if(row_c>rows)
    {
        row_c=rows;
    }

    uint32_t _w=rect.width()/col_c;

    uint32_t _h=rect.height()/row_c;

    uint32_t x=0;

    uint32_t y=0;

    QParallelAnimationGroup *group=new QParallelAnimationGroup(parent());

    for(auto key : _widgets)
    {


        if(y<rows)
        {

        QRect i_rect=QRect(QPoint((x*_w)+m_hSpace,(y*_h)+m_vSpcae),QSize(_w,_h));

       // qDebug()<<"elem: "<<x*y<<" "<<i_rect;


        QPropertyAnimation *anim=new QPropertyAnimation(key->widget(),"geometry");
        anim->setDuration(500);
        anim->setStartValue(key->geometry());
        anim->setEndValue(i_rect);

        // unfreeze widget when animation finished
        QObject::connect(anim,&QPropertyAnimation::finished,this,[this,key]()
        {
            key->widget()->setUpdatesEnabled(true);
        });

        group->addAnimation(anim);

        // freeze widget during animation
        key->widget()->setUpdatesEnabled(false);

        //key->setGeometry(i_rect);

        x++;

        }
    }

    group->start();


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

TableLayout::layout_ptr TableLayout::begin()
{
    return _widgets.begin();
}

TableLayout::layout_ptr TableLayout::end()
{
    return _widgets.end();
}

void TableLayout::remove(TableLayout::layout_ptr ptr)
{
    _widgets.erase(ptr);
}

void TableLayout::remove(uint32_t id)
{
    _widgets.erase(_widgets.begin()+id);
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
    for(auto p : _widgets)
    {
        delete p;
    }
    _widgets.clear();
}
