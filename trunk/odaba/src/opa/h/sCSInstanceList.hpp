/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    CSInstanceList



\date     $Date: 2006/04/26 21:18:22,01 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSInstanceList_HPP
#define   CSInstanceList_HPP

class     CSInstanceList;

#define  DBStructDef_COUNT                         15
class     CDictionary;
class     CS_Handle;
class     CS_Message;
class     DBExtend;
class     DBFieldDef;
class     DBIndex;
class     DBResource;
class     DBStructDef;
class     Dictionary;
class     ParmList;
class     StructDef;
class     kcb;
class     kfc;
class     smcb;
#include  <sCSInstance.hpp>
#include  <sInstance.hpp>
#include  <sdttm.hpp>
#pragma pack(8)

class  CSInstanceList
{
protected  :         CSInstance                                  *list;                                                      
protected  :         int32                                        count;                                                     
protected  :         int32                                        curcount;                                                  
protected  :         logical                                      conversion;                                                
protected  :         CSInstance                                   inst_area;                                                 
protected  :         CS_Message                                  *cs_message;                                                

public     :
                     CSInstance                                  *get_list() { return(list); }
                     int32                                        get_count() { return(count); }
                     int32                                        get_curcount() { return(curcount); }
                     logical                                      get_conversion() { return(conversion); }
                     CSInstance                                  &get_inst_area() { return(inst_area); }
                     CS_Message                                  *get_cs_message() { return(cs_message); }
public     :         OPAImpExp                                           CSInstanceList (int16 maxcount, logical convopt, int32 mess_len );
public     :         OPAImpExp                   void Fill ( );
public     :         OPAImpExp                   void Fill (void *buffer, uint16 len );
public     :         OPAImpExp                   void Fill (void *buffer, uint16 len, int16 short_val );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, char *string, int32 long_val, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, int32 long_val, uint16 ushort_val );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, int32 long_val, int32 long_val1, uint16 ushort_val );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, Key key_inst, smcb *keysmcb, int32 long_val, int32 long_val1, int32 long_val2 );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, char *string, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, char *string, int32 long_val, uint8 uchar_val1, uint16 ushort_val, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, CS_Handle *handle1 );
public     :         OPAImpExp                   void Fill (CS_Handle *handle );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, char *string, int32 long_val, uint16 ushort_val );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, int32 long_val );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, int32 long_val1, int32 long_val2 );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, char *string );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, Key key_inst, smcb *keysmcb, int32 long_val1 );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, char *string, int32 long_val );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, CS_Handle *handle1, uint8 uchar_val, int32 long_val, uint8 uchar_val1 );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, uint8 uchar_val, int32 long_val1, int32 long_val2 );
public     :         OPAImpExp                   void Fill (Instance insthandle, DBStructDef *strdef, int32 instlen );
public     :         OPAImpExp                   void Fill (Instance insthandle, DBFieldDef *field_def, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (Instance insthandle, DBStructDef *strdef, int32 instlen, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (Key key_inst, smcb *keysmcb );
public     :         OPAImpExp                   void Fill (Key key_inst, smcb *keysmcb, int16 short_val );
public     :         OPAImpExp                   void Fill (Key key_inst, smcb *keysmcb, int32 long_val );
public     :         OPAImpExp                   void Fill (Key key_inst, smcb *keysmcb, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (int32 long_val );
public     :         OPAImpExp                   void Fill (int32 long_val, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (int32 long_val, char *string );
public     :         OPAImpExp                   void Fill (int32 long_val, Key sort_key_inst, smcb *skey_smcb, Key key_inst, smcb *idkey_smcb, Instance insthandle, DBStructDef *strdef, int32 instlen, logical is_iselarea, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (int32 long_val1, int32 long_val2 );
public     :         OPAImpExp                   void Fill (int32 long_val, char *string1, char *string2, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (int32 long_val1, int32 long_val2, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (int32 long_val, uint8 uchar_val1, logical uchar_val2 );
public     :         OPAImpExp                   void Fill (uint8 uchar_val );
public     :         OPAImpExp                   void Fill (uint8 uchar_val, int32 long_val );
public     :         OPAImpExp                   void Fill (uint8 uchar_val, int16 short_val );
public     :         OPAImpExp                   void Fill (logical error_case, Instance insthandle, DBStructDef *strdef, int32 instlen );
public     :         OPAImpExp                   void Fill (logical error_case, Instance insthandle, DBStructDef *strdef, int32 instlen, int32 objid, int32 indx0, int32 rel_indx0, uint8 uchar_val, smcb *skey_smcb, logical new_instance, logical inst_inserted, logical parent_changed, uint16 version_nr=CUR_VERSION, logical is_init_instance=NO );
public     :         OPAImpExp                   void Fill (logical error_case, Key key_inst, smcb *keysmcb, int32 objid, int32 indx0 );
public     :         OPAImpExp                   void Fill (logical error_case, DBFieldDef *fielddef, smcb *keysmcb );
public     :         OPAImpExp                   void Fill (logical error_case, char *string );
public     :         OPAImpExp                   void Fill (int16 short_val );
public     :         OPAImpExp                   void Fill (int16 short_val1, int16 short_val2, int16 short_val3, char *string, int32 long_val );
public     :         OPAImpExp                   void Fill (int16 short_val1, char *string, int16 short_val2, int16 short_val3, int32 long_val, uint8 uchar_val, uint8 uchar_val1 );
public     :         OPAImpExp                   void Fill (int16 short_val1, int16 short_val2, char *string, int32 long_val );
public     :         OPAImpExp                   void Fill (int16 short_val, logical error_case );
public     :         OPAImpExp                   void Fill (int16 short_val, char *string, int32 long_val );
public     :         OPAImpExp                   void Fill (char *string );
public     :         OPAImpExp                   void Fill (char *string1, char *string2, char *string3, char *string4, uint8 uchar_val1, logical uchar_val2 );
public     :         OPAImpExp                   void Fill (char *string, int32 long_val, uint8 uchar_val, uint16 ushort_val, uint8 uchar_val1 );
public     :         OPAImpExp                   void Fill (char *string1, int32 long_val, char *string2 );
public     :         OPAImpExp                   void Fill (char *string1, char *string2 );
public     :         OPAImpExp                   void Fill (char *string, uint16 ushort_val );
public     :         OPAImpExp                   void Fill (char *string, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (char *string, uint16 ushort_val, int32 long_val );
public     :         OPAImpExp                   void Fill (char *string1, char *string2, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (char *string1, int32 long_val, char *string2, char *string3, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (char *string1, char *string2, uint8 uchar_val, char *string3 );
public     :         OPAImpExp                   void Fill (char *string, int32 long_val );
public     :         OPAImpExp                   void Fill (char *string1, int32 long_val, char *string2, char *string3 );
public     :         OPAImpExp                   void Fill (char *string1, char *string2, char *string3, int16 short_val, int32 long_val );
public     :         OPAImpExp                   void Fill (dttm timestamp1 );
public     :         OPAImpExp                   void Fill (dttm timestamp1, dttm timestamp2 );
public     :         OPAImpExp                   void Fill (dttm timestamp1, uint16 ushort_val );
public     :         OPAImpExp                   void Fill (uint16 ushort_val );
public     :         OPAImpExp                   void Fill (uint16 ushort_val, dttm timestamp_val );
public     :         OPAImpExp                   void Fill (uint16 ushort_val, uint8 uchar_val );
public     :         OPAImpExp                   void Fill (CS_Handle *handle, ParmList *parameters );
public     :         OPAImpExp                   void Fill (char *string, ParmList *parameters );
public     :                                     void FillDBExtent (Dictionary *dictptr, DBExtend *extdef );
public     :                                     void FillDBExtentData (Dictionary *dictptr, DBExtend *extdef );
public     :                                     void FillDBExtentExt (Dictionary *dictptr, DBExtend *extdef );
public     :                                     void FillDBFieldDef (DBFieldDef *fielddef );
public     :                                     void FillDBFieldDefData (DBFieldDef *fielddef );
public     :                                     void FillDBFieldDefList (DBStructDef *strdef );
public     :                                     void FillDBIndex (DBIndex *dbindex );
public     :                                     void FillDBIndexData (DBIndex *dbindex );
public     :                                     void FillDBIndexList (DBFieldDef *fielddef );
public     :                                     void FillDBKeyComponent (kfc *kfcptr );
public     :                                     void FillDBKeyComponentData (kfc *kfcptr );
public     :                                     void FillDBKeyComponentList (kcb *kcbptr );
public     :                                     void FillDBKeyDef (kcb *kcbptr );
public     :                                     void FillDBKeyDefData (kcb *kcbptr );
public     :                                     void FillDBKeyDefList (DBStructDef *strdef );
public     :                                     void FillDBResource (DBResource *dbresource );
public     :                                     void FillDBResourceData (DBResource *dbresource );
public     :                                     void FillDBStructDef (Dictionary *dictptr, DBStructDef *strdef );
public     :                                     void FillDBStructDefData (Dictionary *dictptr, DBStructDef *strdef );
public     :                                     void FillDBStructDefExt (Dictionary *dictptr, DBStructDef *strdef );
public     :                                     void FillDBValue (ENUM_Value *eval );
public     :                                     void FillDBValueData (ENUM_Value *eval );
public     :                                     void FillDBValueList (Dictionary *dictptr, ENUM_ValueList *vlist );
public     :                                     CS_Message *GetCSMessage ( );
public     :         OPAImpExp                   int32 GetCount ( );
public     :                                     DBFieldDef *GetDBExtentData (CDictionary *cdictionary, DBExtend *extdef, int32 &rindx0 );
public     :                                     DBFieldDef *GetDBFieldDefData (CDictionary *cdictionary, DBFieldDef *fielddef, int32 &rindx0 );
public     :                                     logical GetDBFieldDefList (CDictionary *cdictionary, DBStructDef *strdef, int32 &rindx0 );
public     :                                     logical GetDBIndexData (DBFieldDef *fielddef, int32 &rindx0 );
public     :                                     logical GetDBIndexList (CDictionary *cdictionary, DBFieldDef *fielddef, int32 &rindx0 );
public     :                                     logical GetDBKeyComponentData (kcb *kcbptr );
public     :                                     logical GetDBKeyComponentList (CDictionary *cdictionary, kcb *kcbptr, int32 &rindx0 );
public     :                                     kcb *GetDBKeyDefData (CDictionary *cdictionary, DBStructDef *strdef, int32 &rindx0 );
public     :                                     logical GetDBKeyDefList (CDictionary *cdictionary, DBStructDef *strdef, int32 &rindx0 );
public     :                                     DBResource *GetDBResourceData (CDictionary *cdictionary, DBResource *dbresource );
public     :                                     DBStructDef *GetDBStructDefData (CDictionary *cdictionary, DBStructDef *strdef, int32 &rindx0 );
public     :                                     logical GetDBValueData (ENUM_Value *eval );
public     :                                     logical GetDBValueList (CDictionary *cdictionary, DBExtend *extdef, int32 &rindx0 );
public     :         OPAImpExp                   CS_Handle *GetHandle ( );
public     :                                     void Reset ( );
public     :                                     logical Resize ( );
public     :                                     void SetConversion (logical convopt );
public     :                                     void SetHandle (CS_Handle *handle );
public     :                                     void Setup (CS_Message *cs_msg );
public     :                                     void Terminate ( );
public     :                                     CSInstance &operator[] (int32 indx0 );
public     :         OPAImpExp                                           ~CSInstanceList ( );
};

#pragma pack()
#endif
