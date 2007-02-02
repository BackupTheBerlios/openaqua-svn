#################################################
# remove everything with maven
#
mvn clean



#################################################
# remove potential existing original directories
#
rm -rf ./db4oj/src
rm -rf ./db4oj.tests/src
rm -rf ./db4oj.tests/src
rm -rf ./db4ounit/src
rm -rf ./db4ounit/src
rm -rf ./db4ojdk1.2/src
rm -rf ./db4ounit.extensions/src
rm -rf ./db4ojdk5/src
rm -rf ./db4oj.tools/src
rm -rf ./db4ojdk5.plugins/src
rm -rf ./db4onqopt/src
rm -rf ./bloat/src
rm -rf ./db4onqopt.tests/src
rm -rf ./db4onqopt.testsExe/src
rm -rf ./db4ojdk1.2.tests/src
rm -rf ./db4ojdk1.2.tests/src
rm -rf ./db4ojdk5.tests/src
rm -rf ./db4ojdk5.tests/src



#################################################
# recreate directories
#
mkdir -p ./db4oj/src/main/java
mkdir -p ./db4oj.tests/src/main/java
mkdir -p ./db4oj.tests/src/main/resources
mkdir -p ./db4ounit/src/main/java
mkdir -p ./db4ounit/src/main/resources
mkdir -p ./db4ojdk1.2/src/main/java
mkdir -p ./db4ounit.extensions/src/main/java
mkdir -p ./db4ojdk5/src/main/java
mkdir -p ./db4oj.tools/src/main/java
mkdir -p ./db4ojdk5.plugins/src/main/java
mkdir -p ./db4onqopt/src/main/java
mkdir -p ./bloat/src/main/java
mkdir -p ./db4onqopt.tests/src/main/java
mkdir -p ./db4onqopt.testsExe/src/main/java
mkdir -p ./db4ojdk1.2.tests/src/main/java
mkdir -p ./db4ojdk1.2.tests/src/main/resources
mkdir -p ./db4ojdk5.tests/src/main/java
mkdir -p ./db4ojdk5.tests/src/main/resources


#################################################
# get a fresh copy from subversion
#
svn co https://db4objects.net/svn/db4o/trunk/db4oj/core/src ./db4oj/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4oj.tests/src ./db4oj.tests/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4oj.tests/test ./db4oj.tests/src/main/resources
svn co https://db4objects.net/svn/db4o/trunk/db4ounit/src ./db4ounit/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4ounit/META-INF ./db4ounit/src/main/resources
svn co https://db4objects.net/svn/db4o/trunk/db4ojdk1.2/core/src ./db4ojdk1.2/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4ounit.extensions/src ./db4ounit.extensions/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4ojdk5/core/src ./db4ojdk5/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4oj/tools/src ./db4oj.tools/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4ojdk5/plugins/src ./db4ojdk5.plugins/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4onqopt/core/src ./db4onqopt/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/bloat/src ./bloat/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4onqopt/core/testsrc ./db4onqopt.tests/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4onqopt/test/src ./db4onqopt.testsExe/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4ojdk1.2/test/src ./db4ojdk1.2.tests/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4ojdk1.2/test ./db4ojdk1.2.tests/src/main/resources
svn co https://db4objects.net/svn/db4o/trunk/db4ojdk5/test/src ./db4ojdk5.tests/src/main/java
svn co https://db4objects.net/svn/db4o/trunk/db4ojdk5/test ./db4ojdk5.tests/src/main/resources


#################################################
# execute mvn
#
mvn compile
mvn compile
