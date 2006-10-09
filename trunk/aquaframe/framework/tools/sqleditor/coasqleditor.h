#ifndef __CoaToolsSqlEditor_h_
#define __CoaToolsSqlEditor_h_

#include <CoaToolWindow>
#include <CoaMakros>
#include <CoaString>


class CoaSqlConnectionWidget;
class CoaTableView;
class CoaToolButton;

/**
@brief

The Object destroyes itself after closing.
*/
class CoaToolsSqlEditor: public CoaToolWindow
{
Q_OBJECT

public:
   bool isValid() const;
   void setIsValid(const bool isValid);

public slots:

   void slotShowTable(const CoaString &table);
   void addConnection();

   void slotAddRecord();
   void slotRemRecord();

private:
   void connectSignals();
   bool setInternalGuiPointers();

signals:
    void statusMessage(const CoaString &message);

private:
   bool                    m_isValid;
   CoaTableView           *m_table;
   CoaPushButton          *m_btnAdd;
   CoaPushButton          *m_btnRem;
   CoaSqlConnectionWidget *m_connectionWidget;

   //CoaDebugSettingsModel *sqlModel;
   COAMAKRO_DEKLARE_SINGLETONMETHODS(CoaToolsSqlEditor);
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaToolsSqlEditor);
   COAMAKRO_NO_COMPARE(CoaToolsSqlEditor);

};

#endif //__CoaToolsSqlEditor_h_
