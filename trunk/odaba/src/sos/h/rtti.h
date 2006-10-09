#ifndef __RTTI_H__ 
#define __RTTI_H__

#define CRTTI const RTTIClassInfo*
#define PTR_CAST(T,p) ((p) ? \
  (T*) (p)->RTTI_Cast(STATIC_CLASS_INFO(T)) : 0)

#define CONST_PTR_CAST(T,p) ((p) ? \
  (const T*) ((T*)p)->RTTI_Cast(STATIC_CLASS_INFO(T)) : 0)

#define PTR_INHERITS(T,p) ((p) ? \
  CLASS_INFO(p)->Inherits(STATIC_CLASS_INFO(T)) : 1)

#define CLASS_INFO(p) ((p) ? (p)->RTTI_ClassInfo() : 0)

#define STATIC_CLASS_INFO(T) T::RTTI_StaticClassInfo()

#define DYNAMIC_CREATE(T,I) \
  (T*) I::Create( STATIC_CLASS_INFO(T) )

#define DYNAMIC_REPLICATE(T,p) ((p) ? \
  (T*) (p)->RTTI_ClassInfo()->Replicate( \
         STATIC_CLASS_INFO(T), p ) : 0);

#define TYPE_DATA \
private: \
  static const RTTIClassInfo RTTI_classInfo; \
  static void* RTTI_Create(); \
  static void* RTTI_Replicate( const void* ); \
public: \
  virtual void* RTTI_Cast( CRTTI c ); \
  static void* RTTI_StaticCast( void* ths, CRTTI c ); \
  virtual CRTTI RTTI_ClassInfo() const \
  { \
    return &RTTI_classInfo; \
  } \
  static CRTTI RTTI_StaticClassInfo() \
  { \
    return &RTTI_classInfo; \
  }

#include <srttici.hpp>

#endif  // __RTTI_H__

