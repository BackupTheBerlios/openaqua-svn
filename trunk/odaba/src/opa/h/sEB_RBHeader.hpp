/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EB_RBHeader

\brief    


\date     $Date: 2006/03/12 19:13:18,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EB_RBHeader_HPP
#define   EB_RBHeader_HPP

class     EB_RBHeader;

#include  <sEB_MBHeader.hpp>
#pragma pack(8)

class  EB_RBHeader :public EB_MBHeader
{

public     :
public     :                                                             EB_RBHeader (uint16 len, logical netopt );
public     : virtual                             logical Reset ( );
};

#pragma pack()
#endif
