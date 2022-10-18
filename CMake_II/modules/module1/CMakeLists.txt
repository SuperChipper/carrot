

aux_source_directory(src/module1a build_A)
aux_source_directory(src/module1b build_B)
add_library(module1 SHARED ${build_B} ${build_A})
#add_library(module1 INTERFACE)


target_include_directories(module1 PUBLIC include)
target_link_libraries(module1 assembly2)