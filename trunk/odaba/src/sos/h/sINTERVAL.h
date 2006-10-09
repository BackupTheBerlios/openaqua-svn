/*******************************************************************/
/*                         I N T E R V A L L                       */
/*                         Class Declaration                       */
/*   Version 2.0                                          06.04.95 */
/*******************************************************************/

#ifndef   INTERVAL_HPP
#define   INTERVAL_HPP

#define   INTERVAL(p_type)     tc_interval<p_type>
#define   INTERVAL_dcl(p_type)

template <class p_type> class tc_interval
{
  protected:
    p_type       low;
    p_type       high;

  public:
    logical      IsInside       (p_type value)
                                { return ( low < value && value < high ); }
    logical      IsOutside      (p_type value)
                                { return ( high < value || value < low ); }
    logical      IsValid        ()
                                { return ( low <= high ); }
    logical      Overlapp       (tc_interval &interval)
                                {
                               	  return (
                               	    !(
                               	      interval.get_low()  > high ||
                                      interval.get_high() < low
                                    )
                                  );
                                }

                 tc_interval    (){}
                 tc_interval    (p_type lval, p_type hval) :
                                  low(lval), high(hval)
                                {}

    void         set_low        (p_type &value)
                                { low  = value; }
    void         set_high       (p_type &value)
                                { high = value; }

    p_type     & get_low        ()
                                { return(low); }
    p_type     & get_high       ()
                                { return(high); }
};

#endif
