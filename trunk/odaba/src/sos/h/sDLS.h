/*******************************************************************/
/*                         D L L                                   */
/*                         Generic Class Declaration               */
/*   Version 0.1                                          18.03.97 */
/*******************************************************************/

#ifndef   DL_LIST_HPP
#define   DL_LIST_HPP

#include  <sSList.hpp>

#define   DLS(itp)     tc_dls<itp>
#define   DLS_dcl(itp)

template <class itp> class tc_dls :
  public  SList
{
  public:
    void         AddHead        (itp * entptr)
                                { SList::AddHead((void *)entptr); }
    void         AddTail        (itp * entptr)
                                { SList::AddTail((void *)entptr); }
    int          FindIndex      (int indx0)
                                { return(SList::FindIndex(indx0)); }
    int          Find           (itp * entptr)
                                { return(SList::Find((void *)entptr)); }
    itp       *& GetObjectInst  (int indx0)
                                { return((itp *&)SList::GetObjectInst(indx0)); }
    int          GetPosition    (itp *entptr)
                                { return(SList::GetPosition((void *)entptr)); }
    itp       *& Get            (int indx0)
                                { return( (itp *&)SList::Get(indx0) ); }
    itp       *& GetAt          ()
                                { return( (itp *&)SList::GetAt() ); }
    int          GetCount       ()
                                { return(SList::GetCount()); }
    itp       *& GetHead        ()
                                { return( (itp *&)SList::GetHead() ); }
    itp       *& GetNext        ()
                                { return( (itp *&)SList::GetNext() ); }
    itp       *& GetPrev        ()
                                { return( (itp *&)SList::GetPrev() ); }
    itp       *& GetTail        ()
                                { return( (itp *&)SList::GetTail() ); }
    void         GoBottom       ()
                                { SList::GoBottom(); }
    void         GoTop          ()
                                { SList::GoTop(); }
    void         InsertAfter    (itp *entptr)
                                { SList::InsertAfter((void *)entptr);  }
    void         InsertBefore   (itp *entptr)
                                { SList::InsertBefore((void *)entptr); }
    void         Insert         (itp *entptr,int indx0)
                                { SList::Insert((void *)entptr,indx0); }
    itp       *  Remove         (int indx0)
                                { return( (itp *)SList::Remove(indx0) ); }
    itp       *  Remove         (itp *entptr)
                                { return( (itp *)SList::Remove(entptr) ); }
    itp       *  RemoveAt       ()
                                { return( (itp *)SList::RemoveAt() ); }
    itp       *  RemoveHead     ()
                                { return( (itp *)SList::RemoveHead() ); }
    itp       *  RemoveTail     ()
                                { return( (itp *)SList::RemoveTail() ); }
    void         SetAt          (itp *entptr)
                                { SList::SetAt((void *)entptr);   }

    itp      *  operator()      (int indx0)
                                { return( (itp *&)SList::Get(indx0) ); }
    tc_dls   &  operator=       (tc_dls &rlist)
                                { return( (tc_dls &)SList::operator=((SList &)rlist) ); }

                 tc_dls         () :
                                  SList()
                                {}
                 tc_dls         (tc_dls &rlist) :
                                  SList((SList &)rlist)
                                {}
                 tc_dls         (int16 buffcount) :
                                  SList(buffcount)
                                {}
                ~tc_dls         () {}
};

#endif
