# Include core-modules

add_library(md5-engine "")
set_target_properties(md5-engine PROPERTIES PREFIX "")


target_sources(
        md5-engine
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/md5-engine.c
        ${CMAKE_CURRENT_LIST_DIR}/rfc1321/md5c.c
)

target_include_directories(
        md5-engine
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_compile_options(
        md5-engine
        PUBLIC

)

target_link_libraries(
        md5-engine
        PUBLIC
        OpenSSL::SSL
        OpenSSL::Crypto
)
