set(SOURCES "steppers.cpp")

add_library(Steppers STATIC ${SOURCES})
target_link_libraries(Steppers PUBLIC cxx_setup Utilities)
target_include_directories(Steppers PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(StepperSorts main.cpp)
target_link_libraries(StepperSorts PRIVATE Steppers)
target_include_directories(StepperSorts PUBLIC ${PROJECT_SOURCE_DIR})
 
if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET Steppers PROPERTY CXX_STANDARD 20)
endif()