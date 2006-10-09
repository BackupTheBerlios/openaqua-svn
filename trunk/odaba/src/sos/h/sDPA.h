/*******************************************************************/
/*                         D P A                                   */
/*                         Generic Class Declaration               */
/*   Version 0.1                                          03.09.92 */
/*******************************************************************/

#ifndef   DP_ARRAY_HPP
#define   DP_ARRAY_HPP

#include  <sPtrArray.hpp>

#define   DPA(itp)     tc_dpa<itp>
#define   DPA_dcl(itp)

template <class itp> class tc_dpa :
  public PtrArray
{
  public:
    itp       *& ElementAt      (int indx0)
                                { return( (itp *&)PtrArray::ElementAt(indx0) ); }
    itp       *& operator[]     (int indx0)
                                { return( (itp *&)PtrArray::ElementAt(indx0) ); }
    itp       *  GetAt          (int indx0) const
                                { return( (itp *)PtrArray::GetAt(indx0) ); }
    itp       *  GetLast        () const
                                { return( (itp *)PtrArray::GetLast() ); }
    void         SetAtGrow      (int indx0, itp *entptr)
                                { PtrArray::SetAtGrow(indx0, (void *)entptr); }
    int          Add            (itp *entptr)
                                { return( PtrArray::Add((void *)entptr)); }
    int          Add            ()
                                { return( PtrArray::Add((void *)new itp())); }
    int          InsertAt       (int indx0)
                                {
                                  PtrArray::InsertAt(indx0,(void *)new itp());
                                  return(indx0);
                                }
    void         InsertAt       (int indx0, itp *entptr )
                                { PtrArray::InsertAt(indx0,(void *)entptr);}
    void         InsertAt       (int indx0, tc_dpa *dpaptr)
                                { PtrArray::InsertAt(indx0,(void *)dpaptr); }
    void         Clear          (void)
                                { PtrArray::Clear(); }

                 tc_dpa           (int size=0 ) :
                                  PtrArray(size)
                                {}
                ~tc_dpa           () {}
};

#endif



