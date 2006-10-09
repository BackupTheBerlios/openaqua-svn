#!/bin/bash



#set and test args
args=`getopt cvs $*`
if [ $? != 0 ]
then
        echo
        echo "   Usage: `basename $0` " ;
        echo "   -c -lean      remove object files and core files" ;
        echo "   -v -eryclean  clean + temp files, core files, bins, libs, tmp" ;
        echo "   -s -vn        veryclean + remove all svn stuff " ;
        echo
        exit 1;
fi



set -- $args
for i
do
  case "$i" in
        -c) shift;echo "set MAKE CLEAN";      CLEAN=1;;
        -v) shift;echo "set MAKE VERYCLEAN";  CLEAN=1; VERYCLEAN=1;;
        -s) shift;echo "set MAKE REMOVE SVN"; CLEAN=1; VERYCLEAN=1; REMOVESVN=1;;
  esac
done
#default
CLEAN=1
  


#do clean
if [ $CLEAN ] 
then
   echo "SHOW SVN STATUS ...";
   svn status
   echo "MAKE CLEAN ...";
   qmake 
   make clean >/dev/null 2>&1
   find . -name 2 -exec rm {} \;
fi 


#do clean
if [ $VERYCLEAN ] 
then
   echo "MAKE VERY CLEAN ...";
   rm -rf build
   rm -rf framework/build/*   2>/dev/null
   rm -rf lib/*
   rm -rf bin
   rm -rf doc/*
   rm -f tags
   find . -name build -type d -exec rm -rf {} \; 2>/dev/null
   find . -name core.\* -exec rm -f {} \; 2>/dev/null
   find . -name core -exec rm -f {} \;  2>/dev/null
   find . -name \*.pcs -type f -exec rm -f {} \; 2>/dev/null
   find . -name \*.kdevses -type f -exec rm -f {} \; 2>/dev/null
   find . -name \*~ -exec rm -f {} \;  2>/dev/null
   find . -name \*.bak -exec rm -f {} \;  2>/dev/null
   find . -name \*.tmp -exec rm -f {} \;  2>/dev/null
   find . -name .obj -exec rm -rf {} \;  2>/dev/null
   find . -name .moc -exec rm -rf {} \;  2>/dev/null
   find . -name .ui -exec rm -rf {} \;  2>/dev/null
   find . -name .qrc_\*.cpp -exec rm -f {} \;  2>/dev/null
   find . -name Makefile -exec rm -f {} \; 2>/dev/null
   find . -name \*.gch -type d -exec rm -rf {} \; 2>/dev/null
   find . -name \*.app  -exec rm -rf {} \; 2>/dev/null
   find . -name Debug -type d -exec rm -rf {} \; 2>/dev/null
   rm -f  linktest/testframework/testframework \; 2>/dev/null
   rm -f  linktest/testplugins/testplugins \; 2>/dev/null
   rm -f  applications/oaletter/oaletter \; 2>/dev/null
   rm -f  applications/oaeditor/oaeditor \; 2>/dev/null
   rm -f  applications/oatravel/oatravel \; 2>/dev/null
   rm -f  applications/linktest/linktest \; 2>/dev/null
   rm -f  applications/actioneditor/actioneditor \; 2>/dev/null
   rm -f  applications/testserver/testserver \; 2>/dev/null
   rm -f  applications/testclient/testclient \; 2>/dev/null
   rm -f  applications/corbaserver/corbaserver \; 2>/dev/null
   rm -f *.pcs
fi 


#do clean
if [ $REMOVESVN ] 
then
   echo "MAKE REMOVE SVN ...";
   find . -name .svn -exec rm -rf {} \;  2>/dev/null
fi 

exit 0
