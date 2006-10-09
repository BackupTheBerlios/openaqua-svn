/*******************************************************************/ 
/*			     O Q L			           */ 
/*                      OQL Error Macro Definitions                */ 
/*   Version 0.1                                          02.07.95 */ 
/*******************************************************************/  

#ifndef   OQLERR_H
#define   OQLERR_H

 /*******************************************************************/ 

#include  <csdberr.h>
#include  <iopai.h>

 /*******************************************************************/  

#define   OQLCERR      { if ( OQLError().CheckError() )	\
                           goto on_error;  }

#define   OQLERROR     ( (short)OQLError().CheckError() )

#define   OQLRESET     { OQLError().ResetError();      }

 /*******************************************************************/ 

#endif

