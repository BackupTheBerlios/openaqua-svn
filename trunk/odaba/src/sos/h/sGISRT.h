/*******************************************************************/
/*                        G I S R T                                */
/*                        Generic Class Declaration                */
/*   Version 0.1                                          26.05.92 */
/*******************************************************************/

#ifndef   GISRT_HPP
#define   GISRT_HPP

#include  <sisrt.hpp>          // Sorted Table

#define   GISRT(itp)     tc_gisrt<itp>
#define   GISRT_dcl(itp)

template <class itp> class tc_gisrt :
  public  isrt
{
  public:
    itp       *  Get            (uint32 ident)  const
                                { return ((itp *)isrt::Get(ident)); }
    itp       *  GetObjectInst  (int16 indx)   const
                                { return ((itp *)isrt::GetObjectInst(indx)); }
    itp       *  Remove         (uint32 ident)
                                { return ((itp *)isrt::Remove(ident)); }
    uint32       GetItemID      (itp *objptr)
                                { return (isrt::GetItemID((void *)objptr)); }
    uint32       GetItemID      (uint16 indx)
                                { return (isrt::GetItemID(indx)); }
    uint32       Insert         (itp *objptr)
                                { return (isrt::Insert((void *)objptr)); }
    uint32       Insert         (uint32 ident, itp *objptr)
                                { return (isrt::Insert(ident,(void *)objptr)); }
    void         DeleteEntries  ()
                                {
                                  int16 indx = GetCount();
                                  itp  *objptr;
                                  while ( indx )
                                    if ( objptr = (itp *)((isrt_entry *)GetEntry(indx--))->datarea )
                                      delete objptr;
                                }

                 tc_gisrt       (int16 maxe = 16) :
                                  isrt(maxe)
                                {}
};

#endif
