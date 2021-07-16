//
// Created by Martin on 15.07.2021.
//

#include "pci.hpp"
#include "stddef.h"

#define PCI_UNKNOWN_IDENTIFIER "?"

namespace PCI
{
  PCIClassIdentifier g_pci_classes[] = {
      {DC_Unclassified, "Unclassified"},
      {DC_MassStorageController, "Mass Storage Controller"},
      {DC_NetworkController, "Network Controller"},
      {DC_DisplayController, "Display Controller"},
      {DC_MultimediaController, "Multimedia Controller"},
      {DC_MemoryController, "Memory Controller"},
      {DC_BridgeDevice, "Bridge Device"},
      {DC_SimpleCommunicationController, "Simple Communication Controller"},
      {DC_BaseSystemPeripheral, "Base System Peripheral"},
      {DC_InputDeviceController, "Input Device Controller"},
      {DC_DockingStation, "Docking Station"},
      {DC_Processor, "Processor"},
      {DC_SerialBusController, "Serial Bus Controller"},
      {DC_WirelessController, "Wireless Controller"},
      {DC_InteligentController, "Intelligent Controller"},
      {DC_SateliteCommunicationController, "Satellite Communication Controller"},
      {DC_EncryptionController, "Encryption Controller"},
      {DC_SignalProcessingController, "Signal Processing Controller"},
      {DC_ProcessingAccelerator, "Processing Accelerator"},
      {DC_NonEssentialInstrumentation, "Non Essential Instrumentation"},
      {DC_CoProcessor, "Co-Processor"}
  };


  PCISublassIdentifier g_pci_subclasses[] = {
      {DC_Unclassified, UCSC_NonVGACompatibleDevice, "Non-VGA-Compatible devices"},
      {DC_Unclassified, UCSC_VGACompatibleDevice, "VGA-Compatible Device"},

      {DC_MassStorageController, MSCSC_SCSIBusController, "SCSI Bus Controller"},
      {DC_MassStorageController, MSCSC_IDEController, "IDE Controller"},
      {DC_MassStorageController, MSCSC_FloppyDiskController, "Floppy Disk Controller"},
      {DC_MassStorageController, MSCSC_IPIBusController, "IPI Bus Controller"},
      {DC_MassStorageController, MSCSC_RaidController, "RAID Controller"},
      {DC_MassStorageController, MSCSC_ATAController, "ATA Controller"},
      {DC_MassStorageController, MSCSC_SATA, "Serial ATA"},
      {DC_MassStorageController, MSCSC_SerialAttachedSCSI, "Serial Attached SCSI"},
      {DC_MassStorageController, MSCSC_NonVolatileMemoryController, "Non-Volatile Memory Controller"},
      {DC_MassStorageController, MSCSC_Other, "Other"},

      {DC_NetworkController, NCSC_EthernetController, "Ethernet Controller"},
      {DC_NetworkController, NCSC_TokenRingController, "Token Ring Controller"},
      {DC_NetworkController, NCSC_FDDIController, "FDDI Controller"},
      {DC_NetworkController, NCSC_ATMController, "ATM Controller"},
      {DC_NetworkController, NCSC_ISDNController, "ISDN Controller"},
      {DC_NetworkController, NCSC_WorldFlipController, "WorldFip Controller"},
      {DC_NetworkController, NCSC_PICMG_2_14_MultiComputing, "PICMG 2.14 Multi Computing"},
      {DC_NetworkController, NCSC_InfinibandController, "Infiniband Controller"},
      {DC_NetworkController, NCSC_FabricController, "Fabric Controller"},
      {DC_NetworkController, NCSC_Other, "Other"},

      {DC_DisplayController, DCSC_VGACompatibleController, "VGA Compatible Controller"},
      {DC_DisplayController, DCSC_XGAController, "XGA Controller"},
      {DC_DisplayController, DCSC_3DController, "3D Controller (Not VGA-Compatible)"},
      {DC_DisplayController, DCSC_Other, "Other"},

      {DC_MultimediaController, MMCSC_MultimediaVideoController, "Multimedia Video Controller"},
      {DC_MultimediaController, MMCSC_MultimediaAudioController, "Multimedia Audio Controller"},
      {DC_MultimediaController, MMCSC_ComputerTelephonyDevice, "Computer Telephony Device"},
      {DC_MultimediaController, MMCSC_AudioDevice, "Audio Device"},
      {DC_MultimediaController, MMCSC_Other, "Other"},

      {DC_MemoryController, MCSC_RAMController, "RAM Controller"},
      {DC_MemoryController, MCSC_FlashController, "Flash Controller"},
      {DC_MemoryController, MCSC_Other, "Other"},

      {DC_BridgeDevice, BDSC_HostBridge, "Host Bridge"},
      {DC_BridgeDevice, BDSC_ISABridge, "ISA Bridge"},
      {DC_BridgeDevice, BDSC_EISABridge, "EISA Bridge"},
      {DC_BridgeDevice, BDSC_MCABridge, "MCA Bridge"},
      {DC_BridgeDevice, BDSC_PCIToPCIBridge1, "PCI-to-PCI Bridge"},
      {DC_BridgeDevice, BDSC_PCMCIABridge, "PCMCIA Bridge"},
      {DC_BridgeDevice, BDSC_NuBusBridge, "NuBus Bridge"},
      {DC_BridgeDevice, BDSC_CardBusBridge, "CardBus Bridge"},
      {DC_BridgeDevice, BDSC_RACEwayBridge, "RACEway Bridge"},
      {DC_BridgeDevice, BDSC_PCIToPCIBridge2, "PCI-to-PCI Bridge"},
      {DC_BridgeDevice, BDSC_InfiniBandToPCIHostBridge, "InfiniBand-to-PCI Host Bridge"},
      {DC_BridgeDevice, BDSC_Other, "Other"},

      {DC_SimpleCommunicationController, SCCSC_SerialController, "Serial Controller"},
      {DC_SimpleCommunicationController, SCCSC_ParallelController, "Parallel Controller"},
      {DC_SimpleCommunicationController, SCCSC_MultiportSerialController, "Multiport Serial Controller"},
      {DC_SimpleCommunicationController, SCCSC_Modem, "Modem"},
      {DC_SimpleCommunicationController, SCCSC_GPIBController, "IEEE 488.1/2 (GPIB) Controller"},
      {DC_SimpleCommunicationController, SCCSC_SmartCard, "Smart Card"},
      {DC_SimpleCommunicationController, SCCSC_Other, "Other"},

      {DC_BaseSystemPeripheral, BSPSC_PIC, "PIC"},
      {DC_BaseSystemPeripheral, BSPSC_DMAController, "DMA Controller"},
      {DC_BaseSystemPeripheral, BSPSC_Timer, "Timer"},
      {DC_BaseSystemPeripheral, BSPSC_RTCController, "RTC Controller"},
      {DC_BaseSystemPeripheral, BSPSC_PCIHotPlugController, "PCI Hot-Plug Controller"},
      {DC_BaseSystemPeripheral, BSPSC_SDHostController, "SD Host controller"},
      {DC_BaseSystemPeripheral, BSPSC_IOMMU, "IOMMU"},
      {DC_BaseSystemPeripheral, BSPSC_Other, "Other"},

      {DC_InputDeviceController, IDCSC_KeyboardController, "Keyboard Controller"},
      {DC_InputDeviceController, IDCSC_DigitizerPen, "Digitizer Pen"},
      {DC_InputDeviceController, IDCSC_MouseController, "Mouse Controller"},
      {DC_InputDeviceController, IDCSC_ScannerController, "Scanner Controller"},
      {DC_InputDeviceController, IDCSC_GameportController, "Gameport Controller"},
      {DC_InputDeviceController, IDCSC_Other, "Other"},

      {DC_DockingStation, DSSC_Generic, "Generic"},
      {DC_DockingStation, DSSC_Other, "Other"},

      {DC_Processor, PSC_386, "386"},
      {DC_Processor, PSC_486, "486"},
      {DC_Processor, PSC_Pentium, "Pentium"},
      {DC_Processor, PSC_PentiumPro, "Pentium Pro"},
      {DC_Processor, PSC_Alpha, "Alpha"},
      {DC_Processor, PSC_PowerPC, "PowerPC"},
      {DC_Processor, PSC_MIPS, "MIPS"},
      {DC_Processor, PSC_CoProcessor, "Co-Processor"},
      {DC_Processor, PSC_Other, "Other"},

      {DC_SerialBusController, SBCSC_FireWireController, "FireWire (IEEE 1394) Controller"},
      {DC_SerialBusController, SBCSC_ACCESSBus, "ACCESS Bus"},
      {DC_SerialBusController, SBCSC_SSA, "SSA"},
      {DC_SerialBusController, SBCSC_USBController, "USB Controller"},
      {DC_SerialBusController, SBCSC_FibreChannel, "Fiber Channel"},
      {DC_SerialBusController, SBCSC_SMBus, "SMBus"},
      {DC_SerialBusController, SBCSC_InfiniBand, "InfiniBand"},
      {DC_SerialBusController, SBCSC_IPMIInterface, "IPMI Interface"},
      {DC_SerialBusController, SBCSC_SERCOSInterface, "SERCOS Interface (IEC 61491)"},
      {DC_SerialBusController, SBCSC_CANBus, "CANbus"},
      {DC_SerialBusController, SBCSC_Other, "Other"},

      {DC_WirelessController, WCSC_iRDACompatibleController, "iRDA Compatible Controller"},
      {DC_WirelessController, WCSC_ConsumerIRController, "Consumer IR Controller"},
      {DC_WirelessController, WCSC_RFController, "RF Controller"},
      {DC_WirelessController, WCSC_BluetoothController, "Bluetooth Controller"},
      {DC_WirelessController, WCSC_BroadbandController, "Broadband Controller"},
      {DC_WirelessController, WCSC_EthernetController802_1a, "Ethernet Controller (802.1a)"},
      {DC_WirelessController, WCSC_EthernetController802_1b, "Ethernet Controller (802.1b)"},
      {DC_WirelessController, WCSC_Other, "Other"},

      {DC_InteligentController, ICSC_I20, "I20"},

      {DC_SateliteCommunicationController, SCCSC_SatelliteTVController, "Satellite TV Controller"},
      {DC_SateliteCommunicationController, SCCSC_SatelliteAudioController, "Satellite Audio Controller"},
      {DC_SateliteCommunicationController, SCCSC_SatelliteVoiceController, "Satellite Voice Controller"},
      {DC_SateliteCommunicationController, SCCSC_SatelliteDataController, "Satellite Data Controller"},

      {DC_EncryptionController, ECSC_Network_Computing_Encrpytion_Decryption, "Network and Computing Encrpytion/Decryption"},
      {DC_EncryptionController, ECSC_EntertainmentEncryption_Decryption, "Entertainment Encryption/Decryption"},
      {DC_EncryptionController, ECSC_Other, "Other Encryption/Decryption"},

      {DC_SignalProcessingController, SPCSC_DPIOModules, "DPIO Modules"},
      {DC_SignalProcessingController, SPCSC_PerformanceCounters, "Performance Counters"},
      {DC_SignalProcessingController, SPCSC_CommunicationSynchronizer, "Communication Synchronizer"},
      {DC_SignalProcessingController, SPCSC_SignalProcessingManagement, "Signal Processing Management"},
      {DC_SignalProcessingController, SPCSC_Other, "Other"}
  };


  PCIProgrammingInterfaceIdentifier g_pci_progifs[] = {
      {DC_MassStorageController, MSCSC_IDEController, 0x00, "ISA Compatibility mode-only controller"},
      {DC_MassStorageController, MSCSC_IDEController, 0x05, "PCI native mode-only controller"},
      {DC_MassStorageController, MSCSC_IDEController, 0x0a, "ISA Compatibility mode controller w/ both channels PCI"},
      {DC_MassStorageController, MSCSC_IDEController, 0x0f, "PCI native mode controller w/ both channels ISA"},
      {DC_MassStorageController, MSCSC_IDEController, 0x80, "ISA Compatibility mode-only controller w/ mastering"},
      {DC_MassStorageController, MSCSC_IDEController, 0x85, "PCI native mode-only controller w/ mastering"},
      {DC_MassStorageController, MSCSC_IDEController, 0x8a, "ISA Compatibility mode controller w/ both channels PCI & mastering"},
      {DC_MassStorageController, MSCSC_IDEController, 0x8f, "PCI native mode controller w/ both channels ISA & mastering"},
      {DC_MassStorageController, MSCSC_ATAController, 0x20, "Single DMA"},
      {DC_MassStorageController, MSCSC_ATAController, 0x30, "Chained DMA"},
      {DC_MassStorageController, MSCSC_SATA, SATAPI_VendorSpecific, "Vendor Specific Interface"},
      {DC_MassStorageController, MSCSC_SATA, SATAPI_AHCI_1_0_Device, "AHCI 1.0"},
      {DC_MassStorageController, MSCSC_SATA, SATAPI_SerialStorageBus, "Serial Storage Bus"},
      {DC_MassStorageController, MSCSC_SerialAttachedSCSI, 0x00, "SAS"},
      {DC_MassStorageController, MSCSC_SerialAttachedSCSI, 0x01, "Serial Storage Bus"},
      {DC_MassStorageController, MSCSC_NonVolatileMemoryController, 0x01, "NVMHCI"},
      {DC_MassStorageController, MSCSC_NonVolatileMemoryController, 0x02, "NVM Express"},

      {DC_DisplayController, DCSC_VGACompatibleController, 0x00, "VGA Controller"},
      {DC_DisplayController, DCSC_VGACompatibleController, 0x01, "8514-Compatible Controller"},

      {DC_BridgeDevice, BDSC_PCIToPCIBridge1, 0x00, "Normal Decode"},
      {DC_BridgeDevice, BDSC_PCIToPCIBridge1, 0x01, "Subtractive Decode"},
      {DC_BridgeDevice, BDSC_RACEwayBridge, 0x00, "Transparent Mode"},
      {DC_BridgeDevice, BDSC_RACEwayBridge, 0x01, "Endpoint Mode"},
      {DC_BridgeDevice, BDSC_PCIToPCIBridge2, 0x40, "Semi-Transparent (primary bus toward CPU)"},
      {DC_BridgeDevice, BDSC_PCIToPCIBridge2, 0x80, "Semi-Transparent (secondary bus toward CPU)"},

      {DC_SimpleCommunicationController, SCCSC_SerialController, 0x00, "8250-Compatible (Generic XT)"},
      {DC_SimpleCommunicationController, SCCSC_SerialController, 0x01, "16450-Compatible"},
      {DC_SimpleCommunicationController, SCCSC_SerialController, 0x02, "16550-Compatible"},
      {DC_SimpleCommunicationController, SCCSC_SerialController, 0x03, "16650-Compatible"},
      {DC_SimpleCommunicationController, SCCSC_SerialController, 0x04, "16750-Compatible"},
      {DC_SimpleCommunicationController, SCCSC_SerialController, 0x05, "16850-Compatible"},
      {DC_SimpleCommunicationController, SCCSC_SerialController, 0x06, "16950-Compatible"},
      {DC_SimpleCommunicationController, SCCSC_ParallelController, 0x00, "Standard Parallel Port"},
      {DC_SimpleCommunicationController, SCCSC_ParallelController, 0x01, "Bi-Directional Parallel Port"},
      {DC_SimpleCommunicationController, SCCSC_ParallelController, 0x02, "ECP 1.X Compliant Parallel Port"},
      {DC_SimpleCommunicationController, SCCSC_ParallelController, 0x03, "IEEE 1284 Controller"},
      {DC_SimpleCommunicationController, SCCSC_ParallelController, 0xFE, "IEEE 1284 Target Device"},
      {DC_SimpleCommunicationController, SCCSC_Modem, 0x00, "Generic Modem"},
      {DC_SimpleCommunicationController, SCCSC_Modem, 0x01, "Hayes 16450-Compatible Interface"},
      {DC_SimpleCommunicationController, SCCSC_Modem, 0x02, "Hayes 16550-Compatible Interface"},
      {DC_SimpleCommunicationController, SCCSC_Modem, 0x03, "Hayes 16650-Compatible Interface"},
      {DC_SimpleCommunicationController, SCCSC_Modem, 0x04, "Hayes 16750-Compatible Interface"},

      {DC_BaseSystemPeripheral, BSPSC_PIC, 0x00, "Generic 8259-Compatible"},
      {DC_BaseSystemPeripheral, BSPSC_PIC, 0x01, "ISA-Compatible"},
      {DC_BaseSystemPeripheral, BSPSC_PIC, 0x02, "EISA-Compatible"},
      {DC_BaseSystemPeripheral, BSPSC_PIC, 0x10, "I/O APIC Interrupt Controller"},
      {DC_BaseSystemPeripheral, BSPSC_PIC, 0x20, "I/O(x) APIC Interrupt Controller"},
      {DC_BaseSystemPeripheral, BSPSC_DMAController, 0x00, "Generic 8237-Compatible"},
      {DC_BaseSystemPeripheral, BSPSC_DMAController, 0x01, "ISA-Compatible"},
      {DC_BaseSystemPeripheral, BSPSC_DMAController, 0x02, "EISA-Compatible"},
      {DC_BaseSystemPeripheral, BSPSC_Timer, 0x00, "Generic 8254-Compatible"},
      {DC_BaseSystemPeripheral, BSPSC_Timer, 0x01, "ISA-Compatible"},
      {DC_BaseSystemPeripheral, BSPSC_Timer, 0x02, "EISA-Compatible"},
      {DC_BaseSystemPeripheral, BSPSC_Timer, 0x03, "HPET"},
      {DC_BaseSystemPeripheral, BSPSC_RTCController, 0x00, "Generic RTC"},
      {DC_BaseSystemPeripheral, BSPSC_RTCController, 0x01, "ISA-Compatible"},

      {DC_InputDeviceController, IDCSC_GameportController, 0x00, "Generic"},
      {DC_InputDeviceController, IDCSC_GameportController, 0x10, "Extended"},

      {DC_SerialBusController, SBCSC_FireWireController, 0x00, "Generic"},
      {DC_SerialBusController, SBCSC_FireWireController, 0x10, "OHCI"},
      {DC_SerialBusController, SBCSC_USBController, USBPI_UHCIController, "UHCI Controller"},
      {DC_SerialBusController, SBCSC_USBController, USBPI_OHCIController, "OHCI Controller"},
      {DC_SerialBusController, SBCSC_USBController, USBPI_EHCIController_USB2, "EHCI (USB2) Controller"},
      {DC_SerialBusController, SBCSC_USBController, USBPI_XHCIController_USB3, "XHCI (USB3) Controller"},
      {DC_SerialBusController, SBCSC_USBController, USBPI_Unspecified, "Unspecified"},
      {DC_SerialBusController, SBCSC_USBController, USBPI_USBDevice, "USB Device"},
      {DC_SerialBusController, SBCSC_IPMIInterface, 0x00, "SMIC"},
      {DC_SerialBusController, SBCSC_IPMIInterface, 0x01, "Keyboard Controller Style"},
      {DC_SerialBusController, SBCSC_IPMIInterface, 0x02, "Block Transfer"}
  };


  PCIVendorIdentifier g_pci_vendors[] = {
      {0x8086, "Intel Corp."},
      {0x1022, "Advanced Micro Devices, Inc. [AMD/ATI]"},
      {0x10de, "NVIDIA Corp."},
      {0x10ec, "Realtek Semiconductor Co., Ltd."},
      {0x0bda, "Realtek Semiconductor Corp."},
      {0x168c, "Qualcomm Atheros"},
  };

  const char* GetClassString(PCIDeviceheader* pci_header) {
    for(size_t i = 0; i < sizeof(g_pci_classes) / sizeof(struct PCIClassIdentifier); i++) {
      if(g_pci_classes[i].classID == pci_header->Class) {
        return g_pci_classes[i].name;
      }
    }
    return PCI_UNKNOWN_IDENTIFIER;
  }
  const char* GetSubclassString(PCIDeviceheader* pci_header) {
    for(size_t i = 0; i < sizeof(g_pci_subclasses) / sizeof(struct PCIClassIdentifier); i++) {
      if(g_pci_subclasses[i].classID == pci_header->Class && g_pci_subclasses[i].subclassID == pci_header->Subclass) {
        return g_pci_subclasses[i].name;
      }
    }
    return PCI_UNKNOWN_IDENTIFIER;
  }
  const char* GetProgIFString(PCIDeviceheader* pci_header) {
    for(size_t i = 0; i < sizeof(g_pci_progifs) / sizeof(PCIClassIdentifier); i++) {
      if(g_pci_progifs[i].classID == pci_header->Class && g_pci_progifs[i].subclassID == pci_header->Subclass && g_pci_progifs[i].program_ifID == pci_header->ProgIF) {
        return g_pci_progifs[i].name;
      }
    }
    return PCI_UNKNOWN_IDENTIFIER;
  }
  const char* GetVendorString(PCIDeviceheader* pci_header) {
    for(size_t i = 0; i < sizeof(g_pci_vendors) / sizeof(struct PCIClassIdentifier); i++) {
      if(g_pci_vendors[i].vendorID == pci_header->VendorID) {
        return g_pci_vendors[i].name;
      }
    }
    return PCI_UNKNOWN_IDENTIFIER;
  }
}
