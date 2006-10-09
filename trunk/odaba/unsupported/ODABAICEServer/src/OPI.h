// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.0
// Generated from file `OPI.ice'

#ifndef __src__OPI_h__
#define __src__OPI_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <Ice/StreamF.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 301
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 < 0
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace OPI
{

class CheckOptions;
bool operator==(const CheckOptions&, const CheckOptions&);
bool operator!=(const CheckOptions&, const CheckOptions&);
bool operator<(const CheckOptions&, const CheckOptions&);
bool operator<=(const CheckOptions&, const CheckOptions&);
bool operator>(const CheckOptions&, const CheckOptions&);
bool operator>=(const CheckOptions&, const CheckOptions&);

class DBObjectHandle;
bool operator==(const DBObjectHandle&, const DBObjectHandle&);
bool operator!=(const DBObjectHandle&, const DBObjectHandle&);
bool operator<(const DBObjectHandle&, const DBObjectHandle&);
bool operator<=(const DBObjectHandle&, const DBObjectHandle&);
bool operator>(const DBObjectHandle&, const DBObjectHandle&);
bool operator>=(const DBObjectHandle&, const DBObjectHandle&);

class DataSourceHandle;
bool operator==(const DataSourceHandle&, const DataSourceHandle&);
bool operator!=(const DataSourceHandle&, const DataSourceHandle&);
bool operator<(const DataSourceHandle&, const DataSourceHandle&);
bool operator<=(const DataSourceHandle&, const DataSourceHandle&);
bool operator>(const DataSourceHandle&, const DataSourceHandle&);
bool operator>=(const DataSourceHandle&, const DataSourceHandle&);

class DatabaseHandle;
bool operator==(const DatabaseHandle&, const DatabaseHandle&);
bool operator!=(const DatabaseHandle&, const DatabaseHandle&);
bool operator<(const DatabaseHandle&, const DatabaseHandle&);
bool operator<=(const DatabaseHandle&, const DatabaseHandle&);
bool operator>(const DatabaseHandle&, const DatabaseHandle&);
bool operator>=(const DatabaseHandle&, const DatabaseHandle&);

class DictionaryHandle;
bool operator==(const DictionaryHandle&, const DictionaryHandle&);
bool operator!=(const DictionaryHandle&, const DictionaryHandle&);
bool operator<(const DictionaryHandle&, const DictionaryHandle&);
bool operator<=(const DictionaryHandle&, const DictionaryHandle&);
bool operator>(const DictionaryHandle&, const DictionaryHandle&);
bool operator>=(const DictionaryHandle&, const DictionaryHandle&);

class ODABAClient;
bool operator==(const ODABAClient&, const ODABAClient&);
bool operator!=(const ODABAClient&, const ODABAClient&);
bool operator<(const ODABAClient&, const ODABAClient&);
bool operator<=(const ODABAClient&, const ODABAClient&);
bool operator>(const ODABAClient&, const ODABAClient&);
bool operator>=(const ODABAClient&, const ODABAClient&);

class OperationHandle;
bool operator==(const OperationHandle&, const OperationHandle&);
bool operator!=(const OperationHandle&, const OperationHandle&);
bool operator<(const OperationHandle&, const OperationHandle&);
bool operator<=(const OperationHandle&, const OperationHandle&);
bool operator>(const OperationHandle&, const OperationHandle&);
bool operator>=(const OperationHandle&, const OperationHandle&);

class PropertyHandle;
bool operator==(const PropertyHandle&, const PropertyHandle&);
bool operator!=(const PropertyHandle&, const PropertyHandle&);
bool operator<(const PropertyHandle&, const PropertyHandle&);
bool operator<=(const PropertyHandle&, const PropertyHandle&);
bool operator>(const PropertyHandle&, const PropertyHandle&);
bool operator>=(const PropertyHandle&, const PropertyHandle&);

class OPIFactory;
bool operator==(const OPIFactory&, const OPIFactory&);
bool operator!=(const OPIFactory&, const OPIFactory&);
bool operator<(const OPIFactory&, const OPIFactory&);
bool operator<=(const OPIFactory&, const OPIFactory&);
bool operator>(const OPIFactory&, const OPIFactory&);
bool operator>=(const OPIFactory&, const OPIFactory&);

class Session;
bool operator==(const Session&, const Session&);
bool operator!=(const Session&, const Session&);
bool operator<(const Session&, const Session&);
bool operator<=(const Session&, const Session&);
bool operator>(const Session&, const Session&);
bool operator>=(const Session&, const Session&);

class SessionFactory;
bool operator==(const SessionFactory&, const SessionFactory&);
bool operator!=(const SessionFactory&, const SessionFactory&);
bool operator<(const SessionFactory&, const SessionFactory&);
bool operator<=(const SessionFactory&, const SessionFactory&);
bool operator>(const SessionFactory&, const SessionFactory&);
bool operator>=(const SessionFactory&, const SessionFactory&);

}

}

namespace OPI
{

class CheckOptions;
bool operator==(const CheckOptions&, const CheckOptions&);
bool operator!=(const CheckOptions&, const CheckOptions&);
bool operator<(const CheckOptions&, const CheckOptions&);
bool operator<=(const CheckOptions&, const CheckOptions&);
bool operator>(const CheckOptions&, const CheckOptions&);
bool operator>=(const CheckOptions&, const CheckOptions&);

class DBObjectHandle;
bool operator==(const DBObjectHandle&, const DBObjectHandle&);
bool operator!=(const DBObjectHandle&, const DBObjectHandle&);
bool operator<(const DBObjectHandle&, const DBObjectHandle&);
bool operator<=(const DBObjectHandle&, const DBObjectHandle&);
bool operator>(const DBObjectHandle&, const DBObjectHandle&);
bool operator>=(const DBObjectHandle&, const DBObjectHandle&);

class DataSourceHandle;
bool operator==(const DataSourceHandle&, const DataSourceHandle&);
bool operator!=(const DataSourceHandle&, const DataSourceHandle&);
bool operator<(const DataSourceHandle&, const DataSourceHandle&);
bool operator<=(const DataSourceHandle&, const DataSourceHandle&);
bool operator>(const DataSourceHandle&, const DataSourceHandle&);
bool operator>=(const DataSourceHandle&, const DataSourceHandle&);

class DatabaseHandle;
bool operator==(const DatabaseHandle&, const DatabaseHandle&);
bool operator!=(const DatabaseHandle&, const DatabaseHandle&);
bool operator<(const DatabaseHandle&, const DatabaseHandle&);
bool operator<=(const DatabaseHandle&, const DatabaseHandle&);
bool operator>(const DatabaseHandle&, const DatabaseHandle&);
bool operator>=(const DatabaseHandle&, const DatabaseHandle&);

class DictionaryHandle;
bool operator==(const DictionaryHandle&, const DictionaryHandle&);
bool operator!=(const DictionaryHandle&, const DictionaryHandle&);
bool operator<(const DictionaryHandle&, const DictionaryHandle&);
bool operator<=(const DictionaryHandle&, const DictionaryHandle&);
bool operator>(const DictionaryHandle&, const DictionaryHandle&);
bool operator>=(const DictionaryHandle&, const DictionaryHandle&);

class ODABAClient;
bool operator==(const ODABAClient&, const ODABAClient&);
bool operator!=(const ODABAClient&, const ODABAClient&);
bool operator<(const ODABAClient&, const ODABAClient&);
bool operator<=(const ODABAClient&, const ODABAClient&);
bool operator>(const ODABAClient&, const ODABAClient&);
bool operator>=(const ODABAClient&, const ODABAClient&);

class OperationHandle;
bool operator==(const OperationHandle&, const OperationHandle&);
bool operator!=(const OperationHandle&, const OperationHandle&);
bool operator<(const OperationHandle&, const OperationHandle&);
bool operator<=(const OperationHandle&, const OperationHandle&);
bool operator>(const OperationHandle&, const OperationHandle&);
bool operator>=(const OperationHandle&, const OperationHandle&);

class PropertyHandle;
bool operator==(const PropertyHandle&, const PropertyHandle&);
bool operator!=(const PropertyHandle&, const PropertyHandle&);
bool operator<(const PropertyHandle&, const PropertyHandle&);
bool operator<=(const PropertyHandle&, const PropertyHandle&);
bool operator>(const PropertyHandle&, const PropertyHandle&);
bool operator>=(const PropertyHandle&, const PropertyHandle&);

class OPIFactory;
bool operator==(const OPIFactory&, const OPIFactory&);
bool operator!=(const OPIFactory&, const OPIFactory&);
bool operator<(const OPIFactory&, const OPIFactory&);
bool operator<=(const OPIFactory&, const OPIFactory&);
bool operator>(const OPIFactory&, const OPIFactory&);
bool operator>=(const OPIFactory&, const OPIFactory&);

class Session;
bool operator==(const Session&, const Session&);
bool operator!=(const Session&, const Session&);
bool operator<(const Session&, const Session&);
bool operator<=(const Session&, const Session&);
bool operator>(const Session&, const Session&);
bool operator>=(const Session&, const Session&);

class SessionFactory;
bool operator==(const SessionFactory&, const SessionFactory&);
bool operator!=(const SessionFactory&, const SessionFactory&);
bool operator<(const SessionFactory&, const SessionFactory&);
bool operator<=(const SessionFactory&, const SessionFactory&);
bool operator>(const SessionFactory&, const SessionFactory&);
bool operator>=(const SessionFactory&, const SessionFactory&);

}

namespace IceInternal
{

void incRef(::OPI::CheckOptions*);
void decRef(::OPI::CheckOptions*);

void incRef(::IceProxy::OPI::CheckOptions*);
void decRef(::IceProxy::OPI::CheckOptions*);

void incRef(::OPI::DBObjectHandle*);
void decRef(::OPI::DBObjectHandle*);

void incRef(::IceProxy::OPI::DBObjectHandle*);
void decRef(::IceProxy::OPI::DBObjectHandle*);

void incRef(::OPI::DataSourceHandle*);
void decRef(::OPI::DataSourceHandle*);

void incRef(::IceProxy::OPI::DataSourceHandle*);
void decRef(::IceProxy::OPI::DataSourceHandle*);

void incRef(::OPI::DatabaseHandle*);
void decRef(::OPI::DatabaseHandle*);

void incRef(::IceProxy::OPI::DatabaseHandle*);
void decRef(::IceProxy::OPI::DatabaseHandle*);

void incRef(::OPI::DictionaryHandle*);
void decRef(::OPI::DictionaryHandle*);

void incRef(::IceProxy::OPI::DictionaryHandle*);
void decRef(::IceProxy::OPI::DictionaryHandle*);

void incRef(::OPI::ODABAClient*);
void decRef(::OPI::ODABAClient*);

void incRef(::IceProxy::OPI::ODABAClient*);
void decRef(::IceProxy::OPI::ODABAClient*);

void incRef(::OPI::OperationHandle*);
void decRef(::OPI::OperationHandle*);

void incRef(::IceProxy::OPI::OperationHandle*);
void decRef(::IceProxy::OPI::OperationHandle*);

void incRef(::OPI::PropertyHandle*);
void decRef(::OPI::PropertyHandle*);

void incRef(::IceProxy::OPI::PropertyHandle*);
void decRef(::IceProxy::OPI::PropertyHandle*);

void incRef(::OPI::OPIFactory*);
void decRef(::OPI::OPIFactory*);

void incRef(::IceProxy::OPI::OPIFactory*);
void decRef(::IceProxy::OPI::OPIFactory*);

void incRef(::OPI::Session*);
void decRef(::OPI::Session*);

void incRef(::IceProxy::OPI::Session*);
void decRef(::IceProxy::OPI::Session*);

void incRef(::OPI::SessionFactory*);
void decRef(::OPI::SessionFactory*);

void incRef(::IceProxy::OPI::SessionFactory*);
void decRef(::IceProxy::OPI::SessionFactory*);

}

namespace OPI
{

typedef ::IceInternal::Handle< ::OPI::CheckOptions> CheckOptionsPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::OPI::CheckOptions> CheckOptionsPrx;

void __write(::IceInternal::BasicStream*, const CheckOptionsPrx&);
void __read(::IceInternal::BasicStream*, CheckOptionsPrx&);
void __write(::IceInternal::BasicStream*, const CheckOptionsPtr&);
void __patch__CheckOptionsPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const CheckOptionsPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const CheckOptionsPtr&);
void __decRefUnsafe(CheckOptionsPtr&);
void __clearHandleUnsafe(CheckOptionsPtr&);

typedef ::IceInternal::Handle< ::OPI::DBObjectHandle> DBObjectHandlePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::OPI::DBObjectHandle> DBObjectHandlePrx;

void __write(::IceInternal::BasicStream*, const DBObjectHandlePrx&);
void __read(::IceInternal::BasicStream*, DBObjectHandlePrx&);
void __write(::IceInternal::BasicStream*, const DBObjectHandlePtr&);
void __patch__DBObjectHandlePtr(void*, ::Ice::ObjectPtr&);

void __addObject(const DBObjectHandlePtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const DBObjectHandlePtr&);
void __decRefUnsafe(DBObjectHandlePtr&);
void __clearHandleUnsafe(DBObjectHandlePtr&);

typedef ::IceInternal::Handle< ::OPI::DataSourceHandle> DataSourceHandlePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::OPI::DataSourceHandle> DataSourceHandlePrx;

void __write(::IceInternal::BasicStream*, const DataSourceHandlePrx&);
void __read(::IceInternal::BasicStream*, DataSourceHandlePrx&);
void __write(::IceInternal::BasicStream*, const DataSourceHandlePtr&);
void __patch__DataSourceHandlePtr(void*, ::Ice::ObjectPtr&);

void __addObject(const DataSourceHandlePtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const DataSourceHandlePtr&);
void __decRefUnsafe(DataSourceHandlePtr&);
void __clearHandleUnsafe(DataSourceHandlePtr&);

typedef ::IceInternal::Handle< ::OPI::DatabaseHandle> DatabaseHandlePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::OPI::DatabaseHandle> DatabaseHandlePrx;

void __write(::IceInternal::BasicStream*, const DatabaseHandlePrx&);
void __read(::IceInternal::BasicStream*, DatabaseHandlePrx&);
void __write(::IceInternal::BasicStream*, const DatabaseHandlePtr&);
void __patch__DatabaseHandlePtr(void*, ::Ice::ObjectPtr&);

void __addObject(const DatabaseHandlePtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const DatabaseHandlePtr&);
void __decRefUnsafe(DatabaseHandlePtr&);
void __clearHandleUnsafe(DatabaseHandlePtr&);

typedef ::IceInternal::Handle< ::OPI::DictionaryHandle> DictionaryHandlePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::OPI::DictionaryHandle> DictionaryHandlePrx;

void __write(::IceInternal::BasicStream*, const DictionaryHandlePrx&);
void __read(::IceInternal::BasicStream*, DictionaryHandlePrx&);
void __write(::IceInternal::BasicStream*, const DictionaryHandlePtr&);
void __patch__DictionaryHandlePtr(void*, ::Ice::ObjectPtr&);

void __addObject(const DictionaryHandlePtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const DictionaryHandlePtr&);
void __decRefUnsafe(DictionaryHandlePtr&);
void __clearHandleUnsafe(DictionaryHandlePtr&);

typedef ::IceInternal::Handle< ::OPI::ODABAClient> ODABAClientPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::OPI::ODABAClient> ODABAClientPrx;

void __write(::IceInternal::BasicStream*, const ODABAClientPrx&);
void __read(::IceInternal::BasicStream*, ODABAClientPrx&);
void __write(::IceInternal::BasicStream*, const ODABAClientPtr&);
void __patch__ODABAClientPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const ODABAClientPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const ODABAClientPtr&);
void __decRefUnsafe(ODABAClientPtr&);
void __clearHandleUnsafe(ODABAClientPtr&);

typedef ::IceInternal::Handle< ::OPI::OperationHandle> OperationHandlePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::OPI::OperationHandle> OperationHandlePrx;

void __write(::IceInternal::BasicStream*, const OperationHandlePrx&);
void __read(::IceInternal::BasicStream*, OperationHandlePrx&);
void __write(::IceInternal::BasicStream*, const OperationHandlePtr&);
void __patch__OperationHandlePtr(void*, ::Ice::ObjectPtr&);

void __addObject(const OperationHandlePtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const OperationHandlePtr&);
void __decRefUnsafe(OperationHandlePtr&);
void __clearHandleUnsafe(OperationHandlePtr&);

typedef ::IceInternal::Handle< ::OPI::PropertyHandle> PropertyHandlePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::OPI::PropertyHandle> PropertyHandlePrx;

void __write(::IceInternal::BasicStream*, const PropertyHandlePrx&);
void __read(::IceInternal::BasicStream*, PropertyHandlePrx&);
void __write(::IceInternal::BasicStream*, const PropertyHandlePtr&);
void __patch__PropertyHandlePtr(void*, ::Ice::ObjectPtr&);

void __addObject(const PropertyHandlePtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const PropertyHandlePtr&);
void __decRefUnsafe(PropertyHandlePtr&);
void __clearHandleUnsafe(PropertyHandlePtr&);

typedef ::IceInternal::Handle< ::OPI::OPIFactory> OPIFactoryPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::OPI::OPIFactory> OPIFactoryPrx;

void __write(::IceInternal::BasicStream*, const OPIFactoryPrx&);
void __read(::IceInternal::BasicStream*, OPIFactoryPrx&);
void __write(::IceInternal::BasicStream*, const OPIFactoryPtr&);
void __patch__OPIFactoryPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const OPIFactoryPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const OPIFactoryPtr&);
void __decRefUnsafe(OPIFactoryPtr&);
void __clearHandleUnsafe(OPIFactoryPtr&);

typedef ::IceInternal::Handle< ::OPI::Session> SessionPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::OPI::Session> SessionPrx;

void __write(::IceInternal::BasicStream*, const SessionPrx&);
void __read(::IceInternal::BasicStream*, SessionPrx&);
void __write(::IceInternal::BasicStream*, const SessionPtr&);
void __patch__SessionPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const SessionPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const SessionPtr&);
void __decRefUnsafe(SessionPtr&);
void __clearHandleUnsafe(SessionPtr&);

typedef ::IceInternal::Handle< ::OPI::SessionFactory> SessionFactoryPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::OPI::SessionFactory> SessionFactoryPrx;

void __write(::IceInternal::BasicStream*, const SessionFactoryPrx&);
void __read(::IceInternal::BasicStream*, SessionFactoryPrx&);
void __write(::IceInternal::BasicStream*, const SessionFactoryPtr&);
void __patch__SessionFactoryPtr(void*, ::Ice::ObjectPtr&);

void __addObject(const SessionFactoryPtr&, ::IceInternal::GCCountMap&);
bool __usesClasses(const SessionFactoryPtr&);
void __decRefUnsafe(SessionFactoryPtr&);
void __clearHandleUnsafe(SessionFactoryPtr&);

}

namespace OPI
{

enum PIACC
{
    piaREAD,
    piaWRITE,
    piaUPDATE,
    piaUNDEFINED
};

void __write(::IceInternal::BasicStream*, PIACC);
void __read(::IceInternal::BasicStream*, PIACC&);

enum PIREPL
{
    piaREPLGUID,
    piaREPLDIRECT,
    piaREPLNONE,
    piaREPLLOCAL,
    piaREPLALL,
    piaREPLINSTANCE,
    piaREPLRELATIONSHIPS,
    piaREPLNOCREATE
};

void __write(::IceInternal::BasicStream*, PIREPL);
void __read(::IceInternal::BasicStream*, PIREPL&);

enum PIADEF
{
    piaUNKNOWN,
    piaEXCLUSIVE,
    piaSHARE
};

void __write(::IceInternal::BasicStream*, PIADEF);
void __read(::IceInternal::BasicStream*, PIADEF&);

enum ResourceTypes
{
    resAUTOMATIC,
    resSERVER,
    resLOCAL,
    resSERVERINTERN
};

void __write(::IceInternal::BasicStream*, ResourceTypes);
void __read(::IceInternal::BasicStream*, ResourceTypes&);

enum ApplicationTypes
{
    aptWINDOWS,
    aptCONSOLE
};

void __write(::IceInternal::BasicStream*, ApplicationTypes);
void __read(::IceInternal::BasicStream*, ApplicationTypes&);

}

namespace IceProxy
{

namespace OPI
{

class CheckOptions : virtual public ::IceProxy::Ice::Object
{
public:

    bool Initialize(const ::std::string& parmstring)
    {
	return Initialize(parmstring, __defaultContext());
    }
    bool Initialize(const ::std::string&, const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class DBObjectHandle : virtual public ::IceProxy::Ice::Object
{
public:

    ::Ice::Int BeginTransaction(bool extTA, ::Ice::Int wmaxnum)
    {
	return BeginTransaction(extTA, wmaxnum, __defaultContext());
    }
    ::Ice::Int BeginTransaction(bool, ::Ice::Int, const ::Ice::Context&);

    bool ChangeTimeStamp(::Ice::Int versionnr, ::Ice::Long timestamp)
    {
	return ChangeTimeStamp(versionnr, timestamp, __defaultContext());
    }
    bool ChangeTimeStamp(::Ice::Int, ::Ice::Long, const ::Ice::Context&);

    bool CommitTransaction(::Ice::Int talevel)
    {
	return CommitTransaction(talevel, __defaultContext());
    }
    bool CommitTransaction(::Ice::Int, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx CreateTempPropertyHandle(const ::OPI::PropertyHandlePrx& prophdlref)
    {
	return CreateTempPropertyHandle(prophdlref, __defaultContext());
    }
    ::OPI::PropertyHandlePrx CreateTempPropertyHandle(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool DeleteExtent(const ::std::string& extnames)
    {
	return DeleteExtent(extnames, __defaultContext());
    }
    bool DeleteExtent(const ::std::string&, const ::Ice::Context&);

    bool DeleteExtentRef(const ::std::string& extnames)
    {
	return DeleteExtentRef(extnames, __defaultContext());
    }
    bool DeleteExtentRef(const ::std::string&, const ::Ice::Context&);

    void DisableEventHandling()
    {
	DisableEventHandling(__defaultContext());
    }
    void DisableEventHandling(const ::Ice::Context&);

    void EnableEventHandling()
    {
	EnableEventHandling(__defaultContext());
    }
    void EnableEventHandling(const ::Ice::Context&);

    bool EventHandling()
    {
	return EventHandling(__defaultContext());
    }
    bool EventHandling(const ::Ice::Context&);

    bool ExecuteDBObjectAction(const ::std::string& actionname, const ::std::string& parmstring)
    {
	return ExecuteDBObjectAction(actionname, parmstring, __defaultContext());
    }
    bool ExecuteDBObjectAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx& resobhandle, const ::std::string& expression)
    {
	return ExecuteExpression(resobhandle, expression, __defaultContext());
    }
    ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool ExtentExist(const ::std::string& extnames)
    {
	return ExtentExist(extnames, __defaultContext());
    }
    bool ExtentExist(const ::std::string&, const ::Ice::Context&);

    ::OPI::PIACC GetAccess()
    {
	return GetAccess(__defaultContext());
    }
    ::OPI::PIACC GetAccess(const ::Ice::Context&);

    ::std::string GetActionResult()
    {
	return GetActionResult(__defaultContext());
    }
    ::std::string GetActionResult(const ::Ice::Context&);

    ::OPI::DatabaseHandlePrx GetDBHandle()
    {
	return GetDBHandle(__defaultContext());
    }
    ::OPI::DatabaseHandlePrx GetDBHandle(const ::Ice::Context&);

    ::OPI::DataSourceHandlePrx GetDataSource()
    {
	return GetDataSource(__defaultContext());
    }
    ::OPI::DataSourceHandlePrx GetDataSource(const ::Ice::Context&);

    ::OPI::DictionaryHandlePrx GetDictionary()
    {
	return GetDictionary(__defaultContext());
    }
    ::OPI::DictionaryHandlePrx GetDictionary(const ::Ice::Context&);

    ::std::string GetExtent(::Ice::Int indx0)
    {
	return GetExtent(indx0, __defaultContext());
    }
    ::std::string GetExtent(::Ice::Int, const ::Ice::Context&);

    ::OPI::DBObjectHandlePrx GetHighObject()
    {
	return GetHighObject(__defaultContext());
    }
    ::OPI::DBObjectHandlePrx GetHighObject(const ::Ice::Context&);

    ::std::string GetObject(::Ice::Int indx0)
    {
	return GetObject(indx0, __defaultContext());
    }
    ::std::string GetObject(::Ice::Int, const ::Ice::Context&);

    ::std::string GetServerVariable(const ::std::string& varname)
    {
	return GetServerVariable(varname, __defaultContext());
    }
    ::std::string GetServerVariable(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int GetSystemVersion()
    {
	return GetSystemVersion(__defaultContext());
    }
    ::Ice::Int GetSystemVersion(const ::Ice::Context&);

    ::Ice::Long GetTimeStamp(::Ice::Int versionnr)
    {
	return GetTimeStamp(versionnr, __defaultContext());
    }
    ::Ice::Long GetTimeStamp(::Ice::Int, const ::Ice::Context&);

    ::Ice::Int GetTransactionLevel()
    {
	return GetTransactionLevel(__defaultContext());
    }
    ::Ice::Int GetTransactionLevel(const ::Ice::Context&);

    ::Ice::Int GetVersion(::Ice::Long timestamp)
    {
	return GetVersion(timestamp, __defaultContext());
    }
    ::Ice::Int GetVersion(::Ice::Long, const ::Ice::Context&);

    bool IsClient()
    {
	return IsClient(__defaultContext());
    }
    bool IsClient(const ::Ice::Context&);

    bool IsEmpty()
    {
	return IsEmpty(__defaultContext());
    }
    bool IsEmpty(const ::Ice::Context&);

    bool IsOpened()
    {
	return IsOpened(__defaultContext());
    }
    bool IsOpened(const ::Ice::Context&);

    bool IsServer()
    {
	return IsServer(__defaultContext());
    }
    bool IsServer(const ::Ice::Context&);

    bool IsValid()
    {
	return IsValid(__defaultContext());
    }
    bool IsValid(const ::Ice::Context&);

    bool NewVersion(::Ice::Long timestamp, ::Ice::Int versionnr)
    {
	return NewVersion(timestamp, versionnr, __defaultContext());
    }
    bool NewVersion(::Ice::Long, ::Ice::Int, const ::Ice::Context&);

    bool OpenObject(const ::OPI::DBObjectHandlePrx& dbobject, const ::std::string& objname, ::OPI::PIACC accopt, ::Ice::Int versionnr, ::OPI::ResourceTypes localressources)
    {
	return OpenObject(dbobject, objname, accopt, versionnr, localressources, __defaultContext());
    }
    bool OpenObject(const ::OPI::DBObjectHandlePrx&, const ::std::string&, ::OPI::PIACC, ::Ice::Int, ::OPI::ResourceTypes, const ::Ice::Context&);

    bool RollBack(::Ice::Int talevel)
    {
	return RollBack(talevel, __defaultContext());
    }
    bool RollBack(::Ice::Int, const ::Ice::Context&);

    void SetActionResult(const ::std::string& resultstring)
    {
	SetActionResult(resultstring, __defaultContext());
    }
    void SetActionResult(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int SetOverload(bool overloadopt)
    {
	return SetOverload(overloadopt, __defaultContext());
    }
    ::Ice::Int SetOverload(bool, const ::Ice::Context&);

    bool SetServerVariable(const ::std::string& varname, const ::std::string& varstring)
    {
	return SetServerVariable(varname, varstring, __defaultContext());
    }
    bool SetServerVariable(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool SetUserDefinedIdentity(bool identityopt)
    {
	return SetUserDefinedIdentity(identityopt, __defaultContext());
    }
    bool SetUserDefinedIdentity(bool, const ::Ice::Context&);

    bool SetVersion(::Ice::Int versionnr)
    {
	return SetVersion(versionnr, __defaultContext());
    }
    bool SetVersion(::Ice::Int, const ::Ice::Context&);

    bool SetVersioni1(::Ice::Long date)
    {
	return SetVersioni1(date, __defaultContext());
    }
    bool SetVersioni1(::Ice::Long, const ::Ice::Context&);

    bool SetVersioni2(::Ice::Long timestamp)
    {
	return SetVersioni2(timestamp, __defaultContext());
    }
    bool SetVersioni2(::Ice::Long, const ::Ice::Context&);

    ::Ice::Int VersionCount()
    {
	return VersionCount(__defaultContext());
    }
    ::Ice::Int VersionCount(const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class DataSourceHandle : virtual public ::IceProxy::Ice::Object
{
public:

    bool BeginTransaction(bool extta)
    {
	return BeginTransaction(extta, __defaultContext());
    }
    bool BeginTransaction(bool, const ::Ice::Context&);

    bool Close()
    {
	return Close(__defaultContext());
    }
    bool Close(const ::Ice::Context&);

    bool CloseDBObject()
    {
	return CloseDBObject(__defaultContext());
    }
    bool CloseDBObject(const ::Ice::Context&);

    bool CloseDatabase()
    {
	return CloseDatabase(__defaultContext());
    }
    bool CloseDatabase(const ::Ice::Context&);

    bool CloseDictionary()
    {
	return CloseDictionary(__defaultContext());
    }
    bool CloseDictionary(const ::Ice::Context&);

    bool CloseProperty()
    {
	return CloseProperty(__defaultContext());
    }
    bool CloseProperty(const ::Ice::Context&);

    bool CloseResourceDB()
    {
	return CloseResourceDB(__defaultContext());
    }
    bool CloseResourceDB(const ::Ice::Context&);

    bool CommitTransaction()
    {
	return CommitTransaction(__defaultContext());
    }
    bool CommitTransaction(const ::Ice::Context&);

    bool Connect(const ::OPI::ODABAClientPrx& podabaclient)
    {
	return Connect(podabaclient, __defaultContext());
    }
    bool Connect(const ::OPI::ODABAClientPrx&, const ::Ice::Context&);

    bool Disconnect()
    {
	return Disconnect(__defaultContext());
    }
    bool Disconnect(const ::Ice::Context&);

    bool Open(const ::OPI::ODABAClientPrx& podabaclient, ::OPI::PIACC accmod)
    {
	return Open(podabaclient, accmod, __defaultContext());
    }
    bool Open(const ::OPI::ODABAClientPrx&, ::OPI::PIACC, const ::Ice::Context&);

    bool Openi02(const ::OPI::ODABAClientPrx& podabaclient, const ::std::string& inifile, const ::std::string& datasourcename)
    {
	return Openi02(podabaclient, inifile, datasourcename, __defaultContext());
    }
    bool Openi02(const ::OPI::ODABAClientPrx&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool Openi1(const ::OPI::ODABAClientPrx& podabaclient, const ::std::string& datasourcename)
    {
	return Openi1(podabaclient, datasourcename, __defaultContext());
    }
    bool Openi1(const ::OPI::ODABAClientPrx&, const ::std::string&, const ::Ice::Context&);

    ::OPI::DBObjectHandlePrx OpenDBObject()
    {
	return OpenDBObject(__defaultContext());
    }
    ::OPI::DBObjectHandlePrx OpenDBObject(const ::Ice::Context&);

    ::OPI::DatabaseHandlePrx OpenDatabase()
    {
	return OpenDatabase(__defaultContext());
    }
    ::OPI::DatabaseHandlePrx OpenDatabase(const ::Ice::Context&);

    ::OPI::DictionaryHandlePrx OpenDictionary(::OPI::PIACC accopt)
    {
	return OpenDictionary(accopt, __defaultContext());
    }
    ::OPI::DictionaryHandlePrx OpenDictionary(::OPI::PIACC, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx OpenProperty(const ::std::string& extname)
    {
	return OpenProperty(extname, __defaultContext());
    }
    ::OPI::PropertyHandlePrx OpenProperty(const ::std::string&, const ::Ice::Context&);

    ::OPI::DatabaseHandlePrx OpenResourceDB()
    {
	return OpenResourceDB(__defaultContext());
    }
    ::OPI::DatabaseHandlePrx OpenResourceDB(const ::Ice::Context&);

    bool RollBack()
    {
	return RollBack(__defaultContext());
    }
    bool RollBack(const ::Ice::Context&);

    bool SetDBObject(const ::OPI::DBObjectHandlePrx& ohandle, const ::std::string& wobjname)
    {
	return SetDBObject(ohandle, wobjname, __defaultContext());
    }
    bool SetDBObject(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool SetDataSource(const ::OPI::DataSourceHandlePrx& dbdefptr)
    {
	return SetDataSource(dbdefptr, __defaultContext());
    }
    bool SetDataSource(const ::OPI::DataSourceHandlePrx&, const ::Ice::Context&);

    bool SetDatabase(const ::OPI::DatabaseHandlePrx& dbhandle, const ::std::string& wbasepath)
    {
	return SetDatabase(dbhandle, wbasepath, __defaultContext());
    }
    bool SetDatabase(const ::OPI::DatabaseHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool SetDictionary(const ::OPI::DictionaryHandlePrx& dictptr, const ::std::string& wdictpath)
    {
	return SetDictionary(dictptr, wdictpath, __defaultContext());
    }
    bool SetDictionary(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool SetResourceDB(const ::OPI::DatabaseHandlePrx& dbhandle, const ::std::string& wbasepath)
    {
	return SetResourceDB(dbhandle, wbasepath, __defaultContext());
    }
    bool SetResourceDB(const ::OPI::DatabaseHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool SetVariables(const ::std::string& datasourcename)
    {
	return SetVariables(datasourcename, __defaultContext());
    }
    bool SetVariables(const ::std::string&, const ::Ice::Context&);

    bool Setup(const ::std::string& inifile, const ::std::string& datasourcename)
    {
	return Setup(inifile, datasourcename, __defaultContext());
    }
    bool Setup(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool SetupVariables(const ::std::string& datasourcename)
    {
	return SetupVariables(datasourcename, __defaultContext());
    }
    bool SetupVariables(const ::std::string&, const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class DatabaseHandle : virtual public ::IceProxy::OPI::DBObjectHandle
{
public:

    bool ActivateShadowBase()
    {
	return ActivateShadowBase(__defaultContext());
    }
    bool ActivateShadowBase(const ::Ice::Context&);

    bool BackupDB(const ::std::string& target)
    {
	return BackupDB(target, __defaultContext());
    }
    bool BackupDB(const ::std::string&, const ::Ice::Context&);

    bool CheckDB(const ::OPI::CheckOptionsPrx& checkopts, const ::std::string& source)
    {
	return CheckDB(checkopts, source, __defaultContext());
    }
    bool CheckDB(const ::OPI::CheckOptionsPrx&, const ::std::string&, const ::Ice::Context&);

    bool CheckLicence(const ::std::string& licowner, const ::std::string& licnumber)
    {
	return CheckLicence(licowner, licnumber, __defaultContext());
    }
    bool CheckLicence(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool CloseWorkspace()
    {
	return CloseWorkspace(__defaultContext());
    }
    bool CloseWorkspace(const ::Ice::Context&);

    bool ConsolidateWorkspace()
    {
	return ConsolidateWorkspace(__defaultContext());
    }
    bool ConsolidateWorkspace(const ::Ice::Context&);

    bool DeactivateShadowBase()
    {
	return DeactivateShadowBase(__defaultContext());
    }
    bool DeactivateShadowBase(const ::Ice::Context&);

    bool DeleteWorkspace(const ::std::string& wsnames, const ::std::string& username)
    {
	return DeleteWorkspace(wsnames, username, __defaultContext());
    }
    bool DeleteWorkspace(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool DisableWorkspace()
    {
	return DisableWorkspace(__defaultContext());
    }
    bool DisableWorkspace(const ::Ice::Context&);

    bool DiscardWorkspace()
    {
	return DiscardWorkspace(__defaultContext());
    }
    bool DiscardWorkspace(const ::Ice::Context&);

    bool EnableWorkspace(const ::std::string& sdwpath)
    {
	return EnableWorkspace(sdwpath, __defaultContext());
    }
    bool EnableWorkspace(const ::std::string&, const ::Ice::Context&);

    bool ExecuteDatabaseAction(const ::std::string& actionname, const ::std::string& parmstring)
    {
	return ExecuteDatabaseAction(actionname, parmstring, __defaultContext());
    }
    bool ExecuteDatabaseAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool ExistWorkspace(const ::std::string& wsnames)
    {
	return ExistWorkspace(wsnames, __defaultContext());
    }
    bool ExistWorkspace(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int GetDatabaseID()
    {
	return GetDatabaseID(__defaultContext());
    }
    ::Ice::Int GetDatabaseID(const ::Ice::Context&);

    ::std::string GetPath()
    {
	return GetPath(__defaultContext());
    }
    ::std::string GetPath(const ::Ice::Context&);

    ::Ice::Int GetSchemaVersion()
    {
	return GetSchemaVersion(__defaultContext());
    }
    ::Ice::Int GetSchemaVersion(const ::Ice::Context&);

    ::std::string GetVersionString()
    {
	return GetVersionString(__defaultContext());
    }
    ::std::string GetVersionString(const ::Ice::Context&);

    ::std::string GetWorkspace(const ::std::string& wsroot, ::Ice::Int wsindex, const ::std::string& username, const ::std::string& wsname, bool refreshopt, const ::std::string& wsinfo)
    {
	return GetWorkspace(wsroot, wsindex, username, wsname, refreshopt, wsinfo, __defaultContext());
    }
    ::std::string GetWorkspace(const ::std::string&, ::Ice::Int, const ::std::string&, const ::std::string&, bool, const ::std::string&, const ::Ice::Context&);

    bool IgnoreWriteProtect()
    {
	return IgnoreWriteProtect(__defaultContext());
    }
    bool IgnoreWriteProtect(const ::Ice::Context&);

    bool InitDataArea(::Ice::Int mbnumber, ::Ice::Int sbnumber, ::Ice::Int danumber, const ::std::string& filename, ::Ice::Int dasize)
    {
	return InitDataArea(mbnumber, sbnumber, danumber, filename, dasize, __defaultContext());
    }
    bool InitDataArea(::Ice::Int, ::Ice::Int, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    bool InitMainBase(::Ice::Int mbnumber, const ::std::string& filename, ::Ice::Int lowEBN, ::Ice::Int highEBN, ::Ice::Int dasize, bool largedb, bool pindep)
    {
	return InitMainBase(mbnumber, filename, lowEBN, highEBN, dasize, largedb, pindep, __defaultContext());
    }
    bool InitMainBase(::Ice::Int, const ::std::string&, ::Ice::Int, ::Ice::Int, ::Ice::Int, bool, bool, const ::Ice::Context&);

    bool InitSubBase(::Ice::Int mbnumber, ::Ice::Int sbnumber, const ::std::string& filename, ::Ice::Int dasize)
    {
	return InitSubBase(mbnumber, sbnumber, filename, dasize, __defaultContext());
    }
    bool InitSubBase(::Ice::Int, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    bool IsLicenced()
    {
	return IsLicenced(__defaultContext());
    }
    bool IsLicenced(const ::Ice::Context&);

    bool IsShared()
    {
	return IsShared(__defaultContext());
    }
    bool IsShared(const ::Ice::Context&);

    bool LocateWorkspace(const ::std::string& wsnames)
    {
	return LocateWorkspace(wsnames, __defaultContext());
    }
    bool LocateWorkspace(const ::std::string&, const ::Ice::Context&);

    bool OpenDatabase(const ::OPI::DictionaryHandlePrx& dicthandle, const ::std::string& cpath, ::OPI::PIACC accopt, bool wnetopt, bool onlineversion, ::Ice::Int versionnr, ::OPI::ResourceTypes localressources, bool sysenv)
    {
	return OpenDatabase(dicthandle, cpath, accopt, wnetopt, onlineversion, versionnr, localressources, sysenv, __defaultContext());
    }
    bool OpenDatabase(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::OPI::PIACC, bool, bool, ::Ice::Int, ::OPI::ResourceTypes, bool, const ::Ice::Context&);

    bool OpenWorkspace(const ::std::string& wsnames, const ::std::string& username, bool exclusive, const ::std::string& wspath)
    {
	return OpenWorkspace(wsnames, username, exclusive, wspath, __defaultContext());
    }
    bool OpenWorkspace(const ::std::string&, const ::std::string&, bool, const ::std::string&, const ::Ice::Context&);

    bool RecreateExtent(const ::std::string& extnames)
    {
	return RecreateExtent(extnames, __defaultContext());
    }
    bool RecreateExtent(const ::std::string&, const ::Ice::Context&);

    bool RestoreDB(const ::std::string& source)
    {
	return RestoreDB(source, __defaultContext());
    }
    bool RestoreDB(const ::std::string&, const ::Ice::Context&);

    bool SetupTypeID(::Ice::Int sid)
    {
	return SetupTypeID(sid, __defaultContext());
    }
    bool SetupTypeID(::Ice::Int, const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class DictionaryHandle : virtual public ::IceProxy::OPI::DatabaseHandle
{
public:

    ::Ice::Int BaseType(const ::std::string& strnames)
    {
	return BaseType(strnames, __defaultContext());
    }
    ::Ice::Int BaseType(const ::std::string&, const ::Ice::Context&);

    bool CheckExpression(const ::std::string& expression, const ::OPI::DBObjectHandlePrx& dbobjhandle, const ::std::string& clsnames)
    {
	return CheckExpression(expression, dbobjhandle, clsnames, __defaultContext());
    }
    bool CheckExpression(const ::std::string&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool CheckExpressionInClass(const ::OPI::DBObjectHandlePrx& resobj, const ::std::string& clsnames, const ::std::string& exprnames, const ::std::string& implnames)
    {
	return CheckExpressionInClass(resobj, clsnames, exprnames, implnames, __defaultContext());
    }
    bool CheckExpressionInClass(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool CheckExtentDef(const ::std::string& scopedname)
    {
	return CheckExtentDef(scopedname, __defaultContext());
    }
    bool CheckExtentDef(const ::std::string&, const ::Ice::Context&);

    bool CheckValueSet(const ::std::string& scopedname)
    {
	return CheckValueSet(scopedname, __defaultContext());
    }
    bool CheckValueSet(const ::std::string&, const ::Ice::Context&);

    bool CopyCodeset(const ::OPI::DictionaryHandlePrx& srcedicthandle, const ::std::string& strname, ::Ice::Int namespaceid, const ::std::string& newnames, ::OPI::PIREPL dbreplace, bool retainSID, bool retainschemav)
    {
	return CopyCodeset(srcedicthandle, strname, namespaceid, newnames, dbreplace, retainSID, retainschemav, __defaultContext());
    }
    bool CopyCodeset(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::Ice::Int, const ::std::string&, ::OPI::PIREPL, bool, bool, const ::Ice::Context&);

    bool CopyExtentDef(const ::OPI::DictionaryHandlePrx& srcedicthandle, const ::std::string& extentname, const ::std::string& newnames, const ::std::string& targstruct, bool transaction, bool retainschemav)
    {
	return CopyExtentDef(srcedicthandle, extentname, newnames, targstruct, transaction, retainschemav, __defaultContext());
    }
    bool CopyExtentDef(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, bool, bool, const ::Ice::Context&);

    bool CopyStructure(const ::OPI::DictionaryHandlePrx& srcedicthandle, const ::std::string& strname, ::Ice::Int namespaceid, const ::std::string& newnames, const ::std::string& topname, ::OPI::PIREPL dbreplace, bool retainSID, bool retainschemav)
    {
	return CopyStructure(srcedicthandle, strname, namespaceid, newnames, topname, dbreplace, retainSID, retainschemav, __defaultContext());
    }
    bool CopyStructure(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::Ice::Int, const ::std::string&, const ::std::string&, ::OPI::PIREPL, bool, bool, const ::Ice::Context&);

    bool CopyType(const ::OPI::DictionaryHandlePrx& srcedicthandle, const ::std::string& strnames, const ::std::string& newnames, const ::std::string& topname, ::OPI::PIREPL dbreplace, bool retainSID, bool transaction, bool retainschemav)
    {
	return CopyType(srcedicthandle, strnames, newnames, topname, dbreplace, retainSID, transaction, retainschemav, __defaultContext());
    }
    bool CopyType(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::PIREPL, bool, bool, bool, const ::Ice::Context&);

    bool CreateEnum(const ::std::string& enumname, const ::std::string& basetype)
    {
	return CreateEnum(enumname, basetype, __defaultContext());
    }
    bool CreateEnum(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    ::std::string CreateTempExtent(const ::std::string& strnames, const ::std::string& extnamesw, const ::std::string& keynamew, const ::std::string& baseextsw, bool weakoptw, bool ownoptw)
    {
	return CreateTempExtent(strnames, extnamesw, keynamew, baseextsw, weakoptw, ownoptw, __defaultContext());
    }
    ::std::string CreateTempExtent(const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, bool, bool, const ::Ice::Context&);

    bool DeleteEnum(const ::std::string& enumname)
    {
	return DeleteEnum(enumname, __defaultContext());
    }
    bool DeleteEnum(const ::std::string&, const ::Ice::Context&);

    ::std::string EnumToString(const ::std::string& enumeration, ::Ice::Int enumval, const ::std::string& pstring, ::Ice::Int len)
    {
	return EnumToString(enumeration, enumval, pstring, len, __defaultContext());
    }
    ::std::string EnumToString(const ::std::string&, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    ::Ice::Int GetLastSchemaVersion()
    {
	return GetLastSchemaVersion(__defaultContext());
    }
    ::Ice::Int GetLastSchemaVersion(const ::Ice::Context&);

    ::std::string GetTempName(const ::std::string& extnames)
    {
	return GetTempName(extnames, __defaultContext());
    }
    ::std::string GetTempName(const ::std::string&, const ::Ice::Context&);

    bool IsBasicType(const ::std::string& typenames)
    {
	return IsBasicType(typenames, __defaultContext());
    }
    bool IsBasicType(const ::std::string&, const ::Ice::Context&);

    bool OpenDictionary(const ::OPI::ODABAClientPrx& podabaclient, const ::std::string& cpath, ::OPI::PIACC accopt, bool wnetopt, ::Ice::Int versionnr, ::OPI::ResourceTypes localressources, bool sysenv)
    {
	return OpenDictionary(podabaclient, cpath, accopt, wnetopt, versionnr, localressources, sysenv, __defaultContext());
    }
    bool OpenDictionary(const ::OPI::ODABAClientPrx&, const ::std::string&, ::OPI::PIACC, bool, ::Ice::Int, ::OPI::ResourceTypes, bool, const ::Ice::Context&);

    ::Ice::Int StringToEnum(const ::std::string& enumeration, const ::std::string& enumstring)
    {
	return StringToEnum(enumeration, enumstring, __defaultContext());
    }
    ::Ice::Int StringToEnum(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool UpdateVersion()
    {
	return UpdateVersion(__defaultContext());
    }
    bool UpdateVersion(const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class ODABAClient : virtual public ::IceProxy::Ice::Object
{
public:

    void ActivateGUIMessages()
    {
	ActivateGUIMessages(__defaultContext());
    }
    void ActivateGUIMessages(const ::Ice::Context&);

    bool BackupDB(const ::std::string& cpath, const ::std::string& target, ::Ice::Int waitsec)
    {
	return BackupDB(cpath, target, waitsec, __defaultContext());
    }
    bool BackupDB(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    bool CheckDB(const ::std::string& dictpath, const ::std::string& cpath, const ::OPI::CheckOptionsPrx& checkopts, const ::std::string& source, ::Ice::Int waitsec)
    {
	return CheckDB(dictpath, cpath, checkopts, source, waitsec, __defaultContext());
    }
    bool CheckDB(const ::std::string&, const ::std::string&, const ::OPI::CheckOptionsPrx&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    bool Close()
    {
	return Close(__defaultContext());
    }
    bool Close(const ::Ice::Context&);

    bool Connect(const ::std::string& servername, ::Ice::Int hostport, const ::std::string& cachestring)
    {
	return Connect(servername, hostport, cachestring, __defaultContext());
    }
    bool Connect(const ::std::string&, ::Ice::Int, const ::std::string&, const ::Ice::Context&);

    bool DictDisplay(const ::std::string& dbpath, const ::std::string& ppath)
    {
	return DictDisplay(dbpath, ppath, __defaultContext());
    }
    bool DictDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    void Disconnect()
    {
	Disconnect(__defaultContext());
    }
    void Disconnect(const ::Ice::Context&);

    bool Exist(const ::std::string& cpath)
    {
	return Exist(cpath, __defaultContext());
    }
    bool Exist(const ::std::string&, const ::Ice::Context&);

    ::std::string GetDataSource(::Ice::Int indx0)
    {
	return GetDataSource(indx0, __defaultContext());
    }
    ::std::string GetDataSource(::Ice::Int, const ::Ice::Context&);

    ::std::string GetHost()
    {
	return GetHost(__defaultContext());
    }
    ::std::string GetHost(const ::Ice::Context&);

    ::Ice::Int GetPort()
    {
	return GetPort(__defaultContext());
    }
    ::Ice::Int GetPort(const ::Ice::Context&);

    ::std::string GetServerVariable(const ::std::string& varname)
    {
	return GetServerVariable(varname, __defaultContext());
    }
    ::std::string GetServerVariable(const ::std::string&, const ::Ice::Context&);

    void Initialize(const ::std::string& inipath, const ::std::string& applicationname, const ::std::string& progpath, ::OPI::ApplicationTypes applicationtype, bool initservices)
    {
	Initialize(inipath, applicationname, progpath, applicationtype, initservices, __defaultContext());
    }
    void Initialize(const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::ApplicationTypes, bool, const ::Ice::Context&);

    bool IsConnected()
    {
	return IsConnected(__defaultContext());
    }
    bool IsConnected(const ::Ice::Context&);

    bool KillClient(::Ice::Int clientid, ::Ice::Int waitsec, bool sendmessage)
    {
	return KillClient(clientid, waitsec, sendmessage, __defaultContext());
    }
    bool KillClient(::Ice::Int, ::Ice::Int, bool, const ::Ice::Context&);

    bool Open(const ::std::string& inipath, const ::std::string& applicationname, const ::std::string& progpath, ::OPI::ApplicationTypes applicationtype)
    {
	return Open(inipath, applicationname, progpath, applicationtype, __defaultContext());
    }
    bool Open(const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::ApplicationTypes, const ::Ice::Context&);

    ::OPI::DBObjectHandlePrx OpenDataSource(const ::std::string& datasourcename, ::OPI::PIACC accopt)
    {
	return OpenDataSource(datasourcename, accopt, __defaultContext());
    }
    ::OPI::DBObjectHandlePrx OpenDataSource(const ::std::string&, ::OPI::PIACC, const ::Ice::Context&);

    bool PackDatabase(const ::std::string& cpath, const ::std::string& temppath)
    {
	return PackDatabase(cpath, temppath, __defaultContext());
    }
    bool PackDatabase(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool RestoreDB(const ::std::string& cpath, const ::std::string& source, ::Ice::Int waitsec)
    {
	return RestoreDB(cpath, source, waitsec, __defaultContext());
    }
    bool RestoreDB(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    bool SendClientMessage(::Ice::Int clientid, const ::std::string& mtext, const ::std::string& mtitle, const ::std::string& mtype)
    {
	return SendClientMessage(clientid, mtext, mtitle, mtype, __defaultContext());
    }
    bool SendClientMessage(::Ice::Int, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool SetServerVariable(const ::std::string& varname, const ::std::string& varstring)
    {
	return SetServerVariable(varname, varstring, __defaultContext());
    }
    bool SetServerVariable(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool ShutDown(const ::std::string& closesystem)
    {
	return ShutDown(closesystem, __defaultContext());
    }
    bool ShutDown(const ::std::string&, const ::Ice::Context&);

    bool StartPause(::Ice::Int waitsec)
    {
	return StartPause(waitsec, __defaultContext());
    }
    bool StartPause(::Ice::Int, const ::Ice::Context&);

    bool StatDisplay(const ::std::string& dbpath, const ::std::string& ppath)
    {
	return StatDisplay(dbpath, ppath, __defaultContext());
    }
    bool StatDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    void StopPause()
    {
	StopPause(__defaultContext());
    }
    void StopPause(const ::Ice::Context&);

    bool SysInfoDisplay(const ::std::string& dbpath, const ::std::string& ppath)
    {
	return SysInfoDisplay(dbpath, ppath, __defaultContext());
    }
    bool SysInfoDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class OperationHandle : virtual public ::IceProxy::Ice::Object
{
public:

    bool CheckExpression(const ::OPI::DictionaryHandlePrx& dictptr, const ::std::string& expression, const ::OPI::DBObjectHandlePrx& obhandle, const ::std::string& clsnames)
    {
	return CheckExpression(dictptr, expression, obhandle, clsnames, __defaultContext());
    }
    bool CheckExpression(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool CheckExpressionInClass(const ::OPI::DictionaryHandlePrx& dictptr, const ::OPI::DBObjectHandlePrx& resobj, const ::std::string& clsnames, const ::std::string& exprnames, const ::std::string& impnames)
    {
	return CheckExpressionInClass(dictptr, resobj, clsnames, exprnames, impnames, __defaultContext());
    }
    bool CheckExpressionInClass(const ::OPI::DictionaryHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool Execute()
    {
	return Execute(__defaultContext());
    }
    bool Execute(const ::Ice::Context&);

    ::OPI::PropertyHandlePrx GetResult()
    {
	return GetResult(__defaultContext());
    }
    ::OPI::PropertyHandlePrx GetResult(const ::Ice::Context&);

    ::Ice::Int GetSize()
    {
	return GetSize(__defaultContext());
    }
    ::Ice::Int GetSize(const ::Ice::Context&);

    bool IsValid()
    {
	return IsValid(__defaultContext());
    }
    bool IsValid(const ::Ice::Context&);

    bool Open(const ::OPI::PropertyHandlePrx& prophdlref)
    {
	return Open(prophdlref, __defaultContext());
    }
    bool Open(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool ProvideExpression(const ::OPI::DictionaryHandlePrx& pdictionary, const ::OPI::DBObjectHandlePrx& resobj, const ::OPI::DBObjectHandlePrx& obhandle, const ::std::string& expression)
    {
	return ProvideExpression(pdictionary, resobj, obhandle, expression, __defaultContext());
    }
    bool ProvideExpression(const ::OPI::DictionaryHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class PropertyHandle : virtual public ::IceProxy::Ice::Object
{
public:

    bool Add(::Ice::Int setpos0, const ::std::string& sortkey, const ::std::string& identkeyw)
    {
	return Add(setpos0, sortkey, identkeyw, __defaultContext());
    }
    bool Add(::Ice::Int, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool AddByKey(const ::std::string& sortkey, const ::std::string& identkeyw)
    {
	return AddByKey(sortkey, identkeyw, __defaultContext());
    }
    bool AddByKey(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool AddInstance(const ::OPI::PropertyHandlePrx& prophdl)
    {
	return AddInstance(prophdl, __defaultContext());
    }
    bool AddInstance(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool AddOnPosition(::Ice::Int setpos0w, bool initinst)
    {
	return AddOnPosition(setpos0w, initinst, __defaultContext());
    }
    bool AddOnPosition(::Ice::Int, bool, const ::Ice::Context&);

    bool AddGlobal(::Ice::Int setpos0, const ::std::string& sortkey, const ::std::string& identkeyw, bool initinst)
    {
	return AddGlobal(setpos0, sortkey, identkeyw, initinst, __defaultContext());
    }
    bool AddGlobal(::Ice::Int, const ::std::string&, const ::std::string&, bool, const ::Ice::Context&);

    bool AddGlobalByKey(const ::std::string& sortkey, const ::std::string& identkeyw, bool initinst)
    {
	return AddGlobalByKey(sortkey, identkeyw, initinst, __defaultContext());
    }
    bool AddGlobalByKey(const ::std::string&, const ::std::string&, bool, const ::Ice::Context&);

    bool AddGlobalOnPosition(::Ice::Int setpos0w, bool initinst)
    {
	return AddGlobalOnPosition(setpos0w, initinst, __defaultContext());
    }
    bool AddGlobalOnPosition(::Ice::Int, bool, const ::Ice::Context&);

    bool AddReference(const ::OPI::PropertyHandlePrx& sourcehandle, ::Ice::Int setpos0w)
    {
	return AddReference(sourcehandle, setpos0w, __defaultContext());
    }
    bool AddReference(const ::OPI::PropertyHandlePrx&, ::Ice::Int, const ::Ice::Context&);

    bool AllocDescription()
    {
	return AllocDescription(__defaultContext());
    }
    bool AllocDescription(const ::Ice::Context&);

    bool AllocateArea()
    {
	return AllocateArea(__defaultContext());
    }
    bool AllocateArea(const ::Ice::Context&);

    bool AppendString(const ::std::string& pstring)
    {
	return AppendString(pstring, __defaultContext());
    }
    bool AppendString(const ::std::string&, const ::Ice::Context&);

    bool AutoLocate(const ::std::string& chkopt)
    {
	return AutoLocate(chkopt, __defaultContext());
    }
    bool AutoLocate(const ::std::string&, const ::Ice::Context&);

    bool Cancel()
    {
	return Cancel(__defaultContext());
    }
    bool Cancel(const ::Ice::Context&);

    bool CancelBuffer()
    {
	return CancelBuffer(__defaultContext());
    }
    bool CancelBuffer(const ::Ice::Context&);

    ::Ice::Int ChangeBuffer(::Ice::Int buffnum)
    {
	return ChangeBuffer(buffnum, __defaultContext());
    }
    ::Ice::Int ChangeBuffer(::Ice::Int, const ::Ice::Context&);

    bool ChangeCache(::Ice::Int buffnum)
    {
	return ChangeCache(buffnum, __defaultContext());
    }
    bool ChangeCache(::Ice::Int, const ::Ice::Context&);

    ::OPI::PIACC ChangeMode(::OPI::PIACC newmode)
    {
	return ChangeMode(newmode, __defaultContext());
    }
    ::OPI::PIACC ChangeMode(::OPI::PIACC, const ::Ice::Context&);

    bool Check(bool iniopt)
    {
	return Check(iniopt, __defaultContext());
    }
    bool Check(bool, const ::Ice::Context&);

    bool CheckPosition()
    {
	return CheckPosition(__defaultContext());
    }
    bool CheckPosition(const ::Ice::Context&);

    bool CheckUpdate(bool pcheckupdate)
    {
	return CheckUpdate(pcheckupdate, __defaultContext());
    }
    bool CheckUpdate(bool, const ::Ice::Context&);

    bool CheckWProtect()
    {
	return CheckWProtect(__defaultContext());
    }
    bool CheckWProtect(const ::Ice::Context&);

    bool Close()
    {
	return Close(__defaultContext());
    }
    bool Close(const ::Ice::Context&);

    ::Ice::Int Compare(const ::OPI::PropertyHandlePrx& cprophdl)
    {
	return Compare(cprophdl, __defaultContext());
    }
    ::Ice::Int Compare(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    ::Ice::Int CompareDate(::Ice::Long dateval)
    {
	return CompareDate(dateval, __defaultContext());
    }
    ::Ice::Int CompareDate(::Ice::Long, const ::Ice::Context&);

    ::Ice::Int CompareFloat(::Ice::Float doubleval)
    {
	return CompareFloat(doubleval, __defaultContext());
    }
    ::Ice::Int CompareFloat(::Ice::Float, const ::Ice::Context&);

    ::Ice::Int CompareInteger(::Ice::Int longval)
    {
	return CompareInteger(longval, __defaultContext());
    }
    ::Ice::Int CompareInteger(::Ice::Int, const ::Ice::Context&);

    ::Ice::Int CompareString(const ::std::string& pstring)
    {
	return CompareString(pstring, __defaultContext());
    }
    ::Ice::Int CompareString(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int CompareTime(::Ice::Long timeval)
    {
	return CompareTime(timeval, __defaultContext());
    }
    ::Ice::Int CompareTime(::Ice::Long, const ::Ice::Context&);

    ::Ice::Int CompareKey(const ::std::string& identkey1, const ::std::string& identkey2)
    {
	return CompareKey(identkey1, identkey2, __defaultContext());
    }
    ::Ice::Int CompareKey(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    ::Ice::Int CompareSortKey(const ::std::string& sortkey1, const ::std::string& sortkey2)
    {
	return CompareSortKey(sortkey1, sortkey2, __defaultContext());
    }
    ::Ice::Int CompareSortKey(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool CompareType(const ::OPI::PropertyHandlePrx& prophdl, bool convert)
    {
	return CompareType(prophdl, convert, __defaultContext());
    }
    bool CompareType(const ::OPI::PropertyHandlePrx&, bool, const ::Ice::Context&);

    bool Copy(const ::OPI::PropertyHandlePrx& sourcehandle, const ::std::string& newkey, ::Ice::Int setpos0, ::OPI::PIREPL replopt, ::OPI::PIREPL copytype)
    {
	return Copy(sourcehandle, newkey, setpos0, replopt, copytype, __defaultContext());
    }
    bool Copy(const ::OPI::PropertyHandlePrx&, const ::std::string&, ::Ice::Int, ::OPI::PIREPL, ::OPI::PIREPL, const ::Ice::Context&);

    bool CopyData(const ::OPI::PropertyHandlePrx& sourcehandle, ::OPI::PIREPL replopt)
    {
	return CopyData(sourcehandle, replopt, __defaultContext());
    }
    bool CopyData(const ::OPI::PropertyHandlePrx&, ::OPI::PIREPL, const ::Ice::Context&);

    bool CopyHandle(const ::OPI::PropertyHandlePrx& prophdl)
    {
	return CopyHandle(prophdl, __defaultContext());
    }
    bool CopyHandle(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool CopyInstanceArea(const ::OPI::PropertyHandlePrx& prophdl)
    {
	return CopyInstanceArea(prophdl, __defaultContext());
    }
    bool CopyInstanceArea(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    ::Ice::Int CopySet(const ::OPI::PropertyHandlePrx& csourcehandle, ::OPI::PIREPL replopt, ::OPI::PIREPL copytype, bool inversecheck)
    {
	return CopySet(csourcehandle, replopt, copytype, inversecheck, __defaultContext());
    }
    ::Ice::Int CopySet(const ::OPI::PropertyHandlePrx&, ::OPI::PIREPL, ::OPI::PIREPL, bool, const ::Ice::Context&);

    bool CreateTempExtent(const ::OPI::PropertyHandlePrx& prophdlref, const ::std::string& extnamesw)
    {
	return CreateTempExtent(prophdlref, extnamesw, __defaultContext());
    }
    bool CreateTempExtent(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool Delete(const ::OPI::PropertyHandlePrx& prophdl)
    {
	return Delete(prophdl, __defaultContext());
    }
    bool Delete(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool DeleteByKey(const ::std::string& sortkey)
    {
	return DeleteByKey(sortkey, __defaultContext());
    }
    bool DeleteByKey(const ::std::string&, const ::Ice::Context&);

    bool DeleteOnPosition(::Ice::Int setpos0w, bool deldep, bool delinst)
    {
	return DeleteOnPosition(setpos0w, deldep, delinst, __defaultContext());
    }
    bool DeleteOnPosition(::Ice::Int, bool, bool, const ::Ice::Context&);

    bool DeleteIndexEntry(::Ice::Int setpos0)
    {
	return DeleteIndexEntry(setpos0, __defaultContext());
    }
    bool DeleteIndexEntry(::Ice::Int, const ::Ice::Context&);

    bool DeleteSet(bool deldep)
    {
	return DeleteSet(deldep, __defaultContext());
    }
    bool DeleteSet(bool, const ::Ice::Context&);

    bool DisableKeyCheck()
    {
	return DisableKeyCheck(__defaultContext());
    }
    bool DisableKeyCheck(const ::Ice::Context&);

    bool Duplicate(::Ice::Int setpos0, ::OPI::PIREPL replopt)
    {
	return Duplicate(setpos0, replopt, __defaultContext());
    }
    bool Duplicate(::Ice::Int, ::OPI::PIREPL, const ::Ice::Context&);

    bool DuplicateKey(const ::std::string& identkey, ::OPI::PIREPL replopt)
    {
	return DuplicateKey(identkey, replopt, __defaultContext());
    }
    bool DuplicateKey(const ::std::string&, ::OPI::PIREPL, const ::Ice::Context&);

    bool EnableKeyCheck()
    {
	return EnableKeyCheck(__defaultContext());
    }
    bool EnableKeyCheck(const ::Ice::Context&);

    bool Execute()
    {
	return Execute(__defaultContext());
    }
    bool Execute(const ::Ice::Context&);

    ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx& resobhandle, const ::OPI::DBObjectHandlePrx& obhandle, const ::std::string& expression)
    {
	return ExecuteExpression(resobhandle, obhandle, expression, __defaultContext());
    }
    ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool ExecuteInstanceAction(const ::std::string& actionname, const ::std::string& parmstring)
    {
	return ExecuteInstanceAction(actionname, parmstring, __defaultContext());
    }
    bool ExecuteInstanceAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool ExecutePropertyAction(const ::std::string& actionname, const ::std::string& parmstring)
    {
	return ExecutePropertyAction(actionname, parmstring, __defaultContext());
    }
    bool ExecutePropertyAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool Exist()
    {
	return Exist(__defaultContext());
    }
    bool Exist(const ::Ice::Context&);

    ::std::string ExtractKey(const ::std::string& keyname)
    {
	return ExtractKey(keyname, __defaultContext());
    }
    ::std::string ExtractKey(const ::std::string&, const ::Ice::Context&);

    ::std::string ExtractSortKey(const ::std::string& sortkeyw)
    {
	return ExtractSortKey(sortkeyw, __defaultContext());
    }
    ::std::string ExtractSortKey(const ::std::string&, const ::Ice::Context&);

    ::std::string FirstKey()
    {
	return FirstKey(__defaultContext());
    }
    ::std::string FirstKey(const ::Ice::Context&);

    bool Get(const ::OPI::PropertyHandlePrx& prophdl)
    {
	return Get(prophdl, __defaultContext());
    }
    bool Get(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool GetAtPosition(::Ice::Int setpos0w)
    {
	return GetAtPosition(setpos0w, __defaultContext());
    }
    bool GetAtPosition(::Ice::Int, const ::Ice::Context&);

    bool GetByKey(const ::std::string& sortkey)
    {
	return GetByKey(sortkey, __defaultContext());
    }
    bool GetByKey(const ::std::string&, const ::Ice::Context&);

    ::std::string GetActionResult()
    {
	return GetActionResult(__defaultContext());
    }
    ::std::string GetActionResult(const ::Ice::Context&);

    ::std::string GetArea(const ::std::string& chkopt)
    {
	return GetArea(chkopt, __defaultContext());
    }
    ::std::string GetArea(const ::std::string&, const ::Ice::Context&);

    ::std::string GetAttribute(::Ice::Int indx0, bool fullpath, bool generic)
    {
	return GetAttribute(indx0, fullpath, generic, __defaultContext());
    }
    ::std::string GetAttribute(::Ice::Int, bool, bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx GetBaseProperty()
    {
	return GetBaseProperty(__defaultContext());
    }
    ::OPI::PropertyHandlePrx GetBaseProperty(const ::Ice::Context&);

    ::Ice::Int GetCollectionID()
    {
	return GetCollectionID(__defaultContext());
    }
    ::Ice::Int GetCollectionID(const ::Ice::Context&);

    ::OPI::PropertyHandlePrx GetCollectionProperty()
    {
	return GetCollectionProperty(__defaultContext());
    }
    ::OPI::PropertyHandlePrx GetCollectionProperty(const ::Ice::Context&);

    ::Ice::Int GetCount()
    {
	return GetCount(__defaultContext());
    }
    ::Ice::Int GetCount(const ::Ice::Context&);

    ::Ice::Int GetCurrentIndex()
    {
	return GetCurrentIndex(__defaultContext());
    }
    ::Ice::Int GetCurrentIndex(const ::Ice::Context&);

    ::Ice::Int GetCurrentSize()
    {
	return GetCurrentSize(__defaultContext());
    }
    ::Ice::Int GetCurrentSize(const ::Ice::Context&);

    ::std::string GetCurrentType()
    {
	return GetCurrentType(__defaultContext());
    }
    ::std::string GetCurrentType(const ::Ice::Context&);

    ::OPI::DatabaseHandlePrx GetDBHandle()
    {
	return GetDBHandle(__defaultContext());
    }
    ::OPI::DatabaseHandlePrx GetDBHandle(const ::Ice::Context&);

    ::Ice::Long GetDate(const ::std::string& proppath)
    {
	return GetDate(proppath, __defaultContext());
    }
    ::Ice::Long GetDate(const ::std::string&, const ::Ice::Context&);

    ::Ice::Long GetDateTime(const ::std::string& proppath)
    {
	return GetDateTime(proppath, __defaultContext());
    }
    ::Ice::Long GetDateTime(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int GetDay(const ::std::string& proppath)
    {
	return GetDay(proppath, __defaultContext());
    }
    ::Ice::Int GetDay(const ::std::string&, const ::Ice::Context&);

    ::OPI::DictionaryHandlePrx GetDictionary()
    {
	return GetDictionary(__defaultContext());
    }
    ::OPI::DictionaryHandlePrx GetDictionary(const ::Ice::Context&);

    ::Ice::Int GetDimension()
    {
	return GetDimension(__defaultContext());
    }
    ::Ice::Int GetDimension(const ::Ice::Context&);

    ::Ice::Float GetDouble(const ::std::string& proppath)
    {
	return GetDouble(proppath, __defaultContext());
    }
    ::Ice::Float GetDouble(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int GetExtInstModCount()
    {
	return GetExtInstModCount(__defaultContext());
    }
    ::Ice::Int GetExtInstModCount(const ::Ice::Context&);

    ::std::string GetExtentName()
    {
	return GetExtentName(__defaultContext());
    }
    ::std::string GetExtentName(const ::Ice::Context&);

    ::std::string GetGUID()
    {
	return GetGUID(__defaultContext());
    }
    ::std::string GetGUID(const ::Ice::Context&);

    ::Ice::Int GetGenAttrType(const ::std::string& wpropnames)
    {
	return GetGenAttrType(wpropnames, __defaultContext());
    }
    ::Ice::Int GetGenAttrType(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int GetGenOrderType()
    {
	return GetGenOrderType(__defaultContext());
    }
    ::Ice::Int GetGenOrderType(const ::Ice::Context&);

    ::Ice::Int GetGlobalID()
    {
	return GetGlobalID(__defaultContext());
    }
    ::Ice::Int GetGlobalID(const ::Ice::Context&);

    ::Ice::Int GetHours(const ::std::string& proppath)
    {
	return GetHours(proppath, __defaultContext());
    }
    ::Ice::Int GetHours(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int GetID(::Ice::Int setpos0w)
    {
	return GetID(setpos0w, __defaultContext());
    }
    ::Ice::Int GetID(::Ice::Int, const ::Ice::Context&);

    ::std::string GetIdentity(const ::std::string& idstring)
    {
	return GetIdentity(idstring, __defaultContext());
    }
    ::std::string GetIdentity(const ::std::string&, const ::Ice::Context&);

    ::std::string GetIndexName(::Ice::Int indx0)
    {
	return GetIndexName(indx0, __defaultContext());
    }
    ::std::string GetIndexName(::Ice::Int, const ::Ice::Context&);

    bool GetInitInstance()
    {
	return GetInitInstance(__defaultContext());
    }
    bool GetInitInstance(const ::Ice::Context&);

    ::Ice::Int GetInstModCount()
    {
	return GetInstModCount(__defaultContext());
    }
    ::Ice::Int GetInstModCount(const ::Ice::Context&);

    ::Ice::Int GetInt(const ::std::string& proppath)
    {
	return GetInt(proppath, __defaultContext());
    }
    ::Ice::Int GetInt(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int GetIntValue(const ::std::string& proppath)
    {
	return GetIntValue(proppath, __defaultContext());
    }
    ::Ice::Int GetIntValue(const ::std::string&, const ::Ice::Context&);

    ::std::string GetKey(::Ice::Int setpos0w)
    {
	return GetKey(setpos0w, __defaultContext());
    }
    ::std::string GetKey(::Ice::Int, const ::Ice::Context&);

    ::Ice::Int GetKeyLength()
    {
	return GetKeyLength(__defaultContext());
    }
    ::Ice::Int GetKeyLength(const ::Ice::Context&);

    ::Ice::Int GetLOID(::Ice::Int setpos0w)
    {
	return GetLOID(setpos0w, __defaultContext());
    }
    ::Ice::Int GetLOID(::Ice::Int, const ::Ice::Context&);

    ::Ice::Int GetLOIDByKey(const ::std::string& sortkey)
    {
	return GetLOIDByKey(sortkey, __defaultContext());
    }
    ::Ice::Int GetLOIDByKey(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int GetMinutes(const ::std::string& proppath)
    {
	return GetMinutes(proppath, __defaultContext());
    }
    ::Ice::Int GetMinutes(const ::std::string&, const ::Ice::Context&);

    ::OPI::PIACC GetMode()
    {
	return GetMode(__defaultContext());
    }
    ::OPI::PIACC GetMode(const ::Ice::Context&);

    ::Ice::Int GetMonth(const ::std::string& proppath)
    {
	return GetMonth(proppath, __defaultContext());
    }
    ::Ice::Int GetMonth(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int GetNormalized()
    {
	return GetNormalized(__defaultContext());
    }
    ::Ice::Int GetNormalized(const ::Ice::Context&);

    ::OPI::DBObjectHandlePrx GetObjectHandle()
    {
	return GetObjectHandle(__defaultContext());
    }
    ::OPI::DBObjectHandlePrx GetObjectHandle(const ::Ice::Context&);

    ::Ice::Int GetOrigin()
    {
	return GetOrigin(__defaultContext());
    }
    ::Ice::Int GetOrigin(const ::Ice::Context&);

    ::OPI::PropertyHandlePrx GetParentProperty()
    {
	return GetParentProperty(__defaultContext());
    }
    ::OPI::PropertyHandlePrx GetParentProperty(const ::Ice::Context&);

    ::OPI::PropertyHandlePrx GetPropertyHandle(const ::std::string& proppath)
    {
	return GetPropertyHandle(proppath, __defaultContext());
    }
    ::OPI::PropertyHandlePrx GetPropertyHandle(const ::std::string&, const ::Ice::Context&);

    ::std::string GetPropertyPath()
    {
	return GetPropertyPath(__defaultContext());
    }
    ::std::string GetPropertyPath(const ::Ice::Context&);

    ::Ice::Int GetRefModCount()
    {
	return GetRefModCount(__defaultContext());
    }
    ::Ice::Int GetRefModCount(const ::Ice::Context&);

    ::std::string GetReference(::Ice::Int indx0, bool fullpath, bool generic)
    {
	return GetReference(indx0, fullpath, generic, __defaultContext());
    }
    ::std::string GetReference(::Ice::Int, bool, bool, const ::Ice::Context&);

    bool GetRelative(::Ice::Int setpos0w)
    {
	return GetRelative(setpos0w, __defaultContext());
    }
    bool GetRelative(::Ice::Int, const ::Ice::Context&);

    ::Ice::Int GetRelativeCount()
    {
	return GetRelativeCount(__defaultContext());
    }
    ::Ice::Int GetRelativeCount(const ::Ice::Context&);

    ::Ice::Int GetRelativeIndex(bool lastopt)
    {
	return GetRelativeIndex(lastopt, __defaultContext());
    }
    ::Ice::Int GetRelativeIndex(bool, const ::Ice::Context&);

    ::Ice::Int GetSeconds(const ::std::string& proppath)
    {
	return GetSeconds(proppath, __defaultContext());
    }
    ::Ice::Int GetSeconds(const ::std::string&, const ::Ice::Context&);

    ::std::string GetSelectedKey()
    {
	return GetSelectedKey(__defaultContext());
    }
    ::std::string GetSelectedKey(const ::Ice::Context&);

    ::Ice::Int GetSize()
    {
	return GetSize(__defaultContext());
    }
    ::Ice::Int GetSize(const ::Ice::Context&);

    ::Ice::Int GetSizeOf()
    {
	return GetSizeOf(__defaultContext());
    }
    ::Ice::Int GetSizeOf(const ::Ice::Context&);

    ::std::string GetSortKey()
    {
	return GetSortKey(__defaultContext());
    }
    ::std::string GetSortKey(const ::Ice::Context&);

    ::Ice::Int GetSortKeyLength()
    {
	return GetSortKeyLength(__defaultContext());
    }
    ::Ice::Int GetSortKeyLength(const ::Ice::Context&);

    ::std::string GetString(const ::std::string& proppath)
    {
	return GetString(proppath, __defaultContext());
    }
    ::std::string GetString(const ::std::string&, const ::Ice::Context&);

    ::Ice::Int GetStringLength()
    {
	return GetStringLength(__defaultContext());
    }
    ::Ice::Int GetStringLength(const ::Ice::Context&);

    ::std::string GetStringValue(const ::std::string& proppath)
    {
	return GetStringValue(proppath, __defaultContext());
    }
    ::std::string GetStringValue(const ::std::string&, const ::Ice::Context&);

    ::std::string GetSubString(::Ice::Int startpos, ::Ice::Int length)
    {
	return GetSubString(startpos, length, __defaultContext());
    }
    ::std::string GetSubString(::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    ::std::string GetText(const ::std::string& proppath)
    {
	return GetText(proppath, __defaultContext());
    }
    ::std::string GetText(const ::std::string&, const ::Ice::Context&);

    ::Ice::Long GetTime(const ::std::string& proppath)
    {
	return GetTime(proppath, __defaultContext());
    }
    ::Ice::Long GetTime(const ::std::string&, const ::Ice::Context&);

    ::std::string GetType()
    {
	return GetType(__defaultContext());
    }
    ::std::string GetType(const ::Ice::Context&);

    bool GetValid()
    {
	return GetValid(__defaultContext());
    }
    bool GetValid(const ::Ice::Context&);

    ::Ice::Int GetVersion()
    {
	return GetVersion(__defaultContext());
    }
    ::Ice::Int GetVersion(const ::Ice::Context&);

    ::Ice::Int GetYear(const ::std::string& proppath)
    {
	return GetYear(proppath, __defaultContext());
    }
    ::Ice::Int GetYear(const ::std::string&, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx Group(const ::OPI::PropertyHandlePrx& prophdlref, const ::std::string& groupingrule, bool distinct)
    {
	return Group(prophdlref, groupingrule, distinct, __defaultContext());
    }
    ::OPI::PropertyHandlePrx Group(const ::OPI::PropertyHandlePrx&, const ::std::string&, bool, const ::Ice::Context&);

    bool HasData()
    {
	return HasData(__defaultContext());
    }
    bool HasData(const ::Ice::Context&);

    bool HasDescription()
    {
	return HasDescription(__defaultContext());
    }
    bool HasDescription(const ::Ice::Context&);

    bool HasGenericAttributes()
    {
	return HasGenericAttributes(__defaultContext());
    }
    bool HasGenericAttributes(const ::Ice::Context&);

    bool HasIndex()
    {
	return HasIndex(__defaultContext());
    }
    bool HasIndex(const ::Ice::Context&);

    bool Inherits(const ::std::string& strnames)
    {
	return Inherits(strnames, __defaultContext());
    }
    bool Inherits(const ::std::string&, const ::Ice::Context&);

    bool InsertString(const ::std::string& pstring, ::Ice::Int position)
    {
	return InsertString(pstring, position, __defaultContext());
    }
    bool InsertString(const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    bool InsertTerminator(const ::std::string& pstring)
    {
	return InsertTerminator(pstring, __defaultContext());
    }
    bool InsertTerminator(const ::std::string&, const ::Ice::Context&);

    bool InstanceInserted()
    {
	return InstanceInserted(__defaultContext());
    }
    bool InstanceInserted(const ::Ice::Context&);

    ::std::string InstanceToString(const ::std::string& stringsep, const ::std::string& fieldsep, const ::std::string& blocksep, const ::std::string& emptystring, bool skiptrans)
    {
	return InstanceToString(stringsep, fieldsep, blocksep, emptystring, skiptrans, __defaultContext());
    }
    ::std::string InstanceToString(const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx Intersect(const ::OPI::PropertyHandlePrx& prophdl1, const ::OPI::PropertyHandlePrx& prophdl2, const ::std::string& skopt)
    {
	return Intersect(prophdl1, prophdl2, skopt, __defaultContext());
    }
    ::OPI::PropertyHandlePrx Intersect(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool Is(const ::OPI::PropertyHandlePrx& prophdl)
    {
	return Is(prophdl, __defaultContext());
    }
    bool Is(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool IsA(const ::std::string& strnames)
    {
	return IsA(strnames, __defaultContext());
    }
    bool IsA(const ::std::string&, const ::Ice::Context&);

    bool IsActive()
    {
	return IsActive(__defaultContext());
    }
    bool IsActive(const ::Ice::Context&);

    bool IsAttribute()
    {
	return IsAttribute(__defaultContext());
    }
    bool IsAttribute(const ::Ice::Context&);

    bool IsAutoSelection()
    {
	return IsAutoSelection(__defaultContext());
    }
    bool IsAutoSelection(const ::Ice::Context&);

    bool IsBasedOn(const ::std::string& strnames)
    {
	return IsBasedOn(strnames, __defaultContext());
    }
    bool IsBasedOn(const ::std::string&, const ::Ice::Context&);

    bool IsBasetypeProperty()
    {
	return IsBasetypeProperty(__defaultContext());
    }
    bool IsBasetypeProperty(const ::Ice::Context&);

    bool IsBasicType()
    {
	return IsBasicType(__defaultContext());
    }
    bool IsBasicType(const ::Ice::Context&);

    bool IsClient()
    {
	return IsClient(__defaultContext());
    }
    bool IsClient(const ::Ice::Context&);

    bool IsCollection(const ::std::string& chkopt)
    {
	return IsCollection(chkopt, __defaultContext());
    }
    bool IsCollection(const ::std::string&, const ::Ice::Context&);

    bool IsCollectionUpdate()
    {
	return IsCollectionUpdate(__defaultContext());
    }
    bool IsCollectionUpdate(const ::Ice::Context&);

    bool IsCopyHandle()
    {
	return IsCopyHandle(__defaultContext());
    }
    bool IsCopyHandle(const ::Ice::Context&);

    bool IsDirty()
    {
	return IsDirty(__defaultContext());
    }
    bool IsDirty(const ::Ice::Context&);

    bool IsEmpty()
    {
	return IsEmpty(__defaultContext());
    }
    bool IsEmpty(const ::Ice::Context&);

    bool IsEnumeration()
    {
	return IsEnumeration(__defaultContext());
    }
    bool IsEnumeration(const ::Ice::Context&);

    bool IsGenericAttribute()
    {
	return IsGenericAttribute(__defaultContext());
    }
    bool IsGenericAttribute(const ::Ice::Context&);

    bool IsInitInstance()
    {
	return IsInitInstance(__defaultContext());
    }
    bool IsInitInstance(const ::Ice::Context&);

    bool IsMemo(const ::std::string& chkopt)
    {
	return IsMemo(chkopt, __defaultContext());
    }
    bool IsMemo(const ::std::string&, const ::Ice::Context&);

    bool IsModified()
    {
	return IsModified(__defaultContext());
    }
    bool IsModified(const ::Ice::Context&);

    bool IsNewInstance()
    {
	return IsNewInstance(__defaultContext());
    }
    bool IsNewInstance(const ::Ice::Context&);

    bool IsNumeric()
    {
	return IsNumeric(__defaultContext());
    }
    bool IsNumeric(const ::Ice::Context&);

    bool IsOldInstance()
    {
	return IsOldInstance(__defaultContext());
    }
    bool IsOldInstance(const ::Ice::Context&);

    bool IsOwner()
    {
	return IsOwner(__defaultContext());
    }
    bool IsOwner(const ::Ice::Context&);

    bool IsPositioned(const ::std::string& chkopt)
    {
	return IsPositioned(chkopt, __defaultContext());
    }
    bool IsPositioned(const ::std::string&, const ::Ice::Context&);

    bool IsReadOnly()
    {
	return IsReadOnly(__defaultContext());
    }
    bool IsReadOnly(const ::Ice::Context&);

    bool IsSelected(const ::std::string& chkopt)
    {
	return IsSelected(chkopt, __defaultContext());
    }
    bool IsSelected(const ::std::string&, const ::Ice::Context&);

    bool IsSensitive(const ::std::string& proppath)
    {
	return IsSensitive(proppath, __defaultContext());
    }
    bool IsSensitive(const ::std::string&, const ::Ice::Context&);

    bool IsServer()
    {
	return IsServer(__defaultContext());
    }
    bool IsServer(const ::Ice::Context&);

    bool IsShareBaseHandle(const ::std::string& chkopt)
    {
	return IsShareBaseHandle(chkopt, __defaultContext());
    }
    bool IsShareBaseHandle(const ::std::string&, const ::Ice::Context&);

    bool IsStructure()
    {
	return IsStructure(__defaultContext());
    }
    bool IsStructure(const ::Ice::Context&);

    bool IsText(const ::std::string& chkopt)
    {
	return IsText(chkopt, __defaultContext());
    }
    bool IsText(const ::std::string&, const ::Ice::Context&);

    bool IsTransient()
    {
	return IsTransient(__defaultContext());
    }
    bool IsTransient(const ::Ice::Context&);

    bool IsTrue(const ::std::string& proppath)
    {
	return IsTrue(proppath, __defaultContext());
    }
    bool IsTrue(const ::std::string&, const ::Ice::Context&);

    bool IsTyped()
    {
	return IsTyped(__defaultContext());
    }
    bool IsTyped(const ::Ice::Context&);

    bool IsUserHandle()
    {
	return IsUserHandle(__defaultContext());
    }
    bool IsUserHandle(const ::Ice::Context&);

    bool IsValid(bool topt)
    {
	return IsValid(topt, __defaultContext());
    }
    bool IsValid(bool, const ::Ice::Context&);

    bool IsValidText(const ::std::string& pstring)
    {
	return IsValidText(pstring, __defaultContext());
    }
    bool IsValidText(const ::std::string&, const ::Ice::Context&);

    bool IsVariableType()
    {
	return IsVariableType(__defaultContext());
    }
    bool IsVariableType(const ::Ice::Context&);

    bool IsWeakTyped()
    {
	return IsWeakTyped(__defaultContext());
    }
    bool IsWeakTyped(const ::Ice::Context&);

    bool IsWrite()
    {
	return IsWrite(__defaultContext());
    }
    bool IsWrite(const ::Ice::Context&);

    bool Locate(::Ice::Int obident, bool readopt)
    {
	return Locate(obident, readopt, __defaultContext());
    }
    bool Locate(::Ice::Int, bool, const ::Ice::Context&);

    bool LocatePath()
    {
	return LocatePath(__defaultContext());
    }
    bool LocatePath(const ::Ice::Context&);

    bool Lock()
    {
	return Lock(__defaultContext());
    }
    bool Lock(const ::Ice::Context&);

    bool LockSet()
    {
	return LockSet(__defaultContext());
    }
    bool LockSet(const ::Ice::Context&);

    void MarkUnused()
    {
	MarkUnused(__defaultContext());
    }
    void MarkUnused(const ::Ice::Context&);

    void MarkUsed()
    {
	MarkUsed(__defaultContext());
    }
    void MarkUsed(const ::Ice::Context&);

    ::OPI::PropertyHandlePrx Minus(const ::OPI::PropertyHandlePrx& prophdl1, const ::OPI::PropertyHandlePrx& prophdl2, const ::std::string& skopt)
    {
	return Minus(prophdl1, prophdl2, skopt, __defaultContext());
    }
    ::OPI::PropertyHandlePrx Minus(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool Modify()
    {
	return Modify(__defaultContext());
    }
    bool Modify(const ::Ice::Context&);

    bool Move(const ::OPI::PropertyHandlePrx& sourcehandle, const ::std::string& newkey, ::OPI::PIREPL replopt)
    {
	return Move(sourcehandle, newkey, replopt, __defaultContext());
    }
    bool Move(const ::OPI::PropertyHandlePrx&, const ::std::string&, ::OPI::PIREPL, const ::Ice::Context&);

    bool MoveDown()
    {
	return MoveDown(__defaultContext());
    }
    bool MoveDown(const ::Ice::Context&);

    bool MoveUp()
    {
	return MoveUp(__defaultContext());
    }
    bool MoveUp(const ::Ice::Context&);

    ::std::string NextKey(const ::std::string& sortkeyw, ::Ice::Int switchlevel)
    {
	return NextKey(sortkeyw, switchlevel, __defaultContext());
    }
    ::std::string NextKey(const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    bool NoWrite()
    {
	return NoWrite(__defaultContext());
    }
    bool NoWrite(const ::Ice::Context&);

    bool Open()
    {
	return Open(__defaultContext());
    }
    bool Open(const ::Ice::Context&);

    bool OpenBigInt(::Ice::Int int64val)
    {
	return OpenBigInt(int64val, __defaultContext());
    }
    bool OpenBigInt(::Ice::Int, const ::Ice::Context&);

    bool OpenBoolean(bool logval)
    {
	return OpenBoolean(logval, __defaultContext());
    }
    bool OpenBoolean(bool, const ::Ice::Context&);

    bool OpenChild(const ::OPI::PropertyHandlePrx& prophdl, const ::std::string& proppath)
    {
	return OpenChild(prophdl, proppath, __defaultContext());
    }
    bool OpenChild(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool OpenChildReference(const ::OPI::PropertyHandlePrx& ppropertyhandle, const ::std::string& proppath)
    {
	return OpenChildReference(ppropertyhandle, proppath, __defaultContext());
    }
    bool OpenChildReference(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    bool OpenCopy(const ::OPI::PropertyHandlePrx& cprophdl)
    {
	return OpenCopy(cprophdl, __defaultContext());
    }
    bool OpenCopy(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool OpenDate(::Ice::Long dateval)
    {
	return OpenDate(dateval, __defaultContext());
    }
    bool OpenDate(::Ice::Long, const ::Ice::Context&);

    bool OpenExtent(const ::OPI::DBObjectHandlePrx& objecthandle, const ::std::string& extnames, ::OPI::PIACC accopt, bool transientw, const ::std::string& keynamew)
    {
	return OpenExtent(objecthandle, extnames, accopt, transientw, keynamew, __defaultContext());
    }
    bool OpenExtent(const ::OPI::DBObjectHandlePrx&, const ::std::string&, ::OPI::PIACC, bool, const ::std::string&, const ::Ice::Context&);

    bool OpenFloat(::Ice::Float dblvalue)
    {
	return OpenFloat(dblvalue, __defaultContext());
    }
    bool OpenFloat(::Ice::Float, const ::Ice::Context&);

    bool OpenInteger(::Ice::Int intval)
    {
	return OpenInteger(intval, __defaultContext());
    }
    bool OpenInteger(::Ice::Int, const ::Ice::Context&);

    bool OpenReference(const ::OPI::PropertyHandlePrx& ppropertyhandle)
    {
	return OpenReference(ppropertyhandle, __defaultContext());
    }
    bool OpenReference(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool OpenSizedString(const ::std::string& pstring, ::Ice::Int stringlen)
    {
	return OpenSizedString(pstring, stringlen, __defaultContext());
    }
    bool OpenSizedString(const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    bool OpenString(const ::std::string& pstring, bool convopt)
    {
	return OpenString(pstring, convopt, __defaultContext());
    }
    bool OpenString(const ::std::string&, bool, const ::Ice::Context&);

    bool OpenTime(::Ice::Long timeval)
    {
	return OpenTime(timeval, __defaultContext());
    }
    bool OpenTime(::Ice::Long, const ::Ice::Context&);

    bool OpenTimestamp(::Ice::Long datetimeval)
    {
	return OpenTimestamp(datetimeval, __defaultContext());
    }
    bool OpenTimestamp(::Ice::Long, const ::Ice::Context&);

    bool OpenHierarchy(const ::OPI::PropertyHandlePrx& bottomph, const ::OPI::PropertyHandlePrx& topph, bool pathopt, ::OPI::PIACC accmode, bool copyselection)
    {
	return OpenHierarchy(bottomph, topph, pathopt, accmode, copyselection, __defaultContext());
    }
    bool OpenHierarchy(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, bool, ::OPI::PIACC, bool, const ::Ice::Context&);

    bool OwnsData()
    {
	return OwnsData(__defaultContext());
    }
    bool OwnsData(const ::Ice::Context&);

    bool Position(::Ice::Int count)
    {
	return Position(count, __defaultContext());
    }
    bool Position(::Ice::Int, const ::Ice::Context&);

    bool PositionTop()
    {
	return PositionTop(__defaultContext());
    }
    bool PositionTop(const ::Ice::Context&);

    ::OPI::PropertyHandlePrx Power(const ::OPI::PropertyHandlePrx& prophdl)
    {
	return Power(prophdl, __defaultContext());
    }
    ::OPI::PropertyHandlePrx Power(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool ProvGenAttribute()
    {
	return ProvGenAttribute(__defaultContext());
    }
    bool ProvGenAttribute(const ::Ice::Context&);

    bool Provide(const ::OPI::PropertyHandlePrx& prophdl)
    {
	return Provide(prophdl, __defaultContext());
    }
    bool Provide(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool ProvideAtPosition(::Ice::Int setpos0w)
    {
	return ProvideAtPosition(setpos0w, __defaultContext());
    }
    bool ProvideAtPosition(::Ice::Int, const ::Ice::Context&);

    bool ProvideByKey(const ::std::string& sortkey)
    {
	return ProvideByKey(sortkey, __defaultContext());
    }
    bool ProvideByKey(const ::std::string&, const ::Ice::Context&);

    bool ProvideArea()
    {
	return ProvideArea(__defaultContext());
    }
    bool ProvideArea(const ::Ice::Context&);

    ::std::string ProvideGUID()
    {
	return ProvideGUID(__defaultContext());
    }
    ::std::string ProvideGUID(const ::Ice::Context&);

    bool ProvideGlobal(const ::OPI::PropertyHandlePrx& prophdl)
    {
	return ProvideGlobal(prophdl, __defaultContext());
    }
    bool ProvideGlobal(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool ProvideGlobalAtPosition(::Ice::Int setpos0w)
    {
	return ProvideGlobalAtPosition(setpos0w, __defaultContext());
    }
    bool ProvideGlobalAtPosition(::Ice::Int, const ::Ice::Context&);

    bool ProvideGlobalByKey(const ::std::string& sortkey)
    {
	return ProvideGlobalByKey(sortkey, __defaultContext());
    }
    bool ProvideGlobalByKey(const ::std::string&, const ::Ice::Context&);

    ::OPI::OperationHandlePrx ProvideOperation(const ::std::string& expression)
    {
	return ProvideOperation(expression, __defaultContext());
    }
    ::OPI::OperationHandlePrx ProvideOperation(const ::std::string&, const ::Ice::Context&);

    bool Refresh()
    {
	return Refresh(__defaultContext());
    }
    bool Refresh(const ::Ice::Context&);

    bool ReleaseBuffer()
    {
	return ReleaseBuffer(__defaultContext());
    }
    bool ReleaseBuffer(const ::Ice::Context&);

    bool RemoveFromCollection()
    {
	return RemoveFromCollection(__defaultContext());
    }
    bool RemoveFromCollection(const ::Ice::Context&);

    bool RemoveString(const ::std::string& pstring, ::Ice::Int position, ::Ice::Int len)
    {
	return RemoveString(pstring, position, len, __defaultContext());
    }
    bool RemoveString(const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    bool RemoveTerminator(const ::std::string& pstring)
    {
	return RemoveTerminator(pstring, __defaultContext());
    }
    bool RemoveTerminator(const ::std::string&, const ::Ice::Context&);

    bool Rename(const ::std::string& newkey)
    {
	return Rename(newkey, __defaultContext());
    }
    bool Rename(const ::std::string&, const ::Ice::Context&);

    bool RepairIndex(const ::std::string& keynamew, const ::std::string& attrstrw)
    {
	return RepairIndex(keynamew, attrstrw, __defaultContext());
    }
    bool RepairIndex(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool ReplaceString(const ::std::string& oldstr, const ::std::string& newstr)
    {
	return ReplaceString(oldstr, newstr, __defaultContext());
    }
    bool ReplaceString(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool ReplaceSysVariables()
    {
	return ReplaceSysVariables(__defaultContext());
    }
    bool ReplaceSysVariables(const ::Ice::Context&);

    bool Reset()
    {
	return Reset(__defaultContext());
    }
    bool Reset(const ::Ice::Context&);

    void ResetDirty()
    {
	ResetDirty(__defaultContext());
    }
    void ResetDirty(const ::Ice::Context&);

    bool ResetTransientProperty()
    {
	return ResetTransientProperty(__defaultContext());
    }
    bool ResetTransientProperty(const ::Ice::Context&);

    bool ResetWProtect()
    {
	return ResetWProtect(__defaultContext());
    }
    bool ResetWProtect(const ::Ice::Context&);

    bool Save(const ::std::string& savopt, bool switchopt)
    {
	return Save(savopt, switchopt, __defaultContext());
    }
    bool Save(const ::std::string&, bool, const ::Ice::Context&);

    ::Ice::Int SearchText(const ::std::string& pstring, ::Ice::Int curpos, bool caseopt)
    {
	return SearchText(pstring, curpos, caseopt, __defaultContext());
    }
    ::Ice::Int SearchText(const ::std::string&, ::Ice::Int, bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx Select(const ::OPI::PropertyHandlePrx& prophdlref, const ::std::string& expression)
    {
	return Select(prophdlref, expression, __defaultContext());
    }
    ::OPI::PropertyHandlePrx Select(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    void SetActionResult(const ::std::string& resultstring)
    {
	SetActionResult(resultstring, __defaultContext());
    }
    void SetActionResult(const ::std::string&, const ::Ice::Context&);

    bool SetContextVariables(const ::std::string& contextstring)
    {
	return SetContextVariables(contextstring, __defaultContext());
    }
    bool SetContextVariables(const ::std::string&, const ::Ice::Context&);

    void SetDirty()
    {
	SetDirty(__defaultContext());
    }
    void SetDirty(const ::Ice::Context&);

    bool SetDynLength()
    {
	return SetDynLength(__defaultContext());
    }
    bool SetDynLength(const ::Ice::Context&);

    bool SetGenAttribute(const ::std::string& attrstr, const ::std::string& proppath)
    {
	return SetGenAttribute(attrstr, proppath, __defaultContext());
    }
    bool SetGenAttribute(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool SetKey(const ::std::string& identkey)
    {
	return SetKey(identkey, __defaultContext());
    }
    bool SetKey(const ::std::string&, const ::Ice::Context&);

    void SetModified()
    {
	SetModified(__defaultContext());
    }
    void SetModified(const ::Ice::Context&);

    bool SetNormalized(::Ice::Int longval)
    {
	return SetNormalized(longval, __defaultContext());
    }
    bool SetNormalized(::Ice::Int, const ::Ice::Context&);

    bool SetOrder(const ::std::string& keyname, const ::std::string& attrstr)
    {
	return SetOrder(keyname, attrstr, __defaultContext());
    }
    bool SetOrder(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    bool SetSelection(const ::std::string& expression)
    {
	return SetSelection(expression, __defaultContext());
    }
    bool SetSelection(const ::std::string&, const ::Ice::Context&);

    bool SetSortKey(const ::std::string& sortkey)
    {
	return SetSortKey(sortkey, __defaultContext());
    }
    bool SetSortKey(const ::std::string&, const ::Ice::Context&);

    bool SetTransientProperty(const ::OPI::PropertyHandlePrx& prophdl)
    {
	return SetTransientProperty(prophdl, __defaultContext());
    }
    bool SetTransientProperty(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    bool SetType(const ::std::string& strnames)
    {
	return SetType(strnames, __defaultContext());
    }
    bool SetType(const ::std::string&, const ::Ice::Context&);

    bool SetUpdate(bool pcheckupdate)
    {
	return SetUpdate(pcheckupdate, __defaultContext());
    }
    bool SetUpdate(bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx SetValue(const ::OPI::PropertyHandlePrx& cprophdl, bool pcheckupdate)
    {
	return SetValue(cprophdl, pcheckupdate, __defaultContext());
    }
    ::OPI::PropertyHandlePrx SetValue(const ::OPI::PropertyHandlePrx&, bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx SetValueBigInt(::Ice::Int int64val, bool pcheckupdate)
    {
	return SetValueBigInt(int64val, pcheckupdate, __defaultContext());
    }
    ::OPI::PropertyHandlePrx SetValueBigInt(::Ice::Int, bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx SetValueBoolean(bool logval, bool pcheckupdate)
    {
	return SetValueBoolean(logval, pcheckupdate, __defaultContext());
    }
    ::OPI::PropertyHandlePrx SetValueBoolean(bool, bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx SetValueDate(::Ice::Long dateval, bool pcheckupdate)
    {
	return SetValueDate(dateval, pcheckupdate, __defaultContext());
    }
    ::OPI::PropertyHandlePrx SetValueDate(::Ice::Long, bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx SetValueFloat(::Ice::Float dblvalue, bool pcheckupdate)
    {
	return SetValueFloat(dblvalue, pcheckupdate, __defaultContext());
    }
    ::OPI::PropertyHandlePrx SetValueFloat(::Ice::Float, bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx SetValueInteger(::Ice::Int longval, bool pcheckupdate)
    {
	return SetValueInteger(longval, pcheckupdate, __defaultContext());
    }
    ::OPI::PropertyHandlePrx SetValueInteger(::Ice::Int, bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx SetValueString(const ::std::string& pstring, bool pcheckupdate, bool convopt)
    {
	return SetValueString(pstring, pcheckupdate, convopt, __defaultContext());
    }
    ::OPI::PropertyHandlePrx SetValueString(const ::std::string&, bool, bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx SetValueTime(::Ice::Long timeval, bool pcheckupdate)
    {
	return SetValueTime(timeval, pcheckupdate, __defaultContext());
    }
    ::OPI::PropertyHandlePrx SetValueTime(::Ice::Long, bool, const ::Ice::Context&);

    ::OPI::PropertyHandlePrx SetValueTimestamp(::Ice::Long datetimeval, bool pcheckupdate)
    {
	return SetValueTimestamp(datetimeval, pcheckupdate, __defaultContext());
    }
    ::OPI::PropertyHandlePrx SetValueTimestamp(::Ice::Long, bool, const ::Ice::Context&);

    bool SetVersion(::Ice::Int versionnr)
    {
	return SetVersion(versionnr, __defaultContext());
    }
    bool SetVersion(::Ice::Int, const ::Ice::Context&);

    bool SetWProtect()
    {
	return SetWProtect(__defaultContext());
    }
    bool SetWProtect(const ::Ice::Context&);

    bool ToTop()
    {
	return ToTop(__defaultContext());
    }
    bool ToTop(const ::Ice::Context&);

    ::OPI::PropertyHandlePrx Union(const ::OPI::PropertyHandlePrx& prophdl1, const ::OPI::PropertyHandlePrx& prophdl2, const ::std::string& skopt, bool distinct)
    {
	return Union(prophdl1, prophdl2, skopt, distinct, __defaultContext());
    }
    ::OPI::PropertyHandlePrx Union(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, bool, const ::Ice::Context&);

    bool Unlock()
    {
	return Unlock(__defaultContext());
    }
    bool Unlock(const ::Ice::Context&);

    bool UnlockSet()
    {
	return UnlockSet(__defaultContext());
    }
    bool UnlockSet(const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class OPIFactory : virtual public ::IceProxy::Ice::Object
{
public:

    void Destroy()
    {
	Destroy(__defaultContext());
    }
    void Destroy(const ::Ice::Context&);

    ::OPI::CheckOptionsPrx GetCheckOptions()
    {
	return GetCheckOptions(__defaultContext());
    }
    ::OPI::CheckOptionsPrx GetCheckOptions(const ::Ice::Context&);

    ::OPI::DBObjectHandlePrx GetDBObjectHandle()
    {
	return GetDBObjectHandle(__defaultContext());
    }
    ::OPI::DBObjectHandlePrx GetDBObjectHandle(const ::Ice::Context&);

    ::OPI::DataSourceHandlePrx GetDataSourceHandle()
    {
	return GetDataSourceHandle(__defaultContext());
    }
    ::OPI::DataSourceHandlePrx GetDataSourceHandle(const ::Ice::Context&);

    ::OPI::DatabaseHandlePrx GetDatabaseHandle()
    {
	return GetDatabaseHandle(__defaultContext());
    }
    ::OPI::DatabaseHandlePrx GetDatabaseHandle(const ::Ice::Context&);

    ::OPI::DictionaryHandlePrx GetDictionaryHandle()
    {
	return GetDictionaryHandle(__defaultContext());
    }
    ::OPI::DictionaryHandlePrx GetDictionaryHandle(const ::Ice::Context&);

    ::OPI::ODABAClientPrx GetODABAClient()
    {
	return GetODABAClient(__defaultContext());
    }
    ::OPI::ODABAClientPrx GetODABAClient(const ::Ice::Context&);

    ::OPI::OperationHandlePrx GetOperationHandle()
    {
	return GetOperationHandle(__defaultContext());
    }
    ::OPI::OperationHandlePrx GetOperationHandle(const ::Ice::Context&);

    ::OPI::PropertyHandlePrx GetPropertyHandle()
    {
	return GetPropertyHandle(__defaultContext());
    }
    ::OPI::PropertyHandlePrx GetPropertyHandle(const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class Session : virtual public ::IceProxy::Ice::Object
{
public:

    ::OPI::OPIFactoryPrx CreateSession()
    {
	return CreateSession(__defaultContext());
    }
    ::OPI::OPIFactoryPrx CreateSession(const ::Ice::Context&);

    void Destroy()
    {
	Destroy(__defaultContext());
    }
    void Destroy(const ::Ice::Context&);

    void TimeOut(::Ice::Int seconds)
    {
	TimeOut(seconds, __defaultContext());
    }
    void TimeOut(::Ice::Int, const ::Ice::Context&);

    ::std::string getName()
    {
	return getName(__defaultContext());
    }
    ::std::string getName(const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

class SessionFactory : virtual public ::IceProxy::Ice::Object
{
public:

    ::OPI::SessionPrx CreateProxy(const ::std::string& name)
    {
	return CreateProxy(name, __defaultContext());
    }
    ::OPI::SessionPrx CreateProxy(const ::std::string&, const ::Ice::Context&);

    void shutdown()
    {
	shutdown(__defaultContext());
    }
    void shutdown(const ::Ice::Context&);
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
};

}

}

namespace IceDelegate
{

namespace OPI
{

class CheckOptions : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool Initialize(const ::std::string&, const ::Ice::Context&) = 0;
};

class DBObjectHandle : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::Ice::Int BeginTransaction(bool, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool ChangeTimeStamp(::Ice::Int, ::Ice::Long, const ::Ice::Context&) = 0;

    virtual bool CommitTransaction(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx CreateTempPropertyHandle(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool DeleteExtent(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool DeleteExtentRef(const ::std::string&, const ::Ice::Context&) = 0;

    virtual void DisableEventHandling(const ::Ice::Context&) = 0;

    virtual void EnableEventHandling(const ::Ice::Context&) = 0;

    virtual bool EventHandling(const ::Ice::Context&) = 0;

    virtual bool ExecuteDBObjectAction(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool ExtentExist(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::OPI::PIACC GetAccess(const ::Ice::Context&) = 0;

    virtual ::std::string GetActionResult(const ::Ice::Context&) = 0;

    virtual ::OPI::DatabaseHandlePrx GetDBHandle(const ::Ice::Context&) = 0;

    virtual ::OPI::DataSourceHandlePrx GetDataSource(const ::Ice::Context&) = 0;

    virtual ::OPI::DictionaryHandlePrx GetDictionary(const ::Ice::Context&) = 0;

    virtual ::std::string GetExtent(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::OPI::DBObjectHandlePrx GetHighObject(const ::Ice::Context&) = 0;

    virtual ::std::string GetObject(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::std::string GetServerVariable(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetSystemVersion(const ::Ice::Context&) = 0;

    virtual ::Ice::Long GetTimeStamp(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetTransactionLevel(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetVersion(::Ice::Long, const ::Ice::Context&) = 0;

    virtual bool IsClient(const ::Ice::Context&) = 0;

    virtual bool IsEmpty(const ::Ice::Context&) = 0;

    virtual bool IsOpened(const ::Ice::Context&) = 0;

    virtual bool IsServer(const ::Ice::Context&) = 0;

    virtual bool IsValid(const ::Ice::Context&) = 0;

    virtual bool NewVersion(::Ice::Long, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool OpenObject(const ::OPI::DBObjectHandlePrx&, const ::std::string&, ::OPI::PIACC, ::Ice::Int, ::OPI::ResourceTypes, const ::Ice::Context&) = 0;

    virtual bool RollBack(::Ice::Int, const ::Ice::Context&) = 0;

    virtual void SetActionResult(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int SetOverload(bool, const ::Ice::Context&) = 0;

    virtual bool SetServerVariable(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetUserDefinedIdentity(bool, const ::Ice::Context&) = 0;

    virtual bool SetVersion(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool SetVersioni1(::Ice::Long, const ::Ice::Context&) = 0;

    virtual bool SetVersioni2(::Ice::Long, const ::Ice::Context&) = 0;

    virtual ::Ice::Int VersionCount(const ::Ice::Context&) = 0;
};

class DataSourceHandle : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool BeginTransaction(bool, const ::Ice::Context&) = 0;

    virtual bool Close(const ::Ice::Context&) = 0;

    virtual bool CloseDBObject(const ::Ice::Context&) = 0;

    virtual bool CloseDatabase(const ::Ice::Context&) = 0;

    virtual bool CloseDictionary(const ::Ice::Context&) = 0;

    virtual bool CloseProperty(const ::Ice::Context&) = 0;

    virtual bool CloseResourceDB(const ::Ice::Context&) = 0;

    virtual bool CommitTransaction(const ::Ice::Context&) = 0;

    virtual bool Connect(const ::OPI::ODABAClientPrx&, const ::Ice::Context&) = 0;

    virtual bool Disconnect(const ::Ice::Context&) = 0;

    virtual bool Open(const ::OPI::ODABAClientPrx&, ::OPI::PIACC, const ::Ice::Context&) = 0;

    virtual bool Openi02(const ::OPI::ODABAClientPrx&, const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool Openi1(const ::OPI::ODABAClientPrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::OPI::DBObjectHandlePrx OpenDBObject(const ::Ice::Context&) = 0;

    virtual ::OPI::DatabaseHandlePrx OpenDatabase(const ::Ice::Context&) = 0;

    virtual ::OPI::DictionaryHandlePrx OpenDictionary(::OPI::PIACC, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx OpenProperty(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::OPI::DatabaseHandlePrx OpenResourceDB(const ::Ice::Context&) = 0;

    virtual bool RollBack(const ::Ice::Context&) = 0;

    virtual bool SetDBObject(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetDataSource(const ::OPI::DataSourceHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool SetDatabase(const ::OPI::DatabaseHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetDictionary(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetResourceDB(const ::OPI::DatabaseHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetVariables(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool Setup(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetupVariables(const ::std::string&, const ::Ice::Context&) = 0;
};

class DatabaseHandle : virtual public ::IceDelegate::OPI::DBObjectHandle
{
public:

    virtual bool ActivateShadowBase(const ::Ice::Context&) = 0;

    virtual bool BackupDB(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool CheckDB(const ::OPI::CheckOptionsPrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool CheckLicence(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool CloseWorkspace(const ::Ice::Context&) = 0;

    virtual bool ConsolidateWorkspace(const ::Ice::Context&) = 0;

    virtual bool DeactivateShadowBase(const ::Ice::Context&) = 0;

    virtual bool DeleteWorkspace(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool DisableWorkspace(const ::Ice::Context&) = 0;

    virtual bool DiscardWorkspace(const ::Ice::Context&) = 0;

    virtual bool EnableWorkspace(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool ExecuteDatabaseAction(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool ExistWorkspace(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetDatabaseID(const ::Ice::Context&) = 0;

    virtual ::std::string GetPath(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetSchemaVersion(const ::Ice::Context&) = 0;

    virtual ::std::string GetVersionString(const ::Ice::Context&) = 0;

    virtual ::std::string GetWorkspace(const ::std::string&, ::Ice::Int, const ::std::string&, const ::std::string&, bool, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IgnoreWriteProtect(const ::Ice::Context&) = 0;

    virtual bool InitDataArea(::Ice::Int, ::Ice::Int, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool InitMainBase(::Ice::Int, const ::std::string&, ::Ice::Int, ::Ice::Int, ::Ice::Int, bool, bool, const ::Ice::Context&) = 0;

    virtual bool InitSubBase(::Ice::Int, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool IsLicenced(const ::Ice::Context&) = 0;

    virtual bool IsShared(const ::Ice::Context&) = 0;

    virtual bool LocateWorkspace(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool OpenDatabase(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::OPI::PIACC, bool, bool, ::Ice::Int, ::OPI::ResourceTypes, bool, const ::Ice::Context&) = 0;

    virtual bool OpenWorkspace(const ::std::string&, const ::std::string&, bool, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool RecreateExtent(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool RestoreDB(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetupTypeID(::Ice::Int, const ::Ice::Context&) = 0;
};

class DictionaryHandle : virtual public ::IceDelegate::OPI::DatabaseHandle
{
public:

    virtual ::Ice::Int BaseType(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool CheckExpression(const ::std::string&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool CheckExpressionInClass(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool CheckExtentDef(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool CheckValueSet(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool CopyCodeset(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::Ice::Int, const ::std::string&, ::OPI::PIREPL, bool, bool, const ::Ice::Context&) = 0;

    virtual bool CopyExtentDef(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, bool, bool, const ::Ice::Context&) = 0;

    virtual bool CopyStructure(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::Ice::Int, const ::std::string&, const ::std::string&, ::OPI::PIREPL, bool, bool, const ::Ice::Context&) = 0;

    virtual bool CopyType(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::PIREPL, bool, bool, bool, const ::Ice::Context&) = 0;

    virtual bool CreateEnum(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string CreateTempExtent(const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, bool, bool, const ::Ice::Context&) = 0;

    virtual bool DeleteEnum(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string EnumToString(const ::std::string&, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetLastSchemaVersion(const ::Ice::Context&) = 0;

    virtual ::std::string GetTempName(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsBasicType(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool OpenDictionary(const ::OPI::ODABAClientPrx&, const ::std::string&, ::OPI::PIACC, bool, ::Ice::Int, ::OPI::ResourceTypes, bool, const ::Ice::Context&) = 0;

    virtual ::Ice::Int StringToEnum(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool UpdateVersion(const ::Ice::Context&) = 0;
};

class ODABAClient : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void ActivateGUIMessages(const ::Ice::Context&) = 0;

    virtual bool BackupDB(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool CheckDB(const ::std::string&, const ::std::string&, const ::OPI::CheckOptionsPrx&, const ::std::string&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool Close(const ::Ice::Context&) = 0;

    virtual bool Connect(const ::std::string&, ::Ice::Int, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool DictDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual void Disconnect(const ::Ice::Context&) = 0;

    virtual bool Exist(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string GetDataSource(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::std::string GetHost(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetPort(const ::Ice::Context&) = 0;

    virtual ::std::string GetServerVariable(const ::std::string&, const ::Ice::Context&) = 0;

    virtual void Initialize(const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::ApplicationTypes, bool, const ::Ice::Context&) = 0;

    virtual bool IsConnected(const ::Ice::Context&) = 0;

    virtual bool KillClient(::Ice::Int, ::Ice::Int, bool, const ::Ice::Context&) = 0;

    virtual bool Open(const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::ApplicationTypes, const ::Ice::Context&) = 0;

    virtual ::OPI::DBObjectHandlePrx OpenDataSource(const ::std::string&, ::OPI::PIACC, const ::Ice::Context&) = 0;

    virtual bool PackDatabase(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool RestoreDB(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool SendClientMessage(::Ice::Int, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetServerVariable(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool ShutDown(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool StartPause(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool StatDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual void StopPause(const ::Ice::Context&) = 0;

    virtual bool SysInfoDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;
};

class OperationHandle : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool CheckExpression(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool CheckExpressionInClass(const ::OPI::DictionaryHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool Execute(const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx GetResult(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetSize(const ::Ice::Context&) = 0;

    virtual bool IsValid(const ::Ice::Context&) = 0;

    virtual bool Open(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool ProvideExpression(const ::OPI::DictionaryHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;
};

class PropertyHandle : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool Add(::Ice::Int, const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool AddByKey(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool AddInstance(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool AddOnPosition(::Ice::Int, bool, const ::Ice::Context&) = 0;

    virtual bool AddGlobal(::Ice::Int, const ::std::string&, const ::std::string&, bool, const ::Ice::Context&) = 0;

    virtual bool AddGlobalByKey(const ::std::string&, const ::std::string&, bool, const ::Ice::Context&) = 0;

    virtual bool AddGlobalOnPosition(::Ice::Int, bool, const ::Ice::Context&) = 0;

    virtual bool AddReference(const ::OPI::PropertyHandlePrx&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool AllocDescription(const ::Ice::Context&) = 0;

    virtual bool AllocateArea(const ::Ice::Context&) = 0;

    virtual bool AppendString(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool AutoLocate(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool Cancel(const ::Ice::Context&) = 0;

    virtual bool CancelBuffer(const ::Ice::Context&) = 0;

    virtual ::Ice::Int ChangeBuffer(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool ChangeCache(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::OPI::PIACC ChangeMode(::OPI::PIACC, const ::Ice::Context&) = 0;

    virtual bool Check(bool, const ::Ice::Context&) = 0;

    virtual bool CheckPosition(const ::Ice::Context&) = 0;

    virtual bool CheckUpdate(bool, const ::Ice::Context&) = 0;

    virtual bool CheckWProtect(const ::Ice::Context&) = 0;

    virtual bool Close(const ::Ice::Context&) = 0;

    virtual ::Ice::Int Compare(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int CompareDate(::Ice::Long, const ::Ice::Context&) = 0;

    virtual ::Ice::Int CompareFloat(::Ice::Float, const ::Ice::Context&) = 0;

    virtual ::Ice::Int CompareInteger(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::Ice::Int CompareString(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int CompareTime(::Ice::Long, const ::Ice::Context&) = 0;

    virtual ::Ice::Int CompareKey(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int CompareSortKey(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool CompareType(const ::OPI::PropertyHandlePrx&, bool, const ::Ice::Context&) = 0;

    virtual bool Copy(const ::OPI::PropertyHandlePrx&, const ::std::string&, ::Ice::Int, ::OPI::PIREPL, ::OPI::PIREPL, const ::Ice::Context&) = 0;

    virtual bool CopyData(const ::OPI::PropertyHandlePrx&, ::OPI::PIREPL, const ::Ice::Context&) = 0;

    virtual bool CopyHandle(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool CopyInstanceArea(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int CopySet(const ::OPI::PropertyHandlePrx&, ::OPI::PIREPL, ::OPI::PIREPL, bool, const ::Ice::Context&) = 0;

    virtual bool CreateTempExtent(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool Delete(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool DeleteByKey(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool DeleteOnPosition(::Ice::Int, bool, bool, const ::Ice::Context&) = 0;

    virtual bool DeleteIndexEntry(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool DeleteSet(bool, const ::Ice::Context&) = 0;

    virtual bool DisableKeyCheck(const ::Ice::Context&) = 0;

    virtual bool Duplicate(::Ice::Int, ::OPI::PIREPL, const ::Ice::Context&) = 0;

    virtual bool DuplicateKey(const ::std::string&, ::OPI::PIREPL, const ::Ice::Context&) = 0;

    virtual bool EnableKeyCheck(const ::Ice::Context&) = 0;

    virtual bool Execute(const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool ExecuteInstanceAction(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool ExecutePropertyAction(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool Exist(const ::Ice::Context&) = 0;

    virtual ::std::string ExtractKey(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string ExtractSortKey(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string FirstKey(const ::Ice::Context&) = 0;

    virtual bool Get(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool GetAtPosition(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool GetByKey(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string GetActionResult(const ::Ice::Context&) = 0;

    virtual ::std::string GetArea(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string GetAttribute(::Ice::Int, bool, bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx GetBaseProperty(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetCollectionID(const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx GetCollectionProperty(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetCount(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetCurrentIndex(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetCurrentSize(const ::Ice::Context&) = 0;

    virtual ::std::string GetCurrentType(const ::Ice::Context&) = 0;

    virtual ::OPI::DatabaseHandlePrx GetDBHandle(const ::Ice::Context&) = 0;

    virtual ::Ice::Long GetDate(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Long GetDateTime(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetDay(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::OPI::DictionaryHandlePrx GetDictionary(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetDimension(const ::Ice::Context&) = 0;

    virtual ::Ice::Float GetDouble(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetExtInstModCount(const ::Ice::Context&) = 0;

    virtual ::std::string GetExtentName(const ::Ice::Context&) = 0;

    virtual ::std::string GetGUID(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetGenAttrType(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetGenOrderType(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetGlobalID(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetHours(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetID(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::std::string GetIdentity(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string GetIndexName(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool GetInitInstance(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetInstModCount(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetInt(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetIntValue(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string GetKey(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetKeyLength(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetLOID(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetLOIDByKey(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetMinutes(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::OPI::PIACC GetMode(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetMonth(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetNormalized(const ::Ice::Context&) = 0;

    virtual ::OPI::DBObjectHandlePrx GetObjectHandle(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetOrigin(const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx GetParentProperty(const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx GetPropertyHandle(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string GetPropertyPath(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetRefModCount(const ::Ice::Context&) = 0;

    virtual ::std::string GetReference(::Ice::Int, bool, bool, const ::Ice::Context&) = 0;

    virtual bool GetRelative(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetRelativeCount(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetRelativeIndex(bool, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetSeconds(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string GetSelectedKey(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetSize(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetSizeOf(const ::Ice::Context&) = 0;

    virtual ::std::string GetSortKey(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetSortKeyLength(const ::Ice::Context&) = 0;

    virtual ::std::string GetString(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetStringLength(const ::Ice::Context&) = 0;

    virtual ::std::string GetStringValue(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string GetSubString(::Ice::Int, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::std::string GetText(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::Ice::Long GetTime(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::std::string GetType(const ::Ice::Context&) = 0;

    virtual bool GetValid(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetVersion(const ::Ice::Context&) = 0;

    virtual ::Ice::Int GetYear(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx Group(const ::OPI::PropertyHandlePrx&, const ::std::string&, bool, const ::Ice::Context&) = 0;

    virtual bool HasData(const ::Ice::Context&) = 0;

    virtual bool HasDescription(const ::Ice::Context&) = 0;

    virtual bool HasGenericAttributes(const ::Ice::Context&) = 0;

    virtual bool HasIndex(const ::Ice::Context&) = 0;

    virtual bool Inherits(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool InsertString(const ::std::string&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool InsertTerminator(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool InstanceInserted(const ::Ice::Context&) = 0;

    virtual ::std::string InstanceToString(const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx Intersect(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool Is(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool IsA(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsActive(const ::Ice::Context&) = 0;

    virtual bool IsAttribute(const ::Ice::Context&) = 0;

    virtual bool IsAutoSelection(const ::Ice::Context&) = 0;

    virtual bool IsBasedOn(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsBasetypeProperty(const ::Ice::Context&) = 0;

    virtual bool IsBasicType(const ::Ice::Context&) = 0;

    virtual bool IsClient(const ::Ice::Context&) = 0;

    virtual bool IsCollection(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsCollectionUpdate(const ::Ice::Context&) = 0;

    virtual bool IsCopyHandle(const ::Ice::Context&) = 0;

    virtual bool IsDirty(const ::Ice::Context&) = 0;

    virtual bool IsEmpty(const ::Ice::Context&) = 0;

    virtual bool IsEnumeration(const ::Ice::Context&) = 0;

    virtual bool IsGenericAttribute(const ::Ice::Context&) = 0;

    virtual bool IsInitInstance(const ::Ice::Context&) = 0;

    virtual bool IsMemo(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsModified(const ::Ice::Context&) = 0;

    virtual bool IsNewInstance(const ::Ice::Context&) = 0;

    virtual bool IsNumeric(const ::Ice::Context&) = 0;

    virtual bool IsOldInstance(const ::Ice::Context&) = 0;

    virtual bool IsOwner(const ::Ice::Context&) = 0;

    virtual bool IsPositioned(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsReadOnly(const ::Ice::Context&) = 0;

    virtual bool IsSelected(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsSensitive(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsServer(const ::Ice::Context&) = 0;

    virtual bool IsShareBaseHandle(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsStructure(const ::Ice::Context&) = 0;

    virtual bool IsText(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsTransient(const ::Ice::Context&) = 0;

    virtual bool IsTrue(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsTyped(const ::Ice::Context&) = 0;

    virtual bool IsUserHandle(const ::Ice::Context&) = 0;

    virtual bool IsValid(bool, const ::Ice::Context&) = 0;

    virtual bool IsValidText(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool IsVariableType(const ::Ice::Context&) = 0;

    virtual bool IsWeakTyped(const ::Ice::Context&) = 0;

    virtual bool IsWrite(const ::Ice::Context&) = 0;

    virtual bool Locate(::Ice::Int, bool, const ::Ice::Context&) = 0;

    virtual bool LocatePath(const ::Ice::Context&) = 0;

    virtual bool Lock(const ::Ice::Context&) = 0;

    virtual bool LockSet(const ::Ice::Context&) = 0;

    virtual void MarkUnused(const ::Ice::Context&) = 0;

    virtual void MarkUsed(const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx Minus(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool Modify(const ::Ice::Context&) = 0;

    virtual bool Move(const ::OPI::PropertyHandlePrx&, const ::std::string&, ::OPI::PIREPL, const ::Ice::Context&) = 0;

    virtual bool MoveDown(const ::Ice::Context&) = 0;

    virtual bool MoveUp(const ::Ice::Context&) = 0;

    virtual ::std::string NextKey(const ::std::string&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool NoWrite(const ::Ice::Context&) = 0;

    virtual bool Open(const ::Ice::Context&) = 0;

    virtual bool OpenBigInt(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool OpenBoolean(bool, const ::Ice::Context&) = 0;

    virtual bool OpenChild(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool OpenChildReference(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool OpenCopy(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool OpenDate(::Ice::Long, const ::Ice::Context&) = 0;

    virtual bool OpenExtent(const ::OPI::DBObjectHandlePrx&, const ::std::string&, ::OPI::PIACC, bool, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool OpenFloat(::Ice::Float, const ::Ice::Context&) = 0;

    virtual bool OpenInteger(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool OpenReference(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool OpenSizedString(const ::std::string&, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool OpenString(const ::std::string&, bool, const ::Ice::Context&) = 0;

    virtual bool OpenTime(::Ice::Long, const ::Ice::Context&) = 0;

    virtual bool OpenTimestamp(::Ice::Long, const ::Ice::Context&) = 0;

    virtual bool OpenHierarchy(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, bool, ::OPI::PIACC, bool, const ::Ice::Context&) = 0;

    virtual bool OwnsData(const ::Ice::Context&) = 0;

    virtual bool Position(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool PositionTop(const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx Power(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool ProvGenAttribute(const ::Ice::Context&) = 0;

    virtual bool Provide(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool ProvideAtPosition(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool ProvideByKey(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool ProvideArea(const ::Ice::Context&) = 0;

    virtual ::std::string ProvideGUID(const ::Ice::Context&) = 0;

    virtual bool ProvideGlobal(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool ProvideGlobalAtPosition(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool ProvideGlobalByKey(const ::std::string&, const ::Ice::Context&) = 0;

    virtual ::OPI::OperationHandlePrx ProvideOperation(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool Refresh(const ::Ice::Context&) = 0;

    virtual bool ReleaseBuffer(const ::Ice::Context&) = 0;

    virtual bool RemoveFromCollection(const ::Ice::Context&) = 0;

    virtual bool RemoveString(const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool RemoveTerminator(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool Rename(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool RepairIndex(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool ReplaceString(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool ReplaceSysVariables(const ::Ice::Context&) = 0;

    virtual bool Reset(const ::Ice::Context&) = 0;

    virtual void ResetDirty(const ::Ice::Context&) = 0;

    virtual bool ResetTransientProperty(const ::Ice::Context&) = 0;

    virtual bool ResetWProtect(const ::Ice::Context&) = 0;

    virtual bool Save(const ::std::string&, bool, const ::Ice::Context&) = 0;

    virtual ::Ice::Int SearchText(const ::std::string&, ::Ice::Int, bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx Select(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual void SetActionResult(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetContextVariables(const ::std::string&, const ::Ice::Context&) = 0;

    virtual void SetDirty(const ::Ice::Context&) = 0;

    virtual bool SetDynLength(const ::Ice::Context&) = 0;

    virtual bool SetGenAttribute(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetKey(const ::std::string&, const ::Ice::Context&) = 0;

    virtual void SetModified(const ::Ice::Context&) = 0;

    virtual bool SetNormalized(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool SetOrder(const ::std::string&, const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetSelection(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetSortKey(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetTransientProperty(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&) = 0;

    virtual bool SetType(const ::std::string&, const ::Ice::Context&) = 0;

    virtual bool SetUpdate(bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx SetValue(const ::OPI::PropertyHandlePrx&, bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx SetValueBigInt(::Ice::Int, bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx SetValueBoolean(bool, bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx SetValueDate(::Ice::Long, bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx SetValueFloat(::Ice::Float, bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx SetValueInteger(::Ice::Int, bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx SetValueString(const ::std::string&, bool, bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx SetValueTime(::Ice::Long, bool, const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx SetValueTimestamp(::Ice::Long, bool, const ::Ice::Context&) = 0;

    virtual bool SetVersion(::Ice::Int, const ::Ice::Context&) = 0;

    virtual bool SetWProtect(const ::Ice::Context&) = 0;

    virtual bool ToTop(const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx Union(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, bool, const ::Ice::Context&) = 0;

    virtual bool Unlock(const ::Ice::Context&) = 0;

    virtual bool UnlockSet(const ::Ice::Context&) = 0;
};

class OPIFactory : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual void Destroy(const ::Ice::Context&) = 0;

    virtual ::OPI::CheckOptionsPrx GetCheckOptions(const ::Ice::Context&) = 0;

    virtual ::OPI::DBObjectHandlePrx GetDBObjectHandle(const ::Ice::Context&) = 0;

    virtual ::OPI::DataSourceHandlePrx GetDataSourceHandle(const ::Ice::Context&) = 0;

    virtual ::OPI::DatabaseHandlePrx GetDatabaseHandle(const ::Ice::Context&) = 0;

    virtual ::OPI::DictionaryHandlePrx GetDictionaryHandle(const ::Ice::Context&) = 0;

    virtual ::OPI::ODABAClientPrx GetODABAClient(const ::Ice::Context&) = 0;

    virtual ::OPI::OperationHandlePrx GetOperationHandle(const ::Ice::Context&) = 0;

    virtual ::OPI::PropertyHandlePrx GetPropertyHandle(const ::Ice::Context&) = 0;
};

class Session : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::OPI::OPIFactoryPrx CreateSession(const ::Ice::Context&) = 0;

    virtual void Destroy(const ::Ice::Context&) = 0;

    virtual void TimeOut(::Ice::Int, const ::Ice::Context&) = 0;

    virtual ::std::string getName(const ::Ice::Context&) = 0;
};

class SessionFactory : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::OPI::SessionPrx CreateProxy(const ::std::string&, const ::Ice::Context&) = 0;

    virtual void shutdown(const ::Ice::Context&) = 0;
};

}

}

namespace IceDelegateM
{

namespace OPI
{

class CheckOptions : virtual public ::IceDelegate::OPI::CheckOptions,
		     virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual bool Initialize(const ::std::string&, const ::Ice::Context&);
};

class DBObjectHandle : virtual public ::IceDelegate::OPI::DBObjectHandle,
		       virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::Ice::Int BeginTransaction(bool, ::Ice::Int, const ::Ice::Context&);

    virtual bool ChangeTimeStamp(::Ice::Int, ::Ice::Long, const ::Ice::Context&);

    virtual bool CommitTransaction(::Ice::Int, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx CreateTempPropertyHandle(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool DeleteExtent(const ::std::string&, const ::Ice::Context&);

    virtual bool DeleteExtentRef(const ::std::string&, const ::Ice::Context&);

    virtual void DisableEventHandling(const ::Ice::Context&);

    virtual void EnableEventHandling(const ::Ice::Context&);

    virtual bool EventHandling(const ::Ice::Context&);

    virtual bool ExecuteDBObjectAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool ExtentExist(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::PIACC GetAccess(const ::Ice::Context&);

    virtual ::std::string GetActionResult(const ::Ice::Context&);

    virtual ::OPI::DatabaseHandlePrx GetDBHandle(const ::Ice::Context&);

    virtual ::OPI::DataSourceHandlePrx GetDataSource(const ::Ice::Context&);

    virtual ::OPI::DictionaryHandlePrx GetDictionary(const ::Ice::Context&);

    virtual ::std::string GetExtent(::Ice::Int, const ::Ice::Context&);

    virtual ::OPI::DBObjectHandlePrx GetHighObject(const ::Ice::Context&);

    virtual ::std::string GetObject(::Ice::Int, const ::Ice::Context&);

    virtual ::std::string GetServerVariable(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetSystemVersion(const ::Ice::Context&);

    virtual ::Ice::Long GetTimeStamp(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int GetTransactionLevel(const ::Ice::Context&);

    virtual ::Ice::Int GetVersion(::Ice::Long, const ::Ice::Context&);

    virtual bool IsClient(const ::Ice::Context&);

    virtual bool IsEmpty(const ::Ice::Context&);

    virtual bool IsOpened(const ::Ice::Context&);

    virtual bool IsServer(const ::Ice::Context&);

    virtual bool IsValid(const ::Ice::Context&);

    virtual bool NewVersion(::Ice::Long, ::Ice::Int, const ::Ice::Context&);

    virtual bool OpenObject(const ::OPI::DBObjectHandlePrx&, const ::std::string&, ::OPI::PIACC, ::Ice::Int, ::OPI::ResourceTypes, const ::Ice::Context&);

    virtual bool RollBack(::Ice::Int, const ::Ice::Context&);

    virtual void SetActionResult(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int SetOverload(bool, const ::Ice::Context&);

    virtual bool SetServerVariable(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetUserDefinedIdentity(bool, const ::Ice::Context&);

    virtual bool SetVersion(::Ice::Int, const ::Ice::Context&);

    virtual bool SetVersioni1(::Ice::Long, const ::Ice::Context&);

    virtual bool SetVersioni2(::Ice::Long, const ::Ice::Context&);

    virtual ::Ice::Int VersionCount(const ::Ice::Context&);
};

class DataSourceHandle : virtual public ::IceDelegate::OPI::DataSourceHandle,
			 virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual bool BeginTransaction(bool, const ::Ice::Context&);

    virtual bool Close(const ::Ice::Context&);

    virtual bool CloseDBObject(const ::Ice::Context&);

    virtual bool CloseDatabase(const ::Ice::Context&);

    virtual bool CloseDictionary(const ::Ice::Context&);

    virtual bool CloseProperty(const ::Ice::Context&);

    virtual bool CloseResourceDB(const ::Ice::Context&);

    virtual bool CommitTransaction(const ::Ice::Context&);

    virtual bool Connect(const ::OPI::ODABAClientPrx&, const ::Ice::Context&);

    virtual bool Disconnect(const ::Ice::Context&);

    virtual bool Open(const ::OPI::ODABAClientPrx&, ::OPI::PIACC, const ::Ice::Context&);

    virtual bool Openi02(const ::OPI::ODABAClientPrx&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool Openi1(const ::OPI::ODABAClientPrx&, const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::DBObjectHandlePrx OpenDBObject(const ::Ice::Context&);

    virtual ::OPI::DatabaseHandlePrx OpenDatabase(const ::Ice::Context&);

    virtual ::OPI::DictionaryHandlePrx OpenDictionary(::OPI::PIACC, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx OpenProperty(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::DatabaseHandlePrx OpenResourceDB(const ::Ice::Context&);

    virtual bool RollBack(const ::Ice::Context&);

    virtual bool SetDBObject(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetDataSource(const ::OPI::DataSourceHandlePrx&, const ::Ice::Context&);

    virtual bool SetDatabase(const ::OPI::DatabaseHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetDictionary(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetResourceDB(const ::OPI::DatabaseHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetVariables(const ::std::string&, const ::Ice::Context&);

    virtual bool Setup(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetupVariables(const ::std::string&, const ::Ice::Context&);
};

class DatabaseHandle : virtual public ::IceDelegate::OPI::DatabaseHandle,
		       virtual public ::IceDelegateM::OPI::DBObjectHandle
{
public:

    virtual bool ActivateShadowBase(const ::Ice::Context&);

    virtual bool BackupDB(const ::std::string&, const ::Ice::Context&);

    virtual bool CheckDB(const ::OPI::CheckOptionsPrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool CheckLicence(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool CloseWorkspace(const ::Ice::Context&);

    virtual bool ConsolidateWorkspace(const ::Ice::Context&);

    virtual bool DeactivateShadowBase(const ::Ice::Context&);

    virtual bool DeleteWorkspace(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool DisableWorkspace(const ::Ice::Context&);

    virtual bool DiscardWorkspace(const ::Ice::Context&);

    virtual bool EnableWorkspace(const ::std::string&, const ::Ice::Context&);

    virtual bool ExecuteDatabaseAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool ExistWorkspace(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetDatabaseID(const ::Ice::Context&);

    virtual ::std::string GetPath(const ::Ice::Context&);

    virtual ::Ice::Int GetSchemaVersion(const ::Ice::Context&);

    virtual ::std::string GetVersionString(const ::Ice::Context&);

    virtual ::std::string GetWorkspace(const ::std::string&, ::Ice::Int, const ::std::string&, const ::std::string&, bool, const ::std::string&, const ::Ice::Context&);

    virtual bool IgnoreWriteProtect(const ::Ice::Context&);

    virtual bool InitDataArea(::Ice::Int, ::Ice::Int, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool InitMainBase(::Ice::Int, const ::std::string&, ::Ice::Int, ::Ice::Int, ::Ice::Int, bool, bool, const ::Ice::Context&);

    virtual bool InitSubBase(::Ice::Int, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool IsLicenced(const ::Ice::Context&);

    virtual bool IsShared(const ::Ice::Context&);

    virtual bool LocateWorkspace(const ::std::string&, const ::Ice::Context&);

    virtual bool OpenDatabase(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::OPI::PIACC, bool, bool, ::Ice::Int, ::OPI::ResourceTypes, bool, const ::Ice::Context&);

    virtual bool OpenWorkspace(const ::std::string&, const ::std::string&, bool, const ::std::string&, const ::Ice::Context&);

    virtual bool RecreateExtent(const ::std::string&, const ::Ice::Context&);

    virtual bool RestoreDB(const ::std::string&, const ::Ice::Context&);

    virtual bool SetupTypeID(::Ice::Int, const ::Ice::Context&);
};

class DictionaryHandle : virtual public ::IceDelegate::OPI::DictionaryHandle,
			 virtual public ::IceDelegateM::OPI::DatabaseHandle
{
public:

    virtual ::Ice::Int BaseType(const ::std::string&, const ::Ice::Context&);

    virtual bool CheckExpression(const ::std::string&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool CheckExpressionInClass(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool CheckExtentDef(const ::std::string&, const ::Ice::Context&);

    virtual bool CheckValueSet(const ::std::string&, const ::Ice::Context&);

    virtual bool CopyCodeset(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::Ice::Int, const ::std::string&, ::OPI::PIREPL, bool, bool, const ::Ice::Context&);

    virtual bool CopyExtentDef(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, bool, bool, const ::Ice::Context&);

    virtual bool CopyStructure(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::Ice::Int, const ::std::string&, const ::std::string&, ::OPI::PIREPL, bool, bool, const ::Ice::Context&);

    virtual bool CopyType(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::PIREPL, bool, bool, bool, const ::Ice::Context&);

    virtual bool CreateEnum(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual ::std::string CreateTempExtent(const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, bool, bool, const ::Ice::Context&);

    virtual bool DeleteEnum(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string EnumToString(const ::std::string&, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int GetLastSchemaVersion(const ::Ice::Context&);

    virtual ::std::string GetTempName(const ::std::string&, const ::Ice::Context&);

    virtual bool IsBasicType(const ::std::string&, const ::Ice::Context&);

    virtual bool OpenDictionary(const ::OPI::ODABAClientPrx&, const ::std::string&, ::OPI::PIACC, bool, ::Ice::Int, ::OPI::ResourceTypes, bool, const ::Ice::Context&);

    virtual ::Ice::Int StringToEnum(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool UpdateVersion(const ::Ice::Context&);
};

class ODABAClient : virtual public ::IceDelegate::OPI::ODABAClient,
		    virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void ActivateGUIMessages(const ::Ice::Context&);

    virtual bool BackupDB(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool CheckDB(const ::std::string&, const ::std::string&, const ::OPI::CheckOptionsPrx&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool Close(const ::Ice::Context&);

    virtual bool Connect(const ::std::string&, ::Ice::Int, const ::std::string&, const ::Ice::Context&);

    virtual bool DictDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual void Disconnect(const ::Ice::Context&);

    virtual bool Exist(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetDataSource(::Ice::Int, const ::Ice::Context&);

    virtual ::std::string GetHost(const ::Ice::Context&);

    virtual ::Ice::Int GetPort(const ::Ice::Context&);

    virtual ::std::string GetServerVariable(const ::std::string&, const ::Ice::Context&);

    virtual void Initialize(const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::ApplicationTypes, bool, const ::Ice::Context&);

    virtual bool IsConnected(const ::Ice::Context&);

    virtual bool KillClient(::Ice::Int, ::Ice::Int, bool, const ::Ice::Context&);

    virtual bool Open(const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::ApplicationTypes, const ::Ice::Context&);

    virtual ::OPI::DBObjectHandlePrx OpenDataSource(const ::std::string&, ::OPI::PIACC, const ::Ice::Context&);

    virtual bool PackDatabase(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool RestoreDB(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool SendClientMessage(::Ice::Int, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetServerVariable(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool ShutDown(const ::std::string&, const ::Ice::Context&);

    virtual bool StartPause(::Ice::Int, const ::Ice::Context&);

    virtual bool StatDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual void StopPause(const ::Ice::Context&);

    virtual bool SysInfoDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&);
};

class OperationHandle : virtual public ::IceDelegate::OPI::OperationHandle,
			virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual bool CheckExpression(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool CheckExpressionInClass(const ::OPI::DictionaryHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool Execute(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetResult(const ::Ice::Context&);

    virtual ::Ice::Int GetSize(const ::Ice::Context&);

    virtual bool IsValid(const ::Ice::Context&);

    virtual bool Open(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool ProvideExpression(const ::OPI::DictionaryHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);
};

class PropertyHandle : virtual public ::IceDelegate::OPI::PropertyHandle,
		       virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual bool Add(::Ice::Int, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool AddByKey(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool AddInstance(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool AddOnPosition(::Ice::Int, bool, const ::Ice::Context&);

    virtual bool AddGlobal(::Ice::Int, const ::std::string&, const ::std::string&, bool, const ::Ice::Context&);

    virtual bool AddGlobalByKey(const ::std::string&, const ::std::string&, bool, const ::Ice::Context&);

    virtual bool AddGlobalOnPosition(::Ice::Int, bool, const ::Ice::Context&);

    virtual bool AddReference(const ::OPI::PropertyHandlePrx&, ::Ice::Int, const ::Ice::Context&);

    virtual bool AllocDescription(const ::Ice::Context&);

    virtual bool AllocateArea(const ::Ice::Context&);

    virtual bool AppendString(const ::std::string&, const ::Ice::Context&);

    virtual bool AutoLocate(const ::std::string&, const ::Ice::Context&);

    virtual bool Cancel(const ::Ice::Context&);

    virtual bool CancelBuffer(const ::Ice::Context&);

    virtual ::Ice::Int ChangeBuffer(::Ice::Int, const ::Ice::Context&);

    virtual bool ChangeCache(::Ice::Int, const ::Ice::Context&);

    virtual ::OPI::PIACC ChangeMode(::OPI::PIACC, const ::Ice::Context&);

    virtual bool Check(bool, const ::Ice::Context&);

    virtual bool CheckPosition(const ::Ice::Context&);

    virtual bool CheckUpdate(bool, const ::Ice::Context&);

    virtual bool CheckWProtect(const ::Ice::Context&);

    virtual bool Close(const ::Ice::Context&);

    virtual ::Ice::Int Compare(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual ::Ice::Int CompareDate(::Ice::Long, const ::Ice::Context&);

    virtual ::Ice::Int CompareFloat(::Ice::Float, const ::Ice::Context&);

    virtual ::Ice::Int CompareInteger(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int CompareString(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int CompareTime(::Ice::Long, const ::Ice::Context&);

    virtual ::Ice::Int CompareKey(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int CompareSortKey(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool CompareType(const ::OPI::PropertyHandlePrx&, bool, const ::Ice::Context&);

    virtual bool Copy(const ::OPI::PropertyHandlePrx&, const ::std::string&, ::Ice::Int, ::OPI::PIREPL, ::OPI::PIREPL, const ::Ice::Context&);

    virtual bool CopyData(const ::OPI::PropertyHandlePrx&, ::OPI::PIREPL, const ::Ice::Context&);

    virtual bool CopyHandle(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool CopyInstanceArea(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual ::Ice::Int CopySet(const ::OPI::PropertyHandlePrx&, ::OPI::PIREPL, ::OPI::PIREPL, bool, const ::Ice::Context&);

    virtual bool CreateTempExtent(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool Delete(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool DeleteByKey(const ::std::string&, const ::Ice::Context&);

    virtual bool DeleteOnPosition(::Ice::Int, bool, bool, const ::Ice::Context&);

    virtual bool DeleteIndexEntry(::Ice::Int, const ::Ice::Context&);

    virtual bool DeleteSet(bool, const ::Ice::Context&);

    virtual bool DisableKeyCheck(const ::Ice::Context&);

    virtual bool Duplicate(::Ice::Int, ::OPI::PIREPL, const ::Ice::Context&);

    virtual bool DuplicateKey(const ::std::string&, ::OPI::PIREPL, const ::Ice::Context&);

    virtual bool EnableKeyCheck(const ::Ice::Context&);

    virtual bool Execute(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool ExecuteInstanceAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool ExecutePropertyAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool Exist(const ::Ice::Context&);

    virtual ::std::string ExtractKey(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string ExtractSortKey(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string FirstKey(const ::Ice::Context&);

    virtual bool Get(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool GetAtPosition(::Ice::Int, const ::Ice::Context&);

    virtual bool GetByKey(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetActionResult(const ::Ice::Context&);

    virtual ::std::string GetArea(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetAttribute(::Ice::Int, bool, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetBaseProperty(const ::Ice::Context&);

    virtual ::Ice::Int GetCollectionID(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetCollectionProperty(const ::Ice::Context&);

    virtual ::Ice::Int GetCount(const ::Ice::Context&);

    virtual ::Ice::Int GetCurrentIndex(const ::Ice::Context&);

    virtual ::Ice::Int GetCurrentSize(const ::Ice::Context&);

    virtual ::std::string GetCurrentType(const ::Ice::Context&);

    virtual ::OPI::DatabaseHandlePrx GetDBHandle(const ::Ice::Context&);

    virtual ::Ice::Long GetDate(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Long GetDateTime(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetDay(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::DictionaryHandlePrx GetDictionary(const ::Ice::Context&);

    virtual ::Ice::Int GetDimension(const ::Ice::Context&);

    virtual ::Ice::Float GetDouble(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetExtInstModCount(const ::Ice::Context&);

    virtual ::std::string GetExtentName(const ::Ice::Context&);

    virtual ::std::string GetGUID(const ::Ice::Context&);

    virtual ::Ice::Int GetGenAttrType(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetGenOrderType(const ::Ice::Context&);

    virtual ::Ice::Int GetGlobalID(const ::Ice::Context&);

    virtual ::Ice::Int GetHours(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetID(::Ice::Int, const ::Ice::Context&);

    virtual ::std::string GetIdentity(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetIndexName(::Ice::Int, const ::Ice::Context&);

    virtual bool GetInitInstance(const ::Ice::Context&);

    virtual ::Ice::Int GetInstModCount(const ::Ice::Context&);

    virtual ::Ice::Int GetInt(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetIntValue(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetKey(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int GetKeyLength(const ::Ice::Context&);

    virtual ::Ice::Int GetLOID(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int GetLOIDByKey(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetMinutes(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::PIACC GetMode(const ::Ice::Context&);

    virtual ::Ice::Int GetMonth(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetNormalized(const ::Ice::Context&);

    virtual ::OPI::DBObjectHandlePrx GetObjectHandle(const ::Ice::Context&);

    virtual ::Ice::Int GetOrigin(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetParentProperty(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetPropertyHandle(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetPropertyPath(const ::Ice::Context&);

    virtual ::Ice::Int GetRefModCount(const ::Ice::Context&);

    virtual ::std::string GetReference(::Ice::Int, bool, bool, const ::Ice::Context&);

    virtual bool GetRelative(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int GetRelativeCount(const ::Ice::Context&);

    virtual ::Ice::Int GetRelativeIndex(bool, const ::Ice::Context&);

    virtual ::Ice::Int GetSeconds(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetSelectedKey(const ::Ice::Context&);

    virtual ::Ice::Int GetSize(const ::Ice::Context&);

    virtual ::Ice::Int GetSizeOf(const ::Ice::Context&);

    virtual ::std::string GetSortKey(const ::Ice::Context&);

    virtual ::Ice::Int GetSortKeyLength(const ::Ice::Context&);

    virtual ::std::string GetString(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetStringLength(const ::Ice::Context&);

    virtual ::std::string GetStringValue(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetSubString(::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    virtual ::std::string GetText(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Long GetTime(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetType(const ::Ice::Context&);

    virtual bool GetValid(const ::Ice::Context&);

    virtual ::Ice::Int GetVersion(const ::Ice::Context&);

    virtual ::Ice::Int GetYear(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Group(const ::OPI::PropertyHandlePrx&, const ::std::string&, bool, const ::Ice::Context&);

    virtual bool HasData(const ::Ice::Context&);

    virtual bool HasDescription(const ::Ice::Context&);

    virtual bool HasGenericAttributes(const ::Ice::Context&);

    virtual bool HasIndex(const ::Ice::Context&);

    virtual bool Inherits(const ::std::string&, const ::Ice::Context&);

    virtual bool InsertString(const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool InsertTerminator(const ::std::string&, const ::Ice::Context&);

    virtual bool InstanceInserted(const ::Ice::Context&);

    virtual ::std::string InstanceToString(const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Intersect(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool Is(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool IsA(const ::std::string&, const ::Ice::Context&);

    virtual bool IsActive(const ::Ice::Context&);

    virtual bool IsAttribute(const ::Ice::Context&);

    virtual bool IsAutoSelection(const ::Ice::Context&);

    virtual bool IsBasedOn(const ::std::string&, const ::Ice::Context&);

    virtual bool IsBasetypeProperty(const ::Ice::Context&);

    virtual bool IsBasicType(const ::Ice::Context&);

    virtual bool IsClient(const ::Ice::Context&);

    virtual bool IsCollection(const ::std::string&, const ::Ice::Context&);

    virtual bool IsCollectionUpdate(const ::Ice::Context&);

    virtual bool IsCopyHandle(const ::Ice::Context&);

    virtual bool IsDirty(const ::Ice::Context&);

    virtual bool IsEmpty(const ::Ice::Context&);

    virtual bool IsEnumeration(const ::Ice::Context&);

    virtual bool IsGenericAttribute(const ::Ice::Context&);

    virtual bool IsInitInstance(const ::Ice::Context&);

    virtual bool IsMemo(const ::std::string&, const ::Ice::Context&);

    virtual bool IsModified(const ::Ice::Context&);

    virtual bool IsNewInstance(const ::Ice::Context&);

    virtual bool IsNumeric(const ::Ice::Context&);

    virtual bool IsOldInstance(const ::Ice::Context&);

    virtual bool IsOwner(const ::Ice::Context&);

    virtual bool IsPositioned(const ::std::string&, const ::Ice::Context&);

    virtual bool IsReadOnly(const ::Ice::Context&);

    virtual bool IsSelected(const ::std::string&, const ::Ice::Context&);

    virtual bool IsSensitive(const ::std::string&, const ::Ice::Context&);

    virtual bool IsServer(const ::Ice::Context&);

    virtual bool IsShareBaseHandle(const ::std::string&, const ::Ice::Context&);

    virtual bool IsStructure(const ::Ice::Context&);

    virtual bool IsText(const ::std::string&, const ::Ice::Context&);

    virtual bool IsTransient(const ::Ice::Context&);

    virtual bool IsTrue(const ::std::string&, const ::Ice::Context&);

    virtual bool IsTyped(const ::Ice::Context&);

    virtual bool IsUserHandle(const ::Ice::Context&);

    virtual bool IsValid(bool, const ::Ice::Context&);

    virtual bool IsValidText(const ::std::string&, const ::Ice::Context&);

    virtual bool IsVariableType(const ::Ice::Context&);

    virtual bool IsWeakTyped(const ::Ice::Context&);

    virtual bool IsWrite(const ::Ice::Context&);

    virtual bool Locate(::Ice::Int, bool, const ::Ice::Context&);

    virtual bool LocatePath(const ::Ice::Context&);

    virtual bool Lock(const ::Ice::Context&);

    virtual bool LockSet(const ::Ice::Context&);

    virtual void MarkUnused(const ::Ice::Context&);

    virtual void MarkUsed(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Minus(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool Modify(const ::Ice::Context&);

    virtual bool Move(const ::OPI::PropertyHandlePrx&, const ::std::string&, ::OPI::PIREPL, const ::Ice::Context&);

    virtual bool MoveDown(const ::Ice::Context&);

    virtual bool MoveUp(const ::Ice::Context&);

    virtual ::std::string NextKey(const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool NoWrite(const ::Ice::Context&);

    virtual bool Open(const ::Ice::Context&);

    virtual bool OpenBigInt(::Ice::Int, const ::Ice::Context&);

    virtual bool OpenBoolean(bool, const ::Ice::Context&);

    virtual bool OpenChild(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool OpenChildReference(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool OpenCopy(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool OpenDate(::Ice::Long, const ::Ice::Context&);

    virtual bool OpenExtent(const ::OPI::DBObjectHandlePrx&, const ::std::string&, ::OPI::PIACC, bool, const ::std::string&, const ::Ice::Context&);

    virtual bool OpenFloat(::Ice::Float, const ::Ice::Context&);

    virtual bool OpenInteger(::Ice::Int, const ::Ice::Context&);

    virtual bool OpenReference(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool OpenSizedString(const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool OpenString(const ::std::string&, bool, const ::Ice::Context&);

    virtual bool OpenTime(::Ice::Long, const ::Ice::Context&);

    virtual bool OpenTimestamp(::Ice::Long, const ::Ice::Context&);

    virtual bool OpenHierarchy(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, bool, ::OPI::PIACC, bool, const ::Ice::Context&);

    virtual bool OwnsData(const ::Ice::Context&);

    virtual bool Position(::Ice::Int, const ::Ice::Context&);

    virtual bool PositionTop(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Power(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool ProvGenAttribute(const ::Ice::Context&);

    virtual bool Provide(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool ProvideAtPosition(::Ice::Int, const ::Ice::Context&);

    virtual bool ProvideByKey(const ::std::string&, const ::Ice::Context&);

    virtual bool ProvideArea(const ::Ice::Context&);

    virtual ::std::string ProvideGUID(const ::Ice::Context&);

    virtual bool ProvideGlobal(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool ProvideGlobalAtPosition(::Ice::Int, const ::Ice::Context&);

    virtual bool ProvideGlobalByKey(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::OperationHandlePrx ProvideOperation(const ::std::string&, const ::Ice::Context&);

    virtual bool Refresh(const ::Ice::Context&);

    virtual bool ReleaseBuffer(const ::Ice::Context&);

    virtual bool RemoveFromCollection(const ::Ice::Context&);

    virtual bool RemoveString(const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    virtual bool RemoveTerminator(const ::std::string&, const ::Ice::Context&);

    virtual bool Rename(const ::std::string&, const ::Ice::Context&);

    virtual bool RepairIndex(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool ReplaceString(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool ReplaceSysVariables(const ::Ice::Context&);

    virtual bool Reset(const ::Ice::Context&);

    virtual void ResetDirty(const ::Ice::Context&);

    virtual bool ResetTransientProperty(const ::Ice::Context&);

    virtual bool ResetWProtect(const ::Ice::Context&);

    virtual bool Save(const ::std::string&, bool, const ::Ice::Context&);

    virtual ::Ice::Int SearchText(const ::std::string&, ::Ice::Int, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Select(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual void SetActionResult(const ::std::string&, const ::Ice::Context&);

    virtual bool SetContextVariables(const ::std::string&, const ::Ice::Context&);

    virtual void SetDirty(const ::Ice::Context&);

    virtual bool SetDynLength(const ::Ice::Context&);

    virtual bool SetGenAttribute(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetKey(const ::std::string&, const ::Ice::Context&);

    virtual void SetModified(const ::Ice::Context&);

    virtual bool SetNormalized(::Ice::Int, const ::Ice::Context&);

    virtual bool SetOrder(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetSelection(const ::std::string&, const ::Ice::Context&);

    virtual bool SetSortKey(const ::std::string&, const ::Ice::Context&);

    virtual bool SetTransientProperty(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool SetType(const ::std::string&, const ::Ice::Context&);

    virtual bool SetUpdate(bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValue(const ::OPI::PropertyHandlePrx&, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueBigInt(::Ice::Int, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueBoolean(bool, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueDate(::Ice::Long, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueFloat(::Ice::Float, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueInteger(::Ice::Int, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueString(const ::std::string&, bool, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueTime(::Ice::Long, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueTimestamp(::Ice::Long, bool, const ::Ice::Context&);

    virtual bool SetVersion(::Ice::Int, const ::Ice::Context&);

    virtual bool SetWProtect(const ::Ice::Context&);

    virtual bool ToTop(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Union(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, bool, const ::Ice::Context&);

    virtual bool Unlock(const ::Ice::Context&);

    virtual bool UnlockSet(const ::Ice::Context&);
};

class OPIFactory : virtual public ::IceDelegate::OPI::OPIFactory,
		   virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual void Destroy(const ::Ice::Context&);

    virtual ::OPI::CheckOptionsPrx GetCheckOptions(const ::Ice::Context&);

    virtual ::OPI::DBObjectHandlePrx GetDBObjectHandle(const ::Ice::Context&);

    virtual ::OPI::DataSourceHandlePrx GetDataSourceHandle(const ::Ice::Context&);

    virtual ::OPI::DatabaseHandlePrx GetDatabaseHandle(const ::Ice::Context&);

    virtual ::OPI::DictionaryHandlePrx GetDictionaryHandle(const ::Ice::Context&);

    virtual ::OPI::ODABAClientPrx GetODABAClient(const ::Ice::Context&);

    virtual ::OPI::OperationHandlePrx GetOperationHandle(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetPropertyHandle(const ::Ice::Context&);
};

class Session : virtual public ::IceDelegate::OPI::Session,
		virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::OPI::OPIFactoryPrx CreateSession(const ::Ice::Context&);

    virtual void Destroy(const ::Ice::Context&);

    virtual void TimeOut(::Ice::Int, const ::Ice::Context&);

    virtual ::std::string getName(const ::Ice::Context&);
};

class SessionFactory : virtual public ::IceDelegate::OPI::SessionFactory,
		       virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::OPI::SessionPrx CreateProxy(const ::std::string&, const ::Ice::Context&);

    virtual void shutdown(const ::Ice::Context&);
};

}

}

namespace IceDelegateD
{

namespace OPI
{

class CheckOptions : virtual public ::IceDelegate::OPI::CheckOptions,
		     virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual bool Initialize(const ::std::string&, const ::Ice::Context&);
};

class DBObjectHandle : virtual public ::IceDelegate::OPI::DBObjectHandle,
		       virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::Ice::Int BeginTransaction(bool, ::Ice::Int, const ::Ice::Context&);

    virtual bool ChangeTimeStamp(::Ice::Int, ::Ice::Long, const ::Ice::Context&);

    virtual bool CommitTransaction(::Ice::Int, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx CreateTempPropertyHandle(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool DeleteExtent(const ::std::string&, const ::Ice::Context&);

    virtual bool DeleteExtentRef(const ::std::string&, const ::Ice::Context&);

    virtual void DisableEventHandling(const ::Ice::Context&);

    virtual void EnableEventHandling(const ::Ice::Context&);

    virtual bool EventHandling(const ::Ice::Context&);

    virtual bool ExecuteDBObjectAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool ExtentExist(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::PIACC GetAccess(const ::Ice::Context&);

    virtual ::std::string GetActionResult(const ::Ice::Context&);

    virtual ::OPI::DatabaseHandlePrx GetDBHandle(const ::Ice::Context&);

    virtual ::OPI::DataSourceHandlePrx GetDataSource(const ::Ice::Context&);

    virtual ::OPI::DictionaryHandlePrx GetDictionary(const ::Ice::Context&);

    virtual ::std::string GetExtent(::Ice::Int, const ::Ice::Context&);

    virtual ::OPI::DBObjectHandlePrx GetHighObject(const ::Ice::Context&);

    virtual ::std::string GetObject(::Ice::Int, const ::Ice::Context&);

    virtual ::std::string GetServerVariable(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetSystemVersion(const ::Ice::Context&);

    virtual ::Ice::Long GetTimeStamp(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int GetTransactionLevel(const ::Ice::Context&);

    virtual ::Ice::Int GetVersion(::Ice::Long, const ::Ice::Context&);

    virtual bool IsClient(const ::Ice::Context&);

    virtual bool IsEmpty(const ::Ice::Context&);

    virtual bool IsOpened(const ::Ice::Context&);

    virtual bool IsServer(const ::Ice::Context&);

    virtual bool IsValid(const ::Ice::Context&);

    virtual bool NewVersion(::Ice::Long, ::Ice::Int, const ::Ice::Context&);

    virtual bool OpenObject(const ::OPI::DBObjectHandlePrx&, const ::std::string&, ::OPI::PIACC, ::Ice::Int, ::OPI::ResourceTypes, const ::Ice::Context&);

    virtual bool RollBack(::Ice::Int, const ::Ice::Context&);

    virtual void SetActionResult(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int SetOverload(bool, const ::Ice::Context&);

    virtual bool SetServerVariable(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetUserDefinedIdentity(bool, const ::Ice::Context&);

    virtual bool SetVersion(::Ice::Int, const ::Ice::Context&);

    virtual bool SetVersioni1(::Ice::Long, const ::Ice::Context&);

    virtual bool SetVersioni2(::Ice::Long, const ::Ice::Context&);

    virtual ::Ice::Int VersionCount(const ::Ice::Context&);
};

class DataSourceHandle : virtual public ::IceDelegate::OPI::DataSourceHandle,
			 virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual bool BeginTransaction(bool, const ::Ice::Context&);

    virtual bool Close(const ::Ice::Context&);

    virtual bool CloseDBObject(const ::Ice::Context&);

    virtual bool CloseDatabase(const ::Ice::Context&);

    virtual bool CloseDictionary(const ::Ice::Context&);

    virtual bool CloseProperty(const ::Ice::Context&);

    virtual bool CloseResourceDB(const ::Ice::Context&);

    virtual bool CommitTransaction(const ::Ice::Context&);

    virtual bool Connect(const ::OPI::ODABAClientPrx&, const ::Ice::Context&);

    virtual bool Disconnect(const ::Ice::Context&);

    virtual bool Open(const ::OPI::ODABAClientPrx&, ::OPI::PIACC, const ::Ice::Context&);

    virtual bool Openi02(const ::OPI::ODABAClientPrx&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool Openi1(const ::OPI::ODABAClientPrx&, const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::DBObjectHandlePrx OpenDBObject(const ::Ice::Context&);

    virtual ::OPI::DatabaseHandlePrx OpenDatabase(const ::Ice::Context&);

    virtual ::OPI::DictionaryHandlePrx OpenDictionary(::OPI::PIACC, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx OpenProperty(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::DatabaseHandlePrx OpenResourceDB(const ::Ice::Context&);

    virtual bool RollBack(const ::Ice::Context&);

    virtual bool SetDBObject(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetDataSource(const ::OPI::DataSourceHandlePrx&, const ::Ice::Context&);

    virtual bool SetDatabase(const ::OPI::DatabaseHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetDictionary(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetResourceDB(const ::OPI::DatabaseHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetVariables(const ::std::string&, const ::Ice::Context&);

    virtual bool Setup(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetupVariables(const ::std::string&, const ::Ice::Context&);
};

class DatabaseHandle : virtual public ::IceDelegate::OPI::DatabaseHandle,
		       virtual public ::IceDelegateD::OPI::DBObjectHandle
{
public:

    virtual bool ActivateShadowBase(const ::Ice::Context&);

    virtual bool BackupDB(const ::std::string&, const ::Ice::Context&);

    virtual bool CheckDB(const ::OPI::CheckOptionsPrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool CheckLicence(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool CloseWorkspace(const ::Ice::Context&);

    virtual bool ConsolidateWorkspace(const ::Ice::Context&);

    virtual bool DeactivateShadowBase(const ::Ice::Context&);

    virtual bool DeleteWorkspace(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool DisableWorkspace(const ::Ice::Context&);

    virtual bool DiscardWorkspace(const ::Ice::Context&);

    virtual bool EnableWorkspace(const ::std::string&, const ::Ice::Context&);

    virtual bool ExecuteDatabaseAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool ExistWorkspace(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetDatabaseID(const ::Ice::Context&);

    virtual ::std::string GetPath(const ::Ice::Context&);

    virtual ::Ice::Int GetSchemaVersion(const ::Ice::Context&);

    virtual ::std::string GetVersionString(const ::Ice::Context&);

    virtual ::std::string GetWorkspace(const ::std::string&, ::Ice::Int, const ::std::string&, const ::std::string&, bool, const ::std::string&, const ::Ice::Context&);

    virtual bool IgnoreWriteProtect(const ::Ice::Context&);

    virtual bool InitDataArea(::Ice::Int, ::Ice::Int, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool InitMainBase(::Ice::Int, const ::std::string&, ::Ice::Int, ::Ice::Int, ::Ice::Int, bool, bool, const ::Ice::Context&);

    virtual bool InitSubBase(::Ice::Int, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool IsLicenced(const ::Ice::Context&);

    virtual bool IsShared(const ::Ice::Context&);

    virtual bool LocateWorkspace(const ::std::string&, const ::Ice::Context&);

    virtual bool OpenDatabase(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::OPI::PIACC, bool, bool, ::Ice::Int, ::OPI::ResourceTypes, bool, const ::Ice::Context&);

    virtual bool OpenWorkspace(const ::std::string&, const ::std::string&, bool, const ::std::string&, const ::Ice::Context&);

    virtual bool RecreateExtent(const ::std::string&, const ::Ice::Context&);

    virtual bool RestoreDB(const ::std::string&, const ::Ice::Context&);

    virtual bool SetupTypeID(::Ice::Int, const ::Ice::Context&);
};

class DictionaryHandle : virtual public ::IceDelegate::OPI::DictionaryHandle,
			 virtual public ::IceDelegateD::OPI::DatabaseHandle
{
public:

    virtual ::Ice::Int BaseType(const ::std::string&, const ::Ice::Context&);

    virtual bool CheckExpression(const ::std::string&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool CheckExpressionInClass(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool CheckExtentDef(const ::std::string&, const ::Ice::Context&);

    virtual bool CheckValueSet(const ::std::string&, const ::Ice::Context&);

    virtual bool CopyCodeset(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::Ice::Int, const ::std::string&, ::OPI::PIREPL, bool, bool, const ::Ice::Context&);

    virtual bool CopyExtentDef(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, bool, bool, const ::Ice::Context&);

    virtual bool CopyStructure(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::Ice::Int, const ::std::string&, const ::std::string&, ::OPI::PIREPL, bool, bool, const ::Ice::Context&);

    virtual bool CopyType(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::PIREPL, bool, bool, bool, const ::Ice::Context&);

    virtual bool CreateEnum(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual ::std::string CreateTempExtent(const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, bool, bool, const ::Ice::Context&);

    virtual bool DeleteEnum(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string EnumToString(const ::std::string&, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int GetLastSchemaVersion(const ::Ice::Context&);

    virtual ::std::string GetTempName(const ::std::string&, const ::Ice::Context&);

    virtual bool IsBasicType(const ::std::string&, const ::Ice::Context&);

    virtual bool OpenDictionary(const ::OPI::ODABAClientPrx&, const ::std::string&, ::OPI::PIACC, bool, ::Ice::Int, ::OPI::ResourceTypes, bool, const ::Ice::Context&);

    virtual ::Ice::Int StringToEnum(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool UpdateVersion(const ::Ice::Context&);
};

class ODABAClient : virtual public ::IceDelegate::OPI::ODABAClient,
		    virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void ActivateGUIMessages(const ::Ice::Context&);

    virtual bool BackupDB(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool CheckDB(const ::std::string&, const ::std::string&, const ::OPI::CheckOptionsPrx&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool Close(const ::Ice::Context&);

    virtual bool Connect(const ::std::string&, ::Ice::Int, const ::std::string&, const ::Ice::Context&);

    virtual bool DictDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual void Disconnect(const ::Ice::Context&);

    virtual bool Exist(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetDataSource(::Ice::Int, const ::Ice::Context&);

    virtual ::std::string GetHost(const ::Ice::Context&);

    virtual ::Ice::Int GetPort(const ::Ice::Context&);

    virtual ::std::string GetServerVariable(const ::std::string&, const ::Ice::Context&);

    virtual void Initialize(const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::ApplicationTypes, bool, const ::Ice::Context&);

    virtual bool IsConnected(const ::Ice::Context&);

    virtual bool KillClient(::Ice::Int, ::Ice::Int, bool, const ::Ice::Context&);

    virtual bool Open(const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::ApplicationTypes, const ::Ice::Context&);

    virtual ::OPI::DBObjectHandlePrx OpenDataSource(const ::std::string&, ::OPI::PIACC, const ::Ice::Context&);

    virtual bool PackDatabase(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool RestoreDB(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool SendClientMessage(::Ice::Int, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetServerVariable(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool ShutDown(const ::std::string&, const ::Ice::Context&);

    virtual bool StartPause(::Ice::Int, const ::Ice::Context&);

    virtual bool StatDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual void StopPause(const ::Ice::Context&);

    virtual bool SysInfoDisplay(const ::std::string&, const ::std::string&, const ::Ice::Context&);
};

class OperationHandle : virtual public ::IceDelegate::OPI::OperationHandle,
			virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual bool CheckExpression(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool CheckExpressionInClass(const ::OPI::DictionaryHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool Execute(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetResult(const ::Ice::Context&);

    virtual ::Ice::Int GetSize(const ::Ice::Context&);

    virtual bool IsValid(const ::Ice::Context&);

    virtual bool Open(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool ProvideExpression(const ::OPI::DictionaryHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);
};

class PropertyHandle : virtual public ::IceDelegate::OPI::PropertyHandle,
		       virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual bool Add(::Ice::Int, const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool AddByKey(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool AddInstance(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool AddOnPosition(::Ice::Int, bool, const ::Ice::Context&);

    virtual bool AddGlobal(::Ice::Int, const ::std::string&, const ::std::string&, bool, const ::Ice::Context&);

    virtual bool AddGlobalByKey(const ::std::string&, const ::std::string&, bool, const ::Ice::Context&);

    virtual bool AddGlobalOnPosition(::Ice::Int, bool, const ::Ice::Context&);

    virtual bool AddReference(const ::OPI::PropertyHandlePrx&, ::Ice::Int, const ::Ice::Context&);

    virtual bool AllocDescription(const ::Ice::Context&);

    virtual bool AllocateArea(const ::Ice::Context&);

    virtual bool AppendString(const ::std::string&, const ::Ice::Context&);

    virtual bool AutoLocate(const ::std::string&, const ::Ice::Context&);

    virtual bool Cancel(const ::Ice::Context&);

    virtual bool CancelBuffer(const ::Ice::Context&);

    virtual ::Ice::Int ChangeBuffer(::Ice::Int, const ::Ice::Context&);

    virtual bool ChangeCache(::Ice::Int, const ::Ice::Context&);

    virtual ::OPI::PIACC ChangeMode(::OPI::PIACC, const ::Ice::Context&);

    virtual bool Check(bool, const ::Ice::Context&);

    virtual bool CheckPosition(const ::Ice::Context&);

    virtual bool CheckUpdate(bool, const ::Ice::Context&);

    virtual bool CheckWProtect(const ::Ice::Context&);

    virtual bool Close(const ::Ice::Context&);

    virtual ::Ice::Int Compare(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual ::Ice::Int CompareDate(::Ice::Long, const ::Ice::Context&);

    virtual ::Ice::Int CompareFloat(::Ice::Float, const ::Ice::Context&);

    virtual ::Ice::Int CompareInteger(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int CompareString(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int CompareTime(::Ice::Long, const ::Ice::Context&);

    virtual ::Ice::Int CompareKey(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int CompareSortKey(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool CompareType(const ::OPI::PropertyHandlePrx&, bool, const ::Ice::Context&);

    virtual bool Copy(const ::OPI::PropertyHandlePrx&, const ::std::string&, ::Ice::Int, ::OPI::PIREPL, ::OPI::PIREPL, const ::Ice::Context&);

    virtual bool CopyData(const ::OPI::PropertyHandlePrx&, ::OPI::PIREPL, const ::Ice::Context&);

    virtual bool CopyHandle(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool CopyInstanceArea(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual ::Ice::Int CopySet(const ::OPI::PropertyHandlePrx&, ::OPI::PIREPL, ::OPI::PIREPL, bool, const ::Ice::Context&);

    virtual bool CreateTempExtent(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool Delete(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool DeleteByKey(const ::std::string&, const ::Ice::Context&);

    virtual bool DeleteOnPosition(::Ice::Int, bool, bool, const ::Ice::Context&);

    virtual bool DeleteIndexEntry(::Ice::Int, const ::Ice::Context&);

    virtual bool DeleteSet(bool, const ::Ice::Context&);

    virtual bool DisableKeyCheck(const ::Ice::Context&);

    virtual bool Duplicate(::Ice::Int, ::OPI::PIREPL, const ::Ice::Context&);

    virtual bool DuplicateKey(const ::std::string&, ::OPI::PIREPL, const ::Ice::Context&);

    virtual bool EnableKeyCheck(const ::Ice::Context&);

    virtual bool Execute(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool ExecuteInstanceAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool ExecutePropertyAction(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool Exist(const ::Ice::Context&);

    virtual ::std::string ExtractKey(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string ExtractSortKey(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string FirstKey(const ::Ice::Context&);

    virtual bool Get(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool GetAtPosition(::Ice::Int, const ::Ice::Context&);

    virtual bool GetByKey(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetActionResult(const ::Ice::Context&);

    virtual ::std::string GetArea(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetAttribute(::Ice::Int, bool, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetBaseProperty(const ::Ice::Context&);

    virtual ::Ice::Int GetCollectionID(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetCollectionProperty(const ::Ice::Context&);

    virtual ::Ice::Int GetCount(const ::Ice::Context&);

    virtual ::Ice::Int GetCurrentIndex(const ::Ice::Context&);

    virtual ::Ice::Int GetCurrentSize(const ::Ice::Context&);

    virtual ::std::string GetCurrentType(const ::Ice::Context&);

    virtual ::OPI::DatabaseHandlePrx GetDBHandle(const ::Ice::Context&);

    virtual ::Ice::Long GetDate(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Long GetDateTime(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetDay(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::DictionaryHandlePrx GetDictionary(const ::Ice::Context&);

    virtual ::Ice::Int GetDimension(const ::Ice::Context&);

    virtual ::Ice::Float GetDouble(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetExtInstModCount(const ::Ice::Context&);

    virtual ::std::string GetExtentName(const ::Ice::Context&);

    virtual ::std::string GetGUID(const ::Ice::Context&);

    virtual ::Ice::Int GetGenAttrType(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetGenOrderType(const ::Ice::Context&);

    virtual ::Ice::Int GetGlobalID(const ::Ice::Context&);

    virtual ::Ice::Int GetHours(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetID(::Ice::Int, const ::Ice::Context&);

    virtual ::std::string GetIdentity(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetIndexName(::Ice::Int, const ::Ice::Context&);

    virtual bool GetInitInstance(const ::Ice::Context&);

    virtual ::Ice::Int GetInstModCount(const ::Ice::Context&);

    virtual ::Ice::Int GetInt(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetIntValue(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetKey(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int GetKeyLength(const ::Ice::Context&);

    virtual ::Ice::Int GetLOID(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int GetLOIDByKey(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetMinutes(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::PIACC GetMode(const ::Ice::Context&);

    virtual ::Ice::Int GetMonth(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetNormalized(const ::Ice::Context&);

    virtual ::OPI::DBObjectHandlePrx GetObjectHandle(const ::Ice::Context&);

    virtual ::Ice::Int GetOrigin(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetParentProperty(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetPropertyHandle(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetPropertyPath(const ::Ice::Context&);

    virtual ::Ice::Int GetRefModCount(const ::Ice::Context&);

    virtual ::std::string GetReference(::Ice::Int, bool, bool, const ::Ice::Context&);

    virtual bool GetRelative(::Ice::Int, const ::Ice::Context&);

    virtual ::Ice::Int GetRelativeCount(const ::Ice::Context&);

    virtual ::Ice::Int GetRelativeIndex(bool, const ::Ice::Context&);

    virtual ::Ice::Int GetSeconds(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetSelectedKey(const ::Ice::Context&);

    virtual ::Ice::Int GetSize(const ::Ice::Context&);

    virtual ::Ice::Int GetSizeOf(const ::Ice::Context&);

    virtual ::std::string GetSortKey(const ::Ice::Context&);

    virtual ::Ice::Int GetSortKeyLength(const ::Ice::Context&);

    virtual ::std::string GetString(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Int GetStringLength(const ::Ice::Context&);

    virtual ::std::string GetStringValue(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetSubString(::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    virtual ::std::string GetText(const ::std::string&, const ::Ice::Context&);

    virtual ::Ice::Long GetTime(const ::std::string&, const ::Ice::Context&);

    virtual ::std::string GetType(const ::Ice::Context&);

    virtual bool GetValid(const ::Ice::Context&);

    virtual ::Ice::Int GetVersion(const ::Ice::Context&);

    virtual ::Ice::Int GetYear(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Group(const ::OPI::PropertyHandlePrx&, const ::std::string&, bool, const ::Ice::Context&);

    virtual bool HasData(const ::Ice::Context&);

    virtual bool HasDescription(const ::Ice::Context&);

    virtual bool HasGenericAttributes(const ::Ice::Context&);

    virtual bool HasIndex(const ::Ice::Context&);

    virtual bool Inherits(const ::std::string&, const ::Ice::Context&);

    virtual bool InsertString(const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool InsertTerminator(const ::std::string&, const ::Ice::Context&);

    virtual bool InstanceInserted(const ::Ice::Context&);

    virtual ::std::string InstanceToString(const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Intersect(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool Is(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool IsA(const ::std::string&, const ::Ice::Context&);

    virtual bool IsActive(const ::Ice::Context&);

    virtual bool IsAttribute(const ::Ice::Context&);

    virtual bool IsAutoSelection(const ::Ice::Context&);

    virtual bool IsBasedOn(const ::std::string&, const ::Ice::Context&);

    virtual bool IsBasetypeProperty(const ::Ice::Context&);

    virtual bool IsBasicType(const ::Ice::Context&);

    virtual bool IsClient(const ::Ice::Context&);

    virtual bool IsCollection(const ::std::string&, const ::Ice::Context&);

    virtual bool IsCollectionUpdate(const ::Ice::Context&);

    virtual bool IsCopyHandle(const ::Ice::Context&);

    virtual bool IsDirty(const ::Ice::Context&);

    virtual bool IsEmpty(const ::Ice::Context&);

    virtual bool IsEnumeration(const ::Ice::Context&);

    virtual bool IsGenericAttribute(const ::Ice::Context&);

    virtual bool IsInitInstance(const ::Ice::Context&);

    virtual bool IsMemo(const ::std::string&, const ::Ice::Context&);

    virtual bool IsModified(const ::Ice::Context&);

    virtual bool IsNewInstance(const ::Ice::Context&);

    virtual bool IsNumeric(const ::Ice::Context&);

    virtual bool IsOldInstance(const ::Ice::Context&);

    virtual bool IsOwner(const ::Ice::Context&);

    virtual bool IsPositioned(const ::std::string&, const ::Ice::Context&);

    virtual bool IsReadOnly(const ::Ice::Context&);

    virtual bool IsSelected(const ::std::string&, const ::Ice::Context&);

    virtual bool IsSensitive(const ::std::string&, const ::Ice::Context&);

    virtual bool IsServer(const ::Ice::Context&);

    virtual bool IsShareBaseHandle(const ::std::string&, const ::Ice::Context&);

    virtual bool IsStructure(const ::Ice::Context&);

    virtual bool IsText(const ::std::string&, const ::Ice::Context&);

    virtual bool IsTransient(const ::Ice::Context&);

    virtual bool IsTrue(const ::std::string&, const ::Ice::Context&);

    virtual bool IsTyped(const ::Ice::Context&);

    virtual bool IsUserHandle(const ::Ice::Context&);

    virtual bool IsValid(bool, const ::Ice::Context&);

    virtual bool IsValidText(const ::std::string&, const ::Ice::Context&);

    virtual bool IsVariableType(const ::Ice::Context&);

    virtual bool IsWeakTyped(const ::Ice::Context&);

    virtual bool IsWrite(const ::Ice::Context&);

    virtual bool Locate(::Ice::Int, bool, const ::Ice::Context&);

    virtual bool LocatePath(const ::Ice::Context&);

    virtual bool Lock(const ::Ice::Context&);

    virtual bool LockSet(const ::Ice::Context&);

    virtual void MarkUnused(const ::Ice::Context&);

    virtual void MarkUsed(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Minus(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool Modify(const ::Ice::Context&);

    virtual bool Move(const ::OPI::PropertyHandlePrx&, const ::std::string&, ::OPI::PIREPL, const ::Ice::Context&);

    virtual bool MoveDown(const ::Ice::Context&);

    virtual bool MoveUp(const ::Ice::Context&);

    virtual ::std::string NextKey(const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool NoWrite(const ::Ice::Context&);

    virtual bool Open(const ::Ice::Context&);

    virtual bool OpenBigInt(::Ice::Int, const ::Ice::Context&);

    virtual bool OpenBoolean(bool, const ::Ice::Context&);

    virtual bool OpenChild(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool OpenChildReference(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual bool OpenCopy(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool OpenDate(::Ice::Long, const ::Ice::Context&);

    virtual bool OpenExtent(const ::OPI::DBObjectHandlePrx&, const ::std::string&, ::OPI::PIACC, bool, const ::std::string&, const ::Ice::Context&);

    virtual bool OpenFloat(::Ice::Float, const ::Ice::Context&);

    virtual bool OpenInteger(::Ice::Int, const ::Ice::Context&);

    virtual bool OpenReference(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool OpenSizedString(const ::std::string&, ::Ice::Int, const ::Ice::Context&);

    virtual bool OpenString(const ::std::string&, bool, const ::Ice::Context&);

    virtual bool OpenTime(::Ice::Long, const ::Ice::Context&);

    virtual bool OpenTimestamp(::Ice::Long, const ::Ice::Context&);

    virtual bool OpenHierarchy(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, bool, ::OPI::PIACC, bool, const ::Ice::Context&);

    virtual bool OwnsData(const ::Ice::Context&);

    virtual bool Position(::Ice::Int, const ::Ice::Context&);

    virtual bool PositionTop(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Power(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool ProvGenAttribute(const ::Ice::Context&);

    virtual bool Provide(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool ProvideAtPosition(::Ice::Int, const ::Ice::Context&);

    virtual bool ProvideByKey(const ::std::string&, const ::Ice::Context&);

    virtual bool ProvideArea(const ::Ice::Context&);

    virtual ::std::string ProvideGUID(const ::Ice::Context&);

    virtual bool ProvideGlobal(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool ProvideGlobalAtPosition(::Ice::Int, const ::Ice::Context&);

    virtual bool ProvideGlobalByKey(const ::std::string&, const ::Ice::Context&);

    virtual ::OPI::OperationHandlePrx ProvideOperation(const ::std::string&, const ::Ice::Context&);

    virtual bool Refresh(const ::Ice::Context&);

    virtual bool ReleaseBuffer(const ::Ice::Context&);

    virtual bool RemoveFromCollection(const ::Ice::Context&);

    virtual bool RemoveString(const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Context&);

    virtual bool RemoveTerminator(const ::std::string&, const ::Ice::Context&);

    virtual bool Rename(const ::std::string&, const ::Ice::Context&);

    virtual bool RepairIndex(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool ReplaceString(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool ReplaceSysVariables(const ::Ice::Context&);

    virtual bool Reset(const ::Ice::Context&);

    virtual void ResetDirty(const ::Ice::Context&);

    virtual bool ResetTransientProperty(const ::Ice::Context&);

    virtual bool ResetWProtect(const ::Ice::Context&);

    virtual bool Save(const ::std::string&, bool, const ::Ice::Context&);

    virtual ::Ice::Int SearchText(const ::std::string&, ::Ice::Int, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Select(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Context&);

    virtual void SetActionResult(const ::std::string&, const ::Ice::Context&);

    virtual bool SetContextVariables(const ::std::string&, const ::Ice::Context&);

    virtual void SetDirty(const ::Ice::Context&);

    virtual bool SetDynLength(const ::Ice::Context&);

    virtual bool SetGenAttribute(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetKey(const ::std::string&, const ::Ice::Context&);

    virtual void SetModified(const ::Ice::Context&);

    virtual bool SetNormalized(::Ice::Int, const ::Ice::Context&);

    virtual bool SetOrder(const ::std::string&, const ::std::string&, const ::Ice::Context&);

    virtual bool SetSelection(const ::std::string&, const ::Ice::Context&);

    virtual bool SetSortKey(const ::std::string&, const ::Ice::Context&);

    virtual bool SetTransientProperty(const ::OPI::PropertyHandlePrx&, const ::Ice::Context&);

    virtual bool SetType(const ::std::string&, const ::Ice::Context&);

    virtual bool SetUpdate(bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValue(const ::OPI::PropertyHandlePrx&, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueBigInt(::Ice::Int, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueBoolean(bool, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueDate(::Ice::Long, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueFloat(::Ice::Float, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueInteger(::Ice::Int, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueString(const ::std::string&, bool, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueTime(::Ice::Long, bool, const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx SetValueTimestamp(::Ice::Long, bool, const ::Ice::Context&);

    virtual bool SetVersion(::Ice::Int, const ::Ice::Context&);

    virtual bool SetWProtect(const ::Ice::Context&);

    virtual bool ToTop(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx Union(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, bool, const ::Ice::Context&);

    virtual bool Unlock(const ::Ice::Context&);

    virtual bool UnlockSet(const ::Ice::Context&);
};

class OPIFactory : virtual public ::IceDelegate::OPI::OPIFactory,
		   virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual void Destroy(const ::Ice::Context&);

    virtual ::OPI::CheckOptionsPrx GetCheckOptions(const ::Ice::Context&);

    virtual ::OPI::DBObjectHandlePrx GetDBObjectHandle(const ::Ice::Context&);

    virtual ::OPI::DataSourceHandlePrx GetDataSourceHandle(const ::Ice::Context&);

    virtual ::OPI::DatabaseHandlePrx GetDatabaseHandle(const ::Ice::Context&);

    virtual ::OPI::DictionaryHandlePrx GetDictionaryHandle(const ::Ice::Context&);

    virtual ::OPI::ODABAClientPrx GetODABAClient(const ::Ice::Context&);

    virtual ::OPI::OperationHandlePrx GetOperationHandle(const ::Ice::Context&);

    virtual ::OPI::PropertyHandlePrx GetPropertyHandle(const ::Ice::Context&);
};

class Session : virtual public ::IceDelegate::OPI::Session,
		virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::OPI::OPIFactoryPrx CreateSession(const ::Ice::Context&);

    virtual void Destroy(const ::Ice::Context&);

    virtual void TimeOut(::Ice::Int, const ::Ice::Context&);

    virtual ::std::string getName(const ::Ice::Context&);
};

class SessionFactory : virtual public ::IceDelegate::OPI::SessionFactory,
		       virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::OPI::SessionPrx CreateProxy(const ::std::string&, const ::Ice::Context&);

    virtual void shutdown(const ::Ice::Context&);
};

}

}

namespace OPI
{

class CheckOptions : virtual public ::Ice::Object
{
public:

    typedef CheckOptionsPrx ProxyType;
    typedef CheckOptionsPtr PointerType;
    
    CheckOptions() {}
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool Initialize(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Initialize(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__CheckOptionsPtr(void*, ::Ice::ObjectPtr&);

class DBObjectHandle : virtual public ::Ice::Object
{
public:

    typedef DBObjectHandlePrx ProxyType;
    typedef DBObjectHandlePtr PointerType;
    
    DBObjectHandle() {}
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::Int BeginTransaction(bool, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___BeginTransaction(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ChangeTimeStamp(::Ice::Int, ::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ChangeTimeStamp(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CommitTransaction(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CommitTransaction(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx CreateTempPropertyHandle(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CreateTempPropertyHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DeleteExtent(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DeleteExtent(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DeleteExtentRef(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DeleteExtentRef(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void DisableEventHandling(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DisableEventHandling(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void EnableEventHandling(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___EnableEventHandling(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool EventHandling(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___EventHandling(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ExecuteDBObjectAction(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ExecuteDBObjectAction(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ExecuteExpression(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ExtentExist(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ExtentExist(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PIACC GetAccess(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetAccess(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetActionResult(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetActionResult(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DatabaseHandlePrx GetDBHandle(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDBHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DataSourceHandlePrx GetDataSource(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDataSource(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DictionaryHandlePrx GetDictionary(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDictionary(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetExtent(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetExtent(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DBObjectHandlePrx GetHighObject(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetHighObject(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetObject(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetObject(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetServerVariable(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetServerVariable(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetSystemVersion(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetSystemVersion(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Long GetTimeStamp(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetTimeStamp(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetTransactionLevel(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetTransactionLevel(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetVersion(::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetVersion(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsClient(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsClient(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsEmpty(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsEmpty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsOpened(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsOpened(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsServer(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsServer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsValid(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsValid(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool NewVersion(::Ice::Long, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___NewVersion(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenObject(const ::OPI::DBObjectHandlePrx&, const ::std::string&, ::OPI::PIACC, ::Ice::Int, ::OPI::ResourceTypes, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenObject(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool RollBack(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RollBack(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void SetActionResult(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetActionResult(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int SetOverload(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetOverload(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetServerVariable(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetServerVariable(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetUserDefinedIdentity(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetUserDefinedIdentity(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetVersion(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetVersion(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetVersioni1(::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetVersioni1(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetVersioni2(::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetVersioni2(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int VersionCount(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___VersionCount(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__DBObjectHandlePtr(void*, ::Ice::ObjectPtr&);

class DataSourceHandle : virtual public ::Ice::Object
{
public:

    typedef DataSourceHandlePrx ProxyType;
    typedef DataSourceHandlePtr PointerType;
    
    DataSourceHandle() {}
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool BeginTransaction(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___BeginTransaction(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Close(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Close(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CloseDBObject(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CloseDBObject(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CloseDatabase(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CloseDatabase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CloseDictionary(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CloseDictionary(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CloseProperty(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CloseProperty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CloseResourceDB(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CloseResourceDB(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CommitTransaction(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CommitTransaction(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Connect(const ::OPI::ODABAClientPrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Connect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Disconnect(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Disconnect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Open(const ::OPI::ODABAClientPrx&, ::OPI::PIACC, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Open(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Openi02(const ::OPI::ODABAClientPrx&, const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Openi02(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Openi1(const ::OPI::ODABAClientPrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Openi1(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DBObjectHandlePrx OpenDBObject(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenDBObject(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DatabaseHandlePrx OpenDatabase(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenDatabase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DictionaryHandlePrx OpenDictionary(::OPI::PIACC, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenDictionary(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx OpenProperty(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenProperty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DatabaseHandlePrx OpenResourceDB(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenResourceDB(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool RollBack(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RollBack(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetDBObject(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetDBObject(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetDataSource(const ::OPI::DataSourceHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetDataSource(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetDatabase(const ::OPI::DatabaseHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetDatabase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetDictionary(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetDictionary(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetResourceDB(const ::OPI::DatabaseHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetResourceDB(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetVariables(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetVariables(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Setup(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Setup(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetupVariables(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetupVariables(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__DataSourceHandlePtr(void*, ::Ice::ObjectPtr&);

class DatabaseHandle : virtual public ::OPI::DBObjectHandle
{
public:

    typedef DatabaseHandlePrx ProxyType;
    typedef DatabaseHandlePtr PointerType;
    
    DatabaseHandle() {}
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool ActivateShadowBase(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ActivateShadowBase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool BackupDB(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___BackupDB(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CheckDB(const ::OPI::CheckOptionsPrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckDB(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CheckLicence(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckLicence(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CloseWorkspace(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CloseWorkspace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ConsolidateWorkspace(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ConsolidateWorkspace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DeactivateShadowBase(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DeactivateShadowBase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DeleteWorkspace(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DeleteWorkspace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DisableWorkspace(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DisableWorkspace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DiscardWorkspace(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DiscardWorkspace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool EnableWorkspace(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___EnableWorkspace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ExecuteDatabaseAction(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ExecuteDatabaseAction(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ExistWorkspace(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ExistWorkspace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetDatabaseID(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDatabaseID(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetPath(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetPath(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetSchemaVersion(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetSchemaVersion(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetVersionString(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetVersionString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetWorkspace(const ::std::string&, ::Ice::Int, const ::std::string&, const ::std::string&, bool, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetWorkspace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IgnoreWriteProtect(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IgnoreWriteProtect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool InitDataArea(::Ice::Int, ::Ice::Int, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___InitDataArea(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool InitMainBase(::Ice::Int, const ::std::string&, ::Ice::Int, ::Ice::Int, ::Ice::Int, bool, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___InitMainBase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool InitSubBase(::Ice::Int, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___InitSubBase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsLicenced(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsLicenced(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsShared(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsShared(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool LocateWorkspace(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___LocateWorkspace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenDatabase(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::OPI::PIACC, bool, bool, ::Ice::Int, ::OPI::ResourceTypes, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenDatabase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenWorkspace(const ::std::string&, const ::std::string&, bool, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenWorkspace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool RecreateExtent(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RecreateExtent(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool RestoreDB(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RestoreDB(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetupTypeID(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetupTypeID(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__DatabaseHandlePtr(void*, ::Ice::ObjectPtr&);

class DictionaryHandle : virtual public ::OPI::DatabaseHandle
{
public:

    typedef DictionaryHandlePrx ProxyType;
    typedef DictionaryHandlePtr PointerType;
    
    DictionaryHandle() {}
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::Ice::Int BaseType(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___BaseType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CheckExpression(const ::std::string&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckExpression(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CheckExpressionInClass(const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckExpressionInClass(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CheckExtentDef(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckExtentDef(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CheckValueSet(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckValueSet(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CopyCodeset(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::Ice::Int, const ::std::string&, ::OPI::PIREPL, bool, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CopyCodeset(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CopyExtentDef(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, bool, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CopyExtentDef(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CopyStructure(const ::OPI::DictionaryHandlePrx&, const ::std::string&, ::Ice::Int, const ::std::string&, const ::std::string&, ::OPI::PIREPL, bool, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CopyStructure(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CopyType(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::PIREPL, bool, bool, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CopyType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CreateEnum(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CreateEnum(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string CreateTempExtent(const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, bool, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CreateTempExtent(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DeleteEnum(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DeleteEnum(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string EnumToString(const ::std::string&, ::Ice::Int, const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___EnumToString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetLastSchemaVersion(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetLastSchemaVersion(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetTempName(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetTempName(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsBasicType(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsBasicType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenDictionary(const ::OPI::ODABAClientPrx&, const ::std::string&, ::OPI::PIACC, bool, ::Ice::Int, ::OPI::ResourceTypes, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenDictionary(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int StringToEnum(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___StringToEnum(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool UpdateVersion(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___UpdateVersion(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__DictionaryHandlePtr(void*, ::Ice::ObjectPtr&);

class ODABAClient : virtual public ::Ice::Object
{
public:

    typedef ODABAClientPrx ProxyType;
    typedef ODABAClientPtr PointerType;
    
    ODABAClient() {}
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void ActivateGUIMessages(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ActivateGUIMessages(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool BackupDB(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___BackupDB(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CheckDB(const ::std::string&, const ::std::string&, const ::OPI::CheckOptionsPrx&, const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckDB(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Close(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Close(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Connect(const ::std::string&, ::Ice::Int, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Connect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DictDisplay(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DictDisplay(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void Disconnect(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Disconnect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Exist(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Exist(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetDataSource(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDataSource(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetHost(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetHost(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetPort(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetPort(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetServerVariable(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetServerVariable(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void Initialize(const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::ApplicationTypes, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Initialize(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsConnected(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsConnected(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool KillClient(::Ice::Int, ::Ice::Int, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___KillClient(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Open(const ::std::string&, const ::std::string&, const ::std::string&, ::OPI::ApplicationTypes, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Open(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DBObjectHandlePrx OpenDataSource(const ::std::string&, ::OPI::PIACC, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenDataSource(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool PackDatabase(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___PackDatabase(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool RestoreDB(const ::std::string&, const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RestoreDB(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SendClientMessage(::Ice::Int, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SendClientMessage(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetServerVariable(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetServerVariable(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ShutDown(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ShutDown(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool StartPause(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___StartPause(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool StatDisplay(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___StatDisplay(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void StopPause(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___StopPause(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SysInfoDisplay(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SysInfoDisplay(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__ODABAClientPtr(void*, ::Ice::ObjectPtr&);

class OperationHandle : virtual public ::Ice::Object
{
public:

    typedef OperationHandlePrx ProxyType;
    typedef OperationHandlePtr PointerType;
    
    OperationHandle() {}
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool CheckExpression(const ::OPI::DictionaryHandlePrx&, const ::std::string&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckExpression(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CheckExpressionInClass(const ::OPI::DictionaryHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckExpressionInClass(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Execute(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Execute(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx GetResult(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetResult(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetSize(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetSize(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsValid(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsValid(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Open(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Open(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ProvideExpression(const ::OPI::DictionaryHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ProvideExpression(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__OperationHandlePtr(void*, ::Ice::ObjectPtr&);

class PropertyHandle : virtual public ::Ice::Object
{
public:

    typedef PropertyHandlePrx ProxyType;
    typedef PropertyHandlePtr PointerType;
    
    PropertyHandle() {}
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual bool Add(::Ice::Int, const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Add(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool AddByKey(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AddByKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool AddInstance(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AddInstance(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool AddOnPosition(::Ice::Int, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AddOnPosition(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool AddGlobal(::Ice::Int, const ::std::string&, const ::std::string&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AddGlobal(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool AddGlobalByKey(const ::std::string&, const ::std::string&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AddGlobalByKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool AddGlobalOnPosition(::Ice::Int, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AddGlobalOnPosition(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool AddReference(const ::OPI::PropertyHandlePrx&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AddReference(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool AllocDescription(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AllocDescription(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool AllocateArea(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AllocateArea(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool AppendString(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AppendString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool AutoLocate(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___AutoLocate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Cancel(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Cancel(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CancelBuffer(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CancelBuffer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int ChangeBuffer(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ChangeBuffer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ChangeCache(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ChangeCache(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PIACC ChangeMode(::OPI::PIACC, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ChangeMode(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Check(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Check(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CheckPosition(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckPosition(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CheckUpdate(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckUpdate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CheckWProtect(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CheckWProtect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Close(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Close(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int Compare(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Compare(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int CompareDate(::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CompareDate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int CompareFloat(::Ice::Float, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CompareFloat(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int CompareInteger(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CompareInteger(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int CompareString(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CompareString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int CompareTime(::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CompareTime(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int CompareKey(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CompareKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int CompareSortKey(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CompareSortKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CompareType(const ::OPI::PropertyHandlePrx&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CompareType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Copy(const ::OPI::PropertyHandlePrx&, const ::std::string&, ::Ice::Int, ::OPI::PIREPL, ::OPI::PIREPL, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Copy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CopyData(const ::OPI::PropertyHandlePrx&, ::OPI::PIREPL, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CopyData(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CopyHandle(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CopyHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CopyInstanceArea(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CopyInstanceArea(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int CopySet(const ::OPI::PropertyHandlePrx&, ::OPI::PIREPL, ::OPI::PIREPL, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CopySet(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool CreateTempExtent(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CreateTempExtent(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Delete(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Delete(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DeleteByKey(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DeleteByKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DeleteOnPosition(::Ice::Int, bool, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DeleteOnPosition(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DeleteIndexEntry(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DeleteIndexEntry(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DeleteSet(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DeleteSet(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DisableKeyCheck(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DisableKeyCheck(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Duplicate(::Ice::Int, ::OPI::PIREPL, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Duplicate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool DuplicateKey(const ::std::string&, ::OPI::PIREPL, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___DuplicateKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool EnableKeyCheck(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___EnableKeyCheck(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Execute(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Execute(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx ExecuteExpression(const ::OPI::DBObjectHandlePrx&, const ::OPI::DBObjectHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ExecuteExpression(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ExecuteInstanceAction(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ExecuteInstanceAction(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ExecutePropertyAction(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ExecutePropertyAction(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Exist(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Exist(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string ExtractKey(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ExtractKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string ExtractSortKey(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ExtractSortKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string FirstKey(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___FirstKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Get(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Get(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool GetAtPosition(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetAtPosition(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool GetByKey(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetByKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetActionResult(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetActionResult(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetArea(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetArea(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetAttribute(::Ice::Int, bool, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetAttribute(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx GetBaseProperty(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetBaseProperty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetCollectionID(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetCollectionID(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx GetCollectionProperty(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetCollectionProperty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetCount(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetCount(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetCurrentIndex(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetCurrentIndex(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetCurrentSize(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetCurrentSize(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetCurrentType(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetCurrentType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DatabaseHandlePrx GetDBHandle(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDBHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Long GetDate(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Long GetDateTime(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDateTime(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetDay(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDay(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DictionaryHandlePrx GetDictionary(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDictionary(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetDimension(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDimension(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Float GetDouble(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDouble(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetExtInstModCount(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetExtInstModCount(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetExtentName(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetExtentName(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetGUID(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetGUID(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetGenAttrType(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetGenAttrType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetGenOrderType(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetGenOrderType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetGlobalID(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetGlobalID(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetHours(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetHours(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetID(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetID(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetIdentity(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetIdentity(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetIndexName(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetIndexName(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool GetInitInstance(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetInitInstance(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetInstModCount(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetInstModCount(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetInt(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetInt(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetIntValue(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetIntValue(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetKey(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetKeyLength(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetKeyLength(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetLOID(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetLOID(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetLOIDByKey(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetLOIDByKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetMinutes(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetMinutes(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PIACC GetMode(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetMode(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetMonth(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetMonth(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetNormalized(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetNormalized(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DBObjectHandlePrx GetObjectHandle(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetObjectHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetOrigin(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetOrigin(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx GetParentProperty(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetParentProperty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx GetPropertyHandle(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetPropertyHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetPropertyPath(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetPropertyPath(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetRefModCount(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetRefModCount(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetReference(::Ice::Int, bool, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetReference(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool GetRelative(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetRelative(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetRelativeCount(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetRelativeCount(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetRelativeIndex(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetRelativeIndex(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetSeconds(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetSeconds(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetSelectedKey(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetSelectedKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetSize(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetSize(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetSizeOf(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetSizeOf(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetSortKey(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetSortKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetSortKeyLength(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetSortKeyLength(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetString(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetStringLength(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetStringLength(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetStringValue(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetStringValue(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetSubString(::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetSubString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetText(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetText(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Long GetTime(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetTime(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string GetType(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool GetValid(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetValid(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetVersion(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetVersion(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int GetYear(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetYear(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx Group(const ::OPI::PropertyHandlePrx&, const ::std::string&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Group(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool HasData(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___HasData(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool HasDescription(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___HasDescription(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool HasGenericAttributes(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___HasGenericAttributes(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool HasIndex(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___HasIndex(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Inherits(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Inherits(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool InsertString(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___InsertString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool InsertTerminator(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___InsertTerminator(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool InstanceInserted(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___InstanceInserted(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string InstanceToString(const ::std::string&, const ::std::string&, const ::std::string&, const ::std::string&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___InstanceToString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx Intersect(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Intersect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Is(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Is(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsA(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsActive(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsActive(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsAttribute(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsAttribute(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsAutoSelection(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsAutoSelection(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsBasedOn(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsBasedOn(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsBasetypeProperty(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsBasetypeProperty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsBasicType(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsBasicType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsClient(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsClient(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsCollection(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsCollection(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsCollectionUpdate(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsCollectionUpdate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsCopyHandle(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsCopyHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsDirty(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsDirty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsEmpty(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsEmpty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsEnumeration(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsEnumeration(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsGenericAttribute(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsGenericAttribute(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsInitInstance(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsInitInstance(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsMemo(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsMemo(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsModified(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsModified(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsNewInstance(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsNewInstance(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsNumeric(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsNumeric(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsOldInstance(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsOldInstance(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsOwner(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsOwner(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsPositioned(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsPositioned(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsReadOnly(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsReadOnly(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsSelected(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsSelected(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsSensitive(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsSensitive(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsServer(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsServer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsShareBaseHandle(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsShareBaseHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsStructure(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsStructure(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsText(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsText(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsTransient(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsTransient(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsTrue(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsTrue(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsTyped(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsTyped(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsUserHandle(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsUserHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsValid(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsValid(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsValidText(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsValidText(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsVariableType(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsVariableType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsWeakTyped(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsWeakTyped(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool IsWrite(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___IsWrite(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Locate(::Ice::Int, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Locate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool LocatePath(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___LocatePath(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Lock(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Lock(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool LockSet(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___LockSet(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void MarkUnused(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___MarkUnused(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void MarkUsed(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___MarkUsed(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx Minus(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Minus(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Modify(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Modify(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Move(const ::OPI::PropertyHandlePrx&, const ::std::string&, ::OPI::PIREPL, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Move(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool MoveDown(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___MoveDown(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool MoveUp(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___MoveUp(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string NextKey(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___NextKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool NoWrite(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___NoWrite(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Open(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Open(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenBigInt(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenBigInt(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenBoolean(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenBoolean(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenChild(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenChild(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenChildReference(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenChildReference(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenCopy(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenCopy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenDate(::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenDate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenExtent(const ::OPI::DBObjectHandlePrx&, const ::std::string&, ::OPI::PIACC, bool, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenExtent(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenFloat(::Ice::Float, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenFloat(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenInteger(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenInteger(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenReference(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenReference(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenSizedString(const ::std::string&, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenSizedString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenString(const ::std::string&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenTime(::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenTime(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenTimestamp(::Ice::Long, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenTimestamp(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OpenHierarchy(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, bool, ::OPI::PIACC, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OpenHierarchy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool OwnsData(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___OwnsData(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Position(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Position(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool PositionTop(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___PositionTop(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx Power(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Power(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ProvGenAttribute(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ProvGenAttribute(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Provide(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Provide(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ProvideAtPosition(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ProvideAtPosition(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ProvideByKey(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ProvideByKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ProvideArea(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ProvideArea(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string ProvideGUID(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ProvideGUID(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ProvideGlobal(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ProvideGlobal(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ProvideGlobalAtPosition(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ProvideGlobalAtPosition(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ProvideGlobalByKey(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ProvideGlobalByKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::OperationHandlePrx ProvideOperation(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ProvideOperation(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Refresh(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Refresh(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ReleaseBuffer(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ReleaseBuffer(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool RemoveFromCollection(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RemoveFromCollection(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool RemoveString(const ::std::string&, ::Ice::Int, ::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RemoveString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool RemoveTerminator(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RemoveTerminator(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Rename(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Rename(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool RepairIndex(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___RepairIndex(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ReplaceString(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ReplaceString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ReplaceSysVariables(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ReplaceSysVariables(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Reset(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Reset(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void ResetDirty(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ResetDirty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ResetTransientProperty(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ResetTransientProperty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ResetWProtect(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ResetWProtect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Save(const ::std::string&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Save(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::Int SearchText(const ::std::string&, ::Ice::Int, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SearchText(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx Select(const ::OPI::PropertyHandlePrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Select(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void SetActionResult(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetActionResult(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetContextVariables(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetContextVariables(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void SetDirty(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetDirty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetDynLength(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetDynLength(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetGenAttribute(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetGenAttribute(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetKey(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void SetModified(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetModified(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetNormalized(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetNormalized(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetOrder(const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetOrder(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetSelection(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetSelection(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetSortKey(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetSortKey(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetTransientProperty(const ::OPI::PropertyHandlePrx&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetTransientProperty(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetType(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetType(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetUpdate(bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetUpdate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx SetValue(const ::OPI::PropertyHandlePrx&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetValue(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx SetValueBigInt(::Ice::Int, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetValueBigInt(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx SetValueBoolean(bool, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetValueBoolean(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx SetValueDate(::Ice::Long, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetValueDate(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx SetValueFloat(::Ice::Float, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetValueFloat(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx SetValueInteger(::Ice::Int, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetValueInteger(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx SetValueString(const ::std::string&, bool, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetValueString(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx SetValueTime(::Ice::Long, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetValueTime(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx SetValueTimestamp(::Ice::Long, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetValueTimestamp(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetVersion(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetVersion(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool SetWProtect(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___SetWProtect(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool ToTop(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___ToTop(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx Union(const ::OPI::PropertyHandlePrx&, const ::OPI::PropertyHandlePrx&, const ::std::string&, bool, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Union(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool Unlock(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Unlock(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual bool UnlockSet(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___UnlockSet(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__PropertyHandlePtr(void*, ::Ice::ObjectPtr&);

class OPIFactory : virtual public ::Ice::Object
{
public:

    typedef OPIFactoryPrx ProxyType;
    typedef OPIFactoryPtr PointerType;
    
    OPIFactory() {}
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual void Destroy(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Destroy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::CheckOptionsPrx GetCheckOptions(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetCheckOptions(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DBObjectHandlePrx GetDBObjectHandle(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDBObjectHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DataSourceHandlePrx GetDataSourceHandle(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDataSourceHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DatabaseHandlePrx GetDatabaseHandle(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDatabaseHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::DictionaryHandlePrx GetDictionaryHandle(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetDictionaryHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::ODABAClientPrx GetODABAClient(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetODABAClient(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::OperationHandlePrx GetOperationHandle(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetOperationHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::OPI::PropertyHandlePrx GetPropertyHandle(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___GetPropertyHandle(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__OPIFactoryPtr(void*, ::Ice::ObjectPtr&);

class Session : virtual public ::Ice::Object
{
public:

    typedef SessionPrx ProxyType;
    typedef SessionPtr PointerType;
    
    Session() {}
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::OPI::OPIFactoryPrx CreateSession(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CreateSession(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void Destroy(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___Destroy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void TimeOut(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___TimeOut(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string getName(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___getName(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__SessionPtr(void*, ::Ice::ObjectPtr&);

class SessionFactory : virtual public ::Ice::Object
{
public:

    typedef SessionFactoryPrx ProxyType;
    typedef SessionFactoryPtr PointerType;
    
    SessionFactory() {}
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::OPI::SessionPrx CreateProxy(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___CreateProxy(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void shutdown(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::IceInternal::DispatchStatus ___shutdown(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::IceInternal::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

void __patch__SessionFactoryPtr(void*, ::Ice::ObjectPtr&);

}

#endif
