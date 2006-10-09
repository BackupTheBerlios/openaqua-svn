/*******************************************************************/
/*                           O P I 2                               */
/*         Project Includes - General Defines and Error Class      */
/*   Version 2.1                                          10.01.97 */
/*******************************************************************/

#ifndef   ODABA2_60_COMP
#define   ODABA2_60_COMP

#define   MEMO            mem

class     DictionaryHandle;
class     DatabaseHandle;
class     DBObjectHandle;

#define   UtilityCB       UtilityHandle
#define   intUtilityCB    CSUtilityHandle

#define   DictionaryHdl   DictionaryHandle
#define   DatabaseHdl     DatabaseHandle
#define   DBObjectHdl     DBObjectHandle

#define   DBField         PropertyHandle
#define   pib             PropertyHandle

#define  GetPIPointer     GetPropertyHandle
#define  GetHighPIPointer GetParentProperty

#define   sdbuptr         UtilityControlBlock()


#endif    // ODABA2_60_COMP

