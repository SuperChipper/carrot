aux_source_directory(src AssSrc2)
add_library(assembly2 SHARED ${AssSrc2})
target_include_directories(assembly2 PUBLIC include)
target_link_libraries(assembly2 ${OpenCV_LIBS})