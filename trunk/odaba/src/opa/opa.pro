
TARGET = odaba_opa
CONFIG += odabalibs
include (../projects.pri)
QMAKE_CXXFLAGS *= -fpermissive
macx: LIBS += -L../../lib  -lodaba_greta -lodaba_zlib -lodaba_sos

isEmpty(PATH_PREFIX) {
   message "Set PATH_PREFIX"
   PATH_PREFIX=.
}


# Input
HEADERS += $$PATH_PREFIX/h/_cs_ctbl_OPA.hpp \
           $$PATH_PREFIX/h/_cs_def.h \
           $$PATH_PREFIX/h/_cs_def_OPA.hpp \
           $$PATH_PREFIX/h/_cs_opa.h \
           $$PATH_PREFIX/h/_cs_OPA.h \
           $$PATH_PREFIX/h/_cs_tbl_OPA.hpp \
           $$PATH_PREFIX/h/_sc_ctbl_OPA.hpp \
           $$PATH_PREFIX/h/_sc_def.h \
           $$PATH_PREFIX/h/_sc_def_OPA.hpp \
           $$PATH_PREFIX/h/_sc_opa.h \
           $$PATH_PREFIX/h/_sc_tbl_OPA.hpp \
           $$PATH_PREFIX/h/ccounts.h \
           $$PATH_PREFIX/h/cCS_ParmTypes.h \
           $$PATH_PREFIX/h/cdbres.h \
           $$PATH_PREFIX/h/cdlhdl.h \
           $$PATH_PREFIX/h/cEBIo.h \
           $$PATH_PREFIX/h/cEventClasses.h \
           $$PATH_PREFIX/h/cevtp.h \
           $$PATH_PREFIX/h/cExecutionTypes.h \
           $$PATH_PREFIX/h/cExtInstTypes.h \
           $$PATH_PREFIX/h/cglobals.h \
           $$PATH_PREFIX/h/cMAT_Types.h \
           $$PATH_PREFIX/h/cMBHdr.h \
           $$PATH_PREFIX/h/cNodeTypes.h \
           $$PATH_PREFIX/h/coclient.h \
           $$PATH_PREFIX/h/cODC_Privilege.h \
           $$PATH_PREFIX/h/coserver.h \
           $$PATH_PREFIX/h/cparser.h \
           $$PATH_PREFIX/h/cPathTypes.h \
           $$PATH_PREFIX/h/cPIADEF.h \
           $$PATH_PREFIX/h/cRBHdr.h \
           $$PATH_PREFIX/h/cRecoveryType.h \
           $$PATH_PREFIX/h/cResourceTypes.h \
           $$PATH_PREFIX/h/cRootBase_Types.h \
           $$PATH_PREFIX/h/cSBHdr.h \
           $$PATH_PREFIX/h/csfctp.h \
           $$PATH_PREFIX/h/csysstr.h \
           $$PATH_PREFIX/h/cSystemPropertyTypes.h \
           $$PATH_PREFIX/h/exdext.h \
           $$PATH_PREFIX/h/gentyps.h \
           $$PATH_PREFIX/h/iCTXInterface.h \
           $$PATH_PREFIX/h/idbd.h \
           $$PATH_PREFIX/h/intmac.h \
           $$PATH_PREFIX/h/iopai.h \
           $$PATH_PREFIX/h/ljump.h \
           $$PATH_PREFIX/h/nodetst.h \
           $$PATH_PREFIX/h/oel_coun.h \
           $$PATH_PREFIX/h/perfchk.h \
           $$PATH_PREFIX/h/popa7.h \
           $$PATH_PREFIX/h/s_cs_OPA.hpp \
           $$PATH_PREFIX/h/s_cs_opa7.hpp \
           $$PATH_PREFIX/h/s_err.hpp \
           $$PATH_PREFIX/h/s_if_CTX_DBBase.hpp \
           $$PATH_PREFIX/h/s_if_CTX_Structure.hpp \
           $$PATH_PREFIX/h/s_if_SystemClass.hpp \
           $$PATH_PREFIX/h/s_sc_OPA.hpp \
           $$PATH_PREFIX/h/s_sc_opa7.hpp \
           $$PATH_PREFIX/h/sACAttribute.hpp \
           $$PATH_PREFIX/h/sacb.hpp \
           $$PATH_PREFIX/h/sACBaseStruct.hpp \
           $$PATH_PREFIX/h/sACDefine.hpp \
           $$PATH_PREFIX/h/sACElmView.hpp \
           $$PATH_PREFIX/h/sACExtend.hpp \
           $$PATH_PREFIX/h/sACGenericAttr.hpp \
           $$PATH_PREFIX/h/sACHierNode.hpp \
           $$PATH_PREFIX/h/sACMetaAttribute.hpp \
           $$PATH_PREFIX/h/sACNode.hpp \
           $$PATH_PREFIX/h/sACObject.hpp \
           $$PATH_PREFIX/h/sACOperand.hpp \
           $$PATH_PREFIX/h/sACOperation.hpp \
           $$PATH_PREFIX/h/sACOPGroupBy.hpp \
           $$PATH_PREFIX/h/sACOPJoin.hpp \
           $$PATH_PREFIX/h/sACOPOutput.hpp \
           $$PATH_PREFIX/h/sACOPProduct.hpp \
           $$PATH_PREFIX/h/sACOPSelect.hpp \
           $$PATH_PREFIX/h/sACOPWhere.hpp \
           $$PATH_PREFIX/h/sACPath.hpp \
           $$PATH_PREFIX/h/sACPath_old.hpp \
           $$PATH_PREFIX/h/sACPathElement.hpp \
           $$PATH_PREFIX/h/sACPathNode.hpp \
           $$PATH_PREFIX/h/sACProperty.hpp \
           $$PATH_PREFIX/h/sACReference.hpp \
           $$PATH_PREFIX/h/sACRelationship.hpp \
           $$PATH_PREFIX/h/sACShareBase.hpp \
           $$PATH_PREFIX/h/sACSRTNode.hpp \
           $$PATH_PREFIX/h/sACStructure.hpp \
           $$PATH_PREFIX/h/sACSubNode.hpp \
           $$PATH_PREFIX/h/sACSysProperty.hpp \
           $$PATH_PREFIX/h/sact.hpp \
           $$PATH_PREFIX/h/sACTempExtent.hpp \
           $$PATH_PREFIX/h/sACTopNode.hpp \
           $$PATH_PREFIX/h/sACTransient.hpp \
           $$PATH_PREFIX/h/sACTransientReference.hpp \
           $$PATH_PREFIX/h/sACUpdate.hpp \
           $$PATH_PREFIX/h/sACView.hpp \
           $$PATH_PREFIX/h/sACViewProperty.hpp \
           $$PATH_PREFIX/h/sbinti.hpp \
           $$PATH_PREFIX/h/sBNF_OSI.hpp \
           $$PATH_PREFIX/h/sBNFExpData.hpp \
           $$PATH_PREFIX/h/sbnode.hpp \
           $$PATH_PREFIX/h/sCACObject.hpp \
           $$PATH_PREFIX/h/sCAU_State.hpp \
           $$PATH_PREFIX/h/sCAU_StateAction.hpp \
           $$PATH_PREFIX/h/sCClient.hpp \
           $$PATH_PREFIX/h/sCDBHandle.hpp \
           $$PATH_PREFIX/h/sCDictionary.hpp \
           $$PATH_PREFIX/h/scinti.hpp \
           $$PATH_PREFIX/h/scka.hpp \
           $$PATH_PREFIX/h/scke.hpp \
           $$PATH_PREFIX/h/sckh.hpp \
           $$PATH_PREFIX/h/sckm.hpp \
           $$PATH_PREFIX/h/sClientConnection.hpp \
           $$PATH_PREFIX/h/sCNode.hpp \
           $$PATH_PREFIX/h/sCNodeAttribute.hpp \
           $$PATH_PREFIX/h/sCodeSet.hpp \
           $$PATH_PREFIX/h/sCOperation.hpp \
           $$PATH_PREFIX/h/sCPE.hpp \
           $$PATH_PREFIX/h/scpt.hpp \
           $$PATH_PREFIX/h/sCSAccess.hpp \
           $$PATH_PREFIX/h/scse.hpp \
           $$PATH_PREFIX/h/sCServer.hpp \
           $$PATH_PREFIX/h/sCSHandle.hpp \
           $$PATH_PREFIX/h/sCSHandleList.hpp \
           $$PATH_PREFIX/h/sCSInstance.hpp \
           $$PATH_PREFIX/h/sCSInstanceList.hpp \
           $$PATH_PREFIX/h/sCSInstHeader.hpp \
           $$PATH_PREFIX/h/sCSLHandleList.hpp \
           $$PATH_PREFIX/h/sCSLLHandleList.hpp \
           $$PATH_PREFIX/h/sCSNode.hpp \
           $$PATH_PREFIX/h/scst.hpp \
           $$PATH_PREFIX/h/scte.hpp \
           $$PATH_PREFIX/h/sctr.hpp \
           $$PATH_PREFIX/h/sCTX_DataBase.hpp \
           $$PATH_PREFIX/h/sCTX_DBBase.hpp \
           $$PATH_PREFIX/h/sCTX_Object.hpp \
           $$PATH_PREFIX/h/sCTX_Property.hpp \
           $$PATH_PREFIX/h/sCTX_Structure.hpp \
           $$PATH_PREFIX/h/sCTXInterface.h \
           $$PATH_PREFIX/h/sDATE_TIME.hpp \
           $$PATH_PREFIX/h/sdb_RootBase.hpp \
           $$PATH_PREFIX/h/sDBEvent.hpp \
           $$PATH_PREFIX/h/sDBEventList.hpp \
           $$PATH_PREFIX/h/sDBExtend.hpp \
           $$PATH_PREFIX/h/sdbf.hpp \
           $$PATH_PREFIX/h/sDBField_CHAR.hpp \
           $$PATH_PREFIX/h/sDBField_DATE.hpp \
           $$PATH_PREFIX/h/sDBField_DATETIME.hpp \
           $$PATH_PREFIX/h/sDBField_INT.hpp \
           $$PATH_PREFIX/h/sDBField_REAL.hpp \
           $$PATH_PREFIX/h/sDBField_TIME.hpp \
           $$PATH_PREFIX/h/sDBFieldDef.hpp \
           $$PATH_PREFIX/h/sDBFieldList.hpp \
           $$PATH_PREFIX/h/sDBHandle.hpp \
           $$PATH_PREFIX/h/sDBHeader.hpp \
           $$PATH_PREFIX/h/sDBIndex.hpp \
           $$PATH_PREFIX/h/sDBIndexList.hpp \
           $$PATH_PREFIX/h/sDBInfo.hpp \
           $$PATH_PREFIX/h/sDBQOutput.hpp \
           $$PATH_PREFIX/h/sDBQuery.hpp \
           $$PATH_PREFIX/h/sDBReaction.hpp \
           $$PATH_PREFIX/h/sDBResource.hpp \
           $$PATH_PREFIX/h/sDBStructDef.hpp \
           $$PATH_PREFIX/h/sDBViewGroup.hpp \
           $$PATH_PREFIX/h/sDBViewGroupCase.hpp \
           $$PATH_PREFIX/h/sDBViewPath.hpp \
           $$PATH_PREFIX/h/sDBViewStructDef.hpp \
           $$PATH_PREFIX/h/sDelInstEntry.hpp \
           $$PATH_PREFIX/h/sDictDescriptor.hpp \
           $$PATH_PREFIX/h/sDictionary.hpp \
           $$PATH_PREFIX/h/sDifferenceList.hpp \
           $$PATH_PREFIX/h/sDiffListBuffer.hpp \
           $$PATH_PREFIX/h/sDiffListEntry.hpp \
           $$PATH_PREFIX/h/sDiffListList.hpp \
           $$PATH_PREFIX/h/sDiffListListEntry.hpp \
           $$PATH_PREFIX/h/sdisel.hpp \
           $$PATH_PREFIX/h/sDLL_Handle.hpp \
           $$PATH_PREFIX/h/sdsc.hpp \
           $$PATH_PREFIX/h/seb_Buffer.hpp \
           $$PATH_PREFIX/h/seb_BufferEntry.hpp \
           $$PATH_PREFIX/h/seb_ClusterPool.hpp \
           $$PATH_PREFIX/h/sEB_DAHeader.hpp \
           $$PATH_PREFIX/h/seb_DataArea.hpp \
           $$PATH_PREFIX/h/sEB_extDAHeader.hpp \
           $$PATH_PREFIX/h/sEB_extHeader.hpp \
           $$PATH_PREFIX/h/sEB_extMBHeader.hpp \
           $$PATH_PREFIX/h/sEB_extRBHeader.hpp \
           $$PATH_PREFIX/h/sEB_extSBHeader.hpp \
           $$PATH_PREFIX/h/sEB_Header.hpp \
           $$PATH_PREFIX/h/seb_MainBase.hpp \
           $$PATH_PREFIX/h/sEB_MBHeader.hpp \
           $$PATH_PREFIX/h/sEB_Number.hpp \
           $$PATH_PREFIX/h/sEB_RBHeader.hpp \
           $$PATH_PREFIX/h/seb_RootBase.hpp \
           $$PATH_PREFIX/h/sEB_SBHeader.hpp \
           $$PATH_PREFIX/h/seb_SubBase.hpp \
           $$PATH_PREFIX/h/sEBDataArea.hpp \
           $$PATH_PREFIX/h/sEBI.hpp \
           $$PATH_PREFIX/h/sEBMainBase.hpp \
           $$PATH_PREFIX/h/sEBRootBase.hpp \
           $$PATH_PREFIX/h/sEBSF.hpp \
           $$PATH_PREFIX/h/sEBSubBase.hpp \
           $$PATH_PREFIX/h/sEntryEvent.hpp \
           $$PATH_PREFIX/h/sEntryEventList.hpp \
           $$PATH_PREFIX/h/sEntryHandle.hpp \
           $$PATH_PREFIX/h/sEnumValue.hpp \
           $$PATH_PREFIX/h/sEnumValueList.hpp \
           $$PATH_PREFIX/h/sEventHandler.hpp \
           $$PATH_PREFIX/h/sEventLink.hpp \
           $$PATH_PREFIX/h/sEventLinkList.hpp \
           $$PATH_PREFIX/h/sEventParms.hpp \
           $$PATH_PREFIX/h/sEventProxy.hpp \
           $$PATH_PREFIX/h/sexd.hpp \
           $$PATH_PREFIX/h/sexdBBuffer.hpp \
           $$PATH_PREFIX/h/sexdBEntry.hpp \
           $$PATH_PREFIX/h/sexdBuffer.hpp \
           $$PATH_PREFIX/h/sexdEntry.hpp \
           $$PATH_PREFIX/h/sExpressionReference.hpp \
           $$PATH_PREFIX/h/sFieldDef.hpp \
           $$PATH_PREFIX/h/sFieldList.hpp \
           $$PATH_PREFIX/h/sFieldSource.hpp \
           $$PATH_PREFIX/h/sfnc_prop.hpp \
           $$PATH_PREFIX/h/sFunctionDecl.hpp \
           $$PATH_PREFIX/h/sFunctLink.hpp \
           $$PATH_PREFIX/h/sGlobalObject.hpp \
           $$PATH_PREFIX/h/sgmvl.hpp \
           $$PATH_PREFIX/h/sHandleInfo.hpp \
           $$PATH_PREFIX/h/sHInstEntry.hpp \
           $$PATH_PREFIX/h/sicb.hpp \
           $$PATH_PREFIX/h/sicbe.hpp \
           $$PATH_PREFIX/h/sICEntry.hpp \
           $$PATH_PREFIX/h/sieh.hpp \
           $$PATH_PREFIX/h/sIFClass.hpp \
           $$PATH_PREFIX/h/sIFFunction.hpp \
           $$PATH_PREFIX/h/sInitArea.hpp \
           $$PATH_PREFIX/h/sInstanceCache.hpp \
           $$PATH_PREFIX/h/sInstanceDescriptor.hpp \
           $$PATH_PREFIX/h/sInstancePool.hpp \
           $$PATH_PREFIX/h/sInstBuffer.hpp \
           $$PATH_PREFIX/h/sInternalTA.hpp \
           $$PATH_PREFIX/h/sinti.hpp \
           $$PATH_PREFIX/h/sisel.hpp \
           $$PATH_PREFIX/h/sk32.hpp \
           $$PATH_PREFIX/h/sKeyCache.hpp \
           $$PATH_PREFIX/h/sKeyCacheBase.hpp \
           $$PATH_PREFIX/h/sKeyCacheEntry.hpp \
           $$PATH_PREFIX/h/sKeyCacheFile.hpp \
           $$PATH_PREFIX/h/sKeyCacheIndex.hpp \
           $$PATH_PREFIX/h/skmvl.hpp \
           $$PATH_PREFIX/h/sLACObject.hpp \
           $$PATH_PREFIX/h/sLDBHandle.hpp \
           $$PATH_PREFIX/h/sLDBQuery.hpp \
           $$PATH_PREFIX/h/sLDictionary.hpp \
           $$PATH_PREFIX/h/slinti.hpp \
           $$PATH_PREFIX/h/sLNode.hpp \
           $$PATH_PREFIX/h/sLOperation.hpp \
           $$PATH_PREFIX/h/sMemberInfo.hpp \
           $$PATH_PREFIX/h/sMemoAccess.hpp \
           $$PATH_PREFIX/h/sModBuffer.hpp \
           $$PATH_PREFIX/h/smven.hpp \
           $$PATH_PREFIX/h/smvl.hpp \
           $$PATH_PREFIX/h/smvld.hpp \
           $$PATH_PREFIX/h/smvli.hpp \
           $$PATH_PREFIX/h/smvll.hpp \
           $$PATH_PREFIX/h/smvln.hpp \
           $$PATH_PREFIX/h/smvlp.hpp \
           $$PATH_PREFIX/h/smvlx.hpp \
           $$PATH_PREFIX/h/smvlz.hpp \
           $$PATH_PREFIX/h/sNamespace.hpp \
           $$PATH_PREFIX/h/snode.hpp \
           $$PATH_PREFIX/h/snodelist.hpp \
           $$PATH_PREFIX/h/sNodeStack.hpp \
           $$PATH_PREFIX/h/sOBH_ListEntry.hpp \
           $$PATH_PREFIX/h/sObjectEntry.hpp \
           $$PATH_PREFIX/h/sObjectEntryList.hpp \
           $$PATH_PREFIX/h/sODBC_Column.hpp \
           $$PATH_PREFIX/h/sODBC_SpecialCol.hpp \
           $$PATH_PREFIX/h/sODBC_Statistics.hpp \
           $$PATH_PREFIX/h/sODBC_Table.hpp \
           $$PATH_PREFIX/h/sODBC_TypeInfo.hpp \
           $$PATH_PREFIX/h/sofifct.h \
           $$PATH_PREFIX/h/sOP_SysvarDecl.hpp \
           $$PATH_PREFIX/h/sOPA_Variables.hpp \
           $$PATH_PREFIX/h/sOPAGlobals.hpp \
           $$PATH_PREFIX/h/sopai.h \
           $$PATH_PREFIX/h/sOperation.hpp \
           $$PATH_PREFIX/h/sOperationDecl.hpp \
           $$PATH_PREFIX/h/sParmString.hpp \
           $$PATH_PREFIX/h/sPCSHandle.hpp \
           $$PATH_PREFIX/h/sPoolTA.hpp \
           $$PATH_PREFIX/h/sPoolTA_old.hpp \
           $$PATH_PREFIX/h/sProcessEventHandler.hpp \
           $$PATH_PREFIX/h/sPropAllocation.hpp \
           $$PATH_PREFIX/h/sPropertyPath.hpp \
           $$PATH_PREFIX/h/sref.hpp \
           $$PATH_PREFIX/h/sRefAccess.hpp \
           $$PATH_PREFIX/h/srefEntry.hpp \
           $$PATH_PREFIX/h/srefp.hpp \
           $$PATH_PREFIX/h/srefs.hpp \
           $$PATH_PREFIX/h/srefTable.hpp \
           $$PATH_PREFIX/h/srefx.hpp \
           $$PATH_PREFIX/h/sRootBaseEntry.hpp \
           $$PATH_PREFIX/h/sRootBaseTA.hpp \
           $$PATH_PREFIX/h/srvr.hpp \
           $$PATH_PREFIX/h/srvre.hpp \
           $$PATH_PREFIX/h/srvrh.hpp \
           $$PATH_PREFIX/h/sSC_CacheInfo.hpp \
           $$PATH_PREFIX/h/sSC_Connection.hpp \
           $$PATH_PREFIX/h/sSC_ConnectionCache.hpp \
           $$PATH_PREFIX/h/sSC_Database.hpp \
           $$PATH_PREFIX/h/sSC_DBObject.hpp \
           $$PATH_PREFIX/h/sSC_Dictionary.hpp \
           $$PATH_PREFIX/h/sSC_Handle.hpp \
           $$PATH_PREFIX/h/sSC_Operation.hpp \
           $$PATH_PREFIX/h/sSC_Property.hpp \
           $$PATH_PREFIX/h/sSC_Query.hpp \
           $$PATH_PREFIX/h/sServerConnection.hpp \
           $$PATH_PREFIX/h/sServices.hpp \
           $$PATH_PREFIX/h/ssinti.hpp \
           $$PATH_PREFIX/h/sStatEntry.hpp \
           $$PATH_PREFIX/h/sstest.hpp \
           $$PATH_PREFIX/h/sStructAccess.hpp \
           $$PATH_PREFIX/h/sStructDef.hpp \
           $$PATH_PREFIX/h/sSystemClass.hpp \
           $$PATH_PREFIX/h/sSystemDict.hpp \
           $$PATH_PREFIX/h/sSystemObject.hpp \
           $$PATH_PREFIX/h/sTABuffer.hpp \
           $$PATH_PREFIX/h/sTestOPA2.hpp \
           $$PATH_PREFIX/h/sTypeKey.hpp \
           $$PATH_PREFIX/h/sVersionEntry.hpp \
           $$PATH_PREFIX/h/svinti.hpp \
           $$PATH_PREFIX/h/sWorkspace.hpp \
           $$PATH_PREFIX/h/sWorkspaceEntry.hpp \
           $$PATH_PREFIX/h/sWSList.hpp \
           $$PATH_PREFIX/h/sxx.hpp \
           $$PATH_PREFIX/h/xxBVFilter.hpp \
           $$PATH_PREFIX/h/xxBViewDef.hpp \
           $$PATH_PREFIX/h/xxBViewDefEntry.hpp \
           $$PATH_PREFIX/h/xxBViewGroup.hpp \
           $$PATH_PREFIX/h/xxBViewGroupCase.hpp \
           $$PATH_PREFIX/h/xxBViewPath.hpp \
           $$PATH_PREFIX/h/xxBViewStructDef.hpp \
           $$PATH_PREFIX/h/xxBVOrder.hpp \
           $$PATH_PREFIX/h/xxBVProperty.hpp 
           
SOURCES += $$PATH_PREFIX/qlib/OSI.cpp \
        $$PATH_PREFIX/qlib/ACAttribute.cpp \
        $$PATH_PREFIX/qlib/ACBaseStruct.cpp \
        $$PATH_PREFIX/qlib/ACExtend.cpp \
        $$PATH_PREFIX/qlib/ACGenericAttr.cpp \
        $$PATH_PREFIX/qlib/ACHierNode.cpp \
        $$PATH_PREFIX/qlib/ACMetaAttribute.cpp \
        $$PATH_PREFIX/qlib/ACNode.cpp \
        $$PATH_PREFIX/qlib/ACOPGroupBy.cpp \
        $$PATH_PREFIX/qlib/ACOPJoin.cpp \
        $$PATH_PREFIX/qlib/ACOPOutput.cpp \
        $$PATH_PREFIX/qlib/ACOPProduct.cpp \
        $$PATH_PREFIX/qlib/ACOPSelect.cpp \
        $$PATH_PREFIX/qlib/ACOPWhere.cpp \
        $$PATH_PREFIX/qlib/ACObject.cpp \
        $$PATH_PREFIX/qlib/ACOperand.cpp \
        $$PATH_PREFIX/qlib/ACOperation.cpp \
        $$PATH_PREFIX/qlib/ACPath.cpp \
        $$PATH_PREFIX/qlib/ACPathNode.cpp \
        $$PATH_PREFIX/qlib/ACProperty.cpp \
        $$PATH_PREFIX/qlib/ACReference.cpp \
        $$PATH_PREFIX/qlib/ACRelationship.cpp \
        $$PATH_PREFIX/qlib/ACSRTNode.cpp \
        $$PATH_PREFIX/qlib/ACShareBase.cpp \
        $$PATH_PREFIX/qlib/ACStructure.cpp \
        $$PATH_PREFIX/qlib/ACSubNode.cpp \
        $$PATH_PREFIX/qlib/ACTempExtent.cpp \
        $$PATH_PREFIX/qlib/ACTopNode.cpp \
        $$PATH_PREFIX/qlib/ACTransient.cpp \
        $$PATH_PREFIX/qlib/ACTransientReference.cpp \
        $$PATH_PREFIX/qlib/BNFExpData.cpp \
        $$PATH_PREFIX/qlib/CACObject.cpp \
        $$PATH_PREFIX/qlib/CClient.cpp \
        $$PATH_PREFIX/qlib/CDBHandle.cpp \
        $$PATH_PREFIX/qlib/CDictionary.cpp \
        $$PATH_PREFIX/qlib/CNode.cpp \
        $$PATH_PREFIX/qlib/CNodeAttribute.cpp \
        $$PATH_PREFIX/qlib/COperation.cpp \
        $$PATH_PREFIX/qlib/CPE.cpp \
        $$PATH_PREFIX/qlib/CSHandle.cpp \
        $$PATH_PREFIX/qlib/CSHandleList.cpp \
        $$PATH_PREFIX/qlib/CSInstHeader.cpp \
        $$PATH_PREFIX/qlib/CSInstance.cpp \
        $$PATH_PREFIX/qlib/CSInstanceList.cpp \
        $$PATH_PREFIX/qlib/CSLHandleList.cpp \
        $$PATH_PREFIX/qlib/CSLLHandleList.cpp \
        $$PATH_PREFIX/qlib/CSNode.cpp \
        $$PATH_PREFIX/qlib/CServer.cpp \
        $$PATH_PREFIX/qlib/CTX_DBBase.cpp \
        $$PATH_PREFIX/qlib/CTX_DataBase.cpp \
        $$PATH_PREFIX/qlib/CTX_Object.cpp \
        $$PATH_PREFIX/qlib/CTX_Property.cpp \
        $$PATH_PREFIX/qlib/CTX_Structure.cpp \
        $$PATH_PREFIX/qlib/ClientConnection.cpp \
        $$PATH_PREFIX/qlib/DATE_TIME.cpp \
        $$PATH_PREFIX/qlib/DBEvent.cpp \
        $$PATH_PREFIX/qlib/DBEventList.cpp \
        $$PATH_PREFIX/qlib/DBExtend.cpp \
        $$PATH_PREFIX/qlib/DBFieldDef.cpp \
        $$PATH_PREFIX/qlib/DBFieldList.cpp \
        $$PATH_PREFIX/qlib/DBField_CHAR.cpp \
        $$PATH_PREFIX/qlib/DBField_DATE.cpp \
        $$PATH_PREFIX/qlib/DBField_DATETIME.cpp \
        $$PATH_PREFIX/qlib/DBField_INT.cpp \
        $$PATH_PREFIX/qlib/DBField_REAL.cpp \
        $$PATH_PREFIX/qlib/DBField_TIME.cpp \
        $$PATH_PREFIX/qlib/DBHandle.cpp \
        $$PATH_PREFIX/qlib/DBHeader.cpp \
        $$PATH_PREFIX/qlib/DBIndex.cpp \
        $$PATH_PREFIX/qlib/DBIndexList.cpp \
        $$PATH_PREFIX/qlib/DBInfo.cpp \
        $$PATH_PREFIX/qlib/DBQOutput.cpp \
        $$PATH_PREFIX/qlib/DBReaction.cpp \
        $$PATH_PREFIX/qlib/DBResource.cpp \
        $$PATH_PREFIX/qlib/DBStructDef.cpp \
        $$PATH_PREFIX/qlib/DBViewGroup.cpp \
        $$PATH_PREFIX/qlib/DBViewGroupCase.cpp \
        $$PATH_PREFIX/qlib/DBViewPath.cpp \
        $$PATH_PREFIX/qlib/DBViewStructDef.cpp \
        $$PATH_PREFIX/qlib/DLL_Handle.cpp \
        $$PATH_PREFIX/qlib/DelInstEntry.cpp \
        $$PATH_PREFIX/qlib/DictDescriptor.cpp \
        $$PATH_PREFIX/qlib/Dictionary.cpp \
        $$PATH_PREFIX/qlib/DiffListBuffer.cpp \
        $$PATH_PREFIX/qlib/DiffListEntry.cpp \
        $$PATH_PREFIX/qlib/DiffListList.cpp \
        $$PATH_PREFIX/qlib/DiffListListEntry.cpp \
        $$PATH_PREFIX/qlib/DifferenceList.cpp \
        $$PATH_PREFIX/qlib/EBDataArea.cpp \
        $$PATH_PREFIX/qlib/EBI.cpp \
        $$PATH_PREFIX/qlib/EBMainBase.cpp \
        $$PATH_PREFIX/qlib/EBRootBase.cpp \
        $$PATH_PREFIX/qlib/EBSubBase.cpp \
        $$PATH_PREFIX/qlib/EB_DAHeader.cpp \
        $$PATH_PREFIX/qlib/EB_Header.cpp \
        $$PATH_PREFIX/qlib/EB_MBHeader.cpp \
        $$PATH_PREFIX/qlib/EB_Number.cpp \
        $$PATH_PREFIX/qlib/EB_RBHeader.cpp \
        $$PATH_PREFIX/qlib/EB_SBHeader.cpp \
        $$PATH_PREFIX/qlib/EB_extDAHeader.cpp \
        $$PATH_PREFIX/qlib/EB_extHeader.cpp \
        $$PATH_PREFIX/qlib/EB_extMBHeader.cpp \
        $$PATH_PREFIX/qlib/EB_extRBHeader.cpp \
        $$PATH_PREFIX/qlib/EB_extSBHeader.cpp \
        $$PATH_PREFIX/qlib/EntryEvent.cpp \
        $$PATH_PREFIX/qlib/EntryEventList.cpp \
        $$PATH_PREFIX/qlib/EntryHandle.cpp \
        $$PATH_PREFIX/qlib/EventHandler.cpp \
        $$PATH_PREFIX/qlib/EventLink.cpp \
        $$PATH_PREFIX/qlib/EventLinkList.cpp \
        $$PATH_PREFIX/qlib/EventParms.cpp \
        $$PATH_PREFIX/qlib/EventProxy.cpp \
        $$PATH_PREFIX/qlib/ExpressionReference.cpp \
        $$PATH_PREFIX/qlib/FieldDef.cpp \
        $$PATH_PREFIX/qlib/FieldList.cpp \
        $$PATH_PREFIX/qlib/FieldSource.cpp \
        $$PATH_PREFIX/qlib/FunctLink.cpp \
        $$PATH_PREFIX/qlib/GlobalObject.cpp \
        $$PATH_PREFIX/qlib/HInstEntry.cpp \
        $$PATH_PREFIX/qlib/HandleInfo.cpp \
        $$PATH_PREFIX/qlib/ICEntry.cpp \
        $$PATH_PREFIX/qlib/IFClass.cpp \
        $$PATH_PREFIX/qlib/IFFunction.cpp \
        $$PATH_PREFIX/qlib/InitArea.cpp \
        $$PATH_PREFIX/qlib/InstBuffer.cpp \
        $$PATH_PREFIX/qlib/InstanceCache.cpp \
        $$PATH_PREFIX/qlib/InstanceDescriptor.cpp \
        $$PATH_PREFIX/qlib/InstancePool.cpp \
        $$PATH_PREFIX/qlib/InternalTA.cpp \
        $$PATH_PREFIX/qlib/KeyCache.cpp \
        $$PATH_PREFIX/qlib/KeyCacheBase.cpp \
        $$PATH_PREFIX/qlib/KeyCacheEntry.cpp \
        $$PATH_PREFIX/qlib/KeyCacheFile.cpp \
        $$PATH_PREFIX/qlib/KeyCacheIndex.cpp \
        $$PATH_PREFIX/qlib/LACObject.cpp \
        $$PATH_PREFIX/qlib/LDBHandle.cpp \
        $$PATH_PREFIX/qlib/LDictionary.cpp \
        $$PATH_PREFIX/qlib/LNode.cpp \
        $$PATH_PREFIX/qlib/LOperation.cpp \
        $$PATH_PREFIX/qlib/MemberInfo.cpp \
        $$PATH_PREFIX/qlib/ModBuffer.cpp \
        $$PATH_PREFIX/qlib/Namespace.cpp \
        $$PATH_PREFIX/qlib/NodeStack.cpp \
        $$PATH_PREFIX/qlib/OBH_ListEntry.cpp \
        $$PATH_PREFIX/qlib/OPAGlobals.cpp \
        $$PATH_PREFIX/qlib/OPA_Variables.cpp \
        $$PATH_PREFIX/qlib/ObjectEntry.cpp \
        $$PATH_PREFIX/qlib/ObjectEntryList.cpp \
        $$PATH_PREFIX/qlib/Operation.cpp \
        $$PATH_PREFIX/qlib/PCSHandle.cpp \
        $$PATH_PREFIX/qlib/ParmString.cpp \
        $$PATH_PREFIX/qlib/PoolTA.cpp \
        $$PATH_PREFIX/qlib/ProcessEventHandler.cpp \
        $$PATH_PREFIX/qlib/PropertyPath.cpp \
        $$PATH_PREFIX/qlib/RefAccess.cpp \
        $$PATH_PREFIX/qlib/RootBaseEntry.cpp \
        $$PATH_PREFIX/qlib/RootBaseTA.cpp \
        $$PATH_PREFIX/qlib/SC_CacheInfo.cpp \
        $$PATH_PREFIX/qlib/SC_Connection.cpp \
        $$PATH_PREFIX/qlib/SC_ConnectionCache.cpp \
        $$PATH_PREFIX/qlib/SC_DBObject.cpp \
        $$PATH_PREFIX/qlib/SC_Database.cpp \
        $$PATH_PREFIX/qlib/SC_Dictionary.cpp \
        $$PATH_PREFIX/qlib/SC_Handle.cpp \
        $$PATH_PREFIX/qlib/SC_Operation.cpp \
        $$PATH_PREFIX/qlib/SC_Property.cpp \
        $$PATH_PREFIX/qlib/ServerConnection.cpp \
        $$PATH_PREFIX/qlib/Services.cpp \
        $$PATH_PREFIX/qlib/StatEntry.cpp \
        $$PATH_PREFIX/qlib/StructAccess.cpp \
        $$PATH_PREFIX/qlib/StructDef.cpp \
        $$PATH_PREFIX/qlib/SystemClass.cpp \
        $$PATH_PREFIX/qlib/SystemDict.cpp \
        $$PATH_PREFIX/qlib/SystemObject.cpp \
        $$PATH_PREFIX/qlib/TABuffer.cpp \
        $$PATH_PREFIX/qlib/TypeKey.cpp \
        $$PATH_PREFIX/qlib/VersionEntry.cpp \
        $$PATH_PREFIX/qlib/WSList.cpp \
        $$PATH_PREFIX/qlib/Workspace.cpp \
        $$PATH_PREFIX/qlib/WorkspaceEntry.cpp \
        $$PATH_PREFIX/qlib/_cs_opa.cpp \
        $$PATH_PREFIX/qlib/acb.cpp \
        $$PATH_PREFIX/qlib/binti.cpp \
        $$PATH_PREFIX/qlib/bnode.cpp \
        $$PATH_PREFIX/qlib/cinti.cpp \
        $$PATH_PREFIX/qlib/cka.cpp \
        $$PATH_PREFIX/qlib/cke.cpp \
        $$PATH_PREFIX/qlib/ckh.cpp \
        $$PATH_PREFIX/qlib/ckm.cpp \
        $$PATH_PREFIX/qlib/cpt.cpp \
        $$PATH_PREFIX/qlib/cse.cpp \
        $$PATH_PREFIX/qlib/cte.cpp \
        $$PATH_PREFIX/qlib/ctr.cpp \
        $$PATH_PREFIX/qlib/db_RootBase.cpp \
        $$PATH_PREFIX/qlib/dbf.cpp \
        $$PATH_PREFIX/qlib/disel.cpp \
        $$PATH_PREFIX/qlib/dsc.cpp \
        $$PATH_PREFIX/qlib/eb_Buffer.cpp \
        $$PATH_PREFIX/qlib/eb_BufferEntry.cpp \
        $$PATH_PREFIX/qlib/eb_ClusterPool.cpp \
        $$PATH_PREFIX/qlib/eb_DataArea.cpp \
        $$PATH_PREFIX/qlib/eb_MainBase.cpp \
        $$PATH_PREFIX/qlib/eb_RootBase.cpp \
        $$PATH_PREFIX/qlib/eb_SubBase.cpp \
        $$PATH_PREFIX/qlib/exd.cpp \
        $$PATH_PREFIX/qlib/exdBBuffer.cpp \
        $$PATH_PREFIX/qlib/exdBEntry.cpp \
        $$PATH_PREFIX/qlib/exdBuffer.cpp \
        $$PATH_PREFIX/qlib/exdEntry.cpp \
        $$PATH_PREFIX/qlib/gmvl.cpp \
        $$PATH_PREFIX/qlib/icb.cpp \
        $$PATH_PREFIX/qlib/icbe.cpp \
        $$PATH_PREFIX/qlib/ieh.cpp \
        $$PATH_PREFIX/qlib/inti.cpp \
        $$PATH_PREFIX/qlib/isel.cpp \
        $$PATH_PREFIX/qlib/kmvl.cpp \
        $$PATH_PREFIX/qlib/linti.cpp \
        $$PATH_PREFIX/qlib/mven.cpp \
        $$PATH_PREFIX/qlib/mvl.cpp \
        $$PATH_PREFIX/qlib/mvld.cpp \
        $$PATH_PREFIX/qlib/mvli.cpp \
        $$PATH_PREFIX/qlib/mvll.cpp \
        $$PATH_PREFIX/qlib/mvln.cpp \
        $$PATH_PREFIX/qlib/mvlp.cpp \
        $$PATH_PREFIX/qlib/mvlx.cpp \
        $$PATH_PREFIX/qlib/node.cpp \
        $$PATH_PREFIX/qlib/nodelist.cpp \
        $$PATH_PREFIX/qlib/opai.cpp \
        $$PATH_PREFIX/qlib/ref.cpp \
        $$PATH_PREFIX/qlib/refEntry.cpp \
        $$PATH_PREFIX/qlib/refTable.cpp \
        $$PATH_PREFIX/qlib/refp.cpp \
        $$PATH_PREFIX/qlib/refs.cpp \
        $$PATH_PREFIX/qlib/refx.cpp \
        $$PATH_PREFIX/qlib/rvr.cpp \
        $$PATH_PREFIX/qlib/rvre.cpp \
        $$PATH_PREFIX/qlib/rvrh.cpp \
        $$PATH_PREFIX/qlib/sinti.cpp \

        
#$$PATH_PREFIX/qlib/CTXInterface.cpp \        