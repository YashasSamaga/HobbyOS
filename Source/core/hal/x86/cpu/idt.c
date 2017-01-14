/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	Processor Interface
//	Interrupt Descriptor Table Implementations
//
//	idt.c
//	Provides an interface to work with processor's IDT.
//
//	Date: January 6th 2017
//
/*************************************************************************************************/
#include <stdint.h>

#include <hal.h>
#include <chips/pic-i8259.h>
#include <cpu/cpu.h>
#include <cpu/idt.h>
#include <cpu/gdt.h>

/*==============================================================================================*/
// Implementation External Function Prototypes
/*==============================================================================================*/
extern void isr_except0();
extern void isr_except1();
extern void isr_except2();
extern void isr_except3();
extern void isr_except4();
extern void isr_except5();
extern void isr_except6();
extern void isr_except7();
extern void isr_except8();
extern void isr_except9();
extern void isr_except10();
extern void isr_except11();
extern void isr_except12();
extern void isr_except13();
extern void isr_except14();
extern void isr_except15();
extern void isr_except16();
extern void isr_except17();
extern void isr_except18();
extern void isr_except19();
extern void isr_except20();
extern void isr_except21();
extern void isr_except22();
extern void isr_except23();
extern void isr_except24();
extern void isr_except25();
extern void isr_except26();
extern void isr_except27();
extern void isr_except28();
extern void isr_except29();
extern void isr_except30();
extern void isr_except31();

extern void isr_hwd_irq0();
extern void isr_hwd_irq1();
extern void isr_hwd_irq2();
extern void isr_hwd_irq3();
extern void isr_hwd_irq4();
extern void isr_hwd_irq5();
extern void isr_hwd_irq6();
extern void isr_hwd_irq7();
extern void isr_hwd_irq8();
extern void isr_hwd_irq9();
extern void isr_hwd_irq10();
extern void isr_hwd_irq11();
extern void isr_hwd_irq12();
extern void isr_hwd_irq13();
extern void isr_hwd_irq14();
extern void isr_hwd_irq15();

extern void isr48();
extern void isr49();
extern void isr50();
extern void isr51();
extern void isr52();
extern void isr53();
extern void isr54();
extern void isr55();
extern void isr56();
extern void isr57();
extern void isr58();
extern void isr59();
extern void isr60();
extern void isr61();
extern void isr62();
extern void isr63();
extern void isr64();
extern void isr65();
extern void isr66();
extern void isr67();
extern void isr68();
extern void isr69();
extern void isr70();
extern void isr71();
extern void isr72();
extern void isr73();
extern void isr74();
extern void isr75();
extern void isr76();
extern void isr77();
extern void isr78();
extern void isr79();
extern void isr80();
extern void isr81();
extern void isr82();
extern void isr83();
extern void isr84();
extern void isr85();
extern void isr86();
extern void isr87();
extern void isr88();
extern void isr89();
extern void isr90();
extern void isr91();
extern void isr92();
extern void isr93();
extern void isr94();
extern void isr95();
extern void isr96();
extern void isr97();
extern void isr98();
extern void isr99();
extern void isr100();
extern void isr101();
extern void isr102();
extern void isr103();
extern void isr104();
extern void isr105();
extern void isr106();
extern void isr107();
extern void isr108();
extern void isr109();
extern void isr110();
extern void isr111();
extern void isr112();
extern void isr113();
extern void isr114();
extern void isr115();
extern void isr116();
extern void isr117();
extern void isr118();
extern void isr119();
extern void isr120();
extern void isr121();
extern void isr122();
extern void isr123();
extern void isr124();
extern void isr125();
extern void isr126();
extern void isr127();
extern void isr128();
extern void isr129();
extern void isr130();
extern void isr131();
extern void isr132();
extern void isr133();
extern void isr134();
extern void isr135();
extern void isr136();
extern void isr137();
extern void isr138();
extern void isr139();
extern void isr140();
extern void isr141();
extern void isr142();
extern void isr143();
extern void isr144();
extern void isr145();
extern void isr146();
extern void isr147();
extern void isr148();
extern void isr149();
extern void isr150();
extern void isr151();
extern void isr152();
extern void isr153();
extern void isr154();
extern void isr155();
extern void isr156();
extern void isr157();
extern void isr158();
extern void isr159();
extern void isr160();
extern void isr161();
extern void isr162();
extern void isr163();
extern void isr164();
extern void isr165();
extern void isr166();
extern void isr167();
extern void isr168();
extern void isr169();
extern void isr170();
extern void isr171();
extern void isr172();
extern void isr173();
extern void isr174();
extern void isr175();
extern void isr176();
extern void isr177();
extern void isr178();
extern void isr179();
extern void isr180();
extern void isr181();
extern void isr182();
extern void isr183();
extern void isr184();
extern void isr185();
extern void isr186();
extern void isr187();
extern void isr188();
extern void isr189();
extern void isr190();
extern void isr191();
extern void isr192();
extern void isr193();
extern void isr194();
extern void isr195();
extern void isr196();
extern void isr197();
extern void isr198();
extern void isr199();
extern void isr200();
extern void isr201();
extern void isr202();
extern void isr203();
extern void isr204();
extern void isr205();
extern void isr206();
extern void isr207();
extern void isr208();
extern void isr209();
extern void isr210();
extern void isr211();
extern void isr212();
extern void isr213();
extern void isr214();
extern void isr215();
extern void isr216();
extern void isr217();
extern void isr218();
extern void isr219();
extern void isr220();
extern void isr221();
extern void isr222();
extern void isr223();
extern void isr224();
extern void isr225();
extern void isr226();
extern void isr227();
extern void isr228();
extern void isr229();
extern void isr230();
extern void isr231();
extern void isr232();
extern void isr233();
extern void isr234();
extern void isr235();
extern void isr236();
extern void isr237();
extern void isr238();
extern void isr239();
extern void isr240();
extern void isr241();
extern void isr242();
extern void isr243();
extern void isr244();
extern void isr245();
extern void isr246();
extern void isr247();
extern void isr248();
extern void isr249();
extern void isr250();
extern void isr251();
extern void isr252();
extern void isr253();
extern void isr254();
extern void isr255();

/*==============================================================================================*/
// Implementation Structures (Private)
/*==============================================================================================*/
struct idt_ptr
{
    uint16_t limit;
    uintptr_t base;
} __attribute__((packed));

/*==============================================================================================*/
// Implementation Data (Private)
/*==============================================================================================*/
static struct
{
	struct idt_entry entries [MAX_INTERRUPTS];
	struct idt_ptr idtr;
}idt;

/*==============================================================================================*/
// Interface Functions
/*==============================================================================================*/
/*************************************************************************************************
	<summary>idt_get_descriptor</summary>
	<para>gets the pointer to the asked descriptor</para>
	<param name="idx" type="unsigned int">IDT descriptor index</param>
	<remarks>the pointer returned points to the "real" descriptor in the memory</remarks>
	<returns>a pointer to the descriptor (idt_entry *)</returns>
*************************************************************************************************/
struct idt_entry* idt_get_descriptor (int idx) 
{
	return &idt.entries[idx];
}

/*************************************************************************************************
	<summary>idt_set_descriptor</summary>
	<para>sets a IDT descriptor</para>
	<param name="num" type="unsigned int">IDT descriptor index</param>
	<param name="base" type="uint32_t">IR base address</param>
	<param name="sel" type="uint16_t">GDT segment selector</param>
	<param name="flags" type="uint8_t">flags</param>
	<remarks>refer to cpu.h for the list of flags</remarks>
*************************************************************************************************/
void idt_set_descriptor(uint8_t num, uintptr_t base, uint16_t sel, uint8_t flags)
{
    idt.entries[num].base_low = (base & 0xFFFF);
    idt.entries[num].base_high = (base >> 16) & 0xFFFF;
    idt.entries[num].sel = sel;
    idt.entries[num].always0 = 0;
    idt.entries[num].flags = flags;
}

/*************************************************************************************************
	<summary>initilize_idt</summary>
	<para>installs the IDT</para>
	<remarks>sets the descriptors (including exceptions and hardware interrupts)</remarks>
*************************************************************************************************/
void initilize_idt()
{
	// Exceptions
	idt_set_descriptor(0, (unsigned)isr_except0, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(1, (unsigned)isr_except1, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(2, (unsigned)isr_except2, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(3, (unsigned)isr_except3, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(4, (unsigned)isr_except4, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(5, (unsigned)isr_except5, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(6, (unsigned)isr_except6, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(7, (unsigned)isr_except7, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(8, (unsigned)isr_except8, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(9, (unsigned)isr_except9, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(10, (unsigned)isr_except10, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(11, (unsigned)isr_except11, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(12, (unsigned)isr_except12, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(13, (unsigned)isr_except13, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(14, (unsigned)isr_except14, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(15, (unsigned)isr_except15, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(16, (unsigned)isr_except16, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(17, (unsigned)isr_except17, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(18, (unsigned)isr_except18, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(19, (unsigned)isr_except19, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(20, (unsigned)isr_except20, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(21, (unsigned)isr_except21, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(22, (unsigned)isr_except22, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(23, (unsigned)isr_except23, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(24, (unsigned)isr_except24, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(25, (unsigned)isr_except25, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(26, (unsigned)isr_except26, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(27, (unsigned)isr_except27, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(28, (unsigned)isr_except28, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(29, (unsigned)isr_except29, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(30, (unsigned)isr_except30, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(31, (unsigned)isr_except31, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	
	// Hardware Interrupts
	idt_set_descriptor(32, (unsigned)isr_hwd_irq0, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(33, (unsigned)isr_hwd_irq1, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(34, (unsigned)isr_hwd_irq2, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(35, (unsigned)isr_hwd_irq3, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(36, (unsigned)isr_hwd_irq4, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(37, (unsigned)isr_hwd_irq5, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(38, (unsigned)isr_hwd_irq6, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(39, (unsigned)isr_hwd_irq7, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);

    idt_set_descriptor(40, (unsigned)isr_hwd_irq8, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(41, (unsigned)isr_hwd_irq9, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(42, (unsigned)isr_hwd_irq10, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(43, (unsigned)isr_hwd_irq11, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(44, (unsigned)isr_hwd_irq12, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(45, (unsigned)isr_hwd_irq13, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(46, (unsigned)isr_hwd_irq14, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
    idt_set_descriptor(47, (unsigned)isr_hwd_irq15, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	
	// Other Software Interrupts	
	idt_set_descriptor(48, (unsigned)isr48, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(49, (unsigned)isr49, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(50, (unsigned)isr50, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(51, (unsigned)isr51, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(52, (unsigned)isr52, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(53, (unsigned)isr53, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(54, (unsigned)isr54, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(55, (unsigned)isr55, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(56, (unsigned)isr56, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(57, (unsigned)isr57, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(58, (unsigned)isr58, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(59, (unsigned)isr59, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(60, (unsigned)isr60, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(61, (unsigned)isr61, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(62, (unsigned)isr62, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(63, (unsigned)isr63, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(64, (unsigned)isr64, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(65, (unsigned)isr65, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(66, (unsigned)isr66, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(67, (unsigned)isr67, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(68, (unsigned)isr68, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(69, (unsigned)isr69, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(70, (unsigned)isr70, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(71, (unsigned)isr71, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(72, (unsigned)isr72, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(73, (unsigned)isr73, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(74, (unsigned)isr74, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(75, (unsigned)isr75, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(76, (unsigned)isr76, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(77, (unsigned)isr77, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(78, (unsigned)isr78, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(79, (unsigned)isr79, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(80, (unsigned)isr80, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(81, (unsigned)isr81, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(82, (unsigned)isr82, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(83, (unsigned)isr83, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(84, (unsigned)isr84, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(85, (unsigned)isr85, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(86, (unsigned)isr86, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(87, (unsigned)isr87, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(88, (unsigned)isr88, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(89, (unsigned)isr89, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(90, (unsigned)isr90, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(91, (unsigned)isr91, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(92, (unsigned)isr92, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(93, (unsigned)isr93, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(94, (unsigned)isr94, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(95, (unsigned)isr95, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(96, (unsigned)isr96, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(97, (unsigned)isr97, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(98, (unsigned)isr98, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(99, (unsigned)isr99, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(100, (unsigned)isr100, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(101, (unsigned)isr101, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(102, (unsigned)isr102, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(103, (unsigned)isr103, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(104, (unsigned)isr104, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(105, (unsigned)isr105, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(106, (unsigned)isr106, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(107, (unsigned)isr107, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(108, (unsigned)isr108, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(109, (unsigned)isr109, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(110, (unsigned)isr110, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(111, (unsigned)isr111, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(112, (unsigned)isr112, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(113, (unsigned)isr113, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(114, (unsigned)isr114, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(115, (unsigned)isr115, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(116, (unsigned)isr116, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(117, (unsigned)isr117, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(118, (unsigned)isr118, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(119, (unsigned)isr119, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(120, (unsigned)isr120, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(121, (unsigned)isr121, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(122, (unsigned)isr122, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(123, (unsigned)isr123, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(124, (unsigned)isr124, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(125, (unsigned)isr125, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(126, (unsigned)isr126, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(127, (unsigned)isr127, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(128, (unsigned)isr128, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(129, (unsigned)isr129, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(130, (unsigned)isr130, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(131, (unsigned)isr131, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(132, (unsigned)isr132, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(133, (unsigned)isr133, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(134, (unsigned)isr134, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(135, (unsigned)isr135, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(136, (unsigned)isr136, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(137, (unsigned)isr137, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(138, (unsigned)isr138, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(139, (unsigned)isr139, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(140, (unsigned)isr140, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(141, (unsigned)isr141, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(142, (unsigned)isr142, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(143, (unsigned)isr143, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(144, (unsigned)isr144, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(145, (unsigned)isr145, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(146, (unsigned)isr146, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(147, (unsigned)isr147, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(148, (unsigned)isr148, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(149, (unsigned)isr149, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(150, (unsigned)isr150, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(151, (unsigned)isr151, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(152, (unsigned)isr152, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(153, (unsigned)isr153, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(154, (unsigned)isr154, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(155, (unsigned)isr155, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(156, (unsigned)isr156, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(157, (unsigned)isr157, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(158, (unsigned)isr158, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(159, (unsigned)isr159, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(160, (unsigned)isr160, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(161, (unsigned)isr161, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(162, (unsigned)isr162, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(163, (unsigned)isr163, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(164, (unsigned)isr164, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(165, (unsigned)isr165, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(166, (unsigned)isr166, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(167, (unsigned)isr167, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(168, (unsigned)isr168, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(169, (unsigned)isr169, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(170, (unsigned)isr170, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(171, (unsigned)isr171, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(172, (unsigned)isr172, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(173, (unsigned)isr173, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(174, (unsigned)isr174, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(175, (unsigned)isr175, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(176, (unsigned)isr176, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(177, (unsigned)isr177, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(178, (unsigned)isr178, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(179, (unsigned)isr179, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(180, (unsigned)isr180, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(181, (unsigned)isr181, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(182, (unsigned)isr182, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(183, (unsigned)isr183, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(184, (unsigned)isr184, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(185, (unsigned)isr185, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(186, (unsigned)isr186, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(187, (unsigned)isr187, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(188, (unsigned)isr188, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(189, (unsigned)isr189, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(190, (unsigned)isr190, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(191, (unsigned)isr191, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(192, (unsigned)isr192, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(193, (unsigned)isr193, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(194, (unsigned)isr194, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(195, (unsigned)isr195, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(196, (unsigned)isr196, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(197, (unsigned)isr197, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(198, (unsigned)isr198, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(199, (unsigned)isr199, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(200, (unsigned)isr200, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(201, (unsigned)isr201, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(202, (unsigned)isr202, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(203, (unsigned)isr203, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(204, (unsigned)isr204, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(205, (unsigned)isr205, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(206, (unsigned)isr206, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(207, (unsigned)isr207, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(208, (unsigned)isr208, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(209, (unsigned)isr209, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(210, (unsigned)isr210, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(211, (unsigned)isr211, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(212, (unsigned)isr212, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(213, (unsigned)isr213, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(214, (unsigned)isr214, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(215, (unsigned)isr215, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(216, (unsigned)isr216, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(217, (unsigned)isr217, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(218, (unsigned)isr218, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(219, (unsigned)isr219, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(220, (unsigned)isr220, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(221, (unsigned)isr221, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(222, (unsigned)isr222, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(223, (unsigned)isr223, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(224, (unsigned)isr224, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(225, (unsigned)isr225, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(226, (unsigned)isr226, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(227, (unsigned)isr227, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(228, (unsigned)isr228, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(229, (unsigned)isr229, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(230, (unsigned)isr230, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(231, (unsigned)isr231, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(232, (unsigned)isr232, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(233, (unsigned)isr233, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(234, (unsigned)isr234, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(235, (unsigned)isr235, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(236, (unsigned)isr236, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(237, (unsigned)isr237, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(238, (unsigned)isr238, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(239, (unsigned)isr239, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(240, (unsigned)isr240, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(241, (unsigned)isr241, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(242, (unsigned)isr242, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(243, (unsigned)isr243, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(244, (unsigned)isr244, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(245, (unsigned)isr245, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(246, (unsigned)isr246, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(247, (unsigned)isr247, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(248, (unsigned)isr248, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(249, (unsigned)isr249, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(250, (unsigned)isr250, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(251, (unsigned)isr251, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(252, (unsigned)isr252, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(253, (unsigned)isr253, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(254, (unsigned)isr254, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	idt_set_descriptor(255, (unsigned)isr255, CODE_DESC, IDT_DESC_TYPE_INT_32 | IDT_DESC_DPL_RING0 | IDT_DESC_PRESENT);
	
	// set IDT pointer
	idt.idtr.limit = (sizeof (struct idt_entry) * MAX_INTERRUPTS) - 1;
    idt.idtr.base = (uint32_t)&idt.entries;
	
	// set IDTR processor register
	__asm__ __volatile__ ("lidt %0" : : "m"(idt.idtr) : "memory");	
}