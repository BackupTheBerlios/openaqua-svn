/*******************************************************************/
/*                         D L L                                   */
/*                         Generic Class Declaration               */
/*   Version 0.1                                          18.03.97 */
/*******************************************************************/

#ifndef   BT_ITER_HPP
#define   BT_ITER_HPP

#include  <afxcolli.h>
#include  <sBTIterator.hpp>

#define   BTI(itp)     tc_bti<itp>
#define   BTI_dcl(itp)

template <class itp> class tc_bti :
  public  BTIterator
{
  public:
    itp       *  Get            (int indx0)
                                { return( (itp *)BTIterator::Get(indx0) ); }
    itp       *  Get            (char *key_value, logical exact)
                                { return( (itp *)BTIterator::Get(key_value,exact) ); }
    itp       *  GetAt          ()
                                { return( (itp *)BTIterator::GetAt() ); }
    itp       *  GetHead        ()
                                { return( (itp *)BTIterator::GetHead() ); }
    itp       *  GetNext        ()
                                { return( (itp *)BTIterator::GetNext() ); }
    itp       *  GetPrevious    ()
                                { return( (itp *)BTIterator::GetPrevious() ); }
    itp       *  GetTail        ()
                                { return( (itp *)BTIterator::GetTail() ); }
    logical      Insert         (itp *entptr)
                                { return( BTIterator::Insert((void *)entptr) ); }
    logical      Insert         (char *key_value)
                                { return( BTIterator::Insert(key_value) ); }
    itp       *  Remove         (itp *entptr)
                                { return( (itp *)BTIterator::Remove((void *)entptr) ); }
    itp       *  Remove         (int indx0)
                                { return( (itp *)BTIterator::Remove(indx0) ); }
    itp       *  Remove         (char *key_value)
                                { return( (itp *)BTIterator::Remove(key_value) ); }
    itp       *  RemoveAt       ()
                                { return( (itp *)BTIterator::RemoveAt() ); }
    itp       *  RemoveHead     ()
                                { return( (itp *)BTIterator::RemoveHead() ); }
    itp       *  RemoveTail     ()
                                { return( (itp *)BTIterator::RemoveTail() ); }

    tc_bti   &  operator++      ( )
                                { BTIterator::operator++(); return((tc_bti) &(*this)); }
    tc_bti   &  operator--      ( )
                                { BTIterator::operator--(); return((tc_bti) &(*this)); }
    itp      *  operator->      ( )
                                { return( (itp *)BTIterator::GetAt() ); }
    itp      *  operator()      (int indx0)
                                { return( (itp *)BTIterator::Get(indx0) ); }
    itp      *  operator()      (char *key_value)
                                { return( (itp *)BTIterator::Get(key_value) ); }
    tc_bti   &  operator=       (tc_bti &rlist)
                                { SetTree(rlist.get_tree()); return((tc_bti) &(*this)); }

                 tc_bti         () :
                                  BTIterator(NULL)
                                {}
                 tc_bti         (tc_bti &rlist) :
                                  BTIterator(rlist.get_tree())
                                {}
                 tc_bti         (BinTree *btree) :
                                  BTIterator(btree)
                                {}
                ~tc_bti         () {}
};

#endif
