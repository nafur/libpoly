set(polyxx_tests
    test_algebraic_number
    test_assignment
    test_context
    test_dyadic_interval
    test_integer
    test_upolynomial
    test_variable
)

foreach(file ${polyxx_tests})
    add_executable(${file} ${file}.cpp)
    target_include_directories(${file} PUBLIC ${CMAKE_SOURCE_DIR}/include)
    add_test(NAME ${file} COMMAND ${file})
    target_link_libraries(${file} polyxx poly)
endforeach()
