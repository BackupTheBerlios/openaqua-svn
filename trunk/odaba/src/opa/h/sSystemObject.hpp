/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    SystemObject



\date     $Date: 2006/05/13 12:51:18,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SystemObject_HPP
#define   SystemObject_HPP

class     SystemObject;

class     ACObject;
#pragma pack(8)

class  SystemObject :public ACObject
{

public     :
public     :                                        logical Version6 ( );
public     :                                        logical VersionCheck ( );
public     :                                        logical VersionChecka ( );
};

#pragma pack()
#endif
