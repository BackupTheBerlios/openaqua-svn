/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_Hund

\brief    


\date     $Date: 2006/07/21 16:22:28,81 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_Hund"

#include  <pVGKbase.h>
#include  <spc_Hund.hpp>


/******************************************************************************/
/**
\brief  GetKampfhundCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKampfhundCount"

int32 pc_Hund :: GetKampfhundCount ( )
{
  PropertyHandle   *kampfhund = GPH("kampfhund");
  int32             indx0     = 0;
  int32             count     = 0;
  while ( Get(indx0++) )
    if ( kampfhund->IsTrue() )
      count++;
  return(count);
}

/******************************************************************************/
/**
\brief  pc_Hund - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_Hund"

     pc_Hund :: pc_Hund (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


