/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_Environment

\brief    


\date     $Date: 2006/03/13 21:30:31,26 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_Environment_HPP
#define   ODC_Environment_HPP

class     ODC_Environment;

#ifndef   P_ODC_Project_HPP
#define   P_ODC_Project_HPP
#include  <sPI.hpp>
class       ODC_Project;
PI_dcl     (ODC_Project)
#endif
#include  <sSDB_Resource.hpp>
#pragma pack(8)

class  ODC_Environment :public SDB_Resource
{
protected  :         char                                         env_title[51] ATTR_ALIGN(4);                               
protected  :         char                                         link_spec[397];                                            
protected  :         char                                         lib_manager[161];                                          
protected  :         PI(mem)                                      help_spec;                                                 
protected  :         PI(mem)                                      resc_spec;                                                 
protected  :         PI(mem)                                      comp_spec;                                                 
protected  :         PI(ODC_Project)                              env_ref;                                                   

public     :
                     char                                        *get_env_title() { return(env_title); }
                     char                                        *get_link_spec() { return(link_spec); }
                     char                                        *get_lib_manager() { return(lib_manager); }
                     PI(mem)                                     &get_help_spec() { return(help_spec); }
                     PI(mem)                                     &get_resc_spec() { return(resc_spec); }
                     PI(mem)                                     &get_comp_spec() { return(comp_spec); }
                     PI(ODC_Project)                             &get_env_ref() { return(env_ref); }
};

#pragma pack()
#endif
