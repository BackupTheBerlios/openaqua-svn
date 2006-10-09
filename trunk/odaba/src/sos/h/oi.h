#ifndef __OI_H__ 
#define __OI_H__

#include <sObjectInfo.hpp>
#define OI_CAST(T,p) ((T*) ObjectInfo::StaticCast(p,#T))

#endif  // __OI_H__