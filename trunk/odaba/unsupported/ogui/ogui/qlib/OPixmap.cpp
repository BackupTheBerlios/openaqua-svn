/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OPixmap

\brief    


\date     $Date: 2006/03/13 21:36:09,70 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPixmap"

#include  <pogui7.h>
#include  <sOPixmap.hpp>


/******************************************************************************/
/**
\brief  FromDPixmap - 



\param  rDPixmap -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromDPixmap"

void OPixmap :: FromDPixmap (DPixmap &rDPixmap )
{
  char      string[1024];
BEGINSEQ
  if ( !rDPixmap.path || !*rDPixmap.path )           ERROR
  
  ReplaceSysVariable(strcpy(string,rDPixmap.path),sizeof(string)-1);
  
  load(SZ2QS(string));
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  OPixmap - 


-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPixmap"

                        OPixmap :: OPixmap ( )
                     : QPixmap (),
  use_for_normal(NO),
  use_for_active(NO),
  use_for_disabled(NO)
{

  memset(name,' ',sizeof(name));


}

/******************************************************************************/
/**
\brief  i01


\param  rDPixmap -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPixmap"

                        OPixmap :: OPixmap (DPixmap &rDPixmap )
                     : QPixmap (),
  use_for_normal(NO),
  use_for_active(NO),
  use_for_disabled(NO)
{

  memset(name,' ',sizeof(name));
  
  FromDPixmap(rDPixmap);

}

/******************************************************************************/
/**
\brief  i02


\param  rOPixmap -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPixmap"

                        OPixmap :: OPixmap (OPixmap &rOPixmap )
                     : QPixmap (rOPixmap),
  use_for_normal(rOPixmap.use_for_normal),
  use_for_active(rOPixmap.use_for_active),
  use_for_disabled(rOPixmap.use_for_disabled)
{

  memcpy(name,rOPixmap.name,sizeof(name));


}

/******************************************************************************/
/**
\brief  ~OPixmap - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPixmap"

                        OPixmap :: ~OPixmap ( )
{



}


