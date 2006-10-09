#ifndef __CQT_H__
#define __CQT_H__

#define QT_DLL
#define QT_THREAD_SUPPORT

// #pragma pack(8)

#define QT_NO_CAST_ASCII
#define QT_NO_ASCII_CAST

// Q4 Includes
#include <QAbstractItemModel>
#include <QAction>
#include <QApplication>
#include <QBitmap>
#include <QBoxLayout>
#include <QButtonGroup>
#include <QCheckBox>
#include <QCloseEvent>
#include <QCustomEvent>
#include <QColorDialog>
#include <QColorGroup>
#include <QConicalGradient>
#include <QComboBox>
#include <QCoreApplication>
#include <QDateEdit>
#include <QDesktopWidget>
#include <QDial>
#include <QDialog>
#include <QDockWidget>
#include <QDrag>
#include <QEvent>
#include <QFileDialog>
#include <QFocusEvent>
#include <QFontDatabase>
#include <QFontDialog>
#include <QFont>
#include <QFrame>
#include <QGradient>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QItemDelegate>
#include <QKeyEvent>
#include <QLabel>
#include <QLinearGradient>
#include <QLineEdit>
#include <QListView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QRadialGradient>
#include <QRadioButton>
#include <QScrollBar>
#include <QScrollArea>
#include <QSettings>
#include <QShortcut>
#include <QSortFilterProxyModel>
#include <QSpinBox>
#include <QSplitter>
#include <QSplashScreen>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QStatusBar>
#include <QSyntaxHighlighter>
#include <QTableView>
#include <QTextBrowser>
#include <QTextEdit>
#include <QTextList>
#include <QTextLayout>
#include <QTextStream>
#include <QTextCodec>
#include <QTextCursor>
#include <QTextDocumentFragment>
#include <QTime>
#include <QTimer>
#include <QTimerEvent>
#include <QTextEdit>
#include <QToolTip>
#include <QToolBar>
#include <QToolBox>
#include <QToolButton>
#include <QTreeView>
//#include <QWorkSpace>
#include <qworkspace.h>

/*
#include <qcstring.h> 
#define QCString _______QCString_no
class QCString;
#include <qstring.h>
#undef QCString

#include <qnamespace.h>
#include <qaccel.h>
#include <qaction.h>
#include <qapplication.h>
#include <qeventloop.h>
#include <qasciidict.h>
#include <qbitmap.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qcolor.h>
#include <qcolordialog.h>
#include <qcombobox.h>
#include <qcursor.h>
#include <qdatetimeedit.h>
#include <qdatastream.h>
#include <qdatetime.h>
#include <qdial.h>
#include <qdict.h>
#include <qdockarea.h>
#include <qdom.h>
#include <qdragobject.h>
#include <qevent.h>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qfocusdata.h>
#include <qfontdialog.h>
#include <qguardedptr.h>
#include <qheader.h>
#include <qinputdialog.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qlistview.h>
#include <qmainwindow.h>
#include <qmenudata.h>
#include <qmenubar.h>
#include <qmessagebox.h>
#include <qmutex.h>
#include <qobjcoll.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include <qpicture.h>
#include <qpixmap.h>
#include <qpopupmenu.h>
#include <qptrdict.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qscrollview.h>
#include <qsettings.h>
#include <qspinbox.h>
#include <qslider.h>
#include <qsplitter.h>
#include <qstatusbar.h>
#include <qstyle.h>
#include <qsyntaxhighlighter.h>
#include <qtabbar.h>
#include <qtable.h>
#include <qtextedit.h>
#include <qtextcodec.h>
#include <qthread.h>
#include <qtimer.h>
#include <qtoolbutton.h>
#include <qtooltip.h>
#include <qvalidator.h>
#include <qvaluelist.h>
#include <qvbox.h>
#include <qvbuttongroup.h>
#include <qwidget.h>
#include <qwidgetstack.h>
#include <qworkspace.h>
*/
#pragma pack()

//typedef std::vector<QString> QStringList;
//typedef std::pair<ODataWidget*,int> p_odwint;

#define BEGIN_ONCE( param ) \
  if( !param ) \
  { \
    logical& __lock_param= param; \
    param= YES;

#define END_ONCE \
    __lock_param= NO; \
    goto __lock_end; \
    __lock_end:; \
  }

#define LEAVE_ONCE( code ) \
  { __lock_param= NO; \
  code; \
  goto __lock_end; }

#define EXCEPT_ONCE( code ) \
  { __lock_param= NO; \
  code; \
  __lock_param= YES; }
/*
class ODeferrer : public QObject
{
private:
  int timerid;
public:
  void timerEvent ( QTimerEvent * )
  {
    killTimer(timerid);
    if( parent() ) parent()->removeChild( this );
    Fire();
    delete this;
  }
  virtual void Fire() {}
  ODeferrer(QObject* parent) : QObject(parent)
  {
    timerid= startTimer(0);
  }
};
*/
#define USE_DEFERRER1(parent,action,type1,val1) \
  { \
    class _Def : public ODeferrer \
    { \
    public: \
      type1 param1; \
      _Def(QObject* par,type1 param1) : ODeferrer(par), param1(param1) \
      {} \
      void Fire() { action; } \
    }; \
    new _Def(parent,val1); \
  }

#define USE_DEFERRER2(parent,action,type1,val1,type2,val2) \
  { \
    class _Def : public ODeferrer \
    { \
    public: \
      type1 param1; \
      type2 param2; \
      _Def(QObject* par,type1 param1,type2 param2) : ODeferrer(par), param1(param1), \
      param2(param2) \
      {} \
      void Fire() { action; } \
    }; \
    new _Def(parent,val1,val2); \
  }

#define CC (char*)(const char*)

#define SZ2QS(sz) ( QString::fromLatin1(sz) )
//#define QS2SZ(qs) ( (char*) (qs).latin1() )
#define QS2SZ(qs) \
  ( (char*) ((qs).isNull() ? (char*) NULL : (char*) (qs).isEmpty() ? (char*)"" : (char*)(qs).toLatin1().data()) )
//  ( (char*) ((qs).isNull() ? NULL : (qs).isEmpty() ? "" : (char*)(qs).toLatin1().data()) )

#define QS2SZ_P(qs,qba) \
  ( (char*) ((qs).isNull() ? (char*) NULL : (char*) (qs).isEmpty() ? (char*)"" : (char*)(qba = (qs).toLatin1()).data()) ) 
//  ( (char*) ((qs).isNull() ? NULL : (qs).isEmpty() ? "" : (qba = (qs).toLatin1())) )

#define SZB2QS(sz,l) \
  ( QString::fromLatin1( sz, __FB_get_len( sz, l ) ) )

#define SZB2QC(sz,l) \
  ( QCString( sz, __FB_get_len( sz, l ) + 1 ) )

#define QC2SZB(qc,l) \
  ( CC (qc).leftJustify(l) )

#define QS2SZB(qs,l) \
  ( QS2SZ( (qs).leftJustify(l) ) )


static int __FB_get_len( const char* c, int len )
{
    if( c )
    {
      const char* pc= &c[len-1];
      while( len && *(pc--) == ' ' ) len--;
      return len;
    } else return 0;
}

#undef  Q_OBJECT    // wir muessen die virtuellen Funktionen exportieren um ausserhalb der ogui-dll ableiten zu koennen
#define Q_OBJECT \
public: \
    static const QMetaObject staticMetaObject; \
    virtual OGUI7ImpExp const QMetaObject *metaObject() const; \
    virtual OGUI7ImpExp void *qt_metacast(const char *); \
    QT_TR_FUNCTIONS \
    virtual OGUI7ImpExp int qt_metacall(QMetaObject::Call, int, void **); \
private:

#endif //  __CQT_H__
