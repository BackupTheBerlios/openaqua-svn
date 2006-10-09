#include "coaborderlayout.h"
#include <CoaDebug>

#include <QLayoutItem>

CoaBorderLayout::CoaBorderLayout(QWidget *parent, int margin, int spacing)
    : QLayout(parent)
{
   BEGIN;
   setMargin(margin);
   setSpacing(spacing);
}




CoaBorderLayout::CoaBorderLayout(int spacing)
{
   BEGIN;
   setSpacing(spacing);
}




CoaBorderLayout::~CoaBorderLayout()
{
   BEGIN;
   QLayoutItem *l;
   while ((l = takeAt(0))){
      delete l;
   }
}




void CoaBorderLayout::addItem(QLayoutItem *item)
{
   BEGIN;
   add(item, West);
}




void CoaBorderLayout::addWidget(QWidget *widget, Position position)
{
   BEGIN;
   add(new QWidgetItem(widget), position);
}


Qt::Orientations CoaBorderLayout::expandingDirections() const
{
   BEGIN;
   return Qt::Horizontal | Qt::Vertical;
}



bool CoaBorderLayout::hasHeightForWidth() const
{
   BEGIN;
   RETURN(false);
}



int CoaBorderLayout::count() const
{
   BEGIN;
   RETURN(list.size());
}



QLayoutItem *CoaBorderLayout::itemAt(int index) const
{
   BEGIN;
   ItemWrapper *wrapper = list.value(index);
   if (wrapper)
      return wrapper->item;
   else
      return 0;
}




QSize CoaBorderLayout::minimumSize() const
{
   BEGIN;
   return calculateSize(MinimumSize);
}




void CoaBorderLayout::setGeometry(const QRect &rect)
{
   BEGIN;
    ItemWrapper *center = 0;
    int eastWidth = 0;
    int westWidth = 0;
    int northHeight = 0;
    int southHeight = 0;
    int centerHeight = 0;
    int i;

    QLayout::setGeometry(rect);

    for (i = 0; i < list.size(); ++i) {
        ItemWrapper *wrapper = list.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == North) {
            item->setGeometry(QRect(rect.x(), northHeight, rect.width(),
                                    item->sizeHint().height()));

            northHeight += item->geometry().height() + spacing();
        } else if (position == South) {
            item->setGeometry(QRect(item->geometry().x(),
                                    item->geometry().y(), rect.width(),
                                    item->sizeHint().height()));

            southHeight += item->geometry().height() + spacing();

            item->setGeometry(QRect(rect.x(),
                              rect.y() + rect.height() - southHeight + spacing(),
                              item->geometry().width(),
                              item->geometry().height()));
        } else if (position == Center) {
            center = wrapper;
        }
    }

    centerHeight = rect.height() - northHeight - southHeight;

    for (i = 0; i < list.size(); ++i) {
        ItemWrapper *wrapper = list.at(i);
        QLayoutItem *item = wrapper->item;
        Position position = wrapper->position;

        if (position == West) {
            item->setGeometry(QRect(rect.x() + westWidth, northHeight,
                                    item->sizeHint().width(), centerHeight));

            westWidth += item->geometry().width() + spacing();
        } else if (position == East) {
            item->setGeometry(QRect(item->geometry().x(), item->geometry().y(),
                                    item->sizeHint().width(), centerHeight));

            eastWidth += item->geometry().width() + spacing();

            item->setGeometry(QRect(
                              rect.x() + rect.width() - eastWidth + spacing(),
                              northHeight, item->geometry().width(),
                              item->geometry().height()));
        }
    }

    if (center)
        center->item->setGeometry(QRect(westWidth, northHeight,
                                        rect.width() - eastWidth - westWidth,
                                        centerHeight));
}




QSize CoaBorderLayout::sizeHint() const
{
   BEGIN;
    return calculateSize(SizeHint);
}




QLayoutItem *CoaBorderLayout::takeAt(int index)
{
   BEGIN;
   if (index >= 0 && index < list.size()) {
      ItemWrapper *layoutStruct = list.takeAt(index);
      return layoutStruct->item;
   }
   return 0;
}




void CoaBorderLayout::add(QLayoutItem *item, Position position)
{
   BEGIN;
   list.append(new ItemWrapper(item, position));
}


void CoaBorderLayout::addLayout(QLayout *layout, Position position)
{
   BEGIN;
   list.append(new ItemWrapper(layout, position));
}




QSize CoaBorderLayout::calculateSize(SizeType sizeType) const
{
   BEGIN;
    QSize totalSize;

    for (int i = 0; i < list.size(); ++i) {
        ItemWrapper *wrapper = list.at(i);
        Position position = wrapper->position;
        QSize itemSize;

        if (sizeType == MinimumSize)
            itemSize = wrapper->item->minimumSize();
        else // (sizeType == SizeHint)
            itemSize = wrapper->item->sizeHint();

        if (position == North || position == South || position == Center)
            totalSize.rheight() += itemSize.height();

        if (position == West || position == East || position == Center)
            totalSize.rwidth() += itemSize.width();
    }
    return totalSize;
}
