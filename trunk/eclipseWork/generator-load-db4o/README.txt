JTA jar can’t be loaded by a Maven repository because of Sun’s Binary License.
Download it from there: http://java.sun.com/products/jta/
Install it with

mvn install:install-file \
  -Dfile=./jta-1_0_1B-classes.zip \
  -DgroupId=javax.transaction \
  -DartifactId=jta -Dversion=1.0.1B \
  -Dpackaging=jar


The same for the resources connector
Download from there http://java.sun.com/j2ee/connector/download.html (Version 1.0)
install it with

mvn install:install-file -DgroupId=javax.resource -DartifactId=connector \
           -Dversion=1.0 -Dpackaging=jar -Dfile=./j2ee_connector-1_0-fr-class.zip






####################################################
# Setup a maven environment for db4o
mvn install:install-file -DgroupId=com.db4o -DartifactId=bloat        -Dversion=1.0 -Dpackaging=jar -Dfile=./bloat-1.0.jar
mvn install:install-file -DgroupId=com.db4o -DartifactId=db4ounit     -Dversion=6.1 -Dpackaging=jar -Dfile=./db4o-6.1-db4ounit.jar
mvn install:install-file -DgroupId=com.db4o -DartifactId=db4o-java1-1 -Dversion=6.1 -Dpackaging=jar -Dfile=./db4o-6.1-java1.1.jar
mvn install:install-file -DgroupId=com.db4o -DartifactId=db4o-java1-2 -Dversion=6.1 -Dpackaging=jar -Dfile=./db4o-6.1-java1.2.jar
mvn install:install-file -DgroupId=com.db4o -DartifactId=db4o-java5   -Dversion=6.1 -Dpackaging=jar -Dfile=./db4o-6.1-java5.jar
mvn install:install-file -DgeneratePom=true -DpomFile=~/workspace/eclipseWork/generator-load-db4o/db4o.pom -DgroupId=com.db4o -DartifactId=db4o-nqopt   -Dversion=6.1 -Dpackaging=jar -Dfile=./db4o-6.1-nqopt.jar  -DcreateChecksum=true

http://maven.apache.org/plugins/maven-deploy-plugin/

#3rdpartylibs.txt  ant.license.txt  bloat.license.txt
#db4o-6.1-java1.1.jar
#db4o-6.1-java5.jar
#ant.jar
#bloat-1.0.jar
#db4o-6.1-db4ounit.jar
#db4o-6.1-java1.2.jar
#db4o-6.1-nqopt.jar

mvn -e deploy:deploy-file -DgeneratePom=true -DpomFile=./pom.xml -Dfile=../db4o-java11/db4o-6.0-java1.1.jar  -DcreateChecksum=true -Durl=file:///users/dxccwl/user7/behrenan/workspace/tmp/deploy


mvn deploy:deploy-file -Durl=file:///users/dxccwl/user7/behrenan/workspace/tmp/deploy \
                       -DrepositoryId=some.id \
                       -Dfile=../db4o-java11/db4o-6.0-java1.1.jar  \
                       -DpomFile=./pom.xml \
                       -DgroupId=com.db4o \
							  -DartifactId=your-artifact \
                       -Dversion=6.0 \
                       -Dpackaging=jar \
                       -DgeneratePom=true \
                       -DgeneratePom.description="DB4O Package" \
                       -DrepositoryLayout=default


mvn -e deploy:deploy-file -DartifactId=db4o-java11 -DgroupId=com.db4o -DgeneratePom=true -DpomFile=./pom.xml -Dfile=../db4o-java11/db4o-6.0-java1.1.jar  -DcreateChecksum=true -Durl=file:///users/dxccwl/user7/behrenan/workspace/tmp/deploy