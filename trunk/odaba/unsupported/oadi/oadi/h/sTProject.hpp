/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    TProject

\brief    


\date     $Date: 2006/07/31 11:18:49,37 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TProject_HPP
#define   TProject_HPP

class     TProject;

class     CTX_Project;
class     ODProject;
class     OElementStyle;
class     OProject;
class     TControl;
#include  <sTActionHandler.hpp>
#include  <sTApplication.hpp>
class  TProject :public TApplication
{
protected  :         OProject                                    *project;                                                   // 

public     :
                     OProject                                    *get_project() { return(project); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     :                                        logical DoCreate ( );
public     :                                        logical DoCreated ( );
public     :                                        void SetMainWindow ( );
public     :                                             TProject ( );
};

#endif
