/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_DAHeader

\brief    


\date     $Date: 2006/03/12 19:13:16,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EB_DAHeader_HPP
#define   EB_DAHeader_HPP

class     EB_DAHeader;

#include  <sEB_Header.hpp>
#pragma pack(8)

class  EB_DAHeader :public EB_Header
{
public     :         FILE                                        *temp_file ATTR_ALIGN(4);                                   

public     :
public     :                                                             EB_DAHeader (uint16 len, logical netopt );
public     :                                     logical IncreasePosition (int32 length );
public     : virtual                             logical Reset ( );
public     :                                     void SetPosition (uint64 position64 );
public     :                                     void SetSize (int64 dasize64 );
public     :                                     logical SetVersion (int16 new_version );
public     :                                     logical UpdatePosition (logical writeopt );
};

#pragma pack()
#endif
