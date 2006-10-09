/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    svel

\brief    System Variable List
          System  variables are  variables, which  can be  passed via an ini- or
          configuration  file (XML). In addition, system variables can be set in
          the application program or in the system environment. 
          System  variables are  searched in  the following sequence (svelget(),
          GetSysVariable()):
          - in the internal table (svel)
          - in the ini- or configuration file
          - in the system environment
          System  variables,  which  could  not  be  located, are added as empty
          variables  to the table  and will not  be reloaded when being searched
          later on. 
          System   variables   usually   are   thread   variables,   i.e.   the 
          GetSysVariable()  function returns a  thread specific system variable.
          Each  thread  inherits  system  variables  from  its  parent thread by
          looking  for system variables  in a hierarchy  of variable lists. When
          looking  for a variable in a hierarchy, searching starts at the bottom
          list.  When the variable could not be found in the list and not in the
          ini-  or  configuration  file,  the  variable is searched in the upper
          list  etc. When not being found in  any list in the hierarchy, finally
          the variable is searched in the system variable.
          The  hierarchy  can  be  maintained using ConnectAt() or ConnectLast()
          and  DisconnectAt() or  DisconnectLast(). Both  functions will connect
          or  disconnect  two  hierarchies.  When  connecting  two  hierarchies,
          PopStop  is  set  for  the  hierarchy  connected  with  the  calling 
          hierarchy.  This is done automatically  by connect functions and reset
          by disconnect functions.

\date     $Date: 2006/05/30 13:49:18,32 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "svel"

#include  <pdefault.h>
#include  <sIniFile.hpp>
#include  <ssve.hpp>
#include  <ssvel.hpp>
#include  <ssvel.hpp>


/******************************************************************************/
/**
\brief  CheckSection

\return term - Success

\param  sectionname
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckSection"

logical svel :: CheckSection (char *sectionname )
{
  char         old_section[256];
  logical      term = NO;
  strcpy(old_section,svelpini->get_section_name());

  term = svelpini->LocateSection(sectionname);
  
  svelpini->LocateSection(old_section);

  return(term);
}

/******************************************************************************/
/**
\brief  ConnectAt        The  function connects two variable  hierarchies by inserting the passed
        hierarchy  immediately after  the current  list. PopStop  is set for the
        first  variable  list  in  the  hierarchy  to  be  connected  and in the
        variable list appended at the end

\return term - Success

\param  svelptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectAt"

logical svel :: ConnectAt (svel *svelptr )
{
  logical       term = NO;
BEGINSEQ
  if ( !svelptr )                                    LEAVESEQ
    
  if ( upper_list )
    if ( svelptr->ConnectTail(DisconnectUpper()) )   ERROR
 
  if ( ConnectTail(svelptr) )                        ERROR

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ConnectTail - Connect variable hierarchies
        The  function connects two variable  hierarchies by appending the passed
        hierarchy  or list at  the end of  the current hierarchy. PopStop is set
        for the first variable list in the hierarchy to be connected.

\return term - Success

\param  svelptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectTail"

logical svel :: ConnectTail (svel *svelptr )
{
  svel         *lsv;
  logical       term = NO;
BEGINSEQ
  if ( !svelptr )                                    ERROR
    
  if ( !svelpini && svelptr->get_svelpini() )
  {
    svelpini = new IniFile(*svelptr->get_svelpini());
    strcpy(svelmini,svelptr->get_svelmini());
  }
  
  lsv = this;
  while ( lsv && lsv->upper_list )
    lsv = lsv->upper_list;
  
  if ( lsv->ConnectUpper(svelptr) )                  ERROR
  svelptr->SetPopStop(YES);
RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ConnectUpper - Connect upper list
        The  function connects  a variable  list (or list hierarchy) immediately
        after  the current variable list. The  function fails, when the variable
        list has already an upper list.

\return term - Success

\param  svelptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectUpper"

logical svel :: ConnectUpper (svel *svelptr )
{
  logical       term = NO;
BEGINSEQ
  if ( !svelptr )                                    LEAVESEQ
  if ( upper_list )                                  ERROR
  
  upper_list = svelptr;
  upper_list->Lock();
  upper_list->children.AddTail(this);
  upper_list->Unlock();

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Copy

\return term - Success

\param  srcesvel
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical svel :: Copy (svel *srcesvel )
{

  return( svelcpy(srcesvel) );
 

}

/******************************************************************************/
/**
\brief  DisconnectAll


\param  svelptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisconnectAll"

void svel :: DisconnectAll (svel *svelptr )
{
  svel     *parent;
  if ( !svelptr )
    svelptr = NextSubHierarchy();
  parent = DisconnectTail(svelptr);
  
  children.GoTop();
  while ( svelptr = children.GetHead() )
  {
    svelptr->DisconnectUpper();
    svelptr->ConnectUpper(parent);
  }


}

/******************************************************************************/
/**
\brief  DisconnectAt - Disconnect Hierarchy or list
        The   function   removes   a   sub-hierarchy   from   the hierarchy. The
        sub-hierarchy  starts  with  the  list  passed to the function. When the
        list  could not be found in the hierarchy, the function returns an error
        (NULL).  Otherwise, the function  removes the part  of the list upto the
        next  higher  list  marked  as  PopStop. When no upper list is marked as
        PopStop, the whole tail is removed.

\return svelptr

\param  svelptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisconnectAt"

svel *svel :: DisconnectAt (svel *svelptr )
{
  svel       *lsv;
  svel       *upl;
BEGINSEQ
  if ( !svelptr || svelptr == this )                 ERROR
    
  lsv = svelptr;
  while ( lsv && !lsv->upper_list->PopStop() )
    lsv = lsv->upper_list;
    
  upl = this;
  while ( upl && upl->upper_list != svelptr ) 
    upl = upl->upper_list;
  if ( !upl )                                        ERROR
  
  if ( lsv )
    lsv = lsv->DisconnectUpper();
  
  upl->DisconnectUpper();
  upl->ConnectTail(lsv);

  svelptr->SetPopStop(NO);
RECOVER
  svelptr = NULL;
ENDSEQ
  return(svelptr);
}

/******************************************************************************/
/**
\brief  DisconnectTail - Disconnect last hierarchy or list
        The  function  removes  an  upper  hierarchy  (tail)  from  the  current
        hierarchy.  The upper  hierarchy to  be removed  starts with the varable
        list  passed to the function. When no variable list has been passed, the
        function  removes the last hierarchy or  variable list in the hierarchy,
        i.e.  the last variable  list, which is  marked as PopStop. When no such
        list  exists  in  the  hierarchy,  the function returns an error (NULL).
        Otherwise,  the function removes the upper hierarchy or list and returns
        it to the calling function.

\return svelptr

\param  svelptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisconnectTail"

svel *svel :: DisconnectTail (svel *svelptr )
{
  svel       *pdc;
BEGINSEQ
  if ( svelptr )
  {
    pdc = this;
    while ( pdc && pdc->upper_list != svelptr )
      pdc = pdc->upper_list;
  }
  else
  {
    svelptr = this;
    while ( svelptr )
    {
      if ( svelptr->upper_list->PopStop() )
        pdc = svelptr;   
      svelptr = svelptr->upper_list;
    }
  }  
  if ( !pdc )                                        ERROR
      
  svelptr = pdc->DisconnectUpper();

RECOVER
  svelptr = NULL;
ENDSEQ
  return(svelptr);
}

/******************************************************************************/
/**
\brief  DisconnectUpper - Disconnect upper list
        The  function  disconnects  the  variable  list  (or  list  hierarchy) 
        immediately  after the current variable  list (upper list). The function
        returns the variable list disconnected.

\return svelptr

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisconnectUpper"

svel *svel :: DisconnectUpper ( )
{
  svel       *upl = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( upl = upper_list )
  {
    upl->Lock();
    upl->children.Remove(this); 
    upper_list = NULL;
    upl->Unlock();
  }

RECOVER

ENDSEQ
  return(upl);
}

/******************************************************************************/
/**
\brief  GetINIFile

\return inipath

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetINIFile"

char *svel :: GetINIFile ( )
{

  return ( this && svelpini ? svelpini->get_file_name() : NULL );

}

/******************************************************************************/
/**
\brief  NextSubHierarchy

\return svelptr

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextSubHierarchy"

svel *svel :: NextSubHierarchy ( )
{
  svel       *svelptr = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  svelptr = upper_list;
  while ( svelptr && !svelptr->PopStop() )
    svelptr = svelptr->upper_list;


RECOVER
  svelptr = NULL;
ENDSEQ
  return(svelptr);
}

/******************************************************************************/
/**
\brief  Parent

\return svelptr

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parent"

svel *svel :: Parent ( )
{

  return ( this ? upper_list : NULL );

}

/******************************************************************************/
/**
\brief  Pop

\return svelptr

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Pop"

svel *svel :: Pop ( )
{
  svel      *high_svel = NULL;
  if ( !PopStop() && (high_svel = DisconnectUpper()) )
    delete this;

  return(high_svel);
}

/******************************************************************************/
/**
\brief  PopStop

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PopStop"

logical svel :: PopStop ( )
{

  return(this ? stscnof() : YES);

}

/******************************************************************************/
/**
\brief  Push

\return svelptr

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Push"

svel *svel :: Push ( )
{
  logical     ps;
  svel       *svelptr = NULL;
  svelptr = new svel(srtmax());

  ps = PopStop();
  svelptr->ConnectTail(this);
  SetPopStop(ps);



  return(svelptr);
}

/******************************************************************************/
/**
\brief  RemoveEmpty

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveEmpty"

logical svel :: RemoveEmpty ( )
{
  short int indx   = srtcnt();
  char     *vtext;
  sve      *sveptr = NULL;

  while ( indx && (sveptr = GetEntry(indx--)) )
  {
    vtext = sveptr->get_svetext().bdsagt();
    if ( !vtext || !*vtext )
      DeleteEntry(indx+1);
  }
  return(NO);

}

/******************************************************************************/
/**
\brief  SetPopStop


\param  pop_stop
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPopStop"

void svel :: SetPopStop (logical pop_stop )
{
  if ( pop_stop )
    stssnof();
  else
    stsrnof();
}

/******************************************************************************/
/**
\brief  svel


\param  maxe
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svel"

     svel :: svel (int32 maxe )
                     : GSRT(sve) (maxe,sizeof(sve),ID_SIZE,1,'C',YES),
  svelpini(NULL),
  upper_list(NULL),
  children()
{
  *svelmini = 0;

}

/******************************************************************************/
/**
\brief  sveladd

\return sveptr

\param  vnames
\param  vtext
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sveladd"

sve *svel :: sveladd (char *vnames, char *vtext )
{
  short int indx = 0;

BEGINSEQ
  if ( !vnames || !*vnames )                         ERROR
  
  sve       sveenty(vnames,vtext);
  if ( indx = FindEntry(sveenty.get_svename()) )     LEAVESEQ
  if ( !(indx = AddEntry(&sveenty)) )                ERROR

RECOVER

ENDSEQ
  return ( indx ? GetEntry(indx) : NULL );

}

/******************************************************************************/
/**
\brief  svelcpr

\return term - Success

\param  srcesvel
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svelcpr"

logical svel :: svelcpr (svel *srcesvel )
{
  short int indx = 0;
  sve      *sveptr = NULL;

  while ( sveptr = srcesvel->GetEntry(++indx) )
    svelset(sveptr->get_svename(),sveptr->get_svetext().bdsagt());
  return(NO);

}

/******************************************************************************/
/**
\brief  svelcpy

\return term - Success

\param  srcesvel
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svelcpy"

logical svel :: svelcpy (svel *srcesvel )
{
  short int indx   = 0;
  sve      *sveptr = NULL;
  char     *curval;

  while ( sveptr = srcesvel->GetEntry(++indx) )
  {
    if ( curval = svelget(sveptr->get_svename()) )
      svelset(sveptr->get_svename(),curval);
    else
    {
      sve  sveenty(sveptr->get_svename(),sveptr->get_svetext().bdsagt());
      AddEntry(&sveenty);
    }
  }  

  delete svelpini;
  svelpini = new IniFile(*srcesvel->get_svelpini());

  strcpy(svelmini,srcesvel->get_svelmini());

  return(NO);

}

/******************************************************************************/
/**
\brief  sveleget

\return sveptr

\param  vnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sveleget"

sve *svel :: sveleget (char *vnames )
{
  sve      *sveptr = NULL;
  svel     *svelptr = this;
  char      keyarea[ID_SIZE+1];
BEGINSEQ
  gvtxstb(keyarea,vnames,ID_SIZE);
  while ( svelptr )
  {
    if ( sveptr = svelptr->GetEntry(keyarea) )       LEAVESEQ
    svelptr = svelptr->upper_list;
  }
ENDSEQ
  return ( sveptr );

}

/******************************************************************************/
/**
\brief  svelexc

\return textptr

\param  textptr
\param  mlen
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svelexc"

char *svel :: svelexc (char *textptr, uint16 mlen )
{
  char     *curpos   = textptr;
  char     *variable = NULL;
  char     *varend   = NULL;
  char      varname[65];
  int       newlen   = UNDEF;
  int       oldlen   = strlen(textptr);
  logical   term     = NO;

BEGINSEQ
  while ( !term && (curpos = strchr(curpos,'%')) )
  {
    if ( curpos[1] == '%' )
    {
      gvtssdl(curpos,1);
      curpos++;
    }
    else
    {
      if ( !(varend = gvtsfbp(curpos,UNDEF)) )         ERROR
      *(varend-1) = 0;
      if ( strchr(curpos,' ') )
      {
        *(varend-1) = '%';
        curpos = varend-1;
      }
      else
      {
        variable = svelget(curpos+1);
        *(varend-1) = '%';
        memset(varname,0,sizeof(varname));
        memcpy(varname,curpos,MIN(64,varend-curpos));
        SOSRESET
        gvtsexc(textptr,varname,variable,mlen);
        if ( SOSERROR == 11 )
          term = YES;
        curpos += strlen(variable);
      }
    }
  }

  SOSRESET

  if ( (newlen = strlen(textptr)) < oldlen )
    memset(textptr+newlen,0,oldlen-newlen);

  if ( term )                                       ERROR
RECOVER
  textptr = NULL;
ENDSEQ
  return(textptr);

}

/******************************************************************************/
/**
\brief  svelfini

\return term - Success

\param  inipath
\param  mainsect
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svelfini"

logical svel :: svelfini (char *inipath, char *mainsect )
{
  logical       term = NO;
BEGINSEQ
  if ( inipath )
  {
    delete svelpini;
    svelpini = new IniFile(inipath);                 SOSCERR
    svelupd("_INIPATH_",svelpini->get_file_name());
    if ( svelpini->IsEmpty() )                       ERROR
  }
  
  if ( mainsect )
    strncpy(svelmini,mainsect,sizeof(svelmini)-1);
  
  if ( svelpini->LocateSection(svelmini) )           ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  svelget

\return vtext
-------------------------------------------------------------------------------
\brief  SVELGET


\param  vnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svelget"

char *svel :: svelget (char *vnames )
{
  sve      *sveptr = NULL;
  svel     *svelptr = this;
  char      keyarea[ID_SIZE+1];
  char     *vtext;
BEGINSEQ
//  SOSRESET  führt zu dead-locks im multithreading
  if ( !vnames || !*vnames )                         ERROR
  
  while ( svelptr )
  {
    if ( sveptr = svelptr->GetEntry(gvtxstb(keyarea,vnames,ID_SIZE)) )
    {
      vtext = sveptr->svetextg().bdsagt();
      if ( (vtext && *vtext) || svelptr == this )    LEAVESEQ
      break;
    }
    svelptr = svelptr->upper_list;
  }
  
  if ( !(vtext = svelread(vnames,NULL)) )
    vtext = getenv(gvtxbts(keyarea,vnames,ID_SIZE));
  
  if (vtext == 0) vtext = "";  
  if ( !(sveptr = sveladd(vnames,vtext )) ) ERROR
  // hier dürfen wir keinen SOSERROR setzen, da bei Fehlerausgabe sonst Fehler weg
  if ( !vtext )                                      ERROR

RECOVER

ENDSEQ
  return ( sveptr ? sveptr->svetextg().bdsagt() : NULL );

}

/******************************************************************************/
/**
\brief  i01


\param  indx
\param  vnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svelget"

char *svel :: svelget (int16 indx, char *vnames )
{
  sve      *sveptr = NULL;
  svel     *svelptr = this;
  char     *vtext   = NULL;
BEGINSEQ
  SOSRESET
  
  while ( !sveptr && svelptr )
  {
    if ( !(sveptr = svelptr->GetEntry(indx)) )
    {
      if ( (indx -= svelptr->srtcnt()) <= 0 )        LEAVESEQ
      svelptr = svelptr->upper_list;
    }
  }
  
  if ( sveptr )
  {
    if ( !(vtext = sveptr->svetextg().bdsagt()) )
      vtext = "";
    gvtxbts(vnames,sveptr->get_svename(),ID_SIZE);
  }

ENDSEQ
  return ( vtext );
}

/******************************************************************************/
/**
\brief  svelread

\return vtext
-------------------------------------------------------------------------------
\brief  SVELGET


\param  vnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svelread"

char *svel :: svelread (char *vnames )
{
  sve      *sveptr  = NULL;
  char      keyarea[ID_SIZE+1];
  char     *vtext;
BEGINSEQ
  if ( !vnames || !*vnames )                         ERROR
  
  if ( !(vtext = svelread(vnames,NULL)) )
    vtext = getenv(gvtxbts(keyarea,vnames,ID_SIZE));
  
  if ( !vtext )                                      ERROR
    
  svelset(vnames,vtext);
  sveptr = sveleget(vnames);
RECOVER
  sveptr = NULL;
ENDSEQ
  return ( sveptr ? sveptr->svetextg().bdsagt() : NULL );
}

/******************************************************************************/
/**
\brief  SVELGET_


\param  vnames
\param  sectname
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svelread"

char *svel :: svelread (char *vnames, char *sectname )
{
  char  *vtext = NULL;
BEGINSEQ
  if ( !svelpini )                                   ERROR
    
  svelpini->Refresh();
  
  if ( !sectname || !*sectname )
    sectname = svelmini;
  
  svelpini->LocateSection(sectname);

  vtext = svelpini->GetVariable(vnames);
RECOVER
ENDSEQ
  return(vtext);

}

/******************************************************************************/
/**
\brief  svelrmv

\return term - Success

\param  vnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svelrmv"

logical svel :: svelrmv (char *vnames )
{
  short int indx;
  logical   term = NO;

BEGINSEQ
  if ( !vnames || !*vnames )                         ERROR
  
  sve       sveenty(vnames,"");
  SOSCERR

  if ( !(indx = FindEntry(sveenty.get_svename())) )  ERROR
  if ( DeleteEntry(indx) )                           SOSERR(99)

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  svelset

\return term - Success

\param  vnames
\param  vtext
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svelset"

logical svel :: svelset (char *vnames, char *vtext )
{
  char      keyarea[ID_SIZE+1];
  sve      *sveptr;
  logical   term = NO;

BEGINSEQ
  if ( !vtext )                                      ERROR
  if ( !(sveptr = GetEntry(gvtxstb(keyarea,vnames,ID_SIZE))) )   
  {
    if ( !sveladd(vnames,vtext) )                    ERROR
  }
  else
    if ( sveptr->sveupd(vtext) )                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return (term);

}

/******************************************************************************/
/**
\brief  svelupd

\return vtext

\param  vnames
\param  vtext
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "svelupd"

char *svel :: svelupd (char *vnames, char *vtext )
{
  char      keyarea[ID_SIZE+1];
  sve      *sveptr;

BEGINSEQ
  if ( !(sveptr = sveleget(vnames)) )                ERROR
  if ( svelset(vnames,vtext) )                       ERROR
  sveptr = GetEntry(gvtxstb(keyarea,vnames,ID_SIZE));
RECOVER
  sveptr = NULL;
ENDSEQ
  return ( sveptr ? sveptr->svetextg().bdsagt() : NULL );

}

/******************************************************************************/
/**
\brief  ~svel


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~svel"

     svel :: ~svel ( )
{
  sve      *sveptr;
  short     indx = 0;

  DisconnectAll(NULL);
  DisconnectUpper();
  
  while ( sveptr = GetEntry(++indx) )
    sveptr->svetextg().bdsfree();

  delete svelpini;
  svelpini = NULL;

}


