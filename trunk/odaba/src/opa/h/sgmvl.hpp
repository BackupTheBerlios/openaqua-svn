/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    gmvl

\brief    


\date     $Date: 2006/03/12 19:14:24,20 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   gmvl_HPP
#define   gmvl_HPP

class     gmvl;

#ifndef   DPA_ref_HPP
#define   DPA_ref_HPP
#include  <sref.hpp>
#include  <sDPA.h>
#endif
class     DBIndex;
class     LACObject;
class     binti;
class     inti;
class     kcb;
class     ref;
#include  <sEB_Number.hpp>
#include  <smvli.hpp>
#pragma pack(8)

class  gmvl :public mvli
{
protected  :         DPA(ref)                                     ref_list ATTR_ALIGN(4);                                    
protected  :         DBIndex                                     *index_def;                                                 
protected  :         kcb                                         *code_kcb;                                                  
protected  :         int                                          attr_type;                                                 

public     :
                     DPA(ref)                                    &get_ref_list() { return(ref_list); }
                     DBIndex                                     *get_index_def() { return(index_def); }
                     kcb                                         *get_code_kcb() { return(code_kcb); }
                     int                                         &get_attr_type() { return(attr_type); }
public     : virtual                             logical AddID (inti *intiptr, EB_Number entnr, int32 lindx0 );
public     :                                     logical CheckID (void *instptr, void *oldinst, EB_Number entnr );
public     : virtual                             char *CheckMod (void *instptr, void *oldinst, char *key_area );
public     : virtual                             logical CheckNewID (void *instptr, EB_Number entnr );
public     :                                     logical CreateReference (int attrtype );
public     : virtual                             logical DeleteID (inti *intiptr, void *oldinst, EB_Number entnr );
public     : virtual                             logical DeleteID (EB_Number entnr );
public     : virtual                             void DeleteReference ( );
public     :                                     int16 GetAttributeType (ref *refptr );
public     : virtual                             char *GetGenAttribute ( );
public     :                                     ref *GetReference (int attrtype, logical provide );
public     : virtual                             logical Refresh ( );
public     : virtual                             logical Reset ( );
public     : virtual                             logical Save ( );
public     :                                     ref *SetAttributeType (void *instptr, logical provide );
public     : virtual                             void SetVersion (uint16 version_nr=CUR_VERSION );
public     : virtual                             logical Setup (EB_Number *extref, EB_Number clnumb, int16 w_mbnumber=0 );
public     :                                     logical SetupReferences ( );
public     : virtual                             logical UpdateID (inti *intiptr, void *oldinst, EB_Number entnr );
public     :                                                             gmvl (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind );
public     : virtual                                                     ~gmvl ( );
};

#pragma pack()
#endif
