 /*******************************************************************/
 /*  SRTCMP                              of 06.03.92  ReiNa         */
 /*                                                                 */
 /*  FUNCTION                                                       */
 /*             - Compares Keys in SRT Tables                       */
 /*  VALUE                                                          */
 /*                                                                 */
 /*    cmpval   - compare value (-1,0,1)             - int          */
 /*               0 - error                                         */
 /*                                                                 */
 /*  PARAMETER                                                      */
 /*                                                                 */
 /*    entry1   - first entry to be compared     - I - *void(*)     */
 /*    entry2   - second entry to be compared    - I - *void(*)     */
 /*                                                                 */
 /*  SUB-FUNCTIONS                                                  */
 /*                                                                 */
 /*  NOTES                                                          */
 /*                                                                 */
 /*    The external pointer to SRT table c_srtpt has to be set      */
 /*                                                                 */
 /*******************************************************************/

#include  <pdefault.h>
#include  <ssrt.hpp>
#include  <ckeycmp.h>

#undef     MOD_ID
#define    MOD_ID  "srtcmp"

srt        *c_srtpt;

int __far __cdecl  srtcmp  ( const void *entry1, const void *entry2) 
{
  return(c_srtpt->Compare(entry1,entry2));
}


