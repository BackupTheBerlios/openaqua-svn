#!/bin/bash
#################################################
# remove everything with maven
#
#mvn eclipse:clean
#mvn clean



svn update					bloat/src/main/java
svn update					db4ojdk1.2/src/main/java
svn update					db4ojdk5/src/main/java
svn update					db4oj/src/main/java
svn update					db4oj.tests/src/main/java
svn update					db4onqopt/src/main/java
svn update					db4ounit/src/main/java
svn update					db4ounit.extensions/src/main/java




#################################################
# build the environment
mvn compile eclipse:eclipse -DdownloadSources=true




