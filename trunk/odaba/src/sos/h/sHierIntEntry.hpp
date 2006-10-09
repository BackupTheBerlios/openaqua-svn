/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    HierIntEntry

\brief    Hierarchie Interval Entry
          The  interval  entry  describes  the  upper  and lower boundery of the
          interval.  High  and  low  value  are  included  in  the interval. The
          interval  can  be  an  exclusive  or  an  inclusive  interval.  It  is
          associated  with  an  sub-intervall  list  that  contains  a  list  of
          inclusions  ( if  the interval  is exclusive)  or a list of exclusions
          (if teh interval is inclusive).

\date     $Date: 2006/03/12 19:20:02,64 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   HierIntEntry_HPP
#define   HierIntEntry_HPP

class     HierIntEntry;

class     HierarchicalIntervall;
#pragma pack(8)

class  HierIntEntry
{
protected  :         char                                         low[40];                                                   //
public     :         char                                         high[40];                                                  //
protected  :         HierarchicalIntervall                       *sub_list;                                                  //

public     :
                     char                                        *get_low() { return(low); }
public     :                                                             HierIntEntry (char *rule, logical exclude=NO );
public     :                                                             HierIntEntry ( );
public     :                                     logical Includes (char *string, logical exclude=NO );
public     :                                                             ~HierIntEntry ( );
};

#pragma pack()
#endif
