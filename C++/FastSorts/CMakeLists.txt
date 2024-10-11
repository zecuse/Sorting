project(FastSorts)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Comparors/)
	add_subdirectory (Comparors)
endif()
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Distributors/)
	add_subdirectory (Distributors)
endif()
