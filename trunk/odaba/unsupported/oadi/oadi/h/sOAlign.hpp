/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OAlign



\date     $Date: 2006/04/28 16:39:36,25 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OAlign_HPP
#define   OAlign_HPP

class     OAlign;

class     PropertyHandle;
#include  <sDAlign.hpp>
#include  <sOPersistent.hpp>
#pragma pack(4)

class  OAlign :public OPersistent,
public DAlign
{

public     :
public     :                                             OAlign ( );
public     :                                             OAlign (OPersistent bcOPersistent, DAlign bcDAlign );
public     : virtual                                logical Read (PropertyHandle *ph );
public     :                                        void Reset ( );
public     : virtual                                     ~OAlign ( );
};

#pragma pack()
#endif
