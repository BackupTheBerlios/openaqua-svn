/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_SBHeader

\brief    


\date     $Date: 2006/03/12 19:13:18,20 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EB_SBHeader_HPP
#define   EB_SBHeader_HPP

class     EB_SBHeader;

#include  <sEB_DAHeader.hpp>
#pragma pack(8)

class  EB_SBHeader :public EB_DAHeader
{
protected  :         int32                                        buffer_size ATTR_ALIGN(4);                                 //

public     :
                     int32                                        get_buffer_size() { return(buffer_size); }
public     :                                                             EB_SBHeader (uint16 len, logical netopt );
public     :                                     void NextArea ( );
public     : virtual                             logical Reset ( );
public     :                                     void SetMaxEntry (int32 length );
};

#pragma pack()
#endif
