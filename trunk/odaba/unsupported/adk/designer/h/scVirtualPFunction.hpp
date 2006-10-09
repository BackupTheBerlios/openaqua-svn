/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/14|13:42:34,87}|(REF)
\class    cVirtualPFunction



\date     $Date: 2006/03/23 18:29:13,95 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cVirtualPFunction_HPP
#define   cVirtualPFunction_HPP

class     cVirtualPFunction;

class  cVirtualPFunction :public CTX_Control
{
protected  :         PropertyHandle                               source;                                                    

public     :
                     PropertyHandle                              &get_source() { return(source); }
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                     int8 DoAfterOpen ( );
public     :                                                             cVirtualPFunction ( );
public     : virtual                                                     ~cVirtualPFunction ( );
};

#endif
