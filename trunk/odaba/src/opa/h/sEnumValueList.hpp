/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    EnumValueList



\date     $Date: 2006/04/09 15:56:26,53 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EnumValueList_HPP
#define   EnumValueList_HPP

class     EnumValueList;

#define  CS_STR                                    'S'
#define  CS_TYP                                    'T'
#define  CS_U                                      -32767
#define  CS_VAL                                    'V'
#include  <sGSRT.h>
class     EnumValue;
class     ACObject;
class     DBExtend;
class     DBFieldDef;
class     DBHandle;
class     DBStructDef;
class     EnumValue;
class     LACObject;
class     PropertyHandle;
class     RefAccess;
class     SDB_CSEntry;
class     StructAccess;
#include  <sEB_Number.hpp>
#include  <sacc.hpp>
#include  <scst.hpp>
#include  <smvl.hpp>
#pragma pack(8)

class  EnumValueList :public acc
{
protected  :         char                                         order ATTR_ALIGN(4);                                       
protected  :         char                                         basetype[40];                                              
protected  :         DBStructDef                                 *struct_def;                                                
protected  :         GSRT(EnumValue)                             *value_list;                                                
protected  :         ACObject                                    *object_handle;                                             
protected  :         DBExtend                                    *extent_def;                                                

public     :
                     char                                        *get_basetype() { return(basetype); }
                     DBStructDef                                 *get_struct_def() { return(struct_def); }
                     GSRT(EnumValue)                             *get_value_list() { return(value_list); }
                     ACObject                                    *get_object_handle() { return(object_handle); }
                     DBExtend                                    *get_extent_def() { return(extent_def); }
public     : virtual                             char *Access (int32 indx0 );
public     : virtual                             char *Access (char *keyval );
public     :                                     logical AddValue (int32 cval, char *cstring, char *btype );
public     :                                     logical AddValue (PropertyHandle *val_ph );
public     :                                     logical ChangeOrder (char sortopt );
public     :                                     void Clear ( );
public     :                                                             EnumValueList (DBExtend *extdef, ACObject *obhandle );
public     :                                                             EnumValueList (ACObject *obhandle, DBExtend *extdef );
public     :                                                             EnumValueList (cst &cst_ref );
public     :                                                             EnumValueList (LACObject *lobhandle, DBFieldDef *fielddef, RefAccess *refacc, int16 strlen, logical extopt );
public     :                                     logical FillValueList (PropertyHandle *vl_ph );
public     : virtual                             acc *GetAccess (int16 atyp=UNDF );
public     :                                     EnumValue *GetEntry (char *cstring );
public     :                                     EnumValue *GetEntry (int32 lindx0 );
public     : virtual                             EB_Number GetID (int32 lindx0 );
public     :                                     char *GetName (char *cstring );
public     :                                     char *GetName (int32 lindx0 );
public     :                                     int32 GetValue (char *cstring );
public     :                                     int32 GetValue (int32 lindx0 );
public     :                                     logical HasValues ( );
public     :                                     logical InitValuelist (int32 count );
public     :                                     logical Initialize ( );
public     : virtual                             logical Refresh ( );
public     :                                     void Resize (int32 count );
public     : virtual                             logical Save ( );
public     :                                     logical SaveServer ( );
public     :                                     void SetHasValues ( );
public     :                                     void SetValue (char *enumerator_ptr, char *cstr );
public     :                                     logical cstadd (char *enumerator_ptr );
public     :                                     char *cstcsg (int32 cval );
public     :                                     char *cstcsgt (char *ctyp=NULL );
public     :                                     char *cstctg (int32 cval );
public     :                                     char *cstctg (char *cstr );
public     :                                     int32 cstcvgt (char *ctyp=NULL );
public     :                                     int16 cstcvng ( );
public     :                                     logical cstdel (char *cstr );
public     :                                     char *cstget (char *enumerator_ptr, int16 indx, char sortopt );
public     :                                     int8 cstlengt ( );
public     :                                     logical cstwptc ( );
public     :                                     logical cstwptr ( );
public     :                                     logical cstwpts ( );
public     : virtual                                                     ~EnumValueList ( );
};

#pragma pack()
#endif
