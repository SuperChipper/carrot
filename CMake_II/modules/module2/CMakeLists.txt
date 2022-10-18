aux_source_directory(src module2_src)
add_library(module2 SHARED ${module2_src})
target_include_directories(module2 PUBLIC include)
target_link_libraries(module2 pthread)