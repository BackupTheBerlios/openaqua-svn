/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ClusteredList

\brief    Clustered list
          The  list does administrate a  set of items of  any type. Items can be
          accessed  by  index  or  by  position. The list can be browsed in both
          directions. 
          The  list moves the  items into clusters  with a minimum and a maximum
          size.  The minimum size is used for cluster reorganisation, when items
          have been deleted. 
          The  list generates several on-events, which  can be overloaded by the
          application to free or allocate resources.
          E

\date     $Date: 2006/06/21 18:54:14,73 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ClusteredList"

#include  <pogui7.h>
#include  <cclstlis.h>
#include  <sClusteredList.hpp>


/******************************************************************************/
/**
\brief  Append - Appemd an item
        The  item passed will  be appended to  the end of  the list. The item is
        moved  according to its size (item size)  as it has been defined for the
        list.

\return  - 

\param  pitem - Pointer to the item
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

size_t ClusteredList :: Append (void *pitem )
{
  CLPosition   tail;

  if ( !GetTailPosition(tail) ) 
    GetNextPosition(tail);

  InsertAt(pitem,tail);



  return count - 1;
}

/******************************************************************************/
/**
\brief  CanGetAt - 


\return res - 

\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CanGetAt"

logical ClusteredList :: CanGetAt (CLPosition &rCLPosition )
{

  return rCLPosition.validread;

}

/******************************************************************************/
/**
\brief  CanWriteAt - 


\return res - 

\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CanWriteAt"

logical ClusteredList :: CanWriteAt (CLPosition &rCLPosition )
{

  return rCLPosition.validwrite;

}

/******************************************************************************/
/**
\brief  ClusteredList - Constructor


\return term - 

\param  sizeItem - Item size
\param  fSignalDelete - Generate dletion event
\param  sizeLower_64 - Minimum item count
\param  sizeUpper_256 - Maximum Item number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClusteredList"

     ClusteredList :: ClusteredList (size_t sizeItem, logical fSignalDelete, size_t sizeLower_64, size_t sizeUpper_256 )
                     : count(0),
  clusters(NULL),
  clusterCount(0),
  itemSize(sizeof(void*)),
  signalDelete(NO),
  lower(sizeLower_64),
  upper(sizeUpper_256)
{

  this->itemSize     = sizeItem;
  this->signalDelete = fSignalDelete;
  
  DeleteAll();

}

/******************************************************************************/
/**
\brief  Delete - Delete item
        The  function removes the  first item from  the list, which is identical
        with the passed item. The function generated an OnDeleteItem event.

\return term - 

\param  pitem - Pointer to the item
\param  fFree_NO - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ClusteredList :: Delete (void *pitem, logical fFree_NO )
{
  CLPosition   p;
  logical            term = NO;

BEGINSEQ
  if ( GetPositionByItem(p,pitem) )                   ERROR
  if ( DeleteAt(p,fFree_NO) )                        ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteAll - Remove all items
        The function removes all items from the list.

\return term - 

\param  fFree_NO - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteAll"

logical ClusteredList :: DeleteAll (logical fFree_NO )
{
  CLPosition    p;
  void               *pitem;
  size_t              i    = 0;
  logical             term = NO;
  if ( count > 0 )
  {
    if ( signalDelete || fFree_NO )
    {
      GetHeadPosition( p );
      while( p.validread )
      {
        pitem = GetNext(p);
        OnDeleteItem(pitem,fFree_NO);
      }
    }
  }

  ppCLUSTER c = (ppCLUSTER) clusters;

  for ( i = 0; i < clusterCount; i++ ) 
    free( c[i] );

  if ( clusters ) 
    free(clusters);

  count                    = 0;
  clusterCount             = 1;
  clusters                 = malloc(sizeof(void *));
  ((ppCLUSTER)clusters)[0] = (pCLUSTER)MakeCluster();
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteAt - Delete by position
        The  function removes an item from the list by position. The position in
        a cluster list can be retrieved, e.g. with GetPositionByIndex().

\return term - 

\param  rCLPosition - 
\param  fFree_NO - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteAt"

logical ClusteredList :: DeleteAt (CLPosition &rCLPosition, logical fFree_NO )
{
  char      *l;
  char      *l0;
  char      *dl;
  char      *dr;
  size_t     ci;
  size_t     nl;
  size_t     nr;  
  size_t     al;
  size_t     ar;
  size_t     bl;
  size_t     br;
  logical    term = NO;
BEGINSEQ
  if ( !rCLPosition.validread )                ERROR

  pCLUSTER cl = (pCLUSTER)rCLPosition.cluster;

  count--;
  cl->count--;

  l  = &cl->data;
  l0 = &l[rCLPosition.clindex * itemSize];

  OnDeleteItem(l0,fFree_NO);

  memmove(l0, 
          l0 + itemSize,
          (cl->count - rCLPosition.clindex) * itemSize);

  if ( cl->count < lower )
  {
    // arrange clusters
    ppCLUSTER c  = (ppCLUSTER) clusters;
    pCLUSTER  cr;
    
    ci = rCLPosition.clnum;
    al = upper;
    ar = upper;
  
    if ( ci > 0 ) 
      al = c[ci-1]->count;
    if ( ci + 1 < clusterCount ) 
      ar = c[ci+1]->count;
    if ( al != upper || ar != upper )
    {
      if ( ar < al )
      {
        // arrange with next cluster
        nl = ci; 
        nr = ci + 1;
        cr = c[nr];
        al = cl->count;      
        //redundant ar = cr->count;            
      }
      else
      {
        // arrange with prev cluster
        nl = ci - 1; 
        nr = ci;
        cr = cl;
        cl = c[nl];
        //redundant al = cl->count;
        ar = cr->count;      
      }
      if ( al + ar < upper )
      {  
        // merge
        dl = &cl->data;
        dr = &cr->data;
        memmove(&dl[al * itemSize],&dr[0],ar * itemSize);
        cl->count = al + ar;
        // remove empty cluster
        clusterCount--;      
        memmove(&c[nr],&c[nr+1],(clusterCount - nr) * sizeof(pCLUSTER));
        free(cr);      
      }
      else
      {
        // balance
        bl = (al + ar) / 2;
        br = al + ar - bl;
        if ( al < bl ) 
        {
          // move some right to left
          dl = &cl->data;
          dr = &cr->data;
          memmove(&dl[al * itemSize],&dr[0],(bl - al) * itemSize);
          memmove(&dr[0],&dr[(bl-al) * itemSize],br * itemSize);
        }
        else
        {
          // move some left to right
          dl = &cl->data;
          dr = &cr->data;
          memmove(&dr[(br-ar) * itemSize],&dr[0],ar * itemSize);
          memmove(&dl[bl * itemSize],&dr[0],(br - ar) * itemSize);
        }
        cl->count = bl;
        cr->count = br;        
      }
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteByIndex - Delete item by index
        The  function removes  an item  at the  passed position (index) from the
        list.

\return term - 

\param  index - 
\param  fFree_NO - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteByIndex"

logical ClusteredList :: DeleteByIndex (int index, logical fFree_NO )
{
  CLPosition   p;
  logical            term = NO;
BEGINSEQ
  if ( GetPositionByIndex(p,index) )                 ERROR
  if ( DeleteAt(p) )                                 ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Enumerate - 


\return term - 

\param  rCLEnumerator - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Enumerate"

logical ClusteredList :: Enumerate (CLEnumerator &rCLEnumerator )
{
  CLPosition         pos;
  int                index = 0;
  logical            term  = NO;
BEGINSEQ
  if ( GetHeadPosition(pos) )                        LEAVESEQ

  do
  {
    if ( rCLEnumerator.Enum(GetAt(pos),index++) ) 
                                                     LEAVESEQ
  } while ( GetNextPosition(pos) );
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Free - 


\return term - 

\param  pObj - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Free"

logical ClusteredList :: Free (void *pObj )
{

  return Delete(pObj,YES);

}

/******************************************************************************/
/**
\brief  FreeAll - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeAll"

logical ClusteredList :: FreeAll ( )
{

  return DeleteAll(YES);

}

/******************************************************************************/
/**
\brief  FreeAt - 


\return term - 

\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeAt"

logical ClusteredList :: FreeAt (CLPosition &rCLPosition )
{

  return DeleteAt(rCLPosition,YES);

}

/******************************************************************************/
/**
\brief  FreeByIndex - 


\return term - 

\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeByIndex"

logical ClusteredList :: FreeByIndex (int index )
{

  return DeleteByIndex(index,YES);

}

/******************************************************************************/
/**
\brief  GetAt - 


\return res - 

\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAt"

void *ClusteredList :: GetAt (CLPosition &rCLPosition )
{
  char       *l;
  void       *res = NULL;
BEGINSEQ
  if ( !rCLPosition.validread )                ERROR

  pCLUSTER  cl = (pCLUSTER)rCLPosition.cluster;

  l   = &cl->data;
  res = &l[rCLPosition.clindex * itemSize];
RECOVER
  res = NULL;
ENDSEQ
  return(res);
}

/******************************************************************************/
/**
\brief  GetByIndex - 


\return res - 

\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetByIndex"

void *ClusteredList :: GetByIndex (int index )
{
  CLPosition   p;
  void              *res = NULL;
BEGINSEQ
  if ( GetPositionByIndex(p,index) )                 ERROR

  res = GetAt(p);
RECOVER
  res = NULL;
ENDSEQ
  return res;
}

/******************************************************************************/
/**
\brief  GetCount - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

size_t ClusteredList :: GetCount ( )
{

  return count;

}

/******************************************************************************/
/**
\brief  GetHeadPosition - 


\return term - 

\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHeadPosition"

logical ClusteredList :: GetHeadPosition (CLPosition &rCLPosition )
{

  rCLPosition.clnum      = 0;
  rCLPosition.clindex    = 0;
  rCLPosition.cluster    = ((ppCLUSTER) clusters)[0];
  rCLPosition.validread  = count > 0;
  rCLPosition.validwrite = YES;

  return !rCLPosition.validread;
}

/******************************************************************************/
/**
\brief  GetIndexByPosition - 


\return res - 

\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndexByPosition"

size_t ClusteredList :: GetIndexByPosition (CLPosition &rCLPosition )
{
  size_t    res;
  size_t    i;
  res         = rCLPosition.clindex;
  ppCLUSTER c = (ppCLUSTER) clusters;

  for ( i = 0; i < rCLPosition.clnum - 1; i++  )
    res += c[i]->count;

  return res;
}

/******************************************************************************/
/**
\brief  GetNext - 


\return res - 

\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNext"

void *ClusteredList :: GetNext (CLPosition &rCLPosition )
{
  void    *res = NULL;
BEGINSEQ
  if ( !rCLPosition.validread )                ERROR

  res = GetAt(rCLPosition);
  GetNextPosition(rCLPosition);
RECOVER
res= NULL;
ENDSEQ
  return(res);
}

/******************************************************************************/
/**
\brief  GetNextPosition - 


\return term - 

\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNextPosition"

logical ClusteredList :: GetNextPosition (CLPosition &rCLPosition )
{

  rCLPosition.clindex++;

  if ( rCLPosition.clindex >= ((pCLUSTER) rCLPosition.cluster)->count )
  {
    rCLPosition.clnum++;
    if ( rCLPosition.clnum >= clusterCount )
      rCLPosition.clnum--;
    else
    {
      rCLPosition.cluster = ((ppCLUSTER) clusters)[rCLPosition.clnum];
      rCLPosition.clindex = 0;
    }
  }
  rCLPosition.validread  = rCLPosition.clindex < ((pCLUSTER) rCLPosition.cluster)->count;
  rCLPosition.validwrite = rCLPosition.clindex <= ((pCLUSTER) rCLPosition.cluster)->count;

  return !rCLPosition.validread;
}

/******************************************************************************/
/**
\brief  GetPositionByIndex - 


\return term - 

\param  rCLPosition - 
\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPositionByIndex"

logical ClusteredList :: GetPositionByIndex (CLPosition &rCLPosition, int index )
{
  size_t    clnum = 0;

  ppCLUSTER c  = (ppCLUSTER) clusters;
  pCLUSTER  cl = NULL;

  for(;;)
  {
    cl = c[clnum];
    
    if ( index < cl->count ) 
      break;
  
    if ( clnum + 1 >= clusterCount ) 
      break;
  
    index -= cl->count;
    clnum++;
  }

  rCLPosition.cluster    = cl;
  rCLPosition.clnum      = clnum;
  rCLPosition.clindex    = index;
  rCLPosition.validread  = index < cl->count;
  rCLPosition.validwrite = index <= cl->count;

  return !rCLPosition.validread;
}

/******************************************************************************/
/**
\brief  GetPositionByItem - Get index by item
        The  function searches the item in teh  list and returns the position of
        the  first item  in the  list, which  is identical with the passed item.
        Items are compared according to the item size defined for the list.

\return term - 

\param  rCLPosition - 
\param  pitem - Pointer to the item
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPositionByItem"

logical ClusteredList :: GetPositionByItem (CLPosition &rCLPosition, void *pitem )
{
  size_t          i;
  size_t          j;
  char           *it;
  logical         term = NO;
BEGINSEQ
  ppCLUSTER cls = (ppCLUSTER) clusters;

  for( i = 0; i < clusterCount; i++ );
  {
    pCLUSTER cl = *(cls++);
    it          = &cl->data;
    for ( j = 0; j < cl->count; j++ )
    {
      if( memcmp(it,pitem,itemSize) )
      {
        rCLPosition.cluster    = cl;
        rCLPosition.clnum      = i;
        rCLPosition.clindex    = j;
        rCLPosition.validread  = YES;
        rCLPosition.validwrite = YES;
        LEAVESEQ
      }
      it += itemSize;
    }
  }
  
  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetPrev - 


\return res - 

\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrev"

void *ClusteredList :: GetPrev (CLPosition &rCLPosition )
{
  void    *res = NULL;
BEGINSEQ
  if ( !rCLPosition.validread )                ERROR

  res = GetAt(rCLPosition);
  GetPrevPosition(rCLPosition);
RECOVER
  res = NULL;
ENDSEQ
  return(res);
}

/******************************************************************************/
/**
\brief  GetPrevPosition - 


\return term - 

\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrevPosition"

logical ClusteredList :: GetPrevPosition (CLPosition &rCLPosition )
{

  rCLPosition.validread  = YES;
  rCLPosition.validwrite = YES;

  if ( rCLPosition.clindex-- == 0 )
  {
    if ( rCLPosition.clnum-- == 0 )
    {
      rCLPosition.clnum      = 0;
      rCLPosition.clindex    = 0;
      rCLPosition.validread  = NO;
      rCLPosition.validwrite = NO;
    }
    else
    {
      rCLPosition.cluster = ((ppCLUSTER)clusters)[rCLPosition.clnum];
      rCLPosition.clindex = ((pCLUSTER)rCLPosition.cluster)->count;
    }
  }
  return !rCLPosition.validread;
}

/******************************************************************************/
/**
\brief  GetTailPosition - 


\return term - 

\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTailPosition"

logical ClusteredList :: GetTailPosition (CLPosition &rCLPosition )
{

  pCLUSTER c = ((ppCLUSTER)clusters)[clusterCount-1];

  rCLPosition.clnum      = clusterCount - 1;
  rCLPosition.clindex    = c->count == 0 ? 0 : c->count - 1;
  rCLPosition.cluster    = c;
  rCLPosition.validread  = count > 0;
  rCLPosition.validwrite = YES;

  return !rCLPosition.validread;
}

/******************************************************************************/
/**
\brief  InsertAt - 


\return term - 

\param  pitem - Pointer to the item
\param  rCLPosition - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertAt"

logical ClusteredList :: InsertAt (void *pitem, CLPosition &rCLPosition )
{
  char        *l;
  char        *l0;
  char        *r;
  size_t       ci;
  size_t       nl;
  size_t       nr;
  logical      term = NO;
BEGINSEQ
  if ( !rCLPosition.validwrite )               ERROR

  pCLUSTER cl = (pCLUSTER)rCLPosition.cluster;

  l  = &cl->data;
  l0 = &l[rCLPosition.clindex*itemSize];

  memmove(l0 + itemSize, 
          l0,
          (cl->count - rCLPosition.clindex) * itemSize);

  memmove(l0,pitem,itemSize);

  OnInsertItem(l0);
  count++;
  cl->count++;

  if ( cl->count == upper )
  {
    // split  
    ppCLUSTER c = (ppCLUSTER)clusters;
    ci          = rCLPosition.clnum;
    nl          = cl->count;
    nr          = nl / 2;
    nl -= nr;
    pCLUSTER cr = (pCLUSTER) MakeCluster();
    l           = (char*)&cl->data;
    r           = (char*)&cr->data;  
    memmove(&r[0],&l[nl * itemSize],nr * itemSize);
    cl->count   = nl;
    cr->count   = nr;
    clusters    = c = (ppCLUSTER)realloc(c,sizeof(void *) * (clusterCount + 1));
    ci++;
    memmove(&c[ci+1],&c[ci],(clusterCount - ci) * sizeof(void *));
    c[ci]= cr;
    clusterCount++;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  MakeCluster - 


\return res - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MakeCluster"

void *ClusteredList :: MakeCluster ( )
{

  pCLUSTER  c = (pCLUSTER)malloc(sizeof(CLUSTER) + upper * itemSize);
  c->count    = 0;


  return c;
}

/******************************************************************************/
/**
\brief  OnDeleteItem - 



\param  pitem - Pointer to the item
\param  fFree - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnDeleteItem"

void ClusteredList :: OnDeleteItem (void *pitem, logical fFree )
{



}

/******************************************************************************/
/**
\brief  OnInsertItem - 



\param  pitem - Pointer to the item
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnInsertItem"

void ClusteredList :: OnInsertItem (void *pitem )
{



}

/******************************************************************************/
/**
\brief  ~ClusteredList - Destructor
        The  destructor  removes  all  entries  from  the  list  and releses the
        clusters.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ClusteredList"

     ClusteredList :: ~ClusteredList ( )
{

  DeleteAll();

}


