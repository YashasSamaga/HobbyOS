/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	8259 PIC Microcontroller
//
//	pic.c
//	Provides an interface to work with the i8259 PIC
//
//	Date: January 7th 2017
//
/*************************************************************************************************/
#include <stdint.h>

#include <hal.h>

/*==============================================================================================*/
// Defines (Private)
/*==============================================================================================*/
#define PIC_MASTER_COMMAND_PORT		0x20
#define PIC_MASTER_DATA_PORT		0x21

#define PIC_SLAVE_COMMAND_PORT		0xA0
#define PIC_SLAVE_DATA_PORT			0xA1

// Initilization Control Word 1
#define PIC_ICW1_EXPECT_ICW4 0x01

#define PIC_ICW1_SINGLE_PIC 0x02
#define PIC_ICW1_CASCADED_PIC 0x00

#define PIC_ICW1_LEVEL_TRIG_MODE 0x08
#define PIC_ICW1_EDGE_TRIG_MODE 0x00

#define PIC_ICW1_INITILIZATION 0x10

// Initilization Control Word 3
// Master PIC accepts IRQ number as bit positions
#define PIC_ICW3_MASTER_IRQ0 0x01
#define PIC_ICW3_MASTER_IRQ1 0x02
#define PIC_ICW3_MASTER_IRQ2 0x04
#define PIC_ICW3_MASTER_IRQ3 0x08
#define PIC_ICW3_MASTER_IRQ4 0x10
#define PIC_ICW3_MASTER_IRQ5 0x20
#define PIC_ICW3_MASTER_IRQ6 0x40
#define PIC_ICW3_MASTER_IRQ7 0x80
// Slave PIC accepts IRQ number as a decimal
#define PIC_ICW3_SLAVE_IRQ0 0
#define PIC_ICW3_SLAVE_IRQ1 1
#define PIC_ICW3_SLAVE_IRQ2 2
#define PIC_ICW3_SLAVE_IRQ3 3
#define PIC_ICW3_SLAVE_IRQ4 4
#define PIC_ICW3_SLAVE_IRQ5 5
#define PIC_ICW3_SLAVE_IRQ6 6
#define PIC_ICW3_SLAVE_IRQ7 7

// Initilization Control Word 4
#define PIC_ICW4_MODE86 0x01
#define PIC_ICW4_MODE85 0x00
#define PIC_ICW4_AUTO_EOI 0x02
#define PIC_ICW4_BUFFERED_MASTER 0x04
#define PIC_ICW4_BUFFERED_SLAVE 0x00
#define PIC_ICW4_BUFFERED_MODE 0x08
#define PIC_ICW4_SPL_FULLY_NESTED 0x10

#define PIC_COMMAND_EOI 0x20
#define PIC_OCW_COMMAND_GET_IRR                0x0A
#define PIC_OCW_COMMAND_GET_ISR                0x0B 

/*==============================================================================================*/
// Implementation Macros (Private)
/*==============================================================================================*/
#define pic_master_send_command(x) outportb(PIC_MASTER_COMMAND_PORT,(x))
#define pic_slave_send_command(x)  outportb(PIC_SLAVE_COMMAND_PORT,(x))
#define pic_master_send_data(x) outportb(PIC_MASTER_DATA_PORT,(x))
#define pic_slave_send_data(x)  outportb(PIC_SLAVE_DATA_PORT,(x))
#define pic_master_read_data() inportb(PIC_MASTER_DATA_PORT)
#define pic_slave_read_data()  inportb(PIC_SLAVE_DATA_PORT)

/*==============================================================================================*/
// Implementation Data (Private)
/*==============================================================================================*/
static uint16_t pic_irq_masks;

/*==============================================================================================*/
// Interface Functions
/*==============================================================================================*/
/*************************************************************************************************
	<summary>pic_send_command_eoi</summary>
	<para>sends end-of-interrupt (EOI) signal to the PIC(s)</para>
	<param name="irq" type="unsigned int"></param>
*************************************************************************************************/
void pic_send_command_eoi(unsigned int irq)
{
	if(irq >= 8)
		pic_slave_send_command(PIC_COMMAND_EOI);
 
	pic_master_send_command(PIC_COMMAND_EOI);
}

/*************************************************************************************************
	<summary>pic_disable</summary>
	<para>disables hardware interrupts through PIC</para>
*************************************************************************************************/
void pic_disable_irq()
{
	pic_master_send_data(0xFF);
	pic_slave_send_data(0xFF);
}

/*************************************************************************************************
	<summary>pic_enable</summary>
	<para>disables hardware interrupts through PIC</para>
*************************************************************************************************/
void pic_enable_irq()
{
	pic_master_send_data((uint8_t)pic_irq_masks);
	pic_slave_send_data(((uint8_t)(pic_irq_masks >> 8)));
}

/*************************************************************************************************
	<summary>pic_set_irq_mask</summary>
	<para>masks an interrupt by setting the interrupt's flag in the PIC's Mask Register</para>
	<param name="irq" type="unsigned int">IRQ number which is to be masked (0-15)</param>
*************************************************************************************************/
void pic_set_irq_mask(unsigned int irq) 
{ 
	pic_irq_masks |= (1 << irq);
    if(irq < 8) 
		pic_master_send_data(pic_master_read_data() | (1 << irq));
	else 
		pic_slave_send_data(pic_slave_read_data() | (1 << (irq - 8)));      
}
 
/*************************************************************************************************
	<summary>pic_clear_irq_mask</summary>
	<para>unmasks an interrupt by clearning the interrupt's flag in the PIC's Mask Register</para>
	<param name="irq" type="unsigned int">IRQ number which is to be masked (0-15)</param>
*************************************************************************************************/
void pic_clear_irq_mask(unsigned int irq) 
{ 
	pic_irq_masks &= ~(1 << irq);
    if(irq < 8) 
		pic_master_send_data(pic_master_read_data() & ~(1 << irq));
	else 
		pic_slave_send_data(pic_slave_read_data() & ~(1 << (irq - 8)));         
}
 
/*************************************************************************************************
	<summary>pic_get_irr</summary>
	<para>returns contents of the interrupt request register (IRR) of the PIC(s)</para>
*************************************************************************************************/
uint16_t pic_get_irr()
{
    pic_master_send_command(PIC_OCW_COMMAND_GET_IRR);
    pic_slave_send_command(PIC_OCW_COMMAND_GET_IRR);
    return ((inportb(PIC_SLAVE_COMMAND_PORT) << 8) | inportb(PIC_MASTER_COMMAND_PORT));
}

/*************************************************************************************************
	<summary>pic_get_isr</summary>
	<para>returns contents of the in-service register (ISR) of the PIC(s)</para>
*************************************************************************************************/
uint16_t pic_get_isr()
{
    pic_master_send_command(PIC_OCW_COMMAND_GET_ISR);
    pic_slave_send_command(PIC_OCW_COMMAND_GET_ISR);
    return ((inportb(PIC_SLAVE_COMMAND_PORT) << 8) | inportb(PIC_MASTER_COMMAND_PORT));
}

/*************************************************************************************************
	<summary>pic_initialize</summary>
	<para>remaps the PIC with the given interrupt vectors</para>
	<param name="base_master" type="uint8_t">starting interrupt vector for the master PIC</param>
	<param name="base_slave" type="uint8_t">starting interrupt vector for the slave PIC</param>
*************************************************************************************************/
void pic_initialize(uint8_t base_master, uint8_t base_slave) 
{
	pic_master_send_command(PIC_ICW1_EXPECT_ICW4 | PIC_ICW1_CASCADED_PIC | PIC_ICW1_EDGE_TRIG_MODE | PIC_ICW1_INITILIZATION);
	io_wait();
	pic_slave_send_command(PIC_ICW1_EXPECT_ICW4 | PIC_ICW1_CASCADED_PIC | PIC_ICW1_EDGE_TRIG_MODE | PIC_ICW1_INITILIZATION);
	io_wait();
	pic_master_send_data(base_master);
	io_wait();
	pic_slave_send_data(base_slave);
	io_wait();

	pic_master_send_data(PIC_ICW3_MASTER_IRQ2);
	io_wait();
	pic_slave_send_data(PIC_ICW3_SLAVE_IRQ2);
	io_wait();

	pic_master_send_data (PIC_ICW4_MODE86);
	io_wait();
	pic_slave_send_data (PIC_ICW4_MODE86);
	io_wait();
	
	pic_irq_masks = pic_master_read_data() | (pic_slave_read_data() << 8);
} 