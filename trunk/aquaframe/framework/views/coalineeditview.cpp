#include "coalineeditview.h"
#include <CoaDebug>

#include <CoaLineEdit>
#include <QHBoxLayout>


CoaLineEditViewDelegate::CoaLineEditViewDelegate(QObject *parent)
: CoaItemDelegate(parent)
{
   BEGIN;
}


CoaLineEditViewDelegate::~CoaLineEditViewDelegate()
{
   BEGIN;
}



QWidget *CoaLineEditViewDelegate::createEditor    (QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   BEGIN;
   Q_UNUSED(option);
   if (! index.isValid()) return 0;

   CoaLineEdit *editor = new CoaLineEdit(parent);
   assert(editor);

   editor->installEventFilter(const_cast<CoaLineEditViewDelegate*>(this));

   connect (editor, SIGNAL(activated (int)),       editor, SLOT (emitDataChanged()) );
   connect (editor, SIGNAL(dataChanged(QWidget*)), this,   SIGNAL(commitData ( QWidget *)) );

   return editor;

}


void CoaLineEditViewDelegate::setEditorData       (QWidget *editor, const QModelIndex &index) const
{
   BEGIN;

   //some checks
   assert(editor);
   if (editor == 0)      return;
   if (!index.isValid()) return;

   CoaLineEdit *e = static_cast<CoaLineEdit*>(editor);
   if (e == 0) return;

   e->setText(index.model()->data(index, Qt::DisplayRole).toString());
}


void CoaLineEditViewDelegate::setModelData        (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
   BEGIN;

   assert(editor);
   assert(model);

   if (editor == 0) return;
   if (model  == 0) return;

   CoaLineEdit *e = static_cast<CoaLineEdit*>(editor);
   if (e == 0) return;
   model->setData(index, e->text());

}


void CoaLineEditViewDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   BEGIN;
   Q_UNUSED(index);

   //some checks
   assert(editor);
   if (editor == 0)      return;

   editor->setGeometry(option.rect);

}




CoaLineEditView::CoaLineEditView(QWidget *const parent)
: CoaAbstractItemView(parent)
, m_fixColumn(-1)
, m_fixRow(-1)
{
   BEGIN;
   setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   horizontalScrollBar()->setRange(0, 0);
   verticalScrollBar()->setRange(0, 0);


   //setItemDelegate(new CoaLineEditViewDelegate(this));
   //m_lineedit = new CoaLineEdit(this);
   //m_lineedit->resize(size());
   //connect(this, SIGNAL(), m_lineedit, SLOT());
   //m_lineedit->setText("foobar");
   //m_lineedit->setReadOnly(true);

}


CoaLineEditView::~CoaLineEditView()
{
   BEGIN;
}


/**
@brief Set the column for all used indicies

Given you want to share Model with a QTreeView / QTableView and a CoaLineEditView
can you set the Model Index for this View to a fix value.

Independent from the selected row would this item show (for example) the
first row.

@param set QModelIndex.column() to a fix value, -1 turns off

@see setFixColumn(const int row)
@see setFixRow(const int row)
@see fixRow()
@see fixColumn()
*/
void CoaLineEditView::setFixColumn(const int column)
{
   m_fixColumn = column;
}


/**
@brief Set the column for all used indicies

Given you want to share Model with a QTreeView / QTableView and a CoaLineEditView
can you set the Model Index for this View to a fix value.

Independent from the selected row would this item show (for example) the
first row.

@param set QModelIndex.column() to a fix value, -1 turns off

@see setFixColumn(const int row)
@see setFixRow(const int row)
@see fixRow()
@see fixColumn()
*/
void CoaLineEditView::setFixRow(const int row)
{
   m_fixRow = row;
}


/**
@brief Set the column for all used indicies

Given you want to share Model with a QTreeView / QTableView and a CoaLineEditView
can you set the Model Index for this View to a fix value.

Independent from the selected row would this item show (for example) the
first row.

@param set QModelIndex.column() to a fix value, -1 turns off

@see setFixColumn(const int row)
@see setFixRow(const int row)
@see fixRow()
@see fixColumn()
*/
const int CoaLineEditView::fixColumn()
{
   return m_fixColumn;
}


/**
@brief Set the column for all used indicies

Given you want to share Model with a QTreeView / QTableView and a CoaLineEditView
can you set the Model Index for this View to a fix value.

Independent from the selected row would this item show (for example) the
first row.

@param set QModelIndex.column() to a fix value, -1 turns off

@see setFixColumn(const int row)
@see setFixRow(const int row)
@see fixRow()
@see fixColumn()
*/
const int CoaLineEditView::fixRow()
{
   return m_fixRow;
}


void CoaLineEditView::setCurrentIndex ( const QModelIndex & index )
{
   if (index.isValid() && model() != 0) {
      int row = m_fixRow;
      int col = m_fixColumn;
      if (row == -1) row = index.row();
      if (col == -1) row = index.column();
      const QModelIndex myIndex = model()->index(row, col, index.parent());
      CoaAbstractItemView::setCurrentIndex(myIndex);
   } else {
      CoaAbstractItemView::setCurrentIndex(index);
   }
}



/**
Method simply returns the rootIndex() since the View can show only one item.
*/
QModelIndex CoaLineEditView::indexAt ( const QPoint & p ) const
{
   //BEGIN;
   Q_UNUSED(p);
   return currentIndex();
}



void CoaLineEditView::scrollTo ( const QModelIndex & index, ScrollHint hint )
{
   BEGIN;
   Q_UNUSED(index);
   Q_UNUSED(hint);
   ERR("CoaLineEditView::scrollTo called, but this method doesn't do any usefull");
   return;

   QRect area = viewport()->rect();
   QRect rect = visualRect(index);

   if (rect.left() < area.left())
        horizontalScrollBar()->setValue(
            horizontalScrollBar()->value() + rect.left() - area.left());
   else if (rect.right() > area.right())
        horizontalScrollBar()->setValue(
            horizontalScrollBar()->value() + qMin(
                rect.right() - area.right(), rect.left() - area.left()));

   if (rect.top() < area.top())
        verticalScrollBar()->setValue(
            verticalScrollBar()->value() + rect.top() - area.top());
   else if (rect.bottom() > area.bottom())
        verticalScrollBar()->setValue(
            verticalScrollBar()->value() + qMin(
                rect.bottom() - area.bottom(), rect.top() - area.top()));
}


/*
    Returns the rectangle of the item at position \a index in the
    model. The rectangle is in contents coordinates.
*/
QRect CoaLineEditView::itemRect(const QModelIndex &index) const
{
   BEGIN;
   if (!index.isValid())
      RETURN(QRect());


   RETURN(viewport()->rect());
}

QRect CoaLineEditView::visualRect ( const QModelIndex & index ) const
{
   BEGIN;
   QRect rect = itemRect(index);
   if (rect.isValid()){
        return QRect(rect.left() - horizontalScrollBar()->value(),
                     rect.top() - verticalScrollBar()->value(),
                     rect.width(), rect.height());
   } else {
        return rect;
   }
}

void CoaLineEditView::setRootIndex ( const QModelIndex & index )
{
   BEGIN;

   INF(QString("QModelIndex(row=%1, col=%2)").arg(index.row()).arg(index.column()));

   if (index.isValid() && model() != 0) {
      int row = m_fixRow;
      int col = m_fixColumn;
      if (row == -1) row = index.row();
      if (col == -1) row = index.column();
      const QModelIndex myIndex = model()->index(row, col, index.parent());
      CoaAbstractItemView::setRootIndex (index);
   } else {
      CoaAbstractItemView::setRootIndex (index);
   }
}


void CoaLineEditView::setModel ( QAbstractItemModel * model )
{
   BEGIN;
   CoaAbstractItemView::setModel (model);
}

void CoaLineEditView::currentChanged ( const QModelIndex & current, const QModelIndex & previous )
{
   BEGIN;
   Q_UNUSED(current);
   Q_UNUSED(previous);
   viewport()->update();
}

void CoaLineEditView::dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight )
{
   BEGIN;
   CoaAbstractItemView::dataChanged(topLeft, bottomRight);
   viewport()->update();
}


bool CoaLineEditView::edit(const QModelIndex &index, EditTrigger trigger, QEvent *event)
{
   BEGIN;
   return CoaAbstractItemView::edit(index, trigger, event);
}

void CoaLineEditView::mouseReleaseEvent(QMouseEvent *e)
{
    QAbstractItemView::mouseReleaseEvent(e);
    //selectionRect = QRect();
    viewport()->update();
}

void CoaLineEditView::paintEvent(QPaintEvent *e)
{
   //BEGIN;
   QStyleOptionViewItem option = viewOptions();
   QPainter painter(viewport()); //get the viewport widget
   QRect area = e->rect();
   painter.fillRect(area, option.palette.base()); //makes the background??

   //const QPoint offset = QPoint(-83, -34);//scrollDelayOffset();
   const QPoint offset = QPoint(0, 0);//scrollDelayOffset();
   const QModelIndex current = currentIndex();
   const QAbstractItemDelegate *delegate = itemDelegate();
   const QItemSelectionModel *selections = selectionModel();
   const bool focus = (hasFocus() || viewport()->hasFocus()) && current.isValid();
   //const QPalette::ColorGroup cg = (option.state & QStyle::State_Enabled
   //                                  ? QPalette::Normal : QPalette::Disabled);
   //const QBrush baseBrush = option.palette.brush(cg, QPalette::Base);
   //const QBrush alternateBrush = option.palette.brush(cg, QPalette::AlternateBase);
   //const QStyle::State state = option.state;


   if (current.isValid()){
      option.rect = visualRect(current).translated(offset);
      //option.rect = visualRect(current).translated(offset);
      //option.rect = geometry();
      //option.state = state;

      //set some colors depending on the model state and model flags
       if (selections && selections->isSelected(current))
            option.state |= QStyle::State_Selected;
       if ((model()->flags(current) & Qt::ItemIsEnabled) == 0)
            option.state &= ~QStyle::State_Enabled;
       if (focus ) {
            option.state |= QStyle::State_HasFocus;
            if (this->state() == EditingState)
                option.state |= QStyle::State_Editing;
       }

       delegate->paint(&painter, option, current);
   } else {
      CoaAbstractItemView::paintEvent(e);
   }
}


void CoaLineEditView::resizeEvent ( QResizeEvent * event )
{
   Q_UNUSED(event);
   updateGeometries();
}



void CoaLineEditView::scrollContentsBy(int dx, int dy)
{
   viewport()->scroll(dx, dy);
}



int CoaLineEditView::horizontalOffset () const
{
   BEGIN;
   return horizontalScrollBar()->value();
}



int CoaLineEditView::verticalOffset () const
{
   BEGIN;
   return verticalScrollBar()->value();
}



bool CoaLineEditView::isIndexHidden ( const QModelIndex & index ) const
{
   BEGIN;
   Q_UNUSED(index);
   RETURN(false);
}



QModelIndex CoaLineEditView::moveCursor ( CursorAction cursorAction, Qt::KeyboardModifiers modifiers )
{
   BEGIN;
   Q_UNUSED(cursorAction);
   Q_UNUSED(modifiers);
   ERR("This method isn't supported");
   RETURN(currentIndex());
}


/*
    Find the indices corresponding to the extent of the selection.
*/
void CoaLineEditView::setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags flags )
{
   BEGIN;
   Q_UNUSED(rect);
   QItemSelection selection(currentIndex (), currentIndex ());
   selectionModel()->select(selection, flags);
}



QRegion CoaLineEditView::visualRegionForSelection ( const QItemSelection & selection ) const
{
   //BEGIN;
   int ranges = selection.count();
   if (ranges == 0) return QRect();

   //Well, its stupid code since we use just one item
   //but anyway...
   int firstRow = selection.at(0).top();
   int lastRow = selection.at(0).top();

   for (int i = 0; i < ranges; ++i) {
        firstRow = qMin(firstRow, selection.at(i).top());
        lastRow = qMax(lastRow, selection.at(i).bottom());
    }

    QModelIndex firstItem = model()->index(qMin(firstRow, lastRow), 0, rootIndex());
    QModelIndex lastItem = model()->index(qMax(firstRow, lastRow), 0, rootIndex());

    QRect firstRect = visualRect(firstItem);
    QRect lastRect = visualRect(lastItem);

    return firstRect.unite(lastRect);
}

void CoaLineEditView::rowsInserted(const QModelIndex &parent, int start, int end)
{
   BEGIN;
   CoaAbstractItemView::rowsInserted (parent, start, end);
}

