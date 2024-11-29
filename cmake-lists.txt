# Top-level CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(SwarmIntelligenceNode C CXX)

# ESP-IDF Configuration
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Add components
set(EXTRA_COMPONENT_DIRS 
    ${CMAKE_SOURCE_DIR}/components/crypto
    ${CMAKE_SOURCE_DIR}/components/models
)

# Project specific configurations
set(COMPONENT_INCLUDES 
    ${CMAKE_SOURCE_DIR}/main
    ${CMAKE_SOURCE_DIR}/components
)

# Security and optimization flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} 
    -Wall -Wextra -Werror 
    -fstack-protector-strong 
    -fPIE -D_FORTIFY_SOURCE=2
")

# TensorFlow Lite and project libraries
list(APPEND REQUIRED_LIBRARIES
    tensorflow-lite
    mbedtls
    esp_now
    esp_wifi
)

# Main build configuration
idf_build_process(swarm_node
    COMPONENTS 
        main 
        crypto 
        models
)
