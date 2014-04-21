cmake_minimum_required (VERSION 2.6)
project(anomaly)

# Find all the input files

file (GLOB CURRENT_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

# message("----------------------------------------")
# foreach(libs  ${LIBRARIES})
#   message(${libs})
# endforeach(libs)
# message("----------------------------------------")


set(EXEC_NAME "run-check")

add_executable( ${EXEC_NAME} ${CURRENT_FILES} )
target_link_libraries( ${EXEC_NAME}  ${LIBRARIES}  )



