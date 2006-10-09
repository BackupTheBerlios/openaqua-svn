#ifndef __CoaToolWindow_h__
#define __CoaToolWindow_h__

#include <CoaMainWindow>
#include <CoaMakros>
#include <CoaString>
#include <CoaLabel>


class CoaWorkbench;
class CoaBorderLayout;
class CoaPushButton;
class CoaVBoxLayout;
class QHBoxLayout;


/**
@brief A Tool Window class, meant to deal together with CoaWorkbench
*/
class CoaToolWindow: public CoaMainWindow
{
    Q_OBJECT
public:
   explicit CoaToolWindow(const CoaString& objectName,  CoaWorkbench *const parent, Qt::WFlags flags = 0 );
   virtual ~CoaToolWindow();

   CoaWorkbench *const  workbench() const;

   void addButton(CoaPushButton *const button);
   void addButtonStretch();

protected:


private:

   CoaWorkbench       * const m_workbench;
   CoaString                 m_windowTitle;

   COAMAKRO_NO_DEFAULT(CoaToolWindow);
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaToolWindow);
   COAMAKRO_NO_COMPARE(CoaToolWindow);

};

#endif // __CoaToolWindow_h__
