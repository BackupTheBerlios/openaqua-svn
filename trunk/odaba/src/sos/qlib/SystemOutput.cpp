/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    SystemOutput

\brief    


\date     $Date: 2006/08/27 10:42:16,96 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SystemOutput"

#include  <pdefault.h>
#include  <sCTX_Base.hpp>
#include  <sSystemOutput.hpp>


/******************************************************************************/
/**
\brief  SystemOutput - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SystemOutput"

     SystemOutput :: SystemOutput ( )
                     : SystemIO()
{



}

/******************************************************************************/
/**
\brief  Write - 



\return term - Success

\param  string - String value
\param  line_end - 
\param  clear_opt - 
\param  flush_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical SystemOutput :: Write (char *string, logical line_end, logical clear_opt, logical flush_opt )
{
  logical      term = NO;
  if ( context )
    context->Output(string,line_end,clear_opt,flush_opt);
  else
  {
    CTX_Base     loc_ctx();
    loc_ctx->Output(string,line_end,clear_opt,flush_opt);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ~SystemOutput - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SystemOutput"

     SystemOutput :: ~SystemOutput ( )
{



}


