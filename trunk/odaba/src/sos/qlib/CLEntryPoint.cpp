/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CLEntryPoint

\brief    Command Line Entry Point


\date     $Date: 2006/03/12 19:21:22,04 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CLEntryPoint"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <sCommandLine.hpp>
#include  <sflnk.hpp>
#include  <sCLEntryPoint.hpp>


/******************************************************************************/
/**
\brief  CLEntryPoint


\param  ep_name - Entry point name
\param  cmdlist -
\param  pos -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CLEntryPoint"

                        CLEntryPoint :: CLEntryPoint (char *ep_name, DLL(CommandLine) *cmdlist, uint16 pos )
                     :   cmd_list(cmdlist),
  cmd_pos(pos)
{

  if ( ep_name )
    gvtxstb(cmd_name,ep_name,sizeof(cmd_name));
  else
    memset(cmd_name,' ',sizeof(cmd_name)-1);


}


