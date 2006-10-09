/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassStack

\brief    


\date     $Date: 2006/06/01 16:56:04,84 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cClassStack"

#include  <pdesign.h>
#include  <scClassStack.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cClassStack :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cClassStack();
  return(NO);


}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return  - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical cClassStack :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("SetLastImplementation",ALINK(this,cClassStack,SetLastImplementation)),
                           cfte("Synchronize",ALINK(this,cClassStack,Synchronize)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = CTX_Control::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetLastImplementation - 


\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastImplementation"

logical cClassStack :: SetLastImplementation ( )
{

  return( SetLastImplementation(Parm(1)) );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  impl_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastImplementation"

logical cClassStack :: SetLastImplementation (char *impl_name )
{
  logical     term = NO;
  if ( !impl_name || !*impl_name )
    last_impl[0] = 0;
  else 
    gvtxstb(last_impl,impl_name,ID_SIZE);
  return(term);
}

/******************************************************************************/
/**
\brief  Synchronize - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Synchronize"

logical cClassStack :: Synchronize ( )
{
  PropertyHandle  *prophdl = NULL;
  PropertyHandle  *funct_ph = NULL;
  PropertyHandle  *impl_ph = NULL;
  CTX_Control     *tab_ctx = NULL;
  char            *parm    = Parm(1);
  logical          started;
  logical          term    = NO;
BEGINSEQ
  Pointer(POINTER_Wait);
  
  if ( SetVirtualType(parm) )
    SetVirtualType("STRING");
  else
  {
    if ( !(tab_ctx = GetActiveElementContext()) )   P_ERR(99)
    
    if ( !tab_ctx->UserState1() )
    {
      tab_ctx->SetUserState1(YES);
      if ( strcmp(parm,"STRING") )
      {
        PropertyHandle  tab_ph(GetDATDB(),parm,PI_Update);
                                                    P_SDBCERR
        if ( tab_ctx->SetPropertyHandle(&tab_ph) )  ERROR
      }
    }

    if ( !(prophdl = GetCurrentPropertyHandle()) )  ERROR
    if ( !(parm = Parm(2)) )                        LEAVESEQ
    
    started = prophdl->StartRTA() ? YES : NO;
    PropertyHandle phparm2(parm);
    if ( !prophdl->Get(phparm2) )      
      term = YES;
    else if ( parm = Parm(3) )
    { 
      funct_ph = prophdl->GPH("pfunctions");
      PropertyHandle phparm3(parm);
      if ( !(funct_ph->Get(phparm3)) )
        term = YES;
      else 
      {
        impl_ph = funct_ph->GPH("implementations");
        if ( *last_impl )
          impl_ph->Get(last_impl);
        if ( !impl_ph->IsPositioned() )
          impl_ph->Get(0);
      }
    } 
    prophdl->StopRTA(started);
  }  

RECOVER
  term = YES;
ENDSEQ
  Pointer(POINTER_Arrow);
  return(term);
}

/******************************************************************************/
/**
\brief  cClassStack - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cClassStack"

     cClassStack :: cClassStack ( )
                     : CTX_Control ()
{

  last_impl[0] = 0;

}

/******************************************************************************/
/**
\brief  ~cClassStack - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cClassStack"

     cClassStack :: ~cClassStack ( )
{



}


