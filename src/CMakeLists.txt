add_library(wavio STATIC wavio.c)
add_library(dp STATIC dp.c)

target_include_directories(wavio
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)
target_include_directories(dp
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

add_executable(main.out main.c)
target_link_libraries(main.out dp)