qmake -spec macx-xcode
exit 0
cd ./actions 		
qmake -spec macx-xcode
cd ..

cd ./applications
qmake -spec macx-xcode
cd ..

cd ./framework
qmake -spec macx-xcode
cd ..

cd ./gui
qmake -spec macx-xcode
cd ..

cd ./linktest/testactions
qmake -spec macx-xcode
cd ../..

cd ./linktest/testframework
qmake -spec macx-xcode
cd ../..

cd ./linktest/testgui
qmake -spec macx-xcode
cd ../..

cd ./linktest/testplugins
qmake -spec macx-xcode
cd ../..

cd ./linktest
qmake -spec macx-xcode
cd ..


cd ./plugins/designer
qmake -spec macx-xcode

cd ../..

cd ./plugins
qmake -spec macx-xcode
cd ..

