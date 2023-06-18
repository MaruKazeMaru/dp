add_library(city STATIC city.c)
target_include_directories(city
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

add_library(txtlist STATIC txtlist.c)
target_include_directories(txtlist
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

add_library(dp_matching STATIC dp_matching.c)
target_link_libraries(dp_matching m)
target_include_directories(dp_matching
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

#target_link_libraries(${PROJECT_NAME} m)

add_executable(main.out main.c)

target_link_libraries(main.out m)
target_link_libraries(main.out city)
target_link_libraries(main.out txtlist)
target_link_libraries(main.out dp_matching)
