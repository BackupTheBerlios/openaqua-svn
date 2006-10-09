/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CodeSet

\brief    


\date     $Date: 2006/03/12 19:12:46,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CodeSet_HPP
#define   CodeSet_HPP

class     CodeSet;

#define  CS                                        CodeSet
#define  CS_U                                      -32767
class     DBHandle;
class     Dictionary;
class     cst;
#include  <cPIACC.h>
#include  <ssts.hpp>
#pragma pack(8)

class  CodeSet :public sts
{
protected  :         char                                         cxidnt[4] ATTR_ALIGN(4);                                   
protected  :         DBHandle                                    *cxsdbh;                                                    
protected  :         cst                                         *cxcst;                                                     
protected  :         char                                        *cxcse;                                                     
protected  :         char                                         cxacopt;                                                   
protected  :         int16                                        cxindx;                                                    

public     :
public     :         opa7ImpExp                  int16 Add (char *cstr, int16 cval, char *ctyp=NULL );
public     :         opa7ImpExp                  logical CheckCS ( );
public     :         opa7ImpExp                  logical CheckWProtect ( );
public     :         opa7ImpExp                  void Close ( );
public     :         opa7ImpExp                                          CodeSet (DBHandle *dbhandle, char *csnames, PIACC accopt );
public     :         opa7ImpExp                                          CodeSet (DatabaseHandle &dbhdl, char *csnames, PIACC accopt );
public     :         opa7ImpExp                                          CodeSet (DictionaryHandle &dict_hdl, char *csnames, PIACC accopt );
public     :         opa7ImpExp                                          CodeSet (Dictionary *dictionary, char *csnames, PIACC accopt );
public     :         opa7ImpExp                  logical Delete (char *cstr );
public     :         opa7ImpExp                  char *GetBaseType ( );
public     :         opa7ImpExp                  char *GetCodeString (int16 cval, char *w_cstr=NULL );
public     :         opa7ImpExp                  char *GetCodeString (char *ctyp=NULL, char *w_cstr=NULL );
public     :         opa7ImpExp                  int16 GetCodeValue (char *cstr );
public     :         opa7ImpExp                  int32 GetCount ( );
public     :         opa7ImpExp                  char *GetEnumType (int16 cval );
public     :         opa7ImpExp                  char *GetEnumType (char *cstr );
public     :         opa7ImpExp                  int8 GetStringLength ( );
public     :         opa7ImpExp                  logical Initialize (Dictionary *dictionary, char *csnames, PIACC accopt );
public     :         opa7ImpExp                  logical Lock ( );
public     :         opa7ImpExp                  logical ResetWProtect ( );
public     :         opa7ImpExp                  logical SetWProtect ( );
public     :         opa7ImpExp                  logical Unlock ( );
public     :         opa7ImpExp                  logical UpdateType (char *cstr, char *ctyp=NULL );
public     :         opa7ImpExp                  logical UpdateValue (char *cstr, int16 cval );
protected  :                                     logical cxchck (PIACC accopt );
public     :                                     char *cxegti (int32 indx0, int16 *cvalptr=NULL );
public     :         opa7ImpExp                  char *operator() (int32 indx0, int16 *cvalptr=NULL );
public     :         opa7ImpExp                                          ~CodeSet ( );
};

#pragma pack()
#endif
