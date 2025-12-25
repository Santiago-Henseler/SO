#include "idt.h"

static IDTEntry   idtEntry[IDT_ENTRIES];
static IDTPointer idt;

extern void idtLoad(IDTPointer* idt);

extern void interruptHandlerNoCode0();
extern void interruptHandlerNoCode1();
extern void interruptHandlerNoCode2();
extern void interruptHandlerNoCode3();
extern void interruptHandlerNoCode4();
extern void interruptHandlerNoCode5();
extern void interruptHandlerNoCode6();
extern void interruptHandlerNoCode7();
extern void interruptHandlerCode8();
extern void interruptHandlerNoCode9();
extern void interruptHandlerCode10();
extern void interruptHandlerCode11();
extern void interruptHandlerCode12();
extern void interruptHandlerCode13();
extern void interruptHandlerCode14();
extern void interruptHandlerNoCode15();
extern void interruptHandlerNoCode16();
extern void interruptHandlerCode17();
extern void interruptHandlerNoCode18();
extern void interruptHandlerNoCode19();
extern void interruptHandlerNoCode20();
extern void interruptHandlerNoCode21();
extern void interruptHandlerNoCode22();
extern void interruptHandlerNoCode23();
extern void interruptHandlerNoCode24();
extern void interruptHandlerNoCode25();
extern void interruptHandlerNoCode26();
extern void interruptHandlerNoCode27();
extern void interruptHandlerNoCode28();
extern void interruptHandlerNoCode29();
extern void interruptHandlerNoCode30();
extern void interruptHandlerNoCode31();


// setea una entrada en la IDT
void idtSetEntry(uint8 num, uint32 base, uint16 selector, uint8 flags) {
    idtEntry[num].offset_low  = base & 0xFFFF;
    idtEntry[num].selector    = selector;
    idtEntry[num].zero        = 0;
    idtEntry[num].type_attr   = flags;
    idtEntry[num].offset_high = (base >> 16) & 0xFFFF;
}

void initInterrupts(){
    idt.limit = sizeof(IDTEntry) * IDT_ENTRIES - 1;
    idt.base  = (uint32)&idtEntry;

    for (int i = 0; i < IDT_ENTRIES; i++) {
        idtEntry[i].offset_low  = 0;
        idtEntry[i].offset_high = 0;
        idtEntry[i].selector    = 0;
        idtEntry[i].zero        = 0;
        idtEntry[i].type_attr   = 0;
    }

    idtSetEntry(0,  (uint32)interruptHandlerNoCode0,  0x08, IDT_FLAGS);
    idtSetEntry(1,  (uint32)interruptHandlerNoCode1,  0x08, IDT_FLAGS);
    idtSetEntry(2,  (uint32)interruptHandlerNoCode2,  0x08, IDT_FLAGS);
    idtSetEntry(3,  (uint32)interruptHandlerNoCode3,  0x08, IDT_FLAGS);
    idtSetEntry(4,  (uint32)interruptHandlerNoCode4,  0x08, IDT_FLAGS);
    idtSetEntry(5,  (uint32)interruptHandlerNoCode5,  0x08, IDT_FLAGS);
    idtSetEntry(6,  (uint32)interruptHandlerNoCode6,  0x08, IDT_FLAGS);
    idtSetEntry(7,  (uint32)interruptHandlerNoCode7,  0x08, IDT_FLAGS);
    idtSetEntry(8,  (uint32)interruptHandlerCode8,  0x08, IDT_FLAGS);
    idtSetEntry(9,  (uint32)interruptHandlerNoCode9,  0x08, IDT_FLAGS);
    idtSetEntry(10, (uint32)interruptHandlerCode10, 0x08, IDT_FLAGS);
    idtSetEntry(11, (uint32)interruptHandlerCode11, 0x08, IDT_FLAGS);
    idtSetEntry(12, (uint32)interruptHandlerCode12, 0x08, IDT_FLAGS);
    idtSetEntry(13, (uint32)interruptHandlerCode13, 0x08, IDT_FLAGS);
    idtSetEntry(14, (uint32)interruptHandlerCode14, 0x08, IDT_FLAGS);
    idtSetEntry(15, (uint32)interruptHandlerNoCode15, 0x08, IDT_FLAGS);
    idtSetEntry(16, (uint32)interruptHandlerNoCode16, 0x08, IDT_FLAGS);
    idtSetEntry(17, (uint32)interruptHandlerCode17, 0x08, IDT_FLAGS);
    idtSetEntry(18, (uint32)interruptHandlerNoCode18, 0x08, IDT_FLAGS);
    idtSetEntry(19, (uint32)interruptHandlerNoCode19, 0x08, IDT_FLAGS);
    idtSetEntry(20, (uint32)interruptHandlerNoCode20, 0x08, IDT_FLAGS);
    idtSetEntry(21, (uint32)interruptHandlerNoCode21, 0x08, IDT_FLAGS);
    idtSetEntry(22, (uint32)interruptHandlerNoCode22, 0x08, IDT_FLAGS);
    idtSetEntry(23, (uint32)interruptHandlerNoCode23, 0x08, IDT_FLAGS);
    idtSetEntry(24, (uint32)interruptHandlerNoCode24, 0x08, IDT_FLAGS);
    idtSetEntry(25, (uint32)interruptHandlerNoCode25, 0x08, IDT_FLAGS);
    idtSetEntry(26, (uint32)interruptHandlerNoCode26, 0x08, IDT_FLAGS);
    idtSetEntry(27, (uint32)interruptHandlerNoCode27, 0x08, IDT_FLAGS);
    idtSetEntry(28, (uint32)interruptHandlerNoCode28, 0x08, IDT_FLAGS);
    idtSetEntry(29, (uint32)interruptHandlerNoCode29, 0x08, IDT_FLAGS);
    idtSetEntry(30, (uint32)interruptHandlerNoCode30, 0x08, IDT_FLAGS);
    idtSetEntry(31, (uint32)interruptHandlerNoCode31, 0x08, IDT_FLAGS);

    idtLoad(&idt);

    mapPic();
}