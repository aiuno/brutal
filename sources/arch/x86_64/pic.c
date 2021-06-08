#include "arch/x86_64/pic.h"

#include "arch/x86_64/asm.h"

void pic_initialize(void)
{
    /* Cascade initialization */
    asm_out8(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    PIC_WAIT();
    asm_out8(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    PIC_WAIT();

    /* Remap */
    asm_out8(PIC1_DATA, PIC1_OFFSET);
    PIC_WAIT();
    asm_out8(PIC2_DATA, PIC2_OFFSET);
    PIC_WAIT();

    /* Cascade identity with slave PIC at IRQ2 */
    asm_out8(PIC1_DATA, 0x04);
    PIC_WAIT();
    asm_out8(PIC2_DATA, 0x02);
    PIC_WAIT();

    /* Request 8086 mode on each PIC */
    asm_out8(PIC1_DATA, 0x01);
    PIC_WAIT();
    asm_out8(PIC2_DATA, 0x01);
    PIC_WAIT();

    asm_out8(PIC1_DATA, 0x00);
    PIC_WAIT();
    asm_out8(PIC2_DATA, 0x00);
    PIC_WAIT();
}

void pic_disable(void)
{
    asm_out8(PIC2_DATA, 0xff);
    asm_out8(PIC1_DATA, 0xff);
}
