/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/20|15:35:34,34}|(REF)
\class    sLanguageDependendBase

\brief    


\date     $Date: 2006/04/13 15:29:03,20 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sLanguageDependendBase_HPP
#define   sLanguageDependendBase_HPP

class     sLanguageDependendBase;

class  sLanguageDependendBase :public CTX_Structure
{
protected  :         PropertyHandle                              *languages;                                                 
protected  :         int                                          language;                                                  
protected  :         int                                          old_language;                                              

public     :
                     PropertyHandle                              *get_languages() { return(languages); }
                     int                                         &get_language() { return(language); }
                     int                                         &get_old_language() { return(old_language); }
public     : virtual                             logical DBCreated ( );
public     : virtual                             logical DBOpened ( );
public     : virtual                             logical DBRead ( );
public     : virtual                             logical SetLanguage ( );
public     :                                                             sLanguageDependendBase ( );
public     : virtual                                                     ~sLanguageDependendBase ( );
};

#endif
