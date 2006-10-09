/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    cst

\brief    


\date     $Date: 2006/03/12 19:14:08,62 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cst_HPP
#define   cst_HPP

class     cst;

#define  CS_STR                                    'S'
#define  CS_TYP                                    'T'
#define  CS_U                                      -32767
#define  CS_VAL                                    'V'
class     ACObject;
class     DBExtend;
class     DBFieldDef;
class     DBHandle;
class     DBStructDef;
class     LACObject;
class     RefAccess;
class     SDB_CSEntry;
class     StructAccess;
#include  <sEB_Number.hpp>
#include  <sacc.hpp>
#include  <smvl.hpp>
#pragma pack(8)

class  cst :public acc,
public mvl
{
protected  :         EB_Number                                    cstrex ATTR_ALIGN(4);                                      //
protected  :         char                                         cstcsort;                                                  //
protected  :         int16                                        cstval_pos;                                                //
protected  :         int16                                        cstval_len;                                                //
protected  :         char                                         cstval_typ;                                                //
protected  :         char                                         base_type[40];                                             //
protected  :         int16                                        id_size;                                                   //
protected  :         DBStructDef                                 *struct_def;                                                //
protected  :         ACObject                                    *object_handle;                                             //

public     :
                     int16                                        get_cstval_pos() { return(cstval_pos); }
                     int16                                        get_cstval_len() { return(cstval_len); }
                     char                                         get_cstval_typ() { return(cstval_typ); }
                     char                                        *get_base_type() { return(base_type); }
                     int16                                        get_id_size() { return(id_size); }
                     DBStructDef                                 *get_struct_def() { return(struct_def); }
                     ACObject                                    *get_object_handle() { return(object_handle); }
public     : virtual                             char *Access (int32 indx0 );
public     : virtual                             char *Access (char *keyval );
public     :                                     logical AddCSEntry (SDB_CSEntry *csentry, int32 lindx0 );
public     : virtual                             acc *GetAccess (int16 atyp=UNDF );
public     : virtual                             EB_Number GetID (int32 lindx0 );
public     :                                     logical HasValues ( );
public     :                                     logical InitValuelist (int32 count );
protected  : virtual                             logical Refresh ( );
public     : virtual                             logical Save ( );
public     :                                     logical SaveServer ( );
public     :                                     void SetHasValues ( );
public     :                                     void SetValue (char *enumerator_ptr, char *cstr );
public     :                                                             cst (DBExtend *extdef, ACObject *obhandle );
public     :                                                             cst (ACObject *obhandle, DBExtend *extdef );
public     :                                                             cst (LACObject *lobhandle, DBFieldDef *fielddef, RefAccess *refacc, int16 strlen, logical extopt );
public     :                                     logical cstadd (char *enumerator_ptr );
public     :                                     char *cstcsg (int16 cval );
public     :                                     char *cstcsgt (char *ctyp=NULL );
public     :                                     char *cstctg (int16 cval );
public     :                                     char *cstctg (char *cstr );
public     :                                     int16 cstcvg (char *cstr );
public     :                                     int16 cstcvg (int32 lindx0 );
public     :                                     int32 cstcvgt (char *ctyp=NULL );
protected  :                                     int16 cstcvng ( );
public     :                                     logical cstdel (char *cstr );
public     :                                     char *cstget (char *enumerator_ptr, int16 indx, char sortopt );
public     :                                     logical cstini (int16 ityp, logical extopt );
public     :                                     logical cstini (DBStructDef *dbstrdef, logical extopt );
public     :                                     int8 cstlengt ( );
public     :                                     logical cstsoch (char sortopt );
public     :                                     logical cstwptc ( );
public     :                                     logical cstwptr ( );
public     :                                     logical cstwpts ( );
public     : virtual                                                     ~cst ( );
};

#pragma pack()
#endif
