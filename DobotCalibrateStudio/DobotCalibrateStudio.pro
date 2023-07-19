TEMPLATE = subdirs

contains(QT_ARCH, i386) {
    TEMPFILE_BUILD_OUTPUT_DIR=build-DobotCalibrateStudio_x86
} else {
    TEMPFILE_BUILD_OUTPUT_DIR=build-DobotCalibrateStudio_x64
}
CONFIG(release, debug|release): MOC_OBJ_TEMPFILE = $$PWD/../$${TEMPFILE_BUILD_OUTPUT_DIR}/Release
else:CONFIG(debug, debug|release): MOC_OBJ_TEMPFILE = $$PWD/../$${TEMPFILE_BUILD_OUTPUT_DIR}/Debug

MOC_DIR = $${MOC_OBJ_TEMPFILE}
OBJECTS_DIR = $${MOC_OBJ_TEMPFILE}

SUBDIRS += \
    DobotInterfacePlugin \
    DobotCalibrate \
    DobotCalibrateConsole \
    HKIndustrialCameraPlugin \
    HKIndustrialIOControllerPlugin \
    HKSmartCameraPlugin


