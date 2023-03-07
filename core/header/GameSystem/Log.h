#pragma once

#include <Project_Config.h>
#include <iostream>
#include <windows.h>
// log lib
#ifdef ENABLE_ALL_LOG
#define LOG_Log(...) Log::Log(__VA_ARGS__)
#define LOG_Error(...) Log::Error(__VA_ARGS__)
#define LOG_Warning(...) Log::Warning(__VA_ARGS__)
#endif
#ifdef LOG_ERROR_ONLY
#define LOG_Error(...) Log::Error(__VA_ARGS__)
#define LOG_Log(...)
#define LOG_Warning(...)
#endif

void SetConsoleColor(int color) {
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

namespace Log {
void Log(std::string from, std::string type, std::string info) {
  SetConsoleColor(2);
  std::cout << "Log";
  SetConsoleColor(7);
  std::cout << "::";
  SetConsoleColor(5);
  std::cout << from;
  SetConsoleColor(7);
  std::cout << "::";
  SetConsoleColor(2);
  std::cout << type;
  SetConsoleColor(7);
  if (!info.empty()) {
    std::cout << ":  " << info;
  }
  std::cout << std::endl;
}

void Error(std::string from, std::string type, std::string info) {
  SetConsoleColor(4);
  std::cout << "Error";
  SetConsoleColor(7);
  std::cout << "::";
  SetConsoleColor(5);
  std::cout << from;
  SetConsoleColor(7);
  std::cout << "::";
  SetConsoleColor(4);
  std::cout << type;
  SetConsoleColor(7);
  { std::cout << ":  " << info; }
  std::cout << std::endl;
}

void Warning(std::string from, std::string type, std::string info) {
  SetConsoleColor(6);
  std::cout << "Warning";
  SetConsoleColor(7);
  std::cout << "::";
  SetConsoleColor(5);
  std::cout << from;
  SetConsoleColor(7);
  std::cout << "::";
  SetConsoleColor(6);
  std::cout << type;
  SetConsoleColor(7);
  if (!info.empty()) {
    std::cout << ":  " << info;
  }
  std::cout << std::endl;
}
} // namespace Log
