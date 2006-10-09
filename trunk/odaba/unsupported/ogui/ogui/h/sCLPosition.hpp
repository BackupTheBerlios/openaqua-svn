/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    CLPosition

\brief    


\date     $Date: 2006/03/13 21:33:33,26 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CLPosition_HPP
#define   CLPosition_HPP

class     CLPosition;

#pragma pack(4)

class  CLPosition
{
public     :         size_t                                       clnum;                                                     
public     :         size_t                                       clindex;                                                   
public     :         void                                        *cluster;                                                   
public     :         logical                                      validread;                                                 
public     :         logical                                      validwrite;                                                

public     :
public     :                                                             CLPosition ( );
};

#pragma pack()
#endif
