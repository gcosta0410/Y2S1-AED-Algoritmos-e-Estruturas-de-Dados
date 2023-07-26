cmake_minimum_required(VERSION 3.20)
project(AED2122)

set(CMAKE_CXX_STANDARD 14)


include_directories(Classes)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


set(BUILD_1 main)
set(SOURCE_FILES_1
        Classes/bst.h
        Classes/Airline.cpp
        Classes/Airline.h
        Classes/AuxiliaryFunctions.cpp
        Classes/AuxiliaryFunctions.h
        Classes/Date.cpp
        Classes/Date.h
        Classes/Flight.cpp
        Classes/Flight.h
        Classes/Luggage.cpp
        Classes/Luggage.h
        Classes/menu.cpp
        Classes/menu.h
        Classes/Passenger.cpp
        Classes/Passenger.h
        Classes/Person.cpp
        Classes/Person.h
        Classes/Plane.cpp
        Classes/Plane.h
        Classes/Service.cpp
        Classes/Service.h
        Classes/Ticket.cpp
        Classes/Ticket.h
        Classes/TransportCar.cpp
        Classes/TransportCar.h
        main.cpp
        Classes/Airport.cpp
        Classes/Airport.h
        Classes/Seat.cpp
        Classes/Seat.h Classes/MeanOfTransport.cpp Classes/MeanOfTransport.h Classes/Time_m.cpp Classes/Time_m.h Classes/Worker.cpp Classes/Worker.h)
add_executable(${BUILD_1} ${SOURCE_FILES_1})