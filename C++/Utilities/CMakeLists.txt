add_library(Utilities STATIC utils.cpp)
target_link_libraries(Utilities PUBLIC cxx_setup)
target_include_directories(Utilities PUBLIC ${PROJECT_SOURCE_DIR}/C++)