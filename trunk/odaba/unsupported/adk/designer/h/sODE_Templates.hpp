/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    ODE_Templates



\date     $Date: 2006/05/30 15:29:53,29 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODE_Templates_HPP
#define   ODE_Templates_HPP

class     ODE_Templates;

#include  <cProjectImplementationType.h>
#include  <sNString.hpp>
class  ODE_Templates
{
protected  :         NString                                      tpl_path;                                                  
protected  :         NString                                      target_path;                                               
protected  :         char                                        *type;                                                      

public     :
                     NString                                     &get_tpl_path() { return(tpl_path); }
                     NString                                     &get_target_path() { return(target_path); }
                     char                                        *get_type() { return(type); }
public     :                                        char *GetTemplatePathSubFolder ( );
public     :                                        char *GetTemplateVariable ( );
public     :                                        logical InitFile (char *srce_path, char *fnames, char *var_ident, NString &nstring );
public     :                                        logical InitFiles (ProjectImplementationType pimpl_type, char *var_ident, NString &nstring );
public     :                                        logical InitFiles (char *srce_path, char *var_ident, NString &nstring );
public     :                                             ODE_Templates (char *folder_type );
public     :                                        char *TargetPath (PropertyHandle *prophdl, NString &nstring );
public     :                                        char *TemplatePath ( );
public     :                                        logical WriteFile (char *cpath, char *area, NString &nstring );
};

#endif
