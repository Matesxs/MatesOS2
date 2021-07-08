#include "features.hpp"
#include "cpuInfo.hpp"

namespace CPU
{
  namespace feature
  {
    bool CPUFeature1(CPUIDFeatureSet1 feature)
    {
      CPUInfo info = GetCPUInfo();
      if (!info.features.set1)
        return false;
      
      uint32_t val = info.features.set1 & feature;
      return val > 0;
    }

    bool CPUFeature2(CPUIDFeatureSet2 feature)
    {
      CPUInfo info = GetCPUInfo();
      if (!info.features.set2)
        return false;
      return (bool)(info.features.set2 & feature);
    }

    bool CPUFeature3(CPUIDFeatureSet3 feature)
    {
      CPUInfo info = GetCPUInfo();
      if (!info.features.set3)
        return false;
      return (bool)(info.features.set3 & feature);
    }

    bool CPUFeature4(CPUIDFeatureSet4 feature)
    {
      CPUInfo info = GetCPUInfo();
      if (!info.features.set4)
        return false;
      return (bool)(info.features.set4 & feature);
    }

    bool CPUFeature5(CPUIDFeatureSet5 feature)
    {
      CPUInfo info = GetCPUInfo();
      if (!info.features.set5)
        return false;
      return (bool)(info.features.set5 & feature);
    }

    bool CPUFeature6(CPUIDFeatureSet6 feature)
    {
      CPUInfo info = GetCPUInfo();
      if (!info.features.set6)
        return false;
      return (bool)(info.features.set6 & feature);
    }

    bool CPUFeatureAMD1(CPUIDFeatureSetAMD1 feature)
    {
      CPUInfo info = GetCPUInfo();
      if (!info.features.amd1)
        return false;
      return (bool)(info.features.amd1 & feature);
    }

    bool CPUFeatureAMD2(CPUIDFeatureSetAMD2 feature)
    {
      CPUInfo info = GetCPUInfo();
      if (!info.features.amd2)
        return false;
      return (bool)(info.features.amd2 & feature);
    }

    // Set1
    bool FPU() { return CPUFeature1(CPUID_FPU); }
    bool APIC() { return CPUFeature1(CPUID_APIC); }
    bool SSE() { return CPUFeature1(CPUID_SSE); }

    // Set2
    bool X2APIC() { return CPUFeature2(CPUID_X2APIC); }
  }
}