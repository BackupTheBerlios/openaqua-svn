/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    BinaryList

\brief    


\date     $Date: 2006/04/20 18:09:35,29 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BinaryList"

#include  <pogui7.h>
#include  <cclstlis.h>
#include  <sBinaryList.hpp>



/******************************************************************************/
/**
\brief  Add - 


\return 

\param  pitem - Pointer to the item
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical BinaryList :: Add (void *pitem )
{
  void            *pkey;
  logical          term = NO;
BEGINSEQ
  CLPosition    p;

  pkey = OnGetKey(pitem);

  if ( !GetPositionByKey(p,pkey) )                   ERROR // error if duplicated
  if ( InsertAt(pitem,p) )                           ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  BinaryList - 



\param  sizeItem - Item size
\param  fSignalDelete - Generate dletion event
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BinaryList"

                        BinaryList :: BinaryList (size_t sizeItem, logical fSignalDelete )
                     : ClusteredList (sizeItem,fSignalDelete)
{



}

/******************************************************************************/
/**
\brief  CheckOrderIntegrity - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckOrderIntegrity"

logical BinaryList :: CheckOrderIntegrity ( )
{
  void           *pitem;
  void           *pitem2;
  logical         term = NO;
BEGINSEQ
  CLPosition   p;
  
  GetHeadPosition(p);
  while ( p.validread )
  {
    pitem = GetNext(p);
    if ( p.validread )
    {  
      pitem2 = GetAt(p);  
      if ( OnCompare(OnGetKey(pitem),OnGetKey(pitem2)) >= 0 )
                                                     ERROR
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteByKey - 


\return term

\param  pkey - 
\param  fFree - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteByKey"

logical BinaryList :: DeleteByKey (void *pkey, logical fFree )
{
  logical                 term = NO;
BEGINSEQ
  CLPosition   p;

  if ( GetPositionByKey(p,pkey) )                    ERROR
  if ( DeleteAt(p,fFree) )                           ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetByKey - 


\return res - 

\param  pkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetByKey"

void *BinaryList :: GetByKey (void *pkey )
{
  void*                 res = NULL;
BEGINSEQ
  CLPosition   p;

  if ( GetPositionByKey(p,pkey) )                    ERROR

  res = GetAt(p);
RECOVER
  res= NULL;
ENDSEQ
  return(res);
}

/******************************************************************************/
/**
\brief  GetPositionByItem - 


\return term - 

\param  rCLPosition - 
\param  pitem - Pointer to the item
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPositionByItem"

logical BinaryList :: GetPositionByItem (CLPosition &rCLPosition, void *pitem )
{
  void     *pkey;
  pkey = OnGetKey(pitem);



  return GetPositionByKey(rCLPosition,pkey);
}

/******************************************************************************/
/**
\brief  GetPositionByKey - 


\return term - 

\param  rCLPosition - 
\param  pkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPositionByKey"

logical BinaryList :: GetPositionByKey (CLPosition &rCLPosition, void *pkey )
{
  int      l     = 0;
  int      h     = clusterCount - 1;
  logical  found = NO;
  size_t   i;
  int      cf;
  char    *ll;


  if ( count == 0 )
    return GetHeadPosition(rCLPosition);

  // find cluster

  ppCLUSTER cs = (ppCLUSTER)clusters;

  while ( l <= h )
  {
    i  = ( l + h ) / 2;
    if ( (cf = OnCompare(OnGetKey(&(cs[i]->data)),pkey)) < 0 )
      l = i + 1;
    else
    {
      if ( !cf )
      {
        l     = i;
        found = YES;
        break;
      }
      h = i - 1;
    }
  }
  
  if ( !found && l > 0 ) 
    l--; // for the item is at the page previous

  pCLUSTER c = cs[l];
  rCLPosition.clnum   = l;
  rCLPosition.cluster = c;

  if ( found ) 
    l = 0;
  else
  {
    // find right item
  
    ll = &c->data;
    l  = 0;
    h  = c->count - 1;

    while ( l <= h )
    {
      i  = ( l + h ) / 2;
      if ( (cf = OnCompare(OnGetKey(&ll[i * itemSize]),pkey)) < 0 )
        l = i + 1;
      else
      {
        if ( !cf )
        {
          l     = i;
          found = YES;
          break;
        }
        h = i - 1;
      }
    }
  }

  rCLPosition.clindex    = l;
  rCLPosition.validwrite = YES;
  rCLPosition.validread  = ( (size_t) l ) < c->count;
  return !found;
}

/******************************************************************************/
/**
\brief  OnCompare - 


\return res - 

\param  pkey1 - 
\param  pkey2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnCompare"

int32 BinaryList :: OnCompare (void *pkey1, void *pkey2 )
{

  return 0;

}

/******************************************************************************/
/**
\brief  OnGetKey - 


\return pitem - Pointer to the item

\param  pitem - Pointer to the item
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnGetKey"

void *BinaryList :: OnGetKey (void *pitem )
{

  return pitem;

}


