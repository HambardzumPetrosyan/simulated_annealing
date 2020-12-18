## Test name
set(test simulated_annealing_travelling_salesman)

## Sources
set(src
	TravellingSalesman.cpp
)

## Create test
add_executable(${test} ${src})

## Run test
add_test(
	NAME ${test}
	COMMAND bash -c "
    ${CMAKE_CURRENT_BINARY_DIR}/${test} ${CMAKE_CURRENT_SOURCE_DIR}/TSP_15.in > TSP_15.out
    diff TSP_15.out ${CMAKE_CURRENT_SOURCE_DIR}/TSP_15.gout
	"
)
