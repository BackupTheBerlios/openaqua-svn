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
rm -rf ./db4ojdk1.2/src
rm -rf ./db4ounit.extensions/src
rm -rf ./db4ojdk5/src
rm -rf ./db4onqopt/src
rm -rf ./bloat/src


#################################################
# remove potential existing original directories
#
find . -name \*~ -exec rm {} \;

#rm -f db4o-6.0-java.zip

