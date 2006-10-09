/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACView

\brief    


\date     $Date: 2006/03/12 19:12:18,50 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACView_HPP
#define   ACView_HPP

class     ACView;

#ifndef   DLL_PropAllocation_HPP
#define   DLL_PropAllocation_HPP
#include  <sPropAllocation.hpp>
#include  <sDLL.h>
#endif
class     ACObject;
class     DBExtend;
class     DBFieldList;
class     DBStructDef;
class     PropertyHandle;
class     bnode;
class     inti;
class     node;
#include  <cPIACC.h>
#include  <sACNode.hpp>
#include  <sDBViewDef.hpp>
#pragma pack(8)

class  ACView :public ACNode
{
protected  :         bnode                                       *view_base ATTR_ALIGN(4);                                   //
protected  :         DLL(PropAllocation)                          allocations;                                               //
protected  :         int32                                        last_view_index;                                           //
protected  :         int32                                        last_base_view_index;                                      //
protected  :         int32                                        last_index;                                                //
protected  :         logical                                      temp_struct;                                               //
protected  :         logical                                      has_references;                                            //
protected  :         logical                                      copy_node;                                                 //
protected  :         logical                                      owns_nodenode;                                             //

public     :
                     bnode                                       *get_view_base() { return(view_base); }
                     DLL(PropAllocation)                         &get_allocations() { return(allocations); }
                     int32                                        get_last_view_index() { return(last_view_index); }
                     int32                                        get_last_base_view_index() { return(last_base_view_index); }
                     int32                                        get_last_index() { return(last_index); }
                     logical                                      get_temp_struct() { return(temp_struct); }
                     logical                                      get_has_references() { return(has_references); }
                     logical                                      get_copy_node() { return(copy_node); }
                     logical                                      get_owns_nodenode() { return(owns_nodenode); }
public     :                                                             ACView (DBViewDef &view_def, PIACC access_mode=PI_Read );
public     :                                                             ACView ( );
public     :                                                             ACView (ACObject *obhandle, DBExtend *dbextdef, PIACC accmode=PI_undefined );
public     :                                                             ACView (node *nodeptr, DBExtend *dbextdef, PIACC accmode=PI_undefined );
public     : virtual                             void *Add (int32 lindx0, char *skey, char *idkey, void *initinst=NULL, logical global_add=NO );
public     : virtual                             logical Cancel (logical chknode=YES );
public     : virtual                             int16 ChangeBuffer (int16 bufnum=AUTO );
public     : virtual                             logical Close ( );
public     :                                     logical CreateExpressionBase (char *expression );
public     :                                     DBFieldList *CreateFields ( );
public     :                                     inti *CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes=YES );
public     :                                     logical CreateScopeNode (char *id_string );
public     :                                     DBStructDef *CreateStruct (char *strnames_w=NULL );
public     : virtual                             logical Execute ( );
public     : virtual                             char *FirstKey (logical chknode=YES );
public     : virtual                             void *Get (int32 indx0, logical chknode=YES );
public     : virtual                             void *Get (char *skey, logical chknode=YES );
public     :                                     int32 GetCount (logical chknode=YES );
public     :                                     logical GetData ( );
public     :                                     logical InitViewBase (DBViewDef &view_def, PIACC access_mode=PI_Read );
public     :                                     logical InitViewBase (PropertyHandle *view_ph, PIACC accmode=PI_undefined );
public     :                                     logical InitViewFilters (DBViewDef &view_def );
public     :                                     logical InitViewNode (ACObject *obhandle, PIACC access_mode=PI_Read );
public     :                                     logical InitViewOrders (DBViewDef &view_def );
public     :                                     logical InitViewOrders (PropertyHandle *view_ph );
public     :                                     logical InitViewParent (DBViewDef &view_def );
public     :                                     logical InitViewStructure (DBViewDef &view_def, PIACC access_mode=PI_Read );
public     :                                     logical InitViewStructure (PropertyHandle *view_ph, PIACC accmode=PI_undefined );
public     :                                     logical LocateKey (char *skey, logical exact=YES, logical chknode=YES );
public     :                                     void *Modify (logical chknode=YES );
public     :                                     char *NextKey (char *skey, int16 switch_level=0 );
public     :                                     logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     :                                     logical SetData ( );
public     :                                     logical SetOrder (char *strnames, int attrtype, char *attrstr );
public     :                                     logical SetPostCondition (char *expression );
public     :                                     logical SetPreCondition (char *expression );
public     : virtual                                                     ~ACView ( );
};

#pragma pack()
#endif
