/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_Executable

\brief    


\date     $Date: 2006/03/13 21:30:31,35 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_Executable_HPP
#define   ODC_Executable_HPP

class     ODC_Executable;

#ifndef   P_FileMemo_HPP
#define   P_FileMemo_HPP
#include  <sPI.hpp>
class       FileMemo;
PI_dcl     (FileMemo)
#endif
#ifndef   P_ODC_DefFile_HPP
#define   P_ODC_DefFile_HPP
#include  <sPI.hpp>
class       ODC_DefFile;
PI_dcl     (ODC_DefFile)
#endif
#ifndef   P_ODC_Main_HPP
#define   P_ODC_Main_HPP
#include  <sPI.hpp>
class       ODC_Main;
PI_dcl     (ODC_Main)
#endif
#ifndef   P_ODC_Module_HPP
#define   P_ODC_Module_HPP
#include  <sPI.hpp>
class       ODC_Module;
PI_dcl     (ODC_Module)
#endif
#include  <sODC_Main.hpp>
#pragma pack(8)

class  ODC_Executable :public ODC_Main
{
protected  :         logical                                      autolink ATTR_ALIGN(4);                                    //
protected  :         logical                                      dll_option;                                                //
protected  :         PI(FileMemo)                                 def_file;                                                  //
protected  :         PI(ODC_Module)                               module;                                                    //
protected  :         PI(ODC_Variable)                             mexternals;                                                

public     :
                     logical                                      get_autolink() { return(autolink); }
                     logical                                      get_dll_option() { return(dll_option); }
                     PI(FileMemo)                                &get_def_file() { return(def_file); }
                     PI(ODC_Module)                              &get_module() { return(module); }
                     PI(ODC_Variable)                            &get_mexternals() { return(mexternals); }
public     :                                     char *GetDocFileName ( );
};

#pragma pack()
#endif
