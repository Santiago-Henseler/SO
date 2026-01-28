global setPageDirectory
setPageDirectory:
    mov eax, [esp+4]
    mov cr3, eax
    ret

global startPagination
startPagination:
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    ret