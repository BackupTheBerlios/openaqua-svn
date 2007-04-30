<#-- This is a freemarker comment-->

-- This is a generated file, dont modify it manually
--------------------------------------------------------
-- SYNTAX PRODUCED BY: AndroMDA ASN.1 Cartridge
-- SYNTAX PRODUCED AT: asnHelper
-- SYNTAX LOCATION ON: ${file.fullyQualifiedNamePath}.asn


RE-07-01 DEFINITIONS IMPLICIT TAGS ::=

BEGIN

RETransferBatch ::= [APPLICATION 80] SEQUENCE
{
     headerRecord                      HeaderRecord,
     detailRecordList                  DetailRecordList
}


Properties
<#list file.properties as property>
	property: ${property.type} ${property.fullyQualifiedNamePath}
</#list>

allProperties
<#list file.allProperties as tooff>
	tooff: ${tooff.fullyQualifiedNamePath}
</#list>

allAssociatedClasses
<#list file.allAssociatedClasses as assoc>
	assoc: ${assoc.fullyQualifiedNamePath}
</#list>





END
