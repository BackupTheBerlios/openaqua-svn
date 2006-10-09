/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    BNFElement

\brief    BNF element
          A  BNF element  describes an  element in  a BNF expression. An element
          might  be  a  symbol  or  a  token.  Symbols  must  be  defined as BNF
          expressions,  again. Symbols  might be  optional or mandatory. Symbols
          can  be  defined  by  means  of  a repitition factor (0: any number of
          repititions).

\date     $Date: 2006/06/03 13:27:34,04 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BNFElement"

#include  <pdefault.h>
#ifndef   DLL_BNFElement_HPP
#define   DLL_BNFElement_HPP
#include  <sBNFElement.hpp>
#include  <sDLL.h>
#endif
#include  <sBNFData.hpp>
#include  <sBNFExpression.hpp>
#include  <sBNFParser.hpp>
#include  <sBNFSymbol.hpp>
#include  <sBNFElement.hpp>


/******************************************************************************/
/**
\brief  Analyze - 


\return vcode - Validation code

\param  bdata - Pointer to BNF Node
\param  belements - 
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Analyze"

int32 BNFElement :: Analyze (BNFData *bdata, DLL(BNFElement) *belements, logical case_opt )
{
  BNFSymbol          *tsymbol;
  BNFSymbol          *bsymbol;
  BNFElement         *belement;
  BNFExpression      *bexpressions[EXP_VECT_SIZE];
  BNFData            *last_child = bdata->GetLastElement();
  int                 index0 = 0;
  int32               vcode = 4;
BEGINSEQ
  memset(bexpressions,0,sizeof(bexpressions));
  
  if ( case_opt )
    case_opt = case_sensitive;
    
  tsymbol = symbol->TerminalSymbol(bexpressions,bdata,case_sensitive);
  if ( bexpressions[0] )
    index0 = 1;
  if ( (index0 = tsymbol->LocateExpressions(symbol,bexpressions,bdata,index0,case_opt)) >= 0 || optional )
    vcode = 3;       
  tsymbol = symbol->ElementaryToken(bdata->CurrentToken(),case_opt);
  
  while ( vcode < 4 )
  {  
    if ( index0 >= 0 && (vcode = symbol->Analyze(bexpressions,bdata,index0-1,case_opt)) < 3 )
    {
      bdata->UpdatePosition(separated);
      vcode = AnalyzeRepetitions(bdata,case_opt);    // returns 1 or 2 always!!
    } 
    if ( vcode > 2 && !optional )
      vcode = 4;       
    if ( vcode > 3 && optional )
      vcode = 3;       

    if ( vcode < 4 )                                
      if ( belement = belements->GetNext() )
        vcode = belement->Analyze(bdata,belements,case_opt);

    if ( separated && isalpha(*tsymbol->get_name()) && !bdata->get_separated() &&
         ( isalpha(bdata->CurrentToken()) || bdata->CurrentToken() == '_' )    &&
         !symbol->HasExpressions()                                                )
      vcode = 4;
      
    if ( vcode != 4 )                                
      break;
    
    belements->GetPrev();
    bdata->RemoveLastChildren(last_child,separated);
    
    index0 = symbol->GetExpCount(bexpressions);
    if ( index0 > 0 )
    {
      bsymbol = index0 > 1 ? bexpressions[index0-2]->get_symbol() : tsymbol;
      index0 = bsymbol->NextExpressions(symbol,bexpressions,bdata,index0-1,case_opt);
      if ( index0 >= 0 )
        vcode = 3;       
    }
  }
  
  if ( vcode > 4 )                                  ERROR
  
  bdata->UpdatePosition(separated);

RECOVER
  if ( vcode < 4 ) 
    vcode = 4;
ENDSEQ
  return(vcode);
}

/******************************************************************************/
/**
\brief  AnalyzeExpression - 


\return vcode - Validation code

\param  bexpressions - 
\param  bdata - Pointer to BNF Node
\param  index0 - 
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AnalyzeExpression"

int32 BNFElement :: AnalyzeExpression (BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt )
{
  int32                   vcode = 0;
BEGINSEQ
  if ( case_opt )
    case_opt = case_sensitive;
    
  if ( bexpressions[index0]->get_symbol() != symbol ||
       (vcode = symbol->AnalyzeExpression(bexpressions,bdata,index0,case_opt)) == 4 )  
  {
//    if ( repititions && !optional )                  ERROR
    if ( !optional )                                 ERROR
    vcode = 3;                                       LEAVESEQ
  }
  if ( vcode > 4 )                                   ERROR
  
  bdata->UpdatePosition(separated);

RECOVER
  if ( vcode < 4 ) 
    vcode = 4;
ENDSEQ
  return(vcode);
}

/******************************************************************************/
/**
\brief  AnalyzeRepetitions - 


\return vcode - Validation code

\param  bdata - Pointer to BNF Node
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AnalyzeRepetitions"

int32 BNFElement :: AnalyzeRepetitions (BNFData *bdata, logical case_opt )
{
  int                     count;
  int32                   vcode = 2;
  count = repititions;
  while ( vcode > 1 && --count )
    if ( (vcode = symbol->Analyze(bdata,case_opt)) > 2 )
    {
//      if ( vcode > 3 )
//        symbol->get_top_symbol()->SetError(bdata);
      break;
    }
    else
      bdata->UpdatePosition(separated);

  vcode = bdata->HasData() ? 2 : 1;
    

  return(vcode);
}

/******************************************************************************/
/**
\brief  BNFElement - 



\param  bexpression - 
\param  bsymbol - BNF Symbol
\param  is_optional - Is value optional
\param  rep_count - Repetition count
\param  case_opt - Case sensitive (not supported)
\param  sep_opt - Separator option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFElement"

     BNFElement :: BNFElement (BNFExpression *bexpression, BNFSymbol *bsymbol, logical is_optional, int32 rep_count, logical case_opt, logical sep_opt )
                     : symbol(bsymbol),
  optional(is_optional),
  separated(sep_opt),
  case_sensitive(case_opt),
  repititions(rep_count),
  expression(bexpression)
{

  bsymbol->RegisterUpper(GetSymbol());

}

/******************************************************************************/
/**
\brief  GetSymbol - 


\return bsymbol - BNF Symbol

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSymbol"

BNFSymbol *BNFElement :: GetSymbol ( )
{

  return ( expression ? expression->get_symbol() : NULL );

}

/******************************************************************************/
/**
\brief  ~BNFElement - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BNFElement"

     BNFElement :: ~BNFElement ( )
{



}


