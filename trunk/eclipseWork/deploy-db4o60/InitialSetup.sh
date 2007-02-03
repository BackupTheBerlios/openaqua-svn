#################################################
# remove everything with maven
#
mvn clean



#################################################
# remove potential existing original directories
#
rm -rf ./bloat/src
rm -rf ./db4ojdk1.2/src
rm -rf ./db4ojdk1.2.tests/src
rm -rf ./db4ojdk5.plugins/src
rm -rf ./db4ojdk5/src
rm -rf ./db4ojdk5.tests/src
rm -rf ./db4oj/src
rm -rf ./db4oj.tests/src
rm -rf ./db4oj.tools/src
rm -rf ./db4onqopt/src
rm -rf ./db4onqopt.testsExe/src
rm -rf ./db4onqopt.tests/src
rm -rf ./db4ounit.extensions/src
rm -rf ./db4ounit/src
rm -rf tmp




#################################################
# recreate directories
#
mkdir -p ./bloat/src/main/java
mkdir -p ./db4ojdk1.2/src/main/java
mkdir -p ./db4ojdk5/src/main/java/com/db4o/
mkdir -p ./db4oj/src/main/java/com/db4o/
mkdir -p ./db4oj.tests/src/main/java/
mkdir -p ./db4oj.tools/src/main/java/
mkdir -p ./db4oj.tests/src/main/resources
mkdir -p ./db4onqopt/src/main/java/com/db4o/
mkdir -p ./db4ounit.extensions/src/main/java/com/db4o/
mkdir -p ./db4ounit/src/main/java/com/db4o/
mkdir -p ./db4ounit/src/main/resources



#################################################
#get the db4o file
#wget http://213.203.204.172/downloads/db4o-6.0-java.zip




#################################################
# unpack the db4o file
#
mkdir -p tmp
cd tmp
unzip ../db4o-6.0-java.zip
cd ..


#################################################
# rebuilds the environment
#
mv tmp/db4o-6.0/src/bloat/src/* 						      ./bloat/src/main/java/

mv tmp/db4o-6.0/src/db4ojdk1.2/core/src/com/db4o/*   	./db4ojdk1.2/src/main/java/com/db4o/
mv tmp/db4o-6.0/src/db4ojdk1.2/test/src/com/db4o/*    ./db4ojdk1.2/src/main/java/com/db4o


mv tmp/db4o-6.0/src/db4ojdk5/core/src/com/db4o/*      ./db4ojdk5/src/main/java/com/db4o/
mv tmp/db4o-6.0/src/db4ojdk5/test/src/com/db4o/*      ./db4ojdk5/src/main/java/com/db4o/
mv tmp/db4o-6.0/src/db4ojdk5/plugins/src/com/db4o/*   ./db4ojdk5/src/main/java/com/db4o/


mv tmp/db4o-6.0/src/db4oj/core/src/* 	               ./db4oj/src/main/java/
mv tmp/db4o-6.0/src/db4oj/tools/src/*         	      ./db4oj.tools/src/main/java

mv tmp/db4o-6.0/src/db4oj.tests/src/*        	      ./db4oj.tests/src/main/java


mv tmp/db4o-6.0/src/db4onqopt/core/src/*   	         ./db4onqopt/src/main/java
mv tmp/db4o-6.0/src/db4onqopt/test/src/com/db4o/*     ./db4onqopt/src/main/java

mv tmp/db4o-6.0/src/db4ounit.extensions/src/*  	      ./db4ounit.extensions/src/main/java
mv tmp/db4o-6.0/src/db4ounit/src/*					      ./db4ounit/src/main/java


#./db4ojdk1.2.tests/src/main/resources
#./db4ojdk5.tests/src/main/resources
#./db4oj.tests/src/main/resources
#./db4onqopt.testsExe/src/main/java
#./db4ounit/src/main/resources

#################################################
# clean tmp
#
rm -rf tmp
exit 0;

#################################################
# build the environment
# must be compiled two times!
mvn compile
#mvn compile




