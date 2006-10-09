/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    sBase_SharedData

\brief    


\date     $Date: 2006/06/19 17:36:27,20 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sBase_SharedData_HPP
#define   sBase_SharedData_HPP

class     sBase_SharedData;

class  sBase_SharedData :public CTX_Structure
{

public     :
public     :                                        logical InitKey (char *prop_path, char *extnames );
public     :                                             sBase_SharedData ( );
public     : virtual                                     ~sBase_SharedData ( );
};

#endif
