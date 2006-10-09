/********************************* Class Declaration ***************************/
/**
\package  OPS - 
\class    ENUM_ValueList

\brief    


\date     $Date: 2006/06/04 13:21:03,92 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ENUM_ValueList_HPP
#define   ENUM_ValueList_HPP

class     ENUM_ValueList;

#define  CS_DSP                                    'D'
#define  CS_STR                                    'S'
#define  CS_TIT                                    't'
#define  CS_TYP                                    'T'
#define  CS_VAL                                    'V'
#include  <sGSRT.h>
class     ENUM_Value;
class     DBExtend;
class     DBStructDef;
class     ENUM_Value;
class     PropertyHandle;
#include  <sNString.hpp>
#include  <sacc.hpp>
class  ENUM_ValueList :public acc
{
protected  :         char                                         order;                                                     // 
protected  :         char                                         basetype[40];                                              // 
protected  :         GSRT(ENUM_Value)                            *value_list;                                                // 
protected  :         NString                                      result;                                                    // 

public     :
                     char                                         get_order() { return(order); }
                     char                                        *get_basetype() { return(basetype); }
                     GSRT(ENUM_Value)                            *get_value_list() { return(value_list); }
                     NString                                     &get_result() { return(result); }
public     : virtual                                char *Access (int32 lindx0, char *string, int32 maxlen );
public     : virtual                                char *Access (char *keyptr, int32 &int_ref );
public     :                  OPSImpExp             logical AddValue (PropertyHandle *val_ph );
public     :                  OPSImpExp             logical AddValue (int32 cval, char *cname, char *btype, char *clabel, char *ctitle, char *cdescr );
public     :                  OPSImpExp             logical AddValue (ENUM_Value *eval );
public     :                                        logical ChangeOrder (char sortopt );
public     :                                             ENUM_ValueList (PropertyHandle *val_ph );
public     :                                             ENUM_ValueList (ENUM_Value **enum_list, char *btype, int32 count );
public     :                                             ENUM_ValueList ( );
public     :                                        int32 GetCode (char *keyptr );
public     :                                        int32 GetCount ( );
public     :                                        int32 GetCurrentIndex (char *keyptr );
public     :                                        ENUM_Value *GetEntry (int32 lindx0 );
public     :                                        ENUM_Value *GetEntry (char *keyptr );
public     :                                        int32 GetKeyLength ( );
public     :                                        char *GetName (ENUM_Value *eval );
public     :                                        char *GetSortKey (ENUM_Value *eval, char sortopt );
public     :                                        int32 GetSortKeyLength ( );
public     :                                        char *GetString (int32 int_val, char *string, int32 maxlen );
public     :                                        logical HasValues ( );
public     :                                        logical InitValueList (int32 count );
public     :                                        logical Initialize (PropertyHandle *val_ph );
public     :                                        logical Initialize (ENUM_Value **enum_list, int32 count );
public     :                                        int32 LocateKey (char *keyptr, logical exact );
public     :                  OPSImpExp             int32 NextCode ( );
public     :                                        logical Resize (int32 count );
public     :                                             ~ENUM_ValueList ( );
};

#endif
