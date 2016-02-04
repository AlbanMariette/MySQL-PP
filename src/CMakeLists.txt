
file(GLOB_RECURSE sources_application Application/*.cpp Application/*.h)
file(GLOB_RECURSE sources_mysqlLib mysqlLib/*.cpp mysqlLib/*.h)
file(GLOB sources_localdir *.cpp *.h)


set(mysql_SRCS
  ${mysql_SRCS}
  ${sources_application}
  ${sources_mysqlLib}
  ${sources_localdir}
)

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Application
  ${CMAKE_CURRENT_SOURCE_DIR}/MysqlLib
  ${MYSQL_INCLUDE_DIR}
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(mysql
  ${mysql_SRCS}
  ${mysql_PCH_SRC}
)

if( NOT WIN32 )
  set_target_properties(mysql PROPERTIES
    COMPILE_DEFINITIONS _TRINITY_BNET_CONFIG="${CONF_DIR}/mysql.conf"
  )
endif()

target_link_libraries(mysql
  ${MYSQL_LIBRARY}
)
