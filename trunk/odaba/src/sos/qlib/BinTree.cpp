/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    BinTree

\brief    Binary tree
          A  binary  tree  provides  fast  maintenance  features  for  ordered 
          collections.  The  order  is  defined  by  an elementary value and its
          position  in the instance or by complex keys consisting of one or more
          key attributes.

\date     $Date: 2006/07/09 10:25:18,59 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BinTree"

#include  <pdefault.h>
#include  <sBTEntry.hpp>
#include  <skcb.hpp>
#include  <sBinTree.hpp>


/******************************************************************************/
/**
\brief  AddEntry - 



\return term - Success

\param  bt_entry - Pointer to binary tree entry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEntry"

logical BinTree :: AddEntry (BTEntry *bt_entry )
{
  logical                 term = NO;
  if ( top_entry )
    term = top_entry->AddEntry(bt_entry,this);
  else
    top_entry = bt_entry;
  return(term);
}

/******************************************************************************/
/**
\brief  BinTree - Konstructor



-------------------------------------------------------------------------------
\brief  i0 - 



\param  keydef - 
\param  entry_size - 
\param  block_size - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BinTree"

     BinTree :: BinTree (kcb *keydef, int32 entry_size, int32 block_size )
                     : sts (),
  key_definition(keydef),
  entry_length(entry_size),
  key_length(UNDEF),
  key_position(UNDEF),
  key_type('S'),
  top_entry(NULL),
  entry_pool(sizeof(BTEntry),block_size),
  instance_pool(entry_size,block_size),
  resource_lock(NO),
  iterators(),
  optimizing(NO)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  entry_size - 
\param  key_pos - 
\param  key_len - 
\param  key_typ - 
\param  block_size - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BinTree"

     BinTree :: BinTree (int32 entry_size, int32 key_pos, int32 key_len, char key_typ, int32 block_size )
                     : sts (),
  key_definition(NULL),
  entry_length(entry_size),
  key_length(key_len),
  key_position(key_pos),
  key_type(key_typ),
  top_entry(NULL),
  entry_pool(sizeof(BTEntry),block_size),
  instance_pool(entry_size,block_size),
  resource_lock(NO),
  iterators(),
  optimizing(NO)
{



}

/******************************************************************************/
/**
\brief  Clear - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void BinTree :: Clear ( )
{

  if ( top_entry )
    top_entry->Reset(this);
  top_entry = NULL;

}

/******************************************************************************/
/**
\brief  Compare - 



\return cmpval - Comparision result

\param  entry1 - 
\param  entry2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compare"

int8 BinTree :: Compare (const void *entry1, const void *entry2 )
{
  char	    *buffer1 = (char *)entry1;
  char	    *buffer2 = (char *)entry2;
  int8       cmpval  = UNDEF;
  char      *cint1;
  char      *cint2;
  int16     *sint1;
  int16     *sint2;
  int32     *lint1;
  int32     *lint2;
  int64     *llint1;
  int64     *llint2;
  char      *cptr1;
  char      *cptr2;
  float     *fint1;
  float     *fint2;
  double    *dint1;
  double    *dint2;
BEGINSEQ
  if ( !key_length )                               SOSERR(5)

  switch ( key_type )
  {
    case 'C' : cmpval = memcmp(buffer1+key_position,
                               buffer2+key_position,
                               key_length      );
               break;
    case 'V' : cmpval = strcmp(buffer1+key_position,
                               buffer2+key_position);
               break;
    case 'I' : switch ( key_length )
               {
                 case 1  : cint1  = buffer1+key_position;
                           cint2  = buffer2+key_position;
                           cmpval = ( *cint1 > *cint2 ) - ( *cint1 < *cint2 );
                           break;
                 case 2  : sint1  = (int16 *)(buffer1+key_position);
                           sint2  = (int16 *)(buffer2+key_position);
                           cmpval = ( *sint1 > *sint2 ) - ( *sint1 < *sint2 );
                           break;
                 case 4  : lint1  = (int32 *)(buffer1+key_position);
                           lint2  = (int32 *)(buffer2+key_position);
                           cmpval = ( *lint1 > *lint2 ) - ( *lint1 < *lint2 );
                           break;
                 case 8  : llint1 = (int64 *)(buffer1+key_position);
                           llint2 = (int64 *)(buffer2+key_position);
                           cmpval = ( *llint1 > *llint2 ) - ( *llint1 < *llint2 );
                           break;
                 default :                                   ERROR
	       }
               break;
    case 'c' : cptr1   = *(char **)(buffer1+key_position);
               cptr2   = *(char **)(buffer2+key_position);
               cmpval = memcmp(cptr1,cptr2,key_length);
               break;
    case 'v' : cptr1   = *(char **)(buffer1+key_position);
               cptr2   = *(char **)(buffer2+key_position);
               cmpval = strcmp(cptr1,cptr2);
               break;
    case 'S' : 
    case 'K' :                                       SOSERR(99)
               break; 
    case 'F' : switch ( key_length )
               {
                 case 4  : fint1  = (float *)(buffer1+key_position);
                           fint2  = (float *)(buffer2+key_position);
                           cmpval = ( *fint1 > *fint2 ) - ( *fint1 < *fint2 );
                 case 8  : dint1  = (double *)(buffer1+key_position);
                           dint2  = (double *)(buffer2+key_position);
                           cmpval = ( *dint1 > *dint2 ) - ( *dint1 < *dint2 );
		 default :                                 ERROR
	       }
	       break;
    default  :                                             ERROR
  }

RECOVER
  cmpval = ERIC;
ENDSEQ
  if ( cmpval )
    cmpval = cmpval < 0 ? -1 : 1;
  return(cmpval);
}

/******************************************************************************/
/**
\brief  CompareInst - 



\return cmpval - Comparision result

\param  bt_instance1 - 
\param  bt_instance2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareInst"

int8 BinTree :: CompareInst (void *bt_instance1, void *bt_instance2 )
{

  return ( key_definition ? key_definition->kcbkcp((char *)bt_instance1,(char *)bt_instance2,CMP_II)
                          : Compare(bt_instance1,bt_instance2) );

}

/******************************************************************************/
/**
\brief  CompareKey - 



\return cmpval - Comparision result

\param  key_value - 
\param  bt_instance - Instance returned from a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareKey"

int8 BinTree :: CompareKey (char *key_value, void *bt_instance )
{

  return ( key_definition ? key_definition->kcbkcp(key_value,(char *)bt_instance,CMP_KI)
                          : Compare(key_value-key_position,bt_instance) );


}

/******************************************************************************/
/**
\brief  CreateEntry - 



\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - 



\param  bt_instance - Instance returned from a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEntry"

logical BinTree :: CreateEntry (void *bt_instance )
{
  BTEntry                *bt_entry = NULL;
  logical                 term = NO;
  bt_entry = (BTEntry *)entry_pool.ReserveEntry(NO);
  bt_entry->Initialize();
  
  if ( !bt_instance )
  {
    bt_instance = instance_pool.ReserveEntry(NO);
    memset(bt_instance,0,entry_length);
    bt_entry->set_instance_owner(YES);
    bt_entry->set_instance(bt_instance);
  }
  bt_entry->set_instance(bt_instance);

  AddEntry(bt_entry);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEntry"

logical BinTree :: CreateEntry (char *key_value )
{
  void                   *bt_instance = NULL;
  BTEntry                *bt_entry = NULL;
  logical                 term = NO;
  bt_entry = (BTEntry *)entry_pool.ReserveEntry(NO);
  bt_entry->Initialize();
  
  bt_instance = instance_pool.ReserveEntry(NO);
  bt_entry->set_instance_owner(YES);
  SetKey(bt_instance,key_value);
  bt_entry->set_instance(bt_instance);

  AddEntry(bt_entry);
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteEntry - 



\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - 



\param  bt_instance - Instance returned from a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteEntry"

logical BinTree :: DeleteEntry (void *bt_instance )
{
  BTEntry                *bt_entry = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !(bt_entry = GetEntry(bt_instance)) || stscerr() ) ERROR
  
  RemoveEntry(bt_entry);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteEntry"

logical BinTree :: DeleteEntry (char *key_value )
{
  BTEntry                *bt_entry = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !(bt_entry = GetEntry(key_value)) || stscerr() )  ERROR
  
  RemoveEntry(bt_entry);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 BinTree :: GetCount ( )
{

  return ( top_entry ? top_entry->get_count() : 0 );

}

/******************************************************************************/
/**
\brief  GetEntry - Get entry

        The  function  locates  an  entry  in  the  binary  tree and returns the
        instance  when  being  located  successfully. When not being successful,
        the function returns NULL.

\return bt_entry - Pointer to binary tree entry
-------------------------------------------------------------------------------
\brief  i00 - Locate entry by index

        The  implementation tries to locate an  entry in a binary tree according
        to the position passed to the function.

\param  lindx0 - Index position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

BTEntry *BinTree :: GetEntry (int32 lindx0 )
{
  BTEntry                *bt_entry = NULL;
BEGINSEQ
  if ( !top_entry || top_entry->get_count() <= lindx0 ) ERROR
  
  stsrerr();
  bt_entry = top_entry->GetEntry(lindx0);
RECOVER
  bt_entry = NULL;
ENDSEQ
  return(bt_entry);
}

/******************************************************************************/
/**
\brief  i01 - Locate entry by key value

        The  implementation tries to locate an  entry in a binary tree according
        to  the key  value passed  to the  function. When  no entry with the key
        value  passed could  be found  in the  binary tree, the function returns
        NULL.

\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

BTEntry *BinTree :: GetEntry (char *key_value )
{
  BTEntry                *bt_entry = NULL;
BEGINSEQ
  if ( !top_entry )                                     ERROR
  
  stsrerr();
  bt_entry = top_entry->GetEntry(key_value,this);
RECOVER
  bt_entry = NULL;
ENDSEQ
  return(bt_entry);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  bt_instance - Instance returned from a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

BTEntry *BinTree :: GetEntry (void *bt_instance )
{
  BTEntry                *bt_entry = NULL;
BEGINSEQ
  if ( !top_entry )                                     ERROR
  
  stsrerr();
  bt_entry = top_entry->GetEntry(bt_instance,this);
RECOVER
  bt_entry = NULL;
ENDSEQ
  return(bt_entry);
}

/******************************************************************************/
/**
\brief  GetFirstEntry - 



\return bt_entry - Pointer to binary tree entry

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFirstEntry"

BTEntry *BinTree :: GetFirstEntry ( )
{
  BTEntry                *bt_entry = top_entry;
  while ( bt_entry )
    if ( bt_entry->get_left() )
      bt_entry = bt_entry->get_left();
    else
      break;
  return(bt_entry);
}

/******************************************************************************/
/**
\brief  GetKey - 



\return keyptr - 

\param  bt_instance - Instance returned from a binary tree
\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *BinTree :: GetKey (void *bt_instance, char *key_value )
{
  char                   *inst = (char *)bt_instance;
  return( this && bt_instance 
          ? key_definition 
            ? key_definition->GetKey(inst,key_value)
            : key_value
              ? (char *)memcpy(key_value,inst+key_position,key_length)
              : inst+key_position 
          : NULL);


}

/******************************************************************************/
/**
\brief  GetLastEntry - 



\return bt_entry - Pointer to binary tree entry

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastEntry"

BTEntry *BinTree :: GetLastEntry ( )
{
  BTEntry                *bt_entry = top_entry;
  while ( bt_entry )
    if ( bt_entry->get_right() )
      bt_entry = bt_entry->get_right();
    else
      break;
  return(bt_entry);
}

/******************************************************************************/
/**
\brief  Lock - 



\return term - Success

\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical BinTree :: Lock (logical wait )
{

  return(resource_lock.ILock(wait));

}

/******************************************************************************/
/**
\brief  Print - 



\return term - Success

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Print"

logical BinTree :: Print (char *cpath )
{
  FILE                   *fileptr = NULL;
  logical                 term = NO;
BEGINSEQ
  if ((fileptr = fopen(cpath,"w")) == 0)            ERROR

  top_entry->Print(fileptr,0);

  fclose(fileptr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RegisterIterator - 




\param  bt_iterator - Iterator for a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterIterator"

void BinTree :: RegisterIterator (BTIterator &bt_iterator )
{

  iterators.AddTail(&bt_iterator);

}

/******************************************************************************/
/**
\brief  RemoveEntry - 



\return term - Success

\param  bt_entry - Pointer to binary tree entry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveEntry"

logical BinTree :: RemoveEntry (BTEntry *bt_entry )
{
  int32                   count = top_entry->Count();
  logical                 term = NO;
BEGINSEQ
  if ( !count )                                      ERROR
  
  if ( bt_entry->get_instance_owner() )
    instance_pool.ReleaseEntry(bt_entry->get_instance());
  
  bt_entry->Remove(this);
  bt_entry->Initialize();
  entry_pool.ReleaseEntry(bt_entry);

  if ( count == 1 )
    top_entry = NULL;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetKey - 



\return term - Success

\param  bt_instance - Instance returned from a binary tree
\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

logical BinTree :: SetKey (void *bt_instance, char *key_value )
{
  char                   *inst = (char *)bt_instance;
  logical                 term = NO;
  if ( key_definition )
    key_definition->SetKey(inst,key_value);
  else
    memcpy(inst+key_position,key_value,key_length);

  return(term);
}

/******************************************************************************/
/**
\brief  SetTop - 




\param  bt_entry - Pointer to binary tree entry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTop"

void BinTree :: SetTop (BTEntry *bt_entry )
{

  top_entry = bt_entry;


}

/******************************************************************************/
/**
\brief  Unlock - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical BinTree :: Unlock ( )
{

  return(resource_lock.IUnlock());

}

/******************************************************************************/
/**
\brief  UnregisterIterator - 




\param  bt_iterator - Iterator for a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterIterator"

void BinTree :: UnregisterIterator (BTIterator &bt_iterator )
{

  bt_iterator.Reset();
  
  if ( iterators.FindTail(&bt_iterator) )
    iterators.RemoveAt();

}

/******************************************************************************/
/**
\brief  ~BinTree - Destructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BinTree"

     BinTree :: ~BinTree ( )
{
  BTIterator      *bti;
  while ( bti = iterators.RemoveTail() )
    bti->Reset();

}


