add_executable(utest-md5 utest-md5.cpp)
target_link_libraries(utest-md5 gtest gtest_main gmock)
target_compile_features(utest-md5 PRIVATE cxx_std_17)

# -- Enable testing

enable_testing()
add_test(utest-md5 utest-md5)