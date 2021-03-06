find_package(Gperftools QUIET)
if(GPERFTOOLS_FOUND)
    message(STATUS "Found gperftools; compiling tests with TCMalloc")
    list(APPEND PLATFORM_SPECIFIC_LIBS tcmalloc)
endif()

file(GLOB_RECURSE COMMON_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

add_subdirectory(hippomocks)

add_executable(chain_test ${SOURCES} ${COMMON_SOURCES})
target_link_libraries(chain_test
                      HippoMocks
                      chainbase
                      scorum_chain
                      scorum_protocol
                      scorum_app
                      scorum_account_history
                      scorum_witness
                      scorum_egenesis_none
                      scorum_debug_node
                      fc
                      ${PLATFORM_SPECIFIC_LIBS})
target_include_directories(chain_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/common")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/plugin_tests/*.cpp")

add_executable(plugin_test ${SOURCES} ${COMMON_SOURCES})
target_link_libraries(plugin_test
                      scorum_chain
                      scorum_protocol
                      scorum_app
                      scorum_account_history
                      scorum_witness
                      scorum_egenesis_none
                      scorum_debug_node
                      fc
                      ${PLATFORM_SPECIFIC_LIBS})
target_include_directories(plugin_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/common")

file(GLOB_RECURSE WALLET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/wallet/*.cpp")
add_executable(wallet_tests ${WALLET_SOURCES})
target_link_libraries(wallet_tests
                      scorum_wallet
                      scorum_chain
                      scorum_app
                      scorum_private_message
                      scorum_egenesis_none
                      graphene_utilities
                      fc
                      ${PLATFORM_SPECIFIC_LIBS})

if(MSVC)
    set_source_files_properties(tests/serialization_tests.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

#add_subdirectory( generate_empty_blocks )
