#xcodebuild -project framework/openaquaframework.xcodeproj
xcodebuild -project framework/openaquaframework.xcodeproj -activeconfiguration -activetarget BUILDROOT=framework INSTALL_DIR=lib OBJROOT=build SYMROOT=build

#xcodebuild -project linktest/testframework/testframework.xcodeproj

#xcodebuild -project actions/openaquaactions.xcodeproj
#xcodebuild -project linktest/testactions/testactions.xcodeproj

#xcodebuild -project gui/openaquagui.xcodeproj
#xcodebuild -project linktest/testgui/testgui.xcodeproj

#xcodebuild -project applications/actioneditor/actioneditor.xcodeproj
