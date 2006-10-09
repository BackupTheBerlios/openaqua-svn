/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBHeader

\brief    


\date     $Date: 2006/03/12 19:17:05,42 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBHeader"

#include  <popa7.h>
#include  <iNetConversion.h>
#include  <sDBHeader.hpp>


/******************************************************************************/
/**
\brief  DBHeader - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBHeader"

                        DBHeader :: DBHeader ( )
                     :   last_str_number(1000),
  root_objekt(0), 
  recover_number(0),
  version(CUR_DBVERSION),
  recover_first(0),
  schema_version(0),
  save_transaction(NO),
  write_transact(0),
  recover_pos(0),
  recover_write(NO),
  system_version(CUR_SYSVERSION),
  shadow_db(),
  next_ws_number(0)
{

  memset(recover_path,0,sizeof(recover_path));
  memset(reserved1,' ',sizeof(reserved1));
  memset(reserved,0,sizeof(reserved));
  memcpy(ident,"DBH2",4);

}

/******************************************************************************/
/**
\brief  FromPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

void DBHeader :: FromPIF (logical pif )
{

  last_str_number = PIFToShort(last_str_number,pif);
  recover_number  = PIFToShort(recover_number,pif);
  recover_first   = PIFToShort(recover_first,pif);
  root_objekt     = PIFToLong(root_objekt,pif);
  version         = PIFToShort(version,pif);
  schema_version  = PIFToShort(schema_version,pif);
  write_transact  = PIFToLong(write_transact,pif);
  recover_pos     = PIFToLong(recover_pos,pif);
  system_version  = PIFToShort(system_version,pif);
  next_ws_number  = PIFToLong(next_ws_number,pif);
  shadow_db       = PIFToBig(shadow_db.get_ebsnum(),pif);

}

/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void DBHeader :: Initialize ( )
{

  memset(recover_path,0,sizeof(recover_path));
  memset(reserved1,' ',sizeof(reserved1));
  memset(reserved,0,sizeof(reserved));
  memcpy(ident,"DBH2",4);
  
  last_str_number = 64;
  root_objekt     = 0; 
  recover_number  = 0;
  recover_first   = 0;
  
  version         = CUR_DBVERSION;
  system_version  = CUR_SYSVERSION;


}

/******************************************************************************/
/**
\brief  ToPIF - 



\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

void DBHeader :: ToPIF (logical pif )
{

  last_str_number = ShortToPIF(last_str_number,pif);
  recover_number  = ShortToPIF(recover_number,pif);
  recover_first   = ShortToPIF(recover_first,pif);
  root_objekt     = LongToPIF(root_objekt,pif);
  version         = ShortToPIF(version,pif);
  schema_version  = ShortToPIF(schema_version,pif);
  write_transact  = LongToPIF(write_transact,pif);
  recover_pos     = LongToPIF(recover_pos,pif);
  system_version  = ShortToPIF(system_version,pif);
  next_ws_number  = LongToPIF(next_ws_number,pif);
  shadow_db       = BigToPIF(shadow_db.get_ebsnum(),pif);


}

/******************************************************************************/
/**
\brief  get_last_str_number - 


\return last_str_number -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_last_str_number"

int32 DBHeader :: get_last_str_number ( )
{


  return(last_str_number);
}

/******************************************************************************/
/**
\brief  get_recover_first - 


\return recover_first -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_recover_first"

int16 DBHeader :: get_recover_first ( )
{


  return(recover_first);
}

/******************************************************************************/
/**
\brief  get_recover_number - 


\return recover_number -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_recover_number"

uint16 DBHeader :: get_recover_number ( )
{


  return(recover_number);
}

/******************************************************************************/
/**
\brief  get_recover_pos - 


\return recover_pos -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_recover_pos"

int32 DBHeader :: get_recover_pos ( )
{


  return(recover_pos);
}

/******************************************************************************/
/**
\brief  get_root_objekt - 


\return root_objekt -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_root_objekt"

EB_Number DBHeader :: get_root_objekt ( )
{


  return(root_objekt);
}

/******************************************************************************/
/**
\brief  get_schema_version - 


\return schema_version -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_schema_version"

int16 DBHeader :: get_schema_version ( )
{


  return(schema_version);
}

/******************************************************************************/
/**
\brief  get_system_version - 


\return system_version -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_system_version"

int16 DBHeader :: get_system_version ( )
{


  return(system_version);
}

/******************************************************************************/
/**
\brief  get_version - 


\return version -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_version"

int16 DBHeader :: get_version ( )
{


  return(version);
}

/******************************************************************************/
/**
\brief  get_write_transact - 


\return write_transact -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_write_transact"

int32 DBHeader :: get_write_transact ( )
{


  return(write_transact);
}

/******************************************************************************/
/**
\brief  inc_next_ws_number - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "inc_next_ws_number"

void DBHeader :: inc_next_ws_number ( )
{

  next_ws_number++;

}

/******************************************************************************/
/**
\brief  set_last_str_num - 



\param  maxstrnum -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_last_str_num"

void DBHeader :: set_last_str_num (uint16 maxstrnum )
{

BEGINSEQ
  if ( last_str_number <= maxstrnum )
  {
    last_str_number = maxstrnum;
//    SDBERR(99);
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  set_next_ws_number - 



\param  ws_num -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_next_ws_number"

void DBHeader :: set_next_ws_number (int32 ws_num )
{

  next_ws_number = ws_num;

}

/******************************************************************************/
/**
\brief  set_recover_fst - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_recover_fst"

void DBHeader :: set_recover_fst ( )
{

  if ( !recover_first )
    recover_first = recover_number;

}

/******************************************************************************/
/**
\brief  set_recover_numb - 


\return recnum - Numer of recovery file

\param  recnum - Numer of recovery file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_recover_numb"

uint16 DBHeader :: set_recover_numb (uint16 recnum )
{

  return(recover_number = recnum);

}

/******************************************************************************/
/**
\brief  set_recover_path - 



\param  recpath - Recovery path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_recover_path"

void DBHeader :: set_recover_path (char *recpath )
{

  if ( recpath )
    strncpy(recover_path,recpath,sizeof(recover_path)-1);
  else
    memset(recover_path,0,sizeof(recover_path));


}

/******************************************************************************/
/**
\brief  set_recover_pos - 



\param  rec_position -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_recover_pos"

void DBHeader :: set_recover_pos (int32 rec_position )
{

  recover_pos = rec_position;

}

/******************************************************************************/
/**
\brief  set_recover_writ - 



\param  recover_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_recover_writ"

void DBHeader :: set_recover_writ (logical recover_opt )
{

  recover_write = recover_opt;

}

/******************************************************************************/
/**
\brief  set_root_objekt - 


\return entnr -

\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_root_objekt"

EB_Number DBHeader :: set_root_objekt (EB_Number entnr )
{

  root_objekt = (uint32)entnr.get_ebsnum();
  return(entnr);
}

/******************************************************************************/
/**
\brief  set_save_ta - 


\return term - Termination code

\param  save_ta -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_save_ta"

logical DBHeader :: set_save_ta (logical save_ta )
{
  logical     oldstate = save_transaction;
  save_transaction = save_ta;
  return(oldstate);
}

/******************************************************************************/
/**
\brief  set_schema_vers - 



\param  version -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_schema_vers"

void DBHeader :: set_schema_vers (uint16 version )
{

  schema_version = version;

}

/******************************************************************************/
/**
\brief  set_system_version


\param  version -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_system_version"

void DBHeader :: set_system_version (uint16 version )
{

  system_version = version;

}

/******************************************************************************/
/**
\brief  set_version - 



\param  new_version -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_version"

void DBHeader :: set_version (int16 new_version )
{

  version = new_version;

}

/******************************************************************************/
/**
\brief  set_write_ta - 


\return wta_number -

\param  write_ta -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_write_ta"

int32 DBHeader :: set_write_ta (char write_ta )
{
  int32        wta_number = write_transact;
  write_transact = write_ta;
  return(wta_number);
}


