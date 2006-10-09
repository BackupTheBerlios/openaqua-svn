/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CSegment

\brief    


\date     $Date: 2006/03/12 19:21:29,07 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSegment"

#include  <pdefault.h>
#include  <cvp.h>
#include  <sCSegment.hpp>
#include  <sCSegment.hpp>


/******************************************************************************/
/**
\brief  CSegment

\return a
-------------------------------------------------------------------------------
\brief i00


\param  init_size -
\param  prev_seg -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSegment"

                        CSegment :: CSegment (uint16 init_size, CSegment *prev_seg )
                     :   previous(prev_seg),
  next(NULL),
  size(init_size),
  count(init_size),
  seg_nodes((void**)new VoidPtr[size])


{

  memset(seg_nodes,0,size*sizeof(VoidPtr));


}

/******************************************************************************/
/**
\brief i01


\param  seg_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSegment"

                        CSegment :: CSegment (const CSegment &seg_ref )
                     :   previous(seg_ref.previous),
  next(seg_ref.next),
  size(seg_ref.size),
  count(seg_ref.count),
  seg_nodes((void**)new VoidPtr[size])

{

  memcpy(seg_nodes,seg_ref.seg_nodes,size*sizeof(VoidPtr));


}

/******************************************************************************/
/**
\brief i02


\param  init_size -
\param  prev_seg -
\param  next_seg -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSegment"

                        CSegment :: CSegment (uint16 init_size, CSegment *prev_seg, CSegment *next_seg )
                     :   previous(prev_seg),
  next(next_seg),
  size(init_size),
  count(0),
  seg_nodes((void**)new VoidPtr[size])


{



}

/******************************************************************************/
/**
\brief  GetNextSegment

\return seg_ptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNextSegment"

CSegment *CSegment :: GetNextSegment ( )
{

  return(next);

}

/******************************************************************************/
/**
\brief  GetObjectInst

\return element -

\param  index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectInst"

void *CSegment :: GetObjectInst (uint16 index )
{

  return(seg_nodes[index]);

}

/******************************************************************************/
/**
\brief  GetObjectPtr

\return void_ptr

\param  index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectPtr"

void **CSegment :: GetObjectPtr (uint16 index )
{

  return &(seg_nodes[index]);


}

/******************************************************************************/
/**
\brief  GetPrevSegment

\return seg_ptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrevSegment"

CSegment *CSegment :: GetPrevSegment ( )
{

  return(previous);

}

/******************************************************************************/
/**
\brief  Insert


\param  element -
\param  index -
\param  new_size -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

void CSegment :: Insert (void *element, uint16 index, uint16 new_size )
{
  void        **new_nodes;
  if ( count == size )
  {
    size += new_size;
    new_nodes = (void**)new VoidPtr[size];

    if ( count == index )
      memcpy(new_nodes,seg_nodes,count*sizeof(VoidPtr));
    else
    {
      memcpy(new_nodes,seg_nodes,index*sizeof(VoidPtr));
      memcpy(new_nodes+index+1,seg_nodes+index,(count-index)*sizeof(VoidPtr) );
    }

    delete seg_nodes;
    seg_nodes = new_nodes;
  }
  else
    if ( index < count )
      memmove(seg_nodes+index+1,seg_nodes+index,(count-index)*sizeof(VoidPtr) );

  seg_nodes[index] = element;
  count++;

}

/******************************************************************************/
/**
\brief  Remove

\return void_ptr

\param  index -
\param  new_size -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *CSegment :: Remove (uint16 index, uint16 new_size )
{
  void         *old_element = seg_nodes[index];
  void        **new_nodes;

  if ( (count-1) == (size-new_size-(new_size / 4)) )
  {
    size -= new_size;
    new_nodes = (void**)new VoidPtr[size];

    if ( index == (count-1) )
      memcpy( new_nodes, seg_nodes, (count-1)*sizeof(VoidPtr) );
    else
    {
      memcpy(new_nodes,seg_nodes,index*sizeof(VoidPtr));
      memcpy(new_nodes+index,seg_nodes+index+1,(count-index-1)*sizeof(VoidPtr) );
    }

    delete seg_nodes;
    seg_nodes = new_nodes;
  }
  else
    if ( index < (count-1) )
      memmove(seg_nodes+index,seg_nodes+index+1,(count-index-1)*sizeof(VoidPtr));

  count--;

  return(old_element);

}

/******************************************************************************/
/**
\brief  Replace

\return void_ptr

\param  element -
\param  index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Replace"

void *CSegment :: Replace (void *element, uint16 index )
{
  void         *old_element = seg_nodes[index];
  seg_nodes[index] = element;

  return(old_element);
}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void CSegment :: Reset ( )
{

  count = 0;

}

/******************************************************************************/
/**
\brief  SetNextSegment


\param  seg_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNextSegment"

void CSegment :: SetNextSegment (CSegment *seg_ptr )
{

  next = seg_ptr;

}

/******************************************************************************/
/**
\brief  SetPrevSegment


\param  seg_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPrevSegment"

void CSegment :: SetPrevSegment (CSegment *seg_ptr )
{

  previous = seg_ptr;

}

/******************************************************************************/
/**
\brief  SetSize - 



\param  new_size -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSize"

void CSegment :: SetSize (uint16 new_size )
{
  void        **new_nodes;
  if ( new_size != count )
  {
    new_nodes = new VoidPtr[new_size];

    if ( new_size < count )
      memcpy(new_nodes,seg_nodes,new_size*sizeof(VoidPtr));
    else
    {
      memcpy(new_nodes,seg_nodes,count*sizeof(VoidPtr));
      memset(new_nodes+count,0,(new_size-count)*sizeof(VoidPtr));
    }

    size  = new_size;
    count = size;
    delete seg_nodes;
    seg_nodes = new_nodes;
  }


}

/******************************************************************************/
/**
\brief  Split

\return pCSegment

\param  element -
\param  index -
\param  new_size -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Split"

CSegment *CSegment :: Split (void *element, uint16 index, uint16 new_size )
{
  CSegment     *new_segment;
  ushort        new_count;
  new_count = index > count/2 ? count-index : index;

  if ( new_count < new_size )
    new_count = new_size;
  else
  {
    if ( new_count % new_size )
      new_count += new_size - (new_count % new_size);
    else
      new_count += new_size;
  }

  if ( index > count/2 )
  {
    new_segment = new CSegment(new_count,this,next);

    if ( next )
      next->previous = new_segment;
    next = new_segment;

    if ( index < count )
    {
      memcpy(new_segment->seg_nodes+1,seg_nodes+index,(count-index)*sizeof(VoidPtr));
      new_segment->count = (count-index+1);
      count = index;
    }
    else
      new_segment->count = 1;

    new_segment->seg_nodes[0] = element;
  }
  else
  {
    new_segment = new CSegment(new_count,previous,this);

    if ( previous )
      previous->next = new_segment;
    previous = new_segment;

    if ( index )
    {
      memcpy(new_segment->seg_nodes,seg_nodes,index*sizeof(VoidPtr));
      count -= index;
      memmove( seg_nodes, seg_nodes+index, count*sizeof(VoidPtr) );
    }

    new_segment->seg_nodes[index] = element;
    new_segment->count = index+1;
  }
  return(new_segment);

}

/******************************************************************************/
/**
\brief  ~CSegment

\return ainline

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSegment"

                        CSegment :: ~CSegment ( )
{

  delete seg_nodes;


}


