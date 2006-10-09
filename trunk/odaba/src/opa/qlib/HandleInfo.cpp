/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    HandleInfo

\brief    


\date     $Date: 2006/03/12 19:17:35,73 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "HandleInfo"

#include  <popa7.h>
#ifndef   GSRT_HandleInfo_HPP
#define   GSRT_HandleInfo_HPP
#include  <sHandleInfo.hpp>
#include  <sGSRT.h>
#endif
#include  <sCClient.hpp>
#include  <sCS_Handle.hpp>
#include  <sHandleInfo.hpp>


/******************************************************************************/
/**
\brief  Build - 


\return term - Termination code

\param  ph -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Build"

logical HandleInfo :: Build (PropertyHandle &ph )
{
  int32                    indx = 0;
  logical                 term = NO;
  ph.Provide(Key(number));
  *(HandleInfo *)ph.GetInstance().GetData() = *this;
  ph.Modify();
  ph.Save();

  return(term);
}

/******************************************************************************/
/**
\brief  BuildList - 


\return term - Termination code

\param  ph -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BuildList"

logical HandleInfo :: BuildList (PropertyHandle &ph )
{
  int32                    indx = 0;
  HandleInfo             *hi;
  logical                 term = NO;
  CreateSubHandleList();

  while ( hi = sub_handles->GetEntry(++indx) )
    hi->Build(*ph.GetPropertyHandle("sub_handles"));

  delete sub_handles;
  sub_handles = NULL;  

  return(term);
}

/******************************************************************************/
/**
\brief  CreateSubHandleList - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubHandleList"

logical HandleInfo :: CreateSubHandleList ( )
{
  int32                    indx0 = 0;
  CS_Handle              *ch;
  logical                 term = NO;
  if ( !sub_handles )
  {
    sub_handles = new GSRT(HandleInfo)(10,sizeof(HandleInfo),128,0,'C',YES);
    while ( ch = GetClientHandle(indx0) )
    {
      HandleInfo  hi(this,ch);
//      memcpy(hi.number,"99999",5);
//      gvtxltp(hi.number,indx0,5);
      sub_handles->AddEntry(&hi);
      indx0++;
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Disconnect

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Disconnect"

logical HandleInfo :: Disconnect ( )
{
  logical                 term = NO;
  if ( cclient )
    cclient->Disconnect();
  return(term);
}

/******************************************************************************/
/**
\brief  GetClientHandle - 


\return ch -

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClientHandle"

CS_Handle *HandleInfo :: GetClientHandle (int32 indx0 )
{

  return ( cs_handle.GetServerPointer() 
           ? cclient->GetClientHandle(&cs_handle,indx0) 
           : cclient->GetClientHandle(indx0)  );


}

/******************************************************************************/
/**
\brief  HandleInfo - 


-------------------------------------------------------------------------------
\brief i0


\param  parent_info -
\param  ch -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandleInfo"

                        HandleInfo :: HandleInfo (HandleInfo *parent_info, CS_Handle *ch )
                     : name(),
  type(),
  calls(0),
  calls_time(0),
  all_calls(0),
  all_calls_time(0),
  is_active(NO),
  n_sub_handles(0),
  level(parent_info->level+1),
  sub_handles(NULL),
  cclient(parent_info->cclient),
  cs_handle(*ch)
{

  if ( ch )
    cclient->GetHandleInfo(&cs_handle,*this);


}

/******************************************************************************/
/**
\brief i1


\param  client -
\param  server_name -
\param  port_name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandleInfo"

                        HandleInfo :: HandleInfo (ODABAClient &client, char *server_name, char *port_name )
                     :   calls(0),
  calls_time(0),
  all_calls(0),
  all_calls_time(0),
  is_active(NO),
  level(0),
  n_sub_handles(0),
  sub_handles(NULL),
  cclient(client.GetClientPtr()),
  cs_handle()
{

  memcpy(number,"00000",5);
  strcpy(type,"Server");
  strcat(strcat(strcpy(name,server_name),"/"),port_name);

}

/******************************************************************************/
/**
\brief i2


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandleInfo"

                        HandleInfo :: HandleInfo ( )
                     :   calls(0),
  calls_time(0),
  all_calls(0),
  all_calls_time(0),
  is_active(NO),
  n_sub_handles(0),
  level(0),
  cclient(NULL),
  cs_handle(),
  sub_handles(NULL)
{

  memset(number,' ',sizeof(number));
  memset(name,' ',sizeof(name));
  memset(type,' ',sizeof(type));


}

/******************************************************************************/
/**
\brief  Kill

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Kill"

logical HandleInfo :: Kill ( )
{
  char                    string[10];
  logical                 term = NO;
  if ( cclient )
    cclient->KillClient(atol(gvtxbts(string,number,sizeof(number))));
  return(term);
}

/******************************************************************************/
/**
\brief  Print - 


\return term - Termination code

\param  filehdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Print"

logical HandleInfo :: Print (FILE *filehdl )
{
  char                    out[256];
  char                   *pos = out; 
  int32                    indx = 0;
  HandleInfo             *hi;
  logical                 term = NO;
  CreateSubHandleList();

  strcpy(pos,"\r\n");
  pos += 2;
  memcpy(pos,number,sizeof(number));
  pos += sizeof(number);
  memset(pos,' ',level*2);
  pos += level*2;
  strcat(strcat(strcat(strcpy(pos,name)," ("),type),")");
  fprintf(filehdl,out);
  
  while ( hi = sub_handles->GetEntry(++indx) )
    hi->Print(filehdl);


  delete sub_handles;
  sub_handles = NULL;
  return(term);
}

/******************************************************************************/
/**
\brief  operator= - 


\return hi_ref -

\param  hi_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

HandleInfo &HandleInfo :: operator= (HandleInfo &hi_ref )
{

  memcpy(number,hi_ref.number,sizeof(number));
  memcpy(name,hi_ref.name,sizeof(name));
  memcpy(type,hi_ref.type,sizeof(type));
  calls           = hi_ref.calls;
  calls_time      = hi_ref.calls_time;
  all_calls       = hi_ref.all_calls;
  all_calls_time  = hi_ref.all_calls_time;
  n_sub_handles   = hi_ref.n_sub_handles;
  level           = hi_ref.level;
  cclient         = hi_ref.cclient;
  memcpy(&cs_handle,&hi_ref.cs_handle,sizeof(cs_handle));

  return(*this);
}

/******************************************************************************/
/**
\brief  ~HandleInfo - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~HandleInfo"

                        HandleInfo :: ~HandleInfo ( )
{



}


