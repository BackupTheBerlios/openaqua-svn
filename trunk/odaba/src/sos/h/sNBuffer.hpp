/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    NBuffer

\brief    


\date     $Date: 2006/03/12 19:20:04,71 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   NBuffer_HPP
#define   NBuffer_HPP

class     NBuffer;

#include  <sNBase.hpp>
#include  <sNBuffer.hpp>
#pragma pack(8)

class  NBuffer :public NBase
{
protected  :         int32                                        cur_size ATTR_ALIGN(4);                                    
protected  :         int32                                        resize;                                                    

public     :
                     int32                                        get_cur_size() { return(cur_size); }
                     int32                                        get_resize() { return(resize); }
public     :         SOS7ImpExp                  char *AddBuffer (char *buffer, size_t len );
public     :         SOS7ImpExp                  logical Cut (size_t len );
public     :         SOS7ImpExp                  int32 GetCurrentSize ( );
public     :         SOS7ImpExp                                          NBuffer (int32 res_val=0 );
public     :         SOS7ImpExp                                          NBuffer (char *string, int32 res_val=0 );
public     :         SOS7ImpExp                                          NBuffer (char *buffer, size_t len, int32 res_val=0 );
public     :         SOS7ImpExp                                          NBuffer (NBuffer &nbuffer );
public     :         SOS7ImpExp                                          NBuffer (size_t len, int32 res_val=0 );
public     :         SOS7ImpExp                  char *SetBuffer (char *buffer, size_t len );
public     :         SOS7ImpExp                  logical operator+= (NBuffer &nbuffer );
public     :         SOS7ImpExp                  logical operator+= (char *string );
public     :         SOS7ImpExp                  char *operator= (NBuffer &nbuffer );
public     :         SOS7ImpExp                  char *operator= (char *string );
public     :         SOS7ImpExp                                          ~NBuffer ( );
};

#pragma pack()
#endif
