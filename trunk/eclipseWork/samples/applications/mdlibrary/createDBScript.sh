#! /bin/sh
mvn -o -f core/pom.xml andromdapp:schema -Dtasks=create -DexecuteScripts=false
