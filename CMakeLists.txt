cmake_minimum_required(VERSION 3.22.1)

project (Morel)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Morel src/Setup.cpp src/Helper.cpp src/Dialog.cpp src/UpdateExpenseList.cpp src/GenerateDataFile.cpp src/GenerateReport.cpp src/Calculator.cpp src/app.cpp)
    target_link_libraries(Morel ${Boost_LIBRARIES})
endif()

