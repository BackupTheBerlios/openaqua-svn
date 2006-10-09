/*******************************************************************/
/*                 O G U I                                             */
/*         Project Includes - General Defines and Error Class      */
/*   Version 0.1                                          12.02.92 */
/*******************************************************************/ 

#ifndef   OGUI_IF_H
#define   OGUI_IF_H
#include  <coguidll.h>
#include  <copadll.h>
#include  <csosdll.h>
#include  <padcstd.h>
#include  <cqt.h>

// override the the imp/exp setting for applications
// qt includes will complain because Q_OBJECT is redefined by cqt.h
// better is to include the qt header in cqt
//  generates Compiler Error C2487 in Visual Studio
#define OGUI7ImpExp 

#ifndef   CONCAT
#define   CONCAT(a,b) a##b
#endif

#define QT_DEBUG   // for QT debug-info

/*****************************************************************************/

#define   OGUIERR(x)    { OGUIError().SetError( x,OBJ_ID,MOD_ID); goto on_error;  }

#define   OGUIIERR(x)   { OGUIError().SetError( x,NULL,NULL);     goto on_error;  }

#define   OGUIPERR      { OGUIError().SetError(0,"",MOD_ID);       goto on_error;  }

#define   OGUICERR      { if ( OGUIError().CheckError() )          goto on_error;  }

#define   OGUISET(x)    { OGUIError().SetError( x,OBJ_ID,MOD_ID);  }

#define   OGUIISET(x)   { OGUIError().SetError( x,NULL,NULL);       }

#define   OGUIRESET     { OGUIError().ResetError();      }

#define   OGUIEV1(str,len)  { OGUIError().SetErrorVariable(1, str, len); }
#define   OGUIEV2(str,len)  { OGUIError().SetErrorVariable(2, str, len); }
#define   OGUIEV3(str,len)  { OGUIError().SetErrorVariable(3, str, len); }
#define   OGUIEV4(str,len)  { OGUIError().SetErrorVariable(4, str, len); }
#define   OGUIEV5(str,len)  { OGUIError().SetErrorVariable(5, str, len); }

#define      OGUISDBCERR       { if ( SDBError().CheckError() )    \
                             { OGUIError().SetError(ODABA_ERROR,OBJ_ID,MOD_ID); \
                               goto on_error; } }

#define   OGUISDBCSERR(x)   { if ( SDBError().CheckError() )                     \
                                OGUIError().SetError(ODABA_ERROR,OBJ_ID,MOD_ID); \
                              else                                               \
       	                        OGUIError().SetError( x,OBJ_ID,MOD_ID);         \
                              goto on_error;  }

#define   P_OGUICERR         { if ( OGUIError().CheckError() )                         \
                               { P_Error().SetError(OGUI_ERROR,OBJ_ID,MOD_ID); \
                                 goto on_error; } }

#define      OGUIDCCERR        { if ( DCError().CheckError() ) \
                             { OGUIError().SetError(DC_ERROR,OBJ_ID,MOD_ID); \
                               goto on_error; } }

#define  OGUIDISPLAY_ERROR { OGUIError().DisplayMessage();          }

#define  OGUIDISPLAY(x)    { OGUIError().SetError( x,NULL,NULL);     \
                             OGUIError().DisplayMessage();          }

#define     OGUI_CANCEL 1000

/*****************************************************************************/

#include  <coguierr.h>

#include <csos4mac.h>
#include <codaba2.h>
#include <igvtx.h>
#include <iiGUI.h>
#include <iopai.h>

#include <cstats.h>

#endif
