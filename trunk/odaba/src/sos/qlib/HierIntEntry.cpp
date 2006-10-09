/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    HierIntEntry

\brief    Hierarchie Interval Entry
          The  interval  entry  describes  the  upper  and lower boundery of the
          interval.  High  and  low  value  are  included  in  the interval. The
          interval  can  be  an  exclusive  or  an  inclusive  interval.  It  is
          associated  with  an  sub-intervall  list  that  contains  a  list  of
          inclusions  ( if  the interval  is exclusive)  or a list of exclusions
          (if teh interval is inclusive).

\date     $Date: 2006/03/12 19:21:43,56 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "HierIntEntry"

#include  <pdefault.h>
#include  <igvtx.h>
#include  <sHierarchicalIntervall.hpp>
#include  <sHierIntEntry.hpp>


/******************************************************************************/
/**
\brief  HierIntEntry

-------------------------------------------------------------------------------
\brief i0


\param  rule -
\param  exclude -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HierIntEntry"

                        HierIntEntry :: HierIntEntry (char *rule, logical exclude )
                     : low(),
  high(),
  sub_list(NULL)
{
  char     *pos  = rule;
  char     *expr = NULL;
  char     *intv = NULL;
  char     *end  = NULL;
  int       len;
  while ( *pos && *pos == ' ' )
    pos++;
  expr = strchr(pos,'(');
  intv = strchr(pos,'-');
    
  if ( expr && expr < intv )
    end = expr, intv = NULL;
  if ( !end && intv )
    end = intv;
  if ( !end )
    end = pos + strlen(pos);
   
  len = MIN(ID_SIZE,end-pos);
  memset(low,0,ID_SIZE);
  memset(high,0xFF,ID_SIZE);
  memcpy(low,pos,len);
    
  end = NULL;
  if ( intv )
  {
    pos = intv+1;
    while ( *pos && *pos == ' ' )
      pos++;
    if ( expr )
      end = expr;
    if ( !end )
      end = pos + strlen(pos);
    len = MIN(ID_SIZE,end-pos);
  }
  memcpy(high,pos,len);

  if ( expr )
  {
    if ( end = gvtsfbp(expr,UNDEF) )
      *(end-1) = 0;
    sub_list = new HierarchicalIntervall(expr+1,exclude);
  }


}

/******************************************************************************/
/**
\brief i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HierIntEntry"

                        HierIntEntry :: HierIntEntry ( )
                     : low(),
  high(),
  sub_list(NULL)
{



}

/******************************************************************************/
/**
\brief  Includes

\return cond - Return value

\param  string - String value
\param  exclude -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Includes"

logical HierIntEntry :: Includes (char *string, logical exclude )
{
  logical                 contained = NO;
  if ( contained = memcmp(low,string,sizeof(low)) <= 0 &&
                   memcmp(string,high,sizeof(low)) <= 0   )
    contained = !sub_list->Includes(string);

  if ( exclude ) 
    contained = !contained;
  return(contained);
}

/******************************************************************************/
/**
\brief  ~HierIntEntry


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~HierIntEntry"

                        HierIntEntry :: ~HierIntEntry ( )
{



}


