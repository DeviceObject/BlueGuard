#ifndef _SMP_
#define _SMP_

#include <efi.h>
#include <efilib.h>
#include <stdarg.h>

#define MSR_IA32_APIC_BASE 0x1B
// IA32_APIC_BASE flags:
#define APIC_ENABLED 1 << 11
#define IS_BSP 1 << 8

extern volatile int * CPUs_activated;
extern volatile int CPU_notified;
extern int CPU_count;
extern uint64_t LAPIC_addr;

extern void * ap_stacks;

// Local APIC Register Addresses
#define LAPIC_ID_REG 0x20
#define SPURIOUS_INT_REG 0xF0
#define INT_COMMAND_REG_LOW 0x300
#define INT_COMMAND_REG_HIGH 0x310

// Local x2APIC Registers
#define MSR_LAPIC_ID_REG 0x802
#define MSR_SPURIOUS_INT_REG 0x80F
#define MSR_INT_COMMAND_REG 0x830

// IPI flags
#define DLV_STATUS 1 << 12 // 0: command completed, 1: command pending
#define LVL_ASSERT 1 << 14
#define DM_INIT 5 << 8
#define DM_STARTUP 6 << 8

extern uint8_t ProcAPIC_IDs[256];
extern uint32_t Proc_x2APIC_IDs[256];

typedef struct _RSDP{
	// In ACPI >= 1
	char Signature[8];
	uint8_t Checksum;
	char OEMID[6];
	uint8_t Revision;
	uint32_t RsdtAddress;
	// In ACPI >= 2
	uint32_t Length;
	uint64_t XsdtAddress;
	uint8_t ExtendedChecksum;
	uint8_t reserved[3];
} __attribute__((packed)) RSDP;

typedef struct _SDTHeader{
  char Signature[4];
  uint32_t Length;
  uint8_t Revision;
  uint8_t Checksum;
  char OEMID[6];
  char OEMTableID[8];
  uint32_t OEMRevision;
  uint32_t CreatorID;
  uint32_t CreatorRevision;
} __attribute__((packed)) SDTHeader;

typedef struct _XSDT{
  SDTHeader h;
  uint64_t PointerToOtherSDT[1]; // Actual length according to h.Length
} __attribute__((packed)) XSDT;


typedef struct _APICStructHeader{
	uint8_t Type;
	uint8_t Length;
} __attribute__((packed)) APICStructHeader;

typedef struct _MADT{
	SDTHeader h;
	uint32_t LocalControllerAddress; // Important (LAPIC)
	uint32_t Flags;
	APICStructHeader APICStructs[1];
} __attribute__((packed)) MADT;

enum{
	TypeProcLocalAPIC,
	TypeIO_APIC,
	TypeProcLocal_x2APIC = 9
	/* ... */
};

#define PROC_ENABLED 1 // ProcLocalAPIC flag

typedef struct _EntryProcLocalAPIC{
	APICStructHeader h;
	uint8_t ProcID;
	uint8_t APIC_ID;
	uint32_t Flags;
} __attribute__((packed)) EntryProcLocalAPIC;

typedef struct _EntryProcLocal_x2APIC{
	APICStructHeader h;
	uint16_t reserved;
	uint32_t x2APIC_ID;
	uint32_t Flags;
	uint32_t ProcUID;
} __attribute__((packed)) EntryProcLocal_x2APIC;

int init_smp(void);
int start_smp(void);
void ap_entry64(uint8_t cpu);
void recv_msg(char * str);
void send_msg(char * str);
int bsp_printf(const char * format, ...);

#endif