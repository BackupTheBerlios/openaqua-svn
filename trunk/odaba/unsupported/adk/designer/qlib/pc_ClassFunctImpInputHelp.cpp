/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc_ClassFunctImpInputHelp

\brief    


\date     $Date: 2006/06/13 23:02:00,79 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ClassFunctImpInputHelp"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ClassFunctImpInputHelp.hpp>


/******************************************************************************/
/**
\brief  DeinitHandles - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeinitHandles"

void pc_ClassFunctImpInputHelp :: DeinitHandles ( )
{

  ident.Close();
  source.Close();

  Close();


}

/******************************************************************************/
/**
\brief  InitHandles - 


\return term - 

\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitHandles"

logical pc_ClassFunctImpInputHelp :: InitHandles (PropertyHandle *prophdl )
{
  logical                 term = NO;
  Open(prophdl->GPH("funct_impls"));

  ident.Open(GPH("ident"));
  source.Open(GPH("source"));  

  return(term);
}

/******************************************************************************/
/**
\brief  IsFilled - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsFilled"

logical pc_ClassFunctImpInputHelp :: IsFilled ( )
{

  return ( GetParentProperty()->GPH("filled")->IsTrue() );

}

/******************************************************************************/
/**
\brief  SetFilled - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilled"

logical pc_ClassFunctImpInputHelp :: SetFilled ( )
{
  logical                 term = NO;
BEGINSEQ
  *GetParentProperty()->GPH("filled") = YES;
  Save();                                            P_SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupList - 


\return term - 

\param  functimp_ph - 
\param  base_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupList"

logical pc_ClassFunctImpInputHelp :: SetupList (PropertyHandle *functimp_ph, logical base_opt )
{
  PropertyHandle    *class_ident = functimp_ph->GetParentProperty()->GetParentProperty()->GPH("sys_ident");
  PropertyHandle    *head_line   = functimp_ph->GPH("head_line");
  char              *start_pos   = NULL;
  int32              indx0       = 0;
  logical            term        = NO;
  while ( functimp_ph->Get(indx0++) )
    if ( start_pos = strchr(head_line->GetString(),'(') )
    {
      PropertyHandle   idkey(start_pos+1);
      if ( !Get(idkey) )
      {
        GetInitInstance();
        *GPH("_const_par") = "( ";
        ident = idkey;
        if ( base_opt && class_ident )
          source = *class_ident;
        Save();
      }
    }

  return(term);
}

/******************************************************************************/
/**
\brief  pc_ClassFunctImpInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ClassFunctImpInputHelp"

     pc_ClassFunctImpInputHelp :: pc_ClassFunctImpInputHelp ( )
                     : PropertyHandle (),
  ident(),
  source()
{



}


