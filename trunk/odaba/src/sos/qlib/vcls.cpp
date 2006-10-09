/********************************* Class Source Code ***************************/
/**
\package  SOS
\class    vcls

\brief    Virtual class
          This  is an empty class that acts as base class for objects supporting
          dynamical  function  calls.  Depending  on  the  compiler  the  class 
          occupies no or one byte memory. 
          A  global count field (vcls_count) allows checking whether all objects
          have been desctructed at the end of a program.

\date     $Date: 2006/05/01 18:16:58,14 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "vcls"

#include  <pdefault.h>
#include  <stim.hpp>
#include  <svcls.hpp>

int32 vcls_count = 0;
DLL(vcls) vcls_list;

/******************************************************************************/
/**
\brief  Wait - Wait


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Wait"

logical vcls :: Wait ( )
{
  logical                 term = NO;
  TWAIT(1000000);
  return(term);
}

/******************************************************************************/
/**
\brief  vcls


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "vcls"

     vcls :: vcls ( )
{
  logical      test = NO;
#ifdef VCLS_LIST
  vcls_list.AddTail(this);

  if ( test )
  {
    vcls    *vclsptr;
    int32    indx = 0;
    vcls_list.GoBottom();
    while ( vclsptr = vcls_list.GetPrev() )
    {
      indx++;
      test = NO;
    }
  }
#endif

vcls_count++;

}

/******************************************************************************/
/**
\brief  ~vcls


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~vcls"

     vcls :: ~vcls ( )
{
#ifdef VCLS_LIST
  if ( vcls_list.Find(this))
    vcls_list.RemoveAt();
#endif
  

vcls_count--;
}


