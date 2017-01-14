;************************************************************************************************
;	Hardware Abstraction Layer x86
;
;	HAL Entry Stub
;	The bootloader will call start which initiates the HAL initilization process.
;
;	stub_entry.c
;	Date: January 6th 2017
;
;************************************************************************************************
bits 32

;************************************************************************************************
; 	Entry Function (called from the bootloader)
;************************************************************************************************
global start ; must be visible to the linker (link.ld asks the linker to put 'start' at the start)

start:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	pop edx
	
	mov ss, ax
	mov	esp, 0x80000
	
	push edx
	jmp 0x08:start2

start2:	
	extern hal_initialize
	call hal_initialize
	cli
	hlt

;************************************************************************************************
; 	Exception Handler
;************************************************************************************************
global isr_except0
global isr_except1
global isr_except2
global isr_except3
global isr_except4
global isr_except5
global isr_except6
global isr_except7
global isr_except8
global isr_except9
global isr_except10
global isr_except11
global isr_except12
global isr_except13
global isr_except14
global isr_except15
global isr_except16
global isr_except17
global isr_except18
global isr_except19
global isr_except20
global isr_except21
global isr_except22
global isr_except23
global isr_except24
global isr_except25
global isr_except26
global isr_except27
global isr_except28
global isr_except29
global isr_except30
global isr_except31

isr_except0:
    cli
    push  0
    push  0
    jmp isr_except_stub

isr_except1:
    cli
    push  0
    push  1
    jmp isr_except_stub

isr_except2:
    cli
    push  0
    push  2
    jmp isr_except_stub

isr_except3:
    cli
    push  0
    push  3
    jmp isr_except_stub

isr_except4:
    cli
    push  0
    push  4
    jmp isr_except_stub

isr_except5:
    cli
    push  0
    push  5
    jmp isr_except_stub

isr_except6:
    cli
    push  0
    push  6
    jmp isr_except_stub

isr_except7:
    cli
    push  0
    push  7
    jmp isr_except_stub

isr_except8:
    cli
    push  8
    jmp isr_except_stub

isr_except9:
    cli
    push  0
    push  9
    jmp isr_except_stub

isr_except10:
    cli
    push  10
    jmp isr_except_stub

isr_except11:
    cli
    push  11
    jmp isr_except_stub

isr_except12:
    cli
    push  12
    jmp isr_except_stub

isr_except13:
    cli
    push  13
    jmp isr_except_stub

isr_except14:
    cli
    push  14
    jmp isr_except_stub

isr_except15:
    cli
    push  0
    push  15
    jmp isr_except_stub

isr_except16:
    cli
    push  0
    push  16
    jmp isr_except_stub

isr_except17:
    cli
    push  0
    push  17
    jmp isr_except_stub

isr_except18:
    cli
    push  0
    push  18
    jmp isr_except_stub

isr_except19:
    cli
    push  0
    push  19
    jmp isr_except_stub

isr_except20:
    cli
    push  0
    push  20
    jmp isr_except_stub

isr_except21:
    cli
    push  0
    push  21
    jmp isr_except_stub

isr_except22:
    cli
    push  0
    push  22
    jmp isr_except_stub

isr_except23:
    cli
    push  0
    push  23
    jmp isr_except_stub

isr_except24:
    cli
    push  0
    push  24
    jmp isr_except_stub

isr_except25:
    cli
    push  0
    push  25
    jmp isr_except_stub

isr_except26:
    cli
    push  0
    push  26
    jmp isr_except_stub

isr_except27:
    cli
    push  0
    push  27
    jmp isr_except_stub

isr_except28:
    cli
    push  0
    push  28
    jmp isr_except_stub

isr_except29:
    cli
    push  0
    push  29
    jmp isr_except_stub

isr_except30:
    cli
    push  0
    push  30
    jmp isr_except_stub

isr_except31:
    cli
    push  0
    push  31
    jmp isr_except_stub

extern _exception_handler
isr_except_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, _exception_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret	
	
;************************************************************************************************
; 	Hardware Interrupts Handler
;************************************************************************************************
global isr_hwd_irq0
global isr_hwd_irq1
global isr_hwd_irq2
global isr_hwd_irq3
global isr_hwd_irq4
global isr_hwd_irq5
global isr_hwd_irq6
global isr_hwd_irq7
global isr_hwd_irq8
global isr_hwd_irq9
global isr_hwd_irq10
global isr_hwd_irq11
global isr_hwd_irq12
global isr_hwd_irq13
global isr_hwd_irq14
global isr_hwd_irq15

isr_hwd_irq0:
	cli
	push  0
	push  32
	jmp isr_hwd_irq_stub
	
isr_hwd_irq1:
	cli
	push  0
	push  33
	jmp isr_hwd_irq_stub
	
isr_hwd_irq2:
	cli
	push  0
	push  34
	jmp isr_hwd_irq_stub
	
isr_hwd_irq3:
	cli
	push  0
	push  35
	jmp isr_hwd_irq_stub
	
isr_hwd_irq4:
	cli
	push  0
	push  36
	jmp isr_hwd_irq_stub
	
isr_hwd_irq5:
	cli
	push  0
	push  37
	jmp isr_hwd_irq_stub
	
isr_hwd_irq6:
	cli
	push  0
	push  38
	jmp isr_hwd_irq_stub
	
isr_hwd_irq7:
	cli
	push  0
	push  39
	jmp isr_hwd_irq_stub
	
isr_hwd_irq8:
	cli
	push  0
	push  40
	jmp isr_hwd_irq_stub
	
isr_hwd_irq9:
	cli
	push  0
	push  41
	jmp isr_hwd_irq_stub
	
isr_hwd_irq10:
	cli
	push  0
	push  42
	jmp isr_hwd_irq_stub
	
isr_hwd_irq11:
	cli
	push  0
	push  43
	jmp isr_hwd_irq_stub
	
isr_hwd_irq12:
	cli
	push  0
	push  44
	jmp isr_hwd_irq_stub
	
isr_hwd_irq13:
	cli
	push  0
	push  45
	jmp isr_hwd_irq_stub
	
isr_hwd_irq14:
	cli
	push  0
	push  46
	jmp isr_hwd_irq_stub
	
isr_hwd_irq15:
	cli
	push  0
	push  47
	jmp isr_hwd_irq_stub
	
extern _hwd_irq_handler
isr_hwd_irq_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, _hwd_irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret	
	
;************************************************************************************************
; 	Other Interrupts Handler
;************************************************************************************************
global isr48
global isr49
global isr50
global isr51
global isr52
global isr53
global isr54
global isr55
global isr56
global isr57
global isr58
global isr59
global isr60
global isr61
global isr62
global isr63
global isr64
global isr65
global isr66
global isr67
global isr68
global isr69
global isr70
global isr71
global isr72
global isr73
global isr74
global isr75
global isr76
global isr77
global isr78
global isr79
global isr80
global isr81
global isr82
global isr83
global isr84
global isr85
global isr86
global isr87
global isr88
global isr89
global isr90
global isr91
global isr92
global isr93
global isr94
global isr95
global isr96
global isr97
global isr98
global isr99
global isr100
global isr101
global isr102
global isr103
global isr104
global isr105
global isr106
global isr107
global isr108
global isr109
global isr110
global isr111
global isr112
global isr113
global isr114
global isr115
global isr116
global isr117
global isr118
global isr119
global isr120
global isr121
global isr122
global isr123
global isr124
global isr125
global isr126
global isr127
global isr128
global isr129
global isr130
global isr131
global isr132
global isr133
global isr134
global isr135
global isr136
global isr137
global isr138
global isr139
global isr140
global isr141
global isr142
global isr143
global isr144
global isr145
global isr146
global isr147
global isr148
global isr149
global isr150
global isr151
global isr152
global isr153
global isr154
global isr155
global isr156
global isr157
global isr158
global isr159
global isr160
global isr161
global isr162
global isr163
global isr164
global isr165
global isr166
global isr167
global isr168
global isr169
global isr170
global isr171
global isr172
global isr173
global isr174
global isr175
global isr176
global isr177
global isr178
global isr179
global isr180
global isr181
global isr182
global isr183
global isr184
global isr185
global isr186
global isr187
global isr188
global isr189
global isr190
global isr191
global isr192
global isr193
global isr194
global isr195
global isr196
global isr197
global isr198
global isr199
global isr200
global isr201
global isr202
global isr203
global isr204
global isr205
global isr206
global isr207
global isr208
global isr209
global isr210
global isr211
global isr212
global isr213
global isr214
global isr215
global isr216
global isr217
global isr218
global isr219
global isr220
global isr221
global isr222
global isr223
global isr224
global isr225
global isr226
global isr227
global isr228
global isr229
global isr230
global isr231
global isr232
global isr233
global isr234
global isr235
global isr236
global isr237
global isr238
global isr239
global isr240
global isr241
global isr242
global isr243
global isr244
global isr245
global isr246
global isr247
global isr248
global isr249
global isr250
global isr251
global isr252
global isr253
global isr254
global isr255

isr48:
	cli
	push  0
	push  48
	jmp isr_common_stub
	
isr49:
	cli
	push  0
	push  49
	jmp isr_common_stub
	
isr50:
	cli
	push  0
	push  50
	jmp isr_common_stub
	
isr51:
	cli
	push  0
	push  51
	jmp isr_common_stub
	
isr52:
	cli
	push  0
	push  52
	jmp isr_common_stub
	
isr53:
	cli
	push  0
	push  53
	jmp isr_common_stub
	
isr54:
	cli
	push  0
	push  54
	jmp isr_common_stub
	
isr55:
	cli
	push  0
	push  55
	jmp isr_common_stub
	
isr56:
	cli
	push  0
	push  56
	jmp isr_common_stub
	
isr57:
	cli
	push  0
	push  57
	jmp isr_common_stub
	
isr58:
	cli
	push  0
	push  58
	jmp isr_common_stub
	
isr59:
	cli
	push  0
	push  59
	jmp isr_common_stub
	
isr60:
	cli
	push  0
	push  60
	jmp isr_common_stub
	
isr61:
	cli
	push  0
	push  61
	jmp isr_common_stub
	
isr62:
	cli
	push  0
	push  62
	jmp isr_common_stub
	
isr63:
	cli
	push  0
	push  63
	jmp isr_common_stub
	
isr64:
	cli
	push  0
	push  64
	jmp isr_common_stub
	
isr65:
	cli
	push  0
	push  65
	jmp isr_common_stub
	
isr66:
	cli
	push  0
	push  66
	jmp isr_common_stub
	
isr67:
	cli
	push  0
	push  67
	jmp isr_common_stub
	
isr68:
	cli
	push  0
	push  68
	jmp isr_common_stub
	
isr69:
	cli
	push  0
	push  69
	jmp isr_common_stub
	
isr70:
	cli
	push  0
	push  70
	jmp isr_common_stub
	
isr71:
	cli
	push  0
	push  71
	jmp isr_common_stub
	
isr72:
	cli
	push  0
	push  72
	jmp isr_common_stub
	
isr73:
	cli
	push  0
	push  73
	jmp isr_common_stub
	
isr74:
	cli
	push  0
	push  74
	jmp isr_common_stub
	
isr75:
	cli
	push  0
	push  75
	jmp isr_common_stub
	
isr76:
	cli
	push  0
	push  76
	jmp isr_common_stub
	
isr77:
	cli
	push  0
	push  77
	jmp isr_common_stub
	
isr78:
	cli
	push  0
	push  78
	jmp isr_common_stub
	
isr79:
	cli
	push  0
	push  79
	jmp isr_common_stub
	
isr80:
	cli
	push  0
	push  80
	jmp isr_common_stub
	
isr81:
	cli
	push  0
	push  81
	jmp isr_common_stub
	
isr82:
	cli
	push  0
	push  82
	jmp isr_common_stub
	
isr83:
	cli
	push  0
	push  83
	jmp isr_common_stub
	
isr84:
	cli
	push  0
	push  84
	jmp isr_common_stub
	
isr85:
	cli
	push  0
	push  85
	jmp isr_common_stub
	
isr86:
	cli
	push  0
	push  86
	jmp isr_common_stub
	
isr87:
	cli
	push  0
	push  87
	jmp isr_common_stub
	
isr88:
	cli
	push  0
	push  88
	jmp isr_common_stub
	
isr89:
	cli
	push  0
	push  89
	jmp isr_common_stub
	
isr90:
	cli
	push  0
	push  90
	jmp isr_common_stub
	
isr91:
	cli
	push  0
	push  91
	jmp isr_common_stub
	
isr92:
	cli
	push  0
	push  92
	jmp isr_common_stub
	
isr93:
	cli
	push  0
	push  93
	jmp isr_common_stub
	
isr94:
	cli
	push  0
	push  94
	jmp isr_common_stub
	
isr95:
	cli
	push  0
	push  95
	jmp isr_common_stub
	
isr96:
	cli
	push  0
	push  96
	jmp isr_common_stub
	
isr97:
	cli
	push  0
	push  97
	jmp isr_common_stub
	
isr98:
	cli
	push  0
	push  98
	jmp isr_common_stub
	
isr99:
	cli
	push  0
	push  99
	jmp isr_common_stub
	
isr100:
	cli
	push  0
	push  100
	jmp isr_common_stub
	
isr101:
	cli
	push  0
	push  101
	jmp isr_common_stub
	
isr102:
	cli
	push  0
	push  102
	jmp isr_common_stub
	
isr103:
	cli
	push  0
	push  103
	jmp isr_common_stub
	
isr104:
	cli
	push  0
	push  104
	jmp isr_common_stub
	
isr105:
	cli
	push  0
	push  105
	jmp isr_common_stub
	
isr106:
	cli
	push  0
	push  106
	jmp isr_common_stub
	
isr107:
	cli
	push  0
	push  107
	jmp isr_common_stub
	
isr108:
	cli
	push  0
	push  108
	jmp isr_common_stub
	
isr109:
	cli
	push  0
	push  109
	jmp isr_common_stub
	
isr110:
	cli
	push  0
	push  110
	jmp isr_common_stub
	
isr111:
	cli
	push  0
	push  111
	jmp isr_common_stub
	
isr112:
	cli
	push  0
	push  112
	jmp isr_common_stub
	
isr113:
	cli
	push  0
	push  113
	jmp isr_common_stub
	
isr114:
	cli
	push  0
	push  114
	jmp isr_common_stub
	
isr115:
	cli
	push  0
	push  115
	jmp isr_common_stub
	
isr116:
	cli
	push  0
	push  116
	jmp isr_common_stub
	
isr117:
	cli
	push  0
	push  117
	jmp isr_common_stub
	
isr118:
	cli
	push  0
	push  118
	jmp isr_common_stub
	
isr119:
	cli
	push  0
	push  119
	jmp isr_common_stub
	
isr120:
	cli
	push  0
	push  120
	jmp isr_common_stub
	
isr121:
	cli
	push  0
	push  121
	jmp isr_common_stub
	
isr122:
	cli
	push  0
	push  122
	jmp isr_common_stub
	
isr123:
	cli
	push  0
	push  123
	jmp isr_common_stub
	
isr124:
	cli
	push  0
	push  124
	jmp isr_common_stub
	
isr125:
	cli
	push  0
	push  125
	jmp isr_common_stub
	
isr126:
	cli
	push  0
	push  126
	jmp isr_common_stub
	
isr127:
	cli
	push  0
	push  127
	jmp isr_common_stub
	
isr128:
	cli
	push  0
	push  128
	jmp isr_common_stub
	
isr129:
	cli
	push  0
	push  129
	jmp isr_common_stub
	
isr130:
	cli
	push  0
	push  130
	jmp isr_common_stub
	
isr131:
	cli
	push  0
	push  131
	jmp isr_common_stub
	
isr132:
	cli
	push  0
	push  132
	jmp isr_common_stub
	
isr133:
	cli
	push  0
	push  133
	jmp isr_common_stub
	
isr134:
	cli
	push  0
	push  134
	jmp isr_common_stub
	
isr135:
	cli
	push  0
	push  135
	jmp isr_common_stub
	
isr136:
	cli
	push  0
	push  136
	jmp isr_common_stub
	
isr137:
	cli
	push  0
	push  137
	jmp isr_common_stub
	
isr138:
	cli
	push  0
	push  138
	jmp isr_common_stub
	
isr139:
	cli
	push  0
	push  139
	jmp isr_common_stub
	
isr140:
	cli
	push  0
	push  140
	jmp isr_common_stub
	
isr141:
	cli
	push  0
	push  141
	jmp isr_common_stub
	
isr142:
	cli
	push  0
	push  142
	jmp isr_common_stub
	
isr143:
	cli
	push  0
	push  143
	jmp isr_common_stub
	
isr144:
	cli
	push  0
	push  144
	jmp isr_common_stub
	
isr145:
	cli
	push  0
	push  145
	jmp isr_common_stub
	
isr146:
	cli
	push  0
	push  146
	jmp isr_common_stub
	
isr147:
	cli
	push  0
	push  147
	jmp isr_common_stub
	
isr148:
	cli
	push  0
	push  148
	jmp isr_common_stub
	
isr149:
	cli
	push  0
	push  149
	jmp isr_common_stub
	
isr150:
	cli
	push  0
	push  150
	jmp isr_common_stub
isr151:
	cli
	push  0
	push  151
	jmp isr_common_stub
	
isr152:
	cli
	push  0
	push  152
	jmp isr_common_stub
	
isr153:
	cli
	push  0
	push  153
	jmp isr_common_stub
	
isr154:
	cli
	push  0
	push  154
	jmp isr_common_stub
	
isr155:
	cli
	push  0
	push  155
	jmp isr_common_stub
	
isr156:
	cli
	push  0
	push  156
	jmp isr_common_stub
	
isr157:
	cli
	push  0
	push  157
	jmp isr_common_stub
	
isr158:
	cli
	push  0
	push  158
	jmp isr_common_stub
isr159:
	cli
	push  0
	push  159
	jmp isr_common_stub
	
isr160:
	cli
	push  0
	push  160
	jmp isr_common_stub
	
isr161:
	cli
	push  0
	push  161
	jmp isr_common_stub
	
isr162:
	cli
	push  0
	push  162
	jmp isr_common_stub
	
isr163:
	cli
	push  0
	push  163
	jmp isr_common_stub
	
isr164:
	cli
	push  0
	push  164
	jmp isr_common_stub
	
isr165:
	cli
	push  0
	push  165
	jmp isr_common_stub
	
isr166:
	cli
	push  0
	push  166
	jmp isr_common_stub
	
isr167:
	cli
	push  0
	push  167
	jmp isr_common_stub
	
isr168:
	cli
	push  0
	push  168
	jmp isr_common_stub
	
isr169:
	cli
	push  0
	push  169
	jmp isr_common_stub
	
isr170:
	cli
	push  0
	push  170
	jmp isr_common_stub
	
isr171:
	cli
	push  0
	push  171
	jmp isr_common_stub
	
isr172:
	cli
	push  0
	push  172
	jmp isr_common_stub
	
isr173:
	cli
	push  0
	push  173
	jmp isr_common_stub
	
isr174:
	cli
	push  0
	push  174
	jmp isr_common_stub
	
isr175:
	cli
	push  0
	push  175
	jmp isr_common_stub
	
isr176:
	cli
	push  0
	push  176
	jmp isr_common_stub
	
isr177:
	cli
	push  0
	push  177
	jmp isr_common_stub
	
isr178:
	cli
	push  0
	push  178
	jmp isr_common_stub
	
isr179:
	cli
	push  0
	push  179
	jmp isr_common_stub
	
isr180:
	cli
	push  0
	push  180
	jmp isr_common_stub
isr181:
	cli
	push  0
	push  181
	jmp isr_common_stub
	
isr182:
	cli
	push  0
	push  182
	jmp isr_common_stub
	
isr183:
	cli
	push  0
	push  183
	jmp isr_common_stub
	
isr184:
	cli
	push  0
	push  184
	jmp isr_common_stub
	
isr185:
	cli
	push  0
	push  185
	jmp isr_common_stub
	
isr186:
	cli
	push  0
	push  186
	jmp isr_common_stub
	
isr187:
	cli
	push  0
	push  187
	jmp isr_common_stub
	
isr188:
	cli
	push  0
	push  188
	jmp isr_common_stub
	
isr189:
	cli
	push  0
	push  189
	jmp isr_common_stub
	
isr190:
	cli
	push  0
	push  190
	jmp isr_common_stub
	
isr191:
	cli
	push  0
	push  191
	jmp isr_common_stub
	
isr192:
	cli
	push  0
	push  192
	jmp isr_common_stub
	
isr193:
	cli
	push  0
	push  193
	jmp isr_common_stub
	
isr194:
	cli
	push  0
	push  194
	jmp isr_common_stub
	
isr195:
	cli
	push  0
	push  195
	jmp isr_common_stub
	
isr196:
	cli
	push  0
	push  196
	jmp isr_common_stub
	
isr197:
	cli
	push  0
	push  197
	jmp isr_common_stub
	
isr198:
	cli
	push  0
	push  198
	jmp isr_common_stub
	
isr199:
	cli
	push  0
	push  199
	jmp isr_common_stub
	
isr200:
	cli
	push  0
	push  200
	jmp isr_common_stub
	
isr201:
	cli
	push  0
	push  201
	jmp isr_common_stub
	
isr202:
	cli
	push  0
	push  202
	jmp isr_common_stub
	
isr203:
	cli
	push  0
	push  203
	jmp isr_common_stub
	
isr204:
	cli
	push  0
	push  204
	jmp isr_common_stub
	
isr205:
	cli
	push  0
	push  205
	jmp isr_common_stub
	
isr206:
	cli
	push  0
	push  206
	jmp isr_common_stub
	
isr207:
	cli
	push  0
	push  207
	jmp isr_common_stub
	
isr208:
	cli
	push  0
	push  208
	jmp isr_common_stub
	
isr209:
	cli
	push  0
	push  209
	jmp isr_common_stub
	
isr210:
	cli
	push  0
	push  210
	jmp isr_common_stub
	
isr211:
	cli
	push  0
	push  211
	jmp isr_common_stub
	
isr212:
	cli
	push  0
	push  212
	jmp isr_common_stub
	
isr213:
	cli
	push  0
	push  213
	jmp isr_common_stub
	
isr214:
	cli
	push  0
	push  214
	jmp isr_common_stub
	
isr215:
	cli
	push  0
	push  215
	jmp isr_common_stub
	
isr216:
	cli
	push  0
	push  216
	jmp isr_common_stub
	
isr217:
	cli
	push  0
	push  217
	jmp isr_common_stub
	
isr218:
	cli
	push  0
	push  218
	jmp isr_common_stub
	
isr219:
	cli
	push  0
	push  219
	jmp isr_common_stub
	
isr220:
	cli
	push  0
	push  220
	jmp isr_common_stub
	
isr221:
	cli
	push  0
	push  221
	jmp isr_common_stub
	
isr222:
	cli
	push  0
	push  222
	jmp isr_common_stub
	
isr223:
	cli
	push  0
	push  223
	jmp isr_common_stub
	
isr224:
	cli
	push  0
	push  224
	jmp isr_common_stub
	
isr225:
	cli
	push  0
	push  225
	jmp isr_common_stub
	
isr226:
	cli
	push  0
	push  226
	jmp isr_common_stub
	
isr227:
	cli
	push  0
	push  227
	jmp isr_common_stub
	
isr228:
	cli
	push  0
	push  228
	jmp isr_common_stub
	
isr229:
	cli
	push  0
	push  229
	jmp isr_common_stub
	
isr230:
	cli
	push  0
	push  230
	jmp isr_common_stub
	
isr231:
	cli
	push  0
	push  231
	jmp isr_common_stub
isr232:
	cli
	push  0
	push  232
	jmp isr_common_stub
	
isr233:
	cli
	push  0
	push  233
	jmp isr_common_stub
isr234:
	cli
	push  0
	push  234
	jmp isr_common_stub
isr235:
	cli
	push  0
	push  235
	jmp isr_common_stub
	
isr236:
	cli
	push  0
	push  236
	jmp isr_common_stub
	
isr237:
	cli
	push  0
	push  237
	jmp isr_common_stub
	
isr238:
	cli
	push  0
	push  238
	jmp isr_common_stub
	
isr239:
	cli
	push  0
	push  239
	jmp isr_common_stub
	
isr240:
	cli
	push  0
	push  240
	jmp isr_common_stub
	
isr241:
	cli
	push  0
	push  241
	jmp isr_common_stub
isr242:
	cli
	push  0
	push  242
	jmp isr_common_stub
	
isr243:
	cli
	push  0
	push  243
	jmp isr_common_stub
	
isr244:
	cli
	push  0
	push  244
	jmp isr_common_stub
isr245:
	cli
	push  0
	push  245
	jmp isr_common_stub
	
isr246:
	cli
	push  0
	push  246
	jmp isr_common_stub
	
isr247:
	cli
	push  0
	push  247
	jmp isr_common_stub
	
isr248:
	cli
	push  0
	push  248
	jmp isr_common_stub
	
isr249:
	cli
	push  0
	push  249
	jmp isr_common_stub
	
isr250:
	cli
	push  0
	push  250
	jmp isr_common_stub
	
isr251:
	cli
	push  0
	push  251
	jmp isr_common_stub
	
isr252:
	cli
	push  0
	push  252
	jmp isr_common_stub
	
isr253:
	cli
	push  0
	push  253
	jmp isr_common_stub
	
isr254:
	cli
	push  0
	push  254
	jmp isr_common_stub
	
isr255:
	cli
	push  0
	push  255
	jmp isr_common_stub
	
extern isr_default_handler
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, isr_default_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret