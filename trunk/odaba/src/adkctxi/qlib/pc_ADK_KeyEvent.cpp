/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi
\class    pc_ADK_KeyEvent



\date     $Date: 2006/05/23 13:14:15,82 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADK_KeyEvent"

#include  <padkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ADK_KeyEvent.hpp>


/******************************************************************************/
/**
\brief  SetKeyString

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKeyString"

logical pc_ADK_KeyEvent :: SetKeyString ( )
{
  char                    area[256];
  logical                 term = NO;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
    
  *area = 0;
  if ( GPH("ctrl")->IsTrue() )
    strcat(area,"Ctrl+");
  if ( GPH("alt")->IsTrue() )
    strcat(area,"Alt+");
  if ( GPH("shift")->IsTrue() )
    strcat(area,"Shift+");
  if ( GPH("meta")->IsTrue() )
    strcat(area,"Meta+");
  strcat(area,GetString("key_code"));
  *GPH("key_string") = area;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ADK_KeyEvent


\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_KeyEvent"

     pc_ADK_KeyEvent :: pc_ADK_KeyEvent (PropertyHandle *ph )
                     : PropertyHandle(ph)
{
}


