/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    DSC_Topic

\brief    Title
          Topics  are  used  to  refer  to details that are defined in a certain
          context.  In  contrast  to  concepts  and terms that are more abstract
          topics  describe details as part of  a whole. While "Person" defines a
          concept,  "Anthon Miller" would be described as a detail. Thus, topics
          usually  describe concrete things (concrete  is always relative to the
          concepts the detail belongs to).

\date     $Date: 2006/03/13 21:30:07,18 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DSC_Topic_HPP
#define   DSC_Topic_HPP

class     DSC_Topic;

#ifndef   P_DSC_Concept_HPP
#define   P_DSC_Concept_HPP
#include  <sPI.hpp>
class       DSC_Concept;
PI_dcl     (DSC_Concept)
#endif
#ifndef   P_DSC_Topic_HPP
#define   P_DSC_Topic_HPP
#include  <sPI.hpp>
class       DSC_Topic;
PI_dcl     (DSC_Topic)
#endif
#ifndef   P_SDB_Resource_HPP
#define   P_SDB_Resource_HPP
#include  <sPI.hpp>
class       SDB_Resource;
PI_dcl     (SDB_Resource)
#endif
#include  <sDSC_TopicDef.hpp>
#pragma pack(8)

class  DSC_Topic :public __OBJECT
{
protected  :         char                                         sys_ident[40] ATTR_ALIGN(4);                               // Topic name
protected  :         int32                                        __AUTOIDENT;                                               // Internal topic number
protected  :         DSC_TopicDef                                 definition;                                                // Topic definition
protected  :         logical                                      problem_relevant;                                          // Topic is of general interest
protected  :         PI(DSC_Topic)                                sub_topics;                                                // Sub-Topics for hierarchical definition
protected  :         PI(DSC_Concept)                              descriptors;                                               // Descriptors associated with the topic
protected  :         PI(DSC_Topic)                                references;                                                // References to other topics
protected  :         PI(DSC_Topic)                                referenced_in;                                             // Topics referring to this topic
protected  :         PI(SDB_ResourceRef)                          resources;                                                 // Resources described by this topic

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
                     int32                                        get___AUTOIDENT() { return(__AUTOIDENT); }
                     DSC_TopicDef                                &get_definition() { return(definition); }
                     logical                                      get_problem_relevant() { return(problem_relevant); }
                     PI(DSC_Topic)                               &get_sub_topics() { return(sub_topics); }
                     PI(DSC_Concept)                             &get_descriptors() { return(descriptors); }
                     PI(DSC_Topic)                               &get_references() { return(references); }
                     PI(DSC_Topic)                               &get_referenced_in() { return(referenced_in); }
                     PI(SDB_ResourceRef)                         &get_resources() { return(resources); }
};

#pragma pack()
#endif
