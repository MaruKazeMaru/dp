add_library(wavio STATIC wavio.c)
target_include_directories(wavio
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)


add_library(dp STATIC dp.c)
target_include_directories(dp
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

add_library(city STATIC city.c)
target_include_directories(city
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

add_library(txtlist STATIC txtlist.c)
target_include_directories(txtlist
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

add_executable(main.out main.c)
target_link_libraries(main.out dp)
target_link_libraries(main.out city)
target_link_libraries(main.out txtlist)