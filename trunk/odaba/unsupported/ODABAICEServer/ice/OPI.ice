module OPI{
enum PIACC            { piaREAD, piaWRITE, piaUPDATE,piaUNDEFINED };
enum PIREPL           { piaREPLGUID, piaREPLDIRECT, piaREPLNONE, piaREPLLOCAL, piaREPLALL, piaREPLINSTANCE, piaREPLRELATIONSHIPS, piaREPLNOCREATE};
enum PIADEF           { piaUNKNOWN, piaEXCLUSIVE, piaSHARE }; 
enum ResourceTypes    { resAUTOMATIC, resSERVER, resLOCAL, resSERVERINTERN };
enum ApplicationTypes { aptWINDOWS, aptCONSOLE };

// class declaration
	class CheckOptions;
	class DBObjectHandle;
	class DataSourceHandle;
	class DatabaseHandle;
	class DictionaryHandle;
	class ODABAClient;
	class OperationHandle;
	class PropertyHandle;
class CheckOptions
{	bool Initialize(
		  string parmstring		//<STRING|parmstring

	);

};// end of CheckOptions slice

class DBObjectHandle
{	int BeginTransaction(
		  bool extTA		//<LOGICAL|ext_TA
		, int wmaxnum		//<INT|w_maxnum

	);
	bool ChangeTimeStamp(
		  int versionnr		//<UINT|version_nr
		, long timestamp		//<dttm|timestamp

	);
	bool CommitTransaction(
		  int talevel		//<INT|talevel

	);
	PropertyHandle* CreateTempPropertyHandle(
		  PropertyHandle* prophdlref		//<PropertyHandle|prophdl_ref

	);
	bool DeleteExtent(
		  string extnames		//<STRING|extnames

	);
	bool DeleteExtentRef(
		  string extnames		//<STRING|extnames

	);
	void DisableEventHandling();
	void EnableEventHandling();
	bool EventHandling();
	bool ExecuteDBObjectAction(
		  string actionname		//<CHAR|action_name
		, string parmstring		//<STRING|parm_string

	);
	PropertyHandle* ExecuteExpression(
		  DBObjectHandle* resobhandle		//<DBObjectHandle|res_obhandle
		, string expression		//<STRING|expression

	);
	bool ExtentExist(
		  string extnames		//<STRING|extnames

	);
	PIACC GetAccess();
	string GetActionResult();
	DatabaseHandle* GetDBHandle();
	DataSourceHandle* GetDataSource();
	DictionaryHandle* GetDictionary();
	string GetExtent(
		  int indx0		//<INT|indx0

	);
	DBObjectHandle* GetHighObject();
	string GetObject(
		  int indx0		//<INT|indx0

	);
	string GetServerVariable(
		  string varname		//<STRING|var_name

	);
	int GetSystemVersion();
	long GetTimeStamp(
		  int versionnr		//<UINT|version_nr

	);
	int GetTransactionLevel();
	int GetVersion(
		  long timestamp		//<dttm|timestamp

	);
	bool IsClient();
	bool IsEmpty();
	bool IsOpened();
	bool IsServer();
	bool IsValid();
	bool NewVersion(
		  long timestamp		//<dttm|timestamp
		, int versionnr		//<UINT|version_nr

	);
	bool OpenObject(
		  DBObjectHandle* dbobject		//<DBObjectHandle|dbobject
		, string objname		//<CHAR|objname
		, PIACC accopt		//<PIACC|accopt
		, int versionnr		//<UINT|version_nr
		, ResourceTypes localressources		//<ResourceTypes|local_ressources

	);
	bool RollBack(
		  int talevel		//<INT|talevel

	);
	void SetActionResult(
		  string resultstring		//<STRING|result_string

	);
	int SetOverload(
		  bool overloadopt		//<LOGICAL|overload_opt

	);
	bool SetServerVariable(
		  string varname		//<STRING|var_name
		, string varstring		//<STRING|var_string

	);
	bool SetUserDefinedIdentity(
		  bool identityopt		//<LOGICAL|identity_opt

	);
	bool SetVersion(
		  int versionnr		//<UINT|version_nr

	);
	bool SetVersioni1(
		  long date		//<dbdt|date

	);
	bool SetVersioni2(
		  long timestamp		//<dttm|timestamp

	);
	int VersionCount();

};// end of DBObjectHandle slice

class DataSourceHandle
{	bool BeginTransaction(
		  bool extta		//<LOGICAL|ext_ta

	);
	bool Close();
	bool CloseDBObject();
	bool CloseDatabase();
	bool CloseDictionary();
	bool CloseProperty();
	bool CloseResourceDB();
	bool CommitTransaction();
	bool Connect(
		  ODABAClient* podabaclient		//<ODABAClient|odaba_client

	);
	bool Disconnect();
	bool Open(
		  ODABAClient* podabaclient		//<ODABAClient|odaba_client
		, PIACC accmod		//<PIACC|acc_mod

	);
	bool Openi02(
		  ODABAClient* podabaclient		//<ODABAClient|odaba_client
		, string inifile		//<STRING|ini_file
		, string datasourcename		//<STRING|datasource_name

	);
	bool Openi1(
		  ODABAClient* podabaclient		//<ODABAClient|odaba_client
		, string datasourcename		//<STRING|datasource_name

	);
	DBObjectHandle* OpenDBObject();
	DatabaseHandle* OpenDatabase();
	DictionaryHandle* OpenDictionary(
		  PIACC accopt		//<PIACC|accopt

	);
	PropertyHandle* OpenProperty(
		  string extname		//<CHAR|extname

	);
	DatabaseHandle* OpenResourceDB();
	bool RollBack();
	bool SetDBObject(
		  DBObjectHandle* ohandle		//<DBObjectHandle|ohandle
		, string wobjname		//<STRING|w_objname

	);
	bool SetDataSource(
		  DataSourceHandle* dbdefptr		//<DataSourceHandle|dbdefptr

	);
	bool SetDatabase(
		  DatabaseHandle* dbhandle		//<DatabaseHandle|db_handle
		, string wbasepath		//<STRING|w_basepath

	);
	bool SetDictionary(
		  DictionaryHandle* dictptr		//<DictionaryHandle|dictptr
		, string wdictpath		//<STRING|w_dictpath

	);
	bool SetResourceDB(
		  DatabaseHandle* dbhandle		//<DatabaseHandle|db_handle
		, string wbasepath		//<STRING|w_basepath

	);
	bool SetVariables(
		  string datasourcename		//<STRING|datasource_name

	);
	bool Setup(
		  string inifile		//<STRING|ini_file
		, string datasourcename		//<STRING|datasource_name

	);
	bool SetupVariables(
		  string datasourcename		//<STRING|datasource_name

	);

};// end of DataSourceHandle slice

class DatabaseHandle extends DBObjectHandle
{	bool ActivateShadowBase();
	bool BackupDB(
		  string target		//<STRING|target

	);
	bool CheckDB(
		  CheckOptions* checkopts		//<CheckOptions|check_opts
		, string source		//<STRING|source

	);
	bool CheckLicence(
		  string licowner		//<STRING|lic_owner
		, string licnumber		//<CHAR|lic_number

	);
	bool CloseWorkspace();
	bool ConsolidateWorkspace();
	bool DeactivateShadowBase();
	bool DeleteWorkspace(
		  string wsnames		//<STRING|ws_names
		, string username		//<STRING|user_name

	);
	bool DisableWorkspace();
	bool DiscardWorkspace();
	bool EnableWorkspace(
		  string sdwpath		//<CHAR|sdw_path

	);
	bool ExecuteDatabaseAction(
		  string actionname		//<CHAR|action_name
		, string parmstring		//<STRING|parm_string

	);
	bool ExistWorkspace(
		  string wsnames		//<STRING|ws_names

	);
	int GetDatabaseID();
	string GetPath();
	int GetSchemaVersion();
	string GetVersionString();
	string GetWorkspace(
		  string wsroot		//<STRING|ws_root
		, int wsindex		//<INT|ws_index
		, string username		//<STRING|user_name
		, string wsname		//<STRING|ws_name
		, bool refreshopt		//<LOGICAL|refresh_opt
		, string wsinfo		//<CHAR|ws_info

	);
	bool IgnoreWriteProtect();
	bool InitDataArea(
		  int mbnumber		//<INT|mbnumber
		, int sbnumber		//<INT|sbnumber
		, int danumber		//<UINT|danumber
		, string filename		//<STRING|filename
		, int dasize		//<INT|dasize

	);
	bool InitMainBase(
		  int mbnumber		//<INT|mbnumber
		, string filename		//<STRING|filename
		, int lowEBN		//<INT|lowEBN
		, int highEBN		//<INT|highEBN
		, int dasize		//<INT|dasize
		, bool largedb		//<LOGICAL|largedb
		, bool pindep		//<LOGICAL|pindep

	);
	bool InitSubBase(
		  int mbnumber		//<INT|mbnumber
		, int sbnumber		//<INT|sbnumber
		, string filename		//<STRING|filename
		, int dasize		//<INT|dasize

	);
	bool IsLicenced();
	bool IsShared();
	bool LocateWorkspace(
		  string wsnames		//<STRING|ws_names

	);
	bool OpenDatabase(
		  DictionaryHandle* dicthandle		//<DictionaryHandle|dict_handle
		, string cpath		//<STRING|cpath
		, PIACC accopt		//<PIACC|accopt
		, bool wnetopt		//<LOGICAL|w_netopt
		, bool onlineversion		//<LOGICAL|online_version
		, int versionnr		//<UINT|version_nr
		, ResourceTypes localressources		//<ResourceTypes|local_ressources
		, bool sysenv		//<LOGICAL|sysenv

	);
	bool OpenWorkspace(
		  string wsnames		//<STRING|ws_names
		, string username		//<STRING|user_name
		, bool exclusive		//<LOGICAL|exclusive
		, string wspath		//<STRING|ws_path

	);
	bool RecreateExtent(
		  string extnames		//<STRING|extnames

	);
	bool RestoreDB(
		  string source		//<STRING|source

	);
	bool SetupTypeID(
		  int sid		//<INT|sid

	);

};// end of DatabaseHandle slice

class DictionaryHandle extends DatabaseHandle
{	int BaseType(
		  string strnames		//<STRING|strnames

	);
	bool CheckExpression(
		  string expression		//<STRING|expression
		, DBObjectHandle* dbobjhandle		//<DBObjectHandle|dbobj_handle
		, string clsnames		//<STRING|clsnames

	);
	bool CheckExpressionInClass(
		  DBObjectHandle* resobj		//<DBObjectHandle|resobj
		, string clsnames		//<STRING|clsnames
		, string exprnames		//<STRING|exprnames
		, string implnames		//<STRING|implnames

	);
	bool CheckExtentDef(
		  string scopedname		//<STRING|scoped_name

	);
	bool CheckValueSet(
		  string scopedname		//<STRING|scoped_name

	);
	bool CopyCodeset(
		  DictionaryHandle* srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, string strname		//<CHAR|strname
		, int namespaceid		//<INT|namespace_id
		, string newnames		//<STRING|newnames
		, PIREPL dbreplace		//<PIREPL|db_replace
		, bool retainSID		//<LOGICAL|retainSID
		, bool retainschemav		//<LOGICAL|retain_schemav

	);
	bool CopyExtentDef(
		  DictionaryHandle* srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, string extentname		//<STRING|extentname
		, string newnames		//<STRING|newnames
		, string targstruct		//<STRING|targ_struct
		, bool transaction		//<LOGICAL|transaction
		, bool retainschemav		//<LOGICAL|retain_schemav

	);
	bool CopyStructure(
		  DictionaryHandle* srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, string strname		//<CHAR|strname
		, int namespaceid		//<INT|namespace_id
		, string newnames		//<STRING|newnames
		, string topname		//<CHAR|topname
		, PIREPL dbreplace		//<PIREPL|db_replace
		, bool retainSID		//<LOGICAL|retainSID
		, bool retainschemav		//<LOGICAL|retain_schemav

	);
	bool CopyType(
		  DictionaryHandle* srcedicthandle		//<DictionaryHandle|srce_dicthandle
		, string strnames		//<STRING|strnames
		, string newnames		//<STRING|newnames
		, string topname		//<CHAR|topname
		, PIREPL dbreplace		//<PIREPL|db_replace
		, bool retainSID		//<LOGICAL|retainSID
		, bool transaction		//<LOGICAL|transaction
		, bool retainschemav		//<LOGICAL|retain_schemav

	);
	bool CreateEnum(
		  string enumname		//<STRING|enum_name
		, string basetype		//<STRING|basetype

	);
	string CreateTempExtent(
		  string strnames		//<STRING|strnames
		, string extnamesw		//<STRING|extnames_w
		, string keynamew		//<CHAR|key_name_w
		, string baseextsw		//<STRING|baseexts_w
		, bool weakoptw		//<LOGICAL|weak_opt_w
		, bool ownoptw		//<LOGICAL|own_opt_w

	);
	bool DeleteEnum(
		  string enumname		//<STRING|enum_name

	);
	string EnumToString(
		  string enumeration		//<STRING|enumeration
		, int enumval		//<INT|enum_val
		, string pstring		//<STRING|string
		, int len		//<INT|len

	);
	int GetLastSchemaVersion();
	string GetTempName(
		  string extnames		//<STRING|extnames

	);
	bool IsBasicType(
		  string typenames		//<STRING|typenames

	);
	bool OpenDictionary(
		  ODABAClient* podabaclient		//<ODABAClient|odaba_client
		, string cpath		//<STRING|cpath
		, PIACC accopt		//<PIACC|accopt
		, bool wnetopt		//<LOGICAL|w_netopt
		, int versionnr		//<UINT|version_nr
		, ResourceTypes localressources		//<ResourceTypes|local_ressources
		, bool sysenv		//<LOGICAL|sysenv

	);
	int StringToEnum(
		  string enumeration		//<STRING|enumeration
		, string enumstring		//<STRING|enum_string

	);
	bool UpdateVersion();

};// end of DictionaryHandle slice

class ODABAClient
{	void ActivateGUIMessages();
	bool BackupDB(
		  string cpath		//<STRING|cpath
		, string target		//<STRING|target
		, int waitsec		//<INT|wait_sec

	);
	bool CheckDB(
		  string dictpath		//<STRING|dict_path
		, string cpath		//<STRING|cpath
		, CheckOptions* checkopts		//<CheckOptions|check_opts
		, string source		//<STRING|source
		, int waitsec		//<INT|wait_sec

	);
	bool Close();
	bool Connect(
		  string servername		//<STRING|server_name
		, int hostport		//<UINT|host_port
		, string cachestring		//<STRING|cache_string

	);
	bool DictDisplay(
		  string dbpath		//<STRING|dbpath
		, string ppath		//<STRING|ppath

	);
	void Disconnect();
	bool Exist(
		  string cpath		//<STRING|cpath

	);
	string GetDataSource(
		  int indx0		//<INT|indx0

	);
	string GetHost();
	int GetPort();
	string GetServerVariable(
		  string varname		//<STRING|var_name

	);
	void Initialize(
		  string inipath		//<STRING|inipath
		, string applicationname		//<STRING|application_name
		, string progpath		//<STRING|progpath
		, ApplicationTypes applicationtype		//<ApplicationTypes|application_type
		, bool initservices		//<LOGICAL|init_services

	);
	bool IsConnected();
	bool KillClient(
		  int clientid		//<INT|client_id
		, int waitsec		//<INT|wait_sec
		, bool sendmessage		//<LOGICAL|send_message

	);
	bool Open(
		  string inipath		//<STRING|inipath
		, string applicationname		//<STRING|application_name
		, string progpath		//<STRING|progpath
		, ApplicationTypes applicationtype		//<ApplicationTypes|application_type

	);
	DBObjectHandle* OpenDataSource(
		  string datasourcename		//<STRING|datasource_name
		, PIACC accopt		//<PIACC|accopt

	);
	bool PackDatabase(
		  string cpath		//<STRING|cpath
		, string temppath		//<STRING|temp_path

	);
	bool RestoreDB(
		  string cpath		//<STRING|cpath
		, string source		//<STRING|source
		, int waitsec		//<INT|wait_sec

	);
	bool SendClientMessage(
		  int clientid		//<INT|client_id
		, string mtext		//<STRING|mtext
		, string mtitle		//<STRING|mtitle
		, string mtype		//<CHAR|mtype

	);
	bool SetServerVariable(
		  string varname		//<STRING|var_name
		, string varstring		//<STRING|var_string

	);
	bool ShutDown(
		  string closesystem		//<CHAR|close_system

	);
	bool StartPause(
		  int waitsec		//<INT|wait_sec

	);
	bool StatDisplay(
		  string dbpath		//<STRING|dbpath
		, string ppath		//<STRING|ppath

	);
	void StopPause();
	bool SysInfoDisplay(
		  string dbpath		//<STRING|dbpath
		, string ppath		//<STRING|ppath

	);

};// end of ODABAClient slice

class OperationHandle
{	bool CheckExpression(
		  DictionaryHandle* dictptr		//<DictionaryHandle|dictptr
		, string expression		//<STRING|expression
		, DBObjectHandle* obhandle		//<DBObjectHandle|obhandle
		, string clsnames		//<STRING|clsnames

	);
	bool CheckExpressionInClass(
		  DictionaryHandle* dictptr		//<DictionaryHandle|dictptr
		, DBObjectHandle* resobj		//<DBObjectHandle|resobj
		, string clsnames		//<STRING|clsnames
		, string exprnames		//<STRING|exprnames
		, string impnames		//<STRING|impnames

	);
	bool Execute();
	PropertyHandle* GetResult();
	int GetSize();
	bool IsValid();
	bool Open(
		  PropertyHandle* prophdlref		//<PropertyHandle|prophdl_ref

	);
	bool ProvideExpression(
		  DictionaryHandle* pdictionary		//<DictionaryHandle|dictionary
		, DBObjectHandle* resobj		//<DBObjectHandle|resobj
		, DBObjectHandle* obhandle		//<DBObjectHandle|obhandle
		, string expression		//<STRING|expression

	);

};// end of OperationHandle slice

class PropertyHandle
{	bool Add(
		  int setpos0		//<INT|set_pos0
		, string sortkey		//<Key|sortkey
		, string identkeyw		//<Key|identkey_w

	);
	bool AddByKey(
		  string sortkey		//<Key|sortkey
		, string identkeyw		//<Key|identkey_w

	);
	bool AddInstance(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);
	bool AddOnPosition(
		  int setpos0w		//<INT|set_pos0_w
		, bool initinst		//<LOGICAL|init_inst

	);
	bool AddGlobal(
		  int setpos0		//<INT|set_pos0
		, string sortkey		//<Key|sortkey
		, string identkeyw		//<Key|identkey_w
		, bool initinst		//<LOGICAL|init_inst

	);
	bool AddGlobalByKey(
		  string sortkey		//<Key|sortkey
		, string identkeyw		//<Key|identkey_w
		, bool initinst		//<LOGICAL|init_inst

	);
	bool AddGlobalOnPosition(
		  int setpos0w		//<INT|set_pos0_w
		, bool initinst		//<LOGICAL|init_inst

	);
	bool AddReference(
		  PropertyHandle* sourcehandle		//<PropertyHandle|source_handle
		, int setpos0w		//<INT|set_pos0_w

	);
	bool AllocDescription();
	bool AllocateArea();
	bool AppendString(
		  string pstring		//<STRING|string

	);
	bool AutoLocate(
		  string chkopt		//<CHAR|chkopt

	);
	bool Cancel();
	bool CancelBuffer();
	int ChangeBuffer(
		  int buffnum		//<INT|buffnum

	);
	bool ChangeCache(
		  int buffnum		//<INT|buffnum

	);
	PIACC ChangeMode(
		  PIACC newmode		//<PIACC|newmode

	);
	bool Check(
		  bool iniopt		//<LOGICAL|ini_opt

	);
	bool CheckPosition();
	bool CheckUpdate(
		  bool pcheckupdate		//<LOGICAL|check_update

	);
	bool CheckWProtect();
	bool Close();
	int Compare(
		  PropertyHandle* cprophdl		//<PropertyHandle|cprop_hdl

	);
	int CompareDate(
		  long dateval		//<dbdt|date_val

	);
	int CompareFloat(
		  float doubleval		//<REAL|double_val

	);
	int CompareInteger(
		  int longval		//<INT|long_val

	);
	int CompareString(
		  string pstring		//<STRING|string

	);
	int CompareTime(
		  long timeval		//<dbtm|time_val

	);
	int CompareKey(
		  string identkey1		//<Key|ident_key1
		, string identkey2		//<Key|ident_key2

	);
	int CompareSortKey(
		  string sortkey1		//<Key|sort_key1
		, string sortkey2		//<Key|sort_key2

	);
	bool CompareType(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl
		, bool convert		//<LOGICAL|convert

	);
	bool Copy(
		  PropertyHandle* sourcehandle		//<PropertyHandle|source_handle
		, string newkey		//<Key|new_key
		, int setpos0		//<INT|set_pos0
		, PIREPL replopt		//<PIREPL|replopt
		, PIREPL copytype		//<PIREPL|copy_type

	);
	bool CopyData(
		  PropertyHandle* sourcehandle		//<PropertyHandle|source_handle
		, PIREPL replopt		//<PIREPL|replopt

	);
	bool CopyHandle(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);
	bool CopyInstanceArea(
		  PropertyHandle* prophdl		//<PropertyHandle|prophdl

	);
	int CopySet(
		  PropertyHandle* csourcehandle		//<PropertyHandle|csource_handle
		, PIREPL replopt		//<PIREPL|replopt
		, PIREPL copytype		//<PIREPL|copy_type
		, bool inversecheck		//<LOGICAL|inverse_check

	);
	bool CreateTempExtent(
		  PropertyHandle* prophdlref		//<PropertyHandle|prophdl_ref
		, string extnamesw		//<STRING|extnames_w

	);
	bool Delete(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);
	bool DeleteByKey(
		  string sortkey		//<Key|sort_key

	);
	bool DeleteOnPosition(
		  int setpos0w		//<INT|set_pos0_w
		, bool deldep		//<LOGICAL|del_dep
		, bool delinst		//<LOGICAL|del_inst

	);
	bool DeleteIndexEntry(
		  int setpos0		//<INT|set_pos0

	);
	bool DeleteSet(
		  bool deldep		//<LOGICAL|del_dep

	);
	bool DisableKeyCheck();
	bool Duplicate(
		  int setpos0		//<INT|set_pos0
		, PIREPL replopt		//<PIREPL|replopt

	);
	bool DuplicateKey(
		  string identkey		//<Key|ident_key
		, PIREPL replopt		//<PIREPL|replopt

	);
	bool EnableKeyCheck();
	bool Execute();
	PropertyHandle* ExecuteExpression(
		  DBObjectHandle* resobhandle		//<DBObjectHandle|res_obhandle
		, DBObjectHandle* obhandle		//<DBObjectHandle|obhandle
		, string expression		//<STRING|expression

	);
	bool ExecuteInstanceAction(
		  string actionname		//<CHAR|action_name
		, string parmstring		//<STRING|parm_string

	);
	bool ExecutePropertyAction(
		  string actionname		//<CHAR|action_name
		, string parmstring		//<STRING|parm_string

	);
	bool Exist();
	string ExtractKey(
		  string keyname		//<STRING|key_name

	);
	string ExtractSortKey(
		  string sortkeyw		//<Key|sort_key_w

	);
	string FirstKey();
	bool Get(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);
	bool GetAtPosition(
		  int setpos0w		//<INT|set_pos0_w

	);
	bool GetByKey(
		  string sortkey		//<Key|sort_key

	);
	string GetActionResult();
	string GetArea(
		  string chkopt		//<CHAR|chkopt

	);
	string GetAttribute(
		  int indx0		//<INT|indx0
		, bool fullpath		//<LOGICAL|full_path
		, bool generic		//<LOGICAL|generic

	);
	PropertyHandle* GetBaseProperty();
	int GetCollectionID();
	PropertyHandle* GetCollectionProperty();
	int GetCount();
	int GetCurrentIndex();
	int GetCurrentSize();
	string GetCurrentType();
	DatabaseHandle* GetDBHandle();
	long GetDate(
		  string proppath		//<STRING|prop_path

	);
	long GetDateTime(
		  string proppath		//<STRING|prop_path

	);
	int GetDay(
		  string proppath		//<STRING|prop_path

	);
	DictionaryHandle* GetDictionary();
	int GetDimension();
	float GetDouble(
		  string proppath		//<STRING|prop_path

	);
	int GetExtInstModCount();
	string GetExtentName();
	string GetGUID();
	int GetGenAttrType(
		  string wpropnames		//<STRING|w_propnames

	);
	int GetGenOrderType();
	int GetGlobalID();
	int GetHours(
		  string proppath		//<STRING|prop_path

	);
	int GetID(
		  int setpos0w		//<INT|set_pos0_w

	);
	string GetIdentity(
		  string idstring		//<STRING|id_string

	);
	string GetIndexName(
		  int indx0		//<INT|indx0

	);
	bool GetInitInstance();
	int GetInstModCount();
	int GetInt(
		  string proppath		//<STRING|prop_path

	);
	int GetIntValue(
		  string proppath		//<STRING|prop_path

	);
	string GetKey(
		  int setpos0w		//<INT|set_pos0_w

	);
	int GetKeyLength();
	int GetLOID(
		  int setpos0w		//<INT|set_pos0_w

	);
	int GetLOIDByKey(
		  string sortkey		//<Key|sort_key

	);
	int GetMinutes(
		  string proppath		//<STRING|prop_path

	);
	PIACC GetMode();
	int GetMonth(
		  string proppath		//<STRING|prop_path

	);
	int GetNormalized();
	DBObjectHandle* GetObjectHandle();
	int GetOrigin();
	PropertyHandle* GetParentProperty();
	PropertyHandle* GetPropertyHandle(
		  string proppath		//<STRING|prop_path

	);
	string GetPropertyPath();
	int GetRefModCount();
	string GetReference(
		  int indx0		//<INT|indx0
		, bool fullpath		//<LOGICAL|full_path
		, bool generic		//<LOGICAL|generic

	);
	bool GetRelative(
		  int setpos0w		//<INT|set_pos0_w

	);
	int GetRelativeCount();
	int GetRelativeIndex(
		  bool lastopt		//<LOGICAL|last_opt

	);
	int GetSeconds(
		  string proppath		//<STRING|prop_path

	);
	string GetSelectedKey();
	int GetSize();
	int GetSizeOf();
	string GetSortKey();
	int GetSortKeyLength();
	string GetString(
		  string proppath		//<STRING|prop_path

	);
	int GetStringLength();
	string GetStringValue(
		  string proppath		//<STRING|prop_path

	);
	string GetSubString(
		  int startpos		//<INT|start_pos
		, int length		//<INT|length

	);
	string GetText(
		  string proppath		//<STRING|prop_path

	);
	long GetTime(
		  string proppath		//<STRING|prop_path

	);
	string GetType();
	bool GetValid();
	int GetVersion();
	int GetYear(
		  string proppath		//<STRING|prop_path

	);
	PropertyHandle* Group(
		  PropertyHandle* prophdlref		//<PropertyHandle|prophdl_ref
		, string groupingrule		//<STRING|grouping_rule
		, bool distinct		//<LOGICAL|distinct

	);
	bool HasData();
	bool HasDescription();
	bool HasGenericAttributes();
	bool HasIndex();
	bool Inherits(
		  string strnames		//<STRING|strnames

	);
	bool InsertString(
		  string pstring		//<STRING|string
		, int position		//<INT|position

	);
	bool InsertTerminator(
		  string pstring		//<STRING|string

	);
	bool InstanceInserted();
	string InstanceToString(
		  string stringsep		//<STRING|string_sep
		, string fieldsep		//<STRING|field_sep
		, string blocksep		//<STRING|block_sep
		, string emptystring		//<STRING|empty_string
		, bool skiptrans		//<LOGICAL|skip_trans

	);
	PropertyHandle* Intersect(
		  PropertyHandle* prophdl1		//<PropertyHandle|prop_hdl1
		, PropertyHandle* prophdl2		//<PropertyHandle|prop_hdl2
		, string skopt		//<CHAR|sk_opt

	);
	bool Is(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);
	bool IsA(
		  string strnames		//<STRING|strnames

	);
	bool IsActive();
	bool IsAttribute();
	bool IsAutoSelection();
	bool IsBasedOn(
		  string strnames		//<STRING|strnames

	);
	bool IsBasetypeProperty();
	bool IsBasicType();
	bool IsClient();
	bool IsCollection(
		  string chkopt		//<CHAR|chkopt

	);
	bool IsCollectionUpdate();
	bool IsCopyHandle();
	bool IsDirty();
	bool IsEmpty();
	bool IsEnumeration();
	bool IsGenericAttribute();
	bool IsInitInstance();
	bool IsMemo(
		  string chkopt		//<CHAR|chkopt

	);
	bool IsModified();
	bool IsNewInstance();
	bool IsNumeric();
	bool IsOldInstance();
	bool IsOwner();
	bool IsPositioned(
		  string chkopt		//<CHAR|chkopt

	);
	bool IsReadOnly();
	bool IsSelected(
		  string chkopt		//<CHAR|chkopt

	);
	bool IsSensitive(
		  string proppath		//<STRING|prop_path

	);
	bool IsServer();
	bool IsShareBaseHandle(
		  string chkopt		//<CHAR|chkopt

	);
	bool IsStructure();
	bool IsText(
		  string chkopt		//<CHAR|chkopt

	);
	bool IsTransient();
	bool IsTrue(
		  string proppath		//<STRING|prop_path

	);
	bool IsTyped();
	bool IsUserHandle();
	bool IsValid(
		  bool topt		//<LOGICAL|topt

	);
	bool IsValidText(
		  string pstring		//<STRING|string

	);
	bool IsVariableType();
	bool IsWeakTyped();
	bool IsWrite();
	bool Locate(
		  int obident		//<INT|obident
		, bool readopt		//<LOGICAL|read_opt

	);
	bool LocatePath();
	bool Lock();
	bool LockSet();
	void MarkUnused();
	void MarkUsed();
	PropertyHandle* Minus(
		  PropertyHandle* prophdl1		//<PropertyHandle|prop_hdl1
		, PropertyHandle* prophdl2		//<PropertyHandle|prop_hdl2
		, string skopt		//<CHAR|sk_opt

	);
	bool Modify();
	bool Move(
		  PropertyHandle* sourcehandle		//<PropertyHandle|source_handle
		, string newkey		//<Key|new_key
		, PIREPL replopt		//<PIREPL|replopt

	);
	bool MoveDown();
	bool MoveUp();
	string NextKey(
		  string sortkeyw		//<Key|sort_key_w
		, int switchlevel		//<INT|switch_level

	);
	bool NoWrite();
	bool Open();
	bool OpenBigInt(
		  int int64val		//<INT|int64_val

	);
	bool OpenBoolean(
		  bool logval		//<LOGICAL|logval

	);
	bool OpenChild(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl
		, string proppath		//<STRING|prop_path

	);
	bool OpenChildReference(
		  PropertyHandle* ppropertyhandle		//<PropertyHandle|property_handle
		, string proppath		//<STRING|prop_path

	);
	bool OpenCopy(
		  PropertyHandle* cprophdl		//<PropertyHandle|cprop_hdl

	);
	bool OpenDate(
		  long dateval		//<dbdt|date_val

	);
	bool OpenExtent(
		  DBObjectHandle* objecthandle		//<DBObjectHandle|object_handle
		, string extnames		//<STRING|extnames
		, PIACC accopt		//<PIACC|accopt
		, bool transientw		//<LOGICAL|transient_w
		, string keynamew		//<CHAR|key_name_w

	);
	bool OpenFloat(
		  float dblvalue		//<REAL|dbl_value

	);
	bool OpenInteger(
		  int intval		//<INT|int_val

	);
	bool OpenReference(
		  PropertyHandle* ppropertyhandle		//<PropertyHandle|property_handle

	);
	bool OpenSizedString(
		  string pstring		//<STRING|string
		, int stringlen		//<INT|string_len

	);
	bool OpenString(
		  string pstring		//<STRING|string
		, bool convopt		//<LOGICAL|conv_opt

	);
	bool OpenTime(
		  long timeval		//<dbtm|time_val

	);
	bool OpenTimestamp(
		  long datetimeval		//<dttm|datetime_val

	);
	bool OpenHierarchy(
		  PropertyHandle* bottomph		//<PropertyHandle|bottom_ph
		, PropertyHandle* topph		//<PropertyHandle|top_ph
		, bool pathopt		//<LOGICAL|path_opt
		, PIACC accmode		//<PIACC|accmode
		, bool copyselection		//<LOGICAL|copy_selection

	);
	bool OwnsData();
	bool Position(
		  int count		//<INT|count

	);
	bool PositionTop();
	PropertyHandle* Power(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);
	bool ProvGenAttribute();
	bool Provide(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);
	bool ProvideAtPosition(
		  int setpos0w		//<INT|set_pos0_w

	);
	bool ProvideByKey(
		  string sortkey		//<Key|sort_key

	);
	bool ProvideArea();
	string ProvideGUID();
	bool ProvideGlobal(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);
	bool ProvideGlobalAtPosition(
		  int setpos0w		//<INT|set_pos0_w

	);
	bool ProvideGlobalByKey(
		  string sortkey		//<Key|sort_key

	);
	OperationHandle* ProvideOperation(
		  string expression		//<STRING|expression

	);
	bool Refresh();
	bool ReleaseBuffer();
	bool RemoveFromCollection();
	bool RemoveString(
		  string pstring		//<STRING|string
		, int position		//<INT|position
		, int len		//<INT|len

	);
	bool RemoveTerminator(
		  string pstring		//<STRING|string

	);
	bool Rename(
		  string newkey		//<Key|new_key

	);
	bool RepairIndex(
		  string keynamew		//<CHAR|key_name_w
		, string attrstrw		//<STRING|attrstr_w

	);
	bool ReplaceString(
		  string oldstr		//<STRING|old_str
		, string newstr		//<STRING|new_str

	);
	bool ReplaceSysVariables();
	bool Reset();
	void ResetDirty();
	bool ResetTransientProperty();
	bool ResetWProtect();
	bool Save(
		  string savopt		//<CHAR|savopt
		, bool switchopt		//<LOGICAL|switchopt

	);
	int SearchText(
		  string pstring		//<STRING|string
		, int curpos		//<INT|curpos
		, bool caseopt		//<LOGICAL|case_opt

	);
	PropertyHandle* Select(
		  PropertyHandle* prophdlref		//<PropertyHandle|prophdl_ref
		, string expression		//<STRING|expression

	);
	void SetActionResult(
		  string resultstring		//<STRING|result_string

	);
	bool SetContextVariables(
		  string contextstring		//<STRING|context_string

	);
	void SetDirty();
	bool SetDynLength();
	bool SetGenAttribute(
		  string attrstr		//<STRING|attrstr
		, string proppath		//<STRING|prop_path

	);
	bool SetKey(
		  string identkey		//<Key|ident_key

	);
	void SetModified();
	bool SetNormalized(
		  int longval		//<INT|long_val

	);
	bool SetOrder(
		  string keyname		//<STRING|key_name
		, string attrstr		//<STRING|attrstr

	);
	bool SetSelection(
		  string expression		//<STRING|expression

	);
	bool SetSortKey(
		  string sortkey		//<Key|sort_key

	);
	bool SetTransientProperty(
		  PropertyHandle* prophdl		//<PropertyHandle|prop_hdl

	);
	bool SetType(
		  string strnames		//<STRING|strnames

	);
	bool SetUpdate(
		  bool pcheckupdate		//<LOGICAL|check_update

	);
	PropertyHandle* SetValue(
		  PropertyHandle* cprophdl		//<PropertyHandle|cprop_hdl
		, bool pcheckupdate		//<LOGICAL|check_update

	);
	PropertyHandle* SetValueBigInt(
		  int int64val		//<INT|int64_val
		, bool pcheckupdate		//<LOGICAL|check_update

	);
	PropertyHandle* SetValueBoolean(
		  bool logval		//<LOGICAL|logval
		, bool pcheckupdate		//<LOGICAL|check_update

	);
	PropertyHandle* SetValueDate(
		  long dateval		//<dbdt|date_val
		, bool pcheckupdate		//<LOGICAL|check_update

	);
	PropertyHandle* SetValueFloat(
		  float dblvalue		//<REAL|dbl_value
		, bool pcheckupdate		//<LOGICAL|check_update

	);
	PropertyHandle* SetValueInteger(
		  int longval		//<INT|long_val
		, bool pcheckupdate		//<LOGICAL|check_update

	);
	PropertyHandle* SetValueString(
		  string pstring		//<STRING|string
		, bool pcheckupdate		//<LOGICAL|check_update
		, bool convopt		//<LOGICAL|conv_opt

	);
	PropertyHandle* SetValueTime(
		  long timeval		//<dbtm|time_val
		, bool pcheckupdate		//<LOGICAL|check_update

	);
	PropertyHandle* SetValueTimestamp(
		  long datetimeval		//<dttm|datetime_val
		, bool pcheckupdate		//<LOGICAL|check_update

	);
	bool SetVersion(
		  int versionnr		//<UINT|version_nr

	);
	bool SetWProtect();
	bool ToTop();
	PropertyHandle* Union(
		  PropertyHandle* prophdl1		//<PropertyHandle|prop_hdl1
		, PropertyHandle* prophdl2		//<PropertyHandle|prop_hdl2
		, string skopt		//<CHAR|sk_opt
		, bool distinct		//<LOGICAL|distinct

	);
	bool Unlock();
	bool UnlockSet();

};// end of PropertyHandle slice

class OPIFactory{

	void Destroy();
	CheckOptions* GetCheckOptions();
	DBObjectHandle* GetDBObjectHandle();
	DataSourceHandle* GetDataSourceHandle();
	DatabaseHandle* GetDatabaseHandle();
	DictionaryHandle* GetDictionaryHandle();
	ODABAClient* GetODABAClient();
	OperationHandle* GetOperationHandle();
	PropertyHandle* GetPropertyHandle();
};
class Session{

	OPIFactory* CreateSession();
	void Destroy();
	void TimeOut(int seconds);
	string getName();
};
class SessionFactory{

	Session* CreateProxy(string name);
	void shutdown();
};
};//module
