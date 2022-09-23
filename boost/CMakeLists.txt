
find_package(Boost)

if (Boost_FOUND)
    add_executable(boost_asio asio.cpp)
    target_include_directories(boost_asio PRIVATE ${Boost_INCLUDE_DIR})
endif ()
