QT += quick virtualkeyboard multimedia qml core

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        audiochart.cpp \
        audioconfig.cpp \
        audiocontroller.cpp \
        audiodevice.cpp \
        audioio.cpp \
        audioprocessing.cpp \
        main.cpp

RESOURCES += \
    $$files(qml/*)

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = qml/imports

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qml/content/ConfigAudio.qml \
    qml/content/Processing.qml \
    qml/content/component/BottomMenu.qml \
    qml/content/component/ButtonWithEffect.qml \
    qml/content/component/StatusLight.qml \
    qml/content/component/TopBar.qml \
    qml/content/fonts/Oxanium-Regular.ttf \
    qml/content/fonts/Oxanium-VariableFont_wght.ttf \
    qml/content/images/rcd.png \
    qml/content/images/rcdFocus.png \
    qml/content/images/record.svg \
    qml/content/images/recordFocus.svg

HEADERS += \
    IAudioRecorder.h \
    audiochart.h \
    audioconfig.h \
    audiocontroller.h \
    audiodevice.h \
    audioio.h \
    audioprocessing.h \
    interfaces/IAudioRecorder.h
