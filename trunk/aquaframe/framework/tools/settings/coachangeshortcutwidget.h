#ifndef __CoaSettingsWidgetChangeShortcut_h__
#define __CoaSettingsWidgetChangeShortcut_h__

#include <CoaSettingsWidget>
#include <CoaLineEdit>
#include <CoaItemSelection>
#include <CoaItemDelegate>

#include <QStyleOptionViewItem>

class CoaActionViewModel;



/**
@brief

The Object destroyes itself after closing.
*/
class CoaSettingsWidgetChangeShortcut: public CoaSettingsWidget
{
Q_OBJECT

private:

   class KeyRecordEdit: public CoaLineEdit
   {
      public:
      explicit KeyRecordEdit (QWidget *parent = 0);
   protected:
      virtual void keyPressEvent ( QKeyEvent * e );
   };


   class KeyRecordDelegate : public CoaItemDelegate
   {
   public:
      explicit KeyRecordDelegate(QObject *parent = 0);
      virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
      virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
      virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
      virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
   };


public:
   CoaSettingsWidgetChangeShortcut ( QWidget * const parent = 0, Qt::WFlags f = 0 );
   virtual ~CoaSettingsWidgetChangeShortcut();
   virtual bool canApplyDefaults() const;

public slots:
   virtual bool applyChanges();
   virtual bool applyDefaults();
   void slotSelectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );

private slots:
   void loadActions();

private:
   CoaTreeView          *m_actionView;
   CoaActionViewModel   *m_actionModel;

};

#endif //__CoaSettingsWidgetChangeShortcut_h__
