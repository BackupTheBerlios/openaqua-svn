/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    DBreakPoint

\brief    


\date     $Date: 2006/03/12 19:19:51,60 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBreakPoint_HPP
#define   DBreakPoint_HPP

class     DBreakPoint;

class  DBreakPoint
{
protected  :         char                                        *auto_proc;                                                 //

public     :
                     char                                        *get_auto_proc() { return(auto_proc); }
public     :                                                             DBreakPoint ( );
public     :                                     void SetAutoRun (char *name );
public     :                                                             ~DBreakPoint ( );
};

#endif
