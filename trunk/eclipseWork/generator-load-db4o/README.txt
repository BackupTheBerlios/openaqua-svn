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
