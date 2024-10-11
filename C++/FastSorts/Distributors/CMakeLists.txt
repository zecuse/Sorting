set(SOURCES "distributors.cpp")

add_library(Distributors STATIC ${SOURCES})
target_link_libraries(Distributors PUBLIC cxx_setup Utilities)
target_include_directories(Distributors PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(DistributorSorts main.cpp)
target_link_libraries(DistributorSorts PRIVATE Distributors)
target_include_directories(DistributorSorts PUBLIC ${PROJECT_SOURCE_DIR})
 
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET Distributors PROPERTY CXX_STANDARD 20)
endif()