/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cDSCTopicEdit

\brief    


\date     $Date: 2006/04/24 13:34:16,87 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cDSCTopicEdit_HPP
#define   cDSCTopicEdit_HPP

class     cDSCTopicEdit;

class  cDSCTopicEdit :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                             int8 DoBeforeFillData ( );
public     :                                                             cDSCTopicEdit ( );
public     : virtual                                                     ~cDSCTopicEdit ( );
};

#endif
