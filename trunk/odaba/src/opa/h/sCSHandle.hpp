/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    CSHandle



\date     $Date: 2006/05/08 15:16:10,34 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSHandle_HPP
#define   CSHandle_HPP

class     CSHandle;

#define  HNDL_ID                                   1279544904
#define  HNDL_IDD                                  1279544864
#define  RET_BUF_LEN                               512
class     CS_Connection;
class     ClientConnection;
class     ServerConnection;
class     acb;
#include  <sCSA_Handle.hpp>
#include  <sCSInstanceList.hpp>
#pragma pack(8)

class  CSHandle :public CSA_Handle
{
protected  :         int32                                        ident;                                                     
protected  :         char                                        *return_buffer;                                             

public     :
                     int32                                        get_ident() { return(ident); }
                     char                                        *get_return_buffer() { return(return_buffer); }
public     :                                        ClientConnection *CConnection ( );
public     : virtual          OPAImpExp             void CSAClosed (char *parmstring );
public     :                                             CSHandle ( );
public     :                                             CSHandle (CS_Connection *cs_connection );
public     :                                        logical GenerateEvent (CSA_Events event_id, int64 identity, logical is_instance );
public     :                                        ODABAClient &GetClient ( );
public     :                                        CSInstanceList &Get_rec_result ( );
public     :                                        CSInstanceList &Get_send_parms ( );
public     :                                        logical InitHandle (logical alloc_buffer=YES );
public     :                                        logical IsConnected ( );
public     :                                        CSInstanceList &LockSendParms ( );
public     :                                        ServerConnection *SConnection ( );
public     :                                        void UninitHandle ( );
public     :                                        logical UnlockSendParms ( );
public     :                                        logical ValidHandle ( );
public     :                                             ~CSHandle ( );
};

#pragma pack()
#endif
