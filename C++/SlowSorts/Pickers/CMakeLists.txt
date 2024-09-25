set(SOURCES "pickers.cpp")

add_library(Pickers STATIC ${SOURCES})
target_link_libraries(Pickers PUBLIC cxx_setup Utilities)
target_include_directories(Pickers PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(PickerSorts main.cpp)
target_link_libraries(PickerSorts PRIVATE Pickers)
target_include_directories(PickerSorts PUBLIC ${PROJECT_SOURCE_DIR})
 
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET Pickers PROPERTY CXX_STANDARD 20)
endif()