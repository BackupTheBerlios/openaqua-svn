/*******************************************************************/
/*                         D L L                                   */
/*                         Generic Class Declaration               */
/*   Version 0.1                                          18.03.97 */
/*******************************************************************/

#ifndef   DL_LIST_HPP
#define   DL_LIST_HPP

#include  <afxcolli.h>
#include  <sQuList.hpp>

#define   DLL(itp)     tc_dll<itp>
#define   DLL_dcl(itp)

template <class itp> class tc_dll :
  public  QuList
{
  public:
    void         AddHead        (itp * entptr)
                                { QuList::AddHead((void *)entptr); }
    void         AddTail        (itp * entptr)
                                { QuList::AddTail((void *)entptr); }
    int          FindIndex      (int indx0)
                                { return(QuList::FindIndex(indx0)); }
    int          Find           (itp * entptr)
                                { return(QuList::Find((void *)entptr)); }
    itp       *& GetObjectInst  (int indx0)
                                { return((itp *&)QuList::GetObjectInst(indx0)); }
    int          GetPosition    (itp *entptr)
                                { return(QuList::GetPosition((void *)entptr)); }
    itp       *& Get            (int indx0)
                                { return( (itp *&)QuList::Get(indx0) ); }
    itp       *& GetAt          ()
                                { return( (itp *&)QuList::GetAt() ); }
    int          GetCount       ()
                                { return(QuList::GetCount()); }
    itp       *& GetHead        ()
                                { return( (itp *&)QuList::GetHead() ); }
    itp       *& GetNext        ()
                                { return( (itp *&)QuList::GetNext() ); }
    itp       *& GetPrev        ()
                                { return( (itp *&)QuList::GetPrev() ); }
    itp       *& GetTail        ()
                                { return( (itp *&)QuList::GetTail() ); }
    void         GoBottom       ()
                                { QuList::GoBottom(); }
    void         GoTop          ()
                                { QuList::GoTop(); }
    void         InsertAfter    (itp *entptr)
                                { QuList::InsertAfter((void *)entptr);  }
    void         InsertBefore   (itp *entptr)
                                { QuList::InsertBefore((void *)entptr); }
    void         Insert         (itp *entptr,int indx0)
                                { QuList::Insert((void *)entptr,indx0); }
    itp       *  Remove         (int indx0)
                                { return( (itp *)QuList::Remove(indx0) ); }
    itp       *  Remove         (itp *entptr)
                                { return( (itp *)QuList::Remove(entptr) ); }
    itp       *  RemoveAt       ()
                                { return( (itp *)QuList::RemoveAt() ); }
    itp       *  RemoveHead     ()
                                { return( (itp *)QuList::RemoveHead() ); }
    itp       *  RemoveTail     ()
                                { return( (itp *)QuList::RemoveTail() ); }
    void         SetAt          (itp *entptr)
                                { QuList::SetAt((void *)entptr);   }

    itp      *  operator()      (int indx0)
                                { return( (itp *&)QuList::Get(indx0) ); }
    tc_dll   &  operator=       (tc_dll &rlist)
                                { return( (tc_dll &)QuList::operator=((QuList &)rlist) ); }

                 tc_dll         () :
                                  QuList()
                                {}
                 tc_dll         (tc_dll &rlist) :
                                  QuList((QuList &)rlist)
                                {}
                 tc_dll         (int16 buffcount) :
                                  QuList(buffcount)
                                {}
                ~tc_dll         () {}
};

#endif
