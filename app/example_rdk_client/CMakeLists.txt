# ===================================================================
# PROJECT SETUP
# ===================================================================
project(example_rdk_client VERSION 0.1.0)

# ===================================================================
# PROJECT DEPENDENCIES
# ===================================================================
# find_package(Threads REQUIRED)

# ===================================================================
# MIDDLEWARE2 IDL GENERATION
# ===================================================================
# Generate middleware2 message source codes from idl files
flexiv_middleware2_fastrtpsgen(${CMAKE_CURRENT_SOURCE_DIR}/../../idl
    gui_msgs/msg
    ${CMAKE_CURRENT_BINARY_DIR}/generated
    GENERATED_IDL_GUI_HEADER
    GENERATED_IDL_GUI_SOURCE
    GENERATED_IDL_GUI_INCLUDE_DIRECTORIES)

flexiv_middleware2_fastrtpsgen(${CMAKE_CURRENT_SOURCE_DIR}/../../idl
    plan_msgs/msg
    ${CMAKE_CURRENT_BINARY_DIR}/generated
    GENERATED_IDL_PLAN_HEADER
    GENERATED_IDL_PLAN_SOURCE
    GENERATED_IDL_PLAN_INCLUDE_DIRECTORIES)

# ===================================================================
# PROJECT EXECUTABLES
# ===================================================================
# add executables
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src MAIN_SOURCE)
add_executable(${PROJECT_NAME} ${MAIN_SOURCE} ${GENERATED_IDL_GUI_SOURCE} ${GENERATED_IDL_PLAN_SOURCE})

# add path to idl header files and flexiv rdk header files
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${GENERATED_IDL_GUI_INCLUDE_DIRECTORIES}
    ${GENERATED_IDL_PLAN_INCLUDE_DIRECTORIES}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/flexiv_rdk/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# find and link dependencies
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
    flexiv::flexiv_app_guis
    ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/flexiv_rdk/lib/libFlexivRdk.x86_64-linux-gnu.a
)
