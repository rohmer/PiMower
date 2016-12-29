#include "humblelogging/api.h"

#include <Windows.h>

#include "humblelogging/util/mutex.h"

HUMBLE_LOGGER(logger, "default");

using namespace humble::logging;

Mutex mtx;

DWORD WINAPI threadWork1(LPVOID lpThreadParameter)
{
  MutexLockGuard lock(mtx);
  for (int i = 0; i < 100; ++i) {
    HL_DEBUG(logger, "*");
  }
  return 0;
}

DWORD WINAPI threadWork2(LPVOID lpThreadParameter)
{
  MutexLockGuard lock(mtx);
  for (int i = 0; i < 100; ++i) {
    HL_DEBUG(logger, "?");
  }
  return 0;
}

int main(int argc, char **argv)
{
  HL_DEBUG(logger, "Initialize logging (this text should NOT be logged).");

  Factory &fac = Factory::getInstance();
  fac.registerAppender(new ConsoleAppender());
  fac.registerAppender(new FileAppender("humble.log"));

  HL_DEBUG(logger, "Begin of example.");
  HANDLE hThread1 = CreateThread(NULL, 0, threadWork1, NULL, 0, NULL);
  HANDLE hThread2 = CreateThread(NULL, 0, threadWork2, NULL, 0, NULL);
  WaitForSingleObject(hThread1, INFINITE);
  WaitForSingleObject(hThread2, INFINITE);
  HL_DEBUG(logger, "End of example.");
  return 0;
}
