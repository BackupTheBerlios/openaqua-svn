/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DSyntaxClass

\brief    


\date     $Date: 2006/03/13 21:35:03,32 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DSyntaxClass"

#include  <pogui7.h>
#include  <sDSyntaxClass.hpp>


/******************************************************************************/
/**
\brief  DSyntaxClass


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DSyntaxClass"

                        DSyntaxClass :: DSyntaxClass ( )
                     : class_name(),
  expressions()
{



}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void DSyntaxClass :: Reset ( )
{
  char          *string;
  while ( string = expressions.RemoveHead() )
    free(string);

}

/******************************************************************************/
/**
\brief  ~DSyntaxClass - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DSyntaxClass"

                        DSyntaxClass :: ~DSyntaxClass ( )
{

  Reset();

}


