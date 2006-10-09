/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cDoubleTabMaster

\brief    


\date     $Date: 2006/06/03 15:05:22,89 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cDoubleTabMaster_HPP
#define   cDoubleTabMaster_HPP

class     cDoubleTabMaster;

class  cDoubleTabMaster :public CTX_Control
{
protected  :         int32                                        display_level;                                             // 
protected  :         logical                                      ignore_slave;                                              // 

public     :
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                        logical DisplayLevelChanged ( );
public     : virtual                                int8 DoAfterSelect ( );
public     : virtual                                int8 DoBeforeSelect ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                             cDoubleTabMaster ( );
public     :                                             ~cDoubleTabMaster ( );
};

#endif
