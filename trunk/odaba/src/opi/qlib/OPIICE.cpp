#include <OdabaI.h>
#include <Ice/Ice.h>
using namespace std;
bool
CheckOptionsI::Initialize(
		  const ::std::string& parmstring		//<STRING|parmstring
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Initialize
	return ret;

}
::Ice::Int
DBObjectHandleI::BeginTransaction(
		  bool extTA		//<LOGICAL|ext_TA
		, ::Ice::Int wmaxnum		//<INT|w_maxnum
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::BeginTransaction
	return ret;

}
bool
DBObjectHandleI::ChangeTimeStamp(
		  ::Ice::Int versionnr		//<UINT|version_nr
		, ::Ice::Long timestamp		//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ChangeTimeStamp
	return ret;

}
bool
DBObjectHandleI::CommitTransaction(
		  ::Ice::Int talevel		//<INT|talevel
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CommitTransaction
	return ret;

}
::Odaba::PropertyHandlePrx
DBObjectHandleI::CreateTempPropertyHandle(
		  const ::Odaba::PropertyHandlePrx& prophdlref		//<PropertyHandle|prophdl_ref
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::CreateTempPropertyHandle
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
DBObjectHandleI::DeleteExtent(
		  const ::std::string& extnames		//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::DeleteExtent
	return ret;

}
bool
DBObjectHandleI::DeleteExtentRef(
		  const ::std::string& extnames		//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::DeleteExtentRef
	return ret;

}
void
DBObjectHandleI::DisableEventHandling(
		  const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::DisableEventHandling
	return ret;

}
void
DBObjectHandleI::EnableEventHandling(
		  const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::EnableEventHandling
	return ret;

}
bool
DBObjectHandleI::EventHandling(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::EventHandling
	return ret;

}
bool
DBObjectHandleI::ExecuteDBObjectAction(
		  const ::std::string& actionname		//<CHAR|action_name
		, const ::std::string& parmstring		//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ExecuteDBObjectAction
	return ret;

}
::Odaba::PropertyHandlePrx
DBObjectHandleI::ExecuteExpression(
		  const ::Odaba::DBObjectHandlePrx& resobhandle		//<DBObjectHandle|res_obhandle
		, const ::std::string& expression		//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::ExecuteExpression
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
DBObjectHandleI::ExtentExist(
		  const ::std::string& extnames		//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ExtentExist
	return ret;

}
::Odaba::PIACC
DBObjectHandleI::GetAccess(
		  const ::Ice::Current& current //< ice default

	)
{
	::Odaba::PIACC ret;
	ret=enumcpp2ice((PIACC)::GetAccess
	return ret;

}
::std::string
DBObjectHandleI::GetActionResult(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetActionResult
	return ret;

}
::Odaba::DatabaseHandlePrx
DBObjectHandleI::GetDBHandle(
		  const ::Ice::Current& current //< ice default

	)
{
	DatabaseHandleIPtr ret;
	ret=new DatabaseHandleI(::GetDBHandle
	return Odaba::DatabaseHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::DataSourceHandlePrx
DBObjectHandleI::GetDataSource(
		  const ::Ice::Current& current //< ice default

	)
{
	DataSourceHandleIPtr ret;
	ret=new DataSourceHandleI(::GetDataSource
	return Odaba::DataSourceHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::DictionaryHandlePrx
DBObjectHandleI::GetDictionary(
		  const ::Ice::Current& current //< ice default

	)
{
	DictionaryHandleIPtr ret;
	ret=new DictionaryHandleI(::GetDictionary
	return Odaba::DictionaryHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::std::string
DBObjectHandleI::GetExtent(
		  ::Ice::Int indx0		//<INT|indx0
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetExtent
	return ret;

}
::Odaba::DBObjectHandlePrx
DBObjectHandleI::GetHighObject(
		  const ::Ice::Current& current //< ice default

	)
{
	DBObjectHandleIPtr ret;
	ret=new DBObjectHandleI(::GetHighObject
	return Odaba::DBObjectHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::std::string
DBObjectHandleI::GetObject(
		  ::Ice::Int indx0		//<INT|indx0
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetObject
	return ret;

}
::std::string
DBObjectHandleI::GetServerVariable(
		  const ::std::string& varname		//<STRING|var_name
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetServerVariable
	return ret;

}
::Ice::Int
DBObjectHandleI::GetSystemVersion(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetSystemVersion
	return ret;

}
::Ice::Long
DBObjectHandleI::GetTimeStamp(
		  ::Ice::Int versionnr		//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	)
{
	dttm ret;
	ret=::GetTimeStamp
	return ret;

}
::Ice::Int
DBObjectHandleI::GetTransactionLevel(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetTransactionLevel
	return ret;

}
::Ice::Int
DBObjectHandleI::GetVersion(
		  ::Ice::Long timestamp		//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetVersion
	return ret;

}
bool
DBObjectHandleI::IsClient(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsClient
	return ret;

}
bool
DBObjectHandleI::IsEmpty(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsEmpty
	return ret;

}
bool
DBObjectHandleI::IsOpened(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsOpened
	return ret;

}
bool
DBObjectHandleI::IsServer(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsServer
	return ret;

}
bool
DBObjectHandleI::IsValid(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsValid
	return ret;

}
bool
DBObjectHandleI::NewVersion(
		  ::Ice::Long timestamp		//<dttm|timestamp
		, ::Ice::Int versionnr		//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::NewVersion
	return ret;

}
bool
DBObjectHandleI::OpenObject(
		  const ::Odaba::DBObjectHandlePrx& dbobject		//<DBObjectHandle|dbobject
		, const ::std::string& objname		//<CHAR|objname
		, ::Odaba::PIACC accopt		//<PIACC|accopt
		, ::Ice::Int versionnr		//<UINT|version_nr
		, ::Odaba::ResourceTypes localressources		//<ResourceTypes|local_ressources
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::OpenObject
	return ret;

}
bool
DBObjectHandleI::RollBack(
		  ::Ice::Int talevel		//<INT|talevel
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::RollBack
	return ret;

}
void
DBObjectHandleI::SetActionResult(
		  const ::std::string& resultstring		//<STRING|result_string
		, const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::SetActionResult
	return ret;

}
::Ice::Int
DBObjectHandleI::SetOverload(
		  bool overloadopt		//<LOGICAL|overload_opt
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::SetOverload
	return ret;

}
bool
DBObjectHandleI::SetServerVariable(
		  const ::std::string& varname		//<STRING|var_name
		, const ::std::string& varstring		//<STRING|var_string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetServerVariable
	return ret;

}
bool
DBObjectHandleI::SetUserDefinedIdentity(
		  bool identityopt		//<LOGICAL|identity_opt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetUserDefinedIdentity
	return ret;

}
bool
DBObjectHandleI::SetVersion(
		  ::Ice::Int versionnr		//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetVersion
	return ret;

}
bool
DBObjectHandleI::SetVersioni1(
		  ::Ice::Long date		//<dbdt|date
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetVersion
	return ret;

}
bool
DBObjectHandleI::SetVersioni2(
		  ::Ice::Long timestamp		//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetVersion
	return ret;

}
::Ice::Int
DBObjectHandleI::VersionCount(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::VersionCount
	return ret;

}
bool
DataSourceHandleI::BeginTransaction(
		  bool extta		//<LOGICAL|ext_ta
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::BeginTransaction
	return ret;

}
bool
DataSourceHandleI::Close(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Close
	return ret;

}
bool
DataSourceHandleI::CloseDBObject(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CloseDBObject
	return ret;

}
bool
DataSourceHandleI::CloseDatabase(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CloseDatabase
	return ret;

}
bool
DataSourceHandleI::CloseDictionary(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CloseDictionary
	return ret;

}
bool
DataSourceHandleI::CloseProperty(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CloseProperty
	return ret;

}
bool
DataSourceHandleI::CloseResourceDB(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CloseResourceDB
	return ret;

}
bool
DataSourceHandleI::CommitTransaction(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CommitTransaction
	return ret;

}
bool
DataSourceHandleI::Connect(
		  const ::Odaba::ODABAClientPrx& odabaclient		//<ODABAClient|odaba_client
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Connect
	return ret;

}
bool
DataSourceHandleI::Disconnect(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Disconnect
	return ret;

}
bool
DataSourceHandleI::Open(
		  const ::Odaba::ODABAClientPrx& odabaclient		//<ODABAClient|odaba_client
		, ::Odaba::PIACC accmod		//<PIACC|acc_mod
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
DataSourceHandleI::Openi02(
		  const ::Odaba::ODABAClientPrx& odabaclient		//<ODABAClient|odaba_client
		, const ::std::string& inifile		//<STRING|ini_file
		, const ::std::string& datasourcename		//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
DataSourceHandleI::Openi1(
		  const ::Odaba::ODABAClientPrx& odabaclient		//<ODABAClient|odaba_client
		, const ::std::string& datasourcename		//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
::Odaba::DBObjectHandlePrx
DataSourceHandleI::OpenDBObject(
		  const ::Ice::Current& current //< ice default

	)
{
	DBObjectHandleIPtr ret;
	ret=new DBObjectHandleI(::OpenDBObject
	return Odaba::DBObjectHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::DatabaseHandlePrx
DataSourceHandleI::OpenDatabase(
		  const ::Ice::Current& current //< ice default

	)
{
	DatabaseHandleIPtr ret;
	ret=new DatabaseHandleI(::OpenDatabase
	return Odaba::DatabaseHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::DictionaryHandlePrx
DataSourceHandleI::OpenDictionary(
		  ::Odaba::PIACC accopt		//<PIACC|accopt
		, const ::Ice::Current& current //< ice default

	)
{
	DictionaryHandleIPtr ret;
	ret=new DictionaryHandleI(::OpenDictionary
	return Odaba::DictionaryHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::PropertyHandlePrx
DataSourceHandleI::OpenProperty(
		  const ::std::string& extname		//<CHAR|extname
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::OpenProperty
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::DatabaseHandlePrx
DataSourceHandleI::OpenResourceDB(
		  const ::Ice::Current& current //< ice default

	)
{
	DatabaseHandleIPtr ret;
	ret=new DatabaseHandleI(::OpenResourceDB
	return Odaba::DatabaseHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
DataSourceHandleI::RollBack(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::RollBack
	return ret;

}
bool
DataSourceHandleI::SetDBObject(
		  const ::Odaba::DBObjectHandlePrx& ohandle		//<DBObjectHandle|ohandle
		, const ::std::string& wobjname		//<STRING|w_objname
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetDBObject
	return ret;

}
bool
DataSourceHandleI::SetDataSource(
		  const ::Odaba::DataSourceHandlePrx& dbdefptr		//<DataSourceHandle|dbdefptr
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetDataSource
	return ret;

}
bool
DataSourceHandleI::SetDatabase(
		  const ::Odaba::DatabaseHandlePrx& dbhandle		//<DatabaseHandle|db_handle
		, const ::std::string& wbasepath		//<STRING|w_basepath
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetDatabase
	return ret;

}
bool
DataSourceHandleI::SetDictionary(
		  const ::Odaba::DictionaryHandlePrx& dictptr		//<DictionaryHandle|dictptr
		, const ::std::string& wdictpath		//<STRING|w_dictpath
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetDictionary
	return ret;

}
bool
DataSourceHandleI::SetResourceDB(
		  const ::Odaba::DatabaseHandlePrx& dbhandle		//<DatabaseHandle|db_handle
		, const ::std::string& wbasepath		//<STRING|w_basepath
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetResourceDB
	return ret;

}
bool
DataSourceHandleI::SetVariables(
		  const ::std::string& datasourcename		//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetVariables
	return ret;

}
bool
DataSourceHandleI::Setup(
		  const ::std::string& inifile		//<STRING|ini_file
		, const ::std::string& datasourcename		//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Setup
	return ret;

}
bool
DataSourceHandleI::SetupVariables(
		  const ::std::string& datasourcename		//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetupVariables
	return ret;

}
bool
DatabaseHandleI::ActivateShadowBase(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ActivateShadowBase
	return ret;

}
bool
DatabaseHandleI::BackupDB(
		  const ::std::string& target		//<STRING|target
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::BackupDB
	return ret;

}
bool
DatabaseHandleI::CheckDB(
		  const ::Odaba::CheckOptionsPrx& checkopts		//<CheckOptions|check_opts
		, const ::std::string& source		//<STRING|source
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckDB
	return ret;

}
bool
DatabaseHandleI::CheckLicence(
		  const ::std::string& licowner		//<STRING|lic_owner
		, const ::std::string& licnumber		//<CHAR|lic_number
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckLicence
	return ret;

}
bool
DatabaseHandleI::CloseWorkspace(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CloseWorkspace
	return ret;

}
bool
DatabaseHandleI::ConsolidateWorkspace(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ConsolidateWorkspace
	return ret;

}
bool
DatabaseHandleI::DeactivateShadowBase(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::DeactivateShadowBase
	return ret;

}
bool
DatabaseHandleI::DeleteWorkspace(
		  const ::std::string& wsnames		//<STRING|ws_names
		, const ::std::string& username		//<STRING|user_name
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::DeleteWorkspace
	return ret;

}
bool
DatabaseHandleI::DisableWorkspace(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::DisableWorkspace
	return ret;

}
bool
DatabaseHandleI::DiscardWorkspace(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::DiscardWorkspace
	return ret;

}
bool
DatabaseHandleI::EnableWorkspace(
		  const ::std::string& sdwpath		//<CHAR|sdw_path
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::EnableWorkspace
	return ret;

}
bool
DatabaseHandleI::ExecuteDatabaseAction(
		  const ::std::string& actionname		//<CHAR|action_name
		, const ::std::string& parmstring		//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ExecuteDatabaseAction
	return ret;

}
bool
DatabaseHandleI::ExistWorkspace(
		  const ::std::string& wsnames		//<STRING|ws_names
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ExistWorkspace
	return ret;

}
::Ice::Int
DatabaseHandleI::GetDatabaseID(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetDatabaseID
	return ret;

}
::std::string
DatabaseHandleI::GetPath(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetPath
	return ret;

}
::Ice::Int
DatabaseHandleI::GetSchemaVersion(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetSchemaVersion
	return ret;

}
::std::string
DatabaseHandleI::GetVersionString(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetVersionString
	return ret;

}
::std::string
DatabaseHandleI::GetWorkspace(
		  const ::std::string& wsroot		//<STRING|ws_root
		, ::Ice::Int wsindex		//<INT|ws_index
		, const ::std::string& username		//<STRING|user_name
		, const ::std::string& wsname		//<STRING|ws_name
		, bool refreshopt		//<LOGICAL|refresh_opt
		, const ::std::string& wsinfo		//<CHAR|ws_info
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetWorkspace
	return ret;

}
bool
DatabaseHandleI::IgnoreWriteProtect(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IgnoreWriteProtect
	return ret;

}
bool
DatabaseHandleI::InitDataArea(
		  ::Ice::Int mbnumber		//<INT|mbnumber
		, ::Ice::Int sbnumber		//<INT|sbnumber
		, ::Ice::Int danumber		//<UINT|danumber
		, const ::std::string& filename		//<STRING|filename
		, ::Ice::Int dasize		//<INT|dasize
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::InitDataArea
	return ret;

}
bool
DatabaseHandleI::InitMainBase(
		  ::Ice::Int mbnumber		//<INT|mbnumber
		, const ::std::string& filename		//<STRING|filename
		, ::Ice::Int lowEBN		//<INT|lowEBN
		, ::Ice::Int highEBN		//<INT|highEBN
		, ::Ice::Int dasize		//<INT|dasize
		, bool largedb		//<LOGICAL|largedb
		, bool pindep		//<LOGICAL|pindep
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::InitMainBase
	return ret;

}
bool
DatabaseHandleI::InitSubBase(
		  ::Ice::Int mbnumber		//<INT|mbnumber
		, ::Ice::Int sbnumber		//<INT|sbnumber
		, const ::std::string& filename		//<STRING|filename
		, ::Ice::Int dasize		//<INT|dasize
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::InitSubBase
	return ret;

}
bool
DatabaseHandleI::IsLicenced(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsLicenced
	return ret;

}
bool
DatabaseHandleI::IsShared(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsShared
	return ret;

}
bool
DatabaseHandleI::LocateWorkspace(
		  const ::std::string& wsnames		//<STRING|ws_names
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::LocateWorkspace
	return ret;

}
bool
DatabaseHandleI::OpenDatabase(
		  const ::Odaba::DictionaryHandlePrx& dicthandle		//<DictionaryHandle|dict_handle
		, const ::std::string& cpath		//<STRING|cpath
		, ::Odaba::PIACC accopt		//<PIACC|accopt
		, bool wnetopt		//<LOGICAL|w_netopt
		, bool onlineversion		//<LOGICAL|online_version
		, ::Ice::Int versionnr		//<UINT|version_nr
		, ::Odaba::ResourceTypes localressources		//<ResourceTypes|local_ressources
		, bool sysenv		//<LOGICAL|sysenv
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::OpenDatabase
	return ret;

}
bool
DatabaseHandleI::OpenWorkspace(
		  const ::std::string& wsnames		//<STRING|ws_names
		, const ::std::string& username		//<STRING|user_name
		, bool exclusive		//<LOGICAL|exclusive
		, const ::std::string& wspath		//<STRING|ws_path
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::OpenWorkspace
	return ret;

}
bool
DatabaseHandleI::RecreateExtent(
		  const ::std::string& extnames		//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::RecreateExtent
	return ret;

}
bool
DatabaseHandleI::RestoreDB(
		  const ::std::string& source		//<STRING|source
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::RestoreDB
	return ret;

}
bool
DatabaseHandleI::SetupTypeID(
		  ::Ice::Int sid		//<INT|sid
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetupTypeID
	return ret;

}
::Ice::Int
DictionaryHandleI::BaseType(
		  const ::std::string& strnames		//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::BaseType
	return ret;

}
bool
DictionaryHandleI::CheckExpression(
		  const ::std::string& expression		//<STRING|expression
		, const ::Odaba::DBObjectHandlePrx& dbobjhandle		//<DBObjectHandle|dbobj_handle
		, const ::std::string& clsnames		//<STRING|clsnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckExpression
	return ret;

}
bool
DictionaryHandleI::CheckExpressionInClass(
		  const ::Odaba::DBObjectHandlePrx& resobj		//<DBObjectHandle|resobj
		, const ::std::string& clsnames		//<STRING|clsnames
		, const ::std::string& exprnames		//<STRING|exprnames
		, const ::std::string& implnames		//<STRING|implnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckExpression
	return ret;

}
bool
DictionaryHandleI::CheckExtentDef(
		  const ::std::string& scopedname		//<STRING|scoped_name
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckExtentDef
	return ret;

}
bool
DictionaryHandleI::CheckValueSet(
		  const ::std::string& scopedname		//<STRING|scoped_name
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckValueSet
	return ret;

}
bool
DictionaryHandleI::CopyCodeset(
		  const ::Odaba::DictionaryHandlePrx& srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, const ::std::string& strname		//<CHAR|strname
		, ::Ice::Int namespaceid		//<INT|namespace_id
		, const ::std::string& newnames		//<STRING|newnames
		, ::Odaba::PIREPL dbreplace		//<PIREPL|db_replace
		, bool retainSID		//<LOGICAL|retainSID
		, bool retainschemav		//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CopyCodeset
	return ret;

}
bool
DictionaryHandleI::CopyExtentDef(
		  const ::Odaba::DictionaryHandlePrx& srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, const ::std::string& extentname		//<STRING|extentname
		, const ::std::string& newnames		//<STRING|newnames
		, const ::std::string& targstruct		//<STRING|targ_struct
		, bool transaction		//<LOGICAL|transaction
		, bool retainschemav		//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CopyExtentDef
	return ret;

}
bool
DictionaryHandleI::CopyStructure(
		  const ::Odaba::DictionaryHandlePrx& srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, const ::std::string& strname		//<CHAR|strname
		, ::Ice::Int namespaceid		//<INT|namespace_id
		, const ::std::string& newnames		//<STRING|newnames
		, const ::std::string& topname		//<CHAR|topname
		, ::Odaba::PIREPL dbreplace		//<PIREPL|db_replace
		, bool retainSID		//<LOGICAL|retainSID
		, bool retainschemav		//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CopyStructure
	return ret;

}
bool
DictionaryHandleI::CopyType(
		  const ::Odaba::DictionaryHandlePrx& srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, const ::std::string& strnames		//<STRING|strnames
		, const ::std::string& newnames		//<STRING|newnames
		, const ::std::string& topname		//<CHAR|topname
		, ::Odaba::PIREPL dbreplace		//<PIREPL|db_replace
		, bool retainSID		//<LOGICAL|retainSID
		, bool transaction		//<LOGICAL|transaction
		, bool retainschemav		//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CopyType
	return ret;

}
bool
DictionaryHandleI::CreateEnum(
		  const ::std::string& enumname		//<STRING|enum_name
		, const ::std::string& basetype		//<STRING|basetype
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CreateEnum
	return ret;

}
::std::string
DictionaryHandleI::CreateTempExtent(
		  const ::std::string& strnames		//<STRING|strnames
		, const ::std::string& extnamesw		//<STRING|extnames_w
		, const ::std::string& keynamew		//<CHAR|key_name_w
		, const ::std::string& baseextsw		//<STRING|baseexts_w
		, bool weakoptw		//<LOGICAL|weak_opt_w
		, bool ownoptw		//<LOGICAL|own_opt_w
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::CreateTempExtent
	return ret;

}
bool
DictionaryHandleI::DeleteEnum(
		  const ::std::string& enumname		//<STRING|enum_name
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::DeleteEnum
	return ret;

}
::std::string
DictionaryHandleI::EnumToString(
		  const ::std::string& enumeration		//<STRING|enumeration
		, ::Ice::Int enumval		//<INT|enum_val
		, const ::std::string& string		//<STRING|string
		, ::Ice::Int len		//<INT|len
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::EnumToString
	return ret;

}
::Ice::Int
DictionaryHandleI::GetLastSchemaVersion(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetLastSchemaVersion
	return ret;

}
::std::string
DictionaryHandleI::GetTempName(
		  const ::std::string& extnames		//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetTempName
	return ret;

}
bool
DictionaryHandleI::IsBasicType(
		  const ::std::string& typenames		//<STRING|typenames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsBasicType
	return ret;

}
bool
DictionaryHandleI::OpenDictionary(
		  const ::Odaba::ODABAClientPrx& odabaclient		//<ODABAClient|odaba_client
		, const ::std::string& cpath		//<STRING|cpath
		, ::Odaba::PIACC accopt		//<PIACC|accopt
		, bool wnetopt		//<LOGICAL|w_netopt
		, ::Ice::Int versionnr		//<UINT|version_nr
		, ::Odaba::ResourceTypes localressources		//<ResourceTypes|local_ressources
		, bool sysenv		//<LOGICAL|sysenv
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::OpenDictionary
	return ret;

}
::Ice::Int
DictionaryHandleI::StringToEnum(
		  const ::std::string& enumeration		//<STRING|enumeration
		, const ::std::string& enumstring		//<STRING|enum_string
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::StringToEnum
	return ret;

}
bool
DictionaryHandleI::UpdateVersion(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::UpdateVersion
	return ret;

}
void
ODABAClientI::ActivateGUIMessages(
		  const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::ActivateGUIMessages
	return ret;

}
bool
ODABAClientI::BackupDB(
		  const ::std::string& cpath		//<STRING|cpath
		, const ::std::string& target		//<STRING|target
		, ::Ice::Int waitsec		//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::BackupDB
	return ret;

}
bool
ODABAClientI::CheckDB(
		  const ::std::string& dictpath		//<STRING|dict_path
		, const ::std::string& cpath		//<STRING|cpath
		, const ::Odaba::CheckOptionsPrx& checkopts		//<CheckOptions|check_opts
		, const ::std::string& source		//<STRING|source
		, ::Ice::Int waitsec		//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckDB
	return ret;

}
bool
ODABAClientI::Close(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Close
	return ret;

}
bool
ODABAClientI::Connect(
		  const ::std::string& servername		//<STRING|server_name
		, ::Ice::Int hostport		//<UINT|host_port
		, const ::std::string& cachestring		//<STRING|cache_string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Connect
	return ret;

}
bool
ODABAClientI::DictDisplay(
		  const ::std::string& dbpath		//<STRING|dbpath
		, const ::std::string& ppath		//<STRING|ppath
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::DictDisplay
	return ret;

}
void
ODABAClientI::Disconnect(
		  const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::Disconnect
	return ret;

}
bool
ODABAClientI::Exist(
		  const ::std::string& cpath		//<STRING|cpath
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Exist
	return ret;

}
::std::string
ODABAClientI::GetDataSource(
		  ::Ice::Int indx0		//<INT|indx0
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetDataSource
	return ret;

}
::std::string
ODABAClientI::GetHost(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetHost
	return ret;

}
::Ice::Int
ODABAClientI::GetPort(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetPort
	return ret;

}
::std::string
ODABAClientI::GetServerVariable(
		  const ::std::string& varname		//<STRING|var_name
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetServerVariable
	return ret;

}
void
ODABAClientI::Initialize(
		  const ::std::string& inipath		//<STRING|inipath
		, const ::std::string& applicationname		//<STRING|application_name
		, const ::std::string& progpath		//<STRING|progpath
		, ::Odaba::ApplicationTypes applicationtype		//<ApplicationTypes|application_type
		, bool initservices		//<LOGICAL|init_services
		, const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::Initialize
	return ret;

}
bool
ODABAClientI::IsConnected(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsConnected
	return ret;

}
bool
ODABAClientI::KillClient(
		  ::Ice::Int clientid		//<INT|client_id
		, ::Ice::Int waitsec		//<INT|wait_sec
		, bool sendmessage		//<LOGICAL|send_message
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::KillClient
	return ret;

}
bool
ODABAClientI::Open(
		  const ::std::string& inipath		//<STRING|inipath
		, const ::std::string& applicationname		//<STRING|application_name
		, const ::std::string& progpath		//<STRING|progpath
		, ::Odaba::ApplicationTypes applicationtype		//<ApplicationTypes|application_type
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
::Odaba::DBObjectHandlePrx
ODABAClientI::OpenDataSource(
		  const ::std::string& datasourcename		//<STRING|datasource_name
		, ::Odaba::PIACC accopt		//<PIACC|accopt
		, const ::Ice::Current& current //< ice default

	)
{
	DBObjectHandleIPtr ret;
	ret=new DBObjectHandleI(::OpenDataSource
	return Odaba::DBObjectHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
ODABAClientI::PackDatabase(
		  const ::std::string& cpath		//<STRING|cpath
		, const ::std::string& temppath		//<STRING|temp_path
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::PackDatabase
	return ret;

}
bool
ODABAClientI::RestoreDB(
		  const ::std::string& cpath		//<STRING|cpath
		, const ::std::string& source		//<STRING|source
		, ::Ice::Int waitsec		//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::RestoreDB
	return ret;

}
bool
ODABAClientI::SendClientMessage(
		  ::Ice::Int clientid		//<INT|client_id
		, const ::std::string& mtext		//<STRING|mtext
		, const ::std::string& mtitle		//<STRING|mtitle
		, const ::std::string& mtype		//<CHAR|mtype
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SendClientMessage
	return ret;

}
bool
ODABAClientI::SetServerVariable(
		  const ::std::string& varname		//<STRING|var_name
		, const ::std::string& varstring		//<STRING|var_string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetServerVariable
	return ret;

}
bool
ODABAClientI::ShutDown(
		  const ::std::string& closesystem		//<CHAR|close_system
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ShutDown
	return ret;

}
bool
ODABAClientI::StartPause(
		  ::Ice::Int waitsec		//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::StartPause
	return ret;

}
bool
ODABAClientI::StatDisplay(
		  const ::std::string& dbpath		//<STRING|dbpath
		, const ::std::string& ppath		//<STRING|ppath
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::StatDisplay
	return ret;

}
void
ODABAClientI::StopPause(
		  const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::StopPause
	return ret;

}
bool
ODABAClientI::SysInfoDisplay(
		  const ::std::string& dbpath		//<STRING|dbpath
		, const ::std::string& ppath		//<STRING|ppath
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SysInfoDisplay
	return ret;

}
bool
OperationHandleI::CheckExpression(
		  const ::Odaba::DictionaryHandlePrx& dictptr		//<DictionaryHandle|dictptr
		, const ::std::string& expression		//<STRING|expression
		, const ::Odaba::DBObjectHandlePrx& obhandle		//<DBObjectHandle|obhandle
		, const ::std::string& clsnames		//<STRING|clsnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckExpression
	return ret;

}
bool
OperationHandleI::CheckExpressionInClass(
		  const ::Odaba::DictionaryHandlePrx& dictptr		//<DictionaryHandle|dictptr
		, const ::Odaba::DBObjectHandlePrx& resobj		//<DBObjectHandle|resobj
		, const ::std::string& clsnames		//<STRING|clsnames
		, const ::std::string& exprnames		//<STRING|exprnames
		, const ::std::string& impnames		//<STRING|impnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckExpression
	return ret;

}
bool
OperationHandleI::Execute(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Execute
	return ret;

}
::Odaba::PropertyHandlePrx
OperationHandleI::GetResult(
		  const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::GetResult
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Ice::Int
OperationHandleI::GetSize(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetSize
	return ret;

}
bool
OperationHandleI::IsValid(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsValid
	return ret;

}
bool
OperationHandleI::Open(
		  const ::Odaba::PropertyHandlePrx& prophdlref		//<PropertyHandle|prophdl_ref
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
OperationHandleI::ProvideExpression(
		  const ::Odaba::DictionaryHandlePrx& dictionary		//<DictionaryHandle|dictionary
		, const ::Odaba::DBObjectHandlePrx& resobj		//<DBObjectHandle|resobj
		, const ::Odaba::DBObjectHandlePrx& obhandle		//<DBObjectHandle|obhandle
		, const ::std::string& expression		//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ProvideExpression
	return ret;

}
bool
PropertyHandleI::Add(
		  ::Ice::Int setpos0		//<INT|set_pos0
		, const ::std::string& sortkey		//<Key|sortkey
		, const ::std::string& identkeyw		//<Key|identkey_w
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Add
	return ret;

}
bool
PropertyHandleI::AddByKey(
		  const ::std::string& sortkey		//<Key|sortkey
		, const ::std::string& identkeyw		//<Key|identkey_w
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Add
	return ret;

}
bool
PropertyHandleI::AddInstance(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Add
	return ret;

}
bool
PropertyHandleI::AddOnPosition(
		  ::Ice::Int setpos0w		//<INT|set_pos0_w
		, bool initinst		//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Add
	return ret;

}
bool
PropertyHandleI::AddGlobal(
		  ::Ice::Int setpos0		//<INT|set_pos0
		, const ::std::string& sortkey		//<Key|sortkey
		, const ::std::string& identkeyw		//<Key|identkey_w
		, bool initinst		//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::AddGlobal
	return ret;

}
bool
PropertyHandleI::AddGlobalByKey(
		  const ::std::string& sortkey		//<Key|sortkey
		, const ::std::string& identkeyw		//<Key|identkey_w
		, bool initinst		//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::AddGlobal
	return ret;

}
bool
PropertyHandleI::AddGlobalOnPosition(
		  ::Ice::Int setpos0w		//<INT|set_pos0_w
		, bool initinst		//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::AddGlobal
	return ret;

}
bool
PropertyHandleI::AddReference(
		  const ::Odaba::PropertyHandlePrx& sourcehandle		//<PropertyHandle|source_handle
		, ::Ice::Int setpos0w		//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::AddReference
	return ret;

}
bool
PropertyHandleI::AllocDescription(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::AllocDescription
	return ret;

}
bool
PropertyHandleI::AllocateArea(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::AllocateArea
	return ret;

}
bool
PropertyHandleI::AppendString(
		  const ::std::string& string		//<STRING|string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::AppendString
	return ret;

}
bool
PropertyHandleI::AutoLocate(
		  const ::std::string& chkopt		//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::AutoLocate
	return ret;

}
bool
PropertyHandleI::Cancel(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Cancel
	return ret;

}
bool
PropertyHandleI::CancelBuffer(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CancelBuffer
	return ret;

}
::Ice::Int
PropertyHandleI::ChangeBuffer(
		  ::Ice::Int buffnum		//<INT|buffnum
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::ChangeBuffer
	return ret;

}
bool
PropertyHandleI::ChangeCache(
		  ::Ice::Int buffnum		//<INT|buffnum
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ChangeCache
	return ret;

}
::Odaba::PIACC
PropertyHandleI::ChangeMode(
		  ::Odaba::PIACC newmode		//<PIACC|newmode
		, const ::Ice::Current& current //< ice default

	)
{
	::Odaba::PIACC ret;
	ret=enumcpp2ice((PIACC)::ChangeMode
	return ret;

}
bool
PropertyHandleI::Check(
		  bool iniopt		//<LOGICAL|ini_opt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Check
	return ret;

}
bool
PropertyHandleI::CheckPosition(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckPosition
	return ret;

}
bool
PropertyHandleI::CheckUpdate(
		  bool checkupdate		//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckUpdate
	return ret;

}
bool
PropertyHandleI::CheckWProtect(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CheckWProtect
	return ret;

}
bool
PropertyHandleI::Close(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Close
	return ret;

}
::Ice::Int
PropertyHandleI::Compare(
		  const ::Odaba::PropertyHandlePrx& cprophdl		//<PropertyHandle|cprop_hdl
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::Compare
	return ret;

}
::Ice::Int
PropertyHandleI::CompareDate(
		  ::Ice::Long dateval		//<dbdt|date_val
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::Compare
	return ret;

}
::Ice::Int
PropertyHandleI::CompareFloat(
		  ::Ice::Float doubleval		//<REAL|double_val
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::Compare
	return ret;

}
::Ice::Int
PropertyHandleI::CompareInteger(
		  ::Ice::Int longval		//<INT|long_val
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::Compare
	return ret;

}
::Ice::Int
PropertyHandleI::CompareString(
		  const ::std::string& string		//<STRING|string
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::Compare
	return ret;

}
::Ice::Int
PropertyHandleI::CompareTime(
		  ::Ice::Long timeval		//<dbtm|time_val
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::Compare
	return ret;

}
::Ice::Int
PropertyHandleI::CompareKey(
		  const ::std::string& identkey1		//<Key|ident_key1
		, const ::std::string& identkey2		//<Key|ident_key2
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::CompareKey
	return ret;

}
::Ice::Int
PropertyHandleI::CompareSortKey(
		  const ::std::string& sortkey1		//<Key|sort_key1
		, const ::std::string& sortkey2		//<Key|sort_key2
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::CompareSortKey
	return ret;

}
bool
PropertyHandleI::CompareType(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prop_hdl
		, bool convert		//<LOGICAL|convert
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CompareType
	return ret;

}
bool
PropertyHandleI::Copy(
		  const ::Odaba::PropertyHandlePrx& sourcehandle		//<PropertyHandle|source_handle
		, const ::std::string& newkey		//<Key|new_key
		, ::Ice::Int setpos0		//<INT|set_pos0
		, ::Odaba::PIREPL replopt		//<PIREPL|replopt
		, ::Odaba::PIREPL copytype		//<PIREPL|copy_type
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Copy
	return ret;

}
bool
PropertyHandleI::CopyData(
		  const ::Odaba::PropertyHandlePrx& sourcehandle		//<PropertyHandle|source_handle
		, ::Odaba::PIREPL replopt		//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CopyData
	return ret;

}
bool
PropertyHandleI::CopyHandle(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CopyHandle
	return ret;

}
bool
PropertyHandleI::CopyInstanceArea(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prophdl
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CopyInstanceArea
	return ret;

}
::Ice::Int
PropertyHandleI::CopySet(
		  const ::Odaba::PropertyHandlePrx& csourcehandle		//<PropertyHandle|csource_handle
		, ::Odaba::PIREPL replopt		//<PIREPL|replopt
		, ::Odaba::PIREPL copytype		//<PIREPL|copy_type
		, bool inversecheck		//<LOGICAL|inverse_check
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::CopySet
	return ret;

}
bool
PropertyHandleI::CreateTempExtent(
		  const ::Odaba::PropertyHandlePrx& prophdlref		//<PropertyHandle|prophdl_ref
		, const ::std::string& extnamesw		//<STRING|extnames_w
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::CreateTempExtent
	return ret;

}
bool
PropertyHandleI::Delete(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Delete
	return ret;

}
bool
PropertyHandleI::DeleteByKey(
		  const ::std::string& sortkey		//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Delete
	return ret;

}
bool
PropertyHandleI::DeleteOnPosition(
		  ::Ice::Int setpos0w		//<INT|set_pos0_w
		, bool deldep		//<LOGICAL|del_dep
		, bool delinst		//<LOGICAL|del_inst
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Delete
	return ret;

}
bool
PropertyHandleI::DeleteIndexEntry(
		  ::Ice::Int setpos0		//<INT|set_pos0
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::DeleteIndexEntry
	return ret;

}
bool
PropertyHandleI::DeleteSet(
		  bool deldep		//<LOGICAL|del_dep
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::DeleteSet
	return ret;

}
bool
PropertyHandleI::DisableKeyCheck(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::DisableKeyCheck
	return ret;

}
bool
PropertyHandleI::Duplicate(
		  ::Ice::Int setpos0		//<INT|set_pos0
		, ::Odaba::PIREPL replopt		//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Duplicate
	return ret;

}
bool
PropertyHandleI::DuplicateKey(
		  const ::std::string& identkey		//<Key|ident_key
		, ::Odaba::PIREPL replopt		//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Duplicate
	return ret;

}
bool
PropertyHandleI::EnableKeyCheck(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::EnableKeyCheck
	return ret;

}
bool
PropertyHandleI::Execute(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Execute
	return ret;

}
::Odaba::PropertyHandlePrx
PropertyHandleI::ExecuteExpression(
		  const ::Odaba::DBObjectHandlePrx& resobhandle		//<DBObjectHandle|res_obhandle
		, const ::Odaba::DBObjectHandlePrx& obhandle		//<DBObjectHandle|obhandle
		, const ::std::string& expression		//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::ExecuteExpression
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
PropertyHandleI::ExecuteInstanceAction(
		  const ::std::string& actionname		//<CHAR|action_name
		, const ::std::string& parmstring		//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ExecuteInstanceAction
	return ret;

}
bool
PropertyHandleI::ExecutePropertyAction(
		  const ::std::string& actionname		//<CHAR|action_name
		, const ::std::string& parmstring		//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ExecutePropertyAction
	return ret;

}
bool
PropertyHandleI::Exist(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Exist
	return ret;

}
::std::string
PropertyHandleI::ExtractKey(
		  const ::std::string& keyname		//<STRING|key_name
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::ExtractKey
	return ret;

}
::std::string
PropertyHandleI::ExtractSortKey(
		  const ::std::string& sortkeyw		//<Key|sort_key_w
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::ExtractSortKey
	return ret;

}
::std::string
PropertyHandleI::FirstKey(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::FirstKey
	return ret;

}
bool
PropertyHandleI::Get(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Get
	return ret;

}
bool
PropertyHandleI::GetAtPosition(
		  ::Ice::Int setpos0w		//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Get
	return ret;

}
bool
PropertyHandleI::GetByKey(
		  const ::std::string& sortkey		//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Get
	return ret;

}
::std::string
PropertyHandleI::GetActionResult(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetActionResult
	return ret;

}
::std::string
PropertyHandleI::GetArea(
		  const ::std::string& chkopt		//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetArea
	return ret;

}
::std::string
PropertyHandleI::GetAttribute(
		  ::Ice::Int indx0		//<INT|indx0
		, bool fullpath		//<LOGICAL|full_path
		, bool generic		//<LOGICAL|generic
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetAttribute
	return ret;

}
::Odaba::PropertyHandlePrx
PropertyHandleI::GetBaseProperty(
		  const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::GetBaseProperty
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Ice::Int
PropertyHandleI::GetCollectionID(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetCollectionID
	return ret;

}
::Odaba::PropertyHandlePrx
PropertyHandleI::GetCollectionProperty(
		  const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::GetCollectionProperty
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Ice::Int
PropertyHandleI::GetCount(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetCount
	return ret;

}
::Ice::Int
PropertyHandleI::GetCurrentIndex(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetCurrentIndex
	return ret;

}
::Ice::Int
PropertyHandleI::GetCurrentSize(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetCurrentSize
	return ret;

}
::std::string
PropertyHandleI::GetCurrentType(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetCurrentType
	return ret;

}
::Odaba::DatabaseHandlePrx
PropertyHandleI::GetDBHandle(
		  const ::Ice::Current& current //< ice default

	)
{
	DatabaseHandleIPtr ret;
	ret=new DatabaseHandleI(::GetDBHandle
	return Odaba::DatabaseHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Ice::Long
PropertyHandleI::GetDate(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	dbdt ret;
	ret=::GetDate
	return ret;

}
::Ice::Long
PropertyHandleI::GetDateTime(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	dttm ret;
	ret=::GetDateTime
	return ret;

}
::Ice::Int
PropertyHandleI::GetDay(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetDay
	return ret;

}
::Odaba::DictionaryHandlePrx
PropertyHandleI::GetDictionary(
		  const ::Ice::Current& current //< ice default

	)
{
	DictionaryHandleIPtr ret;
	ret=new DictionaryHandleI(::GetDictionary
	return Odaba::DictionaryHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Ice::Int
PropertyHandleI::GetDimension(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetDimension
	return ret;

}
::Ice::Float
PropertyHandleI::GetDouble(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	float ret;
	ret=::GetDouble
	return ret;

}
::Ice::Int
PropertyHandleI::GetExtInstModCount(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetExtInstModCount
	return ret;

}
::std::string
PropertyHandleI::GetExtentName(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetExtentName
	return ret;

}
::std::string
PropertyHandleI::GetGUID(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetGUID
	return ret;

}
::Ice::Int
PropertyHandleI::GetGenAttrType(
		  const ::std::string& wpropnames		//<STRING|w_propnames
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetGenAttrType
	return ret;

}
::Ice::Int
PropertyHandleI::GetGenOrderType(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetGenOrderType
	return ret;

}
::Ice::Int
PropertyHandleI::GetGlobalID(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetGlobalID
	return ret;

}
::Ice::Int
PropertyHandleI::GetHours(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetHours
	return ret;

}
::Ice::Int
PropertyHandleI::GetID(
		  ::Ice::Int setpos0w		//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetID
	return ret;

}
::std::string
PropertyHandleI::GetIdentity(
		  const ::std::string& idstring		//<STRING|id_string
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetIdentity
	return ret;

}
::std::string
PropertyHandleI::GetIndexName(
		  ::Ice::Int indx0		//<INT|indx0
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetIndexName
	return ret;

}
bool
PropertyHandleI::GetInitInstance(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::GetInitInstance
	return ret;

}
::Ice::Int
PropertyHandleI::GetInstModCount(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetInstModCount
	return ret;

}
::Ice::Int
PropertyHandleI::GetInt(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetInt
	return ret;

}
::Ice::Int
PropertyHandleI::GetIntValue(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetIntValue
	return ret;

}
::std::string
PropertyHandleI::GetKey(
		  ::Ice::Int setpos0w		//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetKey
	return ret;

}
::Ice::Int
PropertyHandleI::GetKeyLength(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetKeyLength
	return ret;

}
::Ice::Int
PropertyHandleI::GetLOID(
		  ::Ice::Int setpos0w		//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetLOID
	return ret;

}
::Ice::Int
PropertyHandleI::GetLOIDByKey(
		  const ::std::string& sortkey		//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetLOID
	return ret;

}
::Ice::Int
PropertyHandleI::GetMinutes(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetMinutes
	return ret;

}
::Odaba::PIACC
PropertyHandleI::GetMode(
		  const ::Ice::Current& current //< ice default

	)
{
	::Odaba::PIACC ret;
	ret=enumcpp2ice((PIACC)::GetMode
	return ret;

}
::Ice::Int
PropertyHandleI::GetMonth(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetMonth
	return ret;

}
::Ice::Int
PropertyHandleI::GetNormalized(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetNormalized
	return ret;

}
::Odaba::DBObjectHandlePrx
PropertyHandleI::GetObjectHandle(
		  const ::Ice::Current& current //< ice default

	)
{
	DBObjectHandleIPtr ret;
	ret=new DBObjectHandleI(::GetObjectHandle
	return Odaba::DBObjectHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Ice::Int
PropertyHandleI::GetOrigin(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetOrigin
	return ret;

}
::Odaba::PropertyHandlePrx
PropertyHandleI::GetParentProperty(
		  const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::GetParentProperty
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::PropertyHandlePrx
PropertyHandleI::GetPropertyHandle(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::GetPropertyHandle
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::std::string
PropertyHandleI::GetPropertyPath(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetPropertyPath
	return ret;

}
::Ice::Int
PropertyHandleI::GetRefModCount(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetRefModCount
	return ret;

}
::std::string
PropertyHandleI::GetReference(
		  ::Ice::Int indx0		//<INT|indx0
		, bool fullpath		//<LOGICAL|full_path
		, bool generic		//<LOGICAL|generic
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetReference
	return ret;

}
bool
PropertyHandleI::GetRelative(
		  ::Ice::Int setpos0w		//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::GetRelative
	return ret;

}
::Ice::Int
PropertyHandleI::GetRelativeCount(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetRelativeCount
	return ret;

}
::Ice::Int
PropertyHandleI::GetRelativeIndex(
		  bool lastopt		//<LOGICAL|last_opt
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetRelativeIndex
	return ret;

}
::Ice::Int
PropertyHandleI::GetSeconds(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetSeconds
	return ret;

}
::std::string
PropertyHandleI::GetSelectedKey(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetSelectedKey
	return ret;

}
::Ice::Int
PropertyHandleI::GetSize(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetSize
	return ret;

}
::Ice::Int
PropertyHandleI::GetSizeOf(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetSizeOf
	return ret;

}
::std::string
PropertyHandleI::GetSortKey(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetSortKey
	return ret;

}
::Ice::Int
PropertyHandleI::GetSortKeyLength(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetSortKeyLength
	return ret;

}
::std::string
PropertyHandleI::GetString(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetString
	return ret;

}
::Ice::Int
PropertyHandleI::GetStringLength(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetStringLength
	return ret;

}
::std::string
PropertyHandleI::GetStringValue(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetStringValue
	return ret;

}
::std::string
PropertyHandleI::GetSubString(
		  ::Ice::Int startpos		//<INT|start_pos
		, ::Ice::Int length		//<INT|length
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetSubString
	return ret;

}
::std::string
PropertyHandleI::GetText(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetText
	return ret;

}
::Ice::Long
PropertyHandleI::GetTime(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	dbtm ret;
	ret=::GetTime
	return ret;

}
::std::string
PropertyHandleI::GetType(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::GetType
	return ret;

}
bool
PropertyHandleI::GetValid(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::GetValid
	return ret;

}
::Ice::Int
PropertyHandleI::GetVersion(
		  const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetVersion
	return ret;

}
::Ice::Int
PropertyHandleI::GetYear(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::GetYear
	return ret;

}
::Odaba::PropertyHandlePrx
PropertyHandleI::Group(
		  const ::Odaba::PropertyHandlePrx& prophdlref		//<PropertyHandle|prophdl_ref
		, const ::std::string& groupingrule		//<STRING|grouping_rule
		, bool distinct		//<LOGICAL|distinct
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::Group
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
PropertyHandleI::HasData(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::HasData
	return ret;

}
bool
PropertyHandleI::HasDescription(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::HasDescription
	return ret;

}
bool
PropertyHandleI::HasGenericAttributes(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::HasGenericAttributes
	return ret;

}
bool
PropertyHandleI::HasIndex(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::HasIndex
	return ret;

}
bool
PropertyHandleI::Inherits(
		  const ::std::string& strnames		//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Inherits
	return ret;

}
bool
PropertyHandleI::InsertString(
		  const ::std::string& string		//<STRING|string
		, ::Ice::Int position		//<INT|position
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::InsertString
	return ret;

}
bool
PropertyHandleI::InsertTerminator(
		  const ::std::string& string		//<STRING|string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::InsertTerminator
	return ret;

}
bool
PropertyHandleI::InstanceInserted(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::InstanceInserted
	return ret;

}
::std::string
PropertyHandleI::InstanceToString(
		  const ::std::string& stringsep		//<STRING|string_sep
		, const ::std::string& fieldsep		//<STRING|field_sep
		, const ::std::string& blocksep		//<STRING|block_sep
		, const ::std::string& emptystring		//<STRING|empty_string
		, bool skiptrans		//<LOGICAL|skip_trans
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::InstanceToString
	return ret;

}
::Odaba::PropertyHandlePrx
PropertyHandleI::Intersect(
		  const ::Odaba::PropertyHandlePrx& prophdl1		//<PropertyHandle|prop_hdl1
		, const ::Odaba::PropertyHandlePrx& prophdl2		//<PropertyHandle|prop_hdl2
		, const ::std::string& skopt		//<CHAR|sk_opt
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::Intersect
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
PropertyHandleI::Is(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Is
	return ret;

}
bool
PropertyHandleI::IsA(
		  const ::std::string& strnames		//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsA
	return ret;

}
bool
PropertyHandleI::IsActive(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsActive
	return ret;

}
bool
PropertyHandleI::IsAttribute(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsAttribute
	return ret;

}
bool
PropertyHandleI::IsAutoSelection(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsAutoSelection
	return ret;

}
bool
PropertyHandleI::IsBasedOn(
		  const ::std::string& strnames		//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsBasedOn
	return ret;

}
bool
PropertyHandleI::IsBasetypeProperty(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsBasetypeProperty
	return ret;

}
bool
PropertyHandleI::IsBasicType(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsBasicType
	return ret;

}
bool
PropertyHandleI::IsClient(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsClient
	return ret;

}
bool
PropertyHandleI::IsCollection(
		  const ::std::string& chkopt		//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsCollection
	return ret;

}
bool
PropertyHandleI::IsCollectionUpdate(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsCollectionUpdate
	return ret;

}
bool
PropertyHandleI::IsCopyHandle(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsCopyHandle
	return ret;

}
bool
PropertyHandleI::IsDirty(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsDirty
	return ret;

}
bool
PropertyHandleI::IsEmpty(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsEmpty
	return ret;

}
bool
PropertyHandleI::IsEnumeration(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsEnumeration
	return ret;

}
bool
PropertyHandleI::IsGenericAttribute(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsGenericAttribute
	return ret;

}
bool
PropertyHandleI::IsInitInstance(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsInitInstance
	return ret;

}
bool
PropertyHandleI::IsMemo(
		  const ::std::string& chkopt		//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsMemo
	return ret;

}
bool
PropertyHandleI::IsModified(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsModified
	return ret;

}
bool
PropertyHandleI::IsNewInstance(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsNewInstance
	return ret;

}
bool
PropertyHandleI::IsNumeric(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsNumeric
	return ret;

}
bool
PropertyHandleI::IsOldInstance(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsOldInstance
	return ret;

}
bool
PropertyHandleI::IsOwner(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsOwner
	return ret;

}
bool
PropertyHandleI::IsPositioned(
		  const ::std::string& chkopt		//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsPositioned
	return ret;

}
bool
PropertyHandleI::IsReadOnly(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsReadOnly
	return ret;

}
bool
PropertyHandleI::IsSelected(
		  const ::std::string& chkopt		//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsSelected
	return ret;

}
bool
PropertyHandleI::IsSensitive(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsSensitive
	return ret;

}
bool
PropertyHandleI::IsServer(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsServer
	return ret;

}
bool
PropertyHandleI::IsShareBaseHandle(
		  const ::std::string& chkopt		//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsShareBaseHandle
	return ret;

}
bool
PropertyHandleI::IsStructure(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsStructure
	return ret;

}
bool
PropertyHandleI::IsText(
		  const ::std::string& chkopt		//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsText
	return ret;

}
bool
PropertyHandleI::IsTransient(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsTransient
	return ret;

}
bool
PropertyHandleI::IsTrue(
		  const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsTrue
	return ret;

}
bool
PropertyHandleI::IsTyped(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsTyped
	return ret;

}
bool
PropertyHandleI::IsUserHandle(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsUserHandle
	return ret;

}
bool
PropertyHandleI::IsValid(
		  bool topt		//<LOGICAL|topt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsValid
	return ret;

}
bool
PropertyHandleI::IsValidText(
		  const ::std::string& string		//<STRING|string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsValidText
	return ret;

}
bool
PropertyHandleI::IsVariableType(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsVariableType
	return ret;

}
bool
PropertyHandleI::IsWeakTyped(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsWeakTyped
	return ret;

}
bool
PropertyHandleI::IsWrite(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::IsWrite
	return ret;

}
bool
PropertyHandleI::Locate(
		  ::Ice::Int obident		//<INT|obident
		, bool readopt		//<LOGICAL|read_opt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Locate
	return ret;

}
bool
PropertyHandleI::LocatePath(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::LocatePath
	return ret;

}
bool
PropertyHandleI::Lock(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Lock
	return ret;

}
bool
PropertyHandleI::LockSet(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::LockSet
	return ret;

}
void
PropertyHandleI::MarkUnused(
		  const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::MarkUnused
	return ret;

}
void
PropertyHandleI::MarkUsed(
		  const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::MarkUsed
	return ret;

}
::Odaba::PropertyHandlePrx
PropertyHandleI::Minus(
		  const ::Odaba::PropertyHandlePrx& prophdl1		//<PropertyHandle|prop_hdl1
		, const ::Odaba::PropertyHandlePrx& prophdl2		//<PropertyHandle|prop_hdl2
		, const ::std::string& skopt		//<CHAR|sk_opt
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::Minus
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
PropertyHandleI::Modify(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Modify
	return ret;

}
bool
PropertyHandleI::Move(
		  const ::Odaba::PropertyHandlePrx& sourcehandle		//<PropertyHandle|source_handle
		, const ::std::string& newkey		//<Key|new_key
		, ::Odaba::PIREPL replopt		//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Move
	return ret;

}
bool
PropertyHandleI::MoveDown(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::MoveDown
	return ret;

}
bool
PropertyHandleI::MoveUp(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::MoveUp
	return ret;

}
::std::string
PropertyHandleI::NextKey(
		  const ::std::string& sortkeyw		//<Key|sort_key_w
		, ::Ice::Int switchlevel		//<INT|switch_level
		, const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::NextKey
	return ret;

}
bool
PropertyHandleI::NoWrite(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::NoWrite
	return ret;

}
bool
PropertyHandleI::Open(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenBigInt(
		  ::Ice::Int int64val		//<INT|int64_val
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenBoolean(
		  bool logval		//<LOGICAL|logval
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenChild(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prop_hdl
		, const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenChildReference(
		  const ::Odaba::PropertyHandlePrx& propertyhandle		//<PropertyHandle|property_handle
		, const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenCopy(
		  const ::Odaba::PropertyHandlePrx& cprophdl		//<PropertyHandle|cprop_hdl
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenDate(
		  ::Ice::Long dateval		//<dbdt|date_val
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenExtent(
		  const ::Odaba::DBObjectHandlePrx& objecthandle		//<DBObjectHandle|object_handle
		, const ::std::string& extnames		//<STRING|extnames
		, ::Odaba::PIACC accopt		//<PIACC|accopt
		, bool transientw		//<LOGICAL|transient_w
		, const ::std::string& keynamew		//<CHAR|key_name_w
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenFloat(
		  ::Ice::Float dblvalue		//<REAL|dbl_value
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenInteger(
		  ::Ice::Int intval		//<INT|int_val
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenReference(
		  const ::Odaba::PropertyHandlePrx& propertyhandle		//<PropertyHandle|property_handle
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenSizedString(
		  const ::std::string& string		//<STRING|string
		, ::Ice::Int stringlen		//<INT|string_len
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenString(
		  const ::std::string& string		//<STRING|string
		, bool convopt		//<LOGICAL|conv_opt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenTime(
		  ::Ice::Long timeval		//<dbtm|time_val
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenTimestamp(
		  ::Ice::Long datetimeval		//<dttm|datetime_val
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Open
	return ret;

}
bool
PropertyHandleI::OpenHierarchy(
		  const ::Odaba::PropertyHandlePrx& bottomph		//<PropertyHandle|bottom_ph
		, const ::Odaba::PropertyHandlePrx& topph		//<PropertyHandle|top_ph
		, bool pathopt		//<LOGICAL|path_opt
		, ::Odaba::PIACC accmode		//<PIACC|accmode
		, bool copyselection		//<LOGICAL|copy_selection
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::OpenHierarchy
	return ret;

}
bool
PropertyHandleI::OwnsData(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::OwnsData
	return ret;

}
bool
PropertyHandleI::Position(
		  ::Ice::Int count		//<INT|count
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Position
	return ret;

}
bool
PropertyHandleI::PositionTop(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::PositionTop
	return ret;

}
::Odaba::PropertyHandlePrx
PropertyHandleI::Power(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::Power
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
PropertyHandleI::ProvGenAttribute(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ProvGenAttribute
	return ret;

}
bool
PropertyHandleI::Provide(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Provide
	return ret;

}
bool
PropertyHandleI::ProvideAtPosition(
		  ::Ice::Int setpos0w		//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Provide
	return ret;

}
bool
PropertyHandleI::ProvideByKey(
		  const ::std::string& sortkey		//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Provide
	return ret;

}
bool
PropertyHandleI::ProvideArea(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ProvideArea
	return ret;

}
::std::string
PropertyHandleI::ProvideGUID(
		  const ::Ice::Current& current //< ice default

	)
{
	char* ret;
	ret=::ProvideGUID
	return ret;

}
bool
PropertyHandleI::ProvideGlobal(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ProvideGlobal
	return ret;

}
bool
PropertyHandleI::ProvideGlobalAtPosition(
		  ::Ice::Int setpos0w		//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ProvideGlobal
	return ret;

}
bool
PropertyHandleI::ProvideGlobalByKey(
		  const ::std::string& sortkey		//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ProvideGlobal
	return ret;

}
::Odaba::OperationHandlePrx
PropertyHandleI::ProvideOperation(
		  const ::std::string& expression		//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{
	OperationHandleIPtr ret;
	ret=new OperationHandleI(::ProvideOperation
	return Odaba::OperationHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
PropertyHandleI::Refresh(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Refresh
	return ret;

}
bool
PropertyHandleI::ReleaseBuffer(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ReleaseBuffer
	return ret;

}
bool
PropertyHandleI::RemoveFromCollection(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::RemoveFromCollection
	return ret;

}
bool
PropertyHandleI::RemoveString(
		  const ::std::string& string		//<STRING|string
		, ::Ice::Int position		//<INT|position
		, ::Ice::Int len		//<INT|len
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::RemoveString
	return ret;

}
bool
PropertyHandleI::RemoveTerminator(
		  const ::std::string& string		//<STRING|string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::RemoveTerminator
	return ret;

}
bool
PropertyHandleI::Rename(
		  const ::std::string& newkey		//<Key|new_key
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Rename
	return ret;

}
bool
PropertyHandleI::RepairIndex(
		  const ::std::string& keynamew		//<CHAR|key_name_w
		, const ::std::string& attrstrw		//<STRING|attrstr_w
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::RepairIndex
	return ret;

}
bool
PropertyHandleI::ReplaceString(
		  const ::std::string& oldstr		//<STRING|old_str
		, const ::std::string& newstr		//<STRING|new_str
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ReplaceString
	return ret;

}
bool
PropertyHandleI::ReplaceSysVariables(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ReplaceSysVariables
	return ret;

}
bool
PropertyHandleI::Reset(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Reset
	return ret;

}
void
PropertyHandleI::ResetDirty(
		  const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::ResetDirty
	return ret;

}
bool
PropertyHandleI::ResetTransientProperty(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ResetTransientProperty
	return ret;

}
bool
PropertyHandleI::ResetWProtect(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ResetWProtect
	return ret;

}
bool
PropertyHandleI::Save(
		  const ::std::string& savopt		//<CHAR|savopt
		, bool switchopt		//<LOGICAL|switchopt
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Save
	return ret;

}
::Ice::Int
PropertyHandleI::SearchText(
		  const ::std::string& string		//<STRING|string
		, ::Ice::Int curpos		//<INT|curpos
		, bool caseopt		//<LOGICAL|case_opt
		, const ::Ice::Current& current //< ice default

	)
{
	int ret;
	ret=::SearchText
	return ret;

}
::Odaba::PropertyHandlePrx
PropertyHandleI::Select(
		  const ::Odaba::PropertyHandlePrx& prophdlref		//<PropertyHandle|prophdl_ref
		, const ::std::string& expression		//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::Select
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
void
PropertyHandleI::SetActionResult(
		  const ::std::string& resultstring		//<STRING|result_string
		, const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::SetActionResult
	return ret;

}
bool
PropertyHandleI::SetContextVariables(
		  const ::std::string& contextstring		//<STRING|context_string
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetContextVariables
	return ret;

}
void
PropertyHandleI::SetDirty(
		  const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::SetDirty
	return ret;

}
bool
PropertyHandleI::SetDynLength(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetDynLength
	return ret;

}
bool
PropertyHandleI::SetGenAttribute(
		  const ::std::string& attrstr		//<STRING|attrstr
		, const ::std::string& proppath		//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetGenAttribute
	return ret;

}
bool
PropertyHandleI::SetKey(
		  const ::std::string& identkey		//<Key|ident_key
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetKey
	return ret;

}
void
PropertyHandleI::SetModified(
		  const ::Ice::Current& current //< ice default

	)
{
	void ret;
	ret=::SetModified
	return ret;

}
bool
PropertyHandleI::SetNormalized(
		  ::Ice::Int longval		//<INT|long_val
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetNormalized
	return ret;

}
bool
PropertyHandleI::SetOrder(
		  const ::std::string& keyname		//<STRING|key_name
		, const ::std::string& attrstr		//<STRING|attrstr
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetOrder
	return ret;

}
bool
PropertyHandleI::SetSelection(
		  const ::std::string& expression		//<STRING|expression
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetSelection
	return ret;

}
bool
PropertyHandleI::SetSortKey(
		  const ::std::string& sortkey		//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetSortKey
	return ret;

}
bool
PropertyHandleI::SetTransientProperty(
		  const ::Odaba::PropertyHandlePrx& prophdl		//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetTransientProperty
	return ret;

}
bool
PropertyHandleI::SetType(
		  const ::std::string& strnames		//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetType
	return ret;

}
bool
PropertyHandleI::SetUpdate(
		  bool checkupdate		//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetUpdate
	return ret;

}
::Odaba::PropertyHandlePrx
PropertyHandleI::SetValue(
		  const ::Odaba::PropertyHandlePrx& cprophdl		//<PropertyHandle|cprop_hdl
		, bool checkupdate		//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::SetValue
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::PropertyHandlePrx
PropertyHandleI::SetValueBigInt(
		  ::Ice::Int int64val		//<INT|int64_val
		, bool checkupdate		//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::SetValue
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::PropertyHandlePrx
PropertyHandleI::SetValueBoolean(
		  bool logval		//<LOGICAL|logval
		, bool checkupdate		//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::SetValue
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::PropertyHandlePrx
PropertyHandleI::SetValueDate(
		  ::Ice::Long dateval		//<dbdt|date_val
		, bool checkupdate		//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::SetValue
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::PropertyHandlePrx
PropertyHandleI::SetValueFloat(
		  ::Ice::Float dblvalue		//<REAL|dbl_value
		, bool checkupdate		//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::SetValue
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::PropertyHandlePrx
PropertyHandleI::SetValueInteger(
		  ::Ice::Int longval		//<INT|long_val
		, bool checkupdate		//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::SetValue
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::PropertyHandlePrx
PropertyHandleI::SetValueString(
		  const ::std::string& string		//<STRING|string
		, bool checkupdate		//<LOGICAL|check_update
		, bool convopt		//<LOGICAL|conv_opt
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::SetValue
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::PropertyHandlePrx
PropertyHandleI::SetValueTime(
		  ::Ice::Long timeval		//<dbtm|time_val
		, bool checkupdate		//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::SetValue
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
::Odaba::PropertyHandlePrx
PropertyHandleI::SetValueTimestamp(
		  ::Ice::Long datetimeval		//<dttm|datetime_val
		, bool checkupdate		//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::SetValue
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
PropertyHandleI::SetVersion(
		  ::Ice::Int versionnr		//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetVersion
	return ret;

}
bool
PropertyHandleI::SetWProtect(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::SetWProtect
	return ret;

}
bool
PropertyHandleI::ToTop(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::ToTop
	return ret;

}
::Odaba::PropertyHandlePrx
PropertyHandleI::Union(
		  const ::Odaba::PropertyHandlePrx& prophdl1		//<PropertyHandle|prop_hdl1
		, const ::Odaba::PropertyHandlePrx& prophdl2		//<PropertyHandle|prop_hdl2
		, const ::std::string& skopt		//<CHAR|sk_opt
		, bool distinct		//<LOGICAL|distinct
		, const ::Ice::Current& current //< ice default

	)
{
	PropertyHandleIPtr ret;
	ret=new PropertyHandleI(::Union
	return Odaba::PropertyHandlePrx::uncheckedCast(c.adapter->addWithUUID(ret))
}
bool
PropertyHandleI::Unlock(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::Unlock
	return ret;

}
bool
PropertyHandleI::UnlockSet(
		  const ::Ice::Current& current //< ice default

	)
{
	bool ret;
	ret=::UnlockSet
	return ret;

}
