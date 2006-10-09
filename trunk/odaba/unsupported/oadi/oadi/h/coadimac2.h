/*******************************************************************/
/* 			  O A D I										 */
/* 					User Macro Definitions							 */
/*   Version 0.1														 13.04.93 */
/*******************************************************************/

#ifndef	 OADIMAC_H
#define	 OADIMAC_H

//#include  <codcpmac.h>
#include  <fctypes.h>

#include  <coadierr.h>
#include  <iOGUI_Interface.h>

/*
class     WindowEditor;
class     adca;
class     adcm;
class     GUI_WorkWindow;

extern ODCPImpExp  WindowEditor   * PtWindowEditor;

extern ODCPImpExp  adca           * adcappl;
extern ODCPImpExp  adcm           * adcmappl;
extern ODCPImpExp  fnc            * current_fnc;

extern ODCPImpExp  GUI_WorkWindow * mdiwptr;

#include  <codaba2.h>
extern ODCPImpExp  DBObjectHandle  sdbhndl;
extern ODCPImpExp  DBObjectHandle  mdshndl;
*/
 /*******************************************************************/

#define	 OADI_CANCEL 1000

 /*******************************************************************/

#define	 OADICERR	       { if ( OADIError().CheckError() )	\
			                   goto on_error;  }

#define	 OADIRESET	       { OADIError().ResetError(); 	  }

#define	 OADISDBCERR       { if ( SDBError().CheckError() )	\
			                 { OADIError().SetError(ODABA_ERROR,OBJ_ID,MOD_ID); \
			                   goto on_error; } }

#define	 OADISQLCERR       { if ( SQLError().CheckError() )	\
			                 { OADIError().SetError(SQL_ERROR,OBJ_ID,MOD_ID); \
			                   goto on_error; } }

#define	 OADIDCCERR        { if ( DCError().CheckError() ) \
			                 { OADIError().SetError(DC_ERROR,OBJ_ID,MOD_ID); \
			                   goto on_error; } }

#define  OADIDISPLAY_ERROR { OADIError().DisplayMessage();          }

#define  OADIDISPLAY(x)    { OADIError().SetError( x,NULL,NULL);     \
                             OADIError().DisplayMessage();          }

#define	 OADIERROR         OADIError().CheckError()

#define  OADIEV1(str,len)  { OADIError().SetErrorVariable(1, str, len); }
#define  OADIEV2(str,len)  { OADIError().SetErrorVariable(2, str, len); }
#define  OADIEV3(str,len)  { OADIError().SetErrorVariable(3, str, len); }
#define  OADIEV4(str,len)  { OADIError().SetErrorVariable(4, str, len); }
#define  OADIEV5(str,len)  { OADIError().SetErrorVariable(5, str, len); }
 /*******************************************************************/

#endif

