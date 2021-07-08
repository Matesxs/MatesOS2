#include "cpuInfo.hpp"

namespace CPU
{
  CPUInfo g_CPUInfo;

  CPUInfo GetCPUInfo()
  {
    g_CPUInfo.VendorID = cpuid_get_vendor();
    cpuid_get_vendor_str(g_CPUInfo.VendorString);
    cpuid_get_brand_str(g_CPUInfo.BrandString);
    cpuid_get_features(&g_CPUInfo.features);

    return g_CPUInfo;
  }
}