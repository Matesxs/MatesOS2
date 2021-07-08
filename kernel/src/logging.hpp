//
// Created by Martin on 08.07.2021.
//

#ifndef MATESOS2_LOGGING_HPP
#define MATESOS2_LOGGING_HPP

#include "stdarg.h"

namespace logging
{
  enum LoggingLevel
  {
    INFO,
    INFOPlus,
    SUCCESS,
    WARNING,
    ERROR
  };

  void log(LoggingLevel lvl, const char *format, ...);
}

#endif //MATESOS2_LOGGING_HPP
