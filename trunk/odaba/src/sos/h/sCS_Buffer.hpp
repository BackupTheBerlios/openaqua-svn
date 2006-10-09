/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CS_Buffer

\brief    


\date     $Date: 2006/03/12 19:19:40,76 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CS_Buffer_HPP
#define   CS_Buffer_HPP

class     CS_Buffer;

#include  <svcls.hpp>
#include  <swinsock.hpp>
#pragma pack(8)

class  CS_Buffer :public vcls
{
protected  :         size_t                                       threshold ATTR_ALIGN(4);                                   //
protected  :         size_t                                       size;                                                      
protected  :         char                                        *buf;                                                       
protected  :         size_t                                       wpos;                                                      
protected  :         size_t                                       rpos;                                                      
protected  :         size_t                                       capacity;                                                  

public     :
                     char                                        *get_buf() { return(buf); }
public     :                                     void AddBuf (void *buf, size_t valSize_t );
public     :                                     void AddINT64 (int64 val64 );
public     :                                     void AddReserve (size_t valSize_t );
public     :                                     void AddULONG (uint32 val );
public     :         SOS7ImpExp                                          CS_Buffer (size_t threshold );
public     :         SOS7ImpExp                                          CS_Buffer ( );
public     :         SOS7ImpExp                  void Clear (logical forcefree=NO );
public     :                                     char *GetBPtr ( );
public     :                                     void *GetBuf (void *buf, size_t len );
public     :                                     int64 GetINT64 ( );
public     :                                     size_t GetRLeft ( );
public     :                                     size_t GetRPos ( );
public     :                                     char *GetRPtr ( );
public     :                                     size_t GetSize ( );
public     :                                     uint32 GetULONG ( );
public     :                                     size_t GetWPos ( );
public     :                                     char *GetWPtr ( );
public     :         SOS7ImpExp                  void Grow (size_t minsize );
public     :                                     logical HasRData ( );
public     :                                     void SetRPos (size_t valSize_t );
public     :                                     void SetSize (size_t valSize_t );
public     :                                     logical SetThreshold (size_t threshold );
public     :                                     void SetWPos (size_t valSize_t );
public     : virtual SOS7ImpExp                                          ~CS_Buffer ( );
};

#pragma pack()
#endif
