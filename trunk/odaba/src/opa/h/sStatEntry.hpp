/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    StatEntry

\brief    


\date     $Date: 2006/03/12 19:13:53,31 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   StatEntry_HPP
#define   StatEntry_HPP

class     StatEntry;

class     acb;
class     eb_MainBase;
#pragma pack(8)

class  StatEntry
{
protected  :         uint32                                       inst_count;                                                
protected  :         uint32                                       inst_size;                                                 
protected  :         uint32                                       index_count;                                               
protected  :         uint32                                       index_size;                                                
protected  :         uint32                                       del_count;                                                 
protected  :         uint32                                       del_size;                                                  
protected  :         uint32                                       del_index_count;                                           
protected  :         uint32                                       del_index_size;                                            
protected  :         uint32                                       hist_count;                                                
protected  :         uint32                                       hist_size;                                                 

public     :
                     uint32                                       get_inst_count() { return(inst_count); }
                     uint32                                       get_inst_size() { return(inst_size); }
                     uint32                                       get_index_count() { return(index_count); }
                     uint32                                       get_index_size() { return(index_size); }
                     uint32                                       get_del_count() { return(del_count); }
                     uint32                                       get_del_size() { return(del_size); }
                     uint32                                       get_del_index_count() { return(del_index_count); }
                     uint32                                       get_del_index_size() { return(del_index_size); }
                     uint32                                       get_hist_count() { return(hist_count); }
                     uint32                                       get_hist_size() { return(hist_size); }
public     :                                     logical IsEmpty ( );
public     :                                     logical Print (FILE *statfile, char *line );
public     :                                                             StatEntry ( );
public     :                                     logical Update (acb *acbptr, uint32 hcount, uint32 hsize );
public     :                                     StatEntry &operator+= (StatEntry &st_entry );
};

#pragma pack()
#endif
