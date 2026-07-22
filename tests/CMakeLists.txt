include(CTest)

# Helper: each test is a self-checking executable linked against sw::mp_ode.
function(mpode_add_test test_name)
	add_executable(${test_name} ${test_name}.cpp)
	target_link_libraries(${test_name} PRIVATE sw::mp_ode)
	add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# Smoke test: forward Euler integrates through the MTL5 + Universal composition.
mpode_add_test(test_euler_smoke)
