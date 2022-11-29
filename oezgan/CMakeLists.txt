
add_library(oezgan "")
set_target_properties(oezgan PROPERTIES PREFIX "")

set_target_properties(oezgan PROPERTIES LANGUAGE CXX)

target_sources(
        oezgan
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/oezganEngine.cpp
        ${CMAKE_CURRENT_LIST_DIR}/wrapper.cpp
)

target_include_directories(
        oezgan
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_compile_options(
        oezgan
        PUBLIC
)

target_link_libraries(
        oezgan
        PUBLIC
        OpenSSL::SSL
        OpenSSL::Crypto
)