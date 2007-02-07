#!/bin/bash
. ~/.bashrc
cd /Volumes/user/tukaram/workspace/openaqua/eclipseWork/deploy-db4o61
UpdateSetup.sh
mvn -DperformRelease=true deploy
