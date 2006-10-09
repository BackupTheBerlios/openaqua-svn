/********************************* Class Source Code ***************************/
/**
\package  OXML - 
\class    xml_RootBase

\brief    


\date     $Date: 2006/06/11 13:01:06,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "xml_RootBase"

#include  <pOXML.h>
#include  <sacb.hpp>
#include  <sxml_RootBase.hpp>


/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code

\param  path - 
\param  outopt - 
\param  exclusive - 
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical xml_RootBase :: Open (char *path, logical outopt, logical exclusive, char sysenv )
{
  logical   term = NO;
BEGINSEQ
  if ( !path || !*path )                             SDBERR(5)
  SDBEV1(path,UNDEF)

  if ( xml_data.Open(path) )                         ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RBType - 


\return rbtype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RBType"

RootBase_Types xml_RootBase :: RBType ( )
{

  return(RBT_OXML);

}

/******************************************************************************/
/**
\brief  xml_RootBase - 



\param  netopt - Multi-user access
\param  shared_rb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xml_RootBase"

     xml_RootBase :: xml_RootBase (logical netopt, logical shared_rb )
                     : db_RootBase(netopt)
{



}

/******************************************************************************/
/**
\brief  ~xml_RootBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~xml_RootBase"

     xml_RootBase :: ~xml_RootBase ( )
{



}


