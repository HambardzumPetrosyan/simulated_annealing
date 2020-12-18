## Sources
set(src
	SimpleTest.cpp
)

## Create test
add_executable(simulated_annealing_simple_test ${src})

## Run test
add_test(
	NAME simulated_annealing_simple_test
	COMMAND bash -c "
	${CMAKE_CURRENT_BINARY_DIR}/simulated_annealing_simple_test > output
	diff output ${CMAKE_CURRENT_SOURCE_DIR}/goutput
	"
)
