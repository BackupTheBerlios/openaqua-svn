/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    PCSHandle

\brief    


\date     $Date: 2006/03/12 19:13:44,78 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   PCSHandle_HPP
#define   PCSHandle_HPP

class     PCSHandle;

class     CSA_Handle;
#pragma pack(8)

class  PCSHandle
{
protected  :         CSA_Handle                                  *active_handle;                                             

public     :
                     CSA_Handle                                  *get_active_handle() { return(active_handle); }
public     :                                     CSA_Handle *Get ( );
public     :                                                             PCSHandle (CSA_Handle *acthdl=NULL );
public     :                                     CSA_Handle *operator-> ( );
public     :                                     CSA_Handle *operator= (CSA_Handle *act_handle );
public     :                                                             ~PCSHandle ( );
};

#pragma pack()
#endif
