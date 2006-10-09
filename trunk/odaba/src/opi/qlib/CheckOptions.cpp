/********************************* Class Source Code ***************************/
/**
\package  OPI
\class    CheckOptions

\brief    


\date     $Date: 2006/04/24 19:58:16,40 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CheckOptions"

#include  <pdefault.h>
#include  <sCheckOptions.hpp>


/******************************************************************************/
/**
\brief  CheckOptions - 


-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckOptions"

                        CheckOptions :: CheckOptions ( )
                     :   guids(YES),
  deleted_references(YES),
  inverse_references(YES),
  ref_indexes(YES),
  key_values(NO),
  instances(YES),
  collections(YES),
  repair_all(NO),
  show_warnings(NO),
  remote(NO)
{



}

/******************************************************************************/
/**
\brief  i01


\param  parmstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckOptions"

                        CheckOptions :: CheckOptions (char *parmstring )
                     :   guids(YES),
  deleted_references(YES),
  inverse_references(YES),
  ref_indexes(YES),
  key_values(NO),
  instances(YES),
  collections(YES),
  repair_all(NO),
  show_warnings(NO),
  remote(NO)
{

  Initialize(parmstring);

}

/******************************************************************************/
/**
\brief  Initialize

\return term - Termination code

\param  parmstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical CheckOptions :: Initialize (char *parmstring )
{
  char                   *string;
  logical                 term = NO;
  if ( string = GetKeyParm(parmstring,"-C",NO,YES) )
  {
    guids              = NO;
    inverse_references = NO;
    ref_indexes        = NO;
    while ( *string )
    {
      switch ( *string )
      {
        case 'g' : 
        case 'G' : guids = YES;
                   break;
        case 'i' : 
        case 'I' : inverse_references = YES;
                   break;
        case 'x' : 
        case 'X' : ref_indexes = YES;
                   break;
        case 'k' : 
        case 'K' : key_values = YES;
                   break;
        default  : printf("invalid check (-C) option: %c",*string);
                   term = YES;
      }
      *string++;
    }
  }
  if ( string = GetKeyParm(parmstring,"-T",NO,YES) )
  {
    instances   = NO;
    collections = NO;
    switch ( *string )
    {
      case 'i' : 
      case 'I' : instances = YES;
                 break;
      case 'c' : 
      case 'C' : collections = YES;
                 break;
      case 'a' : 
      case 'A' : instances = YES;
                 collections = YES;
                 break;
      default  : printf("invalid type (-T) option: %c",*string);
                 term = YES;
    }
  }
  if ( string = GetKeyParm(parmstring,"-R",NO,YES) )
    repair_all = YES;
  if ( string = GetKeyParm(parmstring,"-W",NO,YES) )
    show_warnings = YES;

  return(term);
}


