cmake_minimum_required(VERSION 3.24)
project(untitled4)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled4 main.cpp FileOperator.cpp FileOperator.h UserCommunicator.cpp UserCommunicator.h PasswordManager.cpp PasswordManager.h EncoderDecoder.cpp EncoderDecoder.h PasswordLine.cpp PasswordLine.h)
