
mvn eclipse:clean -DdownloadSources=true
mvn eclipse:eclipse -DdownloadSources=true

mvn clean
mvn compile
mvn test

mvn compile
mvn test
mvn package
mvn install
mvn clean