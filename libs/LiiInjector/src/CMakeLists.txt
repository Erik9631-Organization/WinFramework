set(injector
        Injector.hpp
        Injectable.h)
source_group("" FILES ${all_files})

set(all_files
        ${injector}
)

add_library(${PROJECT_NAME} INTERFACE ${all_files})
target_include_directories(${PROJECT_NAME} INTERFACE .
)