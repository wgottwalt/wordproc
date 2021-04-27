# sources
SET                   (CXX_SOURCES Main.cxx)
SET                   (INC_FILES )
SET                   (UI_FILES )
SET                   (RES_FILES )
SET                   (TS_FILES )

# wrapper and Qt automoc
QT5_ADD_TRANSLATION   (TS_SOURCES ${TS_FILES})
QT5_WRAP_CPP          (MOC_SOURCES ${INC_FILES})
QT5_WRAP_UI           (UI_SOURCES ${UI_FILES})
QT5_ADD_RESOURCES     (RES_SOURCES ${RES_FILES})

# binaries
ADD_EXECUTABLE        (${CMAKE_PROJECT_NAME} ${CXX_SOURCES} ${MOC_SOURCES} ${UI_SOURCES}
                       ${RES_SOURCES} ${TS_SOURCES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} Qt5::Core Qt5::Widgets)
