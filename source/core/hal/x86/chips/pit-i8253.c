/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	8253 Programmable Interval Timer
//
//	pit.c
//	Provides an interface to work with the i8253 PIT
//
//	Date: January 7th 2017
//
/*************************************************************************************************/
#include <stdint.h>

#include <hal.h>
#include <irq.h>

/*==============================================================================================*/
// Defines (Private)
/*==============================================================================================*/
#define	PIT_COUNTER0_DATA_PORT	0x40
#define	PIT_COUNTER1_DATA_PORT	0x41
#define	PIT_COUNTER2_DATA_PORT	0x42
#define	PIT_COMMAND_PORT		0x43

/*==============================================================================================*/
// Implementation Macros (Private)
/*==============================================================================================*/
#define pit_send_command(x) outportb(PIT_COMMAND_PORT,(x))

#define pic_send_data_counter0(x)  outportb(PIT_COUNTER0_DATA_PORT,(x))
#define pic_send_data_counter1(x)  outportb(PIT_COUNTER1_DATA_PORT,(x))
#define pic_send_data_counter2(x)  outportb(PIT_COUNTER2_DATA_PORT,(x))

#define pic_read_data_counter0(x)  inportb(PIT_COUNTER0_DATA_PORT)
#define pic_read_data_counter1(x)  inportb(PIT_COUNTER1_DATA_PORT)
#define pic_read_data_counter2(x)  inportb(PIT_COUNTER2_DATA_PORT)

/*==============================================================================================*/
// Implementation Data (Private)
/*==============================================================================================*/
uint64_t tick = 0;

int pit_irq_handler(struct IRQ_DETAILS *details)
{
	tick++;
	return 0;
}
/*************************************************************************************************
	<summary>pit_initialize</summary>
	<para>initilizes the PIT</para>
*************************************************************************************************/
void pit_initialize() 
{
	irq_install_handler(0, pit_irq_handler, 0);
} 