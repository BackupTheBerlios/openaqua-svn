/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cInputHelpBase

\brief    


\date     $Date: 2006/04/24 13:38:28,41 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cInputHelpBase_HPP
#define   cInputHelpBase_HPP

class     cInputHelpBase;

class     PropertyHandle;
class  cInputHelpBase :public CTX_Control
{

public     :
public     : virtual                             int8 DoAfterDataSet ( );
public     : virtual                             int8 DoAfterHide ( );
public     :                                     char *GetContextInfo (int32 &offset_ref );
public     :                                     logical GetMyClass (TypeKey &type_key );
public     :                                     PropertyHandle *GetMyFunctImpPH ( );
public     :                                     logical SetDatasource (PropertyHandle *source_ph );
public     :                                                             cInputHelpBase ( );
public     : virtual                                                     ~cInputHelpBase ( );
};

#endif
