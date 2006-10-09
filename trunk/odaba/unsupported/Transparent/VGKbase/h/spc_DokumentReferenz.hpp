/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    pc_DokumentReferenz

\brief    


\date     $Date: 2006/07/19 22:12:56,73 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_DokumentReferenz_HPP
#define   pc_DokumentReferenz_HPP

class     pc_DokumentReferenz;

#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc_DokumentReferenz :public PropertyHandle
{

public     :
public     :                                        logical CreateReferenz (char *cpath );
public     :                                        logical CreateReferenz (char *path, char *filename, char *filext );
public     :                                        char *GetCompletePath (NString &nstring );
public     :                                             pc_DokumentReferenz (PropertyHandle *prophdl );
public     :                                             pc_DokumentReferenz (DatabaseHandle &dbhandle, char *extnames, PIACC accopt );
};

#endif
