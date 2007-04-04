mvn clean
mvn compile
mvn -f core/pom.xml andromdapp:schema -Dtasks=drop
mvn -f core/pom.xml andromdapp:schema -Dtasks=create
