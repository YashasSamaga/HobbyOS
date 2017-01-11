/*************************************************************************************************/
//	Hardware Abstraction Layer (HAL)
//	8259 PIC Microcontroller
//
//	pic.h
//	Provides an interface to work with the i8259 PIC
//
//	Date: January 7th 2017
//
/*************************************************************************************************/
#ifndef _PIC_H
#define _PIC_H

#include <stdint.h>

/*===============================================================================================*/
// Interface Function Prototypes
/*===============================================================================================*/

extern void pic_send_command_eoi(unsigned int irq);
extern void pic_disable();
extern void pic_set_irq_mask(unsigned int irq);
extern void pic_clear_irq_mask(unsigned int irq);
extern uint16_t pic_get_irr(void);
extern uint16_t pic_get_isr(void);
extern void pic_initialize(uint8_t base_master, uint8_t base_slave); 

#endif // _PIC_H
