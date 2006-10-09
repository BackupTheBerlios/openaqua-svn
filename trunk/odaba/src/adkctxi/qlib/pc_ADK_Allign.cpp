/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi - 
\class    pc_ADK_Allign

\brief    


\date     $Date: 2006/06/18 10:24:17,65 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADK_Allign"

#include  <padkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ADK_Allign.hpp>


/******************************************************************************/
/**
\brief  Setup - 


\return term - 

\param  in_grid - 
\param  in_dockwin - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical pc_ADK_Allign :: Setup (logical in_grid, logical in_dockwin )
{
  logical                 term = NO;
  *GPH("position")    = "POS_Parent";
  *GPH("hori")        = "HPS_InnerLeft";
  *GPH("vert")        = "VPS_InnerTop";
  if ( in_grid )
  {
    *GPH("arrange")     = "AT_Grid";
    *GPH("hori_sizing") = "SIZE_Grow";
    *GPH("vert_sizing") = "SIZE_Grow";
    *GPH("margin.right") = 4;
    *GPH("margin.bottom") = 4;
    *GPH("hori_cell") = 1;
    *GPH("vert_cell") = 1;
  }
  else
  {
    *GPH("arrange")     = (char*) (in_dockwin ? "AT_Docking" : "AT_Absolut");
    *GPH("hori_sizing") = "SIZE_Fixed";
    *GPH("vert_sizing") = "SIZE_Fixed";
  }

  return(term);
}

/******************************************************************************/
/**
\brief  pc_ADK_Allign - 



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_Allign"

     pc_ADK_Allign :: pc_ADK_Allign (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{



}

/******************************************************************************/
/**
\brief  ~pc_ADK_Allign - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pc_ADK_Allign"

     pc_ADK_Allign :: ~pc_ADK_Allign ( )
{



}


