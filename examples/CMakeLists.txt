add_executable(sha1_example sha1_example.cpp)

target_link_libraries(sha1_example
        PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
)

add_executable(find_md5_engine find-md5-engine.c)

target_link_libraries(find_md5_engine
        PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
)
