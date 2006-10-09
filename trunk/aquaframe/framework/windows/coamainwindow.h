#ifndef __CoaMainWindow_h__
#define __CoaMainWindow_h__

#include <CoaMakros>

#include <QMainWindow>
#include <QString>
#include <QRect>


class CoaWorkbench;

class QCloseEvent;


/**
@The base class for Coa Windows

<H1>Dirty Flag</H1>

All CoaWindows have an "dirty flag". Use QMainWindow::setWindowModified(bool) the enable / disable that flag.
If the flag is set on "true" a message box will appear if you try to close that window.

The Message box ask "Do you want to save the changes you made to \"%1\" before closing?". Whereas %1 will
replaced by string saveTarget(). By default the message box will show a message

If you modify the save target the window title will be replaced too. For that the windowTitle needs a
special form: "fooo %1 [*]" The %1 will be replaced by the saveTarget(). The [*] will be shown if the
window has unsaved changes

*/
class CoaMainWindow : public QMainWindow
{
Q_OBJECT

public:
   explicit CoaMainWindow (const QString& objectName,  QWidget * parent = 0, Qt::WFlags flags = 0 );
   virtual ~CoaMainWindow();

   virtual void readSettings();
   virtual void writeSettings();

   virtual void saveChanges();
   virtual QSize sizeHint () const;
   virtual void setSizeHint(const QSize& sizeHint);

protected:
   virtual void closeEvent(QCloseEvent *ev);


private:
   QSize   m_sizeHint;

   COAMAKRO_NO_DEFAULT(CoaMainWindow);
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaMainWindow);
   COAMAKRO_NO_COMPARE(CoaMainWindow);


};

#endif //__CoaMainWindow_h__
