#include "page.h"

// TODO: deberia tener un directory por proceso

extern uint8 kernelEnd;
extern uint8 kernelStart;

pageDirectoryEntry * pageDirectory = PAGE_FLAG_NO_PRESENT;  

void initPageTable(){
    pageDirectory = ALIGN(getBlock(), 16);

    for(int i = 0; i < PAGE_DIR_SIZE; i++){
        pageDirectory[i] = PAGE_FLAG_NO_PRESENT; 
    }

    for (uint32 addr = &kernelStart; addr < &kernelEnd; addr += 0x1000) {
        mapPage((void*)addr, (void*)addr, PAGE_FLAG_KERNEL | PAGE_FLAG_GLOBAL | PAGE_FLAG_WRITE);
    }

    mapPage(MEM_VGA, MEM_VGA, PAGE_FLAG_KERNEL | PAGE_FLAG_WRITE | PAGE_FLAG_PRESENT);
}

pageTableEntry * newPageTable(){

    pageTableEntry * pageTable = (pageTableEntry *)ALIGN(getBlock(), 4096);

    for(int i = 0; i < PAGE_TABLE_SIZE; i++){
        pageTable[i] = PAGE_FLAG_NO_PRESENT; 
    }

    return pageTable;
}

void mapPage(void *pa, void *va, uint32 flags){

    uint32 pageDirPos = ((uint32)va & VA_TO_PD_MASK) >> 22;
    uint32 pageTablePos = ((uint32)va & VA_TO_PT_MASK) >> 12;

    if (!(pageDirectory[pageDirPos] & PAGE_FLAG_PRESENT)) {
        pageTableEntry *newP = newPageTable();
        pageDirectory[pageDirPos] = ((uint32)newP & PDE_TO_PT_MASK) | PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE;
    }

    pageTableEntry *pageTable = (pageTableEntry *)(pageDirectory[pageDirPos] & PDE_TO_PT_MASK);

    if (pageTable[pageTablePos] & PAGE_FLAG_PRESENT)
        return; // TODO: no existe tabla para esa pagina

    pageTable[pageTablePos] = ((uint32)pa & PA_TO_ADDR_MASK) | flags;
}