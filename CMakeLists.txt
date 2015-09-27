cmake_minimum_required (VERSION 3.0.2)
project(TicTacToe)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

set(TicTacToe_HEADERS
)

set(TicTacToe_SRCS
    main.cpp
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
cmake_policy(SET CMP0020 NEW)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	find_package(Qt5 COMPONENTS Quick Qml Widgets)

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.5/gcc_64)
	find_package(Qt5 COMPONENTS Quick Qml Widgets PATHS ${HOME}/Qt/)
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

#qt5_wrap_ui(UI_HEADERS *.ui)

qt5_add_resources(QRCS
	./qml.qrc 
)

add_definitions("-std=c++11")


if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	MESSAGE(STATUS "Build application for Windows")
	
	add_executable(TicTacToe WIN32 ${TicTacToe_HEADERS} ${TicTacToe_SRCS} ${UI_HEADERS} ${QRCS})
	
	target_link_libraries(TicTacToe Qt5::WinMain Qt5::Qml Qt5::Quick Qt5::Widgets)
	
	set(DLL_NAMES
	icudt54.dll
	icuin54.dll
	icuuc54.dll
	libwinpthread-1.dll
	libstdc++-6.dll
	libgcc_s_sjlj-1.dll
	libpcre16-0.dll
	libglib-2.0-0.dll
	zlib1.dll
    libprotobuf-8.dll
	libfreetype-6.dll
	libharfbuzz-0.dll
	libpng16-16.dll
    libtiff-5.dll
	libpcre-1.dll
	libintl-8.dll
	libbz2.dll
	libiconv-2.dll
	libeay32.dll
	ssleay32.dll
    libexpat-1.dll
    libjpeg-8.dll
    liblzma-5.dll
    libqjson.dll
    libsqlite3-0.dll
    libcurl-4.dll
    libidn-11.dll
    libgpg-error-0.dll
    libssh2-1.dll
    curl.exe
    libgnutls-30.dll
    libnettle-6-0.dll
    librtmp-1.dll
    libgcrypt-20.dll
    libgmp-10.dll
    libhogweed-4-0.dll
    Qt5Core.dll
    Qt5Qml.dll
    Qt5Widgets.dll
    Qt5Script.dll
	Qt5Network.dll
	Qt5Gui.dll
	Qt5Quick.dll
	Qt5Svg.dll
	Qt5OpenGL.dll
	Qt5Xml.dll
    Qt5Declarative.dll
    Qt5Sql.dll
    Qt5XmlPatterns.dll
	)

	foreach(DLL_NAME ${DLL_NAMES})
		find_path(${DLL_NAME}_PATH ${DLL_NAME} PATHS ${QT_BINARY_DIR} ${QT_LIBRARY_DIR} PATH_SUFFIXES bin lib)
		MESSAGE(STATUS "DLL_NAME = ${DLL_NAME} \t DLL_NAME_PATH = ${${DLL_NAME}_PATH} ")
		if(NOT "${${DLL_NAME}_PATH}" STREQUAL "${DLL_NAME}_PATH-NOTFOUND" )
			install(FILES ${${DLL_NAME}_PATH}/${DLL_NAME} DESTINATION ${CMAKE_BINARY_DIR} )
		else()
			MESSAGE(WARNING "Can't find ${DLL_NAME}")
		endif(NOT "${${DLL_NAME}_PATH}" STREQUAL "${DLL_NAME}_PATH-NOTFOUND" )
	endforeach(DLL_NAME)

	set(FOLDERS_NAMES
		platforms
		qmltooling
		plugins
		Qt
		QtQml
		QtQuick
		QtQuick.2
	)
	
	set (Qt_SDK "${_qt5Qml_install_prefix}")
	foreach(FOLDER_NAME ${FOLDERS_NAMES})
		find_path(${FOLDER_NAME}_PATH ${FOLDER_NAME} PATHS ${Qt_SDK}/qml ${Qt_SDK}/plugins/ ${Qt_SDK} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
		MESSAGE(STATUS "FOLDER_NAME = ${FOLDER_NAME} \t FOLDER_NAME_PATH = ${${FOLDER_NAME}_PATH} ")
		if(NOT "${${FOLDER_NAME}_PATH}" STREQUAL "${FOLDER_NAME}_PATH-NOTFOUND" )
			install(DIRECTORY ${${FOLDER_NAME}_PATH}/${FOLDER_NAME} DESTINATION ${CMAKE_BINARY_DIR} )
		else()
			MESSAGE(WARNING "Can't find ${FOLDER_NAME}")
		endif(NOT "${${FOLDER_NAME}_PATH}" STREQUAL "${FOLDER_NAME}_PATH-NOTFOUND" )
	endforeach(FOLDER_NAME)
else()
	MESSAGE(STATUS "Build application for Linux")
	add_executable(TicTacToe ${TicTacToe_HEADERS} ${TicTacToe_SRCS} ${UI_HEADERS} ${QRCS})
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

qt5_use_modules(TicTacToe Widgets Qml Quick)
