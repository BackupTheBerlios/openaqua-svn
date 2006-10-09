#ifndef __CoaToolsSqlBrowser_h_
#define __CoaToolsSqlBrowser_h_

#include <CoaToolWindow>
#include <CoaMakros>
#include <CoaString>

class CoaTextEdit;
class CoaTableView;
class CoaSqlConnectionWidget;
class CoaPushButton;



/**
@brief

The Object destroyes itself after closing.
*/
class CoaToolsSqlBrowser: public CoaToolWindow
{
Q_OBJECT

public:
   bool isValid() const;
   void setIsValid(const bool isValid);

public slots:
    bool exec();
    void slotShowTable(const CoaString &table);
    void addConnection();

    void slotSubmitButton();
    void slotClearButton();

private slots:
   void connectSignals();
   bool setInternalGuiPointers();

signals:
    void statusMessage(const CoaString &message);

private:
   bool                       m_isValid;
   CoaTextEdit               *m_sqlEdit;
   CoaTableView              *m_table;
   CoaSqlConnectionWidget    *m_connectionWidget;
   CoaPushButton             *m_submitButton;
   CoaPushButton             *m_clearButton;


   //CoaDebugSettingsModel *sqlModel;
   COAMAKRO_DEKLARE_SINGLETONMETHODS(CoaToolsSqlBrowser);
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaToolsSqlBrowser);
   COAMAKRO_NO_COMPARE(CoaToolsSqlBrowser);

};

#endif //__CoaToolsSqlBrowser_h_
