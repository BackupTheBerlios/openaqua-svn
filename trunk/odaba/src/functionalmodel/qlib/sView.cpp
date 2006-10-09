/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    sView

\brief    


\date     $Date: 2006/03/16 17:26:56,79 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sView"

#include  <pfmodel.h>
#ifndef   P_ODC_View_HPP
#define   P_ODC_View_HPP
#include  <sPI.hpp>
class       ODC_View;
PI_dcl     (ODC_View)
#endif
#ifndef   P_SDB_Type_HPP
#define   P_SDB_Type_HPP
#include  <sPI.hpp>
class       SDB_Type;
PI_dcl     (SDB_Type)
#endif
#include  <sCTX_Structure.hpp>
#include  <sODC_View.hpp>
#include  <sSDB_Type.hpp>
#include  <ssView.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return term

\param  strctx_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical sView :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sView();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBCreate - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreate"

logical sView :: DBCreate ( )
{
  SDB_Structure *instance = (ODC_View *)GetPropertyHandle()->GetArea();
  logical        term     = NO;
  instance->set_smcestyp(ST_VIEW);
  instance->set_typetype(TYP_Structure);
  instance->SetAccessType(AT_VIEW);

  return(term);
}

/******************************************************************************/
/**
\brief  sView - Konstruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sView"

                        sView :: sView ( )
                     : CTX_Structure ()
{



}

/******************************************************************************/
/**
\brief  ~sView - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sView"

                        sView :: ~sView ( )
{



}


