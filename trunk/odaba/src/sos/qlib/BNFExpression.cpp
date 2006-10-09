/********************************* Class Source Code ***************************/
/**
\package  SOS
\class    BNFExpression

\brief    BNF expression
          A  BNF expression defines a BNF symbol.  A BNF Symbol might be defined
          by  more than one  expression. A BNF  expression may consist of one or
          more BNF elements with a defined order.

\date     $Date: 2006/04/26 20:50:15,65 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BNFExpression"

#include  <pdefault.h>
#include  <sBNFData.hpp>
#include  <sBNFElement.hpp>
#include  <sBNFExpression.hpp>
#include  <sBNFSymbol.hpp>
#include  <sBNFExpression.hpp>


/******************************************************************************/
/**
\brief  AddElement

\return vcode - Validation code

\param  bsymbol - BNF Symbol
\param  is_optional - Is value optional
\param  rep_count - Repetition count
\param  case_opt - Case sensitive (not supported)
\param  sep_opt - Separator option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddElement"

int32 BNFExpression :: AddElement (BNFSymbol *bsymbol, logical is_optional, int32 rep_count, logical case_opt, logical sep_opt )
{
  logical                 term = NO;
  elements.AddTail(new BNFElement(this,bsymbol,is_optional,
                                  rep_count,case_opt,sep_opt));

  if ( elements.GetCount() == 1 )
    bsymbol->RegisterFirstSymbol(this);
  return(term);
}

/******************************************************************************/
/**
\brief  Analyze - Analyse expression


\return vcode - Validation code

\param  bexpressions - 
\param  bdata - Pointer to BNF Node
\param  index0
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Analyze"

int32 BNFExpression :: Analyze (BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt )
{
  BNFElement     *belement;
  logical         first = YES;
  logical         found = NO;
  int32           vcode = 2;
BEGINSEQ
  DLL(BNFElement)      cursor(elements);
  if ( index0 > 0 )
    vcode = cursor.GetHead()->AnalyzeExpression(bexpressions,bdata,index0-1,case_opt);
  else
    vcode = symbol->Analyze(bexpressions,bdata,index0-1,case_opt);
  if ( vcode == 4 )                                ERROR
  
  if ( vcode < 3 )  // skipp optional element 
  {
    bdata->UpdatePosition(cursor.GetHead()->get_separated());
    cursor.GetHead()->AnalyzeRepetitions(bdata,case_opt);
  }
  
  if ( belement = cursor.GetNext() )
    vcode = belement->Analyze(bdata,&cursor,case_opt);
  
  if ( vcode >= 4 )                                ERROR
  
  vcode = bdata->HasData() ? 2 : 1;

RECOVER
  if ( vcode < 4 ) 
    vcode = 4;
ENDSEQ
  return(vcode);
}

/******************************************************************************/
/**
\brief  BNFExpression


\param  bsymbol - BNF Symbol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFExpression"

                        BNFExpression :: BNFExpression (BNFSymbol *bsymbol )
                     : elements(),
  symbol(NULL)
{
  bsymbol->AddExpression(this);
}

/******************************************************************************/
/**
\brief  IsElementary

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsElementary"

logical BNFExpression :: IsElementary ( )
{
  BNFElement             *element;
  BNFSymbol              *esymbol;
  logical                 cond = YES;
BEGINSEQ
  elements.GoTop();
  while ( element = elements.GetNext() )
    if ( (esymbol = element->get_symbol()) && 
         esymbol->get_expressions()           )
      ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsIdentified

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIdentified"

logical BNFExpression :: IsIdentified ( )
{
  BNFElement             *element;
  BNFSymbol              *symbol;
  logical                 cond = YES;
BEGINSEQ
  if ( (element = elements.GetHead())   &&
       (symbol = element->get_symbol()) && 
       symbol->get_expressions()           )
    ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  LocateExpressions

\return count - 

\param  target_symbol
\param  bexpressions - 
\param  bdata - Pointer to BNF Node
\param  index0
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateExpressions"

int16 BNFExpression :: LocateExpressions (BNFSymbol *target_symbol, BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt )
{
  BNFSymbol              *bsymbol = symbol;
  int16                   count = 0;
 count = symbol->LocateExpressions(target_symbol,bexpressions,bdata,index0,case_opt);

  return(count);
}

/******************************************************************************/
/**
\brief  MatchKeyword

\return len

\param  bdata - Pointer to BNF Node
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MatchKeyword"

int32 BNFExpression :: MatchKeyword (BNFData *bdata )
{
  BNFElement             *element;
  BNFSymbol              *esymbol;
  char                   *pos  = bdata->get_current_pos();
  int32                   len = 0;
BEGINSEQ
  if ( !symbol->IsKeyword() )                        ERROR
    
  elements.GoTop();
  while ( element = elements.GetNext() )
  {
    if ( (esymbol = element->get_symbol()) && esymbol->get_expressions() )
                                                     ERROR
    if ( *pos != *esymbol->get_name() )              ERROR
    pos++;
    len++;
  }
  if ( isalnum(*pos) || *pos == '_' )                ERROR
RECOVER
  len = UNDEF;
ENDSEQ
  return(len);
}

/******************************************************************************/
/**
\brief  NextExpressions

\return count - 

\param  target_symbol
\param  bexpressions - 
\param  bdata - Pointer to BNF Node
\param  index0
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextExpressions"

int16 BNFExpression :: NextExpressions (BNFSymbol *target_symbol, BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt )
{
  BNFSymbol              *bsymbol = symbol;
  BNFExpression          *texp = NULL;
  int16                   count = 0;
  if ( index0 > 0 )
    bsymbol = bexpressions[index0-1]->get_symbol();
  else
    bsymbol = symbol->TerminalSymbol(&texp,bdata,case_opt);
  
  count = bsymbol->NextExpressions(target_symbol,bexpressions,bdata,index0,case_opt);

  return(count);
}

/******************************************************************************/
/**
\brief  SetSymbol


\param  bsymbol - BNF Symbol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSymbol"

void BNFExpression :: SetSymbol (BNFSymbol *bsymbol )
{

  symbol = bsymbol;

}

/******************************************************************************/
/**
\brief  UpdateData

\return vcode - Validation code

\param  bdata - Pointer to BNF Node
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateData"

int32 BNFExpression :: UpdateData (BNFData *bdata )
{
  int32                   vcode = 0;
  return(vcode);
}

/******************************************************************************/
/**
\brief  ~BNFExpression


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BNFExpression"

                        BNFExpression :: ~BNFExpression ( )
{
  BNFElement        *belement;
  elements.GoTop();
  while ( belement = elements.RemoveTail() )
    delete belement;

}


