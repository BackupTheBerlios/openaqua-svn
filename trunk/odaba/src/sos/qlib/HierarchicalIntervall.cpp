/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    HierarchicalIntervall

\brief    Hirarchical Intervall list


\date     $Date: 2006/03/12 19:21:43,75 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "HierarchicalIntervall"

#include  <pdefault.h>
#include  <sHierarchicalIntervall.hpp>


/******************************************************************************/
/**
\brief  GetExpression

\return expr_pos -

\param  string - String value
\param  expression -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExpression"

char *HierarchicalIntervall :: GetExpression (char *string, char *expression )
{
  char      *end;
  char      *expr;
  char      *expr_pos;
  end  = strchr(string,';');
  expr = strchr(string,'(');

  if ( expr && end > expr )
    end = gvtsfbp(expr,UNDEF);
  if ( !end )
    end = string + strlen(string);
    
  memcpy(expression,string,end-string);
  expression[end-string] = 0;
  while ( *end && *end == ';' )
    end++;
  expr_pos = end;

  return(expr_pos);
}

/******************************************************************************/
/**
\brief  HierarchicalIntervall


\param  rule -
\param  exclude -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HierarchicalIntervall"

                        HierarchicalIntervall :: HierarchicalIntervall (char *rule, logical exclude )
                     : GSRT(HierIntEntry)(5,sizeof(HierIntEntry),ID_SIZE,
     offsetof(HierIntEntry,high)+1,'C',YES),
  excludes(exclude)
{
  char     *position = rule;
  char      expression[1000];

  while ( position && *position )
  {
    position = GetExpression(position,expression);
    
    HierIntEntry   hintentry(expression,!excludes);
    AddEntry(&hintentry);
  }

}

/******************************************************************************/
/**
\brief  Includes - Is value included


\return cond - Return value

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Includes"

logical HierarchicalIntervall :: Includes (char *string )
{
  char          value[ID_SIZE];
  int32         indx0 = 0;
  logical       cond  = excludes;
  HierIntEntry *entry = NULL;
BEGINSEQ
  while ( entry = GetEntry(++indx0) )
    if ( entry->Includes(value,excludes) )           LEAVESEQ

  ERROR
RECOVER
  cond = !cond;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ~HierarchicalIntervall


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~HierarchicalIntervall"

                        HierarchicalIntervall :: ~HierarchicalIntervall ( )
{



}


