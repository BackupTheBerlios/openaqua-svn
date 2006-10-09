/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_Handle

\brief    


\date     $Date: 2006/03/12 19:19:44,93 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CS_Handle_HPP
#define   CS_Handle_HPP

class     CS_Handle;

#include  <sCS_Handle.hpp>
#pragma pack(8)

class  CS_Handle
{
protected  :         int64                                        server_object;                                             //
protected  :         int64                                        client_object;                                             //

public     :
                     int64                                        get_server_object() { return(server_object); }
                     int64                                        get_client_object() { return(client_object); }
public     :         SOS7ImpExp                                          CS_Handle ( );
public     :         SOS7ImpExp                  int64 GetClientObject ( );
public     :         SOS7ImpExp                  void *GetClientPointer ( );
public     :         SOS7ImpExp                  int64 GetServerObject ( );
public     :         SOS7ImpExp                  void *GetServerPointer ( );
public     :         SOS7ImpExp                  void SetClientObject (int64 client_obj );
public     :         SOS7ImpExp                  void SetClientPointer (void *client_ptr );
public     :         SOS7ImpExp                  void SetServerObject (int64 server_obj );
public     :         SOS7ImpExp                  void SetServerPointer (void *server_ptr );
public     :         SOS7ImpExp                  CS_Handle &operator= (const CS_Handle &handle_refc );
public     :         SOS7ImpExp                  logical operator== (CS_Handle &handle_ref );
};

#pragma pack()
#endif
