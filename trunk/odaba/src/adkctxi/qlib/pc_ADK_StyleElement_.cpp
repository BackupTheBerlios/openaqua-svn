/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|15:35:34,34}|(REF)
\class    pc_ADK_StyleElement_

\brief    


\date     $Date: 2006/04/24 11:55:42,10 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADK_StyleElement_"

#include  <padkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ADK_Allign.hpp>
#include  <spc_ADK_StyleElement_.hpp>


/******************************************************************************/
/**
\brief  SetupFromParent

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupFromParent"

logical pc_ADK_StyleElement_ :: SetupFromParent ( )
{
  PropertyHandle         *fc       = GetParentProperty();
  logical                 splitter = NO;
  logical                 in_grid  = NO;
  logical                 in_dwin  = NO;
  logical                 in_tab   = NO;
  logical                 term     = NO;
  PropertyHandle   style(*fc->GPH("style"));
  style.Get(FIRST_INSTANCE);
  
  if ( style.IsA("ADKS_Splitter") )
    splitter = YES;
    
  if ( style.IsA("ADKS_Tab") )
  {
    in_tab = YES;
    in_grid = YES;
  }
  else
    in_grid = fc->GPH("allign.vert_cell")->GetInt() > 0 &&
              fc->GPH("allign.hori_cell")->GetInt() > 0;

  if ( fc->GPH("docking_window")->IsTrue() )
  {
    *GPH("docking_window") = YES;
    in_grid = in_tab = splitter = NO;
  }
  
  if ( in_tab )
  {
    *GPH("display_level") = -1;
  }
  PropertyHandle *phallign = GPH("allign");
  pc_ADK_Allign(phallign).Setup(in_grid,in_dwin);
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ADK_StyleElement_ - 



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_StyleElement_"

                        pc_ADK_StyleElement_ :: pc_ADK_StyleElement_ (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{



}

/******************************************************************************/
/**
\brief  ~pc_ADK_StyleElement_ - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pc_ADK_StyleElement_"

                        pc_ADK_StyleElement_ :: ~pc_ADK_StyleElement_ ( )
{



}


