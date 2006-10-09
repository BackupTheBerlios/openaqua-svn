/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    inti

\brief    


\date     $Date: 2006/08/30 16:46:50,75 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   inti_HPP
#define   inti_HPP

class     inti;

class     ACObject;
class     CTX_Property;
class     CTX_Structure;
class     DBFieldDef;
class     DBStructDef;
class     guid;
class     inti;
class     node;
#include  <cDB_Event.h>
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <sEB_Number.hpp>
#include  <snodelist.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  inti :public sts
{
protected  :         char                                        *iselarea;                                                  // 
protected  :         logical                                      iselifo;                                                   // 
protected  :         DBFieldDef                                  *field_def;                                                 // 
protected  :         DBStructDef                                 *struct_def;                                                // 
protected  :         nodelist                                     node_attr;                                                 // 
protected  :         int32                                        inst_index;                                                // 

public     :
                     char                                        *get_iselarea() { return(iselarea); }
                     logical                                      get_iselifo() { return(iselifo); }
                     DBFieldDef                                  *get_field_def() { return(field_def); }
                     DBStructDef                                 *get_struct_def() { return(struct_def); }
                     nodelist                                    &get_node_attr() { return(node_attr); }
                     int32                                        get_inst_index() { return(inst_index); }
public     : virtual          OPAImpExp             logical Add (logical global_add=NO );
public     :                  OPAImpExp             char *AllocateArea ( );
public     :                                        guid *BuildGUID (guid *_guid );
public     : virtual          OPAImpExp             logical Cancel ( );
public     : virtual          OPAImpExp             logical ChangeMode (PIACC accopt );
public     : virtual          OPAImpExp             uint8 CheckWProtect ( );
public     : virtual          OPAImpExp             logical Close ( );
public     : virtual          OPAImpExp             int16 Copy (inti *srceinti, node *nodeptr, PIREPL db_replace=REPL_none, PIREPL copy_type=REPL_all );
public     : virtual          OPAImpExp             logical CopyBufferInstance (inti *intiptr );
public     : virtual          OPAImpExp             logical CreateGUID (guid *_guid );
public     : virtual          OPAImpExp             logical Delete (char *extname, logical is_root, int16 delopt=AUTO );
public     : virtual          OPAImpExp             logical DeleteInstance ( );
public     : virtual          OPAImpExp             void DeleteSubNodes ( );
public     : virtual          OPAImpExp             logical Get (EB_Number entnr );
public     : virtual          OPAImpExp             logical Get (char *extinst );
public     : virtual          OPAImpExp             CTX_Structure *GetContext ( );
public     : virtual          OPAImpExp             int32 GetCount ( );
public     :                  OPAImpExp             guid *GetGUID (char chkopt=AUTO );
public     : virtual          OPAImpExp             EB_Number GetID (int32 w_indx0=-1 );
public     : virtual          OPAImpExp             EB_Number *GetIdentity ( );
public     : virtual          OPAImpExp             int32 GetIndex (EB_Number entnr );
public     :                  OPAImpExp             uint32 GetInstLength ( );
public     : virtual          OPAImpExp             int16 GetModCount ( );
public     : virtual          OPAImpExp             ACObject *GetOBHandle ( );
public     : virtual          OPAImpExp             node *GetPropNode (char *prop_names, CTX_Property *highprop_ctx );
public     : virtual          OPAImpExp             node *GetPropNode (char *prop_names, char *proppath );
public     : virtual          OPAImpExp             node **GetPropNodePtr (char *prop_names, CTX_Property *highprop_ctx );
public     : virtual          OPAImpExp             node **GetPropNodePtr (char *prop_names, char *proppath );
public     : virtual          OPAImpExp             int16 GetSID (EB_Number entnr );
public     :                  OPAImpExp             uint32 GetSize ( );
public     : virtual          OPAImpExp             node *GetSubNode (char *prop_names, CTX_Property *highprop_ctx );
public     : virtual          OPAImpExp             node **GetSubNodePtr (char *prop_names, CTX_Property *highprop_ctx );
public     : virtual          OPAImpExp             uint16 GetVersion ( );
public     :                  OPAImpExp             logical InitArea (void *instptr );
public     : virtual          OPAImpExp             logical Initialize (void *initinst=NULL, logical set_init=YES );
public     :                                        logical IsModified ( );
public     : virtual          OPAImpExp             logical IsNewInstance ( );
public     : virtual          OPAImpExp             logical IsPositioned ( );
public     :                                        logical IsReadOnly ( );
public     : virtual          OPAImpExp             logical IsSelected ( );
public     : virtual          OPAImpExp             logical LocateKey (char *skey, logical exact=YES );
public     : virtual          OPAImpExp             logical Lock ( );
public     : virtual          OPAImpExp             logical Modify ( );
public     : virtual          OPAImpExp             logical MoveInstance (inti *intiptr );
public     : virtual          OPAImpExp             logical Position (int32 count );
public     :                                        node **ProvideAttrNode (node *parent, char *prop_names, DBFieldDef *dbfield_def, int32 offset, CTX_Property *highprop_ctx );
public     : virtual          OPAImpExp             void Release ( );
public     :                  OPAImpExp             void ReleaseArea ( );
public     : virtual          OPAImpExp             logical RemoveGUID ( );
public     : virtual          OPAImpExp             logical Reserve ( );
public     : virtual          OPAImpExp             void Reset ( );
public     :                                        void ResetGUID ( );
public     : virtual          OPAImpExp             void ResetInitialized ( );
public     : virtual          OPAImpExp             logical ResetInstance ( );
public     : virtual          OPAImpExp             logical ResetNodes ( );
public     : virtual          OPAImpExp             logical ResetWProtect ( );
public     : virtual          OPAImpExp             logical Save (logical switchopt, logical overwrite=NO, logical refresh_opt=NO );
public     : virtual          OPAImpExp             logical SetInWork (logical workopt );
public     : virtual          OPAImpExp             void SetObjectID (int64 obj_id );
public     :                  OPAImpExp             void SetPI (node *nodeptr, void *instptr );
public     : virtual          OPAImpExp             logical SetRefContext (inti *intiptr );
public     : virtual          OPAImpExp             void SetVersion (uint16 version_nr=CUR_VERSION );
public     : virtual          OPAImpExp             logical SetWProtect ( );
public     : virtual          OPAImpExp             void Setup ( );
public     : virtual          OPAImpExp             void Setup (EB_Number clnumb, int16 mbnumber );
public     :                  OPAImpExp             logical StructAttrEvents (DB_Event intevent );
public     : virtual          OPAImpExp             logical StructureEvents (DB_Event intevent );
public     : virtual          OPAImpExp             logical Unlock ( );
public     :                  OPAImpExp                  inti (node *node_ptr, DBStructDef *strdefptr, void *instptr, logical crt_opt );
public     :                  OPAImpExp                  inti ( );
public     :                  OPAImpExp             void set_inst_index (int32 lindx0 );
public     :                                        void set_iselarea (void *instptr );
public     : virtual          OPAImpExp                  ~inti ( );
};

#pragma pack()
#endif
