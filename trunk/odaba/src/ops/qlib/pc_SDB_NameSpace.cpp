/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    pc_SDB_NameSpace



\date     $Date: 2006/05/14 11:29:34,28 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_NameSpace"

#include  <pops7.h>
#include  <sPropertyHandle.hpp>
#include  <spc_SDB_NameSpace.hpp>


/******************************************************************************/
/**
\brief  Scope

\return scope

\param  string
\param  len_ref
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Scope"

char *pc_SDB_NameSpace :: Scope (char *string, int32 &len_ref )
{
  char          *name;
  char          *nextpos;
  int16          len;
BEGINSEQ
  pc_SDB_NameSpace   parent(GPH("parent"));

  if ( parent(0) )
  {
    nextpos = parent.Scope(string,len_ref);
    if ( len_ref < 2 )                                  ERROR
    {
      strcpy(nextpos,"::");
      len_ref -= 2;
      nextpos += 2;
    }
  }
  else 
    nextpos = string;
    
  name = GetString("sys_ident");
  len = MIN(strlen(name),len_ref);
  memcpy(nextpos,name,len);
  len_ref -= len;
  nextpos += len;
  *nextpos = 0;
  if ( len < strlen(name) )                             ERROR

RECOVER
  len_ref = AUTO;
ENDSEQ
  return(nextpos);
}

/******************************************************************************/
/**
\brief  pc_SDB_NameSpace

-------------------------------------------------------------------------------
\brief  i00


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_NameSpace"

     pc_SDB_NameSpace :: pc_SDB_NameSpace (PropertyHandle *prophdl )
                     : pc_SDB_Type(prophdl)
{
}

/******************************************************************************/
/**
\brief  i01


\param  dbhandle - 
\param  accopt_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_NameSpace"

     pc_SDB_NameSpace :: pc_SDB_NameSpace (DatabaseHandle &dbhandle, PIACC accopt_w )
                     : pc_SDB_Type(dbhandle,"SDB_NameSpace",accopt_w)
{
}

/******************************************************************************/
/**
\brief  i02


\param  dbhandle - 
\param  strnames
\param  accopt_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_NameSpace"

     pc_SDB_NameSpace :: pc_SDB_NameSpace (DatabaseHandle &dbhandle, char *strnames, PIACC accopt_w )
                     : pc_SDB_Type(dbhandle,strnames,accopt_w)
{
}


