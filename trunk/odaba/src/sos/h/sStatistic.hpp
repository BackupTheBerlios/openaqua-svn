/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    Statistic

\brief    


\date     $Date: 2006/03/12 19:20:17,51 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Statistic_HPP
#define   Statistic_HPP

class     Statistic;

#include  <sStatistic.hpp>
#pragma pack(8)

class  Statistic
{
protected  :         uint32                                       calls;                                                     //
protected  :         int64                                        start_time;                                                //
protected  :         int64                                        exectim;                                                   //
protected  :         int64                                        total_time;                                                //
protected  :         int64                                        perf_freq;                                                 //
protected  :         int64                                        max_time;                                                  //
protected  :         int64                                        min_time;                                                  //
protected  :         int32                                        use_count;                                                 //

public     :
                     uint32                                       get_calls() { return(calls); }
                     int64                                        get_start_time() { return(start_time); }
                     int64                                        get_exectim() { return(exectim); }
                     int64                                        get_total_time() { return(total_time); }
                     int64                                        get_perf_freq() { return(perf_freq); }
                     int64                                        get_max_time() { return(max_time); }
                     int64                                        get_min_time() { return(min_time); }
                     int32                                        get_use_count() { return(use_count); }
public     :         SOS7ImpExp                  char *GetCalls ( );
public     :         SOS7ImpExp                  char *GetMaxTime ( );
public     :         SOS7ImpExp                  char *GetMinTime ( );
public     :         SOS7ImpExp                  char *GetOutput (char *objecttype, logical head_line=NO );
public     :         SOS7ImpExp                  char *GetTime (int64 u_time, int32 factor );
public     :         SOS7ImpExp                  uint32 GetTimeLong (int64 u_time, int32 factor );
public     :         SOS7ImpExp                  char *GetTotalTime ( );
public     :         SOS7ImpExp                  void Initialize ( );
public     :         SOS7ImpExp                  logical IsStarted ( );
public     :         SOS7ImpExp                  logical Print (char *objecttype, logical head_line=NO );
public     :         SOS7ImpExp                  void Start ( );
public     :         SOS7ImpExp                                          Statistic ( );
public     :         SOS7ImpExp                  void Stop ( );
public     :         SOS7ImpExp                  void TraceMessage (char *objecttype, logical head_line=NO );
public     :         SOS7ImpExp                  Statistic &operator+= (Statistic &ref_statistic );
public     :         SOS7ImpExp                                          ~Statistic ( );
};

#pragma pack()
#endif
