#!/bin/bash
#################################################
# remove everything with maven
#
mvn eclipse:clean
mvn clean



#################################################
# remove potential existing original directories
#
rm -rf ./bloat/src
rm -rf ./db4ojdk1.2/src
rm -rf ./db4ojdk5/src
rm -rf ./db4oj/src
rm -rf ./db4oj.tests/src
rm -rf ./db4onqopt/src
rm -rf ./db4ounit.extensions/src
rm -rf ./db4ounit/src




#################################################
# recreate directories
#
mkdir -p ./bloat/src/main/java
mkdir -p ./db4ojdk1.2/src/main/java
mkdir -p ./db4ojdk5/src/main/java
mkdir -p ./db4oj/src/main/java/
mkdir -p ./db4oj.tests/src/main/java/
#mkdir -p ./db4oj.tests/src/main/resources
mkdir -p ./db4onqopt/src/main/java
mkdir -p ./db4ounit.extensions/src/main/java
mkdir -p ./db4ounit/src/main/java
#mkdir -p ./db4ounit/src/main/resources




#################################################
# get a fresh copy from subversion
#
svn co https://db4objects.net/svn/db4o/trunk/bloat/src							bloat/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4ojdk1.2							db4ojdk1.2/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4ojdk5								db4ojdk5/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4oj									db4oj/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4oj.tests/src					db4oj.tests/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4onqopt							db4onqopt/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4ounit/src						db4ounit/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4ounit.extensions/src			db4ounit.extensions/src/main/java




#################################################
# build the environment
mvn compile eclipse:eclipse -DdownloadSources=true




