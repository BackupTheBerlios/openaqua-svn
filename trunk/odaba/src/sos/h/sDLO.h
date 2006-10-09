/*******************************************************************/
/*                         D L L                                   */
/*                         Generic Class Declaration               */
/*   Version 0.1                                          18.03.97 */
/*******************************************************************/

#ifndef   DLO_LIST_HPP
#define   DLO_LIST_HPP

#include  <afxcolli.h>
#include  <sXList.hpp>

#define   DLO(itp)     tc_dlo<itp>
#define   DLO_dcl(itp)

template <class itp> class tc_dlo :
  public  XList
{
  public:
    void         AddHead        (itp * entptr)
                                { XList::AddHead((void *)entptr); }
    void         AddTail        (itp * entptr)
                                { XList::AddTail((void *)entptr); }
    int          FindIndex      (int indx0)
                                { return(XList::FindIndex(indx0)); }
    int          Find           (itp * entptr)
                                { return(XList::Find((void *)entptr)); }
    itp       *& GetObjectInst  (int indx0)
                                { return((itp *&)XList::GetObjectInst(indx0)); }
    int          GetPosition    (itp *entptr)
                                { return(XList::GetPosition((void *)entptr)); }
    itp       *& Get            (int indx0)
                                { return( (itp *&)XList::Get(indx0) ); }
    itp       *& GetAt          ()
                                { return( (itp *&)XList::GetAt() ); }
    int          GetCount       ()
                                { return(XList::GetCount()); }
    itp       *& GetHead        ()
                                { return( (itp *&)XList::GetHead() ); }
    itp       *& GetNext        ()
                                { return( (itp *&)XList::GetNext() ); }
    itp       *& GetPrev        ()
                                { return( (itp *&)XList::GetPrev() ); }
    itp       *& GetTail        ()
                                { return( (itp *&)XList::GetTail() ); }
    void         GoBottom       ()
                                { XList::GoBottom(); }
    void         GoTop          ()
                                { XList::GoTop(); }
    void         InsertAfter    (itp *entptr)
                                { XList::InsertAfter((void *)entptr);  }
    void         InsertBefore   (itp *entptr)
                                { XList::InsertBefore((void *)entptr); }
    void         Insert         (itp *entptr,int indx0)
                                { XList::Insert((void *)entptr,indx0); }
    itp       *  Remove         (int indx0)
                                { return( (itp *)XList::Remove(indx0) ); }
    itp       *  Remove         (itp *entptr)
                                { return( (itp *)XList::Remove(entptr) ); }
    itp       *  RemoveAt       ()
                                { return( (itp *)XList::RemoveAt() ); }
    itp       *  RemoveHead     ()
                                { return( (itp *)XList::RemoveHead() ); }
    itp       *  RemoveTail     ()
                                { return( (itp *)XList::RemoveTail() ); }
    void         SetAt          (itp *entptr)
                                { XList::SetAt((void *)entptr);   }

    itp      *  operator()      (int indx0)
                                { return( (itp *&)XList::Get(indx0) ); }
    tc_dlo   &  operator=       (tc_dlo &rlist)
                                { return( (tc_dlo &)XList::operator=((XList &)rlist) ); }

                 tc_dlo         () :
                                  XList()
                                {}
                 tc_dlo         (tc_dlo &rlist) :
                                  XList((XList &)rlist)
                                {}
                 tc_dlo         (int16 buffcount) :
                                  XList(buffcount)
                                {}
                ~tc_dlo         () {}
};

#endif
