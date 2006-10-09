/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    BTEntry

\brief    Binary tree entry
          An  entry in a binary  tree refers to a  tree instance and its related
          entries.

\date     $Date: 2006/06/11 16:21:13,50 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BTEntry"

#include  <pdefault.h>
#include  <sBTEntry.hpp>
#include  <sBinTree.hpp>
#include  <sBTEntry.hpp>


/******************************************************************************/
/**
\brief  AddEntry - 


\return term - Success

\param  bt_entry - Pointer to binary tree entry
\param  bin_tree - Pointer to a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEntry"

logical BTEntry :: AddEntry (BTEntry *bt_entry, BinTree *bin_tree )
{
  int8                    cmpval;
  logical                 term = NO;
BEGINSEQ
  switch ( cmpval = bin_tree->CompareInst(bt_entry->instance,instance) )
  {
    case -1 : if ( left )
                term = left->AddEntry(bt_entry,bin_tree);
              else
              {
                left = bt_entry;
                bt_entry->parent = this;
              }
              break;
    case  0 :                                        ERROR
    case  1 : if ( right )
                term = right->AddEntry(bt_entry,bin_tree);
              else
              {
                right = bt_entry;
                bt_entry->parent = this;
              }
              break;
    default : ;
  }

  if ( term )                                        ERROR
  
  UpdateCountsRecursive();
  bin_tree->SetTop(GetTop());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  BTEntry - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BTEntry"

     BTEntry :: BTEntry ( )
{

  Initialize();

}

/******************************************************************************/
/**
\brief  Count - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Count"

int32 BTEntry :: Count ( )
{

  return( this ? count : 0 );

}

/******************************************************************************/
/**
\brief  GetEntry - 


\return bt_entry - Pointer to binary tree entry
-------------------------------------------------------------------------------
\brief  i00 - 


\param  lindx0 - Index position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

BTEntry *BTEntry :: GetEntry (int32 lindx0 )
{
  int32                left_count = left ? left->get_count() : 0;
  BTEntry             *bt_entry = NULL;
BEGINSEQ
  if ( left_count > lindx0 )
    bt_entry = left->GetEntry(lindx0);
  else if ( left_count == lindx0 )
    bt_entry = this;
  else if ( right )
    bt_entry = right->GetEntry(lindx0 - (left_count+1) );
  else                                               ERROR
RECOVER
  bt_entry = NULL;
ENDSEQ
  return(bt_entry);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  key_value - 
\param  bin_tree - Pointer to a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

BTEntry *BTEntry :: GetEntry (char *key_value, BinTree *bin_tree )
{
  int8                    cmpval;
  BTEntry                *bt_entry = NULL;
  switch ( cmpval = bin_tree->CompareKey(key_value,instance) )
  {
    case -1 : if ( left )
                bt_entry = left->GetEntry(key_value,bin_tree);
              break;
    case  0 : bt_entry = this;
              break;
    case  1 : if ( right )
                bt_entry = right->GetEntry(key_value,bin_tree);
              break;
    default : ;
  }
  
  if ( !bt_entry )
  {
    bin_tree->stsserr();
    bt_entry = cmpval < 0 ? this : GetNext();
  }
    
      

  return(bt_entry);
}

/******************************************************************************/
/**
\brief  i02 - 


\param  bt_instance - Instance returned from a binary tree
\param  bin_tree - Pointer to a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

BTEntry *BTEntry :: GetEntry (void *bt_instance, BinTree *bin_tree )
{
  int8                    cmpval;
  BTEntry                *bt_entry = NULL;
  switch ( cmpval = bin_tree->CompareInst(bt_instance,instance) )
  {
    case -1 : if ( left )
                bt_entry = left->GetEntry(bt_instance,bin_tree);
              break;
    case  0 : bt_entry = this;
              break;
    case  1 : if ( right )
                bt_entry = right->GetEntry(bt_instance,bin_tree);
              break;
    default : ;
  }
  
  if ( !bt_entry )
  {
    bin_tree->stsserr();
    bt_entry = cmpval < 0 ? this : GetNext();
  }
    
      

  return(bt_entry);
}

/******************************************************************************/
/**
\brief  GetLeftParent - 


\return bt_entry - Pointer to binary tree entry

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLeftParent"

BTEntry *BTEntry :: GetLeftParent ( )
{
  BTEntry                *bt_entry = NULL;
BEGINSEQ
  if ( !parent )                                     ERROR
    
  if ( parent->right == this )
    bt_entry = parent;
  else
    bt_entry = parent->GetLeftParent();

RECOVER
  bt_entry = NULL;
ENDSEQ
  return(bt_entry);
}

/******************************************************************************/
/**
\brief  GetMajor - 


\return bt_entry - Pointer to binary tree entry

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMajor"

BTEntry *BTEntry :: GetMajor ( )
{
  BTEntry                *bt_entry = this;
  if ( right )
    bt_entry = right->GetMajor();

  return(bt_entry);
}

/******************************************************************************/
/**
\brief  GetMinor - 


\return bt_entry - Pointer to binary tree entry

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMinor"

BTEntry *BTEntry :: GetMinor ( )
{
  BTEntry                *bt_entry = this;
  if ( left )
    bt_entry = left->GetMinor();

  return(bt_entry);
}

/******************************************************************************/
/**
\brief  GetNext - Get next entry


\return bt_entry - Pointer to binary tree entry

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNext"

BTEntry *BTEntry :: GetNext ( )
{
  BTEntry                *bt_entry = NULL;
  if ( right )
    bt_entry = right->GetMinor();
  else
    bt_entry = GetRightParent();
  return(bt_entry);
}

/******************************************************************************/
/**
\brief  GetPosition - 


\return lindx0 - Index position

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosition"

int32 BTEntry :: GetPosition ( )
{
  BTEntry                 *bt_entry;
  int32                    lindx0 = AUTO;
  if ( left )
    lindx0 += left->Count();
  
  if ( bt_entry = GetLeftParent() )
    lindx0 += bt_entry->GetPosition() + 1;
  return(lindx0);
}

/******************************************************************************/
/**
\brief  GetPrevious - Get previous entry


\return bt_entry - Pointer to binary tree entry

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrevious"

BTEntry *BTEntry :: GetPrevious ( )
{
  BTEntry                *bt_entry = NULL;
  if ( left )
    bt_entry = left->GetMajor();
  else
    bt_entry = GetLeftParent();
  return(bt_entry);
}

/******************************************************************************/
/**
\brief  GetRightParent - 


\return bt_entry - Pointer to binary tree entry

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRightParent"

BTEntry *BTEntry :: GetRightParent ( )
{
  BTEntry                *bt_entry = NULL;
BEGINSEQ
  if ( !parent )                                     ERROR
    
  if ( parent->left == this )
    bt_entry = parent;
  else
    bt_entry = parent->GetRightParent();

RECOVER
  bt_entry = NULL;
ENDSEQ
  return(bt_entry);
}

/******************************************************************************/
/**
\brief  GetTop - 


\return bt_entry - Pointer to binary tree entry

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTop"

BTEntry *BTEntry :: GetTop ( )
{
  BTEntry                *top = this;
  while ( top->parent )
    top = top->parent;
  return(top);
}

/******************************************************************************/
/**
\brief  HasLeftParent - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasLeftParent"

logical BTEntry :: HasLeftParent ( )
{

  return( parent && parent->right == this );

}

/******************************************************************************/
/**
\brief  HasRightParent - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasRightParent"

logical BTEntry :: HasRightParent ( )
{

  return( parent && parent->left == this );

}

/******************************************************************************/
/**
\brief  Initialize - Initialize tree entry



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void BTEntry :: Initialize ( )
{

  instance       = NULL;
  parent         = NULL;
  left           = NULL;
  right          = NULL;
  count          = 1;
  max_level      = 1;
  instance_owner = NO;

}

/******************************************************************************/
/**
\brief  Level - 


\return level - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Level"

int32 BTEntry :: Level ( )
{

  return( this ? max_level : 0 );

}

/******************************************************************************/
/**
\brief  Print - 


\return term - Success

\param  fileptr - 
\param  level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Print"

logical BTEntry :: Print (FILE *fileptr, int32 level )
{
  char                    string[1024];
  char                   *pos;
  logical                 term = NO;
  if ( left )
    left->Print(fileptr,level+1);
  
  memset(string,' ',sizeof(string));
  *string = '\n';
  pos = string+level*4+1;
  //ltoa(*(int32 *)instance,pos,10);
  sprintf((char*)*(int32 *)instance,"%i",pos);
  fprintf(fileptr,string);

  if ( right )
    right->Print(fileptr,level+1);

  return(term);
}

/******************************************************************************/
/**
\brief  Remove - 


\return term - Success

\param  bin_tree - Pointer to a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

logical BTEntry :: Remove (BinTree *bin_tree )
{
  BTEntry                *free_entry = NULL;
  logical                 term = NO;
  if ( parent )
  {
    if ( HasRightParent() ) 
    {
      if ( parent->left = left )
      {
        left->parent = parent;
        left = NULL;
      }
      free_entry = right;
    }
    else
    {
      if ( parent->right = right )
      {
        right->parent = parent;
        right = NULL;
      }
      free_entry = left;
    }
    if ( free_entry )  
      parent->AddEntry(free_entry,bin_tree);
    else              // otherwise, AddEntry will update counts
    {
      parent->UpdateCountsRecursive();
      bin_tree->SetTop(GetTop());
    }
  }
  else
  {
    if ( left )
    {
      bin_tree->SetTop(left);
      left->parent = NULL;
      if ( right )
        left->AddEntry(right,bin_tree);
    }
    else if ( right )
    {
      bin_tree->SetTop(right);
      right->parent = NULL;
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Reparent - 



\param  bt_entry - Pointer to binary tree entry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reparent"

void BTEntry :: Reparent (BTEntry *bt_entry )
{

  if ( parent )
    if ( HasRightParent() )
      parent->left = bt_entry;
    else
      parent->right = bt_entry;
  
  bt_entry->parent = parent;
  parent = bt_entry;


}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Success

\param  bin_tree - Pointer to a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical BTEntry :: Reset (BinTree *bin_tree )
{
  logical                 term = NO;
  if ( right )
    right->Reset(bin_tree);
  right = NULL;

  if ( left )
    left->Reset(bin_tree);
  left = NULL;

  parent = NULL;
  bin_tree->RemoveEntry(this);
  return(term);
}

/******************************************************************************/
/**
\brief  RotateLeft - 


\return term - Success

\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RotateLeft"

logical BTEntry :: RotateLeft (logical recursive )
{
  BTEntry                *top;
  logical                 term = NO;
  if ( recursive && left->left->Level() < left->right->Level() )
    left->RotateRight(NO);

  Reparent(top = left);
  
  if ( left = top->right )
    left->parent = this;
  top->right = this;

  UpdateCounts();
  top->UpdateCounts();
  return(term);
}

/******************************************************************************/
/**
\brief  RotateRight - 


\return term - Success

\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RotateRight"

logical BTEntry :: RotateRight (logical recursive )
{
  BTEntry                *top;
  logical                 term = NO;
  if ( recursive && right->right->Level() < right->left->Level() )
    right->RotateLeft(NO);
   
  Reparent(top = right);
  
  if ( right = top->left )
    right->parent = this;
  top->left = this;

  UpdateCounts();
  top->UpdateCounts();
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateCounts - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateCounts"

logical BTEntry :: UpdateCounts ( )
{
  logical                 term = NO;
  count = 1;
  
  max_level = left->Level()+1;
  count += left->Count();

  if ( max_level <= right->Level() )
    max_level = right->Level()+1;
  count += right->Count();

  return(term);
}

/******************************************************************************/
/**
\brief  UpdateCountsRecursive - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateCountsRecursive"

logical BTEntry :: UpdateCountsRecursive ( )
{
  logical                 term = NO;
  UpdateCounts();
  
  if ( right->Level() > left->Level()+1 )
    RotateRight(YES);
  else if ( left->Level() > right->Level()+1 )
    RotateLeft(YES);
  
  if ( parent )
    parent->UpdateCountsRecursive();

  return(term);
}

/******************************************************************************/
/**
\brief  set_instance - 



\param  bt_instance - Instance returned from a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_instance"

void BTEntry :: set_instance (void *bt_instance )
{

  instance = bt_instance;

}


