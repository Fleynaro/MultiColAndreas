cmake_minimum_required (VERSION 2.8.11)
cmake_policy(SET CMP0020 NEW)

set (CMAKE_PREFIX_PATH "C:\\Qt\\Static\\qt5-x86-static-release")

find_package(Qt5 COMPONENTS Core Gui Widgets)

if(NOT WIN32)
	set(CMAKE_C_FLAGS "")
	set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-write-strings")
endif(NOT WIN32)

set(CA_VERSION "v1.4.0")
set(CA_DATABASE_VERSION 2)
add_definitions(-DCA_VERSION="${CA_VERSION}" -DCA_DATABASE_VERSION=${CA_DATABASE_VERSION})
include_directories(${CMAKE_BINARY_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_BINARY_DIR}/WizardApp" ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

link_directories("${_qt5_install_prefix}\\.." "${_qt5_install_prefix}\\..\\..\\plugins\\platforms")
	
file(GLOB Wizard_SRC
	"src/*.c"
	"src/*.cpp"
)

file(GLOB Wizard_MOC
	"src/Qt*.cpp"
)

file(GLOB Wizard_UI
	"ui/*.ui"
)

if(WIN32)
	list(APPEND Wizard_SRC "Windows.rc")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

qt5_wrap_cpp(Qt_MOC ${Wizard_MOC})
qt5_wrap_ui(Qt_UI ${Wizard_UI})
qt5_add_resources(Qt_RES "Resources.qrc")
add_executable(WizardApp ${Wizard_SRC} ${Qt_MOC} ${Qt_UI} ${Qt_RES})

if(NOT WIN32)
	target_link_libraries(WizardApp -pthread Qt5::Core Qt5::Gui Qt5::Widgets)
else()
	target_link_libraries(WizardApp Qt5Core.lib Qt5Gui.lib Qt5Widgets.lib qtmain.lib qtharfbuzzng.lib Qt5OpenGL.lib qtpcre.lib qtfreetype.lib Qt5PlatformSupport.lib qwindows.lib kernel32.lib user32.lib uuid.lib shell32.lib ole32.lib comdlg32.lib gdi32.lib Winmm.lib Imm32.lib ws2_32.lib qtpng.lib oleaut32.lib glu32.lib opengl32.lib advapi32.lib)
	set_target_properties(WizardApp PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()