/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|17:41:08,71}|(REF)
\class    ParmList

\brief    


\date     $Date: 2006/04/10 22:51:40,45 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ParmList"

#include  <pdefault.h>
#include  <sExpressionReference.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <sUtilityHandle.hpp>
#include  <sParmList.hpp>


/******************************************************************************/
/**
\brief  AddParm - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00


\param  prophdl_ptr - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddParm"

logical ParmList :: AddParm (PropertyHandle *prophdl_ptr )
{
  logical                 term = NO;
  if ( owner )
    Add(new PropertyHandle(prophdl_ptr));
  else
    Add(prophdl_ptr);

  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  prophdl - 
\param  parmstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddParm"

logical ParmList :: AddParm (PropertyHandle &prophdl, char *parmstr )
{
  PropertyHandle        ph;
  PropertyHandle        *phptr;
  int32                   intval;
  char                  *pos;
  int                    len;
  logical                term = NO;
  if ( *parmstr >= '0' && *parmstr <= '9' )
  {
    intval = atoi(parmstr);
    ph.Open(intval);
  }
  else if ( *parmstr == '\'' )
  {
    if ( pos = gvtsfbp(parmstr,UNDEF) )
      len = pos-(parmstr+1);
    parmstr = strdup(parmstr+1);
    if ( len )
      parmstr[len] = 0;
    ph.Open(parmstr);
    free(parmstr);
  }
  else if ( phptr = prophdl.GPH(parmstr) )
    ph.Open(phptr);
  else
    ph.Open(parmstr);

  AddParm(&ph);
    
  

  return(term);
}

/******************************************************************************/
/**
\brief  ClearList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearList"

void ParmList :: ClearList ( )
{
  int16     parm_cnt;
  parm_cnt = GetSize();
  if ( owner )
    while ( parm_cnt-- )
    {
      delete (*this)[parm_cnt];
      (*this)[parm_cnt] = NULL;
    }
  Clear();

}

/******************************************************************************/
/**
\brief  Compare - 


\return term - Termination code

\param  parameters - 
\param  convert - Conversion option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compare"

logical ParmList :: Compare (ParmList *parameters, logical convert )
{
  int16                   count = GetSize();
  int16                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  if ( count < parameters->GetSize() )               ERROR
    
  while ( indx0 < count )
  {
    if ( indx0 < parameters->GetSize() )
    {
      if ( (*this)[indx0]->CompareType(*(*parameters)[indx0],convert) )
                                                     ERROR
    }
    else
      if ( !(*this)[indx0]->GetDescription()->fmcbinit )
                                                     ERROR
    indx0++;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Copy - 
        hier muss mal beschrieben werden, welche implementierung was tut

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0


\param  parameters - 
\param  field_copy - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical ParmList :: Copy (ParmList *parameters, logical field_copy )
{
  int16      indx = 0;
  int16      cnt  = parameters ? parameters->GetSize() : 0;
  DBField   *field_ptr;
  logical     term = NO;
  DBFieldDef *fmcbptr;
  while ( indx < cnt )
  {
    if ( field_copy )
    {
      field_ptr = new DBField();
      if ( fmcbptr=(*parameters)[indx]->GetDescription() )
      {
        field_ptr->SetDescription(fmcbptr);
        
        if ( (*parameters)[indx]->GetArea() )
        {
          if ( fmcbptr->fmcbityp==-99 )
            field_ptr->SetArea((*parameters)[indx]->GetArea());
          else
          {
            field_ptr->AllocateArea();
            *field_ptr = *(*parameters)[indx];
          }
        }
      }
      Add(field_ptr);
    }
    else
      Add(new DBField(*(*parameters)[indx]));
    indx++;  
  }

  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  parameters - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical ParmList :: Copy (ParmList *parameters )
{
  int16      indx = 0;
  int16      cnt  = parameters ? parameters->GetSize() : 0;
  logical    term = NO;
  ClearList();

  while ( indx < cnt )
  {
    AddParm((*parameters)[indx]);
    indx++;  
  }

  return(term);
}

/******************************************************************************/
/**
\brief  Get - 


\return prophdl_ptr - Property Handle
-------------------------------------------------------------------------------
\brief  i0


\param  varnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

PropertyHandle *ParmList :: Get (char *varnames )
{
  PropertyHandle           *ph = NULL;
  DBFieldDef               *fielddef;
  char                      vname[ID_SIZE];
  int32                     indx0 = 0;
  logical                   term = NO;
BEGINSEQ
  if ( !varnames || !*varnames )                     ERROR
  gvtxstb(vname,varnames,ID_SIZE);

  while ( ph = GetAt(indx0++) )
    if ( (fielddef = ph->GetDescription()) &&
         !memcmp(fielddef->fmcbname,vname,ID_SIZE) )
      break;
RECOVER
  ph = NULL;
ENDSEQ
  return(ph);
}

/******************************************************************************/
/**
\brief  i01


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

PropertyHandle *ParmList :: Get (PropertyHandle &prophdl )
{
  PropertyHandle           *ph = NULL;
  DBFieldDef               *fielddef;
  if ( fielddef = prophdl.GetDescription() )
    ph = Get(fielddef->fmcbname);
  return(ph);
}

/******************************************************************************/
/**
\brief  ParmList - 


-------------------------------------------------------------------------------
\brief  i0


\param  owning - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParmList"

                        ParmList :: ParmList (logical owning )
                     : DPA(PropertyHandle) (),
  owner(owning)
{



}

/******************************************************************************/
/**
\brief  i03


\param  prophdl - 
\param  parm_list - Parameter list
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParmList"

                        ParmList :: ParmList (PropertyHandle &prophdl, char **parm_list )
                     : DPA(PropertyHandle) (),
  owner(YES)
{
  int            i = 0;
  while ( parm_list[i] )
    AddParm(prophdl,parm_list[i++]);


}

/******************************************************************************/
/**
\brief  i1


\param  plist_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParmList"

                        ParmList :: ParmList (ParmList &plist_ref )
                     : DPA(PropertyHandle) (),
  owner(YES)
{

  Copy(&plist_ref,YES);

}

/******************************************************************************/
/**
\brief  i2


\param  parm_string
\param  separators - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParmList"

                        ParmList :: ParmList (char *parm_string, char *separators )
                     : DPA(PropertyHandle) (),
  owner(YES)
{
  DBField  *dbfield_ptr;
  char      work_string[1000];
  char     *token;
BEGINSEQ
  gvtxbts(work_string,parm_string,sizeof(work_string)-1);
  token = strtok(work_string,separators);
  
  while ( token )
  {
    if ( !(dbfield_ptr = new DBField(token)) )       SDBERR(95)
                                                     SDBCERR
    Add(dbfield_ptr);
    token = strtok(NULL,separators);
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  operator= - 


\return term - Termination code

\param  plist_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

logical ParmList :: operator= (ParmList &plist_ref )
{
  int16              count = MIN(GetSize(),plist_ref.GetSize());
  int16              indx0 = 0;
  logical            term = NO;
BEGINSEQ
  if ( GetSize() < plist_ref.GetSize() )             SDBERR(300)
  
  while ( indx0 < count )
  {
    if ( plist_ref[indx0]->GetArea() )
      *(*this)[indx0] = *plist_ref[indx0];
    
    indx0++;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ParmList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ParmList"

                        ParmList :: ~ParmList ( )
{
  int16     parm_cnt;
  if ( owner )
    ClearList();

}


