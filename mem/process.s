global copy_page_physical

copy_page_physical:
    push ebx
    pushf
    cli

    mov ebx, [esp + 12]         ; source address
    mov ecx, [esp + 16]         ; destination address

    ;; disable paging
    mov edx, cr0
    and edx, 0x7fffffff
    mov cr0, edx

    mov edx, 1024               ; copy whole page

.loop:
    mov eax, [ebx]
    mov [ecx], eax
    add ebx, 4
    add ecx, 4
    dec edx
    jnz .loop

    ;; enable paging
    mov edx, cr0
    or  edx, 0x80000000
    mov cr0, edx

    popf
    pop ebx
    ret
