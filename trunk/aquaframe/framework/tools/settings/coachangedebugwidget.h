#ifndef __CoaChangeDebugWidget_h_
#define __CoaChangeDebugWidget_h_


#include <CoaSettingsWidget>
#include <CoaItemDelegate>
#include <CoaItemSelection>
#include <CoaItemEditorFactory>



class SelectDebugLevelDelegate : public CoaItemDelegate
{
Q_OBJECT
public:
   explicit SelectDebugLevelDelegate(QObject *parent = 0);
   virtual ~SelectDebugLevelDelegate();
   virtual QWidget *createEditor    (QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
   virtual void setEditorData       (QWidget *editor, const QModelIndex &index) const;
   virtual void setModelData        (QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
   virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};







class CoaDebugSettingsModel;
class CoaSettingsWidgetChangeDebug: public CoaSettingsWidget
{
Q_OBJECT

public:
   CoaSettingsWidgetChangeDebug ( QWidget * const parent = 0, Qt::WFlags f = 0 );
   virtual ~CoaSettingsWidgetChangeDebug();

   virtual bool canApplyDefaults() const;

public slots:
   void slotSelectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );
   virtual bool applyChanges();
   virtual bool applyDefaults();


private slots:
   void slotSetDebugEnabled(bool);
   void slotShowTimeInOutput(bool);

   void slotSetLevelOff();
   void slotSetLevelErr();
   void slotSetLevelWrn();
   void slotSetLevelInf();
   void slotSetLevelDbg();


   void slotEnableAllPersistentEditors();

private:
   void loadModel();
   void initMainButtons();
   void initDefaultModeButtons();
   void initTableView();


   CoaDebugSettingsModel *actionModel;

};


#endif //__CoaChangeDebugWidget_h_

