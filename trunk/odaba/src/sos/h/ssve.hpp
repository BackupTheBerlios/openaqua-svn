/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    sve

\brief    


\date     $Date: 2006/03/12 19:20:59,10 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sve_HPP
#define   sve_HPP

class     sve;

#include  <sbds.hpp>
#pragma pack(8)

class  sve
{
protected  :         char                                         svename[40];                                               //
protected  :         bds                                          svetext;                                                   //

public     :
                     char                                        *get_svename() { return(svename); }
                     bds                                         &get_svetext() { return(svetext); }
public     :                                                             sve (char *vnames, char *vtext );
public     :                                     logical sveupd (char *vtext );
public     :                                     bds &svetextg ( ){

  return(svetext);

}

};

#pragma pack()
#endif
