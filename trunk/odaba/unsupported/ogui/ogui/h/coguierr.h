 /*******************************************************************/
 /*                                                                 */
 /*                Document Composer Includes                       */
 /*  Version 0.1                                          11.06.93  */
 /*******************************************************************/

#ifndef   OGUIERR_H
#define   OGUIERR_H

#include  <sError.hpp>
//extern  OGUIImpExp  Error   oguierr;

/*******************************************************************/

#define   OGUICERR      { if ( OGUIError().CheckError() ) goto on_error;  }

#define   OGUIRESET     { OGUIError().ResetError(); }

#define   OGUIERROR     OGUIError().CheckError()

/*******************************************************************/ 

#endif
