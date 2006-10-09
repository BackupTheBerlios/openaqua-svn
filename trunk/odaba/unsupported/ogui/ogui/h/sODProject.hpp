/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODProject

\brief    GUI project
          The  GUI project contains the project resources as sub-applications or
          dictionary and database.

\date     $Date: 2006/03/13 21:33:52,68 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODProject_HPP
#define   ODProject_HPP

class     ODProject;

class     ODControl;
#include  <sDictionaryHandle.hpp>
#include  <sODApplication.hpp>
class  ODProject :public ODApplication
{
protected  :         DictionaryHandle                             dictionary;                                                //

public     :
                     DictionaryHandle                            &get_dictionary() { return(dictionary); }
public     :         OGUI7ImpExp                                         ODProject (ODControl *pODControl, char *names );
public     :         OGUI7ImpExp                 logical SetDictionary (DictionaryHandle &dict_handle );
public     :         OGUI7ImpExp                 logical SetDictionary (char *dict_path, PIACC accmode );
public     :         OGUI7ImpExp                                         ~ODProject ( );
};

#endif
