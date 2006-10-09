/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    ActivityManagerI

\brief    


\date     $Date: 2006/03/13 21:33:03,79 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ActivityManagerI"

#include  <poadi.h>
#include  <sAH.hpp>
#include  <sActivityManagerPrivate.hpp>
#include  <sActivityVoidFunctor.hpp>
#include  <sActivityManagerI.hpp>


/******************************************************************************/
/**
\brief  ActivityManagerI

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivityManagerI"

                        ActivityManagerI :: ActivityManagerI ( )
                     : running(0),
p(0)
{



}

/******************************************************************************/
/**
\brief  Add

\return term -

\param  cszName_0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

ActivityHandler<void,void> &ActivityManagerI :: Add (const char *cszName_0 )
{

  if ( !p ) 
    p = new ActivityManagerPrivate;

  AH *ah= new AH(cszName_0);
  p->addList.AddTail(ah);

  return *ah;
}

/******************************************************************************/
/**
\brief  Execute

\return term -

\param  pvoidSender
\param  pvoid -
\param  rcDoF
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical ActivityManagerI :: Execute (void *pvoidSender, void *pvoid, const DoF &rcDoF )
{
  AH      *ah;
  logical  cancel = NO;
  logical  dof    = NO;
  logical  cond   = YES;
BEGINSEQ
  if ( running )                                     LEAVESEQ

//  running = YES;   12.5.2005 sonst kann z.B. eine Knopfaktion nicht rekursiv in einem nachgeordneten window ausgefuehrt werden
//                             das geht aber nur solange, wie nur genau eine simple action ausgefuehrt wird
  flushAddList();

  if ( !p ) 
  {
    rcDoF(pvoidSender,pvoid);
    running = NO;                                    ERROR
  }

  DLL(AH) bit(p->beforeList);
  DLL(AH) clst;

  while ( ah = bit.GetNext() )
  {
    if ( ah->beforeF(pvoidSender,pvoid) )
    {
      cancel = YES;
      break;
    }
    else
      clst.InsertBefore(ah);
  }

  if ( cancel )
  {
    DLL(AH) cit(clst);
    while ( ah = cit.GetNext() )
      ah->cancelF(pvoidSender,pvoid);
  }
  else
  {
    DLL(AH) dit(p->doList);
    while ( ah = dit.GetNext() )
    {
      if ( !dof &&
           ( ( ah->doPos > 0 )               ||
             ( ah->doPos == 0 && !ah->doPre )  ) )
      { // interfere DoF as earliest as pos=0 pre=NO
        dof = YES;
        rcDoF (pvoidSender,pvoid);    
      }
      ah->doF(pvoidSender,pvoid);
    }
    if ( !dof ) 
      rcDoF(pvoidSender,pvoid);
  }

  running = NO;
  cond    = cancel;
RECOVER
  cond = NO;
ENDSEQ
  return cond;
}

/******************************************************************************/
/**
\brief  Remove


\param  cszName -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void ActivityManagerI :: Remove (const char *cszName )
{
  AH    *ah;

BEGINSEQ
  if ( !p )                                          LEAVESEQ

  DLL(AH) ait(p->addList);
  while ( ah = ait.GetNext() )
    if ( ah->name && !strcmp(cszName,ah->name) )
      break;

  if ( ah )
  {
    p->addList.Remove( ah );
    LEAVESEQ
  }
  
  DLL(AH) bit(p->beforeList);
  while ( ah= bit.GetNext() )
    if ( ah->name && !strcmp(cszName,ah->name) )
      break;

  if ( ah )
  {
    p->beforeList.Remove(ah);
    p->doList.Remove(ah);
    LEAVESEQ
  }
ENDSEQ

}

/******************************************************************************/
/**
\brief  flushAddList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "flushAddList"

void ActivityManagerI :: flushAddList ( )
{
  AH      *ah;
  logical  fnd;
  if ( p && p->addList.GetCount() )
    while ( ah = p->addList.GetHead() )
    {
      p->addList.Remove(ah);
    
// das brauchen wir vielleicht nicht ... geht jedenfalls nicht in DDL
//    fnd = !p->beforeList.BinarySearch(&ActivityManagerPrivate::compareBefore,
//                                      ah,ah->beforePre ? -1 : 1 );
OADISET(888)
      fnd = p->beforeList.Find(ah);

      if ( fnd && !ah->beforePre ) 
        p->beforeList.GetNext(); 
      p->beforeList.InsertBefore(ah);
    
// das brauchen wir vielleicht nicht ... geht jedenfalls nicht in DDL
//    fnd = !p->doList.BinarySearch(&ActivityManagerPrivate::compareDo,
//                                  ah,ah->doPre ? -1 : 1 );
      fnd = p->doList.Find(ah);
      
      if ( fnd && !ah->doPre ) 
        p->doList.GetNext(); 
      p->doList.InsertBefore( ah );    
    }


}

/******************************************************************************/
/**
\brief  ~ActivityManagerI

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ActivityManagerI"

                        ActivityManagerI :: ~ActivityManagerI ( )
{

  if ( p ) 
    delete p;

}


