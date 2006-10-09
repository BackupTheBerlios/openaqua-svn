/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_ProjRef

\brief    


\date     $Date: 2006/03/13 21:30:34,03 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_ProjRef_HPP
#define   ODC_ProjRef_HPP

class     ODC_ProjRef;

#ifndef   P_ODC_Project_HPP
#define   P_ODC_Project_HPP
#include  <sPI.hpp>
class       ODC_Project;
PI_dcl     (ODC_Project)
#endif
#pragma pack(8)

class  ODC_ProjRef :public SDB_Resource
{
protected  :         char                                         project_name[40] ATTR_ALIGN(4);                            
protected  :         char                                         dll_path[128];                                             
protected  :         char                                         ini_file[128];                                             
protected  :         char                                         reserved[500];                                             

public     :
                     char                                        *get_project_name() { return(project_name); }
                     char                                        *get_dll_path() { return(dll_path); }
                     char                                        *get_ini_file() { return(ini_file); }
                     char                                        *get_reserved() { return(reserved); }
};

#pragma pack()
#endif
