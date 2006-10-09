/********************************* Class Source Code ***************************/
/**
\package  OPI - 
\class    PIStack

\brief    Property handle stack
          A  property handle stack allows defining  a series of related property
          handles.  A Property handle stack can be defined for a property handle
          and  allows activating a  new and saving  the current handle using the
          Push()  function and re-activating the previous handle using the Pop()
          function.  Thus,  it  becomes  possible,  e.g.  defining a sequence of
          subsequent  selections  with  the  possibility  of  going  back to the
          prevoius level.

\date     $Date: 2006/08/25 14:44:01,89 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "PIStack"

#include  <pdefault.h>
#include  <sNodeStack.hpp>
#include  <sPropertyHandle.hpp>
#include  <sPIStack.hpp>


/******************************************************************************/
/**
\brief  Count - 



\return count - Number of entries

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Count"

int32 PIStack :: Count ( )
{

  return( stack ? stack->GetSize() : ERIC );

}

/******************************************************************************/
/**
\brief  PIStack - Constrauctor

        The  constructor creates a  stack for the  property handle passed to the
        constructor.


\param  property_handle - Pointer to a property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PIStack"

     PIStack :: PIStack (PropertyHandle *property_handle )
                     : PropertyHandle (property_handle),
  stack(new NodeStack())
{



}

/******************************************************************************/
/**
\brief  Pop - Load prevois handle from stack

        The  function loads the previously pushed property handle from the stack
        and  restores it in  the related property  handle. The current handle is
        closed before.

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Pop"

logical PIStack :: Pop ( )
{
  logical    term = NO;
BEGINSEQ
  if ( !stack || stack->GetSize() < 1 )              ERROR
  RegisterNode(stack->Pop());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Push - Push handle to stack

        The  function  pushes  the  current  handle  to the stack and clears the
        related  property handle. The related property handle is empty after the
        Push() function returns and must be re-opened by the application.

-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Push"

void PIStack :: Push ( )
{

  stack->Push(get_nodeptr());
  Close();  


}

/******************************************************************************/
/**
\brief  i01 - 



\param  property_handle - Pointer to a property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Push"

void PIStack :: Push (PropertyHandle *property_handle )
{

  stack->Push(get_nodeptr());
  Open(property_handle);  


}

/******************************************************************************/
/**
\brief  ~PIStack - Destructor

        The  destructor pops all property handles from the stack before deleting
        the  stack. If  there is  any property  handle on the stack the property
        handle  refers to  the first  property handle  pushed to the stack after
        closing the stack.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~PIStack"

     PIStack :: ~PIStack ( )
{



}


