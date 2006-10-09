/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    CSInstanceList

\brief    


\date     $Date: 2006/07/31 12:10:05,59 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSInstanceList"

#include  <popa7.h>
#include  <cSDB_AT.h>
#include  <sACObject.hpp>
#include  <sCDictionary.hpp>
#include  <sCNode.hpp>
#include  <sCSInstance.hpp>
#include  <sCS_Handle.hpp>
#include  <sCS_Message.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBIndex.hpp>
#include  <sDBIndexList.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sENUM_Value.hpp>
#include  <sENUM_ValueList.hpp>
#include  <sParmList.hpp>
#include  <sSC_DBObject.hpp>
#include  <sSC_Property.hpp>
#include  <sStructDef.hpp>
#include  <skcb.hpp>
#include  <skfc.hpp>
#include  <ssmcb.hpp>
#include  <sCSInstanceList.hpp>


/******************************************************************************/
/**
\brief  CSInstanceList - 




\param  maxcount - 
\param  convopt - 
\param  mess_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSInstanceList"

     CSInstanceList :: CSInstanceList (int16 maxcount, logical convopt, int32 mess_len )
                     : list(NULL),
  count(maxcount > 0 ? maxcount : 0),
  curcount(0),
  inst_area(mess_len),
  conversion(convopt),
  cs_message(new CS_Message())
{

  if ( count > 0 )
    list = new CSInstance[count];
    
  cs_message->SetData((char *)inst_area.GetData());


}

/******************************************************************************/
/**
\brief  Fill - 



-------------------------------------------------------------------------------
\brief  i00 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill ( )
{

  Reset();
  Terminate();


}

/******************************************************************************/
/**
\brief  ib_00 - 



\param  buffer - 
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (void *buffer, uint16 len )
{

  Reset();
  
  inst_area.Fill(buffer,len,conversion,YES);  

  Terminate();

}

/******************************************************************************/
/**
\brief  ib_o1 - 



\param  buffer - 
\param  len - 
\param  short_val - 16 bit integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (void *buffer, uint16 len, int16 short_val )
{

  Reset();
  
  inst_area.Fill(buffer,len,conversion,YES);  
  inst_area.Fill(short_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_01 - 



\param  handle - 
\param  string - 
\param  long_val - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, char *string, int32 long_val, uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_02 - 



\param  handle - 
\param  long_val - 
\param  ushort_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, int32 long_val, uint16 ushort_val )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(ushort_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_03 - 



\param  handle - 
\param  long_val - 
\param  long_val1 - 
\param  ushort_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, int32 long_val, int32 long_val1, uint16 ushort_val )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(long_val1,conversion,YES);
  inst_area.Fill(ushort_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_04 - 



\param  handle - 
\param  key_inst - 
\param  keysmcb - 
\param  long_val - 
\param  long_val1 - 
\param  long_val2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, Key key_inst, smcb *keysmcb, int32 long_val, int32 long_val1, int32 long_val2 )
{
  char    string[ID_SIZE+1];
  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(key_inst,keysmcb,conversion,YES);
  inst_area.Fill(keysmcb ? gvtxbts(string,keysmcb->smcbname,ID_SIZE) : (char *)NULL,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(long_val1,conversion,YES);
  inst_area.Fill(long_val2,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ih_05 - 



\param  handle - 
\param  string - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, char *string, uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_06 - 



\param  handle - 
\param  string - 
\param  long_val - 
\param  uchar_val1 - 
\param  ushort_val - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, char *string, int32 long_val, uint8 uchar_val1, uint16 ushort_val, uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(uchar_val1,conversion,YES);
  inst_area.Fill(ushort_val,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_07 - 



\param  handle - 
\param  handle1 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, CS_Handle *handle1 )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(handle1,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_08 - 



\param  handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_09 - 



\param  handle - 
\param  string - 
\param  long_val - 
\param  ushort_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, char *string, int32 long_val, uint16 ushort_val )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(ushort_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_10 - 



\param  handle - 
\param  long_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, int32 long_val )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_11 - 



\param  handle - 
\param  long_val1 - 
\param  long_val2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, int32 long_val1, int32 long_val2 )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(long_val1,conversion,YES);
  inst_area.Fill(long_val2,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_12 - 



\param  handle - 
\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, char *string )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(string,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_13 - 



\param  handle - 
\param  key_inst - 
\param  keysmcb - 
\param  long_val1 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, Key key_inst, smcb *keysmcb, int32 long_val1 )
{
  char    string[ID_SIZE+1];
  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(key_inst,keysmcb,conversion,YES);
  inst_area.Fill(keysmcb ? gvtxbts(string,keysmcb->smcbname,ID_SIZE) : (char *)NULL,conversion,YES);
  inst_area.Fill(long_val1,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ih_14 - 



\param  handle - 
\param  string - 
\param  long_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, char *string, int32 long_val )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ih_15 - 



\param  handle - 
\param  handle1 - 
\param  uchar_val - 
\param  long_val - 
\param  uchar_val1 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, CS_Handle *handle1, uint8 uchar_val, int32 long_val, uint8 uchar_val1 )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(handle1,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(uchar_val1,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ih_16 - 



\param  handle - 
\param  uchar_val - 
\param  long_val1 - 
\param  long_val2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, uint8 uchar_val, int32 long_val1, int32 long_val2 )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);
  inst_area.Fill(long_val1,conversion,YES);
  inst_area.Fill(long_val2,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ii_00 - 



\param  insthandle - 
\param  strdef - Structure definition
\param  instlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (Instance insthandle, DBStructDef *strdef, int32 instlen )
{
  char    string[ID_SIZE+1];
  Reset();
  
  inst_area.Fill(insthandle,strdef,instlen,conversion,YES);
  inst_area.Fill(strdef ? gvtxbts(string,strdef->smcbname,ID_SIZE) : (char *)NULL,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ii_01 - 



\param  insthandle - 
\param  field_def - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (Instance insthandle, DBFieldDef *field_def, uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(insthandle,field_def,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ii_02 - 



\param  insthandle - 
\param  strdef - Structure definition
\param  instlen - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (Instance insthandle, DBStructDef *strdef, int32 instlen, uint8 uchar_val )
{
  char    string[ID_SIZE+1];
  Reset();
  
  inst_area.Fill(insthandle,strdef,instlen,conversion,YES);
  inst_area.Fill(strdef ? gvtxbts(string,strdef->smcbname,ID_SIZE) : (char *)NULL,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ik_00 - 



\param  key_inst - 
\param  keysmcb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (Key key_inst, smcb *keysmcb )
{
  char    string[ID_SIZE+1];
  Reset();
  
  inst_area.Fill(key_inst,keysmcb,conversion,YES);
  inst_area.Fill(keysmcb ? gvtxbts(string,keysmcb->smcbname,ID_SIZE) : (char *)NULL,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ik_01 - 



\param  key_inst - 
\param  keysmcb - 
\param  short_val - 16 bit integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (Key key_inst, smcb *keysmcb, int16 short_val )
{
  char    string[ID_SIZE+1];
  Reset();
  
  inst_area.Fill(key_inst,keysmcb,conversion,YES);
  inst_area.Fill(keysmcb ? gvtxbts(string,keysmcb->smcbname,ID_SIZE) : (char *)NULL,conversion,YES);
  inst_area.Fill(short_val,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ik_02 - 



\param  key_inst - 
\param  keysmcb - 
\param  long_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (Key key_inst, smcb *keysmcb, int32 long_val )
{
  char    string[ID_SIZE+1];
  Reset();
  
  inst_area.Fill(key_inst,keysmcb,conversion,YES);
  inst_area.Fill(keysmcb ? gvtxbts(string,keysmcb->smcbname,ID_SIZE) : (char *)NULL,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ik_03 - 



\param  key_inst - 
\param  keysmcb - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (Key key_inst, smcb *keysmcb, uint8 uchar_val )
{
  char    string[ID_SIZE+1];

  Reset();
  
  inst_area.Fill(key_inst,keysmcb,conversion,YES);
  inst_area.Fill(keysmcb ? gvtxbts(string,keysmcb->smcbname,ID_SIZE) : (char *)NULL,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  il_00 - 



\param  long_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int32 long_val )
{

  Reset();
  
  inst_area.Fill(long_val,conversion,YES);  

  Terminate();

}

/******************************************************************************/
/**
\brief  il_01 - 



\param  long_val - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int32 long_val, uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(long_val,conversion,YES);  
  inst_area.Fill(uchar_val,conversion,YES);  

  Terminate();

}

/******************************************************************************/
/**
\brief  il_02 - 



\param  long_val - 
\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int32 long_val, char *string )
{

  Reset();
  
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(string,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  il_03 - 



\param  long_val - 
\param  sort_key_inst - 
\param  skey_smcb - 
\param  key_inst - 
\param  idkey_smcb - 
\param  insthandle - 
\param  strdef - Structure definition
\param  instlen - 
\param  is_iselarea - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int32 long_val, Key sort_key_inst, smcb *skey_smcb, Key key_inst, smcb *idkey_smcb, Instance insthandle, DBStructDef *strdef, int32 instlen, logical is_iselarea, uint8 uchar_val )
{
  char      string[ID_SIZE+1];
// Wer benutz dies ? einfügen von Strukturnamen und schlüsselnamen ?!  
  
  Reset();
  
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(sort_key_inst,skey_smcb,conversion,YES);
  inst_area.Fill(skey_smcb ? gvtxbts(string,skey_smcb->smcbname,ID_SIZE) : NULL,conversion,YES);
  inst_area.Fill(key_inst,idkey_smcb,conversion,YES);
  inst_area.Fill(idkey_smcb ? gvtxbts(string,idkey_smcb->smcbname,ID_SIZE): NULL,conversion,YES);
  inst_area.Fill(insthandle,strdef,instlen,conversion,YES);
  inst_area.Fill(strdef ? gvtxbts(string,strdef->smcbname,ID_SIZE) : NULL,conversion,YES);
  inst_area.Fill(is_iselarea,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  il_04 - 



\param  long_val1 - 
\param  long_val2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int32 long_val1, int32 long_val2 )
{

  Reset();
  
  inst_area.Fill(long_val1,conversion,YES);  
  inst_area.Fill(long_val2,conversion,YES);  

  Terminate();

}

/******************************************************************************/
/**
\brief  il_05 - 



\param  long_val - 
\param  string1 - 
\param  string2 - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int32 long_val, char *string1, char *string2, uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(string1,conversion,YES);
  inst_area.Fill(string2,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  il_06 - 



\param  long_val1 - 
\param  long_val2 - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int32 long_val1, int32 long_val2, uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(long_val1,conversion,YES);  
  inst_area.Fill(long_val2,conversion,YES);  
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  il_07 - 



\param  long_val - 
\param  uchar_val1 - 
\param  uchar_val2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int32 long_val, uint8 uchar_val1, logical uchar_val2 )
{

  Reset();
  
  inst_area.Fill(long_val,conversion,YES);  
  inst_area.Fill(uchar_val1,conversion,YES);
  inst_area.Fill(uchar_val2,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ilo_00 - 



\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ilo_01 - 



\param  uchar_val - 
\param  long_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (uint8 uchar_val, int32 long_val )
{

  Reset();
  
  inst_area.Fill(uchar_val,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ilo_02 - 



\param  uchar_val - 
\param  short_val - 16 bit integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (uint8 uchar_val, int16 short_val )
{

  Reset();
  
  inst_area.Fill(uchar_val,conversion,YES);
  inst_area.Fill(short_val,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ilo_03 - 



\param  error_case - Error indication
\param  insthandle - 
\param  strdef - Structure definition
\param  instlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (logical error_case, Instance insthandle, DBStructDef *strdef, int32 instlen )
{
  char    string[ID_SIZE+1];
  Reset();
  
  inst_area.Fill(error_case,conversion,YES);
  inst_area.Fill(insthandle,strdef,instlen,conversion,YES);
  inst_area.Fill(gvtxbts(string,strdef->smcbname,ID_SIZE),conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ilo_04 - 



\param  error_case - Error indication
\param  insthandle - 
\param  strdef - Structure definition
\param  instlen - 
\param  objid - Instance or index identity
\param  indx0 - Position in collection
\param  rel_indx0 - 
\param  uchar_val - 
\param  skey_smcb - 
\param  new_instance - 
\param  inst_inserted - 
\param  parent_changed - 
\param  version_nr - Internal version number
\param  is_init_instance - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (logical error_case, Instance insthandle, DBStructDef *strdef, int32 instlen, int32 objid, int32 indx0, int32 rel_indx0, uint8 uchar_val, smcb *skey_smcb, logical new_instance, logical inst_inserted, logical parent_changed, uint16 version_nr, logical is_init_instance )
{
  char    string[ID_SIZE+1];
  Reset();
  
  inst_area.Fill(error_case,conversion,YES);
  inst_area.Fill(insthandle,strdef,instlen,conversion,YES);
  inst_area.Fill(gvtxbts(string,strdef->smcbname,ID_SIZE),conversion,YES);
  inst_area.Fill(objid,conversion,YES);
  inst_area.Fill(indx0,conversion,YES);
  inst_area.Fill(rel_indx0,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);
  inst_area.Fill(skey_smcb ? gvtxbts(string,skey_smcb->smcbname,ID_SIZE) : NULL,conversion,YES);
  inst_area.Fill(new_instance,conversion,YES);
  inst_area.Fill(inst_inserted,conversion,YES);
  inst_area.Fill(parent_changed,conversion,YES);
  inst_area.Fill(version_nr,conversion,YES);
  inst_area.Fill(is_init_instance,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ilo_05 - 



\param  error_case - Error indication
\param  key_inst - 
\param  keysmcb - 
\param  objid - Instance or index identity
\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (logical error_case, Key key_inst, smcb *keysmcb, int32 objid, int32 indx0 )
{
  char    string[ID_SIZE+1];
  Reset();
  
  inst_area.Fill(error_case,conversion,YES);
  inst_area.Fill(key_inst,keysmcb,conversion,YES);
  inst_area.Fill(gvtxbts(string,keysmcb->smcbname,ID_SIZE),conversion,YES);
  inst_area.Fill(objid,conversion,YES);
  inst_area.Fill(indx0,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ilo_06 - 



\param  error_case - Error indication
\param  fielddef - Internal field defintion
\param  keysmcb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (logical error_case, DBFieldDef *fielddef, smcb *keysmcb )
{
  char    string[ID_SIZE+1];
  Reset();
  
  inst_area.Fill(error_case,conversion,YES);
  FillDBFieldDef(fielddef);
  inst_area.Fill(keysmcb ? gvtxbts(string,keysmcb->smcbname,ID_SIZE) : (char *)NULL,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  ilo_07 - 



\param  error_case - Error indication
\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (logical error_case, char *string )
{

  Reset();
  
  inst_area.Fill(error_case,conversion,YES);
  inst_area.Fill(string,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  is_00 - 



\param  short_val - 16 bit integer value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int16 short_val )
{

  Reset();
  
  inst_area.Fill(short_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  is_01 - 



\param  short_val1 - 
\param  short_val2 - 
\param  short_val3 - 
\param  string - 
\param  long_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int16 short_val1, int16 short_val2, int16 short_val3, char *string, int32 long_val )
{

  Reset();
  
  inst_area.Fill(short_val1,conversion,YES);
  inst_area.Fill(short_val2,conversion,YES);
  inst_area.Fill(short_val3,conversion,YES);
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  is_02 - 



\param  short_val1 - 
\param  string - 
\param  short_val2 - 
\param  short_val3 - 
\param  long_val - 
\param  uchar_val - 
\param  uchar_val1 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int16 short_val1, char *string, int16 short_val2, int16 short_val3, int32 long_val, uint8 uchar_val, uint8 uchar_val1 )
{

  Reset();
  
  inst_area.Fill(short_val1,conversion,YES);
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(short_val2,conversion,YES);
  inst_area.Fill(short_val3,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);
  inst_area.Fill(uchar_val1,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  is_03 - 



\param  short_val1 - 
\param  short_val2 - 
\param  string - 
\param  long_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int16 short_val1, int16 short_val2, char *string, int32 long_val )
{

  Reset();
  
  inst_area.Fill(short_val1,conversion,YES);
  inst_area.Fill(short_val2,conversion,YES);
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  is_04 - 



\param  short_val - 16 bit integer value
\param  error_case - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int16 short_val, logical error_case )
{

  Reset();
  
  inst_area.Fill(short_val,conversion,YES);
  inst_area.Fill(error_case,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  is_05 - 



\param  short_val - 16 bit integer value
\param  string - 
\param  long_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (int16 short_val, char *string, int32 long_val )
{

  Reset();
  
  inst_area.Fill(short_val,conversion,YES);
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_00 - 



\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string )
{

  Reset();
  
  inst_area.Fill(string,conversion,YES);  

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_01 - 



\param  string1 - 
\param  string2 - 
\param  string3 - 
\param  string4 - 
\param  uchar_val1 - 
\param  uchar_val2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string1, char *string2, char *string3, char *string4, uint8 uchar_val1, logical uchar_val2 )
{

  Reset();
  
  inst_area.Fill(string1,conversion,YES);
  inst_area.Fill(string2,conversion,YES);
  inst_area.Fill(string3,conversion,YES);
  inst_area.Fill(string4,conversion,YES);
  inst_area.Fill(uchar_val1,conversion,YES);
  inst_area.Fill(uchar_val2,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_02 - 



\param  string - 
\param  long_val - 
\param  uchar_val - 
\param  ushort_val - 
\param  uchar_val1 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string, int32 long_val, uint8 uchar_val, uint16 ushort_val, uint8 uchar_val1 )
{

  Reset();
  
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);
  inst_area.Fill(ushort_val,conversion,YES);
  inst_area.Fill(uchar_val1,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_03 - 



\param  string1 - 
\param  long_val - 
\param  string2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string1, int32 long_val, char *string2 )
{

  Reset();
  
  inst_area.Fill(string1,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(string2,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_04 - 



\param  string1 - 
\param  string2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string1, char *string2 )
{

  Reset();
  
  inst_area.Fill(string1,conversion,YES);
  inst_area.Fill(string2,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_05 - 



\param  string - 
\param  ushort_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string, uint16 ushort_val )
{

  Reset();
  
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(ushort_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_06 - 



\param  string - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string, uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_07 - 



\param  string - 
\param  ushort_val - 
\param  long_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string, uint16 ushort_val, int32 long_val )
{

  Reset();
  
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(ushort_val,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_08 - 



\param  string1 - 
\param  string2 - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string1, char *string2, uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(string1,conversion,YES);
  inst_area.Fill(string2,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_09 - 



\param  string1 - 
\param  long_val - 
\param  string2 - 
\param  string3 - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string1, int32 long_val, char *string2, char *string3, uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(string1,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(string2,conversion,YES);
  inst_area.Fill(string3,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_10 - 



\param  string1 - 
\param  string2 - 
\param  uchar_val - 
\param  string3 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string1, char *string2, uint8 uchar_val, char *string3 )
{

  Reset();
  
  inst_area.Fill(string1,conversion,YES);
  inst_area.Fill(string2,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);
  inst_area.Fill(string3,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_11 - 



\param  string - 
\param  long_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string, int32 long_val )
{

  Reset();
  
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_12 - 



\param  string1 - 
\param  long_val - 
\param  string2 - 
\param  string3 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string1, int32 long_val, char *string2, char *string3 )
{

  Reset();
  
  inst_area.Fill(string1,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);
  inst_area.Fill(string2,conversion,YES);
  inst_area.Fill(string3,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  istr_13 - 



\param  string1 - 
\param  string2 - 
\param  string3 - 
\param  short_val - 16 bit integer value
\param  long_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string1, char *string2, char *string3, int16 short_val, int32 long_val )
{

  Reset();
  
  inst_area.Fill(string1,conversion,YES);
  inst_area.Fill(string2,conversion,YES);
  inst_area.Fill(string3,conversion,YES);
  inst_area.Fill(short_val,conversion,YES);
  inst_area.Fill(long_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  it_00 - 



\param  timestamp1 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (dttm timestamp1 )
{

  Reset();
  
  inst_area.Fill(timestamp1,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  it_01 - 



\param  timestamp1 - 
\param  timestamp2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (dttm timestamp1, dttm timestamp2 )
{

  Reset();
  
  inst_area.Fill(timestamp1,conversion,YES);
  inst_area.Fill(timestamp2,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  it_02 - 



\param  timestamp1 - 
\param  ushort_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (dttm timestamp1, uint16 ushort_val )
{

  Reset();
  
  inst_area.Fill(timestamp1,conversion,YES);
  inst_area.Fill(ushort_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ius_00 - 



\param  ushort_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (uint16 ushort_val )
{

  Reset();
  
  inst_area.Fill(ushort_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ius_01 - 



\param  ushort_val - 
\param  timestamp_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (uint16 ushort_val, dttm timestamp_val )
{

  Reset();
  
  inst_area.Fill(ushort_val,conversion,YES);
  inst_area.Fill(timestamp_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  ius_02 - 



\param  ushort_val - 
\param  uchar_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (uint16 ushort_val, uint8 uchar_val )
{

  Reset();
  
  inst_area.Fill(ushort_val,conversion,YES);
  inst_area.Fill(uchar_val,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  pl_01 - 



\param  handle - 
\param  parameters - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (CS_Handle *handle, ParmList *parameters )
{

  Reset();
  
  inst_area.Fill(handle,conversion,YES);
  inst_area.Fill(parameters,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  pl_02 - 



\param  string - 
\param  parameters - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

void CSInstanceList :: Fill (char *string, ParmList *parameters )
{

  Reset();
  
  inst_area.Fill(string,conversion,YES);
  inst_area.Fill(parameters,conversion,YES);

  Terminate();


}

/******************************************************************************/
/**
\brief  FillDBExtent - 




\param  dictptr - Dictionary handle
\param  extdef - Internal extent definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBExtent"

void CSInstanceList :: FillDBExtent (Dictionary *dictptr, DBExtend *extdef )
{
  CSInstanceList     inst_list(64,conversion,8096);

  inst_list.FillDBExtentData(dictptr,extdef);
  inst_area.Fill(inst_list.get_inst_area().GetData(),
                 inst_list.get_inst_area().GetCurSize(),
                 conversion,YES); 


}

/******************************************************************************/
/**
\brief  FillDBExtentData - 




\param  dictptr - Dictionary handle
\param  extdef - Internal extent definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBExtentData"

void CSInstanceList :: FillDBExtentData (Dictionary *dictptr, DBExtend *extdef )
{

  Reset();
  if ( extdef )
  {
    FillDBFieldDef(extdef);
  
    inst_area.Fill((logical)extdef->get_intersect(),conversion,YES);
    inst_area.Fill((logical)extdef->get_union_set(),conversion,YES);
    inst_area.Fill((logical)extdef->get_disjunct(),conversion,YES);
    inst_area.Fill((int32)extdef->get_acctype(),conversion,YES);
    
    if ( extdef->fmcbsmcb && extdef->fmcbsmcb->smcbstyp == ST_CODE )
      FillDBValueList(dictptr,extdef->get_cs_values());
  }
  Terminate();

}

/******************************************************************************/
/**
\brief  FillDBExtentExt - 




\param  dictptr - Dictionary handle
\param  extdef - Internal extent definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBExtentExt"

void CSInstanceList :: FillDBExtentExt (Dictionary *dictptr, DBExtend *extdef )
{


  Reset();

  FillDBExtent(dictptr,extdef);

  Terminate();

}

/******************************************************************************/
/**
\brief  FillDBFieldDef - 




\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBFieldDef"

void CSInstanceList :: FillDBFieldDef (DBFieldDef *fielddef )
{
  CSInstanceList     inst_list(64,conversion,8096);

  inst_list.FillDBFieldDefData(fielddef);
  inst_area.Fill(inst_list.get_inst_area().GetData(),
                 inst_list.get_inst_area().GetCurSize(),
                 conversion,YES); 


}

/******************************************************************************/
/**
\brief  FillDBFieldDefData - 




\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBFieldDefData"

void CSInstanceList :: FillDBFieldDefData (DBFieldDef *fielddef )
{

  Reset();
  
  if ( fielddef )
  {
    inst_area.Fill(fielddef->fmcbname,ID_SIZE,conversion,YES);
    inst_area.Fill(fielddef->fmcbtype,ID_SIZE,conversion,YES);
    inst_area.Fill(fielddef->fmcbnsid,conversion,YES);
    inst_area.Fill(fielddef->fmcbsize,conversion,YES);
    inst_area.Fill(fielddef->fmcbdim,conversion,YES);
//    inst_area.Fill(fielddef->fmcbdim[0],conversion,YES);
//    inst_area.Fill(fielddef->fmcbdim[1],conversion,YES);
//    inst_area.Fill(fielddef->fmcbdim[2],conversion,YES);
//    inst_area.Fill(fielddef->fmcbdim[3],conversion,YES);
//    inst_area.Fill(fielddef->fmcbdim[4],conversion,YES);
    inst_area.Fill(fielddef->fmcbprec,conversion,YES);
    inst_area.Fill(fielddef->fmcbrlev,conversion,YES);
    inst_area.Fill(fielddef->fmcbposn,conversion,YES);
    inst_area.Fill(fielddef->fmcbbyte,conversion,YES);
    inst_area.Fill(fielddef->fmcbityp,conversion,YES);
// fmcbsmcb  
    inst_area.Fill((int16)fielddef->fmcberr,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbbstr,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbunicode,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbvar,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbtrans,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbopt,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbempty,conversion,YES);
// fmcbwork
// fmcbold
    inst_area.Fill((logical)fielddef->fmcbic,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbdesc,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbcnst,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbstat,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbvirt,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbinit,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcballoc_opt,conversion,YES);
    inst_area.Fill((logical)fielddef->fmcbsensi,conversion,YES);
  
// index_list
    inst_area.Fill(fielddef->get_offset_ext(),conversion,YES);
    inst_area.Fill(fielddef->get_ext_length(),conversion,YES);
// inverse_field
    inst_area.Fill((void *)fielddef->get_inverse_name(),ID_SIZE,conversion,YES);
    inst_area.Fill(fielddef->get_cluster_opt(),conversion,YES);
    inst_area.Fill(fielddef->get_mb_number(),conversion,YES);
    inst_area.Fill((void *)fielddef->get_gen_type(),8,conversion,YES);
    inst_area.Fill((int32)fielddef->get_privilege(),conversion,YES);
    inst_area.Fill(fielddef->get_static(),conversion,YES);
    inst_area.Fill(fielddef->get_virtual(),conversion,YES);
    inst_area.Fill(fielddef->get_dominant(),conversion,YES);
    inst_area.Fill(fielddef->get_sec_reference(),conversion,YES);
    inst_area.Fill(fielddef->get_log_reference(),conversion,YES);
    inst_area.Fill(fielddef->get_version(),conversion,YES);
    inst_area.Fill((char *)fielddef->get_extend(),conversion,YES);
    inst_area.Fill(fielddef->get_owning(),conversion,YES);
    inst_area.Fill(fielddef->get_create(),conversion,YES);
    inst_area.Fill(fielddef->get_weak_typed(),conversion,YES);
    inst_area.Fill(fielddef->get_depend(),conversion,YES);
    inst_area.Fill(fielddef->get_update(),conversion,YES);
    inst_area.Fill(fielddef->get_multikey(),conversion,YES);
    inst_area.Fill((char *)fielddef->get_initval(),conversion,YES);
// resource
    inst_area.Fill(fielddef->get_clst_table(),conversion,YES);
    inst_area.Fill(fielddef->get_is_base_coll(),conversion,YES);
// resource_lock
    inst_area.Fill(fielddef->get_net_pos(),conversion,YES);
    inst_area.Fill(fielddef->get_net_length(),conversion,YES);
// prev_field

    FillDBResource(fielddef->get_resource());
    FillDBIndexList(fielddef);
  }
  Terminate();


}

/******************************************************************************/
/**
\brief  FillDBFieldDefList - 




\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBFieldDefList"

void CSInstanceList :: FillDBFieldDefList (DBStructDef *strdef )
{
  DBFieldDef        *fielddef;
  logical            is_view = strdef->smcbsts.stscusr3();
  int8               trans   = AUTO;
  int32              indx0   = 0;
  int32              pcount  = 0;

BEGINSEQ
  if ( strdef->smcbfmcl )
    pcount = strdef->smcbfmcl->GetCount();
  inst_area.Fill(pcount,conversion,YES);
  if ( !count )                                      LEAVESEQ
  
  while ( fielddef = strdef->GetEntry(++indx0) )
  {
    trans = AUTO;
    if ( is_view && fielddef->fmcbrlev == R_REFR )
      if ( trans = fielddef->get_transient() )
        fielddef->set_transient(NO);
      
    FillDBFieldDef(fielddef);
    
    if ( trans != AUTO )
      fielddef->set_transient(trans);
  }

ENDSEQ

}

/******************************************************************************/
/**
\brief  FillDBIndex - 




\param  dbindex - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBIndex"

void CSInstanceList :: FillDBIndex (DBIndex *dbindex )
{
  CSInstanceList     inst_list(64,conversion,8096);

  inst_list.FillDBIndexData(dbindex);
  inst_area.Fill(inst_list.get_inst_area().GetData(),
                   inst_list.get_inst_area().GetCurSize(),
                   conversion,YES); 


}

/******************************************************************************/
/**
\brief  FillDBIndexData - 




\param  dbindex - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBIndexData"

void CSInstanceList :: FillDBIndexData (DBIndex *dbindex )
{
  char               string[ID_SIZE+1];

  *string = NULL;
  if ( dbindex->get_key_def() )
    gvtxbts(string,dbindex->get_key_def()->scbsmcb->smcbname,ID_SIZE);
  
  Reset();
  if ( dbindex )
  {
    inst_area.Fill(string,conversion,YES);
    inst_area.Fill(dbindex->get_unique(),conversion,YES);
    inst_area.Fill(dbindex->get_temporary(),conversion,YES);
    inst_area.Fill(dbindex->get_case_sensitive(),conversion,YES);
    inst_area.Fill(dbindex->get_no_empty(),conversion,YES);
    inst_area.Fill((int32)dbindex->get_set_type(),conversion,YES);
  }
  Terminate();

}

/******************************************************************************/
/**
\brief  FillDBIndexList - 




\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBIndexList"

void CSInstanceList :: FillDBIndexList (DBFieldDef *fielddef )
{
  DBIndex           *dbindex;
  int32              pcount = 0;
  CSInstanceList     inst_list(64,conversion,8096);
  int32              indx0 = 0;
BEGINSEQ
  if ( fielddef->get_index_list() )
    pcount = fielddef->get_index_list()->GetCount();
  inst_area.Fill(pcount,conversion,YES);
  if ( !pcount )                                     LEAVESEQ
    
  DLO(DBIndex)       cursor(*fielddef->get_index_list());
  while ( dbindex = cursor.GetNext() )
    FillDBIndex(dbindex);

ENDSEQ

}

/******************************************************************************/
/**
\brief  FillDBKeyComponent - 




\param  kfcptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBKeyComponent"

void CSInstanceList :: FillDBKeyComponent (kfc *kfcptr )
{
  CSInstanceList     inst_list(64,conversion,8096);

  inst_list.FillDBKeyComponentData(kfcptr);
  inst_area.Fill(inst_list.get_inst_area().GetData(),
                 inst_list.get_inst_area().GetCurSize(),
                 conversion,YES); 


}

/******************************************************************************/
/**
\brief  FillDBKeyComponentData - 




\param  kfcptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBKeyComponentData"

void CSInstanceList :: FillDBKeyComponentData (kfc *kfcptr )
{
  fmcb         *fmcbptr = NULL;
  Reset();
  if ( kfcptr && (fmcbptr = kfcptr->fcbfmcb) )
  {
    inst_area.Fill(kfcptr->get_kc_name(),conversion,YES);
    inst_area.Fill((logical)fmcbptr->fmcbic,conversion,YES);
    inst_area.Fill((logical)fmcbptr->fmcbdesc,conversion,YES);
  }
  Terminate();

}

/******************************************************************************/
/**
\brief  FillDBKeyComponentList - 




\param  kcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBKeyComponentList"

void CSInstanceList :: FillDBKeyComponentList (kcb *kcbptr )
{
  kfc               *kfcptr;
  int32              pcount = 0;
  int32              indx = 0;
BEGINSEQ
  pcount = kcbptr->scbsmcb->smcbfmcl->GetCount();
  inst_area.Fill(pcount,conversion,YES);
  if ( !pcount )                                      LEAVESEQ
    
  while ( kfcptr = kcbptr->scbfcbl->GetEntry(++indx) )
    FillDBKeyComponent(kfcptr);

ENDSEQ

}

/******************************************************************************/
/**
\brief  FillDBKeyDef - 




\param  kcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBKeyDef"

void CSInstanceList :: FillDBKeyDef (kcb *kcbptr )
{
  CSInstanceList     inst_list(64,conversion,8096);

  inst_list.FillDBKeyDefData(kcbptr);
  inst_area.Fill(inst_list.get_inst_area().GetData(),
                   inst_list.get_inst_area().GetCurSize(),
                   conversion,YES); 


}

/******************************************************************************/
/**
\brief  FillDBKeyDefData - 




\param  kcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBKeyDefData"

void CSInstanceList :: FillDBKeyDefData (kcb *kcbptr )
{

  Reset();
  if ( kcbptr )
  {
    inst_area.Fill(kcbptr->scbsmcb->smcbname,ID_SIZE,conversion,YES);
    inst_area.Fill((int16)kcbptr->get_key_num(),conversion,YES);
  
    FillDBKeyComponentList(kcbptr);
  }
  Terminate();

}

/******************************************************************************/
/**
\brief  FillDBKeyDefList - 




\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBKeyDefList"

void CSInstanceList :: FillDBKeyDefList (DBStructDef *strdef )
{
  kcb               *kcbptr = NULL;  
  CSInstanceList     inst_list(64,conversion,8096);
  int32              indx0 = 0;
  inst_area.Fill(strdef->smcbskey->GetCount(),conversion,YES);
  
  DLL(kcb) cursor(*strdef->smcbskey);
  while ( kcbptr = cursor.GetNext() )
    FillDBKeyDef(kcbptr);


}

/******************************************************************************/
/**
\brief  FillDBResource - 




\param  dbresource - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBResource"

void CSInstanceList :: FillDBResource (DBResource *dbresource )
{
  CSInstanceList     inst_list(64,conversion,8096);
  inst_list.FillDBResourceData(dbresource);
  inst_area.Fill(inst_list.get_inst_area().GetData(),
                 inst_list.get_inst_area().GetCurSize(),
                 conversion,YES); 


}

/******************************************************************************/
/**
\brief  FillDBResourceData - 




\param  dbresource - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBResourceData"

void CSInstanceList :: FillDBResourceData (DBResource *dbresource )
{

  Reset();
  if ( dbresource )
  {
    inst_area.Fill(dbresource->get_res_id(),conversion,YES);
  }
  Terminate();

}

/******************************************************************************/
/**
\brief  FillDBStructDef - 




\param  dictptr - Dictionary handle
\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBStructDef"

void CSInstanceList :: FillDBStructDef (Dictionary *dictptr, DBStructDef *strdef )
{
  CSInstanceList     inst_list(64,conversion,8096);
  inst_list.FillDBStructDefData(dictptr,strdef);
  inst_area.Fill(inst_list.get_inst_area().GetData(),
                 inst_list.get_inst_area().GetCurSize(),
                 conversion,YES); 


}

/******************************************************************************/
/**
\brief  FillDBStructDefData - 




\param  dictptr - Dictionary handle
\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBStructDefData"

void CSInstanceList :: FillDBStructDefData (Dictionary *dictptr, DBStructDef *strdef )
{
  char        csnames[ID_SIZE+1];
  Reset();
  
  if ( strdef )
  {
// when removing adding other fields to the message DBStructDef_COUNT must be updated
    inst_area.Fill(strdef->smcbname,ID_SIZE,conversion,YES);
    inst_area.Fill(strdef->smcbityp,conversion,YES);
    inst_area.Fill(strdef->smcbatyp,conversion,YES);
    inst_area.Fill(strdef->smcbstyp,conversion,YES);
    inst_area.Fill((int16)strdef->defined_align,conversion,YES);
    inst_area.Fill(strdef->GetLength(),conversion,YES);
    inst_area.Fill(strdef->get_base_info().get_count(),conversion,YES);
    inst_area.Fill(strdef->get_attr_info().get_count(),conversion,YES);
    inst_area.Fill(strdef->get_refr_info().get_count(),conversion,YES);
    inst_area.Fill(strdef->get_rshp_info().get_count(),conversion,YES);
    inst_area.Fill(strdef->get_ext_length(),conversion,YES);
    inst_area.Fill(strdef->get_schema_ver(),conversion,YES);
    inst_area.Fill(strdef->get_versioning(),conversion,YES);
    inst_area.Fill(strdef->get_net_length(),conversion,YES);
// ... insert new fields here
// must be at position DBStructDef_COUNT (after last field)
    if ( strdef->smcbidky )
      inst_area.Fill(strdef->smcbidky->scbsmcb->smcbname,ID_SIZE,conversion,YES);
    else
      inst_area.Fill((void*)"",0,conversion,YES);
  
    FillDBResource(strdef->get_resource());
  
    FillDBFieldDefList(strdef);
    if ( strdef->smcbstyp != ST_CODE )
      FillDBKeyDefList(strdef);
  }
  Terminate();

}

/******************************************************************************/
/**
\brief  FillDBStructDefExt - 




\param  dictptr - Dictionary handle
\param  strdef - Structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBStructDefExt"

void CSInstanceList :: FillDBStructDefExt (Dictionary *dictptr, DBStructDef *strdef )
{

  Reset();

  FillDBStructDef(dictptr,strdef);

  Terminate();

}

/******************************************************************************/
/**
\brief  FillDBValue - 




\param  eval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBValue"

void CSInstanceList :: FillDBValue (ENUM_Value *eval )
{
  CSInstanceList     inst_list(64,conversion,8096);
  inst_list.FillDBValueData(eval);
  inst_area.Fill(inst_list.get_inst_area().GetData(),
                 inst_list.get_inst_area().GetCurSize(),
                 conversion,YES); 


}

/******************************************************************************/
/**
\brief  FillDBValueData - 




\param  eval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBValueData"

void CSInstanceList :: FillDBValueData (ENUM_Value *eval )
{

  Reset();
  
  inst_area.Fill(eval->id,conversion,YES);
  inst_area.Fill(eval->code,conversion,YES);
  inst_area.Fill(eval->name,ID_SIZE,conversion,YES);
  inst_area.Fill(eval->type,conversion,YES);
  inst_area.Fill(eval->display_name,conversion,YES);
  inst_area.Fill(eval->title,conversion,YES);
  inst_area.Fill(eval->description,conversion,YES);

  Terminate();

}

/******************************************************************************/
/**
\brief  FillDBValueList - 




\param  dictptr - Dictionary handle
\param  vlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillDBValueList"

void CSInstanceList :: FillDBValueList (Dictionary *dictptr, ENUM_ValueList *vlist )
{
  int32              indx0 = 0;
  int32              pcount = 0;
  ENUM_Value        *eval;
BEGINSEQ
  if ( (pcount = vlist->GetCount()) < 0 )
    pcount = 0;
  inst_area.Fill(pcount,conversion,YES);
  inst_area.Fill(vlist->get_basetype(),ID_SIZE,conversion,YES);
  if ( !pcount )                                     LEAVESEQ
  
  while ( eval = vlist->GetEntry(indx0++) )
    FillDBValue(eval);

ENDSEQ

}

/******************************************************************************/
/**
\brief  GetCSMessage - 



\return cs_msg - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCSMessage"

CS_Message *CSInstanceList :: GetCSMessage ( )
{

  return( cs_message );


}

/******************************************************************************/
/**
\brief  GetCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 CSInstanceList :: GetCount ( )
{

  return(curcount);

}

/******************************************************************************/
/**
\brief  GetDBExtentData - 



\return fielddef - Internal field defintion

\param  cdictionary - 
\param  extdef - Internal extent definition
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBExtentData"

DBFieldDef *CSInstanceList :: GetDBExtentData (CDictionary *cdictionary, DBExtend *extdef, int32 &rindx0 )
{

  cdictionary->SetupDBFieldDef(extdef,rindx0);
  
  extdef->set_intersect((list+rindx0++)->GetUChar());
  extdef->set_union_set((list+rindx0++)->GetUChar());
  extdef->set_disjunct((list+rindx0++)->GetUChar());
  extdef->set_acctype((SDB_AT)(list+rindx0++)->GetLong(conversion));

  extdef->GetDBStruct(cdictionary);
  extdef->SetupInverse();
  
  if ( extdef->fmcbsmcb && extdef->fmcbsmcb->smcbstyp == ST_CODE &&
       !extdef->HasValues() )
    GetDBValueList(cdictionary,extdef,rindx0);

  return(extdef);
}

/******************************************************************************/
/**
\brief  GetDBFieldDefData - 



\return fielddef - Internal field defintion

\param  cdictionary - 
\param  fielddef - Internal field defintion
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBFieldDefData"

DBFieldDef *CSInstanceList :: GetDBFieldDefData (CDictionary *cdictionary, DBFieldDef *fielddef, int32 &rindx0 )
{
  void   *buffer;
  char    emptybuf[ID_SIZE];
BEGINSEQ
  fielddef->Initialize();
  fielddef->set_resource(new DBResource(cdictionary));
  
  if ( !GetCount() )                                 ERROR
  
  memcpy(fielddef->fmcbname,(buffer=(list+rindx0++)->GetBuffer()) ? buffer : emptybuf,ID_SIZE);
  memcpy(fielddef->fmcbtype,(buffer=(list+rindx0++)->GetBuffer()) ? buffer : emptybuf,ID_SIZE);
  fielddef->fmcbnsid    = (list+rindx0++)->GetULong(conversion);
  fielddef->fmcbsize    = (list+rindx0++)->GetULong(conversion);
  fielddef->fmcbdim     = (list+rindx0++)->GetULong(conversion);
//  fielddef->fmcbdim[0]  = (list+rindx0++)->GetULong(conversion);
//  fielddef->fmcbdim[1]  = (list+rindx0++)->GetULong(conversion);
//  fielddef->fmcbdim[2]  = (list+rindx0++)->GetULong(conversion);
//  fielddef->fmcbdim[3]  = (list+rindx0++)->GetULong(conversion);
//  fielddef->fmcbdim[4]  = (list+rindx0++)->GetULong(conversion);
  fielddef->fmcbprec    = (list+rindx0++)->GetShort(conversion);
  fielddef->fmcbrlev    = (list+rindx0++)->GetShort(conversion);
  fielddef->fmcbposn    = (list+rindx0++)->GetLong(conversion);
  fielddef->fmcbbyte    = (list+rindx0++)->GetULong(conversion);
//  fielddef->fmcbityp = (list+rindx0++)->GetShort(conversion);  // sonst wird kein Setup gemacht
  rindx0++;
  fielddef->fmcberr     = (list+rindx0++)->GetShort(conversion);
  fielddef->fmcbbstr    = (list+rindx0++)->GetUChar();
  fielddef->fmcbunicode = (list+rindx0++)->GetUChar();
  fielddef->fmcbvar     = (list+rindx0++)->GetUChar();
  fielddef->fmcbtrans   = (list+rindx0++)->GetUChar();
  fielddef->fmcbopt     = (list+rindx0++)->GetUChar();
  fielddef->fmcbempty   = (list+rindx0++)->GetUChar();
  
  fielddef->fmcbic        = (list+rindx0++)->GetUChar();
  fielddef->fmcbdesc      = (list+rindx0++)->GetUChar();
  fielddef->fmcbcnst      = (list+rindx0++)->GetUChar();
  fielddef->fmcbstat      = (list+rindx0++)->GetUChar();
  fielddef->fmcbvirt      = (list+rindx0++)->GetUChar();
  fielddef->fmcbinit      = (list+rindx0++)->GetUChar();
  fielddef->fmcballoc_opt = (list+rindx0++)->GetUChar();
  fielddef->fmcbsensi     = (list+rindx0++)->GetUChar();
  
  fielddef->set_offset_ext((list+rindx0++)->GetLong(conversion));
  fielddef->set_ext_length((list+rindx0++)->GetLong(conversion));
  
  fielddef->set_inverse_name((char *)(list+rindx0++)->GetBuffer());
  fielddef->set_cluster_opt((list+rindx0++)->GetUChar());
  fielddef->set_mb_number((list+rindx0++)->GetShort(conversion));
  fielddef->set_gen_type((char *)(list+rindx0++)->GetBuffer());
  fielddef->set_privilege((PIADEF)(list+rindx0++)->GetLong(conversion));
  fielddef->set_static_field((list+rindx0++)->GetUChar());
  fielddef->set_virtual((list+rindx0++)->GetUChar());
  fielddef->set_dominant((list+rindx0++)->GetUChar());
  fielddef->set_sec_reference((list+rindx0++)->GetUChar());
  fielddef->set_log_reference((list+rindx0++)->GetUChar());
  fielddef->set_version((list+rindx0++)->GetShort(conversion));
  fielddef->SetExtent((list+rindx0++)->GetString());
  fielddef->set_owning((list+rindx0++)->GetUChar());
  fielddef->set_create((list+rindx0++)->GetUChar());
  fielddef->set_weak_typed((list+rindx0++)->GetUChar());
  fielddef->set_depend((list+rindx0++)->GetUChar());
  fielddef->set_update((list+rindx0++)->GetUChar());
  fielddef->set_multikey((list+rindx0++)->GetUChar());
  fielddef->set_initval((char *)(list+rindx0++)->GetString(),UNDEF);
  
  fielddef->set_clst_table((list+rindx0++)->GetUChar());
  fielddef->set_is_base_coll((list+rindx0++)->GetChar());
  
  fielddef->set_net_pos((list+rindx0++)->GetLong(conversion));
  fielddef->set_net_length((list+rindx0++)->GetULong(conversion));

  fielddef->SetupType(cdictionary,YES);
  
  cdictionary->SetupDBResource(fielddef->get_resource(),rindx0);
  GetDBIndexList(cdictionary,fielddef,rindx0);

RECOVER
  fielddef = NULL;
ENDSEQ
  return(fielddef);
}

/******************************************************************************/
/**
\brief  GetDBFieldDefList - 



\return term - Termination code

\param  cdictionary - 
\param  strdef - Structure definition
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBFieldDefList"

logical CSInstanceList :: GetDBFieldDefList (CDictionary *cdictionary, DBStructDef *strdef, int32 &rindx0 )
{
  int32                   pcount;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  pcount = (list+rindx0++)->GetLong(conversion);  
  if ( !(strdef->smcbfmcl = new DBFieldList(pcount)) )  
                                                     SDBERR(95)                                                     
  while ( pcount-- )
    cdictionary->SetupDBFieldDef(strdef->GetEntry(++indx0),rindx0);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetDBIndexData - 



\return term - Termination code

\param  fielddef - Internal field defintion
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBIndexData"

logical CSInstanceList :: GetDBIndexData (DBFieldDef *fielddef, int32 &rindx0 )
{
  logical              term = NO;

BEGINSEQ
  if ( !GetCount() )                                 ERROR
  
  char     *keyname = (list+rindx0++)->GetString();
  logical   uniopt  = (list+rindx0++)->GetUChar();
  logical   tempopt = (list+rindx0++)->GetUChar();
  logical   caseopt = (list+rindx0++)->GetUChar();
  logical   empopt  = (list+rindx0++)->GetUChar();
  SDB_SET   settyp  = (SDB_SET)(list+rindx0++)->GetLong(conversion);
  
  fielddef->CreateIndex(keyname,uniopt,tempopt,caseopt,empopt,settyp);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetDBIndexList - 



\return term - Termination code

\param  cdictionary - 
\param  fielddef - Internal field defintion
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBIndexList"

logical CSInstanceList :: GetDBIndexList (CDictionary *cdictionary, DBFieldDef *fielddef, int32 &rindx0 )
{
  DBStructDef            *csstr;
  int32                   pcount;
  logical                 term = NO;
  pcount = (list+rindx0++)->GetLong(conversion);  
  
  while ( pcount-- )
    cdictionary->SetupDBIndex(fielddef,rindx0);

  return(term);
}

/******************************************************************************/
/**
\brief  GetDBKeyComponentData - 



\return term - Termination code

\param  kcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBKeyComponentData"

logical CSInstanceList :: GetDBKeyComponentData (kcb *kcbptr )
{
  char      *name;
  logical    ic;
  logical    desc;
  logical    term = NO;
BEGINSEQ
  if ( !GetCount() )                                 ERROR
  
  name = (list+0)->GetString();
  ic   = (list+1)->GetUChar();
  desc = (list+2)->GetUChar();

  kcbptr->kcbfad(name,ic,desc);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetDBKeyComponentList - 



\return term - Termination code

\param  cdictionary - 
\param  kcbptr - 
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBKeyComponentList"

logical CSInstanceList :: GetDBKeyComponentList (CDictionary *cdictionary, kcb *kcbptr, int32 &rindx0 )
{
  DBStructDef            *csstr;
  int32                   pcount;
  logical                 term = NO;
  pcount = (list+rindx0++)->GetLong(conversion);  
  kcbptr->Initialize(pcount);
  
  while ( pcount-- )
    cdictionary->SetupDBKeyComponent(kcbptr,rindx0);



  return(term);
}

/******************************************************************************/
/**
\brief  GetDBKeyDefData - 



\return kcbptr - 

\param  cdictionary - 
\param  strdef - Structure definition
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBKeyDefData"

kcb *CSInstanceList :: GetDBKeyDefData (CDictionary *cdictionary, DBStructDef *strdef, int32 &rindx0 )
{
  kcb    *kcbptr;
  char   *keyname;   
  int16   keynum;

BEGINSEQ
  if ( !GetCount() )                                 ERROR
  
  keyname = (char *)(list+rindx0++)->GetBuffer();
  keynum  = (list+rindx0++)->GetShort(conversion);
  
  kcbptr = strdef->ProvideKCB(keyname,keynum);
  GetDBKeyComponentList(cdictionary,kcbptr,rindx0);

RECOVER
  kcbptr = NULL;
ENDSEQ
  return(kcbptr);
}

/******************************************************************************/
/**
\brief  GetDBKeyDefList - 



\return term - Termination code

\param  cdictionary - 
\param  strdef - Structure definition
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBKeyDefList"

logical CSInstanceList :: GetDBKeyDefList (CDictionary *cdictionary, DBStructDef *strdef, int32 &rindx0 )
{
  DBStructDef            *csstr;
  int32                   pcount;
  logical                 term = NO;
  pcount = (list+rindx0++)->GetLong(conversion);  
  
  while ( pcount-- )
    cdictionary->SetupDBKeyDef(strdef,rindx0);



  return(term);
}

/******************************************************************************/
/**
\brief  GetDBResourceData - 



\return dbresource - 

\param  cdictionary - 
\param  dbresource - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBResourceData"

DBResource *CSInstanceList :: GetDBResourceData (CDictionary *cdictionary, DBResource *dbresource )
{
  int32   rindx0 = 0;
BEGINSEQ
  if ( !GetCount() )                                 ERROR
  
  dbresource->Initialize(NULL,(list+rindx0++)->GetLong(conversion));

RECOVER
  dbresource = NULL;
ENDSEQ
  return(dbresource);
}

/******************************************************************************/
/**
\brief  GetDBStructDefData - 



\return strdef - Structure definition

\param  cdictionary - 
\param  strdef - Structure definition
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBStructDefData"

DBStructDef *CSInstanceList :: GetDBStructDefData (CDictionary *cdictionary, DBStructDef *strdef, int32 &rindx0 )
{
  void          *buffer;   
  int32          int_pos;
  int32          ext_pos;
  int32          net_pos;
  char          *ikname;
BEGINSEQ
  if ( !GetCount() )                                 ERROR
  
  if ( buffer = (list+0)->GetBuffer() )
    memcpy(strdef->smcbname,buffer,ID_SIZE);
  strdef->smcbityp      = (list+1)->GetShort(conversion);
  strdef->smcbatyp      = (list+2)->GetShort(conversion);
  strdef->smcbstyp      = (list+3)->GetShort(conversion);
  strdef->defined_align = (char)(list+4)->GetShort(conversion);
  strdef->SetMemberInfo((list+6)->GetLong(conversion),(list+7)->GetLong(conversion),(list+8)->GetLong(conversion),(list+9)->GetLong(conversion));
  
  int_pos = (list+5)->GetLong(conversion);
  ext_pos = (list+10)->GetLong(conversion);
  net_pos = (list+13)->GetLong(conversion);
  strdef->SetLength(int_pos,ext_pos,net_pos);
  
  strdef->set_schema_vers((list+11)->GetUShort(conversion));

  strdef->set_resource(new DBResource(cdictionary));
  
  rindx0 = DBStructDef_COUNT;
  if ( cdictionary->SetupDBResource(strdef->get_resource(),rindx0) )
                                                     ERROR
  if ( GetDBFieldDefList(cdictionary,strdef,rindx0) )ERROR
  if ( strdef->smcbstyp != ST_CODE )
    GetDBKeyDefList(cdictionary,strdef,rindx0);
  
  if ( ikname = (char *)(list+DBStructDef_COUNT-1)->GetBuffer() )
    strdef->smcbidky = strdef->GetKCB(ikname);

  strdef->SetupClient(cdictionary);
  if ( strdef->smcbstyp == ST_CODE )  // muss nach dem SetupClient kommen!!
    cdictionary->ProvideExtendDef(strdef->smcbname);

RECOVER
  strdef = NULL;
ENDSEQ
  return(strdef);
}

/******************************************************************************/
/**
\brief  GetDBValueData - 



\return term - Termination code

\param  eval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBValueData"

logical CSInstanceList :: GetDBValueData (ENUM_Value *eval )
{
  char                   *string;
  logical                 term = NO;
BEGINSEQ
  if ( !GetCount() )                                 ERROR
  
  eval->id    = (list+0)->GetLOID(conversion);
  eval->code  = (list+1)->GetLong(conversion);
  if ( string = (char *)(list+2)->GetBuffer() )
    memcpy(eval->name,string,ID_SIZE);
  if ( string = (list+3)->GetString() )
    eval->type = strdup(string);
  if ( string = (list+4)->GetString() )
    eval->display_name = strdup(string);
  if ( string = (list+5)->GetString() )
    eval->title = strdup(string);
  if ( string = (list+6)->GetString() )
    eval->description = strdup(string);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetDBValueList - 



\return term - Termination code

\param  cdictionary - 
\param  extdef - Internal extent definition
\param  rindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBValueList"

logical CSInstanceList :: GetDBValueList (CDictionary *cdictionary, DBExtend *extdef, int32 &rindx0 )
{
  ENUM_Value              eval;
  ENUM_ValueList         *eval_list;
  char                    basetype[ID_SIZE];
  char                   *string;
  int32                   pcount;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  memset(basetype,0,ID_SIZE);
  pcount = (list+rindx0++)->GetLong(conversion);  
  if ( string = (char *)(list+rindx0++)->GetBuffer() )
    memcpy(basetype,string,ID_SIZE);
  
  if ( extdef->HasValues() )                         LEAVESEQ
    
  eval_list = new ENUM_ValueList(NULL,basetype,pcount);

  if ( extdef->fmcbsmcb->smcbacc &&
       extdef->fmcbsmcb->smcbacc != (DBStructDef *)extdef->fmcbsmcb ) // ruft sich beim aufbauen noch mal auf
                                                     LEAVESEQ         // wir haun ab, wenn wir schon fertig sind
  extdef->SetValueList(cdictionary,eval_list);
  while ( pcount-- )
  {
    if ( cdictionary->SetupDBValue(&eval,rindx0) )   ERROR
    eval_list->AddValue(&eval);
  }

RECOVER
  term = YES;
ENDSEQ
  eval.Clear();
  return(term);
}

/******************************************************************************/
/**
\brief  GetHandle - 



\return handle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHandle"

CS_Handle *CSInstanceList :: GetHandle ( )
{

  return(cs_message->GetHandle());

}

/******************************************************************************/
/**
\brief  Reset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void CSInstanceList :: Reset ( )
{

  curcount = 0;

  inst_area.SetCurSize(0);

}

/******************************************************************************/
/**
\brief  Resize - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Resize"

logical CSInstanceList :: Resize ( )
{
  CSInstance             *inst_list = list;
  int                     indx = 0;
  logical                 term = NO;
  list = new CSInstance[count+16];

  while ( indx < count )
  {
    list[indx] = inst_list[indx];
    indx++;
  }
  
  delete[] inst_list;
  count = count + 16;
  return(term);
}

/******************************************************************************/
/**
\brief  SetConversion - 




\param  convopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetConversion"

void CSInstanceList :: SetConversion (logical convopt )
{

  conversion = convopt;

}

/******************************************************************************/
/**
\brief  SetHandle - 




\param  handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHandle"

void CSInstanceList :: SetHandle (CS_Handle *handle )
{

  *cs_message->GetHandle() = handle ? *handle : CS_Handle();

}

/******************************************************************************/
/**
\brief  Setup - 




\param  cs_msg - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

void CSInstanceList :: Setup (CS_Message *cs_msg )
{
  CSInstHeader  *inst_hdr;
  int32           size;
  char          *curpos;
BEGINSEQ
  curcount = 0;
  if ( cs_msg )
    cs_message->Copy(cs_msg);
  
  inst_area.SetData(cs_message->GetData());
  size      = cs_message->GetLength();
  curpos    = cs_message->GetData();  
  
  curcount = 0;
  if ( !curpos )                                     LEAVESEQ
    
  while ( size > 0 )
  {
    if ( curcount >= count )
      Resize();
      
    inst_hdr = (CSInstHeader *)curpos;
    if ( conversion )
      inst_hdr->ConvertFromNet(*inst_hdr);
    curpos += sizeof(CSInstHeader);
    size   -= sizeof(CSInstHeader);
    list[curcount++].Initialize(*inst_hdr,curpos);
    curpos += inst_hdr->get_size();
    size   -= inst_hdr->get_size();
  }
  
  if ( size < 0 )                                    SDBERR(USHORTMAX) 

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Terminate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Terminate"

void CSInstanceList :: Terminate ( )
{

  cs_message->SetData((char *)inst_area.GetData());
  cs_message->SetLength(inst_area.get_cursize());

}

/******************************************************************************/
/**
\brief  operator[] - 



\return pInstance - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator[]"

CSInstance &CSInstanceList :: operator[] (int32 indx0 )
{
  CSInstance    *instptr = NULL;
  if ( indx0 < count )
    instptr = list+indx0;
  return(*instptr);
}

/******************************************************************************/
/**
\brief  ~CSInstanceList - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSInstanceList"

     CSInstanceList :: ~CSInstanceList ( )
{

  delete cs_message;
  cs_message = NULL;
  
  delete[] list;
  list = NULL;

}


