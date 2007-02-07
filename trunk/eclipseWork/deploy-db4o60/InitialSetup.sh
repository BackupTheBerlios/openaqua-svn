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
rm -rf tmp




#################################################
# recreate directories
#
mkdir -p ./bloat/src/main/java
mkdir -p ./db4ojdk1.2/src/main/java
mkdir -p ./db4ojdk5/src/main/java
mkdir -p ./db4oj/src/main/java/
mkdir -p ./db4oj.tests/src/main/java/
mkdir -p ./db4oj.tests/src/main/resources
mkdir -p ./db4onqopt/src/main/java
mkdir -p ./db4ounit.extensions/src/main/java
mkdir -p ./db4ounit/src/main/java
mkdir -p ./db4ounit/src/main/resources



#################################################
#get the db4o file
filename=db4o-6.0-java.zip
if [ -f $filename ];
then
	echo "reuse $filename"
else
	wget http://213.203.204.172/downloads/db4o-6.0-java.zip
fi





#################################################
# unpack the db4o file
#
rm -rf tmp
mkdir -p tmp
cd tmp
unzip ../db4o-6.0-java.zip
cd ..


#################################################
# rebuilds the environment
#
cp -R tmp/db4o-6.0/src/bloat/src/* 						      bloat/src/main/java/
cp -R tmp/db4o-6.0/src/db4ojdk1.2/* 	            	   db4ojdk1.2/src/main/java
cp -R tmp/db4o-6.0/src/db4ojdk5/*			               db4ojdk5/src/main/java
cp -R tmp/db4o-6.0/src/db4oj/*	      	               db4oj/src/main/java
cp -R tmp/db4o-6.0/src/db4oj.tests/src/*        	      db4oj.tests/src/main/java
cp -R tmp/db4o-6.0/src/db4onqopt/*	   	               db4onqopt/src/main/java
cp -R tmp/db4o-6.0/src/db4ounit.extensions/src/*  	      db4ounit.extensions/src/main/java
cp -R tmp/db4o-6.0/src/db4ounit/src/*					      db4ounit/src/main/java



#################################################
# clean tmp
#
#rm -rf tmp

#################################################
# build the environment
mvn compile




