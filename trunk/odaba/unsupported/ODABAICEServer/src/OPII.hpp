#ifndef OPI_I_H
#define OPI_I_H
#include <OPI.h>
#include <codaba2.h>
#include <enumconv.h>
#include <list>
#include <Ice/Ice.h>
#include <OPIFactoryI.hpp>

class CheckOptionsI;
typedef IceUtil::Handle<CheckOptionsI> CheckOptionsIPtr; //<cast&convert
typedef std::list< ::OPI::CheckOptionsPrx > CheckOptionsPrxList;
/**
 * \brief ICE Interface Class for CheckOptions
 */
class CheckOptionsI : virtual public OPI::CheckOptions, virtual public ::CheckOptions

{

	private:

	OPIFactoryIPtr factory;
	public:
	CheckOptionsI(::CheckOptions &refobj):
		OPI::CheckOptions()
		,::CheckOptions(refobj)
		,factory(NULL)
		{}

	void SetObjectFactory(OPIFactoryIPtr removingfactory);
	virtual bool Initialize(
		  const ::std::string& parmstring			//<STRING|parmstring
		, const ::Ice::Current& current //< ice default

	);

};//class CheckOptionsI

class DBObjectHandleI;
typedef IceUtil::Handle<DBObjectHandleI> DBObjectHandleIPtr; //<cast&convert
typedef std::list< ::OPI::DBObjectHandlePrx > DBObjectHandlePrxList;
/**
 * \brief ICE Interface Class for DBObjectHandle
 */
class DBObjectHandleI : virtual public OPI::DBObjectHandle, virtual public ::DBObjectHandle

{

	private:

	OPIFactoryIPtr factory;
	public:
	DBObjectHandleI(::DBObjectHandle &refobj):
		OPI::DBObjectHandle()
		,::DBObjectHandle(refobj)
		,factory(NULL)
		{}

	void SetObjectFactory(OPIFactoryIPtr removingfactory);
	virtual ::Ice::Int BeginTransaction(
		  bool extTA			//<LOGICAL|ext_TA
		, ::Ice::Int wmaxnum			//<INT|w_maxnum
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ChangeTimeStamp(
		  ::Ice::Int versionnr			//<UINT|version_nr
		, ::Ice::Long timestamp			//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CommitTransaction(
		  ::Ice::Int talevel			//<INT|talevel
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx CreateTempPropertyHandle(
		  const ::OPI::PropertyHandlePrx& prophdlref			//<PropertyHandle|prophdl_ref
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DeleteExtent(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DeleteExtentRef(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	);
	virtual void DisableEventHandling(
		  const ::Ice::Current& current //< ice default

	);
	virtual void EnableEventHandling(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool EventHandling(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool ExecuteDBObjectAction(
		  const ::std::string& actionname			//<CHAR|action_name
		, const ::std::string& parmstring			//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx ExecuteExpression(
		  const ::OPI::DBObjectHandlePrx& resobhandle			//<DBObjectHandle|res_obhandle
		, const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ExtentExist(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PIACC GetAccess(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetActionResult(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DatabaseHandlePrx GetDBHandle(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DataSourceHandlePrx GetDataSource(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DictionaryHandlePrx GetDictionary(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetExtent(
		  ::Ice::Int indx0			//<INT|indx0
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DBObjectHandlePrx GetHighObject(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetObject(
		  ::Ice::Int indx0			//<INT|indx0
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetServerVariable(
		  const ::std::string& varname			//<STRING|var_name
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetSystemVersion(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Long GetTimeStamp(
		  ::Ice::Int versionnr			//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetTransactionLevel(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetVersion(
		  ::Ice::Long timestamp			//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsClient(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsEmpty(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsOpened(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsServer(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsValid(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool NewVersion(
		  ::Ice::Long timestamp			//<dttm|timestamp
		, ::Ice::Int versionnr			//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenObject(
		  const ::OPI::DBObjectHandlePrx& dbobject			//<DBObjectHandle|dbobject
		, const ::std::string& objname			//<CHAR|objname
		, ::OPI::PIACC accopt			//<PIACC|accopt
		, ::Ice::Int versionnr			//<UINT|version_nr
		, ::OPI::ResourceTypes localressources			//<ResourceTypes|local_ressources
		, const ::Ice::Current& current //< ice default

	);
	virtual bool RollBack(
		  ::Ice::Int talevel			//<INT|talevel
		, const ::Ice::Current& current //< ice default

	);
	virtual void SetActionResult(
		  const ::std::string& resultstring			//<STRING|result_string
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int SetOverload(
		  bool overloadopt			//<LOGICAL|overload_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetServerVariable(
		  const ::std::string& varname			//<STRING|var_name
		, const ::std::string& varstring			//<STRING|var_string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetUserDefinedIdentity(
		  bool identityopt			//<LOGICAL|identity_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetVersion(
		  ::Ice::Int versionnr			//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetVersioni1(
		  ::Ice::Long date			//<dbdt|date
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetVersioni2(
		  ::Ice::Long timestamp			//<dttm|timestamp
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int VersionCount(
		  const ::Ice::Current& current //< ice default

	);

};//class DBObjectHandleI

class DataSourceHandleI;
typedef IceUtil::Handle<DataSourceHandleI> DataSourceHandleIPtr; //<cast&convert
typedef std::list< ::OPI::DataSourceHandlePrx > DataSourceHandlePrxList;
/**
 * \brief ICE Interface Class for DataSourceHandle
 */
class DataSourceHandleI : virtual public OPI::DataSourceHandle, virtual public ::DataSourceHandle

{

	private:

	OPIFactoryIPtr factory;
	public:
	DataSourceHandleI(::DataSourceHandle &refobj):
		OPI::DataSourceHandle()
		,::DataSourceHandle(refobj)
		,factory(NULL)
		{}

	void SetObjectFactory(OPIFactoryIPtr removingfactory);
	virtual bool BeginTransaction(
		  bool extta			//<LOGICAL|ext_ta
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Close(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CloseDBObject(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CloseDatabase(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CloseDictionary(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CloseProperty(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CloseResourceDB(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CommitTransaction(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Connect(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Disconnect(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Open(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, ::OPI::PIACC accmod			//<PIACC|acc_mod
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Openi02(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, const ::std::string& inifile			//<STRING|ini_file
		, const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Openi1(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DBObjectHandlePrx OpenDBObject(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DatabaseHandlePrx OpenDatabase(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DictionaryHandlePrx OpenDictionary(
		  ::OPI::PIACC accopt			//<PIACC|accopt
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx OpenProperty(
		  const ::std::string& extname			//<CHAR|extname
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DatabaseHandlePrx OpenResourceDB(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool RollBack(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool SetDBObject(
		  const ::OPI::DBObjectHandlePrx& ohandle			//<DBObjectHandle|ohandle
		, const ::std::string& wobjname			//<STRING|w_objname
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetDataSource(
		  const ::OPI::DataSourceHandlePrx& dbdefptr			//<DataSourceHandle|dbdefptr
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetDatabase(
		  const ::OPI::DatabaseHandlePrx& dbhandle			//<DatabaseHandle|db_handle
		, const ::std::string& wbasepath			//<STRING|w_basepath
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetDictionary(
		  const ::OPI::DictionaryHandlePrx& dictptr			//<DictionaryHandle|dictptr
		, const ::std::string& wdictpath			//<STRING|w_dictpath
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetResourceDB(
		  const ::OPI::DatabaseHandlePrx& dbhandle			//<DatabaseHandle|db_handle
		, const ::std::string& wbasepath			//<STRING|w_basepath
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetVariables(
		  const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Setup(
		  const ::std::string& inifile			//<STRING|ini_file
		, const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetupVariables(
		  const ::std::string& datasourcename			//<STRING|datasource_name
		, const ::Ice::Current& current //< ice default

	);

};//class DataSourceHandleI

class DatabaseHandleI;
typedef IceUtil::Handle<DatabaseHandleI> DatabaseHandleIPtr; //<cast&convert
typedef std::list< ::OPI::DatabaseHandlePrx > DatabaseHandlePrxList;
/**
 * \brief ICE Interface Class for DatabaseHandle
 */
class DatabaseHandleI : virtual public OPI::DatabaseHandle , virtual public DBObjectHandleI, virtual public ::DatabaseHandle

{

	private:

	OPIFactoryIPtr factory;
	public:
	DatabaseHandleI(::DatabaseHandle &refobj):
		OPI::DatabaseHandle()
		,DBObjectHandleI(refobj)
		,::DatabaseHandle(refobj)
		,factory(NULL)
		{}

	virtual bool ActivateShadowBase(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool BackupDB(
		  const ::std::string& target			//<STRING|target
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CheckDB(
		  const ::OPI::CheckOptionsPrx& checkopts			//<CheckOptions|check_opts
		, const ::std::string& source			//<STRING|source
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CheckLicence(
		  const ::std::string& licowner			//<STRING|lic_owner
		, const ::std::string& licnumber			//<CHAR|lic_number
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CloseWorkspace(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool ConsolidateWorkspace(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool DeactivateShadowBase(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool DeleteWorkspace(
		  const ::std::string& wsnames			//<STRING|ws_names
		, const ::std::string& username			//<STRING|user_name
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DisableWorkspace(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool DiscardWorkspace(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool EnableWorkspace(
		  const ::std::string& sdwpath			//<CHAR|sdw_path
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ExecuteDatabaseAction(
		  const ::std::string& actionname			//<CHAR|action_name
		, const ::std::string& parmstring			//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ExistWorkspace(
		  const ::std::string& wsnames			//<STRING|ws_names
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetDatabaseID(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetPath(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetSchemaVersion(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetVersionString(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetWorkspace(
		  const ::std::string& wsroot			//<STRING|ws_root
		, ::Ice::Int wsindex			//<INT|ws_index
		, const ::std::string& username			//<STRING|user_name
		, const ::std::string& wsname			//<STRING|ws_name
		, bool refreshopt			//<LOGICAL|refresh_opt
		, const ::std::string& wsinfo			//<CHAR|ws_info
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IgnoreWriteProtect(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool InitDataArea(
		  ::Ice::Int mbnumber			//<INT|mbnumber
		, ::Ice::Int sbnumber			//<INT|sbnumber
		, ::Ice::Int danumber			//<UINT|danumber
		, const ::std::string& filename			//<STRING|filename
		, ::Ice::Int dasize			//<INT|dasize
		, const ::Ice::Current& current //< ice default

	);
	virtual bool InitMainBase(
		  ::Ice::Int mbnumber			//<INT|mbnumber
		, const ::std::string& filename			//<STRING|filename
		, ::Ice::Int lowEBN			//<INT|lowEBN
		, ::Ice::Int highEBN			//<INT|highEBN
		, ::Ice::Int dasize			//<INT|dasize
		, bool largedb			//<LOGICAL|largedb
		, bool pindep			//<LOGICAL|pindep
		, const ::Ice::Current& current //< ice default

	);
	virtual bool InitSubBase(
		  ::Ice::Int mbnumber			//<INT|mbnumber
		, ::Ice::Int sbnumber			//<INT|sbnumber
		, const ::std::string& filename			//<STRING|filename
		, ::Ice::Int dasize			//<INT|dasize
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsLicenced(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsShared(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool LocateWorkspace(
		  const ::std::string& wsnames			//<STRING|ws_names
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenDatabase(
		  const ::OPI::DictionaryHandlePrx& dicthandle			//<DictionaryHandle|dict_handle
		, const ::std::string& cpath			//<STRING|cpath
		, ::OPI::PIACC accopt			//<PIACC|accopt
		, bool wnetopt			//<LOGICAL|w_netopt
		, bool onlineversion			//<LOGICAL|online_version
		, ::Ice::Int versionnr			//<UINT|version_nr
		, ::OPI::ResourceTypes localressources			//<ResourceTypes|local_ressources
		, bool sysenv			//<LOGICAL|sysenv
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenWorkspace(
		  const ::std::string& wsnames			//<STRING|ws_names
		, const ::std::string& username			//<STRING|user_name
		, bool exclusive			//<LOGICAL|exclusive
		, const ::std::string& wspath			//<STRING|ws_path
		, const ::Ice::Current& current //< ice default

	);
	virtual bool RecreateExtent(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool RestoreDB(
		  const ::std::string& source			//<STRING|source
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetupTypeID(
		  ::Ice::Int sid			//<INT|sid
		, const ::Ice::Current& current //< ice default

	);

};//class DatabaseHandleI

class DictionaryHandleI;
typedef IceUtil::Handle<DictionaryHandleI> DictionaryHandleIPtr; //<cast&convert
typedef std::list< ::OPI::DictionaryHandlePrx > DictionaryHandlePrxList;
/**
 * \brief ICE Interface Class for DictionaryHandle
 */
class DictionaryHandleI : virtual public OPI::DictionaryHandle , virtual public DatabaseHandleI, virtual public ::DictionaryHandle

{

	private:

	OPIFactoryIPtr factory;
	public:
	DictionaryHandleI(::DictionaryHandle &refobj):
		OPI::DictionaryHandle()
		,DBObjectHandleI(refobj)
		,DatabaseHandleI(refobj)
		,::DictionaryHandle(refobj)
		,factory(NULL)
		{}

	virtual ::Ice::Int BaseType(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CheckExpression(
		  const ::std::string& expression			//<STRING|expression
		, const ::OPI::DBObjectHandlePrx& dbobjhandle			//<DBObjectHandle|dbobj_handle
		, const ::std::string& clsnames			//<STRING|clsnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CheckExpressionInClass(
		  const ::OPI::DBObjectHandlePrx& resobj			//<DBObjectHandle|resobj
		, const ::std::string& clsnames			//<STRING|clsnames
		, const ::std::string& exprnames			//<STRING|exprnames
		, const ::std::string& implnames			//<STRING|implnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CheckExtentDef(
		  const ::std::string& scopedname			//<STRING|scoped_name
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CheckValueSet(
		  const ::std::string& scopedname			//<STRING|scoped_name
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CopyCodeset(
		  const ::OPI::DictionaryHandlePrx& srcedicthandle			//<DictionaryHandle|srce_dicthandle
		, const ::std::string& strname			//<CHAR|strname
		, ::Ice::Int namespaceid			//<INT|namespace_id
		, const ::std::string& newnames			//<STRING|newnames
		, ::OPI::PIREPL dbreplace			//<PIREPL|db_replace
		, bool retainSID			//<LOGICAL|retainSID
		, bool retainschemav			//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CopyExtentDef(
		  const ::OPI::DictionaryHandlePrx& srcedicthandle			//<DictionaryHandle|srce_dicthandle
		, const ::std::string& extentname			//<STRING|extentname
		, const ::std::string& newnames			//<STRING|newnames
		, const ::std::string& targstruct			//<STRING|targ_struct
		, bool transaction			//<LOGICAL|transaction
		, bool retainschemav			//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CopyStructure(
		  const ::OPI::DictionaryHandlePrx& srcedicthandle			//<DictionaryHandle|srce_dicthandle
		, const ::std::string& strname			//<CHAR|strname
		, ::Ice::Int namespaceid			//<INT|namespace_id
		, const ::std::string& newnames			//<STRING|newnames
		, const ::std::string& topname			//<CHAR|topname
		, ::OPI::PIREPL dbreplace			//<PIREPL|db_replace
		, bool retainSID			//<LOGICAL|retainSID
		, bool retainschemav			//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CopyType(
		  const ::OPI::DictionaryHandlePrx& srcedicthandle			//<DictionaryHandle|srce_dicthandle
		, const ::std::string& strnames			//<STRING|strnames
		, const ::std::string& newnames			//<STRING|newnames
		, const ::std::string& topname			//<CHAR|topname
		, ::OPI::PIREPL dbreplace			//<PIREPL|db_replace
		, bool retainSID			//<LOGICAL|retainSID
		, bool transaction			//<LOGICAL|transaction
		, bool retainschemav			//<LOGICAL|retain_schemav
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CreateEnum(
		  const ::std::string& enumname			//<STRING|enum_name
		, const ::std::string& basetype			//<STRING|basetype
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string CreateTempExtent(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::std::string& extnamesw			//<STRING|extnames_w
		, const ::std::string& keynamew			//<CHAR|key_name_w
		, const ::std::string& baseextsw			//<STRING|baseexts_w
		, bool weakoptw			//<LOGICAL|weak_opt_w
		, bool ownoptw			//<LOGICAL|own_opt_w
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DeleteEnum(
		  const ::std::string& enumname			//<STRING|enum_name
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string EnumToString(
		  const ::std::string& enumeration			//<STRING|enumeration
		, ::Ice::Int enumval			//<INT|enum_val
		, const ::std::string& pstring			//<STRING|string
		, ::Ice::Int len			//<INT|len
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetLastSchemaVersion(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetTempName(
		  const ::std::string& extnames			//<STRING|extnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsBasicType(
		  const ::std::string& typenames			//<STRING|typenames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenDictionary(
		  const ::OPI::ODABAClientPrx& podabaclient			//<ODABAClient|odaba_client
		, const ::std::string& cpath			//<STRING|cpath
		, ::OPI::PIACC accopt			//<PIACC|accopt
		, bool wnetopt			//<LOGICAL|w_netopt
		, ::Ice::Int versionnr			//<UINT|version_nr
		, ::OPI::ResourceTypes localressources			//<ResourceTypes|local_ressources
		, bool sysenv			//<LOGICAL|sysenv
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int StringToEnum(
		  const ::std::string& enumeration			//<STRING|enumeration
		, const ::std::string& enumstring			//<STRING|enum_string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool UpdateVersion(
		  const ::Ice::Current& current //< ice default

	);

};//class DictionaryHandleI

class ODABAClientI;
typedef IceUtil::Handle<ODABAClientI> ODABAClientIPtr; //<cast&convert
typedef std::list< ::OPI::ODABAClientPrx > ODABAClientPrxList;
/**
 * \brief ICE Interface Class for ODABAClient
 */
class ODABAClientI : virtual public OPI::ODABAClient, virtual public ::ODABAClient

{

	private:

	OPIFactoryIPtr factory;
	public:
	ODABAClientI(::ODABAClient &refobj):
		OPI::ODABAClient()
		,::ODABAClient(refobj)
		,factory(NULL)
		{}

	void SetObjectFactory(OPIFactoryIPtr removingfactory);
	virtual void ActivateGUIMessages(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool BackupDB(
		  const ::std::string& cpath			//<STRING|cpath
		, const ::std::string& target			//<STRING|target
		, ::Ice::Int waitsec			//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CheckDB(
		  const ::std::string& dictpath			//<STRING|dict_path
		, const ::std::string& cpath			//<STRING|cpath
		, const ::OPI::CheckOptionsPrx& checkopts			//<CheckOptions|check_opts
		, const ::std::string& source			//<STRING|source
		, ::Ice::Int waitsec			//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Close(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Connect(
		  const ::std::string& servername			//<STRING|server_name
		, ::Ice::Int hostport			//<UINT|host_port
		, const ::std::string& cachestring			//<STRING|cache_string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DictDisplay(
		  const ::std::string& dbpath			//<STRING|dbpath
		, const ::std::string& ppath			//<STRING|ppath
		, const ::Ice::Current& current //< ice default

	);
	virtual void Disconnect(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Exist(
		  const ::std::string& cpath			//<STRING|cpath
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetDataSource(
		  ::Ice::Int indx0			//<INT|indx0
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetHost(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetPort(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetServerVariable(
		  const ::std::string& varname			//<STRING|var_name
		, const ::Ice::Current& current //< ice default

	);
	virtual void Initialize(
		  const ::std::string& inipath			//<STRING|inipath
		, const ::std::string& applicationname			//<STRING|application_name
		, const ::std::string& progpath			//<STRING|progpath
		, ::OPI::ApplicationTypes applicationtype			//<ApplicationTypes|application_type
		, bool initservices			//<LOGICAL|init_services
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsConnected(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool KillClient(
		  ::Ice::Int clientid			//<INT|client_id
		, ::Ice::Int waitsec			//<INT|wait_sec
		, bool sendmessage			//<LOGICAL|send_message
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Open(
		  const ::std::string& inipath			//<STRING|inipath
		, const ::std::string& applicationname			//<STRING|application_name
		, const ::std::string& progpath			//<STRING|progpath
		, ::OPI::ApplicationTypes applicationtype			//<ApplicationTypes|application_type
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DBObjectHandlePrx OpenDataSource(
		  const ::std::string& datasourcename			//<STRING|datasource_name
		, ::OPI::PIACC accopt			//<PIACC|accopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool PackDatabase(
		  const ::std::string& cpath			//<STRING|cpath
		, const ::std::string& temppath			//<STRING|temp_path
		, const ::Ice::Current& current //< ice default

	);
	virtual bool RestoreDB(
		  const ::std::string& cpath			//<STRING|cpath
		, const ::std::string& source			//<STRING|source
		, ::Ice::Int waitsec			//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SendClientMessage(
		  ::Ice::Int clientid			//<INT|client_id
		, const ::std::string& mtext			//<STRING|mtext
		, const ::std::string& mtitle			//<STRING|mtitle
		, const ::std::string& mtype			//<CHAR|mtype
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetServerVariable(
		  const ::std::string& varname			//<STRING|var_name
		, const ::std::string& varstring			//<STRING|var_string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ShutDown(
		  const ::std::string& closesystem			//<CHAR|close_system
		, const ::Ice::Current& current //< ice default

	);
	virtual bool StartPause(
		  ::Ice::Int waitsec			//<INT|wait_sec
		, const ::Ice::Current& current //< ice default

	);
	virtual bool StatDisplay(
		  const ::std::string& dbpath			//<STRING|dbpath
		, const ::std::string& ppath			//<STRING|ppath
		, const ::Ice::Current& current //< ice default

	);
	virtual void StopPause(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool SysInfoDisplay(
		  const ::std::string& dbpath			//<STRING|dbpath
		, const ::std::string& ppath			//<STRING|ppath
		, const ::Ice::Current& current //< ice default

	);

};//class ODABAClientI

class OperationHandleI;
typedef IceUtil::Handle<OperationHandleI> OperationHandleIPtr; //<cast&convert
typedef std::list< ::OPI::OperationHandlePrx > OperationHandlePrxList;
/**
 * \brief ICE Interface Class for OperationHandle
 */
class OperationHandleI : virtual public OPI::OperationHandle, virtual public ::OperationHandle

{

	private:

	OPIFactoryIPtr factory;
	public:
	OperationHandleI(::OperationHandle &refobj):
		OPI::OperationHandle()
		,::OperationHandle(refobj)
		,factory(NULL)
		{}

	void SetObjectFactory(OPIFactoryIPtr removingfactory);
	virtual bool CheckExpression(
		  const ::OPI::DictionaryHandlePrx& dictptr			//<DictionaryHandle|dictptr
		, const ::std::string& expression			//<STRING|expression
		, const ::OPI::DBObjectHandlePrx& obhandle			//<DBObjectHandle|obhandle
		, const ::std::string& clsnames			//<STRING|clsnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CheckExpressionInClass(
		  const ::OPI::DictionaryHandlePrx& dictptr			//<DictionaryHandle|dictptr
		, const ::OPI::DBObjectHandlePrx& resobj			//<DBObjectHandle|resobj
		, const ::std::string& clsnames			//<STRING|clsnames
		, const ::std::string& exprnames			//<STRING|exprnames
		, const ::std::string& impnames			//<STRING|impnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Execute(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx GetResult(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetSize(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsValid(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Open(
		  const ::OPI::PropertyHandlePrx& prophdlref			//<PropertyHandle|prophdl_ref
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ProvideExpression(
		  const ::OPI::DictionaryHandlePrx& pdictionary			//<DictionaryHandle|dictionary
		, const ::OPI::DBObjectHandlePrx& resobj			//<DBObjectHandle|resobj
		, const ::OPI::DBObjectHandlePrx& obhandle			//<DBObjectHandle|obhandle
		, const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	);

};//class OperationHandleI

class PropertyHandleI;
typedef IceUtil::Handle<PropertyHandleI> PropertyHandleIPtr; //<cast&convert
typedef std::list< ::OPI::PropertyHandlePrx > PropertyHandlePrxList;
/**
 * \brief ICE Interface Class for PropertyHandle
 */
class PropertyHandleI : virtual public OPI::PropertyHandle, virtual public ::PropertyHandle

{

	private:

	OPIFactoryIPtr factory;
	public:
	PropertyHandleI(::PropertyHandle &refobj):
		OPI::PropertyHandle()
		,::PropertyHandle(refobj)
		,factory(NULL)
		{}

	void SetObjectFactory(OPIFactoryIPtr removingfactory);
	virtual bool Add(
		  ::Ice::Int setpos0			//<INT|set_pos0
		, const ::std::string& sortkey			//<Key|sortkey
		, const ::std::string& identkeyw			//<Key|identkey_w
		, const ::Ice::Current& current //< ice default

	);
	virtual bool AddByKey(
		  const ::std::string& sortkey			//<Key|sortkey
		, const ::std::string& identkeyw			//<Key|identkey_w
		, const ::Ice::Current& current //< ice default

	);
	virtual bool AddInstance(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	);
	virtual bool AddOnPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, bool initinst			//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	);
	virtual bool AddGlobal(
		  ::Ice::Int setpos0			//<INT|set_pos0
		, const ::std::string& sortkey			//<Key|sortkey
		, const ::std::string& identkeyw			//<Key|identkey_w
		, bool initinst			//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	);
	virtual bool AddGlobalByKey(
		  const ::std::string& sortkey			//<Key|sortkey
		, const ::std::string& identkeyw			//<Key|identkey_w
		, bool initinst			//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	);
	virtual bool AddGlobalOnPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, bool initinst			//<LOGICAL|init_inst
		, const ::Ice::Current& current //< ice default

	);
	virtual bool AddReference(
		  const ::OPI::PropertyHandlePrx& sourcehandle			//<PropertyHandle|source_handle
		, ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	);
	virtual bool AllocDescription(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool AllocateArea(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool AppendString(
		  const ::std::string& pstring			//<STRING|string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool AutoLocate(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Cancel(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CancelBuffer(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int ChangeBuffer(
		  ::Ice::Int buffnum			//<INT|buffnum
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ChangeCache(
		  ::Ice::Int buffnum			//<INT|buffnum
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PIACC ChangeMode(
		  ::OPI::PIACC newmode			//<PIACC|newmode
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Check(
		  bool iniopt			//<LOGICAL|ini_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CheckPosition(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool CheckUpdate(
		  bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CheckWProtect(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Close(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int Compare(
		  const ::OPI::PropertyHandlePrx& cprophdl			//<PropertyHandle|cprop_hdl
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int CompareDate(
		  ::Ice::Long dateval			//<dbdt|date_val
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int CompareFloat(
		  ::Ice::Float doubleval			//<REAL|double_val
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int CompareInteger(
		  ::Ice::Int longval			//<INT|long_val
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int CompareString(
		  const ::std::string& pstring			//<STRING|string
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int CompareTime(
		  ::Ice::Long timeval			//<dbtm|time_val
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int CompareKey(
		  const ::std::string& identkey1			//<Key|ident_key1
		, const ::std::string& identkey2			//<Key|ident_key2
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int CompareSortKey(
		  const ::std::string& sortkey1			//<Key|sort_key1
		, const ::std::string& sortkey2			//<Key|sort_key2
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CompareType(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, bool convert			//<LOGICAL|convert
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Copy(
		  const ::OPI::PropertyHandlePrx& sourcehandle			//<PropertyHandle|source_handle
		, const ::std::string& newkey			//<Key|new_key
		, ::Ice::Int setpos0			//<INT|set_pos0
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, ::OPI::PIREPL copytype			//<PIREPL|copy_type
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CopyData(
		  const ::OPI::PropertyHandlePrx& sourcehandle			//<PropertyHandle|source_handle
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CopyHandle(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CopyInstanceArea(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prophdl
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int CopySet(
		  const ::OPI::PropertyHandlePrx& csourcehandle			//<PropertyHandle|csource_handle
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, ::OPI::PIREPL copytype			//<PIREPL|copy_type
		, bool inversecheck			//<LOGICAL|inverse_check
		, const ::Ice::Current& current //< ice default

	);
	virtual bool CreateTempExtent(
		  const ::OPI::PropertyHandlePrx& prophdlref			//<PropertyHandle|prophdl_ref
		, const ::std::string& extnamesw			//<STRING|extnames_w
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Delete(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DeleteByKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DeleteOnPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, bool deldep			//<LOGICAL|del_dep
		, bool delinst			//<LOGICAL|del_inst
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DeleteIndexEntry(
		  ::Ice::Int setpos0			//<INT|set_pos0
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DeleteSet(
		  bool deldep			//<LOGICAL|del_dep
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DisableKeyCheck(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Duplicate(
		  ::Ice::Int setpos0			//<INT|set_pos0
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool DuplicateKey(
		  const ::std::string& identkey			//<Key|ident_key
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool EnableKeyCheck(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Execute(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx ExecuteExpression(
		  const ::OPI::DBObjectHandlePrx& resobhandle			//<DBObjectHandle|res_obhandle
		, const ::OPI::DBObjectHandlePrx& obhandle			//<DBObjectHandle|obhandle
		, const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ExecuteInstanceAction(
		  const ::std::string& actionname			//<CHAR|action_name
		, const ::std::string& parmstring			//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ExecutePropertyAction(
		  const ::std::string& actionname			//<CHAR|action_name
		, const ::std::string& parmstring			//<STRING|parm_string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Exist(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string ExtractKey(
		  const ::std::string& keyname			//<STRING|key_name
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string ExtractSortKey(
		  const ::std::string& sortkeyw			//<Key|sort_key_w
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string FirstKey(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Get(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	);
	virtual bool GetAtPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	);
	virtual bool GetByKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetActionResult(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetArea(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetAttribute(
		  ::Ice::Int indx0			//<INT|indx0
		, bool fullpath			//<LOGICAL|full_path
		, bool generic			//<LOGICAL|generic
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx GetBaseProperty(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetCollectionID(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx GetCollectionProperty(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetCount(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetCurrentIndex(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetCurrentSize(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetCurrentType(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DatabaseHandlePrx GetDBHandle(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Long GetDate(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Long GetDateTime(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetDay(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DictionaryHandlePrx GetDictionary(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetDimension(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Float GetDouble(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetExtInstModCount(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetExtentName(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetGUID(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetGenAttrType(
		  const ::std::string& wpropnames			//<STRING|w_propnames
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetGenOrderType(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetGlobalID(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetHours(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetID(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetIdentity(
		  const ::std::string& idstring			//<STRING|id_string
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetIndexName(
		  ::Ice::Int indx0			//<INT|indx0
		, const ::Ice::Current& current //< ice default

	);
	virtual bool GetInitInstance(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetInstModCount(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetInt(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetIntValue(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetKey(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetKeyLength(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetLOID(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetLOIDByKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetMinutes(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PIACC GetMode(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetMonth(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetNormalized(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::DBObjectHandlePrx GetObjectHandle(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetOrigin(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx GetParentProperty(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx GetPropertyHandle(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetPropertyPath(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetRefModCount(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetReference(
		  ::Ice::Int indx0			//<INT|indx0
		, bool fullpath			//<LOGICAL|full_path
		, bool generic			//<LOGICAL|generic
		, const ::Ice::Current& current //< ice default

	);
	virtual bool GetRelative(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetRelativeCount(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetRelativeIndex(
		  bool lastopt			//<LOGICAL|last_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetSeconds(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetSelectedKey(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetSize(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetSizeOf(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetSortKey(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetSortKeyLength(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetString(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetStringLength(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetStringValue(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetSubString(
		  ::Ice::Int startpos			//<INT|start_pos
		, ::Ice::Int length			//<INT|length
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetText(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Long GetTime(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::std::string GetType(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool GetValid(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetVersion(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int GetYear(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx Group(
		  const ::OPI::PropertyHandlePrx& prophdlref			//<PropertyHandle|prophdl_ref
		, const ::std::string& groupingrule			//<STRING|grouping_rule
		, bool distinct			//<LOGICAL|distinct
		, const ::Ice::Current& current //< ice default

	);
	virtual bool HasData(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool HasDescription(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool HasGenericAttributes(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool HasIndex(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Inherits(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool InsertString(
		  const ::std::string& pstring			//<STRING|string
		, ::Ice::Int position			//<INT|position
		, const ::Ice::Current& current //< ice default

	);
	virtual bool InsertTerminator(
		  const ::std::string& pstring			//<STRING|string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool InstanceInserted(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string InstanceToString(
		  const ::std::string& stringsep			//<STRING|string_sep
		, const ::std::string& fieldsep			//<STRING|field_sep
		, const ::std::string& blocksep			//<STRING|block_sep
		, const ::std::string& emptystring			//<STRING|empty_string
		, bool skiptrans			//<LOGICAL|skip_trans
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx Intersect(
		  const ::OPI::PropertyHandlePrx& prophdl1			//<PropertyHandle|prop_hdl1
		, const ::OPI::PropertyHandlePrx& prophdl2			//<PropertyHandle|prop_hdl2
		, const ::std::string& skopt			//<CHAR|sk_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Is(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsA(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsActive(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsAttribute(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsAutoSelection(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsBasedOn(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsBasetypeProperty(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsBasicType(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsClient(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsCollection(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsCollectionUpdate(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsCopyHandle(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsDirty(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsEmpty(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsEnumeration(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsGenericAttribute(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsInitInstance(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsMemo(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsModified(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsNewInstance(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsNumeric(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsOldInstance(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsOwner(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsPositioned(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsReadOnly(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsSelected(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsSensitive(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsServer(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsShareBaseHandle(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsStructure(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsText(
		  const ::std::string& chkopt			//<CHAR|chkopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsTransient(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsTrue(
		  const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsTyped(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsUserHandle(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsValid(
		  bool topt			//<LOGICAL|topt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsValidText(
		  const ::std::string& pstring			//<STRING|string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool IsVariableType(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsWeakTyped(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool IsWrite(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Locate(
		  ::Ice::Int obident			//<INT|obident
		, bool readopt			//<LOGICAL|read_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool LocatePath(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Lock(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool LockSet(
		  const ::Ice::Current& current //< ice default

	);
	virtual void MarkUnused(
		  const ::Ice::Current& current //< ice default

	);
	virtual void MarkUsed(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx Minus(
		  const ::OPI::PropertyHandlePrx& prophdl1			//<PropertyHandle|prop_hdl1
		, const ::OPI::PropertyHandlePrx& prophdl2			//<PropertyHandle|prop_hdl2
		, const ::std::string& skopt			//<CHAR|sk_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Modify(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Move(
		  const ::OPI::PropertyHandlePrx& sourcehandle			//<PropertyHandle|source_handle
		, const ::std::string& newkey			//<Key|new_key
		, ::OPI::PIREPL replopt			//<PIREPL|replopt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool MoveDown(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool MoveUp(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string NextKey(
		  const ::std::string& sortkeyw			//<Key|sort_key_w
		, ::Ice::Int switchlevel			//<INT|switch_level
		, const ::Ice::Current& current //< ice default

	);
	virtual bool NoWrite(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Open(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool OpenBigInt(
		  ::Ice::Int int64val			//<INT|int64_val
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenBoolean(
		  bool logval			//<LOGICAL|logval
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenChild(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenChildReference(
		  const ::OPI::PropertyHandlePrx& ppropertyhandle			//<PropertyHandle|property_handle
		, const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenCopy(
		  const ::OPI::PropertyHandlePrx& cprophdl			//<PropertyHandle|cprop_hdl
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenDate(
		  ::Ice::Long dateval			//<dbdt|date_val
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenExtent(
		  const ::OPI::DBObjectHandlePrx& objecthandle			//<DBObjectHandle|object_handle
		, const ::std::string& extnames			//<STRING|extnames
		, ::OPI::PIACC accopt			//<PIACC|accopt
		, bool transientw			//<LOGICAL|transient_w
		, const ::std::string& keynamew			//<CHAR|key_name_w
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenFloat(
		  ::Ice::Float dblvalue			//<REAL|dbl_value
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenInteger(
		  ::Ice::Int intval			//<INT|int_val
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenReference(
		  const ::OPI::PropertyHandlePrx& ppropertyhandle			//<PropertyHandle|property_handle
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenSizedString(
		  const ::std::string& pstring			//<STRING|string
		, ::Ice::Int stringlen			//<INT|string_len
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenString(
		  const ::std::string& pstring			//<STRING|string
		, bool convopt			//<LOGICAL|conv_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenTime(
		  ::Ice::Long timeval			//<dbtm|time_val
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenTimestamp(
		  ::Ice::Long datetimeval			//<dttm|datetime_val
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OpenHierarchy(
		  const ::OPI::PropertyHandlePrx& bottomph			//<PropertyHandle|bottom_ph
		, const ::OPI::PropertyHandlePrx& topph			//<PropertyHandle|top_ph
		, bool pathopt			//<LOGICAL|path_opt
		, ::OPI::PIACC accmode			//<PIACC|accmode
		, bool copyselection			//<LOGICAL|copy_selection
		, const ::Ice::Current& current //< ice default

	);
	virtual bool OwnsData(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Position(
		  ::Ice::Int count			//<INT|count
		, const ::Ice::Current& current //< ice default

	);
	virtual bool PositionTop(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx Power(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ProvGenAttribute(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Provide(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ProvideAtPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ProvideByKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ProvideArea(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::std::string ProvideGUID(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool ProvideGlobal(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ProvideGlobalAtPosition(
		  ::Ice::Int setpos0w			//<INT|set_pos0_w
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ProvideGlobalByKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::OperationHandlePrx ProvideOperation(
		  const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Refresh(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool ReleaseBuffer(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool RemoveFromCollection(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool RemoveString(
		  const ::std::string& pstring			//<STRING|string
		, ::Ice::Int position			//<INT|position
		, ::Ice::Int len			//<INT|len
		, const ::Ice::Current& current //< ice default

	);
	virtual bool RemoveTerminator(
		  const ::std::string& pstring			//<STRING|string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Rename(
		  const ::std::string& newkey			//<Key|new_key
		, const ::Ice::Current& current //< ice default

	);
	virtual bool RepairIndex(
		  const ::std::string& keynamew			//<CHAR|key_name_w
		, const ::std::string& attrstrw			//<STRING|attrstr_w
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ReplaceString(
		  const ::std::string& oldstr			//<STRING|old_str
		, const ::std::string& newstr			//<STRING|new_str
		, const ::Ice::Current& current //< ice default

	);
	virtual bool ReplaceSysVariables(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Reset(
		  const ::Ice::Current& current //< ice default

	);
	virtual void ResetDirty(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool ResetTransientProperty(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool ResetWProtect(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool Save(
		  const ::std::string& savopt			//<CHAR|savopt
		, bool switchopt			//<LOGICAL|switchopt
		, const ::Ice::Current& current //< ice default

	);
	virtual ::Ice::Int SearchText(
		  const ::std::string& pstring			//<STRING|string
		, ::Ice::Int curpos			//<INT|curpos
		, bool caseopt			//<LOGICAL|case_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx Select(
		  const ::OPI::PropertyHandlePrx& prophdlref			//<PropertyHandle|prophdl_ref
		, const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	);
	virtual void SetActionResult(
		  const ::std::string& resultstring			//<STRING|result_string
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetContextVariables(
		  const ::std::string& contextstring			//<STRING|context_string
		, const ::Ice::Current& current //< ice default

	);
	virtual void SetDirty(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool SetDynLength(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool SetGenAttribute(
		  const ::std::string& attrstr			//<STRING|attrstr
		, const ::std::string& proppath			//<STRING|prop_path
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetKey(
		  const ::std::string& identkey			//<Key|ident_key
		, const ::Ice::Current& current //< ice default

	);
	virtual void SetModified(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool SetNormalized(
		  ::Ice::Int longval			//<INT|long_val
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetOrder(
		  const ::std::string& keyname			//<STRING|key_name
		, const ::std::string& attrstr			//<STRING|attrstr
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetSelection(
		  const ::std::string& expression			//<STRING|expression
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetSortKey(
		  const ::std::string& sortkey			//<Key|sort_key
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetTransientProperty(
		  const ::OPI::PropertyHandlePrx& prophdl			//<PropertyHandle|prop_hdl
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetType(
		  const ::std::string& strnames			//<STRING|strnames
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetUpdate(
		  bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx SetValue(
		  const ::OPI::PropertyHandlePrx& cprophdl			//<PropertyHandle|cprop_hdl
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx SetValueBigInt(
		  ::Ice::Int int64val			//<INT|int64_val
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx SetValueBoolean(
		  bool logval			//<LOGICAL|logval
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx SetValueDate(
		  ::Ice::Long dateval			//<dbdt|date_val
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx SetValueFloat(
		  ::Ice::Float dblvalue			//<REAL|dbl_value
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx SetValueInteger(
		  ::Ice::Int longval			//<INT|long_val
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx SetValueString(
		  const ::std::string& pstring			//<STRING|string
		, bool pcheckupdate			//<LOGICAL|check_update
		, bool convopt			//<LOGICAL|conv_opt
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx SetValueTime(
		  ::Ice::Long timeval			//<dbtm|time_val
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx SetValueTimestamp(
		  ::Ice::Long datetimeval			//<dttm|datetime_val
		, bool pcheckupdate			//<LOGICAL|check_update
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetVersion(
		  ::Ice::Int versionnr			//<UINT|version_nr
		, const ::Ice::Current& current //< ice default

	);
	virtual bool SetWProtect(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool ToTop(
		  const ::Ice::Current& current //< ice default

	);
	virtual ::OPI::PropertyHandlePrx Union(
		  const ::OPI::PropertyHandlePrx& prophdl1			//<PropertyHandle|prop_hdl1
		, const ::OPI::PropertyHandlePrx& prophdl2			//<PropertyHandle|prop_hdl2
		, const ::std::string& skopt			//<CHAR|sk_opt
		, bool distinct			//<LOGICAL|distinct
		, const ::Ice::Current& current //< ice default

	);
	virtual bool Unlock(
		  const ::Ice::Current& current //< ice default

	);
	virtual bool UnlockSet(
		  const ::Ice::Current& current //< ice default

	);

};//class PropertyHandleI

#endif
