/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_Header

\brief    


\date     $Date: 2006/03/12 19:13:16,43 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EB_Header_HPP
#define   EB_Header_HPP

class     EB_Header;

#include  <sEB_extRBHeader.hpp>
#include  <sRessourceLock.hpp>
#pragma pack(8)

class  EB_Header :public EB_extRBHeader,
public RessourceLock,
public bsts
{
protected  :         int16                                        file_handle ATTR_ALIGN(4);                                 //
protected  :         logical                                      net_opt;                                                   //

public     :
                     int16                                        get_file_handle() { return(file_handle); }
                     logical                                      get_net_opt() { return(net_opt); }
public     :                                                             EB_Header (uint16 len, logical netopt );
public     :                                     logical Lock ( );
public     :                                     logical LockInternal (uint64 position64, int32 length, logical wait );
public     : virtual                             logical Read ( );
public     : virtual                             logical Reset ( );
public     :                                     logical Unlock ( );
public     :                                     logical UnlockInternal (uint64 position64, int32 length );
public     :                                     logical Write ( );
public     :                                     void SetFileHandle (int16 filehandle ){

  file_handle = filehandle;

}

};

#pragma pack()
#endif
