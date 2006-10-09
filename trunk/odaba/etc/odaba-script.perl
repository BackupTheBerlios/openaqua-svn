#!/bin/perl
if ( $ENV{ODABA_DEBUG} =~  /^debug$/i )
{
  $ODABA_DEBUG="debug"
} else
{
  if ( $ENV{ODABA_DEBUG} =~ /^nodebug$/i )
  {
    $ODABA_DEBUG="nodebug"
  } else
  {
    $ODABA_DEBUG=""
  }
}

# ODABA directories
$ODABA_DIR            = $ENV{"ODABA_DIR"};
$ODABA_SITE_DIR       = $ENV{"ODABA_SITE_DIR"};
$ODABA_PROJECTS_DIR   = $ENV{"ODABA_PROJECTS_DIR"};

$ODABA_ETC_DIR        = $ENV{"ODABA_ETC_DIR"};
$ODABA_SBIN_DIR       = $ENV{"ODABA_SBIN_DIR"};

$ODABA_BIN_DIR        = $ENV{"ODABA_BIN_DIR"};
$ODABA_LIB_DIR        = $ENV{"ODABA_LIB_DIR"};
$ODABA_TMP_DIR        = $ENV{"ODABA_TMP_DIR"};

# ODABA compiler&linker options
@ODABA_COMPILER_OPTIONS       = ( "-w", "-fpermissive", "-fhandle-exceptions", "-xc++" );
@ODABA_COMPILER_OPTIONS_DEBUG = ( "-w", "-fpermissive", "-fhandle-exceptions", "-xc++", "-ggdb3" );
@ODABA_INCLUDE_DIRS           = ( );
@ODABA_LINKER_OPTIONS         = ( "-L". $ODABA_LIB_DIR );
@ODABA_LINKER_OPTIONS_DEBUG   = @ODABA_LINKER_OPTIONS;
@ODABA_LIBS                   = ("-lrt", "-lpthread", "-ldl", "-lxnet", "/usr/local/lib/libstdc++.so.2.10.0" );

# ProjectDirTemplates
sub ProjectDir {
  return $ODABA_PROJECTS_DIR . "/" . @_[0];
}
sub ProjectSiteDir {
  return $ODABA_SITE_DIR . "/" . @_[0];
}
sub ProjectBatDir {
  return ProjectDir(@_[0]) . "/bat";
}  
sub ProjectSrcDir {
  return ProjectDir(@_[0]) . "/qlib";
}
sub ProjectExeDir {
  return ProjectSiteDir(@_[0]) . "/exe";
}
sub ProjectLibDir {
  return ProjectSiteDir(@_[0]) . "/lib";
}
sub ProjectTempDir {
  return ProjectSiteDir(@_[0]) . "/temp";
}

# misc
$SCRIPT_NAME =  $PROGRAM_NAME;
$SCRIPT_NAME =~ s/\\/\//g;
$SCRIPT_NAME =~ s/\/+$//g;

$o_done="	\033[71G\033[32mdone\033[m";
$o_failed="	\033[71G\033[31m\033[1mfailed\033[m";

$nl="\n";
