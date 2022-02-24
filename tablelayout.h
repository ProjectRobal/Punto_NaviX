#ifndef TABLELAYOUT_H
#define TABLELAYOUT_H


#include <QObject>
#include <QLayout>
#include <unordered_map>
#include <vector>
#include <memory>
#include <xwidget.h>

class TableLayout : public QLayout
{
protected:

     std::vector<QLayoutItem*> _widgets;

     // store row and column count, width is columns , height is rows
     uint32_t columns;
     uint32_t rows;

     // vertical and horizontal spacing
     uint32_t m_hSpace;
     uint32_t m_vSpcae;


public:

     typedef std::vector<QLayoutItem*>::iterator layout_ptr;

    TableLayout(QWidget* parent);

    TableLayout(uint32_t _rows,uint32_t _columns,QWidget* parent);

    void addItem(QLayoutItem *item) override;

    void addItem(QWidget *widget);

    void removeWidget(QWidget *widget);

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

    layout_ptr begin();

    layout_ptr end();

    void remove(layout_ptr ptr);

    void remove(uint32_t id);

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
