set(SOURCES "comparors.cpp")

add_library(Comparors STATIC ${SOURCES})
target_link_libraries(Comparors PUBLIC cxx_setup Utilities)
target_include_directories(Comparors PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(ComparorSorts main.cpp)
target_link_libraries(ComparorSorts PRIVATE Comparors)
target_include_directories(ComparorSorts PUBLIC ${PROJECT_SOURCE_DIR})
 
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET Comparors PROPERTY CXX_STANDARD 20)
endif()