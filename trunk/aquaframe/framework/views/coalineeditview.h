#ifndef __CoaLineEditView_h__
#define __CoaLineEditView_h__

#include <CoaAbstractItemView>
#include <CoaItemDelegate>

#include <QRegion>

class CoaLineEdit;
class CoaLabel;

class CoaLineEditViewDelegate : public CoaItemDelegate
{
Q_OBJECT
public:
   explicit CoaLineEditViewDelegate(QObject *parent = 0);
   virtual ~CoaLineEditViewDelegate();
   virtual QWidget *createEditor    (QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
   virtual void setEditorData       (QWidget *editor, const QModelIndex &index) const;
   virtual void setModelData        (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
   virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};




class Q_GUI_EXPORT CoaLineEditView: public CoaAbstractItemView {
Q_OBJECT
public:
   CoaLineEditView(QWidget *const parent = 0);
   virtual ~CoaLineEditView();

   virtual QModelIndex indexAt ( const QPoint & p ) const;
   virtual void scrollTo ( const QModelIndex & index, ScrollHint hint = EnsureVisible );
   virtual QRect visualRect ( const QModelIndex & index ) const;
   virtual void setRootIndex ( const QModelIndex & index );
   virtual void setModel ( QAbstractItemModel * model );
   void setFixColumn(const int column);
   void setFixRow(const int row);
   const int fixColumn();
   const int fixRow();
   
public slots:
   void setCurrentIndex ( const QModelIndex & index );

protected slots:
   virtual void currentChanged ( const QModelIndex & current, const QModelIndex & previous );
   virtual void dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight );
   virtual void rowsInserted(const QModelIndex &parent, int start, int end);


protected:
   virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
   virtual void paintEvent(QPaintEvent *e);
   virtual void resizeEvent ( QResizeEvent * e );
   virtual void mouseReleaseEvent(QMouseEvent *e);
   virtual void scrollContentsBy(int dx, int dy);

   virtual int horizontalOffset () const;
   virtual int verticalOffset () const;

   virtual bool isIndexHidden ( const QModelIndex & index ) const;
   virtual void setSelection ( const QRect & rect, QItemSelectionModel::SelectionFlags flags );
   virtual QRegion visualRegionForSelection ( const QItemSelection & selection ) const;


   QRect itemRect(const QModelIndex &index) const;
private:
   virtual QModelIndex moveCursor ( CursorAction cursorAction, Qt::KeyboardModifiers modifiers );
   int m_fixColumn;
   int m_fixRow;

};




#endif //__CoaLineEditView_h__


