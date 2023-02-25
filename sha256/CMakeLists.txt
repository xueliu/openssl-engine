# Include core-modules

add_library(sha256-engine "")
set_target_properties(sha256-engine PROPERTIES PREFIX "")


target_sources(
        sha256-engine
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/sha256-engine.c
)

target_include_directories(
        sha256-engine
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_compile_options(
        sha256-engine
        PUBLIC

)

target_link_libraries(
        sha256-engine
        PUBLIC
        OpenSSL::SSL
        OpenSSL::Crypto
)

