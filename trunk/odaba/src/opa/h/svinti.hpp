/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    vinti

\brief    


\date     $Date: 2006/03/12 19:15:11,48 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   vinti_HPP
#define   vinti_HPP

class     vinti;

class     ACElmView;
class     ACNode;
class     DBStructDef;
class     node;
#include  <sEB_Number.hpp>
#include  <sbinti.hpp>
#include  <sinti.hpp>
#pragma pack(8)

class  vinti :public sinti
{
protected  :         int32                                        cur_index ATTR_ALIGN(4);                                   //

public     :
                     int32                                        get_cur_index() { return(cur_index); }
public     :                                     logical Add (char *skey, logical global_add=NO );
public     : virtual                             logical Cancel ( );
public     :                                     logical Close ( );
public     :                                     logical ExtractKey (char *keyptr );
public     :                                     logical First ( );
public     :                                     logical Get ( );
public     : virtual                             int32 GetCount ( );
public     : virtual                             EB_Number GetID (int32 w_indx0=-1 );
public     :                                     ACNode *GetTopNode ( );
public     : virtual                             logical IsPositioned ( );
public     :                                     logical Last ( );
public     :                                     logical LocateKey (char *skey, logical exact=YES );
public     :                                     logical Modify ( );
public     :                                     logical Next (int32 indx0 );
public     :                                     logical Next (node *nodeptr );
public     :                                     logical Position (int32 indx0 );
public     :                                     logical Previous (int32 indx0 );
public     :                                     logical Previous (node *nodeptr );
public     : virtual                             logical ProvGenAttribute ( );
public     : virtual                             void Reset ( );
public     : virtual                             logical Save (logical switchopt, logical overwrite=NO, logical refresh_opt=NO );
public     :                                     logical Switch ( );
public     :                                                             vinti (ACOperation *op_node, DBStructDef *dbstrdef, void *instptr, logical crt_opt, OperEnvironment *operenv );
public     : virtual                                                     ~vinti ( );
};

#pragma pack()
#endif
