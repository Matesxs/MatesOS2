#pragma once

namespace CPU
{
  namespace feature
  {
    // Set1
    bool FPU();
    bool APIC();
    bool SSE();

    // Set2
    bool X2APIC();

    extern "C" void cpu_enable_features();
  }
}