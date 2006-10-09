/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    SyntaxBlock

\brief    


\date     $Date: 2006/04/10 18:21:04,81 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SyntaxBlock"

#include  <pogui7.h>
#include  <sSyntaxElement.hpp>
#include  <sSyntaxBlock.hpp>


/******************************************************************************/
/**
\brief  InBlock - 
        position is in this block

\return cond - 

\param  iPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InBlock"

logical SyntaxBlock :: InBlock (int iPosition )
{
  logical                 term = NO;
  int                     rel;
  rel = iPosition - begin;
  term = rel > 0 && (length<0 || rel <= length);

  return(term);
}

/******************************************************************************/
/**
\brief  SyntaxBlock - Konstructor


\return term - 

\param  syntaxelement - 
\param  iBegin - 
\param  iLength - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyntaxBlock"

                        SyntaxBlock :: SyntaxBlock (SyntaxElement syntaxelement, int iBegin, int iLength )
                     :  syntaxelement(syntaxelement)
,begin(iBegin)
,length(iLength)
{



}


