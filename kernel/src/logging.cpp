//
// Created by Martin on 08.07.2021.
//

#include "logging.hpp"
#include "renderer/basic_renderer.hpp"

namespace logging
{
  void log(LoggingLevel lvl, const char *format, ...)
  {
    BasicRenderer::Color tmpColor = BasicRenderer::GetFrontColor();
    BasicRenderer::SetFrontColor(BasicRenderer::BR_WHITE);

    va_list args;
    va_start(args, format);

    switch (lvl)
    {
      case INFO:
      {
        BasicRenderer::Print("[ INF ] ");
        break;
      }

      case INFOPlus:
      {
        BasicRenderer::SetFrontColor(BasicRenderer::BR_DARK_CYAN);
        BasicRenderer::Print("   - ");
        break;
      }

      case SUCCESS:
      {
        BasicRenderer::Print("[ ");
        BasicRenderer::SetFrontColor(BasicRenderer::BR_GREEN);
        BasicRenderer::Print("SUC");
        BasicRenderer::SetFrontColor(BasicRenderer::BR_WHITE);
        BasicRenderer::Print(" ] ");
        break;
      }

      case WARNING:
      {
        BasicRenderer::Print("[ ");
        BasicRenderer::SetFrontColor(BasicRenderer::BR_YELLOW);
        BasicRenderer::Print("WRN");
        BasicRenderer::SetFrontColor(BasicRenderer::BR_WHITE);
        BasicRenderer::Print(" ] ");
        break;
      }

      case ERROR:
      {
        BasicRenderer::Print("[ ");
        BasicRenderer::SetFrontColor(BasicRenderer::BR_RED);
        BasicRenderer::Print("ERR");
        BasicRenderer::SetFrontColor(BasicRenderer::BR_WHITE);
        BasicRenderer::Print(" ] ");
        break;
      }
    }

    BasicRenderer::Printfa(format, args);
    BasicRenderer::NewLine();

    va_end(args);
    BasicRenderer::SetFrontColor(tmpColor);
  }
}