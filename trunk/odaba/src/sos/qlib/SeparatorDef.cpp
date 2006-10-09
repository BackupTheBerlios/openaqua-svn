/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    SeparatorDef

\brief    Separator definition


\date     $Date: 2006/03/12 19:21:58,53 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SeparatorDef"

#include  <pdefault.h>
#include  <csmcbdef.h>
#include  <sfmcb.hpp>
#include  <sSeparatorDef.hpp>


/******************************************************************************/
/**
\brief  SeparatorDef - 



\param  str_sep - String separator
\param  field_sep - Field separator
\param  block_sep - Block separator
\param  line_sep -
\param  empty_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SeparatorDef"

                        SeparatorDef :: SeparatorDef (char *str_sep, char *field_sep, char *block_sep, char *line_sep, char *empty_string )
{
  fmcb     *staticfmcb = fmcb::GetStaticFMCB(T_STRING);
  memset(this,0,sizeof(*this));
  
  stringfmcb = new fmcb();
  *stringfmcb = *staticfmcb;
  
  if ( str_sep && *str_sep )
  {
    string_start = *str_sep ? *str_sep : *(str_sep+1) ;
    if ( string_start == ' ' )
      string_start = 0;
    if ( str_sep[1] )
    {
      string_stop = str_sep[1];
      if ( string_stop == ' ' )
        string_stop = 0;
      string_repl  = str_sep[2];
      if ( string_repl == ' ' )
        string_repl = 0;
    }
    else
      string_stop = *str_sep;
  }
  
  if ( field_sep && *field_sep)
  {
    field_start = *(field_sep+1) ? *field_sep : 0;
    if ( field_start == ' ' )
      field_start = 0;
    if ( field_sep[1] )
    {
      field_stop  = field_sep[1];
      if ( field_stop == ' ' )
        field_stop = 0;
      field_repl  = field_sep[2];
      if ( field_repl == ' ' )
        field_repl = 0;
    }
    else 
      field_stop  = *field_sep;
      
  }
  
  if ( block_sep && *block_sep )
  {
    block_start = *block_sep ? *block_sep : *(block_sep+1);
    if ( block_start == ' ' )
      block_start = 0;
    if ( block_sep[1] )
    {
      block_stop = block_sep[1];
      if ( block_stop == ' ' )
        block_stop = 0;
      block_repl  = *(block_sep+2);
      if ( block_repl == ' ' )
        block_repl = 0;
    }
    else 
      block_stop = *block_sep;
  }

  if ( line_sep && *line_sep )
    strncpy(new_line,line_sep,sizeof(new_line)-1);

  if ( empty_string )
    strncpy(empty_str,empty_string,sizeof(empty_str)-1);


}

/******************************************************************************/
/**
\brief  ~SeparatorDef - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SeparatorDef"

                        SeparatorDef :: ~SeparatorDef ( )
{

  delete stringfmcb;
  stringfmcb = NULL;

}


