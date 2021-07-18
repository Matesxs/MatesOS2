#pragma once

namespace PCI
{
  enum DeviceClass
  {
    DC_Unclassified = 0x00,
    DC_MassStorageController = 0x01,
    DC_NetworkController = 0x02,
    DC_DisplayController = 0x03,
    DC_MultimediaController = 0x04,
    DC_MemoryController = 0x05,
    DC_BridgeDevice = 0x06,
    DC_SimpleCommunicationController = 0x07,
    DC_BaseSystemPeripheral = 0x08,
    DC_InputDeviceController = 0x09,
    DC_DockingStation = 0x0A,
    DC_Processor = 0x0B,
    DC_SerialBusController = 0x0C,
    DC_WirelessController = 0x0D,
    DC_InteligentController = 0x0E,
    DC_SateliteCommunicationController = 0x0F,
    DC_EncryptionController = 0x10,
    DC_SignalProcessingController = 0x11,
    DC_ProcessingAccelerator = 0x12,
    DC_NonEssentialInstrumentation = 0x13,
    DC_CoProcessor = 0x40
  };

  enum UnclassifiedSubclass
  {
    UCSC_NonVGACompatibleDevice = 0x00,
    UCSC_VGACompatibleDevice = 0x01
  };

  enum MassStorageControllerSubclass
  {
    MSCSC_SCSIBusController = 0x00,
    MSCSC_IDEController = 0x01,
    MSCSC_FloppyDiskController = 0x02,
    MSCSC_IPIBusController = 0x03,
    MSCSC_RaidController = 0x04,
    MSCSC_ATAController = 0x05,
    MSCSC_SATA = 0x06,
    MSCSC_SerialAttachedSCSI = 0x07,
    MSCSC_NonVolatileMemoryController = 0x08,
    MSCSC_Other = 0x80
  };

  enum NetworkControllerSubclass
  {
    NCSC_EthernetController = 0x00,
    NCSC_TokenRingController = 0x01,
    NCSC_FDDIController = 0x02,
    NCSC_ATMController = 0x03,
    NCSC_ISDNController = 0x04,
    NCSC_WorldFlipController = 0x05,
    NCSC_PICMG_2_14_MultiComputing = 0x06,
    NCSC_InfinibandController = 0x07,
    NCSC_FabricController = 0x08,
    NCSC_Other = 0x80
  };

  enum DisplayControllerSubclass
  {
    DCSC_VGACompatibleController = 0x00,
    DCSC_XGAController = 0x01,
    DCSC_3DController = 0x02,
    DCSC_Other = 0x80
  };

  enum MultimediaControllerSubclass
  {
    MMCSC_MultimediaVideoController = 0x00,
    MMCSC_MultimediaAudioController = 0x01,
    MMCSC_ComputerTelephonyDevice = 0x02,
    MMCSC_AudioDevice = 0x03,
    MMCSC_Other = 0x08
  };

  enum MemoryControllerSubclass
  {
    MCSC_RAMController = 0x00,
    MCSC_FlashController = 0x01,
    MCSC_Other = 0x80
  };

  enum BridgeDeviceSubclass
  {
    BDSC_HostBridge = 0x00,
    BDSC_ISABridge = 0x01,
    BDSC_EISABridge = 0x02,
    BDSC_MCABridge = 0x03,
    BDSC_PCIToPCIBridge1 = 0x04,
    BDSC_PCMCIABridge = 0x05,
    BDSC_NuBusBridge = 0x06,
    BDSC_CardBusBridge = 0x07,
    BDSC_RACEwayBridge = 0x08,
    BDSC_PCIToPCIBridge2 = 0x09,
    BDSC_InfiniBandToPCIHostBridge = 0x0A,
    BDSC_Other = 0x80
  };

  enum SimpleCommunicationControllerSubclass
  {
    SCCSC_SerialController = 0x00,
    SCCSC_ParallelController = 0x01,
    SCCSC_MultiportSerialController = 0x02,
    SCCSC_Modem = 0x03,
    SCCSC_GPIBController = 0x04,
    SCCSC_SmartCard = 0x05,
    SCCSC_Other = 0x80
  };

  enum BaseSystemPeripheralSubclass
  {
    BSPSC_PIC = 0x00,
    BSPSC_DMAController = 0x01,
    BSPSC_Timer = 0x02,
    BSPSC_RTCController = 0x03,
    BSPSC_PCIHotPlugController = 0x04,
    BSPSC_SDHostController = 0x05,
    BSPSC_IOMMU = 0x06,
    BSPSC_Other = 0x80
  };

  enum InputDeviceControllerSubclass
  {
    IDCSC_KeyboardController = 0x00,
    IDCSC_DigitizerPen = 0x01,
    IDCSC_MouseController = 0x02,
    IDCSC_ScannerController = 0x03,
    IDCSC_GameportController = 0x04,
    IDCSC_Other = 0x80
  };

  enum DockingStationSubclass
  {
    DSSC_Generic = 0x00,
    DSSC_Other = 0x80
  };

  enum ProcessorSubclass
  {
    PSC_386 = 0x00,
    PSC_486 = 0x01,
    PSC_Pentium = 0x02,
    PSC_PentiumPro = 0x03,
    PSC_Alpha = 0x10,
    PSC_PowerPC = 0x20,
    PSC_MIPS = 0x30,
    PSC_CoProcessor = 0x40,
    PSC_Other = 0x80
  };

  enum SerialBusControllerSubclass
  {
    SBCSC_FireWireController = 0x00,
    SBCSC_ACCESSBus = 0x01,
    SBCSC_SSA = 0x02,
    SBCSC_USBController = 0x03,
    SBCSC_FibreChannel = 0x04,
    SBCSC_SMBus = 0x05,
    SBCSC_InfiniBand = 0x06,
    SBCSC_IPMIInterface = 0x07,
    SBCSC_SERCOSInterface = 0x08,
    SBCSC_CANBus = 0x09,
    SBCSC_Other = 0x80
  };

  enum WirelessControllerSubclass
  {
    WCSC_iRDACompatibleController = 0x00,
    WCSC_ConsumerIRController = 0x01,
    WCSC_RFController = 0x10,
    WCSC_BluetoothController = 0x11,
    WCSC_BroadbandController = 0x12,
    WCSC_EthernetController802_1a = 0x20,
    WCSC_EthernetController802_1b = 0x21,
    WCSC_Other = 0x80
  };

  enum IntelligentControllerSubclas
  {
    ICSC_I20 = 0x00,
  };

  enum SatelliteCommunicationControllerSubclass
  {
    SCCSC_SatelliteTVController = 0x01,
    SCCSC_SatelliteAudioController = 0x02,
    SCCSC_SatelliteVoiceController = 0x03,
    SCCSC_SatelliteDataController = 0x04
  };

  enum EncryptionControllerSubclass
  {
    ECSC_Network_Computing_Encrpytion_Decryption = 0x00,
    ECSC_EntertainmentEncryption_Decryption = 0x10,
    ECSC_Other = 0x80
  };

  enum SignalProcessingControllerSubclass
  {
    SPCSC_DPIOModules = 0x00,
    SPCSC_PerformanceCounters = 0x01,
    SPCSC_CommunicationSynchronizer = 0x10,
    SPCSC_SignalProcessingManagement = 0x20,
    SPCSC_Other = 0x80
  };

  enum SATAProgramInterface
  {
    SATAPI_VendorSpecific = 0x00,
    SATAPI_AHCI_1_0_Device = 0x01,
    SATAPI_SerialStorageBus = 0x02
  };

  enum USBProgramInterface
  {
    USBPI_UHCIController = 0x00,
    USBPI_OHCIController = 0x10,
    USBPI_EHCIController_USB2 = 0x20,
    USBPI_XHCIController_USB3 = 0x30,
    USBPI_Unspecified = 0x80,
    USBPI_USBDevice = 0xFE
  };
}