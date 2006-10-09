/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InitArea

\brief    


\date     $Date: 2006/03/12 19:17:36,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "InitArea"

#include  <popa7.h>
#include  <sInitArea.hpp>


/******************************************************************************/
/**
\brief  InitArea - 



\param  w_size -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitArea"

                        InitArea :: InitArea (int32 w_size )
                     : size(w_size),
  area(NULL)
{

  if ( w_size < 0 )
    size = 64+1024;

  area = new char[size];
  memset(area,0,size);

}

/******************************************************************************/
/**
\brief  ~InitArea - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~InitArea"

                        InitArea :: ~InitArea ( )
{

  delete area;
  area = NULL;

}


