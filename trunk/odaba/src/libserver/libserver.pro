TARGET = odaba_server
CONFIG += collectlibs
include (../projects.pri)
#macx: LIBS += -L../../lib  -lodaba_greta -lodaba_zlib -lodaba_sos



message("=== Include OPA")
PATH_PREFIX=../opa
include (../opa/opa.pro)

message("===  Include OPI")
PATH_PREFIX=../opi
include (../opi/opi.pro)

message("===  Include OPS")
PATH_PREFIX=../ops
include (../ops/ops.pro)

message("===  Include OQL")
PATH_PREFIX=../oql
include (../oql/oql.pro)

message("===  Include OXML")
PATH_PREFIX=../oxml
include (../oxml/oxml.pro)
