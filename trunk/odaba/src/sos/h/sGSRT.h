/*******************************************************************/
/*                         G S R T                                 */
/*                         Class Declaration                       */
/*   Version 0.1                                          26.05.03 */
/*******************************************************************/ 

#ifndef   GSRT_HPP
#define   GSRT_HPP

#include  <ssrt.hpp>       // Sorted Table                  

#define   GSRT(itp)  tc_gsrt<itp>

#define   GSRT_dcl(itp)

template <class itp> class tc_gsrt :
  public  srt
{
 public:  

  itp         *AddFreeEntry    ( ) { return ((itp *)srtfad()); } 
  int32        AddEntry        ( itp *datarea) 
                                  { return (srtkad(datarea)); }   
  int          AddEntry        ( int32 indx, itp *datarea)        
                                  { return (srtiad(indx,datarea)); }  
  void         Clear           ( )                                    
                                  { srtres(); }  
  int          DeleteEntry     ( int32 indx)      
                                  { return (srtidl(indx)); }      
  int32        FindEntry       ( void *skey )
                                  { return (srtssr(skey)); }
  int          SortTable       ( int16 kpos, int16 klen, char ktype) 
                                  { return (srtsor(kpos,klen,ktype)); }
  int32        GetCount        ( ) { return (srtcnt()); }
  itp         *GetEntry        ( int32 indx)
                                  { return ((itp *)srtigt(indx)); }
  itp         *GetEntry        ( void *skey )
                                  { return ((itp *)srtigt(srtssr(skey))); }
  int16        GetEntryLength  ( ) { return (srtlen()); }
  itp         *GetFreeEntry    ( ) { return ((itp *)srtfgt()); }
  int16        GetKeyLength    ( ) { return (srtkln()); }
  void        *GetPool         ( ) { return (srtpool()); }
  itp         *GetTable        ( ) { return ((itp *)srttbl()); }
  itp         *UpdateEntry     ( itp *datarea, int32 indx)
                                  { return ((itp *)srtiup(datarea,indx)); }
  void         SetTable        ( itp *tblptr)
                                  { srtsett(tblptr); }
  void*        srtpool(){return NULL;}
               tc_gsrt         ( ) {} 
               tc_gsrt         ( int32 maxe, 
                                 int16 elen, int16 klen,
                                 int16 kpos, char ktype, logical expand)
                               : srt(maxe,elen,klen,kpos,ktype,expand)
                               {}  
               tc_gsrt       ( int32 ecnt, 
                                 int16 elen, int16 klen,
                                 int16 kpos, char ktype, itp *table,
                                 logical expand)
                               : srt(ecnt,elen,klen,kpos,ktype,
                                     (char *)table,expand)
                               {}
};
#endif
