/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    ODE_SearchReplace

\brief    


\date     $Date: 2006/03/12 19:36:09,26 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODE_SearchReplace_HPP
#define   ODE_SearchReplace_HPP

class     ODE_SearchReplace;

#include  <sDictionaryHandle.hpp>
#include  <sPropertyHandle.hpp>
class  ODE_SearchReplace :public PropertyHandle
{
protected  :         DictionaryHandle                             dictionary;                                                
protected  :         PropertyHandle                               search_string;                                             
protected  :         PropertyHandle                               replace_string;                                            
protected  :         PropertyHandle                               location;                                                  
protected  :         PropertyHandle                               replace;                                                   
protected  :         PropertyHandle                               replace_all;                                               
protected  :         PropertyHandle                               backwards;                                                 
protected  :         PropertyHandle                               case_sensitive;                                            
protected  :         PropertyHandle                               is_regex;                                                  

public     :
                     PropertyHandle                              &get_search_string() { return(search_string); }
                     PropertyHandle                              &get_replace_string() { return(replace_string); }
                     PropertyHandle                              &get_location() { return(location); }
                     PropertyHandle                              &get_replace() { return(replace); }
                     PropertyHandle                              &get_replace_all() { return(replace_all); }
                     PropertyHandle                              &get_backwards() { return(backwards); }
                     PropertyHandle                              &get_case_sensitive() { return(case_sensitive); }
                     PropertyHandle                              &get_is_regex() { return(is_regex); }
public     :                                     void ClosePHs ( );
public     :                                     void Deinit ( );
public     :                                     logical GetCaseSensitive ( );
public     :                                     logical GetData (char *scope, logical do_replace, CTX_GUIBase *ctxptr );
public     :                                     int32 GetLocation ( );
public     :                                     logical GetReplace ( );
public     :                                     logical GetReplaceAll ( );
public     :                                     char *GetReplaceString ( );
public     :                                     char *GetSearchString ( );
public     :                                     void Init (DictionaryHandle &dict_handle );
public     :                                     logical Initialize (char *scope, logical do_replace );
public     :                                     logical IsRegExp ( );
public     :                                                             ODE_SearchReplace ( );
public     :                                     logical OpenPHs ( );
public     :                                     void SetReplaceAll (logical do_replace );
public     :                                                             ~ODE_SearchReplace ( );
};

#endif
