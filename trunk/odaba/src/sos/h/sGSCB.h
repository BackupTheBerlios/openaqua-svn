/*******************************************************************/
/*                       G S C B                                   */
/*                       Generic Class Declaration                 */
/*   Version 0.1                                          15.05.93 */
/*******************************************************************/

#ifndef   GSCB_HPP
#define   GSCB_HPP

class     sfcb;
class     smcb;
class     srt;

#include <sscb.hpp>

#define   GSCB(itp)  tc_gscb<itp, itp##l>
#define   scbfcbl   scbfcbg()

#define   GSCB_dcl(itp)

template <class itp, class itpl> class tc_gscb :
  public scb
{
  public:
    itpl      *  scbfcbg        ()
                                { return ((itpl *)scbfcb); }
    itp       *  GetEntry       (int16 indx)
                                {
                                  return (
                                    (itp *)( scbfcb
                                      ? scbfcb->GetEntry(indx)
                                      : NULL
                                    )
                                  );
                                }
    itp       *  GetEntry       (char *fldnames)
                                { return ((itp *)scbeg(fldnames)); }

                 tc_gscb          (smcb *smcbptr) :
                                  scb(smcbptr, sizeof(itp))
                                {}
                 tc_gscb          () {}
};

#endif

