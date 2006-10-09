/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    NParm

\brief    Parm list
          This  string buffer supports parm lists. Parmlists are ofton passed as
          a  single string and  have to be  splitted into single parameters. The
          NParm-object  supports different types of Parameter lists according to
          type and separator:
          - position parameters
          - keyword parameters 
          Position  parameters  might  be  separated  by different separators as
          ';', ',' or spaces. Keyword parameters are supported in three ways:
          	ab keyword(value)
          	ab keyword=value;
          	ab keyword:value
          Within  one parm list different keyword types  can be used at the same
          time. Only the value is returned when requesting parameters. 

          all  functions  that  may  signal  an  error.  Otherwise  the  calling
          function  may not be  able to determine  whether the error signaled is
          an  old error or  has just been  signaled in the called function. This
          strategy  requires, on the other hand, that signaled errors have to be
          saved  when  other  functions  are  called  in the error handling thet
          might  generate  errors  again,  since  those functions will reset the
          error. You can use the Copy() function to save the error. 
          The  way errors are presented in  the application depends on the error
          handler  installed (ErroerHandle).  Usually errors  are written to the
          console  output for  console applications  and shown  in a message box
          for windows applications.

\date     $Date: 2006/03/12 19:21:46,15 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "NParm"

#include  <pdefault.h>
#include  <igvts.h>
#include  <sNParm.hpp>


/******************************************************************************/
/**
\brief  GetPos

\return parm_no - Parm number

\param  parm_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPos"

int32 NParm :: GetPos (char *parm_string )
{

  return ( GetParmPos(*this,parm_string,separator,NO) );

}

/******************************************************************************/
/**
\brief  NParm

-------------------------------------------------------------------------------
\brief i0


\param  parm_string -
\param  separator - Separator character
\param  key_parms - Parmlist with key parameter format
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NParm"

                        NParm :: NParm (char *parm_string, char separator, logical key_parms )
                     :  NBuffer (),
  count(0),
  parm_value(NULL),
  separator(separator),
  keyword_opt(key_parms)
{

  if ( parm_string )
    *this = parm_string;

}

/******************************************************************************/
/**
\brief i01


\param  separator - Separator character
\param  key_parms - Parmlist with key parameter format
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NParm"

                        NParm :: NParm (char separator, logical key_parms )
                     :  NBuffer (),
  count(0),
  parm_value(NULL),
  separator(separator),
  keyword_opt(key_parms)
{



}

/******************************************************************************/
/**
\brief  operator() - Get parameter
        The  function returns  the parameter  value at  the required position or
        for  the passed keyword. When  requesting keyword parameters as position
        parameters   keyword   and   value   are   returned  including the value
        separators (e.g. "Fields=(a,b,c)"

\return parm_value
-------------------------------------------------------------------------------
\brief i00


\param  parm_no - Parm number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator()"

char *NParm :: operator() (int32 parm_no )
{

  if ( parm_value )
    free(parm_value);
  parm_value = NULL;
  
//  parm_value = GetPosParm(*this,parm_no,separator,YES);
//  wenn pfade im context als parm uebergeben werden, muessen leerzeichen drinbleiben
//  rk 04.05.2003 
  parm_value = GetPosParm(*this,parm_no,separator,NO);

  return(parm_value);
}

/******************************************************************************/
/**
\brief i01


\param  parm_key - Parameter keyword
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator()"

char *NParm :: operator() (char *parm_key )
{

  if ( parm_value )
    free(parm_value);
  
  parm_value = GetKeyParm(*this,parm_key,YES,YES);
  return(parm_value);
}

/******************************************************************************/
/**
\brief  operator= - Set new parameter string
        The  function replaces the parameter string  by a new one. The parameter
        string is copied into an internal area.

\return term - Success

\param  parm_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

logical NParm :: operator= (char *parm_string )
{
  logical                 term = NO;
  *(NBuffer *)this = parm_string;

  return(term);
}

/******************************************************************************/
/**
\brief  ~NParm


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~NParm"

                        NParm :: ~NParm ( )
{

  free(parm_value);
  parm_value = NULL;

}


