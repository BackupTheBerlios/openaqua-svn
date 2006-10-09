/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_View

\brief    View definition
          A  view definition allows defining the  elements of a database view. A
          view  is  considered  as  method  of  a structure (or a combination of
          structures),  which is called the  structural (or intensional) base of
          the  view. The structural base is defined  in the 'from' clause of the
          view.
          The  result of a view  can be stored as  persistent view by making the
          view  persistent. This allows  defining one or  more ODABA extents for
          storing  the view. Persistent views are not updated automatically, but
          must be updated by the user.
          The  view  structure  is  defined  by  the  properties (attributes and
          references)  in the  view. Defining  relationships makes sense in case
          of  persistent views, only.  All properties defined  for a view should
          have  a  constraint,  which  defines  the  expression  or path for the
          property.  Properties, which do not  have a constraint definition, can
          be  evaluated in an appropriate context class or the view structure or
          the property. 
          You  may  define  views  based  on  views  or properties based on view
          structures.  When a property is defined with a view structure as type,
          the  view applies on the source for  the property, which is defined in
          the  constraint.  When  applying  a  view to a property, you may refer
          directly  to a source property (or  property path or expression) or to
          a local view extent. 
          Aggregated  view  can  be  defined  by  using  the  'group_by' clause.
          Aggregated  views always contain a 'value' and a 'partition' property.
          Other  properties can  be defined  by means of aggregation expressions
          for the 'partition' collection.
          You  can define one or  more keys for the  view, which consist of view
          attributes.  Those  keys  can  be  used  for  creating  indexes  for 
          persistent  views. Aggregated views do  always have an identifying key
          '__ident_key'.
          Views  can  be  used  as  reading or updating views. You can, however,
          update  only  those  properties,  which  are connected with its source
          directly  via property paths. This is possible also via several steps,
          i.e.  when  defining  views  on  views.  As  soon,  as  at  least  one
          expression  is  defined  on  the  way  to  the  database  source for a
          property, this property cannot be updated.

\date     $Date: 2006/03/13 21:30:41,62 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODC_View"

#include  <pfmodel.h>
#include  <sODC_View.hpp>


/******************************************************************************/
/**
\brief  GetCollection - 


\return view_path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCollection"

char *ODC_View :: GetCollection ( )
{
  char                    view_path[4000];
  char                   *vpath;
  int                     len = 0;
  int32                   indx0 = 0;
  logical                 first = YES;
BEGINSEQ
  PH(&from,path)
  while ( from.Get(indx0++) )
  {
    if ( !first )
    {
      strcat(view_path,",");
      len++;
    }
    else first = NO;
    vpath = path.GetString();
    if ( (len += strlen(vpath)) > sizeof(view_path)-3 )
                                                     SDBERR(99)
    strcat(view_path,vpath);
  }
  vpath = strdup(view_path);
RECOVER
  vpath = NULL;
ENDSEQ
  return(vpath);
}

/******************************************************************************/
/**
\brief  GetExpression

\return view_path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExpression"

char ODC_View :: GetExpression ( )
{
  char                    view_path;

  return(view_path);
}

/******************************************************************************/
/**
\brief  GetPostCondition - 


\return expression

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPostCondition"

char *ODC_View :: GetPostCondition ( )
{
  char                   *expr = NULL;
  return( strdup(having.GetString()) );
  return(expr);
}

/******************************************************************************/
/**
\brief  GetPreCondition - 


\return expression

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPreCondition"

char *ODC_View :: GetPreCondition ( )
{
  char                   *expr = NULL;
  return( strdup(where.GetString()) );
  return(expr);
}

/******************************************************************************/
/**
\brief  GetViewPath

\return view_path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetViewPath"

char ODC_View :: GetViewPath ( )
{
  char                    view_path;

  return(view_path);
}

/******************************************************************************/
/**
\brief  ODC_View - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODC_View"

                        ODC_View :: ODC_View ( )
                     : SDB_Structure (),
  from(),
  where(),
  group_by(),
  having()
{



}

/******************************************************************************/
/**
\brief  SetProperties

\return term

\param  view_def
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProperties"

logical ODC_View :: SetProperties (char view_def )
{
  logical                 term = NO;

  return(term);
}


