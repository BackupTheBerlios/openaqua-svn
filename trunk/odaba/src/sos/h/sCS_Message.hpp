/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_Message

\brief    


\date     $Date: 2006/03/12 19:19:45,45 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CS_Message_HPP
#define   CS_Message_HPP

class     CS_Message;

#include  <sCS_Buffer.hpp>
#include  <sCS_Handle.hpp>
#pragma pack(8)

class  CS_Message
{
protected  :         int32                                        capacity;                                                  
protected  :         CS_Handle                                    conn_handle;                                               //
public     :         uint32                                       class_id;                                                  //
public     :         uint32                                       function_id;                                               //
public     :         int32                                        length;                                                    //
public     :         char                                        *data;                                                      //
protected  :         logical                                      owning_data;                                               
public     :         logical                                      flush;                                                     

public     :
                     int32                                        get_capacity() { return(capacity); }
                     CS_Handle                                   &get_conn_handle() { return(conn_handle); }
public     :         SOS7ImpExp                                          CS_Message ( );
public     :         SOS7ImpExp                  void Copy (CS_Message *cs_msg );
public     :         SOS7ImpExp                  void Flush ( );
public     :         SOS7ImpExp                  char *GetData ( );
public     :         SOS7ImpExp                  CS_Handle *GetHandle ( );
public     :         SOS7ImpExp                  int32 GetLength ( );
public     :         SOS7ImpExp                  logical Reset ( );
public     :         SOS7ImpExp                  void SetData (char *datarea );
public     :         SOS7ImpExp                  void SetLength (int32 inst_len );
public     :         SOS7ImpExp                                          ~CS_Message ( );
};

#pragma pack()
#endif
