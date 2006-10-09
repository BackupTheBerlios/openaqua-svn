#ifndef __CoaApplicationWindow_h__
#define __CoaApplicationWindow_h__

#include <CoaMainWindow>
#include <CoaMakros>


class CoaWorkspace;



/**
@brief A Application Window class, meant to deal together with CoaWorkbench
*/
class CoaApplicationWindow : public CoaMainWindow
{
Q_OBJECT
public:
   explicit CoaApplicationWindow(const QString& objectName,  CoaWorkspace *const parent, Qt::WFlags flags = 0 );
   virtual ~CoaApplicationWindow();

   virtual void    setWindowTitle(const QString& windowTitle);

protected:
   //CoaWorkbench *const getWorkbench() const;
   //void workbench(CoaWorkbench *);


private:
   CoaWorkspace      * m_workspace;
   QString             m_windowTitle;

   COAMAKRO_NO_DEFAULT(CoaApplicationWindow);
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaApplicationWindow);
   COAMAKRO_NO_COMPARE(CoaApplicationWindow);

};

#endif //__CoaApplicationWindow_h__

