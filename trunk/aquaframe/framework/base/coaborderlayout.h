#ifndef __CoaBorderLayout_h__
#define __CoaBorderLayout_h__

#include <QLayout>
#include <QRect>
//#include <QWidgetItem>

class CoaBorderLayout : public QLayout
{
public:
    enum Position { West, North, South, East, Center };

    CoaBorderLayout(QWidget *parent, int margin = 0, int spacing = -1);
    CoaBorderLayout(int spacing = -1);
    virtual ~CoaBorderLayout();

    void addItem(QLayoutItem *item);
    void addWidget(QWidget *widget, Position position);
    void addLayout(QLayout *layout, Position position);
    Qt::Orientations expandingDirections() const;
    bool hasHeightForWidth() const;
    int count() const;
    QLayoutItem *itemAt(int index) const;
    QSize minimumSize() const;
    void setGeometry(const QRect &rect);
    QSize sizeHint() const;
    QLayoutItem *takeAt(int index);

    void add(QLayoutItem *item, Position position);

private:
    struct ItemWrapper
    {
        ItemWrapper(QLayoutItem *i, Position p) {
            item = i;
            position = p;
        }

        QLayoutItem *item;
        Position position;
    };

    enum SizeType { MinimumSize, SizeHint };
    QSize calculateSize(SizeType sizeType) const;

    CoaList<ItemWrapper *> list;
};

#endif //__CoaBorderLayout_h__
