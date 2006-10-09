/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CLEntryPoint

\brief    Command Line Entry Point


\date     $Date: 2006/03/12 19:19:39,89 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CLEntryPoint_HPP
#define   CLEntryPoint_HPP

class     CLEntryPoint;

class     CommandLine;
#pragma pack(8)

class  CLEntryPoint
{
protected  :         char                                         cmd_name[64];                                              
protected  :         DLL(CommandLine)                            *cmd_list;                                                  
protected  :         uint16                                       cmd_pos;                                                   

public     :
                     char                                        *get_cmd_name() { return(cmd_name); }
                     DLL(CommandLine)                            *get_cmd_list() { return(cmd_list); }
                     uint16                                       get_cmd_pos() { return(cmd_pos); }
public     :                                                             CLEntryPoint (char *ep_name, DLL(CommandLine) *cmdlist, uint16 pos );
};

#pragma pack()
#endif
