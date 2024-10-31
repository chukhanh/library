cmake_minimum_required(VERSION 3.28)
project(LibraryApplication)

set(CMAKE_CXX_STANDARD 11)

add_executable(LibraryApplication main.cpp
        Common/Common.h
        Common/Common.cpp
        Reader/Reader.h
        Reader/Reader.cpp
        Menu/Menu.cpp
        Menu/Menu.h
        Book/Book.cpp
        Book/Book.h
        Reader/Reader.cpp
        Utils/Date.cpp
        Utils/Date.h
        Transaction/Transaction.cpp
        Transaction/Transaction.h)
