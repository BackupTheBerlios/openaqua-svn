/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassCode

\brief    


\date     $Date: 2006/06/01 16:17:31,84 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cClassCode"

#include  <pdesign.h>
#include  <scClassCode.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cClassCode :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cClassCode();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterStoreData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterStoreData"

int8 cClassCode :: DoAfterStoreData ( )
{
  PropertyHandle  *prophdl = GetPropertyHandle();
  cClassCodeBase::DoAfterStoreData();
  
  prophdl->GetParentProperty()->
    ExecuteInstanceAction("SetupCodeBlockOptions",NULL);

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

logical cClassCode :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("InsertCheckError",ALINK(this,cClassCode,InsertCheckError)),
                           cfte("InsertError",ALINK(this,cClassCode,InsertError)),
                           cfte("InsertErrorNum",ALINK(this,cClassCode,InsertErrorNum)),
                           cfte("InsertLeaveseq",ALINK(this,cClassCode,InsertLeaveseq)),
                           cfte("InsertProjError",ALINK(this,cClassCode,InsertProjError)),
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
    term = cClassCodeBase::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InsertCheckError - Insert macro '...CERR'


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertCheckError"

logical cClassCode :: InsertCheckError ( )
{
  char   *errpre = GetSysVariable("ErrPrefix");
  char    string[32];
  strcat(strcpy(string,errpre ? errpre : "P_"),"SDBCERR");
  
  return ( InsertErrString(string) );


}

/******************************************************************************/
/**
\brief  InsertErrString - 


\return term - 

\param  text - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertErrString"

logical cClassCode :: InsertErrString (char *text )
{
  DPoint       dpos       = GetPosition();
  int          line       = 0;
  int          line_end   = 0;
  int          col_pos    = 0;
  std::string  idata("");
  logical      term       = NO;
BEGINSEQ
  if ( ProvideData() )                               ERROR

  line = dpos.Y - 1;
  
  if ( line_end = matches[line].second )
  {
    if ( data.at(matches[line].first + line_end -1) == 0x0a )
      line_end--;
    if ( data.at(matches[line].first + line_end -1) == 0x0d )
      line_end--;
  }
  
  col_pos    = line_end;
  
  if ( line_end > ERR_MACRO_POS )
  {
    idata.append("\n");
    col_pos = 0;
    dpos.Y++;
  }
  idata.append(ERR_MACRO_POS-col_pos,' ');
  idata.append(text);
  
  data.insert(matches[line].first+line_end,idata);
  SetData((char *)data.c_str());
  
  dpos.X = ERR_MACRO_POS+strlen(text)+1;
  SetPosition(dpos);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InsertError - Insert macro 'ERROR


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertError"

logical cClassCode :: InsertError ( )
{

BEGINSEQ
  return ( InsertErrString("ERROR") );
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  InsertErrorNum - Insert next available error number


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertErrorNum"

logical cClassCode :: InsertErrorNum ( )
{
  DPoint       dpos           = GetPosition();
  char        *err_num_string = NULL;
  logical      term           = NO;
BEGINSEQ
  if ( ProvideData() )                               ERROR

  if ( GetProjectContext()->ExecuteFunction("ProvideNewError") )
                                                     ERROR
  err_num_string = GetProjectContext()->GetResult();

  data.insert(offset,err_num_string);
  SetData((char *)data.c_str());
  
  SetPosition(dpos);
  
//  GetProjectContext()->ExecuteAction("EditError");

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InsertLeaveseq - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertLeaveseq"

logical cClassCode :: InsertLeaveseq ( )
{

BEGINSEQ
  return ( InsertErrString("LEAVESEQ") );
ENDSEQ

}

/******************************************************************************/
/**
\brief  InsertProjError - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertProjError"

logical cClassCode :: InsertProjError ( )
{
  char      *errpre = GetSysVariable("ErrPrefix");
  char       string[32];
  DPoint     dpos;
  logical    term   = NO;
BEGINSEQ
  strcat(strcpy(string,errpre ? errpre : "P_"),"ERR()");
  
  if ( InsertErrString(string) )                     ERROR
  
  dpos = GetPosition();
  dpos.X-=1;
  SetPosition(dpos);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cClassCode - Construktor (standard)



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cClassCode"

     cClassCode :: cClassCode ( )
                     : cClassCodeBase ()
{



}

/******************************************************************************/
/**
\brief  ~cClassCode - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cClassCode"

     cClassCode :: ~cClassCode ( )
{



}


