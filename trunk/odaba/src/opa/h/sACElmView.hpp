/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    ACElmView

\brief    


\date     $Date: 2006/04/17 13:07:39,98 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACElmView_HPP
#define   ACElmView_HPP

class     ACElmView;

class     ACObject;
class     DBExtend;
class     DBFieldDef;
class     DBStructDef;
class     kcb;
class     node;
class     vinti;
#include  <cPIACC.h>
#include  <sACElmView.hpp>
#include  <sACNode.hpp>
#pragma pack(8)

class  ACElmView :public ACNode
{
protected  :         DBStructDef                                 *struct_def ATTR_ALIGN(4);                                  // 
protected  :         vinti                                       *nodevinti;                                                 // 
protected  :         logical                                      nodecur_is_valid;                                          // 
protected  :         DBFieldDef                                  *field_def;                                                 // 
protected  :         logical                                      temp_struct;                                               // 

public     :
                     DBStructDef                                 *get_struct_def() { return(struct_def); }
                     vinti                                       *get_nodevinti() { return(nodevinti); }
                     logical                                      get_nodecur_is_valid() { return(nodecur_is_valid); }
                     DBFieldDef                                  *get_field_def() { return(field_def); }
                     logical                                      get_temp_struct() { return(temp_struct); }
public     :                                                             ACElmView (ACObject *obhandle, DBExtend *extdef, PIACC accopt );
public     :                                                             ACElmView (ACElmView &elmview_ref );
public     :                                                             ACElmView (ACObject *obhandle, node *nodeptr, char *proppath, PIACC accopt, char *strnames_w=NULL );
public     : virtual                             void *Add (int32 lindx0, char *skey, char *idkey, void *initinst=NULL, logical global_add=NO );
public     : virtual                             logical Cancel (logical chknode=YES );
public     : virtual                             node *CreateCopyNode ( );
public     : virtual                             char *ExtractKey (char *keyptr, kcb *kcbptr, void *instptr );
public     : virtual                             char *FirstKey (logical chknode=YES );
public     : virtual                             void *Get (int32 indx0, logical chknode=YES );
public     : virtual                             void *Get (char *skey, logical chknode=YES );
public     : virtual                             int32 GetCount (logical chknode=YES );
public     : virtual                             logical LocateKey (char *skey, logical exact=YES, logical chknode=YES );
public     : virtual                             void *Modify (logical chknode=YES );
public     : virtual                             char *NextKey (char *skey, int16 switch_level=0 );
public     : virtual                             logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     : virtual                             logical SetOrder (char *strnames, int attrtype, char *attrstr );
public     : virtual                                                     ~ACElmView ( );
};

#pragma pack()
#endif
