/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    disel

\brief    


\date     $Date: 2006/03/12 19:14:13,40 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   disel_HPP
#define   disel_HPP

class     disel;

class     ACNode;
class     ACObject;
class     DBStructDef;
class     mvld;
class     node;
class     ref;
#include  <sEB_Number.hpp>
#include  <sStructAccess.hpp>
#include  <sbinti.hpp>
#pragma pack(8)

class  disel :public binti
{
protected  :         ref                                         *refptr ATTR_ALIGN(4);                                      //
protected  :         char                                        *ext_inst;                                                  //
protected  :         StructAccess                                *struct_access;                                             //
protected  :         int16                                        mod_count;                                                 //

public     :
                     ref                                         *get_refptr() { return(refptr); }
                     char                                        *get_ext_inst() { return(ext_inst); }
public     : virtual                             logical Add (logical global_add=NO );
public     : virtual                             logical Delete (char *extname, logical is_root, int16 delopt=AUTO );
public     : virtual                             logical Get (EB_Number entnr );
public     : virtual                             EB_Number GetClusterNumber ( );
public     : virtual                             char *GetExtInst ( );
public     : virtual                             EB_Number GetID (int32 w_indx0=-1 );
public     : virtual                             int16 GetMBNumber ( );
public     : virtual                             int16 GetModCount ( );
public     :                                     ACObject *GetOBHandle ( );
public     : virtual                             char *GetOldInst (void *oldinst );
public     : virtual                             StructAccess *GetStructAccess ( );
public     : virtual                             logical IsPositioned ( );
public     : virtual                             logical Lock ( );
public     : virtual                             logical Reserve ( );
public     : virtual                             void Reset ( );
public     : virtual                             logical ResetWProtect ( );
public     : virtual                             logical Save (logical switchopt, logical overwrite=NO, logical refresh_opt=NO );
public     : virtual                             void SetStructAccess (StructAccess *structacc );
public     : virtual                             logical SetWProtect ( );
public     : virtual                             logical Unlock ( );
public     :                                                             disel (node *nodeptr, DBStructDef *strdefptr, void *instptr, ref *refptr, logical crt_opt );
public     :                                                             disel ( );
public     : virtual                                                     ~disel ( );
};

#pragma pack()
#endif
