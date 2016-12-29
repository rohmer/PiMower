#ifndef HL_LOGEVENT_H
#define HL_LOGEVENT_H

#include <string>
#include <ctime>

#include "defines.h"

HL_NAMESPACE_BEGIN

class HUMBLE_EXPORT_API LogEvent
{
public:
  LogEvent(int level, const std::string &message, int line, const std::string &file, const std::string &func);
  ~LogEvent();

  int getLogLevel() const { return _level; }
  const std::string& getMessage() const { return _message; }
  int getLine() const { return _line; }
  const std::string& getFile() const { return _file; }
  const std::string& getFunction() const { return _function; }
  const time_t& getTime() const { return _time; }
  unsigned int getPid() const { return _pid; }
  unsigned int getTid() const { return _tid; }

private:
  int _level;
  std::string _message;
  int _line;
  std::string _file;
  std::string _function;
  time_t _time;
  unsigned int _pid;
  unsigned int _tid;
};

HL_NAMESPACE_END
#endif
