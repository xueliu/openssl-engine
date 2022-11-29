# Include core-modules

add_library(dummy "")
set_target_properties(dummy PROPERTIES PREFIX "")


target_sources(
        dummy
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/engine_init.cpp
)

target_include_directories(
        dummy
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_compile_options(
        dummy
        PUBLIC

)

target_link_libraries(
        dummy
        PUBLIC
        OpenSSL::SSL
        OpenSSL::Crypto
)
