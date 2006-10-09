#include <OPII.hpp>
#include <Ice/Ice.h>
#include <basecast.h>
using namespace std;
// implementations for class CheckOptionsI
bool
CheckOptionsI::Initialize(
		  const ::std::string& parmstring			//<STRING|parmstring
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		CheckOptions::Initialize(
		  (char*) parmstring.c_str()		//<STRING|parmstring|RL_1
		);
	return ret;

}

void CheckOptionsI::SetObjectFactory(OPIFactoryIPtr removingfactory){
	factory = removingfactory;
}
// end CheckOptions -------------
::Ice::Int
DBObjectHandleI::BeginTransaction(
		  bool extTA			//<LOGICAL|ext_TA
		, ::Ice::Int wmaxnum			//<INT|w_maxnum
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		DBObjectHandle::BeginTransaction(
		  extTA		//<LOGICAL|ext_TA|RL_direct
		, wmaxnum		//<INT|w_maxnum|RL_direct
		);
	return ret;

}
// implementations for class DBObjectHandleI
bool
DBObjectHandleI::ChangeTimeStamp(
		  ::Ice::Int versionnr			//<UINT|version_nr
		, ::Ice::Long timestamp			//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	)
{

	dttm TCtimestamp;
	TCtimestamp.FromUnix(timestamp);
	bool ret;
	ret=
		DBObjectHandle::ChangeTimeStamp(
		  versionnr		//<UINT|version_nr|RL_direct
		, TCtimestamp		//<dttm|timestamp|RL_direct
		);
	return ret;

}
bool
DBObjectHandleI::CommitTransaction(
		  ::Ice::Int talevel			//<INT|talevel
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::CommitTransaction(
		  talevel		//<INT|talevel|RL_direct
		);
	return ret;

}
::OPI::PropertyHandlePrx
DBObjectHandleI::CreateTempPropertyHandle(
		  const ::OPI::PropertyHandlePrx& prophdlref			//<PropertyHandle|prophdl_ref
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdlref = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdlref).ice_getIdentity()));
	::PropertyHandle *TCprophdlref = &(*TCPprophdlref);
	PropertyHandleIPtr ret;
	::PropertyHandle TR = 
		DBObjectHandle::CreateTempPropertyHandle(
		  (::PropertyHandle&)*TCprophdlref		//<PropertyHandle|prophdl_ref|RL_reference
		);
	ret = new PropertyHandleI(TR);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
DBObjectHandleI::DeleteExtent(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::DeleteExtent(
		  (char*) extnames.c_str()		//<STRING|extnames|RL_1
		);
	return ret;

}
bool
DBObjectHandleI::DeleteExtentRef(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::DeleteExtentRef(
		  (char*) extnames.c_str()		//<STRING|extnames|RL_1
		);
	return ret;

}
void
DBObjectHandleI::DisableEventHandling(
		  const ::Ice::Current& current //< ice default

	)
{

		DBObjectHandle::DisableEventHandling();
}
void
DBObjectHandleI::EnableEventHandling(
		  const ::Ice::Current& current //< ice default

	)
{

		DBObjectHandle::EnableEventHandling();
}
bool
DBObjectHandleI::EventHandling(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::EventHandling();
	return ret;

}
bool
DBObjectHandleI::ExecuteDBObjectAction(
		  const ::std::string& actionname			//<CHAR|action_name
		, const ::std::string& parmstring			//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::ExecuteDBObjectAction(
		  (char*) actionname.c_str()		//<CHAR|action_name|RL_1
		, (char*) parmstring.c_str()		//<STRING|parm_string|RL_1
		);
	return ret;

}
::OPI::PropertyHandlePrx
DBObjectHandleI::ExecuteExpression(
		  const ::OPI::DBObjectHandlePrx& resobhandle			//<DBObjectHandle|res_obhandle
		, const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	::DBObjectHandle *TCresobhandle = dbocast(resobhandle, current);

	PropertyHandleIPtr ret;
	::PropertyHandle TR = 
		DBObjectHandle::ExecuteExpression(
		  (::DBObjectHandle&)*TCresobhandle		//<DBObjectHandle|res_obhandle|RL_reference
		, (char*) expression.c_str()		//<STRING|expression|RL_1
		);
	ret = new PropertyHandleI(TR);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
DBObjectHandleI::ExtentExist(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::ExtentExist(
		  (char*) extnames.c_str()		//<STRING|extnames|RL_1
		);
	return ret;

}
::OPI::PIACC
DBObjectHandleI::GetAccess(
		  const ::Ice::Current& current //< ice default

	)
{

	::OPI::PIACC ret;
	ret=enumcpp2ice((PIACC)
		DBObjectHandle::GetAccess()
	);
	return ret;

}
::std::string
DBObjectHandleI::GetActionResult(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		DBObjectHandle::GetActionResult();
	return ::std::string(ret);

}
::OPI::DatabaseHandlePrx
DBObjectHandleI::GetDBHandle(
		  const ::Ice::Current& current //< ice default

	)
{

	DatabaseHandleIPtr ret;
	ret=new DatabaseHandleI(
		DBObjectHandle::GetDBHandle()
	);

	::OPI::DatabaseHandlePrx prx = OPI::DatabaseHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DatabaseHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::DataSourceHandlePrx
DBObjectHandleI::GetDataSource(
		  const ::Ice::Current& current //< ice default

	)
{

	DataSourceHandleIPtr ret;
	ret=new DataSourceHandleI(/*RL_1*/*
		DBObjectHandle::GetDataSource()
	);

	::OPI::DataSourceHandlePrx prx = OPI::DataSourceHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DataSourceHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::DictionaryHandlePrx
DBObjectHandleI::GetDictionary(
		  const ::Ice::Current& current //< ice default

	)
{

	DictionaryHandleIPtr ret;
	ret=new DictionaryHandleI(
		DBObjectHandle::GetDictionary()
	);

	::OPI::DictionaryHandlePrx prx = OPI::DictionaryHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DictionaryHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::std::string
DBObjectHandleI::GetExtent(
		  ::Ice::Int indx0			//<INT|indx0
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		DBObjectHandle::GetExtent(
		  indx0		//<INT|indx0|RL_direct
		);
	return ::std::string(ret);

}
::OPI::DBObjectHandlePrx
DBObjectHandleI::GetHighObject(
		  const ::Ice::Current& current //< ice default

	)
{

	DBObjectHandleIPtr ret;
	ret=new DBObjectHandleI(
		DBObjectHandle::GetHighObject()
	);

	::OPI::DBObjectHandlePrx prx = OPI::DBObjectHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DBObjectHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::std::string
DBObjectHandleI::GetObject(
		  ::Ice::Int indx0			//<INT|indx0
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		DBObjectHandle::GetObject(
		  indx0		//<INT|indx0|RL_direct
		);
	return ::std::string(ret);

}
::std::string
DBObjectHandleI::GetServerVariable(
		  const ::std::string& varname			//<STRING|var_name
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		DBObjectHandle::GetServerVariable(
		  (char*) varname.c_str()		//<STRING|var_name|RL_1
		);
	return ::std::string(ret);

}
::Ice::Int
DBObjectHandleI::GetSystemVersion(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		DBObjectHandle::GetSystemVersion();
	return ret;

}
::Ice::Long
DBObjectHandleI::GetTimeStamp(
		  ::Ice::Int versionnr			//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	)
{

	dttm ret;
	ret=
		DBObjectHandle::GetTimeStamp(
		  versionnr		//<UINT|version_nr|RL_direct
		);
	return ret.ToUnix();

}
::Ice::Int
DBObjectHandleI::GetTransactionLevel(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		DBObjectHandle::GetTransactionLevel();
	return ret;

}
::Ice::Int
DBObjectHandleI::GetVersion(
		  ::Ice::Long timestamp			//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	)
{

	dttm TCtimestamp;
	TCtimestamp.FromUnix(timestamp);
	int ret;
	ret=
		DBObjectHandle::GetVersion(
		  TCtimestamp		//<dttm|timestamp|RL_direct
		);
	return ret;

}
bool
DBObjectHandleI::IsClient(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::IsClient();
	return ret;

}
bool
DBObjectHandleI::IsEmpty(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::IsEmpty();
	return ret;

}
bool
DBObjectHandleI::IsOpened(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::IsOpened();
	return ret;

}
bool
DBObjectHandleI::IsServer(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::IsServer();
	return ret;

}
bool
DBObjectHandleI::IsValid(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::IsValid();
	return ret;

}
bool
DBObjectHandleI::NewVersion(
		  ::Ice::Long timestamp			//<dttm|timestamp
		, ::Ice::Int versionnr			//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	)
{

	dttm TCtimestamp;
	TCtimestamp.FromUnix(timestamp);
	bool ret;
	ret=
		DBObjectHandle::NewVersion(
		  TCtimestamp		//<dttm|timestamp|RL_direct
		, versionnr		//<UINT|version_nr|RL_direct
		);
	return ret;

}
bool
DBObjectHandleI::OpenObject(
		  const ::OPI::DBObjectHandlePrx& dbobject			//<DBObjectHandle|dbobject
		, const ::std::string& objname			//<CHAR|objname
		, ::OPI::PIACC accopt			//<PIACC|accopt
		, ::Ice::Int versionnr			//<UINT|version_nr
		, ::OPI::ResourceTypes localressources			//<ResourceTypes|local_ressources
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	::DBObjectHandle *TCdbobject = dbocast(dbobject, current);

	bool ret;
	ret=
		DBObjectHandle::OpenObject(
		  (::DBObjectHandle&)*TCdbobject		//<DBObjectHandle|dbobject|RL_reference
		, (char*) objname.c_str()		//<CHAR|objname|RL_1
		, enumice2cpp(accopt)		//<PIACC|accopt|RL_direct
		, versionnr		//<UINT|version_nr|RL_direct
		, enumice2cpp(localressources)		//<ResourceTypes|local_ressources|RL_direct
		);
	return ret;

}
bool
DBObjectHandleI::RollBack(
		  ::Ice::Int talevel			//<INT|talevel
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::RollBack(
		  talevel		//<INT|talevel|RL_direct
		);
	return ret;

}
void
DBObjectHandleI::SetActionResult(
		  const ::std::string& resultstring			//<STRING|result_string
		, const ::Ice::Current& current //< ice default

	)
{

		DBObjectHandle::SetActionResult(
		  (char*) resultstring.c_str()		//<STRING|result_string|RL_1
		);
}
::Ice::Int
DBObjectHandleI::SetOverload(
		  bool overloadopt			//<LOGICAL|overload_opt
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		DBObjectHandle::SetOverload(
		  overloadopt		//<LOGICAL|overload_opt|RL_direct
		);
	return ret;

}
bool
DBObjectHandleI::SetServerVariable(
		  const ::std::string& varname			//<STRING|var_name
		, const ::std::string& varstring			//<STRING|var_string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::SetServerVariable(
		  (char*) varname.c_str()		//<STRING|var_name|RL_1
		, (char*) varstring.c_str()		//<STRING|var_string|RL_1
		);
	return ret;

}
bool
DBObjectHandleI::SetUserDefinedIdentity(
		  bool identityopt			//<LOGICAL|identity_opt
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::SetUserDefinedIdentity(
		  identityopt		//<LOGICAL|identity_opt|RL_direct
		);
	return ret;

}
bool
DBObjectHandleI::SetVersion(
		  ::Ice::Int versionnr			//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DBObjectHandle::SetVersion(
		  versionnr		//<UINT|version_nr|RL_direct
		);
	return ret;

}
bool
DBObjectHandleI::SetVersioni1(
		  ::Ice::Long date			//<dbdt|date
		, const ::Ice::Current& current //< ice default

	)
{

	dbdt TCdate;
	TCdate.FromUnix(date);
	bool ret;
	ret=
		DBObjectHandle::SetVersion(
		  TCdate		//<dbdt|date|RL_direct
		);
	return ret;

}
bool
DBObjectHandleI::SetVersioni2(
		  ::Ice::Long timestamp			//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	)
{

	dttm TCtimestamp;
	TCtimestamp.FromUnix(timestamp);
	bool ret;
	ret=
		DBObjectHandle::SetVersion(
		  TCtimestamp		//<dttm|timestamp|RL_direct
		);
	return ret;

}
::Ice::Int
DBObjectHandleI::VersionCount(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		DBObjectHandle::VersionCount();
	return ret;

}

void DBObjectHandleI::SetObjectFactory(OPIFactoryIPtr removingfactory){
	factory = removingfactory;
}
// end DBObjectHandle -------------
bool
DataSourceHandleI::BeginTransaction(
		  bool extta			//<LOGICAL|ext_ta
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::BeginTransaction(
		  extta		//<LOGICAL|ext_ta|RL_direct
		);
	return ret;

}
// implementations for class DataSourceHandleI
bool
DataSourceHandleI::Close(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::Close();
	return ret;

}
bool
DataSourceHandleI::CloseDBObject(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::CloseDBObject();
	return ret;

}
bool
DataSourceHandleI::CloseDatabase(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::CloseDatabase();
	return ret;

}
bool
DataSourceHandleI::CloseDictionary(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::CloseDictionary();
	return ret;

}
bool
DataSourceHandleI::CloseProperty(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::CloseProperty();
	return ret;

}
bool
DataSourceHandleI::CloseResourceDB(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::CloseResourceDB();
	return ret;

}
bool
DataSourceHandleI::CommitTransaction(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::CommitTransaction();
	return ret;

}
bool
DataSourceHandleI::Connect(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	ODABAClientIPtr TCPpodabaclient = ODABAClientIPtr::dynamicCast(current.adapter->find((*podabaclient).ice_getIdentity()));
	::ODABAClient *TCpodabaclient = &(*TCPpodabaclient);
	bool ret;
	ret=
		DataSourceHandle::Connect(
		  (::ODABAClient&)*TCpodabaclient		//<ODABAClient|odaba_client|RL_reference
		);
	return ret;

}
bool
DataSourceHandleI::Disconnect(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::Disconnect();
	return ret;

}
bool
DataSourceHandleI::Open(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, ::OPI::PIACC accmod			//<PIACC|acc_mod
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	ODABAClientIPtr TCPpodabaclient = ODABAClientIPtr::dynamicCast(current.adapter->find((*podabaclient).ice_getIdentity()));
	::ODABAClient *TCpodabaclient = &(*TCPpodabaclient);
	bool ret;
	ret=
		DataSourceHandle::Open(
		  (::ODABAClient&)*TCpodabaclient		//<ODABAClient|odaba_client|RL_reference
		, enumice2cpp(accmod)		//<PIACC|acc_mod|RL_direct
		);
	return ret;

}
bool
DataSourceHandleI::Openi02(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, const ::std::string& inifile			//<STRING|ini_file
		, const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	ODABAClientIPtr TCPpodabaclient = ODABAClientIPtr::dynamicCast(current.adapter->find((*podabaclient).ice_getIdentity()));
	::ODABAClient *TCpodabaclient = &(*TCPpodabaclient);
	bool ret;
	ret=
		DataSourceHandle::Open(
		  (::ODABAClient&)*TCpodabaclient		//<ODABAClient|odaba_client|RL_reference
		, (char*) inifile.c_str()		//<STRING|ini_file|RL_1
		, (char*) datasourcename.c_str()		//<STRING|datasource_name|RL_1
		);
	return ret;

}
bool
DataSourceHandleI::Openi1(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	ODABAClientIPtr TCPpodabaclient = ODABAClientIPtr::dynamicCast(current.adapter->find((*podabaclient).ice_getIdentity()));
	::ODABAClient *TCpodabaclient = &(*TCPpodabaclient);
	bool ret;
	ret=
		DataSourceHandle::Open(
		  (::ODABAClient&)*TCpodabaclient		//<ODABAClient|odaba_client|RL_reference
		, (char*) datasourcename.c_str()		//<STRING|datasource_name|RL_1
		);
	return ret;

}
::OPI::DBObjectHandlePrx
DataSourceHandleI::OpenDBObject(
		  const ::Ice::Current& current //< ice default

	)
{

	DBObjectHandleIPtr ret;
	ret=new DBObjectHandleI(
		DataSourceHandle::OpenDBObject()
	);

	::OPI::DBObjectHandlePrx prx = OPI::DBObjectHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DBObjectHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::DatabaseHandlePrx
DataSourceHandleI::OpenDatabase(
		  const ::Ice::Current& current //< ice default

	)
{

	DatabaseHandleIPtr ret;
	ret=new DatabaseHandleI(
		DataSourceHandle::OpenDatabase()
	);

	::OPI::DatabaseHandlePrx prx = OPI::DatabaseHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DatabaseHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::DictionaryHandlePrx
DataSourceHandleI::OpenDictionary(
		  ::OPI::PIACC accopt			//<PIACC|accopt
		, const ::Ice::Current& current //< ice default

	)
{

	DictionaryHandleIPtr ret;
	ret=new DictionaryHandleI(
		DataSourceHandle::OpenDictionary(
		  enumice2cpp(accopt)		//<PIACC|accopt|RL_direct
		)
	);

	::OPI::DictionaryHandlePrx prx = OPI::DictionaryHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DictionaryHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::PropertyHandlePrx
DataSourceHandleI::OpenProperty(
		  const ::std::string& extname			//<CHAR|extname
		, const ::Ice::Current& current //< ice default

	)
{

	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(/*RL_1*/*
		DataSourceHandle::OpenProperty(
		  (char*) extname.c_str()		//<CHAR|extname|RL_1
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::DatabaseHandlePrx
DataSourceHandleI::OpenResourceDB(
		  const ::Ice::Current& current //< ice default

	)
{

	DatabaseHandleIPtr ret;
	ret=new DatabaseHandleI(
		DataSourceHandle::OpenResourceDB()
	);

	::OPI::DatabaseHandlePrx prx = OPI::DatabaseHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DatabaseHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
DataSourceHandleI::RollBack(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::RollBack();
	return ret;

}
bool
DataSourceHandleI::SetDBObject(
		  const ::OPI::DBObjectHandlePrx& ohandle			//<DBObjectHandle|ohandle
		, const ::std::string& wobjname			//<STRING|w_objname
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	::DBObjectHandle *TCohandle = dbocast(ohandle, current);

	bool ret;
	ret=
		DataSourceHandle::SetDBObject(
		  (::DBObjectHandle&)*TCohandle		//<DBObjectHandle|ohandle|RL_reference
		, (char*) wobjname.c_str()		//<STRING|w_objname|RL_1
		);
	return ret;

}
bool
DataSourceHandleI::SetDataSource(
		  const ::OPI::DataSourceHandlePrx& dbdefptr			//<DataSourceHandle|dbdefptr
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	DataSourceHandleIPtr TCPdbdefptr = DataSourceHandleIPtr::dynamicCast(current.adapter->find((*dbdefptr).ice_getIdentity()));
	::DataSourceHandle *TCdbdefptr = &(*TCPdbdefptr);
	bool ret;
	ret=
		DataSourceHandle::SetDataSource(
		  (::DataSourceHandle*)TCdbdefptr		//<DataSourceHandle|dbdefptr|RL_1
		);
	return ret;

}
bool
DataSourceHandleI::SetDatabase(
		  const ::OPI::DatabaseHandlePrx& dbhandle			//<DatabaseHandle|db_handle
		, const ::std::string& wbasepath			//<STRING|w_basepath
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	::DatabaseHandle *TCdbhandle = dbhcast(dbhandle, current);

	bool ret;
	ret=
		DataSourceHandle::SetDatabase(
		  (::DatabaseHandle&)*TCdbhandle		//<DatabaseHandle|db_handle|RL_reference
		, (char*) wbasepath.c_str()		//<STRING|w_basepath|RL_1
		);
	return ret;

}
bool
DataSourceHandleI::SetDictionary(
		  const ::OPI::DictionaryHandlePrx& dictptr			//<DictionaryHandle|dictptr
		, const ::std::string& wdictpath			//<STRING|w_dictpath
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	DictionaryHandleIPtr TCPdictptr = DictionaryHandleIPtr::dynamicCast(current.adapter->find((*dictptr).ice_getIdentity()));
	::DictionaryHandle *TCdictptr = &(*TCPdictptr);
	bool ret;
	ret=
		DataSourceHandle::SetDictionary(
		  (::DictionaryHandle&)*TCdictptr		//<DictionaryHandle|dictptr|RL_reference
		, (char*) wdictpath.c_str()		//<STRING|w_dictpath|RL_1
		);
	return ret;

}
bool
DataSourceHandleI::SetResourceDB(
		  const ::OPI::DatabaseHandlePrx& dbhandle			//<DatabaseHandle|db_handle
		, const ::std::string& wbasepath			//<STRING|w_basepath
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	::DatabaseHandle *TCdbhandle = dbhcast(dbhandle, current);

	bool ret;
	ret=
		DataSourceHandle::SetResourceDB(
		  (::DatabaseHandle&)*TCdbhandle		//<DatabaseHandle|db_handle|RL_reference
		, (char*) wbasepath.c_str()		//<STRING|w_basepath|RL_1
		);
	return ret;

}
bool
DataSourceHandleI::SetVariables(
		  const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::SetVariables(
		  (char*) datasourcename.c_str()		//<STRING|datasource_name|RL_1
		);
	return ret;

}
bool
DataSourceHandleI::Setup(
		  const ::std::string& inifile			//<STRING|ini_file
		, const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::Setup(
		  (char*) inifile.c_str()		//<STRING|ini_file|RL_1
		, (char*) datasourcename.c_str()		//<STRING|datasource_name|RL_1
		);
	return ret;

}
bool
DataSourceHandleI::SetupVariables(
		  const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DataSourceHandle::SetupVariables(
		  (char*) datasourcename.c_str()		//<STRING|datasource_name|RL_1
		);
	return ret;

}

void DataSourceHandleI::SetObjectFactory(OPIFactoryIPtr removingfactory){
	factory = removingfactory;
}
// end DataSourceHandle -------------
bool
DatabaseHandleI::ActivateShadowBase(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::ActivateShadowBase();
	return ret;

}
// implementations for class DatabaseHandleI
bool
DatabaseHandleI::BackupDB(
		  const ::std::string& target			//<STRING|target
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::BackupDB(
		  (char*) target.c_str()		//<STRING|target|RL_1
		);
	return ret;

}
bool
DatabaseHandleI::CheckDB(
		  const ::OPI::CheckOptionsPrx& checkopts			//<CheckOptions|check_opts
		, const ::std::string& source			//<STRING|source
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	CheckOptionsIPtr TCPcheckopts = CheckOptionsIPtr::dynamicCast(current.adapter->find((*checkopts).ice_getIdentity()));
	::CheckOptions *TCcheckopts = &(*TCPcheckopts);
	bool ret;
	ret=
		DatabaseHandle::CheckDB(
		  (::CheckOptions)*TCcheckopts		//<CheckOptions|check_opts|RL_direct
		, (char*) source.c_str()		//<STRING|source|RL_1
		);
	return ret;

}
bool
DatabaseHandleI::CheckLicence(
		  const ::std::string& licowner			//<STRING|lic_owner
		, const ::std::string& licnumber			//<CHAR|lic_number
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::CheckLicence(
		  (char*) licowner.c_str()		//<STRING|lic_owner|RL_1
		, (char*) licnumber.c_str()		//<CHAR|lic_number|RL_1
		);
	return ret;

}
bool
DatabaseHandleI::CloseWorkspace(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::CloseWorkspace();
	return ret;

}
bool
DatabaseHandleI::ConsolidateWorkspace(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::ConsolidateWorkspace();
	return ret;

}
bool
DatabaseHandleI::DeactivateShadowBase(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::DeactivateShadowBase();
	return ret;

}
bool
DatabaseHandleI::DeleteWorkspace(
		  const ::std::string& wsnames			//<STRING|ws_names
		, const ::std::string& username			//<STRING|user_name
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::DeleteWorkspace(
		  (char*) wsnames.c_str()		//<STRING|ws_names|RL_1
		, (char*) username.c_str()		//<STRING|user_name|RL_1
		);
	return ret;

}
bool
DatabaseHandleI::DisableWorkspace(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::DisableWorkspace();
	return ret;

}
bool
DatabaseHandleI::DiscardWorkspace(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::DiscardWorkspace();
	return ret;

}
bool
DatabaseHandleI::EnableWorkspace(
		  const ::std::string& sdwpath			//<CHAR|sdw_path
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::EnableWorkspace(
		  (char*) sdwpath.c_str()		//<CHAR|sdw_path|RL_1
		);
	return ret;

}
bool
DatabaseHandleI::ExecuteDatabaseAction(
		  const ::std::string& actionname			//<CHAR|action_name
		, const ::std::string& parmstring			//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::ExecuteDatabaseAction(
		  (char*) actionname.c_str()		//<CHAR|action_name|RL_1
		, (char*) parmstring.c_str()		//<STRING|parm_string|RL_1
		);
	return ret;

}
bool
DatabaseHandleI::ExistWorkspace(
		  const ::std::string& wsnames			//<STRING|ws_names
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::ExistWorkspace(
		  (char*) wsnames.c_str()		//<STRING|ws_names|RL_1
		);
	return ret;

}
::Ice::Int
DatabaseHandleI::GetDatabaseID(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		DatabaseHandle::GetDatabaseID();
	return ret;

}
::std::string
DatabaseHandleI::GetPath(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		DatabaseHandle::GetPath();
	return ::std::string(ret);

}
::Ice::Int
DatabaseHandleI::GetSchemaVersion(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		DatabaseHandle::GetSchemaVersion();
	return ret;

}
::std::string
DatabaseHandleI::GetVersionString(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		DatabaseHandle::GetVersionString();
	return ::std::string(ret);

}
::std::string
DatabaseHandleI::GetWorkspace(
		  const ::std::string& wsroot			//<STRING|ws_root
		, ::Ice::Int wsindex			//<INT|ws_index
		, const ::std::string& username			//<STRING|user_name
		, const ::std::string& wsname			//<STRING|ws_name
		, bool refreshopt			//<LOGICAL|refresh_opt
		, const ::std::string& wsinfo			//<CHAR|ws_info
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		DatabaseHandle::GetWorkspace(
		  (char*) wsroot.c_str()		//<STRING|ws_root|RL_1
		, wsindex		//<INT|ws_index|RL_direct
		, (char*) username.c_str()		//<STRING|user_name|RL_1
		, (char*) wsname.c_str()		//<STRING|ws_name|RL_1
		, refreshopt		//<LOGICAL|refresh_opt|RL_direct
		, (char*) wsinfo.c_str()		//<CHAR|ws_info|RL_1
		);
	return ::std::string(ret);

}
bool
DatabaseHandleI::IgnoreWriteProtect(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::IgnoreWriteProtect();
	return ret;

}
bool
DatabaseHandleI::InitDataArea(
		  ::Ice::Int mbnumber			//<INT|mbnumber
		, ::Ice::Int sbnumber			//<INT|sbnumber
		, ::Ice::Int danumber			//<UINT|danumber
		, const ::std::string& filename			//<STRING|filename
		, ::Ice::Int dasize			//<INT|dasize
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::InitDataArea(
		  mbnumber		//<INT|mbnumber|RL_direct
		, sbnumber		//<INT|sbnumber|RL_direct
		, danumber		//<UINT|danumber|RL_direct
		, (char*) filename.c_str()		//<STRING|filename|RL_1
		, dasize		//<INT|dasize|RL_direct
		);
	return ret;

}
bool
DatabaseHandleI::InitMainBase(
		  ::Ice::Int mbnumber			//<INT|mbnumber
		, const ::std::string& filename			//<STRING|filename
		, ::Ice::Int lowEBN			//<INT|lowEBN
		, ::Ice::Int highEBN			//<INT|highEBN
		, ::Ice::Int dasize			//<INT|dasize
		, bool largedb			//<LOGICAL|largedb
		, bool pindep			//<LOGICAL|pindep
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::InitMainBase(
		  mbnumber		//<INT|mbnumber|RL_direct
		, (char*) filename.c_str()		//<STRING|filename|RL_1
		, lowEBN		//<INT|lowEBN|RL_direct
		, highEBN		//<INT|highEBN|RL_direct
		, dasize		//<INT|dasize|RL_direct
		, largedb		//<LOGICAL|largedb|RL_direct
		, pindep		//<LOGICAL|pindep|RL_direct
		);
	return ret;

}
bool
DatabaseHandleI::InitSubBase(
		  ::Ice::Int mbnumber			//<INT|mbnumber
		, ::Ice::Int sbnumber			//<INT|sbnumber
		, const ::std::string& filename			//<STRING|filename
		, ::Ice::Int dasize			//<INT|dasize
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::InitSubBase(
		  mbnumber		//<INT|mbnumber|RL_direct
		, sbnumber		//<INT|sbnumber|RL_direct
		, (char*) filename.c_str()		//<STRING|filename|RL_1
		, dasize		//<INT|dasize|RL_direct
		);
	return ret;

}
bool
DatabaseHandleI::IsLicenced(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::IsLicenced();
	return ret;

}
bool
DatabaseHandleI::IsShared(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::IsShared();
	return ret;

}
bool
DatabaseHandleI::LocateWorkspace(
		  const ::std::string& wsnames			//<STRING|ws_names
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::LocateWorkspace(
		  (char*) wsnames.c_str()		//<STRING|ws_names|RL_1
		);
	return ret;

}
bool
DatabaseHandleI::OpenDatabase(
		  const ::OPI::DictionaryHandlePrx& dicthandle			//<DictionaryHandle|dict_handle
		, const ::std::string& cpath			//<STRING|cpath
		, ::OPI::PIACC accopt			//<PIACC|accopt
		, bool wnetopt			//<LOGICAL|w_netopt
		, bool onlineversion			//<LOGICAL|online_version
		, ::Ice::Int versionnr			//<UINT|version_nr
		, ::OPI::ResourceTypes localressources			//<ResourceTypes|local_ressources
		, bool sysenv			//<LOGICAL|sysenv
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	DictionaryHandleIPtr TCPdicthandle = DictionaryHandleIPtr::dynamicCast(current.adapter->find((*dicthandle).ice_getIdentity()));
	::DictionaryHandle *TCdicthandle = &(*TCPdicthandle);
	bool ret;
	ret=
		DatabaseHandle::OpenDatabase(
		  (::DictionaryHandle&)*TCdicthandle		//<DictionaryHandle|dict_handle|RL_reference
		, (char*) cpath.c_str()		//<STRING|cpath|RL_1
		, enumice2cpp(accopt)		//<PIACC|accopt|RL_direct
		, wnetopt		//<LOGICAL|w_netopt|RL_direct
		, onlineversion		//<LOGICAL|online_version|RL_direct
		, versionnr		//<UINT|version_nr|RL_direct
		, enumice2cpp(localressources)		//<ResourceTypes|local_ressources|RL_direct
		, sysenv		//<LOGICAL|sysenv|RL_direct
		);
	return ret;

}
bool
DatabaseHandleI::OpenWorkspace(
		  const ::std::string& wsnames			//<STRING|ws_names
		, const ::std::string& username			//<STRING|user_name
		, bool exclusive			//<LOGICAL|exclusive
		, const ::std::string& wspath			//<STRING|ws_path
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::OpenWorkspace(
		  (char*) wsnames.c_str()		//<STRING|ws_names|RL_1
		, (char*) username.c_str()		//<STRING|user_name|RL_1
		, exclusive		//<LOGICAL|exclusive|RL_direct
		, (char*) wspath.c_str()		//<STRING|ws_path|RL_1
		);
	return ret;

}
bool
DatabaseHandleI::RecreateExtent(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::RecreateExtent(
		  (char*) extnames.c_str()		//<STRING|extnames|RL_1
		);
	return ret;

}
bool
DatabaseHandleI::RestoreDB(
		  const ::std::string& source			//<STRING|source
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::RestoreDB(
		  (char*) source.c_str()		//<STRING|source|RL_1
		);
	return ret;

}
bool
DatabaseHandleI::SetupTypeID(
		  ::Ice::Int sid			//<INT|sid
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DatabaseHandle::SetupTypeID(
		  sid		//<INT|sid|RL_direct
		);
	return ret;

}
// end DatabaseHandle -------------
::Ice::Int
DictionaryHandleI::BaseType(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		DictionaryHandle::BaseType(
		  (char*) strnames.c_str()		//<STRING|strnames|RL_1
		);
	return ret;

}
// implementations for class DictionaryHandleI
bool
DictionaryHandleI::CheckExpression(
		  const ::std::string& expression			//<STRING|expression
		, const ::OPI::DBObjectHandlePrx& dbobjhandle			//<DBObjectHandle|dbobj_handle
		, const ::std::string& clsnames			//<STRING|clsnames
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	::DBObjectHandle *TCdbobjhandle = dbocast(dbobjhandle, current);

	bool ret;
	ret=
		DictionaryHandle::CheckExpression(
		  (char*) expression.c_str()		//<STRING|expression|RL_1
		, (::DBObjectHandle&)*TCdbobjhandle		//<DBObjectHandle|dbobj_handle|RL_reference
		, (char*) clsnames.c_str()		//<STRING|clsnames|RL_1
		);
	return ret;

}
bool
DictionaryHandleI::CheckExpressionInClass(
		  const ::OPI::DBObjectHandlePrx& resobj			//<DBObjectHandle|resobj
		, const ::std::string& clsnames			//<STRING|clsnames
		, const ::std::string& exprnames			//<STRING|exprnames
		, const ::std::string& implnames			//<STRING|implnames
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	::DBObjectHandle *TCresobj = dbocast(resobj, current);

	bool ret;
	ret=
		DictionaryHandle::CheckExpression(
		  (::DBObjectHandle&)*TCresobj		//<DBObjectHandle|resobj|RL_reference
		, (char*) clsnames.c_str()		//<STRING|clsnames|RL_1
		, (char*) exprnames.c_str()		//<STRING|exprnames|RL_1
		, (char*) implnames.c_str()		//<STRING|implnames|RL_1
		);
	return ret;

}
bool
DictionaryHandleI::CheckExtentDef(
		  const ::std::string& scopedname			//<STRING|scoped_name
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DictionaryHandle::CheckExtentDef(
		  (char*) scopedname.c_str()		//<STRING|scoped_name|RL_1
		);
	return ret;

}
bool
DictionaryHandleI::CheckValueSet(
		  const ::std::string& scopedname			//<STRING|scoped_name
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DictionaryHandle::CheckValueSet(
		  (char*) scopedname.c_str()		//<STRING|scoped_name|RL_1
		);
	return ret;

}
bool
DictionaryHandleI::CopyCodeset(
		  const ::OPI::DictionaryHandlePrx& srcedicthandle			//<DictionaryHandle|srce_dicthandle
		, const ::std::string& strname			//<CHAR|strname
		, ::Ice::Int namespaceid			//<INT|namespace_id
		, const ::std::string& newnames			//<STRING|newnames
		, ::OPI::PIREPL dbreplace			//<PIREPL|db_replace
		, bool retainSID			//<LOGICAL|retainSID
		, bool retainschemav			//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	DictionaryHandleIPtr TCPsrcedicthandle = DictionaryHandleIPtr::dynamicCast(current.adapter->find((*srcedicthandle).ice_getIdentity()));
	::DictionaryHandle *TCsrcedicthandle = &(*TCPsrcedicthandle);
	bool ret;
	ret=
		DictionaryHandle::CopyCodeset(
		  (::DictionaryHandle&)*TCsrcedicthandle		//<DictionaryHandle|srce_dicthandle|RL_reference
		, (char*) strname.c_str()		//<CHAR|strname|RL_1
		, namespaceid		//<INT|namespace_id|RL_direct
		, (char*) newnames.c_str()		//<STRING|newnames|RL_1
		, enumice2cpp(dbreplace)		//<PIREPL|db_replace|RL_direct
		, retainSID		//<LOGICAL|retainSID|RL_direct
		, retainschemav		//<LOGICAL|retain_schemav|RL_direct
		);
	return ret;

}
bool
DictionaryHandleI::CopyExtentDef(
		  const ::OPI::DictionaryHandlePrx& srcedicthandle			//<DictionaryHandle|srce_dicthandle
		, const ::std::string& extentname			//<STRING|extentname
		, const ::std::string& newnames			//<STRING|newnames
		, const ::std::string& targstruct			//<STRING|targ_struct
		, bool transaction			//<LOGICAL|transaction
		, bool retainschemav			//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	DictionaryHandleIPtr TCPsrcedicthandle = DictionaryHandleIPtr::dynamicCast(current.adapter->find((*srcedicthandle).ice_getIdentity()));
	::DictionaryHandle *TCsrcedicthandle = &(*TCPsrcedicthandle);
	bool ret;
	ret=
		DictionaryHandle::CopyExtentDef(
		  (::DictionaryHandle&)*TCsrcedicthandle		//<DictionaryHandle|srce_dicthandle|RL_reference
		, (char*) extentname.c_str()		//<STRING|extentname|RL_1
		, (char*) newnames.c_str()		//<STRING|newnames|RL_1
		, (char*) targstruct.c_str()		//<STRING|targ_struct|RL_1
		, transaction		//<LOGICAL|transaction|RL_direct
		, retainschemav		//<LOGICAL|retain_schemav|RL_direct
		);
	return ret;

}
bool
DictionaryHandleI::CopyStructure(
		  const ::OPI::DictionaryHandlePrx& srcedicthandle			//<DictionaryHandle|srce_dicthandle
		, const ::std::string& strname			//<CHAR|strname
		, ::Ice::Int namespaceid			//<INT|namespace_id
		, const ::std::string& newnames			//<STRING|newnames
		, const ::std::string& topname			//<CHAR|topname
		, ::OPI::PIREPL dbreplace			//<PIREPL|db_replace
		, bool retainSID			//<LOGICAL|retainSID
		, bool retainschemav			//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	DictionaryHandleIPtr TCPsrcedicthandle = DictionaryHandleIPtr::dynamicCast(current.adapter->find((*srcedicthandle).ice_getIdentity()));
	::DictionaryHandle *TCsrcedicthandle = &(*TCPsrcedicthandle);
	bool ret;
	ret=
		DictionaryHandle::CopyStructure(
		  (::DictionaryHandle&)*TCsrcedicthandle		//<DictionaryHandle|srce_dicthandle|RL_reference
		, (char*) strname.c_str()		//<CHAR|strname|RL_1
		, namespaceid		//<INT|namespace_id|RL_direct
		, (char*) newnames.c_str()		//<STRING|newnames|RL_1
		, (char*) topname.c_str()		//<CHAR|topname|RL_1
		, enumice2cpp(dbreplace)		//<PIREPL|db_replace|RL_direct
		, retainSID		//<LOGICAL|retainSID|RL_direct
		, retainschemav		//<LOGICAL|retain_schemav|RL_direct
		);
	return ret;

}
bool
DictionaryHandleI::CopyType(
		  const ::OPI::DictionaryHandlePrx& srcedicthandle			//<DictionaryHandle|srce_dicthandle
		, const ::std::string& strnames			//<STRING|strnames
		, const ::std::string& newnames			//<STRING|newnames
		, const ::std::string& topname			//<CHAR|topname
		, ::OPI::PIREPL dbreplace			//<PIREPL|db_replace
		, bool retainSID			//<LOGICAL|retainSID
		, bool transaction			//<LOGICAL|transaction
		, bool retainschemav			//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	DictionaryHandleIPtr TCPsrcedicthandle = DictionaryHandleIPtr::dynamicCast(current.adapter->find((*srcedicthandle).ice_getIdentity()));
	::DictionaryHandle *TCsrcedicthandle = &(*TCPsrcedicthandle);
	bool ret;
	ret=
		DictionaryHandle::CopyType(
		  (::DictionaryHandle&)*TCsrcedicthandle		//<DictionaryHandle|srce_dicthandle|RL_reference
		, (char*) strnames.c_str()		//<STRING|strnames|RL_1
		, (char*) newnames.c_str()		//<STRING|newnames|RL_1
		, (char*) topname.c_str()		//<CHAR|topname|RL_1
		, enumice2cpp(dbreplace)		//<PIREPL|db_replace|RL_direct
		, retainSID		//<LOGICAL|retainSID|RL_direct
		, transaction		//<LOGICAL|transaction|RL_direct
		, retainschemav		//<LOGICAL|retain_schemav|RL_direct
		);
	return ret;

}
bool
DictionaryHandleI::CreateEnum(
		  const ::std::string& enumname			//<STRING|enum_name
		, const ::std::string& basetype			//<STRING|basetype
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DictionaryHandle::CreateEnum(
		  (char*) enumname.c_str()		//<STRING|enum_name|RL_1
		, (char*) basetype.c_str()		//<STRING|basetype|RL_1
		);
	return ret;

}
::std::string
DictionaryHandleI::CreateTempExtent(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::std::string& extnamesw			//<STRING|extnames_w
		, const ::std::string& keynamew			//<CHAR|key_name_w
		, const ::std::string& baseextsw			//<STRING|baseexts_w
		, bool weakoptw			//<LOGICAL|weak_opt_w
		, bool ownoptw			//<LOGICAL|own_opt_w
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		DictionaryHandle::CreateTempExtent(
		  (char*) strnames.c_str()		//<STRING|strnames|RL_1
		, (char*) extnamesw.c_str()		//<STRING|extnames_w|RL_1
		, (char*) keynamew.c_str()		//<CHAR|key_name_w|RL_1
		, (char*) baseextsw.c_str()		//<STRING|baseexts_w|RL_1
		, weakoptw		//<LOGICAL|weak_opt_w|RL_direct
		, ownoptw		//<LOGICAL|own_opt_w|RL_direct
		);
	return ::std::string(ret);

}
bool
DictionaryHandleI::DeleteEnum(
		  const ::std::string& enumname			//<STRING|enum_name
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DictionaryHandle::DeleteEnum(
		  (char*) enumname.c_str()		//<STRING|enum_name|RL_1
		);
	return ret;

}
::std::string
DictionaryHandleI::EnumToString(
		  const ::std::string& enumeration			//<STRING|enumeration
		, ::Ice::Int enumval			//<INT|enum_val
		, const ::std::string& pstring			//<STRING|string
		, ::Ice::Int len			//<INT|len
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		DictionaryHandle::EnumToString(
		  (char*) enumeration.c_str()		//<STRING|enumeration|RL_1
		, enumval		//<INT|enum_val|RL_direct
		, (char*) pstring.c_str()		//<STRING|string|RL_1
		, len		//<INT|len|RL_direct
		);
	return ::std::string(ret);

}
::Ice::Int
DictionaryHandleI::GetLastSchemaVersion(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		DictionaryHandle::GetLastSchemaVersion();
	return ret;

}
::std::string
DictionaryHandleI::GetTempName(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		DictionaryHandle::GetTempName(
		  (char*) extnames.c_str()		//<STRING|extnames|RL_1
		);
	return ::std::string(ret);

}
bool
DictionaryHandleI::IsBasicType(
		  const ::std::string& typenames			//<STRING|typenames
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DictionaryHandle::IsBasicType(
		  (char*) typenames.c_str()		//<STRING|typenames|RL_1
		);
	return ret;

}
bool
DictionaryHandleI::OpenDictionary(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, const ::std::string& cpath			//<STRING|cpath
		, ::OPI::PIACC accopt			//<PIACC|accopt
		, bool wnetopt			//<LOGICAL|w_netopt
		, ::Ice::Int versionnr			//<UINT|version_nr
		, ::OPI::ResourceTypes localressources			//<ResourceTypes|local_ressources
		, bool sysenv			//<LOGICAL|sysenv
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	ODABAClientIPtr TCPpodabaclient = ODABAClientIPtr::dynamicCast(current.adapter->find((*podabaclient).ice_getIdentity()));
	::ODABAClient *TCpodabaclient = &(*TCPpodabaclient);
	bool ret;
	ret=
		DictionaryHandle::OpenDictionary(
		  (::ODABAClient&)*TCpodabaclient		//<ODABAClient|odaba_client|RL_reference
		, (char*) cpath.c_str()		//<STRING|cpath|RL_1
		, enumice2cpp(accopt)		//<PIACC|accopt|RL_direct
		, wnetopt		//<LOGICAL|w_netopt|RL_direct
		, versionnr		//<UINT|version_nr|RL_direct
		, enumice2cpp(localressources)		//<ResourceTypes|local_ressources|RL_direct
		, sysenv		//<LOGICAL|sysenv|RL_direct
		);
	return ret;

}
::Ice::Int
DictionaryHandleI::StringToEnum(
		  const ::std::string& enumeration			//<STRING|enumeration
		, const ::std::string& enumstring			//<STRING|enum_string
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		DictionaryHandle::StringToEnum(
		  (char*) enumeration.c_str()		//<STRING|enumeration|RL_1
		, (char*) enumstring.c_str()		//<STRING|enum_string|RL_1
		);
	return ret;

}
bool
DictionaryHandleI::UpdateVersion(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		DictionaryHandle::UpdateVersion();
	return ret;

}
// end DictionaryHandle -------------
void
ODABAClientI::ActivateGUIMessages(
		  const ::Ice::Current& current //< ice default

	)
{

		ODABAClient::ActivateGUIMessages();
}
// implementations for class ODABAClientI
bool
ODABAClientI::BackupDB(
		  const ::std::string& cpath			//<STRING|cpath
		, const ::std::string& target			//<STRING|target
		, ::Ice::Int waitsec			//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::BackupDB(
		  (char*) cpath.c_str()		//<STRING|cpath|RL_1
		, (char*) target.c_str()		//<STRING|target|RL_1
		, waitsec		//<INT|wait_sec|RL_direct
		);
	return ret;

}
bool
ODABAClientI::CheckDB(
		  const ::std::string& dictpath			//<STRING|dict_path
		, const ::std::string& cpath			//<STRING|cpath
		, const ::OPI::CheckOptionsPrx& checkopts			//<CheckOptions|check_opts
		, const ::std::string& source			//<STRING|source
		, ::Ice::Int waitsec			//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	CheckOptionsIPtr TCPcheckopts = CheckOptionsIPtr::dynamicCast(current.adapter->find((*checkopts).ice_getIdentity()));
	::CheckOptions *TCcheckopts = &(*TCPcheckopts);
	bool ret;
	ret=
		ODABAClient::CheckDB(
		  (char*) dictpath.c_str()		//<STRING|dict_path|RL_1
		, (char*) cpath.c_str()		//<STRING|cpath|RL_1
		, (::CheckOptions)*TCcheckopts		//<CheckOptions|check_opts|RL_direct
		, (char*) source.c_str()		//<STRING|source|RL_1
		, waitsec		//<INT|wait_sec|RL_direct
		);
	return ret;

}
bool
ODABAClientI::Close(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::Close();
	return ret;

}
bool
ODABAClientI::Connect(
		  const ::std::string& servername			//<STRING|server_name
		, ::Ice::Int hostport			//<UINT|host_port
		, const ::std::string& cachestring			//<STRING|cache_string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::Connect(
		  (char*) servername.c_str()		//<STRING|server_name|RL_1
		, hostport		//<UINT|host_port|RL_direct
		, (char*) cachestring.c_str()		//<STRING|cache_string|RL_1
		);
	return ret;

}
bool
ODABAClientI::DictDisplay(
		  const ::std::string& dbpath			//<STRING|dbpath
		, const ::std::string& ppath			//<STRING|ppath
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::DictDisplay(
		  (char*) dbpath.c_str()		//<STRING|dbpath|RL_1
		, (char*) ppath.c_str()		//<STRING|ppath|RL_1
		);
	return ret;

}
void
ODABAClientI::Disconnect(
		  const ::Ice::Current& current //< ice default

	)
{

		ODABAClient::Disconnect();
}
bool
ODABAClientI::Exist(
		  const ::std::string& cpath			//<STRING|cpath
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::Exist(
		  (char*) cpath.c_str()		//<STRING|cpath|RL_1
		);
	return ret;

}
::std::string
ODABAClientI::GetDataSource(
		  ::Ice::Int indx0			//<INT|indx0
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		ODABAClient::GetDataSource(
		  indx0		//<INT|indx0|RL_direct
		);
	return ::std::string(ret);

}
::std::string
ODABAClientI::GetHost(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		ODABAClient::GetHost();
	return ::std::string(ret);

}
::Ice::Int
ODABAClientI::GetPort(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		ODABAClient::GetPort();
	return ret;

}
::std::string
ODABAClientI::GetServerVariable(
		  const ::std::string& varname			//<STRING|var_name
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		ODABAClient::GetServerVariable(
		  (char*) varname.c_str()		//<STRING|var_name|RL_1
		);
	return ::std::string(ret);

}
void
ODABAClientI::Initialize(
		  const ::std::string& inipath			//<STRING|inipath
		, const ::std::string& applicationname			//<STRING|application_name
		, const ::std::string& progpath			//<STRING|progpath
		, ::OPI::ApplicationTypes applicationtype			//<ApplicationTypes|application_type
		, bool initservices			//<LOGICAL|init_services
		, const ::Ice::Current& current //< ice default

	)
{

		ODABAClient::Initialize(
		  (char*) inipath.c_str()		//<STRING|inipath|RL_1
		, (char*) applicationname.c_str()		//<STRING|application_name|RL_1
		, (char*) progpath.c_str()		//<STRING|progpath|RL_1
		, enumice2cpp(applicationtype)		//<ApplicationTypes|application_type|RL_direct
		, initservices		//<LOGICAL|init_services|RL_direct
		);
}
bool
ODABAClientI::IsConnected(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::IsConnected();
	return ret;

}
bool
ODABAClientI::KillClient(
		  ::Ice::Int clientid			//<INT|client_id
		, ::Ice::Int waitsec			//<INT|wait_sec
		, bool sendmessage			//<LOGICAL|send_message
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::KillClient(
		  clientid		//<INT|client_id|RL_direct
		, waitsec		//<INT|wait_sec|RL_direct
		, sendmessage		//<LOGICAL|send_message|RL_direct
		);
	return ret;

}
bool
ODABAClientI::Open(
		  const ::std::string& inipath			//<STRING|inipath
		, const ::std::string& applicationname			//<STRING|application_name
		, const ::std::string& progpath			//<STRING|progpath
		, ::OPI::ApplicationTypes applicationtype			//<ApplicationTypes|application_type
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::Open(
		  (char*) inipath.c_str()		//<STRING|inipath|RL_1
		, (char*) applicationname.c_str()		//<STRING|application_name|RL_1
		, (char*) progpath.c_str()		//<STRING|progpath|RL_1
		, enumice2cpp(applicationtype)		//<ApplicationTypes|application_type|RL_direct
		);
	return ret;

}
::OPI::DBObjectHandlePrx
ODABAClientI::OpenDataSource(
		  const ::std::string& datasourcename			//<STRING|datasource_name
		, ::OPI::PIACC accopt			//<PIACC|accopt
		, const ::Ice::Current& current //< ice default

	)
{

	DBObjectHandleIPtr ret;
	ret=new DBObjectHandleI(/*RL_1*/*
		ODABAClient::OpenDataSource(
		  (char*) datasourcename.c_str()		//<STRING|datasource_name|RL_1
		, enumice2cpp(accopt)		//<PIACC|accopt|RL_direct
		)
	);

	::OPI::DBObjectHandlePrx prx = OPI::DBObjectHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DBObjectHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
ODABAClientI::PackDatabase(
		  const ::std::string& cpath			//<STRING|cpath
		, const ::std::string& temppath			//<STRING|temp_path
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::PackDatabase(
		  (char*) cpath.c_str()		//<STRING|cpath|RL_1
		, (char*) temppath.c_str()		//<STRING|temp_path|RL_1
		);
	return ret;

}
bool
ODABAClientI::RestoreDB(
		  const ::std::string& cpath			//<STRING|cpath
		, const ::std::string& source			//<STRING|source
		, ::Ice::Int waitsec			//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::RestoreDB(
		  (char*) cpath.c_str()		//<STRING|cpath|RL_1
		, (char*) source.c_str()		//<STRING|source|RL_1
		, waitsec		//<INT|wait_sec|RL_direct
		);
	return ret;

}
bool
ODABAClientI::SendClientMessage(
		  ::Ice::Int clientid			//<INT|client_id
		, const ::std::string& mtext			//<STRING|mtext
		, const ::std::string& mtitle			//<STRING|mtitle
		, const ::std::string& mtype			//<CHAR|mtype
		, const ::Ice::Current& current //< ice default

	)
{

	char TCmtype = mtype[0];
	bool ret;
	ret=
		ODABAClient::SendClientMessage(
		  clientid		//<INT|client_id|RL_direct
		, (char*) mtext.c_str()		//<STRING|mtext|RL_1
		, (char*) mtitle.c_str()		//<STRING|mtitle|RL_1
		, TCmtype		//<CHAR|mtype|RL_direct
		);
	return ret;

}
bool
ODABAClientI::SetServerVariable(
		  const ::std::string& varname			//<STRING|var_name
		, const ::std::string& varstring			//<STRING|var_string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::SetServerVariable(
		  (char*) varname.c_str()		//<STRING|var_name|RL_1
		, (char*) varstring.c_str()		//<STRING|var_string|RL_1
		);
	return ret;

}
bool
ODABAClientI::ShutDown(
		  const ::std::string& closesystem			//<CHAR|close_system
		, const ::Ice::Current& current //< ice default

	)
{

	char TCclosesystem = closesystem[0];
	bool ret;
	ret=
		ODABAClient::ShutDown(
		  TCclosesystem		//<CHAR|close_system|RL_direct
		);
	return ret;

}
bool
ODABAClientI::StartPause(
		  ::Ice::Int waitsec			//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::StartPause(
		  waitsec		//<INT|wait_sec|RL_direct
		);
	return ret;

}
bool
ODABAClientI::StatDisplay(
		  const ::std::string& dbpath			//<STRING|dbpath
		, const ::std::string& ppath			//<STRING|ppath
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::StatDisplay(
		  (char*) dbpath.c_str()		//<STRING|dbpath|RL_1
		, (char*) ppath.c_str()		//<STRING|ppath|RL_1
		);
	return ret;

}
void
ODABAClientI::StopPause(
		  const ::Ice::Current& current //< ice default

	)
{

		ODABAClient::StopPause();
}
bool
ODABAClientI::SysInfoDisplay(
		  const ::std::string& dbpath			//<STRING|dbpath
		, const ::std::string& ppath			//<STRING|ppath
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		ODABAClient::SysInfoDisplay(
		  (char*) dbpath.c_str()		//<STRING|dbpath|RL_1
		, (char*) ppath.c_str()		//<STRING|ppath|RL_1
		);
	return ret;

}

void ODABAClientI::SetObjectFactory(OPIFactoryIPtr removingfactory){
	factory = removingfactory;
}
// end ODABAClient -------------
bool
OperationHandleI::CheckExpression(
		  const ::OPI::DictionaryHandlePrx& dictptr			//<DictionaryHandle|dictptr
		, const ::std::string& expression			//<STRING|expression
		, const ::OPI::DBObjectHandlePrx& obhandle			//<DBObjectHandle|obhandle
		, const ::std::string& clsnames			//<STRING|clsnames
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	DictionaryHandleIPtr TCPdictptr = DictionaryHandleIPtr::dynamicCast(current.adapter->find((*dictptr).ice_getIdentity()));
	::DictionaryHandle *TCdictptr = &(*TCPdictptr);
	//call parameter proxy cast
	::DBObjectHandle *TCobhandle = dbocast(obhandle, current);

	bool ret;
	ret=
		OperationHandle::CheckExpression(
		  (::DictionaryHandle&)*TCdictptr		//<DictionaryHandle|dictptr|RL_reference
		, (char*) expression.c_str()		//<STRING|expression|RL_1
		, (::DBObjectHandle&)*TCobhandle		//<DBObjectHandle|obhandle|RL_reference
		, (char*) clsnames.c_str()		//<STRING|clsnames|RL_1
		);
	return ret;

}
bool
OperationHandleI::CheckExpressionInClass(
		  const ::OPI::DictionaryHandlePrx& dictptr			//<DictionaryHandle|dictptr
		, const ::OPI::DBObjectHandlePrx& resobj			//<DBObjectHandle|resobj
		, const ::std::string& clsnames			//<STRING|clsnames
		, const ::std::string& exprnames			//<STRING|exprnames
		, const ::std::string& impnames			//<STRING|impnames
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	DictionaryHandleIPtr TCPdictptr = DictionaryHandleIPtr::dynamicCast(current.adapter->find((*dictptr).ice_getIdentity()));
	::DictionaryHandle *TCdictptr = &(*TCPdictptr);
	//call parameter proxy cast
	::DBObjectHandle *TCresobj = dbocast(resobj, current);

	bool ret;
	ret=
		OperationHandle::CheckExpression(
		  (::DictionaryHandle&)*TCdictptr		//<DictionaryHandle|dictptr|RL_reference
		, (::DBObjectHandle&)*TCresobj		//<DBObjectHandle|resobj|RL_reference
		, (char*) clsnames.c_str()		//<STRING|clsnames|RL_1
		, (char*) exprnames.c_str()		//<STRING|exprnames|RL_1
		, (char*) impnames.c_str()		//<STRING|impnames|RL_1
		);
	return ret;

}
// implementations for class OperationHandleI
bool
OperationHandleI::Execute(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		OperationHandle::Execute();
	return ret;

}
::OPI::PropertyHandlePrx
OperationHandleI::GetResult(
		  const ::Ice::Current& current //< ice default

	)
{

	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		OperationHandle::GetResult()
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::Ice::Int
OperationHandleI::GetSize(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		OperationHandle::GetSize();
	return ret;

}
bool
OperationHandleI::IsValid(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		OperationHandle::IsValid();
	return ret;

}
bool
OperationHandleI::Open(
		  const ::OPI::PropertyHandlePrx& prophdlref			//<PropertyHandle|prophdl_ref
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdlref = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdlref).ice_getIdentity()));
	::PropertyHandle *TCprophdlref = &(*TCPprophdlref);
	bool ret;
	ret=
		OperationHandle::Open(
		  (::PropertyHandle&)*TCprophdlref		//<PropertyHandle|prophdl_ref|RL_reference
		);
	return ret;

}
bool
OperationHandleI::ProvideExpression(
		  const ::OPI::DictionaryHandlePrx& pdictionary			//<DictionaryHandle|dictionary
		, const ::OPI::DBObjectHandlePrx& resobj			//<DBObjectHandle|resobj
		, const ::OPI::DBObjectHandlePrx& obhandle			//<DBObjectHandle|obhandle
		, const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	DictionaryHandleIPtr TCPpdictionary = DictionaryHandleIPtr::dynamicCast(current.adapter->find((*pdictionary).ice_getIdentity()));
	::DictionaryHandle *TCpdictionary = &(*TCPpdictionary);
	//call parameter proxy cast
	::DBObjectHandle *TCresobj = dbocast(resobj, current);

	//call parameter proxy cast
	::DBObjectHandle *TCobhandle = dbocast(obhandle, current);

	bool ret;
	ret=
		OperationHandle::ProvideExpression(
		  (::DictionaryHandle&)*TCpdictionary		//<DictionaryHandle|dictionary|RL_reference
		, (::DBObjectHandle&)*TCresobj		//<DBObjectHandle|resobj|RL_reference
		, (::DBObjectHandle&)*TCobhandle		//<DBObjectHandle|obhandle|RL_reference
		, (char*) expression.c_str()		//<STRING|expression|RL_1
		);
	return ret;

}

void OperationHandleI::SetObjectFactory(OPIFactoryIPtr removingfactory){
	factory = removingfactory;
}
// end OperationHandle -------------
bool
PropertyHandleI::Add(
		  ::Ice::Int setpos0			//<INT|set_pos0
		, const ::std::string& sortkey			//<Key|sortkey
		, const ::std::string& identkeyw			//<Key|identkey_w
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Add(
		  setpos0		//<INT|set_pos0|RL_direct
		, (char*) sortkey.c_str()		//<Key|sortkey|RL_direct
		, (char*) identkeyw.c_str()		//<Key|identkey_w|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::AddByKey(
		  const ::std::string& sortkey			//<Key|sortkey
		, const ::std::string& identkeyw			//<Key|identkey_w
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Add(
		  (char*) sortkey.c_str()		//<Key|sortkey|RL_direct
		, (char*) identkeyw.c_str()		//<Key|identkey_w|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::AddInstance(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	bool ret;
	ret=
		PropertyHandle::Add(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prop_hdl|RL_reference
		);
	return ret;

}
bool
PropertyHandleI::AddOnPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, bool initinst			//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Add(
		  setpos0w		//<INT|set_pos0_w|RL_direct
		, initinst		//<LOGICAL|init_inst|RL_direct
		);
	return ret;

}
// implementations for class PropertyHandleI
bool
PropertyHandleI::AddGlobal(
		  ::Ice::Int setpos0			//<INT|set_pos0
		, const ::std::string& sortkey			//<Key|sortkey
		, const ::std::string& identkeyw			//<Key|identkey_w
		, bool initinst			//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::AddGlobal(
		  setpos0		//<INT|set_pos0|RL_direct
		, (char*) sortkey.c_str()		//<Key|sortkey|RL_direct
		, (char*) identkeyw.c_str()		//<Key|identkey_w|RL_direct
		, initinst		//<LOGICAL|init_inst|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::AddGlobalByKey(
		  const ::std::string& sortkey			//<Key|sortkey
		, const ::std::string& identkeyw			//<Key|identkey_w
		, bool initinst			//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::AddGlobal(
		  (char*) sortkey.c_str()		//<Key|sortkey|RL_direct
		, (char*) identkeyw.c_str()		//<Key|identkey_w|RL_direct
		, initinst		//<LOGICAL|init_inst|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::AddGlobalOnPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, bool initinst			//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::AddGlobal(
		  setpos0w		//<INT|set_pos0_w|RL_direct
		, initinst		//<LOGICAL|init_inst|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::AddReference(
		  const ::OPI::PropertyHandlePrx& sourcehandle			//<PropertyHandle|source_handle
		, ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPsourcehandle = PropertyHandleIPtr::dynamicCast(current.adapter->find((*sourcehandle).ice_getIdentity()));
	::PropertyHandle *TCsourcehandle = &(*TCPsourcehandle);
	bool ret;
	ret=
		PropertyHandle::AddReference(
		  (::PropertyHandle&)*TCsourcehandle		//<PropertyHandle|source_handle|RL_reference
		, setpos0w		//<INT|set_pos0_w|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::AllocDescription(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::AllocDescription();
	return ret;

}
bool
PropertyHandleI::AllocateArea(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::AllocateArea();
	return ret;

}
bool
PropertyHandleI::AppendString(
		  const ::std::string& pstring			//<STRING|string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::AppendString(
		  (char*) pstring.c_str()		//<STRING|string|RL_1
		);
	return ret;

}
bool
PropertyHandleI::AutoLocate(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{

	char TCchkopt = chkopt[0];
	bool ret;
	ret=
		PropertyHandle::AutoLocate(
		  TCchkopt		//<CHAR|chkopt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::Cancel(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Cancel();
	return ret;

}
bool
PropertyHandleI::CancelBuffer(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::CancelBuffer();
	return ret;

}
::Ice::Int
PropertyHandleI::ChangeBuffer(
		  ::Ice::Int buffnum			//<INT|buffnum
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::ChangeBuffer(
		  buffnum		//<INT|buffnum|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::ChangeCache(
		  ::Ice::Int buffnum			//<INT|buffnum
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ChangeCache(
		  buffnum		//<INT|buffnum|RL_direct
		);
	return ret;

}
::OPI::PIACC
PropertyHandleI::ChangeMode(
		  ::OPI::PIACC newmode			//<PIACC|newmode
		, const ::Ice::Current& current //< ice default

	)
{

	::OPI::PIACC ret;
	ret=enumcpp2ice((PIACC)
		PropertyHandle::ChangeMode(
		  enumice2cpp(newmode)		//<PIACC|newmode|RL_direct
		)
	);
	return ret;

}
bool
PropertyHandleI::Check(
		  bool iniopt			//<LOGICAL|ini_opt
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Check(
		  iniopt		//<LOGICAL|ini_opt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::CheckPosition(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::CheckPosition();
	return ret;

}
bool
PropertyHandleI::CheckUpdate(
		  bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::CheckUpdate(
		  pcheckupdate		//<LOGICAL|check_update|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::CheckWProtect(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::CheckWProtect();
	return ret;

}
bool
PropertyHandleI::Close(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Close();
	return ret;

}
::Ice::Int
PropertyHandleI::Compare(
		  const ::OPI::PropertyHandlePrx& cprophdl			//<PropertyHandle|cprop_hdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPcprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*cprophdl).ice_getIdentity()));
	::PropertyHandle *TCcprophdl = &(*TCPcprophdl);
	int ret;
	ret=
		PropertyHandle::Compare(
		  (::PropertyHandle&)*TCcprophdl		//<PropertyHandle|cprop_hdl|RL_reference
		);
	return ret;

}
::Ice::Int
PropertyHandleI::CompareDate(
		  ::Ice::Long dateval			//<dbdt|date_val
		, const ::Ice::Current& current //< ice default

	)
{

	dbdt TCdateval;
	TCdateval.FromUnix(dateval);
	int ret;
	ret=
		PropertyHandle::Compare(
		  TCdateval		//<dbdt|date_val|RL_direct
		);
	return ret;

}
::Ice::Int
PropertyHandleI::CompareFloat(
		  ::Ice::Float doubleval			//<REAL|double_val
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::Compare(
		  doubleval		//<REAL|double_val|RL_direct
		);
	return ret;

}
::Ice::Int
PropertyHandleI::CompareInteger(
		  ::Ice::Int longval			//<INT|long_val
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::Compare(
		  longval		//<INT|long_val|RL_direct
		);
	return ret;

}
::Ice::Int
PropertyHandleI::CompareString(
		  const ::std::string& pstring			//<STRING|string
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::Compare(
		  (char*) pstring.c_str()		//<STRING|string|RL_1
		);
	return ret;

}
::Ice::Int
PropertyHandleI::CompareTime(
		  ::Ice::Long timeval			//<dbtm|time_val
		, const ::Ice::Current& current //< ice default

	)
{

	dbtm TCtimeval;
	TCtimeval.FromUnix(timeval);
	int ret;
	ret=
		PropertyHandle::Compare(
		  TCtimeval		//<dbtm|time_val|RL_direct
		);
	return ret;

}
::Ice::Int
PropertyHandleI::CompareKey(
		  const ::std::string& identkey1			//<Key|ident_key1
		, const ::std::string& identkey2			//<Key|ident_key2
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::CompareKey(
		  (char*) identkey1.c_str()		//<Key|ident_key1|RL_direct
		, (char*) identkey2.c_str()		//<Key|ident_key2|RL_direct
		);
	return ret;

}
::Ice::Int
PropertyHandleI::CompareSortKey(
		  const ::std::string& sortkey1			//<Key|sort_key1
		, const ::std::string& sortkey2			//<Key|sort_key2
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::CompareSortKey(
		  (char*) sortkey1.c_str()		//<Key|sort_key1|RL_direct
		, (char*) sortkey2.c_str()		//<Key|sort_key2|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::CompareType(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, bool convert			//<LOGICAL|convert
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	bool ret;
	ret=
		PropertyHandle::CompareType(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prop_hdl|RL_reference
		, convert		//<LOGICAL|convert|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::Copy(
		  const ::OPI::PropertyHandlePrx& sourcehandle			//<PropertyHandle|source_handle
		, const ::std::string& newkey			//<Key|new_key
		, ::Ice::Int setpos0			//<INT|set_pos0
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, ::OPI::PIREPL copytype			//<PIREPL|copy_type
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPsourcehandle = PropertyHandleIPtr::dynamicCast(current.adapter->find((*sourcehandle).ice_getIdentity()));
	::PropertyHandle *TCsourcehandle = &(*TCPsourcehandle);
	bool ret;
	ret=
		PropertyHandle::Copy(
		  (::PropertyHandle&)*TCsourcehandle		//<PropertyHandle|source_handle|RL_reference
		, (char*) newkey.c_str()		//<Key|new_key|RL_direct
		, setpos0		//<INT|set_pos0|RL_direct
		, enumice2cpp(replopt)		//<PIREPL|replopt|RL_direct
		, enumice2cpp(copytype)		//<PIREPL|copy_type|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::CopyData(
		  const ::OPI::PropertyHandlePrx& sourcehandle			//<PropertyHandle|source_handle
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPsourcehandle = PropertyHandleIPtr::dynamicCast(current.adapter->find((*sourcehandle).ice_getIdentity()));
	::PropertyHandle *TCsourcehandle = &(*TCPsourcehandle);
	bool ret;
	ret=
		PropertyHandle::CopyData(
		  (::PropertyHandle&)*TCsourcehandle		//<PropertyHandle|source_handle|RL_reference
		, enumice2cpp(replopt)		//<PIREPL|replopt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::CopyHandle(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	bool ret;
	ret=
		PropertyHandle::CopyHandle(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prop_hdl|RL_reference
		);
	return ret;

}
bool
PropertyHandleI::CopyInstanceArea(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prophdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	bool ret;
	ret=
		PropertyHandle::CopyInstanceArea(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prophdl|RL_reference
		);
	return ret;

}
::Ice::Int
PropertyHandleI::CopySet(
		  const ::OPI::PropertyHandlePrx& csourcehandle			//<PropertyHandle|csource_handle
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, ::OPI::PIREPL copytype			//<PIREPL|copy_type
		, bool inversecheck			//<LOGICAL|inverse_check
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPcsourcehandle = PropertyHandleIPtr::dynamicCast(current.adapter->find((*csourcehandle).ice_getIdentity()));
	::PropertyHandle *TCcsourcehandle = &(*TCPcsourcehandle);
	int ret;
	ret=
		PropertyHandle::CopySet(
		  (::PropertyHandle&)*TCcsourcehandle		//<PropertyHandle|csource_handle|RL_reference
		, enumice2cpp(replopt)		//<PIREPL|replopt|RL_direct
		, enumice2cpp(copytype)		//<PIREPL|copy_type|RL_direct
		, inversecheck		//<LOGICAL|inverse_check|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::CreateTempExtent(
		  const ::OPI::PropertyHandlePrx& prophdlref			//<PropertyHandle|prophdl_ref
		, const ::std::string& extnamesw			//<STRING|extnames_w
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdlref = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdlref).ice_getIdentity()));
	::PropertyHandle *TCprophdlref = &(*TCPprophdlref);
	bool ret;
	ret=
		PropertyHandle::CreateTempExtent(
		  (::PropertyHandle&)*TCprophdlref		//<PropertyHandle|prophdl_ref|RL_reference
		, (char*) extnamesw.c_str()		//<STRING|extnames_w|RL_1
		);
	return ret;

}
bool
PropertyHandleI::Delete(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	bool ret;
	ret=
		PropertyHandle::Delete(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prop_hdl|RL_reference
		);
	return ret;

}
bool
PropertyHandleI::DeleteByKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Delete(
		  (char*) sortkey.c_str()		//<Key|sort_key|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::DeleteOnPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, bool deldep			//<LOGICAL|del_dep
		, bool delinst			//<LOGICAL|del_inst
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Delete(
		  setpos0w		//<INT|set_pos0_w|RL_direct
		, deldep		//<LOGICAL|del_dep|RL_direct
		, delinst		//<LOGICAL|del_inst|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::DeleteIndexEntry(
		  ::Ice::Int setpos0			//<INT|set_pos0
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::DeleteIndexEntry(
		  setpos0		//<INT|set_pos0|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::DeleteSet(
		  bool deldep			//<LOGICAL|del_dep
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::DeleteSet(
		  deldep		//<LOGICAL|del_dep|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::DisableKeyCheck(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::DisableKeyCheck();
	return ret;

}
bool
PropertyHandleI::Duplicate(
		  ::Ice::Int setpos0			//<INT|set_pos0
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Duplicate(
		  setpos0		//<INT|set_pos0|RL_direct
		, enumice2cpp(replopt)		//<PIREPL|replopt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::DuplicateKey(
		  const ::std::string& identkey			//<Key|ident_key
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Duplicate(
		  (char*) identkey.c_str()		//<Key|ident_key|RL_direct
		, enumice2cpp(replopt)		//<PIREPL|replopt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::EnableKeyCheck(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::EnableKeyCheck();
	return ret;

}
bool
PropertyHandleI::Execute(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Execute();
	return ret;

}
::OPI::PropertyHandlePrx
PropertyHandleI::ExecuteExpression(
		  const ::OPI::DBObjectHandlePrx& resobhandle			//<DBObjectHandle|res_obhandle
		, const ::OPI::DBObjectHandlePrx& obhandle			//<DBObjectHandle|obhandle
		, const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	::DBObjectHandle *TCresobhandle = dbocast(resobhandle, current);

	//call parameter proxy cast
	::DBObjectHandle *TCobhandle = dbocast(obhandle, current);

	PropertyHandleIPtr ret;
	::PropertyHandle TR = 
		PropertyHandle::ExecuteExpression(
		  (::DBObjectHandle&)*TCresobhandle		//<DBObjectHandle|res_obhandle|RL_reference
		, (::DBObjectHandle&)*TCobhandle		//<DBObjectHandle|obhandle|RL_reference
		, (char*) expression.c_str()		//<STRING|expression|RL_1
		);
	ret = new PropertyHandleI(TR);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
PropertyHandleI::ExecuteInstanceAction(
		  const ::std::string& actionname			//<CHAR|action_name
		, const ::std::string& parmstring			//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ExecuteInstanceAction(
		  (char*) actionname.c_str()		//<CHAR|action_name|RL_1
		, (char*) parmstring.c_str()		//<STRING|parm_string|RL_1
		);
	return ret;

}
bool
PropertyHandleI::ExecutePropertyAction(
		  const ::std::string& actionname			//<CHAR|action_name
		, const ::std::string& parmstring			//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ExecutePropertyAction(
		  (char*) actionname.c_str()		//<CHAR|action_name|RL_1
		, (char*) parmstring.c_str()		//<STRING|parm_string|RL_1
		);
	return ret;

}
bool
PropertyHandleI::Exist(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Exist();
	return ret;

}
::std::string
PropertyHandleI::ExtractKey(
		  const ::std::string& keyname			//<STRING|key_name
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::ExtractKey(
		  (char*) keyname.c_str()		//<STRING|key_name|RL_1
		);
	return ::std::string(ret);

}
::std::string
PropertyHandleI::ExtractSortKey(
		  const ::std::string& sortkeyw			//<Key|sort_key_w
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::ExtractSortKey(
		  (char*) sortkeyw.c_str()		//<Key|sort_key_w|RL_direct
		);
	return ::std::string(ret);

}
::std::string
PropertyHandleI::FirstKey(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::FirstKey();
	return ::std::string(ret);

}
bool
PropertyHandleI::Get(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	bool ret;
	ret=
		PropertyHandle::Get(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prop_hdl|RL_reference
		);
	return ret;

}
bool
PropertyHandleI::GetAtPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Get(
		  setpos0w		//<INT|set_pos0_w|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::GetByKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Get(
		  (char*) sortkey.c_str()		//<Key|sort_key|RL_direct
		);
	return ret;

}
::std::string
PropertyHandleI::GetActionResult(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetActionResult();
	return ::std::string(ret);

}
::std::string
PropertyHandleI::GetArea(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{

	char TCchkopt = chkopt[0];
	char* ret;
	ret=
		PropertyHandle::GetArea(
		  TCchkopt		//<CHAR|chkopt|RL_direct
		);
	return ::std::string(ret);

}
::std::string
PropertyHandleI::GetAttribute(
		  ::Ice::Int indx0			//<INT|indx0
		, bool fullpath			//<LOGICAL|full_path
		, bool generic			//<LOGICAL|generic
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetAttribute(
		  indx0		//<INT|indx0|RL_direct
		, fullpath		//<LOGICAL|full_path|RL_direct
		, generic		//<LOGICAL|generic|RL_direct
		);
	return ::std::string(ret);

}
::OPI::PropertyHandlePrx
PropertyHandleI::GetBaseProperty(
		  const ::Ice::Current& current //< ice default

	)
{

	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(/*RL_1*/*
		PropertyHandle::GetBaseProperty()
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::Ice::Int
PropertyHandleI::GetCollectionID(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetCollectionID();
	return ret;

}
::OPI::PropertyHandlePrx
PropertyHandleI::GetCollectionProperty(
		  const ::Ice::Current& current //< ice default

	)
{

	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(/*RL_1*/*
		PropertyHandle::GetCollectionProperty()
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::Ice::Int
PropertyHandleI::GetCount(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetCount();
	return ret;

}
::Ice::Int
PropertyHandleI::GetCurrentIndex(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetCurrentIndex();
	return ret;

}
::Ice::Int
PropertyHandleI::GetCurrentSize(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetCurrentSize();
	return ret;

}
::std::string
PropertyHandleI::GetCurrentType(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetCurrentType();
	return ::std::string(ret);

}
::OPI::DatabaseHandlePrx
PropertyHandleI::GetDBHandle(
		  const ::Ice::Current& current //< ice default

	)
{

	DatabaseHandleIPtr ret;
	ret=new DatabaseHandleI(
		PropertyHandle::GetDBHandle()
	);

	::OPI::DatabaseHandlePrx prx = OPI::DatabaseHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DatabaseHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::Ice::Long
PropertyHandleI::GetDate(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	dbdt ret;
	ret=
		PropertyHandle::GetDate(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret.ToUnix();

}
::Ice::Long
PropertyHandleI::GetDateTime(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	dttm ret;
	ret=
		PropertyHandle::GetDateTime(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret.ToUnix();

}
::Ice::Int
PropertyHandleI::GetDay(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetDay(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
::OPI::DictionaryHandlePrx
PropertyHandleI::GetDictionary(
		  const ::Ice::Current& current //< ice default

	)
{

	DictionaryHandleIPtr ret;
	ret=new DictionaryHandleI(
		PropertyHandle::GetDictionary()
	);

	::OPI::DictionaryHandlePrx prx = OPI::DictionaryHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DictionaryHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::Ice::Int
PropertyHandleI::GetDimension(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetDimension();
	return ret;

}
::Ice::Float
PropertyHandleI::GetDouble(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	float ret;
	ret=
		PropertyHandle::GetDouble(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
::Ice::Int
PropertyHandleI::GetExtInstModCount(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetExtInstModCount();
	return ret;

}
::std::string
PropertyHandleI::GetExtentName(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetExtentName();
	return ::std::string(ret);

}
::std::string
PropertyHandleI::GetGUID(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetGUID();
	return ::std::string(ret);

}
::Ice::Int
PropertyHandleI::GetGenAttrType(
		  const ::std::string& wpropnames			//<STRING|w_propnames
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetGenAttrType(
		  (char*) wpropnames.c_str()		//<STRING|w_propnames|RL_1
		);
	return ret;

}
::Ice::Int
PropertyHandleI::GetGenOrderType(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetGenOrderType();
	return ret;

}
::Ice::Int
PropertyHandleI::GetGlobalID(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetGlobalID();
	return ret;

}
::Ice::Int
PropertyHandleI::GetHours(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetHours(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
::Ice::Int
PropertyHandleI::GetID(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetID(
		  setpos0w		//<INT|set_pos0_w|RL_direct
		);
	return ret;

}
::std::string
PropertyHandleI::GetIdentity(
		  const ::std::string& idstring			//<STRING|id_string
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetIdentity(
		  (char*) idstring.c_str()		//<STRING|id_string|RL_1
		);
	return ::std::string(ret);

}
::std::string
PropertyHandleI::GetIndexName(
		  ::Ice::Int indx0			//<INT|indx0
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetIndexName(
		  indx0		//<INT|indx0|RL_direct
		);
	return ::std::string(ret);

}
bool
PropertyHandleI::GetInitInstance(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::GetInitInstance();
	return ret;

}
::Ice::Int
PropertyHandleI::GetInstModCount(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetInstModCount();
	return ret;

}
::Ice::Int
PropertyHandleI::GetInt(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetInt(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
::Ice::Int
PropertyHandleI::GetIntValue(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetIntValue(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
::std::string
PropertyHandleI::GetKey(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetKey(
		  setpos0w		//<INT|set_pos0_w|RL_direct
		);
	return ::std::string(ret);

}
::Ice::Int
PropertyHandleI::GetKeyLength(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetKeyLength();
	return ret;

}
::Ice::Int
PropertyHandleI::GetLOID(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetLOID(
		  setpos0w		//<INT|set_pos0_w|RL_direct
		);
	return ret;

}
::Ice::Int
PropertyHandleI::GetLOIDByKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetLOID(
		  (char*) sortkey.c_str()		//<Key|sort_key|RL_direct
		);
	return ret;

}
::Ice::Int
PropertyHandleI::GetMinutes(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetMinutes(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
::OPI::PIACC
PropertyHandleI::GetMode(
		  const ::Ice::Current& current //< ice default

	)
{

	::OPI::PIACC ret;
	ret=enumcpp2ice((PIACC)
		PropertyHandle::GetMode()
	);
	return ret;

}
::Ice::Int
PropertyHandleI::GetMonth(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetMonth(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
::Ice::Int
PropertyHandleI::GetNormalized(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetNormalized();
	return ret;

}
::OPI::DBObjectHandlePrx
PropertyHandleI::GetObjectHandle(
		  const ::Ice::Current& current //< ice default

	)
{

	DBObjectHandleIPtr ret;
	ret=new DBObjectHandleI(
		PropertyHandle::GetObjectHandle()
	);

	::OPI::DBObjectHandlePrx prx = OPI::DBObjectHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->DBObjectHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::Ice::Int
PropertyHandleI::GetOrigin(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetOrigin();
	return ret;

}
::OPI::PropertyHandlePrx
PropertyHandleI::GetParentProperty(
		  const ::Ice::Current& current //< ice default

	)
{

	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(/*RL_1*/*
		PropertyHandle::GetParentProperty()
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::PropertyHandlePrx
PropertyHandleI::GetPropertyHandle(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(/*RL_1*/*
		PropertyHandle::GetPropertyHandle(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::std::string
PropertyHandleI::GetPropertyPath(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetPropertyPath();
	return ::std::string(ret);

}
::Ice::Int
PropertyHandleI::GetRefModCount(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetRefModCount();
	return ret;

}
::std::string
PropertyHandleI::GetReference(
		  ::Ice::Int indx0			//<INT|indx0
		, bool fullpath			//<LOGICAL|full_path
		, bool generic			//<LOGICAL|generic
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetReference(
		  indx0		//<INT|indx0|RL_direct
		, fullpath		//<LOGICAL|full_path|RL_direct
		, generic		//<LOGICAL|generic|RL_direct
		);
	return ::std::string(ret);

}
bool
PropertyHandleI::GetRelative(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::GetRelative(
		  setpos0w		//<INT|set_pos0_w|RL_direct
		);
	return ret;

}
::Ice::Int
PropertyHandleI::GetRelativeCount(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetRelativeCount();
	return ret;

}
::Ice::Int
PropertyHandleI::GetRelativeIndex(
		  bool lastopt			//<LOGICAL|last_opt
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetRelativeIndex(
		  lastopt		//<LOGICAL|last_opt|RL_direct
		);
	return ret;

}
::Ice::Int
PropertyHandleI::GetSeconds(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetSeconds(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
::std::string
PropertyHandleI::GetSelectedKey(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetSelectedKey();
	return ::std::string(ret);

}
::Ice::Int
PropertyHandleI::GetSize(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetSize();
	return ret;

}
::Ice::Int
PropertyHandleI::GetSizeOf(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetSizeOf();
	return ret;

}
::std::string
PropertyHandleI::GetSortKey(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetSortKey();
	return ::std::string(ret);

}
::Ice::Int
PropertyHandleI::GetSortKeyLength(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetSortKeyLength();
	return ret;

}
::std::string
PropertyHandleI::GetString(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetString(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ::std::string(ret);

}
::Ice::Int
PropertyHandleI::GetStringLength(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetStringLength();
	return ret;

}
::std::string
PropertyHandleI::GetStringValue(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetStringValue(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ::std::string(ret);

}
::std::string
PropertyHandleI::GetSubString(
		  ::Ice::Int startpos			//<INT|start_pos
		, ::Ice::Int length			//<INT|length
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetSubString(
		  startpos		//<INT|start_pos|RL_direct
		, length		//<INT|length|RL_direct
		);
	return ::std::string(ret);

}
::std::string
PropertyHandleI::GetText(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetText(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ::std::string(ret);

}
::Ice::Long
PropertyHandleI::GetTime(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	dbtm ret;
	ret=
		PropertyHandle::GetTime(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret.ToUnix();

}
::std::string
PropertyHandleI::GetType(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::GetType();
	return ::std::string(ret);

}
bool
PropertyHandleI::GetValid(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::GetValid();
	return ret;

}
::Ice::Int
PropertyHandleI::GetVersion(
		  const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetVersion();
	return ret;

}
::Ice::Int
PropertyHandleI::GetYear(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::GetYear(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
::OPI::PropertyHandlePrx
PropertyHandleI::Group(
		  const ::OPI::PropertyHandlePrx& prophdlref			//<PropertyHandle|prophdl_ref
		, const ::std::string& groupingrule			//<STRING|grouping_rule
		, bool distinct			//<LOGICAL|distinct
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdlref = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdlref).ice_getIdentity()));
	::PropertyHandle *TCprophdlref = &(*TCPprophdlref);
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::Group(
		  (::PropertyHandle&)*TCprophdlref		//<PropertyHandle|prophdl_ref|RL_reference
		, (char*) groupingrule.c_str()		//<STRING|grouping_rule|RL_1
		, distinct		//<LOGICAL|distinct|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
PropertyHandleI::HasData(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::HasData();
	return ret;

}
bool
PropertyHandleI::HasDescription(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::HasDescription();
	return ret;

}
bool
PropertyHandleI::HasGenericAttributes(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::HasGenericAttributes();
	return ret;

}
bool
PropertyHandleI::HasIndex(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::HasIndex();
	return ret;

}
bool
PropertyHandleI::Inherits(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Inherits(
		  (char*) strnames.c_str()		//<STRING|strnames|RL_1
		);
	return ret;

}
bool
PropertyHandleI::InsertString(
		  const ::std::string& pstring			//<STRING|string
		, ::Ice::Int position			//<INT|position
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::InsertString(
		  (char*) pstring.c_str()		//<STRING|string|RL_1
		, position		//<INT|position|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::InsertTerminator(
		  const ::std::string& pstring			//<STRING|string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::InsertTerminator(
		  (char*) pstring.c_str()		//<STRING|string|RL_1
		);
	return ret;

}
bool
PropertyHandleI::InstanceInserted(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::InstanceInserted();
	return ret;

}
::std::string
PropertyHandleI::InstanceToString(
		  const ::std::string& stringsep			//<STRING|string_sep
		, const ::std::string& fieldsep			//<STRING|field_sep
		, const ::std::string& blocksep			//<STRING|block_sep
		, const ::std::string& emptystring			//<STRING|empty_string
		, bool skiptrans			//<LOGICAL|skip_trans
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::InstanceToString(
		  (char*) stringsep.c_str()		//<STRING|string_sep|RL_1
		, (char*) fieldsep.c_str()		//<STRING|field_sep|RL_1
		, (char*) blocksep.c_str()		//<STRING|block_sep|RL_1
		, (char*) emptystring.c_str()		//<STRING|empty_string|RL_1
		, skiptrans		//<LOGICAL|skip_trans|RL_direct
		);
	return ::std::string(ret);

}
::OPI::PropertyHandlePrx
PropertyHandleI::Intersect(
		  const ::OPI::PropertyHandlePrx& prophdl1			//<PropertyHandle|prop_hdl1
		, const ::OPI::PropertyHandlePrx& prophdl2			//<PropertyHandle|prop_hdl2
		, const ::std::string& skopt			//<CHAR|sk_opt
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl1 = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl1).ice_getIdentity()));
	::PropertyHandle *TCprophdl1 = &(*TCPprophdl1);
	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl2 = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl2).ice_getIdentity()));
	::PropertyHandle *TCprophdl2 = &(*TCPprophdl2);
	char TCskopt = skopt[0];
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::Intersect(
		  (::PropertyHandle&)*TCprophdl1		//<PropertyHandle|prop_hdl1|RL_reference
		, (::PropertyHandle&)*TCprophdl2		//<PropertyHandle|prop_hdl2|RL_reference
		, TCskopt		//<CHAR|sk_opt|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
PropertyHandleI::Is(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	bool ret;
	ret=
		PropertyHandle::Is(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prop_hdl|RL_reference
		);
	return ret;

}
bool
PropertyHandleI::IsA(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsA(
		  (char*) strnames.c_str()		//<STRING|strnames|RL_1
		);
	return ret;

}
bool
PropertyHandleI::IsActive(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsActive();
	return ret;

}
bool
PropertyHandleI::IsAttribute(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsAttribute();
	return ret;

}
bool
PropertyHandleI::IsAutoSelection(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsAutoSelection();
	return ret;

}
bool
PropertyHandleI::IsBasedOn(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsBasedOn(
		  (char*) strnames.c_str()		//<STRING|strnames|RL_1
		);
	return ret;

}
bool
PropertyHandleI::IsBasetypeProperty(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsBasetypeProperty();
	return ret;

}
bool
PropertyHandleI::IsBasicType(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsBasicType();
	return ret;

}
bool
PropertyHandleI::IsClient(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsClient();
	return ret;

}
bool
PropertyHandleI::IsCollection(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{

	char TCchkopt = chkopt[0];
	bool ret;
	ret=
		PropertyHandle::IsCollection(
		  TCchkopt		//<CHAR|chkopt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::IsCollectionUpdate(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsCollectionUpdate();
	return ret;

}
bool
PropertyHandleI::IsCopyHandle(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsCopyHandle();
	return ret;

}
bool
PropertyHandleI::IsDirty(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsDirty();
	return ret;

}
bool
PropertyHandleI::IsEmpty(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsEmpty();
	return ret;

}
bool
PropertyHandleI::IsEnumeration(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsEnumeration();
	return ret;

}
bool
PropertyHandleI::IsGenericAttribute(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsGenericAttribute();
	return ret;

}
bool
PropertyHandleI::IsInitInstance(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsInitInstance();
	return ret;

}
bool
PropertyHandleI::IsMemo(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{

	char TCchkopt = chkopt[0];
	bool ret;
	ret=
		PropertyHandle::IsMemo(
		  TCchkopt		//<CHAR|chkopt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::IsModified(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsModified();
	return ret;

}
bool
PropertyHandleI::IsNewInstance(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsNewInstance();
	return ret;

}
bool
PropertyHandleI::IsNumeric(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsNumeric();
	return ret;

}
bool
PropertyHandleI::IsOldInstance(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsOldInstance();
	return ret;

}
bool
PropertyHandleI::IsOwner(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsOwner();
	return ret;

}
bool
PropertyHandleI::IsPositioned(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{

	char TCchkopt = chkopt[0];
	bool ret;
	ret=
		PropertyHandle::IsPositioned(
		  TCchkopt		//<CHAR|chkopt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::IsReadOnly(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsReadOnly();
	return ret;

}
bool
PropertyHandleI::IsSelected(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{

	char TCchkopt = chkopt[0];
	bool ret;
	ret=
		PropertyHandle::IsSelected(
		  TCchkopt		//<CHAR|chkopt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::IsSensitive(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsSensitive(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
bool
PropertyHandleI::IsServer(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsServer();
	return ret;

}
bool
PropertyHandleI::IsShareBaseHandle(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{

	char TCchkopt = chkopt[0];
	bool ret;
	ret=
		PropertyHandle::IsShareBaseHandle(
		  TCchkopt		//<CHAR|chkopt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::IsStructure(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsStructure();
	return ret;

}
bool
PropertyHandleI::IsText(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{

	char TCchkopt = chkopt[0];
	bool ret;
	ret=
		PropertyHandle::IsText(
		  TCchkopt		//<CHAR|chkopt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::IsTransient(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsTransient();
	return ret;

}
bool
PropertyHandleI::IsTrue(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsTrue(
		  (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
bool
PropertyHandleI::IsTyped(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsTyped();
	return ret;

}
bool
PropertyHandleI::IsUserHandle(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsUserHandle();
	return ret;

}
bool
PropertyHandleI::IsValid(
		  bool topt			//<LOGICAL|topt
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsValid(
		  topt		//<LOGICAL|topt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::IsValidText(
		  const ::std::string& pstring			//<STRING|string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsValidText(
		  (char*) pstring.c_str()		//<STRING|string|RL_1
		);
	return ret;

}
bool
PropertyHandleI::IsVariableType(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsVariableType();
	return ret;

}
bool
PropertyHandleI::IsWeakTyped(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsWeakTyped();
	return ret;

}
bool
PropertyHandleI::IsWrite(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::IsWrite();
	return ret;

}
bool
PropertyHandleI::Locate(
		  ::Ice::Int obident			//<INT|obident
		, bool readopt			//<LOGICAL|read_opt
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Locate(
		  obident		//<INT|obident|RL_direct
		, readopt		//<LOGICAL|read_opt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::LocatePath(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::LocatePath();
	return ret;

}
bool
PropertyHandleI::Lock(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Lock();
	return ret;

}
bool
PropertyHandleI::LockSet(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::LockSet();
	return ret;

}
void
PropertyHandleI::MarkUnused(
		  const ::Ice::Current& current //< ice default

	)
{

		PropertyHandle::MarkUnused();
}
void
PropertyHandleI::MarkUsed(
		  const ::Ice::Current& current //< ice default

	)
{

		PropertyHandle::MarkUsed();
}
::OPI::PropertyHandlePrx
PropertyHandleI::Minus(
		  const ::OPI::PropertyHandlePrx& prophdl1			//<PropertyHandle|prop_hdl1
		, const ::OPI::PropertyHandlePrx& prophdl2			//<PropertyHandle|prop_hdl2
		, const ::std::string& skopt			//<CHAR|sk_opt
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl1 = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl1).ice_getIdentity()));
	::PropertyHandle *TCprophdl1 = &(*TCPprophdl1);
	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl2 = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl2).ice_getIdentity()));
	::PropertyHandle *TCprophdl2 = &(*TCPprophdl2);
	char TCskopt = skopt[0];
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::Minus(
		  (::PropertyHandle&)*TCprophdl1		//<PropertyHandle|prop_hdl1|RL_reference
		, (::PropertyHandle&)*TCprophdl2		//<PropertyHandle|prop_hdl2|RL_reference
		, TCskopt		//<CHAR|sk_opt|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
PropertyHandleI::Modify(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Modify();
	return ret;

}
bool
PropertyHandleI::Move(
		  const ::OPI::PropertyHandlePrx& sourcehandle			//<PropertyHandle|source_handle
		, const ::std::string& newkey			//<Key|new_key
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPsourcehandle = PropertyHandleIPtr::dynamicCast(current.adapter->find((*sourcehandle).ice_getIdentity()));
	::PropertyHandle *TCsourcehandle = &(*TCPsourcehandle);
	bool ret;
	ret=
		PropertyHandle::Move(
		  (::PropertyHandle&)*TCsourcehandle		//<PropertyHandle|source_handle|RL_reference
		, (char*) newkey.c_str()		//<Key|new_key|RL_direct
		, enumice2cpp(replopt)		//<PIREPL|replopt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::MoveDown(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::MoveDown();
	return ret;

}
bool
PropertyHandleI::MoveUp(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::MoveUp();
	return ret;

}
::std::string
PropertyHandleI::NextKey(
		  const ::std::string& sortkeyw			//<Key|sort_key_w
		, ::Ice::Int switchlevel			//<INT|switch_level
		, const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::NextKey(
		  (char*) sortkeyw.c_str()		//<Key|sort_key_w|RL_direct
		, switchlevel		//<INT|switch_level|RL_direct
		);
	return ::std::string(ret);

}
bool
PropertyHandleI::NoWrite(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::NoWrite();
	return ret;

}
bool
PropertyHandleI::Open(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Open();
	return ret;

}
bool
PropertyHandleI::OpenBigInt(
		  ::Ice::Int int64val			//<INT|int64_val
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Open(
		  int64val		//<INT|int64_val|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::OpenBoolean(
		  bool logval			//<LOGICAL|logval
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Open(
		  logval		//<LOGICAL|logval|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::OpenChild(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	bool ret;
	ret=
		PropertyHandle::Open(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prop_hdl|RL_reference
		, (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
bool
PropertyHandleI::OpenChildReference(
		  const ::OPI::PropertyHandlePrx& ppropertyhandle			//<PropertyHandle|property_handle
		, const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPppropertyhandle = PropertyHandleIPtr::dynamicCast(current.adapter->find((*ppropertyhandle).ice_getIdentity()));
	::PropertyHandle *TCppropertyhandle = &(*TCPppropertyhandle);
	bool ret;
	ret=
		PropertyHandle::Open(
		  (::PropertyHandle*)TCppropertyhandle		//<PropertyHandle|property_handle|RL_1
		, (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
bool
PropertyHandleI::OpenCopy(
		  const ::OPI::PropertyHandlePrx& cprophdl			//<PropertyHandle|cprop_hdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPcprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*cprophdl).ice_getIdentity()));
	::PropertyHandle *TCcprophdl = &(*TCPcprophdl);
	bool ret;
	ret=
		PropertyHandle::Open(
		  (::PropertyHandle&)*TCcprophdl		//<PropertyHandle|cprop_hdl|RL_reference
		);
	return ret;

}
bool
PropertyHandleI::OpenDate(
		  ::Ice::Long dateval			//<dbdt|date_val
		, const ::Ice::Current& current //< ice default

	)
{

	dbdt TCdateval;
	TCdateval.FromUnix(dateval);
	bool ret;
	ret=
		PropertyHandle::Open(
		  TCdateval		//<dbdt|date_val|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::OpenExtent(
		  const ::OPI::DBObjectHandlePrx& objecthandle			//<DBObjectHandle|object_handle
		, const ::std::string& extnames			//<STRING|extnames
		, ::OPI::PIACC accopt			//<PIACC|accopt
		, bool transientw			//<LOGICAL|transient_w
		, const ::std::string& keynamew			//<CHAR|key_name_w
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	::DBObjectHandle *TCobjecthandle = dbocast(objecthandle, current);

	bool ret;
	ret=
		PropertyHandle::Open(
		  (::DBObjectHandle&)*TCobjecthandle		//<DBObjectHandle|object_handle|RL_reference
		, (char*) extnames.c_str()		//<STRING|extnames|RL_1
		, enumice2cpp(accopt)		//<PIACC|accopt|RL_direct
		, transientw		//<LOGICAL|transient_w|RL_direct
		, (char*) keynamew.c_str()		//<CHAR|key_name_w|RL_1
		);
	return ret;

}
bool
PropertyHandleI::OpenFloat(
		  ::Ice::Float dblvalue			//<REAL|dbl_value
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Open(
		  dblvalue		//<REAL|dbl_value|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::OpenInteger(
		  ::Ice::Int intval			//<INT|int_val
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Open(
		  intval		//<INT|int_val|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::OpenReference(
		  const ::OPI::PropertyHandlePrx& ppropertyhandle			//<PropertyHandle|property_handle
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPppropertyhandle = PropertyHandleIPtr::dynamicCast(current.adapter->find((*ppropertyhandle).ice_getIdentity()));
	::PropertyHandle *TCppropertyhandle = &(*TCPppropertyhandle);
	bool ret;
	ret=
		PropertyHandle::Open(
		  (::PropertyHandle*)TCppropertyhandle		//<PropertyHandle|property_handle|RL_1
		);
	return ret;

}
bool
PropertyHandleI::OpenSizedString(
		  const ::std::string& pstring			//<STRING|string
		, ::Ice::Int stringlen			//<INT|string_len
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Open(
		  (char*) pstring.c_str()		//<STRING|string|RL_1
		, stringlen		//<INT|string_len|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::OpenString(
		  const ::std::string& pstring			//<STRING|string
		, bool convopt			//<LOGICAL|conv_opt
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Open(
		  (char*) pstring.c_str()		//<STRING|string|RL_1
		, convopt		//<LOGICAL|conv_opt|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::OpenTime(
		  ::Ice::Long timeval			//<dbtm|time_val
		, const ::Ice::Current& current //< ice default

	)
{

	dbtm TCtimeval;
	TCtimeval.FromUnix(timeval);
	bool ret;
	ret=
		PropertyHandle::Open(
		  TCtimeval		//<dbtm|time_val|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::OpenTimestamp(
		  ::Ice::Long datetimeval			//<dttm|datetime_val
		, const ::Ice::Current& current //< ice default

	)
{

	dttm TCdatetimeval;
	TCdatetimeval.FromUnix(datetimeval);
	bool ret;
	ret=
		PropertyHandle::Open(
		  TCdatetimeval		//<dttm|datetime_val|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::OpenHierarchy(
		  const ::OPI::PropertyHandlePrx& bottomph			//<PropertyHandle|bottom_ph
		, const ::OPI::PropertyHandlePrx& topph			//<PropertyHandle|top_ph
		, bool pathopt			//<LOGICAL|path_opt
		, ::OPI::PIACC accmode			//<PIACC|accmode
		, bool copyselection			//<LOGICAL|copy_selection
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPbottomph = PropertyHandleIPtr::dynamicCast(current.adapter->find((*bottomph).ice_getIdentity()));
	::PropertyHandle *TCbottomph = &(*TCPbottomph);
	//call parameter proxy cast
	PropertyHandleIPtr TCPtopph = PropertyHandleIPtr::dynamicCast(current.adapter->find((*topph).ice_getIdentity()));
	::PropertyHandle *TCtopph = &(*TCPtopph);
	bool ret;
	ret=
		PropertyHandle::OpenHierarchy(
		  (::PropertyHandle*)TCbottomph		//<PropertyHandle|bottom_ph|RL_1
		, (::PropertyHandle*)TCtopph		//<PropertyHandle|top_ph|RL_1
		, pathopt		//<LOGICAL|path_opt|RL_direct
		, enumice2cpp(accmode)		//<PIACC|accmode|RL_direct
		, copyselection		//<LOGICAL|copy_selection|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::OwnsData(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::OwnsData();
	return ret;

}
bool
PropertyHandleI::Position(
		  ::Ice::Int count			//<INT|count
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Position(
		  count		//<INT|count|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::PositionTop(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::PositionTop();
	return ret;

}
::OPI::PropertyHandlePrx
PropertyHandleI::Power(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	PropertyHandleIPtr ret;
	::PropertyHandle TR = 
		PropertyHandle::Power(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prop_hdl|RL_reference
		);
	ret = new PropertyHandleI(TR);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
PropertyHandleI::ProvGenAttribute(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ProvGenAttribute();
	return ret;

}
bool
PropertyHandleI::Provide(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	bool ret;
	ret=
		PropertyHandle::Provide(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prop_hdl|RL_reference
		);
	return ret;

}
bool
PropertyHandleI::ProvideAtPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Provide(
		  setpos0w		//<INT|set_pos0_w|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::ProvideByKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Provide(
		  (char*) sortkey.c_str()		//<Key|sort_key|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::ProvideArea(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ProvideArea();
	return ret;

}
::std::string
PropertyHandleI::ProvideGUID(
		  const ::Ice::Current& current //< ice default

	)
{

	char* ret;
	ret=
		PropertyHandle::ProvideGUID();
	return ::std::string(ret);

}
bool
PropertyHandleI::ProvideGlobal(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	bool ret;
	ret=
		PropertyHandle::ProvideGlobal(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prop_hdl|RL_reference
		);
	return ret;

}
bool
PropertyHandleI::ProvideGlobalAtPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ProvideGlobal(
		  setpos0w		//<INT|set_pos0_w|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::ProvideGlobalByKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ProvideGlobal(
		  (char*) sortkey.c_str()		//<Key|sort_key|RL_direct
		);
	return ret;

}
::OPI::OperationHandlePrx
PropertyHandleI::ProvideOperation(
		  const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{

	OperationHandleIPtr ret;
	ret=new OperationHandleI(/*RL_1*/*
		PropertyHandle::ProvideOperation(
		  (char*) expression.c_str()		//<STRING|expression|RL_1
		)
	);

	::OPI::OperationHandlePrx prx = OPI::OperationHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->OperationHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
PropertyHandleI::Refresh(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Refresh();
	return ret;

}
bool
PropertyHandleI::ReleaseBuffer(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ReleaseBuffer();
	return ret;

}
bool
PropertyHandleI::RemoveFromCollection(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::RemoveFromCollection();
	return ret;

}
bool
PropertyHandleI::RemoveString(
		  const ::std::string& pstring			//<STRING|string
		, ::Ice::Int position			//<INT|position
		, ::Ice::Int len			//<INT|len
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::RemoveString(
		  (char*) pstring.c_str()		//<STRING|string|RL_1
		, position		//<INT|position|RL_direct
		, len		//<INT|len|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::RemoveTerminator(
		  const ::std::string& pstring			//<STRING|string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::RemoveTerminator(
		  (char*) pstring.c_str()		//<STRING|string|RL_1
		);
	return ret;

}
bool
PropertyHandleI::Rename(
		  const ::std::string& newkey			//<Key|new_key
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Rename(
		  (char*) newkey.c_str()		//<Key|new_key|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::RepairIndex(
		  const ::std::string& keynamew			//<CHAR|key_name_w
		, const ::std::string& attrstrw			//<STRING|attrstr_w
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::RepairIndex(
		  (char*) keynamew.c_str()		//<CHAR|key_name_w|RL_1
		, (char*) attrstrw.c_str()		//<STRING|attrstr_w|RL_1
		);
	return ret;

}
bool
PropertyHandleI::ReplaceString(
		  const ::std::string& oldstr			//<STRING|old_str
		, const ::std::string& newstr			//<STRING|new_str
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ReplaceString(
		  (char*) oldstr.c_str()		//<STRING|old_str|RL_1
		, (char*) newstr.c_str()		//<STRING|new_str|RL_1
		);
	return ret;

}
bool
PropertyHandleI::ReplaceSysVariables(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ReplaceSysVariables();
	return ret;

}
bool
PropertyHandleI::Reset(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Reset();
	return ret;

}
void
PropertyHandleI::ResetDirty(
		  const ::Ice::Current& current //< ice default

	)
{

		PropertyHandle::ResetDirty();
}
bool
PropertyHandleI::ResetTransientProperty(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ResetTransientProperty();
	return ret;

}
bool
PropertyHandleI::ResetWProtect(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ResetWProtect();
	return ret;

}
bool
PropertyHandleI::Save(
		  const ::std::string& savopt			//<CHAR|savopt
		, bool switchopt			//<LOGICAL|switchopt
		, const ::Ice::Current& current //< ice default

	)
{

	char TCsavopt = savopt[0];
	bool ret;
	ret=
		PropertyHandle::Save(
		  TCsavopt		//<CHAR|savopt|RL_direct
		, switchopt		//<LOGICAL|switchopt|RL_direct
		);
	return ret;

}
::Ice::Int
PropertyHandleI::SearchText(
		  const ::std::string& pstring			//<STRING|string
		, ::Ice::Int curpos			//<INT|curpos
		, bool caseopt			//<LOGICAL|case_opt
		, const ::Ice::Current& current //< ice default

	)
{

	int ret;
	ret=
		PropertyHandle::SearchText(
		  (char*) pstring.c_str()		//<STRING|string|RL_1
		, curpos		//<INT|curpos|RL_direct
		, caseopt		//<LOGICAL|case_opt|RL_direct
		);
	return ret;

}
::OPI::PropertyHandlePrx
PropertyHandleI::Select(
		  const ::OPI::PropertyHandlePrx& prophdlref			//<PropertyHandle|prophdl_ref
		, const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdlref = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdlref).ice_getIdentity()));
	::PropertyHandle *TCprophdlref = &(*TCPprophdlref);
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::Select(
		  (::PropertyHandle&)*TCprophdlref		//<PropertyHandle|prophdl_ref|RL_reference
		, (char*) expression.c_str()		//<STRING|expression|RL_1
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
void
PropertyHandleI::SetActionResult(
		  const ::std::string& resultstring			//<STRING|result_string
		, const ::Ice::Current& current //< ice default

	)
{

		PropertyHandle::SetActionResult(
		  (char*) resultstring.c_str()		//<STRING|result_string|RL_1
		);
}
bool
PropertyHandleI::SetContextVariables(
		  const ::std::string& contextstring			//<STRING|context_string
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetContextVariables(
		  (char*) contextstring.c_str()		//<STRING|context_string|RL_1
		);
	return ret;

}
void
PropertyHandleI::SetDirty(
		  const ::Ice::Current& current //< ice default

	)
{

		PropertyHandle::SetDirty();
}
bool
PropertyHandleI::SetDynLength(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetDynLength();
	return ret;

}
bool
PropertyHandleI::SetGenAttribute(
		  const ::std::string& attrstr			//<STRING|attrstr
		, const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetGenAttribute(
		  (char*) attrstr.c_str()		//<STRING|attrstr|RL_1
		, (char*) proppath.c_str()		//<STRING|prop_path|RL_1
		);
	return ret;

}
bool
PropertyHandleI::SetKey(
		  const ::std::string& identkey			//<Key|ident_key
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetKey(
		  (char*) identkey.c_str()		//<Key|ident_key|RL_direct
		);
	return ret;

}
void
PropertyHandleI::SetModified(
		  const ::Ice::Current& current //< ice default

	)
{

		PropertyHandle::SetModified();
}
bool
PropertyHandleI::SetNormalized(
		  ::Ice::Int longval			//<INT|long_val
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetNormalized(
		  longval		//<INT|long_val|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::SetOrder(
		  const ::std::string& keyname			//<STRING|key_name
		, const ::std::string& attrstr			//<STRING|attrstr
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetOrder(
		  (char*) keyname.c_str()		//<STRING|key_name|RL_1
		, (char*) attrstr.c_str()		//<STRING|attrstr|RL_1
		);
	return ret;

}
bool
PropertyHandleI::SetSelection(
		  const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetSelection(
		  (char*) expression.c_str()		//<STRING|expression|RL_1
		);
	return ret;

}
bool
PropertyHandleI::SetSortKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetSortKey(
		  (char*) sortkey.c_str()		//<Key|sort_key|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::SetTransientProperty(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl).ice_getIdentity()));
	::PropertyHandle *TCprophdl = &(*TCPprophdl);
	bool ret;
	ret=
		PropertyHandle::SetTransientProperty(
		  (::PropertyHandle&)*TCprophdl		//<PropertyHandle|prop_hdl|RL_reference
		);
	return ret;

}
bool
PropertyHandleI::SetType(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetType(
		  (char*) strnames.c_str()		//<STRING|strnames|RL_1
		);
	return ret;

}
bool
PropertyHandleI::SetUpdate(
		  bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetUpdate(
		  pcheckupdate		//<LOGICAL|check_update|RL_direct
		);
	return ret;

}
::OPI::PropertyHandlePrx
PropertyHandleI::SetValue(
		  const ::OPI::PropertyHandlePrx& cprophdl			//<PropertyHandle|cprop_hdl
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPcprophdl = PropertyHandleIPtr::dynamicCast(current.adapter->find((*cprophdl).ice_getIdentity()));
	::PropertyHandle *TCcprophdl = &(*TCPcprophdl);
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::SetValue(
		  (::PropertyHandle&)*TCcprophdl		//<PropertyHandle|cprop_hdl|RL_reference
		, pcheckupdate		//<LOGICAL|check_update|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::PropertyHandlePrx
PropertyHandleI::SetValueBigInt(
		  ::Ice::Int int64val			//<INT|int64_val
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{

	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::SetValue(
		  int64val		//<INT|int64_val|RL_direct
		, pcheckupdate		//<LOGICAL|check_update|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::PropertyHandlePrx
PropertyHandleI::SetValueBoolean(
		  bool logval			//<LOGICAL|logval
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{

	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::SetValue(
		  logval		//<LOGICAL|logval|RL_direct
		, pcheckupdate		//<LOGICAL|check_update|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::PropertyHandlePrx
PropertyHandleI::SetValueDate(
		  ::Ice::Long dateval			//<dbdt|date_val
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{

	dbdt TCdateval;
	TCdateval.FromUnix(dateval);
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::SetValue(
		  TCdateval		//<dbdt|date_val|RL_direct
		, pcheckupdate		//<LOGICAL|check_update|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::PropertyHandlePrx
PropertyHandleI::SetValueFloat(
		  ::Ice::Float dblvalue			//<REAL|dbl_value
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{

	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::SetValue(
		  dblvalue		//<REAL|dbl_value|RL_direct
		, pcheckupdate		//<LOGICAL|check_update|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::PropertyHandlePrx
PropertyHandleI::SetValueInteger(
		  ::Ice::Int longval			//<INT|long_val
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{

	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::SetValue(
		  longval		//<INT|long_val|RL_direct
		, pcheckupdate		//<LOGICAL|check_update|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::PropertyHandlePrx
PropertyHandleI::SetValueString(
		  const ::std::string& pstring			//<STRING|string
		, bool pcheckupdate			//<LOGICAL|check_update
		, bool convopt			//<LOGICAL|conv_opt
		, const ::Ice::Current& current //< ice default

	)
{

	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::SetValue(
		  (char*) pstring.c_str()		//<STRING|string|RL_1
		, pcheckupdate		//<LOGICAL|check_update|RL_direct
		, convopt		//<LOGICAL|conv_opt|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::PropertyHandlePrx
PropertyHandleI::SetValueTime(
		  ::Ice::Long timeval			//<dbtm|time_val
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{

	dbtm TCtimeval;
	TCtimeval.FromUnix(timeval);
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::SetValue(
		  TCtimeval		//<dbtm|time_val|RL_direct
		, pcheckupdate		//<LOGICAL|check_update|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
::OPI::PropertyHandlePrx
PropertyHandleI::SetValueTimestamp(
		  ::Ice::Long datetimeval			//<dttm|datetime_val
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{

	dttm TCdatetimeval;
	TCdatetimeval.FromUnix(datetimeval);
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::SetValue(
		  TCdatetimeval		//<dttm|datetime_val|RL_direct
		, pcheckupdate		//<LOGICAL|check_update|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
PropertyHandleI::SetVersion(
		  ::Ice::Int versionnr			//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetVersion(
		  versionnr		//<UINT|version_nr|RL_direct
		);
	return ret;

}
bool
PropertyHandleI::SetWProtect(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::SetWProtect();
	return ret;

}
bool
PropertyHandleI::ToTop(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::ToTop();
	return ret;

}
::OPI::PropertyHandlePrx
PropertyHandleI::Union(
		  const ::OPI::PropertyHandlePrx& prophdl1			//<PropertyHandle|prop_hdl1
		, const ::OPI::PropertyHandlePrx& prophdl2			//<PropertyHandle|prop_hdl2
		, const ::std::string& skopt			//<CHAR|sk_opt
		, bool distinct			//<LOGICAL|distinct
		, const ::Ice::Current& current //< ice default

	)
{

	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl1 = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl1).ice_getIdentity()));
	::PropertyHandle *TCprophdl1 = &(*TCPprophdl1);
	//call parameter proxy cast
	PropertyHandleIPtr TCPprophdl2 = PropertyHandleIPtr::dynamicCast(current.adapter->find((*prophdl2).ice_getIdentity()));
	::PropertyHandle *TCprophdl2 = &(*TCPprophdl2);
	char TCskopt = skopt[0];
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(
		PropertyHandle::Union(
		  (::PropertyHandle&)*TCprophdl1		//<PropertyHandle|prop_hdl1|RL_reference
		, (::PropertyHandle&)*TCprophdl2		//<PropertyHandle|prop_hdl2|RL_reference
		, TCskopt		//<CHAR|sk_opt|RL_direct
		, distinct		//<LOGICAL|distinct|RL_direct
		)
	);

	::OPI::PropertyHandlePrx prx = OPI::PropertyHandlePrx::uncheckedCast(current.adapter->addWithUUID(ret));
	factory->PropertyHandleItems.push_back(prx);
	ret->SetObjectFactory(factory);
	return prx;

}
bool
PropertyHandleI::Unlock(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::Unlock();
	return ret;

}
bool
PropertyHandleI::UnlockSet(
		  const ::Ice::Current& current //< ice default

	)
{

	bool ret;
	ret=
		PropertyHandle::UnlockSet();
	return ret;

}

void PropertyHandleI::SetObjectFactory(OPIFactoryIPtr removingfactory){
	factory = removingfactory;
}
// end PropertyHandle -------------
