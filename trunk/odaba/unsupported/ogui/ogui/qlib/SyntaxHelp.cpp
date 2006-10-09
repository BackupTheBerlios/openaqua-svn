/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    SyntaxHelp

\brief    Syntax Help


\date     $Date: 2006/03/13 21:36:26,81 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SyntaxHelp"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sSyntaxHelp.hpp>


/******************************************************************************/
/**
\brief  GetControl - 


\return pODataWidget - Parent data widget

\param  qsComparator -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControl"

ODataWidget *SyntaxHelp :: GetControl (QString qsComparator )
{

  for(std::vector<std::string>::iterator it = vlActivators.begin()
     ;it!=vlActivators.end()
     ;it++
     )
     if(   (*it).length() > 0 
        && qsComparator.endsWith(SZ2QS((*it).c_str())) )
       return pODataWidget;
  return(NULL);
}

/******************************************************************************/
/**
\brief  GetDefaultControl - 


\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDefaultControl"

ODataWidget *SyntaxHelp :: GetDefaultControl ( )
{

  for(std::vector<std::string>::iterator it = vlActivators.begin()
     ;it!=vlActivators.end()
     ;it++
     )
     if(   (*it).length() == 0  )
       return pODataWidget;

  return (NULL);
}

/******************************************************************************/
/**
\brief  SyntaxHelp - 


-------------------------------------------------------------------------------
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyntaxHelp"

                        SyntaxHelp :: SyntaxHelp ( )
                     :  pODataWidget(NULL)
,vlActivators()
{



}

/******************************************************************************/
/**
\brief  i02


\param  pODW -
\param  vlAct -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyntaxHelp"

                        SyntaxHelp :: SyntaxHelp (ODataWidget *pODW, VECTOR(std_string) &vlAct )
                     :  pODataWidget(pODW)
,vlActivators(vlAct)
{



}

/******************************************************************************/
/**
\brief  ~SyntaxHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SyntaxHelp"

                        SyntaxHelp :: ~SyntaxHelp ( )
{



}


