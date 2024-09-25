project(SlowSorts)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Steppers/)
	add_subdirectory (Steppers)
endif()
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Pickers/)
	add_subdirectory (Pickers)
endif()
