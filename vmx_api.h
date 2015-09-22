#ifndef _VMX_API_
#define _VMX_API_

#include <stdint.h>
#include <stdbool.h>
#include <efi.h>
#include <efilib.h>

#define PG_PRESENT 1
#define PG_SIZE 1<<7

#define MSR_IA32_VMX_BASIC   		0x480
#define MSR_IA32_FEATURE_CONTROL 	0x03a
#define MSR_IA32_VMX_PINBASED_CTLS	0x481
#define MSR_IA32_VMX_PROCBASED_CTLS 0x482
#define MSR_IA32_VMX_PROCBASED_CTLS2	0x48b
#define MSR_IA32_VMX_EXIT_CTLS		0x483
#define MSR_IA32_VMX_ENTRY_CTLS		0x484

#define MSR_IA32_VMX_CR0_FIXED0     0x486
#define MSR_IA32_VMX_CR0_FIXED1     0x487
#define MSR_IA32_VMX_CR4_FIXED0     0x488
#define MSR_IA32_VMX_CR4_FIXED1     0x489

#define MSR_IA32_VMX_EPT_VPID_CAP   0x48c

#define MSR_IA32_SYSENTER_CS		0x174
#define MSR_IA32_SYSENTER_ESP		0x175
#define MSR_IA32_SYSENTER_EIP		0x176
#define MSR_IA32_DEBUGCTL			0x1d9

#define EFER_LME     (1<<8)
#define EFER_LMA     (1<<10)

#define	MSR_EFER 0xc0000080

#define MSR_FS_BASE 0xc0000100                /* 64bit FS base */
#define MSR_GS_BASE 0xc0000101                /* 64bit GS base */

#define MSR_LSTAR		0xC0000082

/*
 * Intel CPU flags in CR0
 */
#define X86_CR0_PE              0x00000001      /* Enable Protected Mode    (RW) */
#define X86_CR0_MP              0x00000002      /* Monitor Coprocessor      (RW) */
#define X86_CR0_EM              0x00000004      /* Require FPU Emulation    (RO) */
#define X86_CR0_TS              0x00000008      /* Task Switched            (RW) */
#define X86_CR0_ET              0x00000010      /* Extension type           (RO) */
#define X86_CR0_NE              0x00000020      /* Numeric Error Reporting  (RW) */
#define X86_CR0_WP              0x00010000      /* Supervisor Write Protect (RW) */
#define X86_CR0_AM              0x00040000      /* Alignment Checking       (RW) */
#define X86_CR0_NW              0x20000000      /* Not Write-Through        (RW) */
#define X86_CR0_CD              0x40000000      /* Cache Disable            (RW) */
#define X86_CR0_PG              0x80000000      /* Paging                   (RW) */

/*
 * Intel CPU features in CR4
 */
#define X86_CR4_VME		0x0001  /* enable vm86 extensions */
#define X86_CR4_PVI		0x0002  /* virtual interrupts flag enable */
#define X86_CR4_TSD		0x0004  /* disable time stamp at ipl 3 */
#define X86_CR4_DE		0x0008  /* enable debugging extensions */
#define X86_CR4_PSE		0x0010  /* enable page size extensions */
#define X86_CR4_PAE		0x0020  /* enable physical address extensions */
#define X86_CR4_MCE		0x0040  /* Machine check enable */
#define X86_CR4_PGE		0x0080  /* enable global pages */
#define X86_CR4_PCE		0x0100  /* enable performance counters at ipl 3 */
#define X86_CR4_OSFXSR		0x0200  /* enable fast FPU save and restore */
#define X86_CR4_OSXMMEXCPT	0x0400  /* enable unmasked SSE exceptions */
#define X86_CR4_VMXE		0x2000  /* enable VMX */

enum{
  // 16 bits Guest State Fields
  GUEST_ES_SELECTOR = 0x00000800,
  GUEST_CS_SELECTOR = 0x00000802,
  GUEST_SS_SELECTOR = 0x00000804,
  GUEST_DS_SELECTOR = 0x00000806,
  GUEST_FS_SELECTOR = 0x00000808,
  GUEST_GS_SELECTOR = 0x0000080a,
  GUEST_LDTR_SELECTOR = 0x0000080c,
  GUEST_TR_SELECTOR = 0x0000080e,
  // 16 bits Host State Fields
  HOST_ES_SELECTOR = 0x00000c00,
  HOST_CS_SELECTOR = 0x00000c02,
  HOST_SS_SELECTOR = 0x00000c04,
  HOST_DS_SELECTOR = 0x00000c06,
  HOST_FS_SELECTOR = 0x00000c08,
  HOST_GS_SELECTOR = 0x00000c0a,
  HOST_TR_SELECTOR = 0x00000c0c,
  // 64 bits Control Fields
  IO_BITMAP_A = 0x00002000,
  IO_BITMAP_A_HIGH = 0x00002001,
  IO_BITMAP_B = 0x00002002,
  IO_BITMAP_B_HIGH = 0x00002003,
  MSR_BITMAP = 0x00002004,
  MSR_BITMAP_HIGH = 0x00002005,
  VM_EXIT_MSR_STORE_ADDR = 0x00002006,
  VM_EXIT_MSR_STORE_ADDR_HIGH = 0x00002007,
  VM_EXIT_MSR_LOAD_ADDR = 0x00002008,
  VM_EXIT_MSR_LOAD_ADDR_HIGH = 0x00002009,
  VM_ENTRY_MSR_LOAD_ADDR = 0x0000200a,
  VM_ENTRY_MSR_LOAD_ADDR_HIGH = 0x0000200b,
  TSC_OFFSET = 0x00002010,
  TSC_OFFSET_HIGH = 0x00002011,
  VIRTUAL_APIC_PAGE_ADDR = 0x00002012,
  VIRTUAL_APIC_PAGE_ADDR_HIGH = 0x00002013,
  EPT_POINTER_FULL = 0x0000201a,
  EPT_POINTER_HIGH = 0x0000201b,
  GUEST_PHYS_ADDR = 0x00002400,
  GUEST_PHYS_ADDR_HIGH = 0x00002401,
  // 64 bits Guest State Fields
  VMCS_LINK_POINTER = 0x00002800,
  VMCS_LINK_POINTER_HIGH = 0x00002801,
  GUEST_IA32_DEBUGCTL = 0x00002802,
  GUEST_IA32_DEBUGCTL_HIGH = 0x00002803,
  // 64 bits Host − State Field
  HOST_IA32_PERF_GLOBAL_CTRL = 0x00002C04,
  HOST_IA32_PERF_GLOBAL_CTRL_HIG = 0x00002C05,
  // 32 bits Control Fields
  PIN_BASED_VM_EXEC_CONTROL = 0x00004000,
  PRIMARY_CPU_BASED_VM_EXEC_CONTROL = 0x00004002,
  EXCEPTION_BITMAP = 0x00004004,
  PAGE_FAULT_ERROR_CODE_MASK = 0x00004006,
  PAGE_FAULT_ERROR_CODE_MATCH = 0x00004008,
  CR3_TARGET_COUNT = 0x0000400a,
  VM_EXIT_CONTROLS = 0x0000400c,
  VM_EXIT_MSR_STORE_COUNT = 0x0000400e,
  VM_EXIT_MSR_LOAD_COUNT = 0x00004010,
  VM_ENTRY_CONTROLS = 0x00004012,
  VM_ENTRY_MSR_LOAD_COUNT = 0x00004014,
  VM_ENTRY_INTR_INFO_FIELD = 0x00004016,
  VM_ENTRY_EXCEPTION_ERROR_CODE = 0x00004018,
  VM_ENTRY_INSTRUCTION_LEN = 0x0000401a,
  TPR_THRESHOLD = 0x0000401c,
  SECONDARY_CPU_BASED_VM_EXEC_CONTROL = 0x000401e,
  // 32 bits Read Only Data Fields
  VM_INSTRUCTION_ERROR = 0x00004400,
  VM_EXIT_REASON = 0x00004402,
  VM_EXIT_INTR_INFO = 0x00004404,
  VM_EXIT_INTR_ERROR_CODE = 0x00004406,
  IDT_VECTORING_INFO_FIELD = 0x00004408,
  IDT_VECTORING_ERROR_CODE = 0x0000440a,
  VM_EXIT_INSTRUCTION_LEN = 0x0000440c,
  VMX_INSTRUCTION_INFO = 0x0000440e,
  // 32 bits Guest State Fields
  GUEST_ES_LIMIT = 0x00004800,
  GUEST_CS_LIMIT = 0x00004802,
  GUEST_SS_LIMIT = 0x00004804,
  GUEST_DS_LIMIT = 0x00004806,
  GUEST_FS_LIMIT = 0x00004808,
  GUEST_GS_LIMIT = 0x0000480a,
  GUEST_LDTR_LIMIT = 0x0000480c,
  GUEST_TR_LIMIT = 0x0000480e,
  GUEST_GDTR_LIMIT = 0x00004810,
  GUEST_IDTR_LIMIT = 0x00004812,
  GUEST_ES_AR_BYTES = 0x00004814,
  GUEST_CS_AR_BYTES = 0x00004816,
  GUEST_SS_AR_BYTES = 0x00004818,
  GUEST_DS_AR_BYTES = 0x0000481a,
  GUEST_FS_AR_BYTES = 0x0000481c,
  GUEST_GS_AR_BYTES = 0x0000481e,
  GUEST_LDTR_AR_BYTES = 0x00004820,
  GUEST_TR_AR_BYTES = 0x00004822,
  GUEST_INTERRUPTIBILITY_INFO = 0x00004824,
  GUEST_ACTIVITY_STATE = 0x00004826,
  GUEST_SM_BASE = 0x00004828,
  GUEST_SYSENTER_CS = 0x0000482A,
  // 32 bits Host State Field
  HOST_IA32_SYSENTER_CS = 0x00004c00,
  // Natural width Control Fields
  CR0_GUEST_HOST_MASK = 0x00006000,
  CR4_GUEST_HOST_MASK = 0x00006002,
  CR0_READ_SHADOW = 0x00006004,
  CR4_READ_SHADOW = 0x00006006,
  CR3_TARGET_VALUE0 = 0x00006008,
  CR3_TARGET_VALUE1 = 0x0000600a,
  CR3_TARGET_VALUE2 = 0x0000600c,
  CR3_TARGET_VALUE3 = 0x0000600e,
  // Natural Width Read Only Data Fields
  EXIT_QUALIFICATION = 0x00006400,
  GUEST_LINEAR_ADDRESS = 0x0000640a,
  // Natural Witdh Guest State Fields
  GUEST_CR0 = 0x00006800,
  GUEST_CR3 = 0x00006802,
  GUEST_CR4 = 0x00006804,
  GUEST_ES_BASE = 0x00006806,
  GUEST_CS_BASE = 0x00006808,
  GUEST_SS_BASE = 0x0000680a,
  GUEST_DS_BASE = 0x0000680c,
  GUEST_FS_BASE = 0x0000680e,
  GUEST_GS_BASE = 0x00006810,
  GUEST_LDTR_BASE = 0x00006812,
  GUEST_TR_BASE = 0x00006814,
  GUEST_GDTR_BASE = 0x00006816,
  GUEST_IDTR_BASE = 0x00006818,
  GUEST_DR7 = 0x0000681a,
  GUEST_ESP = 0x0000681c,
  GUEST_EIP = 0x0000681e,
  GUEST_EFLAGS = 0x00006820,
  GUEST_PENDING_DBG_EXCEPTIONS = 0x00006822,
  GUEST_SYSENTER_ESP = 0x00006824,
  GUEST_SYSENTER_EIP = 0x00006826,
  // Natural Width Host State Fields
  HOST_CR0 = 0x00006c00,
  HOST_CR3 = 0x00006c02,
  HOST_CR4 = 0x00006c04,
  HOST_FS_BASE = 0x00006c06,
  HOST_GS_BASE = 0x00006c08,
  HOST_TR_BASE = 0x00006c0a,
  HOST_GDTR_BASE = 0x00006c0c,
  HOST_IDTR_BASE = 0x00006c0e,
  HOST_IA32_SYSENTER_ESP = 0x00006c10,
  HOST_IA32_SYSENTER_EIP = 0x00006c12,
  HOST_ESP = 0x00006c14,
  HOST_EIP = 0x00006c16,
};

//
// VMX Exit Reasons
//
#define VMX_EXIT_REASONS_FAILED_VMENTRY 0x80000000
#define EXIT_REASON_EXCEPTION_NMI 0
#define EXIT_REASON_EXTERNAL_INTERRUPT 1
#define EXIT_REASON_TRIPLE_FAULT 2
#define EXIT_REASON_INIT 3
#define EXIT_REASON_SIPI 4
#define EXIT_REASON_IO_SMI 5
#define EXIT_REASON_OTHER_SMI 6
#define EXIT_REASON_PENDING_INTERRUPT 7
#define EXIT_REASON_TASK_SWITCH 9
#define EXIT_REASON_CPUID 10
#define EXIT_REASON_HLT 12
#define EXIT_REASON_INVD 13
#define EXIT_REASON_INVLPG 14
#define EXIT_REASON_RDPMC 15
#define EXIT_REASON_RDTSC 16
#define EXIT_REASON_RSM 17
#define EXIT_REASON_VMCALL 18
#define EXIT_REASON_VMCLEAR 19
#define EXIT_REASON_VMLAUNCH 20
#define EXIT_REASON_VMPTRLD 21
#define EXIT_REASON_VMPTRST 22
#define EXIT_REASON_VMREAD 23
#define EXIT_REASON_VMRESUME 24
#define EXIT_REASON_VMWRITE 25
#define EXIT_REASON_VMXOFF 26
#define EXIT_REASON_VMXON 27
#define EXIT_REASON_CR_ACCESS 28
#define EXIT_REASON_DR_ACCESS 29
#define EXIT_REASON_IO_INSTRUCTION 30
#define EXIT_REASON_MSR_READ 31
#define EXIT_REASON_MSR_WRITE 32
#define EXIT_REASON_INVALID_GUEST_STATE 33
#define EXIT_REASON_MSR_LOADING 34
#define EXIT_REASON_MWAIT_INSTRUCTION 36
#define EXIT_REASON_MONITOR_INSTRUCTION 39
#define EXIT_REASON_PAUSE_INSTRUCTION 40
#define EXIT_REASON_MACHINE_CHECK 41
#define EXIT_REASON_TPR_BELOW_THRESHOLD 43
#define EXIT_REASON_EPT_MISCONFIGURATION 49
#define VMX_MAX_GUEST_VMEXIT EXIT_REASON_EPT_MISCONFIGURATION

#define CPU_BASED_ACTIVATE_MSR_BITMAP   0x10000000

//#define VM_EXIT_HOST_ADDR_SPACE_SIZE    0x00000100
#define VM_EXIT_IA32E_MODE              0x00000200
#define VM_EXIT_ACK_INTR_ON_EXIT        0x00008000
#define VM_EXIT_SAVE_IA32_EFER          0x00100000
//#define VM_EXIT_LOAD_IA32_EFER          0x00200000

#define VM_EXEC_PROCBASED_CTLS2_ENABLE 0x80000000
#define VM_EXEC_UG  0x80
#define VM_EXEC_EPT 0x2
#define VM_EXEC_VPID 0x20


#define VM_ENTRY_IA32E_MODE             0x00000200
#define VM_ENTRY_SMM                    0x00000400
#define VM_ENTRY_DEACT_DUAL_MONITOR     0x00000800
#define VM_ENTRY_LOAD_IA32_EFER         0x00008000

#define STATE_ACTIVE 0
#define STATE_HLT 1
#define STATE_SHUTDOWN 2
#define STATE_WAIT_FOR_SIPI 3

typedef struct{
  uint64_t idt_limit;
  uint64_t gdt_limit;
  uint64_t idt_base;
  uint64_t gdt_base;
  uint64_t tss_base;
  uint64_t tr_sel;
  uint64_t host_cr3;
  uint64_t guest_cr3_32bit;
  uint64_t ept_area;
  uint64_t debug_area;
} SharedTables;

typedef struct{
  uint8_t cpu_id;
  bool guest_realmode;
  bool guest_realsegment;
  uint64_t guest_EFER;
  uint64_t guest_CR0;
  uint64_t guest_CR3;
  uint64_t guest_CR4;
  EFI_PHYSICAL_ADDRESS vmxon_region;
  EFI_PHYSICAL_ADDRESS vmcs;
  EFI_PHYSICAL_ADDRESS host_stack;
  SharedTables * st;
} HVM;

extern HVM * bsp_hvm;
extern HVM * ap_hvm; // array of AP HVMs

int vmx_supported(void);
int vmx_ug_supported(void);
int vmx_ept_supported(void);
int vmx_vpid_supported(void);
void vmx_get_revision_and_struct_size(uint32_t * rev, uint32_t * struct_size);
void vmx_enable(void);
int vmx_switch_to_root_op(void * vmxon_region);
int vmx_vmcs_activate(void * vmcs);
void vmx_write(uint64_t index, uint64_t value);
uint64_t vmx_read(uint64_t index);
void vmx_launch(void);
void vmx_exit(void);
void vmx_ret(void);

void vmx_enable_a20_line(void);
void vmx_disable_a20_line(void);

#endif