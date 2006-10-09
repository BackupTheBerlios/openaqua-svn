/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODABA2_extern

\brief    


\date     $Date: 2006/03/13 21:30:30,51 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODABA2_extern_HPP
#define   ODABA2_extern_HPP

class     ODABA2_extern;

#pragma pack(1)

class  ODABA2_extern
{
protected  :         char                                         sys_ident[40];                                             
public     :         char                                         path_names[20][8];                                         
protected  :         char                                         proj_path[129];                                            
protected  :         char                                         error_class[40];                                           

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
                     char                                        *get_proj_path() { return(proj_path); }
                     char                                        *get_error_class() { return(error_class); }
public     :                                     char *GetProjectPath (char *folder_type );
public     :                                     char *GetProjectPath (char *ppath, char *folder_type );
};

#pragma pack()
#endif
