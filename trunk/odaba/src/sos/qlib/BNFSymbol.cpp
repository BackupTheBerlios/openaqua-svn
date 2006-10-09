/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    BNFSymbol

\brief    BNF symbol
          A  BNF symbol is  a variable in  a BNF specification, which is defined
          by  one  or  more  BNF  expressions.  Symbols  do  have a neme and may
          consist  of one or more expressions.  Terminal symbols are tokens with
          a  fixed value, which  is stored in  the name. Terminal symbols do not
          habe expressions.

\date     $Date: 2006/08/28 12:39:52,34 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BNFSymbol"

#include  <pdefault.h>
#ifndef   DLL_BNFExpression_HPP
#define   DLL_BNFExpression_HPP
#include  <sBNFExpression.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_BNFSymbol_HPP
#define   DLL_BNFSymbol_HPP
#include  <sBNFSymbol.hpp>
#include  <sDLL.h>
#endif
#include  <sBNFData.hpp>
#include  <sBNFElement.hpp>
#include  <sBNFExpression.hpp>
#include  <sBNFParser.hpp>
#include  <sBNFSymbol.hpp>
#include  <sBNFSymbol.hpp>


/******************************************************************************/
/**
\brief  AddExpression - 



\param  bexpression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExpression"

void BNFSymbol :: AddExpression (BNFExpression *bexpression )
{

  if ( !expressions )
    expressions = new DLL(BNFExpression)();

  expressions->AddTail(bexpression);
  bexpression->SetSymbol(this);

}

/******************************************************************************/
/**
\brief  Analyze - 


\return vcode - Validation code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  bexpressions - 
\param  bdata - Pointer to BNF Node
\param  index0 - 
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Analyze"

int32 BNFSymbol :: Analyze (BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt )
{
  BNFData        *child = top_symbol->CreateChild(bdata,this);
  char           *lastpos = child->Position();
  BNFSymbol      *tsymbol;
  BNFSymbol      *bsymbol;
  BNFExpression  *texp = NULL;
  int32           vcode = 2;
BEGINSEQ
  if ( !bdata->HasData() )                           ERROR
    
  if ( index0 > 0 )
    tsymbol = ElementaryToken(bdata->CurrentToken(),case_opt);
  else
    bsymbol = TerminalSymbol(&texp,bdata,case_opt);
  
  while ( index0 >= 0 && bexpressions[index0] )
  {  
    vcode = bexpressions[index0]->Analyze(bexpressions,child,index0,case_opt);
    if ( vcode != 4 )    
      break;
    bsymbol = index0 > 0 ? bexpressions[index0-1]->get_symbol() : tsymbol;
    top_symbol->RemoveChild(child);
    child = top_symbol->CreateChild(bdata,this);
    index0 = bsymbol->NextExpressions(this,bexpressions,child,index0,case_opt)-1;
  }
      
  if ( vcode >= 4 )                                          ERROR
  
  if ( index0 < 0 )
    child->UpdatePosition(bsymbol);
  else
  {
    child->UpdatePosition();
    child->SetLength(UNDEF);
  }
  
  if ( child->Position() == lastpos )
  { 
    vcode = 5;
    Output("       symbol '%s' accepts empty expressions",name);
    ERROR
  }
  
  if ( terminate )
    child->RemoveChildren(top_symbol);
RECOVER
  top_symbol->SetError(child);
  top_symbol->RemoveChild(child);
  if ( vcode < 4 ) 
    vcode = 4;
ENDSEQ
  return(vcode);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  bdata - Pointer to BNF Node
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Analyze"

int32 BNFSymbol :: Analyze (BNFData *bdata, logical case_opt )
{
  BNFSymbol          *tsymbol;
  BNFExpression      *bexpressions[EXP_VECT_SIZE];
  int                 count;
  int32               index0 = 0;
  int                 vcode = 4;
BEGINSEQ
  memset(bexpressions,0,sizeof(bexpressions));
  
//  tsymbol = ElementaryToken(bdata->CurrentToken(),case_opt);
  tsymbol = TerminalSymbol(bexpressions,bdata,case_opt);
  if ( bexpressions[0] )
    index0 = 1;
  count = tsymbol->LocateExpressions(this,bexpressions,bdata,index0,case_opt);
  
  while ( count >= 0 )
  {  
    vcode = Analyze(bexpressions,bdata,count-1,case_opt);
    if ( vcode != 4 )                                 LEAVESEQ
    count = tsymbol->NextExpressions(this,bexpressions,bdata,0,case_opt);
  }

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

int32 BNFSymbol :: AnalyzeExpression (BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt )
{
  BNFData        *child = top_symbol->CreateChild(bdata,this);
  int32           vcode = 2;
BEGINSEQ
  vcode = bexpressions[index0]->Analyze(bexpressions,child,index0,case_opt);
  
  if ( vcode == 4 )                                          ERROR
  
  child->UpdatePosition();
  child->SetLength(UNDEF);
   
  if ( terminate )
    child->RemoveChildren(top_symbol);
RECOVER
  top_symbol->SetError(child);
  top_symbol->RemoveChild(child);
  if ( vcode < 4 ) 
    vcode = 4;
ENDSEQ
  return(vcode);
}

/******************************************************************************/
/**
\brief  BNFSymbol - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  bparser - 
\param  names - Name
\param  term_opt - Terminate symbol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFSymbol"

     BNFSymbol :: BNFSymbol (BNFParser *bparser, char *names, logical term_opt )
                     :   expressions(NULL),
  terminate(term_opt),
  is_keyword(NO),
  used_in(NULL),
  starting_symbol_in(NULL),
  top_symbol(bparser),
  osymbol(NULL),
  priority(0)
{

BEGINSEQ
  if ( !names || !*names )                          SOSERR(99)
    
  strncpy(name,names,sizeof(name)-1);
  name_len = strlen(names);

  bparser->AddSymbol(this);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFSymbol"

     BNFSymbol :: BNFSymbol ( )
                     : terminate(NO),
  is_keyword(NO),
  name_len(0),
  expressions(NULL),
  used_in(NULL),
  starting_symbol_in(NULL),
  top_symbol(NULL),
  osymbol(NULL),
  priority(0)
{



}

/******************************************************************************/
/**
\brief  CreateAlias - 


\return bsymbol - BNF Symbol

\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAlias"

BNFSymbol *BNFSymbol :: CreateAlias (char *names )
{
  BNFSymbol              *bsymbol = NULL;
  bsymbol = new BNFSymbol(top_symbol,names);
  bsymbol->SetSymbol(this);
  return(bsymbol);
}

/******************************************************************************/
/**
\brief  ElementaryToken - Provide symbol for elementary token
        The  function  provides  the  standard  symbol  for  single  characters 
        (elementary tokens.

\return bsymbol - BNF Symbol

\param  ctoken - Elementary token
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ElementaryToken"

BNFSymbol *BNFSymbol :: ElementaryToken (uint8 ctoken, logical case_opt )
{

//  if ( !case_opt )
//    ctoken = toupper(ctoken);
  return(top_symbol->ElementaryToken(ctoken));



}

/******************************************************************************/
/**
\brief  GetExpCount - 


\return count - 

\param  bexpressions - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExpCount"

int16 BNFSymbol :: GetExpCount (BNFExpression **bexpressions )
{
  int16                   count = 0;
  while ( bexpressions[count] )
    count++;
  return(count);
}

/******************************************************************************/
/**
\brief  HasExpressions - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasExpressions"

logical BNFSymbol :: HasExpressions ( )
{

  return ( expressions && expressions->GetCount() > 0 ? YES : NO);

}

/******************************************************************************/
/**
\brief  Initialize - 



\param  bstring - 
\param  ctoken - Elementary token
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void BNFSymbol :: Initialize (BNFParser *bstring, uint8 ctoken )
{

  name[0] = ctoken;
  name[1] = 0;
  name_len = 1;

  top_symbol = bstring;

}

/******************************************************************************/
/**
\brief  IsKeyword - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsKeyword"

logical BNFSymbol :: IsKeyword ( )
{

  return(is_keyword);

}

/******************************************************************************/
/**
\brief  LocateExpressions - 


\return count - 

\param  target_symbol - 
\param  bexpressions - 
\param  bdata - Pointer to BNF Node
\param  index0 - 
\param  case_opt - Case sensitive (not supported)
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateExpressions"

int16 BNFSymbol :: LocateExpressions (BNFSymbol *target_symbol, BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt, logical chk_opt )
{
  BNFExpression          *bexpression;
  int                     count = index0;
BEGINSEQ
  if ( index0+1 >= EXP_VECT_SIZE )                   SOSERR(99)  // too many levels
    
  memset(bexpressions+index0,0,sizeof(void *)*(EXP_VECT_SIZE-index0));
  
  if ( !chk_opt && this == target_symbol )           LEAVESEQ
  if ( !starting_symbol_in )                         ERROR
  
  DLL(BNFExpression)      cursor(*starting_symbol_in);
  cursor.GoTop();
  while ( bexpression = cursor.GetNext() )
  {
    count = index0;
    
    if ( !count && bexpression->get_symbol()->IsKeyword() )
      continue;
      
    while ( count-- )      // check for recursion
      if ( bexpressions[count] == bexpression )      ERROR
        
    bexpressions[index0]   = bexpression;
    count = bexpression->LocateExpressions(target_symbol,bexpressions,bdata,index0+1,case_opt);
    if ( count > AUTO )                              LEAVESEQ
  }
  ERROR
RECOVER
  count = AUTO;
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  NextExpressions - 


\return count - 

\param  target_symbol - 
\param  bexpressions - 
\param  bdata - Pointer to BNF Node
\param  index0 - 
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextExpressions"

int16 BNFSymbol :: NextExpressions (BNFSymbol *target_symbol, BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt )
{
  BNFExpression          *bexpression;
  int                     count = AUTO;
  logical                 is_keyword = NO;
  int                     i;
BEGINSEQ
  if ( this == target_symbol )                       ERROR
  
  if ( bexpressions[index0+1] && bexpressions[index0+1]->get_symbol()->IsKeyword() )
    is_keyword = YES;
    
  if ( !starting_symbol_in )                         ERROR
  
  DLL(BNFExpression)      cursor(*starting_symbol_in);
  if ( !bexpressions[index0] ||
       !cursor.Find(bexpressions[index0]) )          ERROR
  
  while ( bexpression = cursor.GetNext() )
    if ( (count = bexpression->LocateExpressions(target_symbol,bexpressions,bdata,index0+1,case_opt)) > AUTO )
    {
      i = 0;
      while ( i < index0 )
        if ( bexpressions[i++] == bexpression )
          count = -1;
      if ( count >= 0 )
      {
        bexpressions[index0] = bexpression;
        LEAVESEQ
      }
    }

  if ( index0 <= 0 ||  
       (index0 == 1 && bexpressions[0]->get_symbol()->IsKeyword()) )
                                                     ERROR
  count = bexpressions[index0-1]->NextExpressions(target_symbol,bexpressions,bdata,index0-1,case_opt);

RECOVER
  count = AUTO;
ENDSEQ
 return(count);
}

/******************************************************************************/
/**
\brief  Optimize - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Optimize"

logical BNFSymbol :: Optimize ( )
{
  BNFExpression          *suc_ex;
  BNFExpression          *pre_ex;
  int                     indx0 = 0;
  logical                 order_changed = YES;
  logical                 term = NO;
  if ( starting_symbol_in )
  {
    while ( order_changed )
    {
      order_changed = NO;
      indx0 = 0;
      pre_ex = starting_symbol_in->GetObjectInst(indx0);
      while ( suc_ex = starting_symbol_in->GetObjectInst(++indx0) )
      {
        if ( pre_ex->get_symbol()->get_priority() < suc_ex->get_symbol()->get_priority() )
        {
          suc_ex = starting_symbol_in->RemoveAt();
          starting_symbol_in->Find(pre_ex);
          starting_symbol_in->InsertBefore(suc_ex);
          order_changed = YES;
        }
        else
          pre_ex = suc_ex;
      }
    }
  }  


  return(term);
}

/******************************************************************************/
/**
\brief  Output - 


\return term - Success

\param  fstring - 
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
\param  parm3 - Third message variable
\param  parm4 - 
\param  parm5 - 
\param  parm6 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical BNFSymbol :: Output (char *fstring, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5, char *parm6 )
{
  char                    string[4096];
  logical                 term = NO;
  if ( !fstring )
    fstring = "\n*** format string missing for output command ***";
  
  sprintf(string,fstring,parm1,parm2,parm3,parm4,parm5);
  SystemOutput(string,NO,YES);


  return(term);
}

/******************************************************************************/
/**
\brief  RegisterFirstSymbol - 



\param  bexpression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterFirstSymbol"

void BNFSymbol :: RegisterFirstSymbol (BNFExpression *bexpression )
{

  if ( bexpression )
  {
    if ( !starting_symbol_in )
      starting_symbol_in = new DLL(BNFExpression)();

    starting_symbol_in->AddTail(bexpression);
  }

}

/******************************************************************************/
/**
\brief  RegisterUpper - 



\param  bsymbol - BNF Symbol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterUpper"

void BNFSymbol :: RegisterUpper (BNFSymbol *bsymbol )
{

  if ( bsymbol )
  {
    if ( !used_in )
      used_in = new DLL(BNFSymbol)();

    used_in->AddTail(bsymbol);
  }

}

/******************************************************************************/
/**
\brief  SetKeyword - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKeyword"

void BNFSymbol :: SetKeyword ( )
{

  if ( this) 
  {
    terminate = YES;
    is_keyword = YES;
  }

}

/******************************************************************************/
/**
\brief  SetPriority - 



\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPriority"

void BNFSymbol :: SetPriority (int32 indx0 )
{

  priority = indx0;

}

/******************************************************************************/
/**
\brief  SetSymbol - 



\param  bsymbol - BNF Symbol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSymbol"

void BNFSymbol :: SetSymbol (BNFSymbol *bsymbol )
{

  if ( bsymbol->get_osymbol() )
    bsymbol = bsymbol->get_osymbol();

  osymbol = bsymbol;

}

/******************************************************************************/
/**
\brief  SetTerminal - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTerminal"

void BNFSymbol :: SetTerminal ( )
{

  if ( this) 
    terminate = YES;

}

/******************************************************************************/
/**
\brief  SetupStartingSymbols - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupStartingSymbols"

void BNFSymbol :: SetupStartingSymbols ( )
{
  BNFExpression          *bexpression;
  BNFElement             *belement;
  if ( expressions )
  {
    expressions->GoTop();
    while ( bexpression = expressions->GetNext() )
    {
      belement = bexpression->get_elements().GetHead();
      while ( belement && belement->get_optional() )
        if ( belement = bexpression->get_elements().GetNext() )
          belement->get_symbol()->RegisterFirstSymbol(bexpression);
    }
  }


}

/******************************************************************************/
/**
\brief  TerminalSymbol - 


\return bsymbol - BNF Symbol

\param  bexpressions - 
\param  bdata - Pointer to BNF Node
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TerminalSymbol"

BNFSymbol *BNFSymbol :: TerminalSymbol (BNFExpression **bexpressions, BNFData *bdata, logical case_opt )
{
  BNFData          *child;
  BNFExpression    *bexpression;
  int32             len;
  BNFSymbol        *tsymbol = NULL;
BEGINSEQ
  if ( !(tsymbol = ElementaryToken(bdata->CurrentToken(),case_opt)) )
                                                     ERROR
  if ( !tsymbol->get_starting_symbol_in() )          ERROR

  if ( bdata->HasPreceedingChar() )                  LEAVESEQ
  if ( bdata->IsTerminalSymbol() )                   LEAVESEQ
    
  DLL(BNFExpression)      cursor(*tsymbol->get_starting_symbol_in());
  cursor.GoTop();
  while ( bexpression = cursor.GetNext() )
  {
    if ( len = bexpression->MatchKeyword(bdata) )
    {
      bexpressions[0] = bexpression;
      tsymbol = bexpression->get_symbol();
      break;
    }
  }

RECOVER
// im Fehlerfall nicht NULL setzen!!!
ENDSEQ
  return(tsymbol);
}

/******************************************************************************/
/**
\brief  ~BNFSymbol - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BNFSymbol"

     BNFSymbol :: ~BNFSymbol ( )
{
  BNFExpression       *bexpression;
  if ( expressions )
  {
    expressions->GoTop();
    while ( bexpression = expressions->RemoveTail() )
      delete bexpression;
    delete expressions;
    expressions = NULL;
  }

  delete starting_symbol_in;
  starting_symbol_in = NULL;
  
  delete used_in;
  used_in = NULL;

}


