
# add directories to be searched by the compiler
# for headers
include_directories( 
${CMAKE_SOURCE_DIR}/include
)

add_executable(AutoTest AutoTest.cpp)
add_executable(MapTest MapTest.cpp)
add_executable(MoveTest MoveTest.cpp)
add_executable(LambdaTest LambdaTest.cpp)
add_executable(TupleTest TupleTest.cpp)
add_executable(ConstExprTest ConstExprTest.cpp)
add_executable(AtomicTest AtomicTest.cpp)
add_executable(SmartPtrTest SmartPtrTest.cpp)

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX
    "${CMAKE_SOURCE_DIR}" CACHE PATH "install prefix" FORCE
    )
ENDIF()

install(TARGETS AutoTest MapTest MoveTest LambdaTest TupleTest SmartPtrTest ConstExprTest AtomicTest
  RUNTIME DESTINATION bin
)