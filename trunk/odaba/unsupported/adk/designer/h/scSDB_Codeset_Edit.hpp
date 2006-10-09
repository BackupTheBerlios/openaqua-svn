/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSDB_Codeset_Edit



\date     $Date: 2006/04/24 13:45:03,71 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cSDB_Codeset_Edit_HPP
#define   cSDB_Codeset_Edit_HPP

class     cSDB_Codeset_Edit;

class  cSDB_Codeset_Edit :public CTX_Control
{
protected  :         PropertyHandle                               cs_ph;                                                     

public     :
                     PropertyHandle                              &get_cs_ph() { return(cs_ph); }
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoBeforeFillData ( );
public     :                                                             cSDB_Codeset_Edit ( );
public     : virtual                                                     ~cSDB_Codeset_Edit ( );
};

#endif
