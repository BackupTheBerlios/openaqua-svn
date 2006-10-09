/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    DSC_TopicDef

\brief    Topic definition
          The   topic   definition   provides   several   definition sections as
          description   or   examples.   Each   topic   definition   has a title
          introducing the detail described by means of a topic.

\date     $Date: 2006/03/13 21:30:07,31 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DSC_TopicDef_HPP
#define   DSC_TopicDef_HPP

class     DSC_TopicDef;

#include  <cLanguage.h>
#include  <sDSC_Description.hpp>
#pragma pack(8)

class  DSC_TopicDef
{
protected  :         Language                                     language;                                                  // Language for Names and Labels
protected  :         char                                         label[41];                                                 // Topic label
protected  :         DSC_Description                              definition;                                                // Topic definition
protected  :         PI(mem)                                      name;                                                      // Topic title
protected  :         PI(DSC_Notes)                                notes;                                                     //

public     :
                     Language                                     get_language() { return(language); }
                     char                                        *get_label() { return(label); }
                     DSC_Description                             &get_definition() { return(definition); }
                     PI(mem)                                     &get_name() { return(name); }
                     PI(DSC_Notes)                               &get_notes() { return(notes); }
};

#pragma pack()
#endif
