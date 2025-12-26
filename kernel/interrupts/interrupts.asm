extern mapPic
global idtLoad
idtLoad:
    mov eax, [esp+4]
    lidt [eax]
    call mapPic
    sti
    ret

extern interrupthandler
commonInterruptHandler:    
    pusha                           ; Pusheo registros de proposito general al stack

    xor eax, eax                    ; Guardo el data segment actual
    mov ax, ds
    push eax

    mov ax, 0x10                    ; kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp

    call interrupthandler

    add  esp, 4                      ; Paso de largo el stack pointer que pushie antes del call
    
    pop eax                          ; Reestablezco el segmento de datos
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa

    add esp, 8

    iret

;; Declaración de todos los interrupt handlers usando macro
%macro interruptHandlerNoCode 1
    global interruptHandlerNoCode%1
    interruptHandlerNoCode%1:
        push dword 0                ; Codigo de error 0
        push dword %1               ; Codigo de la interrupcion
        jmp commonInterruptHandler
%endmacro

%macro interruptHandlerCode 1
    global interruptHandlerCode%1
    interruptHandlerCode%1:
        ; El codigo de error lo da la cpu
        push dword %1               ; Codigo de la interrupcion
        jmp commonInterruptHandler
%endmacro

interruptHandlerNoCode 0
interruptHandlerNoCode 1
interruptHandlerNoCode 2
interruptHandlerNoCode 3
interruptHandlerNoCode 4
interruptHandlerNoCode 5
interruptHandlerNoCode 6
interruptHandlerNoCode 7
interruptHandlerCode 8
interruptHandlerNoCode 9
interruptHandlerCode 10
interruptHandlerCode 11
interruptHandlerCode 12
interruptHandlerCode 13
interruptHandlerCode 14
interruptHandlerNoCode 15
interruptHandlerNoCode 16
interruptHandlerCode 17
interruptHandlerNoCode 18
interruptHandlerNoCode 19
interruptHandlerNoCode 20
interruptHandlerNoCode 21
interruptHandlerNoCode 22
interruptHandlerNoCode 23
interruptHandlerNoCode 24
interruptHandlerNoCode 25
interruptHandlerNoCode 26
interruptHandlerNoCode 27
interruptHandlerNoCode 28
interruptHandlerNoCode 29
interruptHandlerNoCode 30
interruptHandlerNoCode 31
interruptHandlerNoCode 32
interruptHandlerNoCode 33
interruptHandlerNoCode 34
interruptHandlerNoCode 35
interruptHandlerNoCode 36
interruptHandlerNoCode 37
interruptHandlerNoCode 38
interruptHandlerNoCode 39
interruptHandlerNoCode 40
interruptHandlerNoCode 41
interruptHandlerNoCode 42
interruptHandlerNoCode 43
interruptHandlerNoCode 44
interruptHandlerNoCode 45
interruptHandlerNoCode 46
interruptHandlerNoCode 47
interruptHandlerNoCode 48
interruptHandlerNoCode 49
interruptHandlerNoCode 50
interruptHandlerNoCode 51
interruptHandlerNoCode 52
interruptHandlerNoCode 53
interruptHandlerNoCode 54
interruptHandlerNoCode 55
interruptHandlerNoCode 56
interruptHandlerNoCode 57
interruptHandlerNoCode 58
interruptHandlerNoCode 59
interruptHandlerNoCode 60
interruptHandlerNoCode 61
interruptHandlerNoCode 62
interruptHandlerNoCode 63
interruptHandlerNoCode 64
interruptHandlerNoCode 65
interruptHandlerNoCode 66
interruptHandlerNoCode 67
interruptHandlerNoCode 68
interruptHandlerNoCode 69
interruptHandlerNoCode 70
interruptHandlerNoCode 71
interruptHandlerNoCode 72
interruptHandlerNoCode 73
interruptHandlerNoCode 74
interruptHandlerNoCode 75
interruptHandlerNoCode 76
interruptHandlerNoCode 77
interruptHandlerNoCode 78
interruptHandlerNoCode 79
interruptHandlerNoCode 80
interruptHandlerNoCode 81
interruptHandlerNoCode 82
interruptHandlerNoCode 83
interruptHandlerNoCode 84
interruptHandlerNoCode 85
interruptHandlerNoCode 86
interruptHandlerNoCode 87
interruptHandlerNoCode 88
interruptHandlerNoCode 89
interruptHandlerNoCode 90
interruptHandlerNoCode 91
interruptHandlerNoCode 92
interruptHandlerNoCode 93
interruptHandlerNoCode 94
interruptHandlerNoCode 95
interruptHandlerNoCode 96
interruptHandlerNoCode 97
interruptHandlerNoCode 98
interruptHandlerNoCode 99
interruptHandlerNoCode 100
interruptHandlerNoCode 101
interruptHandlerNoCode 102
interruptHandlerNoCode 103
interruptHandlerNoCode 104
interruptHandlerNoCode 105
interruptHandlerNoCode 106
interruptHandlerNoCode 107
interruptHandlerNoCode 108
interruptHandlerNoCode 109
interruptHandlerNoCode 110
interruptHandlerNoCode 111
interruptHandlerNoCode 112
interruptHandlerNoCode 113
interruptHandlerNoCode 114
interruptHandlerNoCode 115
interruptHandlerNoCode 116
interruptHandlerNoCode 117
interruptHandlerNoCode 118
interruptHandlerNoCode 119
interruptHandlerNoCode 120
interruptHandlerNoCode 121
interruptHandlerNoCode 122
interruptHandlerNoCode 123
interruptHandlerNoCode 124
interruptHandlerNoCode 125
interruptHandlerNoCode 126
interruptHandlerNoCode 127
interruptHandlerNoCode 128
interruptHandlerNoCode 129
interruptHandlerNoCode 130
interruptHandlerNoCode 131
interruptHandlerNoCode 132
interruptHandlerNoCode 133
interruptHandlerNoCode 134
interruptHandlerNoCode 135
interruptHandlerNoCode 136
interruptHandlerNoCode 137
interruptHandlerNoCode 138
interruptHandlerNoCode 139
interruptHandlerNoCode 140
interruptHandlerNoCode 141
interruptHandlerNoCode 142
interruptHandlerNoCode 143
interruptHandlerNoCode 144
interruptHandlerNoCode 145
interruptHandlerNoCode 146
interruptHandlerNoCode 147
interruptHandlerNoCode 148
interruptHandlerNoCode 149
interruptHandlerNoCode 150
interruptHandlerNoCode 151
interruptHandlerNoCode 152
interruptHandlerNoCode 153
interruptHandlerNoCode 154
interruptHandlerNoCode 155
interruptHandlerNoCode 156
interruptHandlerNoCode 157
interruptHandlerNoCode 158
interruptHandlerNoCode 159
interruptHandlerNoCode 160
interruptHandlerNoCode 161
interruptHandlerNoCode 162
interruptHandlerNoCode 163
interruptHandlerNoCode 164
interruptHandlerNoCode 165
interruptHandlerNoCode 166
interruptHandlerNoCode 167
interruptHandlerNoCode 168
interruptHandlerNoCode 169
interruptHandlerNoCode 170
interruptHandlerNoCode 171
interruptHandlerNoCode 172
interruptHandlerNoCode 173
interruptHandlerNoCode 174
interruptHandlerNoCode 175
interruptHandlerNoCode 176
interruptHandlerNoCode 177
interruptHandlerNoCode 178
interruptHandlerNoCode 179
interruptHandlerNoCode 180
interruptHandlerNoCode 181
interruptHandlerNoCode 182
interruptHandlerNoCode 183
interruptHandlerNoCode 184
interruptHandlerNoCode 185
interruptHandlerNoCode 186
interruptHandlerNoCode 187
interruptHandlerNoCode 188
interruptHandlerNoCode 189
interruptHandlerNoCode 190
interruptHandlerNoCode 191
interruptHandlerNoCode 192
interruptHandlerNoCode 193
interruptHandlerNoCode 194
interruptHandlerNoCode 195
interruptHandlerNoCode 196
interruptHandlerNoCode 197
interruptHandlerNoCode 198
interruptHandlerNoCode 199
interruptHandlerNoCode 200
interruptHandlerNoCode 201
interruptHandlerNoCode 202
interruptHandlerNoCode 203
interruptHandlerNoCode 204
interruptHandlerNoCode 205
interruptHandlerNoCode 206
interruptHandlerNoCode 207
interruptHandlerNoCode 208
interruptHandlerNoCode 209
interruptHandlerNoCode 210
interruptHandlerNoCode 211
interruptHandlerNoCode 212
interruptHandlerNoCode 213
interruptHandlerNoCode 214
interruptHandlerNoCode 215
interruptHandlerNoCode 216
interruptHandlerNoCode 217
interruptHandlerNoCode 218
interruptHandlerNoCode 219
interruptHandlerNoCode 220
interruptHandlerNoCode 221
interruptHandlerNoCode 222
interruptHandlerNoCode 223
interruptHandlerNoCode 224
interruptHandlerNoCode 225
interruptHandlerNoCode 226
interruptHandlerNoCode 227
interruptHandlerNoCode 228
interruptHandlerNoCode 229
interruptHandlerNoCode 230
interruptHandlerNoCode 231
interruptHandlerNoCode 232
interruptHandlerNoCode 233
interruptHandlerNoCode 234
interruptHandlerNoCode 235
interruptHandlerNoCode 236
interruptHandlerNoCode 237
interruptHandlerNoCode 238
interruptHandlerNoCode 239
interruptHandlerNoCode 240
interruptHandlerNoCode 241
interruptHandlerNoCode 242
interruptHandlerNoCode 243
interruptHandlerNoCode 244
interruptHandlerNoCode 245
interruptHandlerNoCode 246
interruptHandlerNoCode 247
interruptHandlerNoCode 248
interruptHandlerNoCode 249
interruptHandlerNoCode 250
interruptHandlerNoCode 251
interruptHandlerNoCode 252
interruptHandlerNoCode 253
interruptHandlerNoCode 254
interruptHandlerNoCode 255