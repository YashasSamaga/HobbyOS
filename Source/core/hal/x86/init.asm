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
	mov ss, ax
	mov	esp, 0x7FFFF
	jmp 0x08:start2
	
start2:
	extern _hal_initialize
	jmp _hal_initialize
	cli
	hlt

;************************************************************************************************
; 	Exception Handler
;************************************************************************************************
global _isr_except0
global _isr_except1
global _isr_except2
global _isr_except3
global _isr_except4
global _isr_except5
global _isr_except6
global _isr_except7
global _isr_except8
global _isr_except9
global _isr_except10
global _isr_except11
global _isr_except12
global _isr_except13
global _isr_except14
global _isr_except15
global _isr_except16
global _isr_except17
global _isr_except18
global _isr_except19
global _isr_except20
global _isr_except21
global _isr_except22
global _isr_except23
global _isr_except24
global _isr_except25
global _isr_except26
global _isr_except27
global _isr_except28
global _isr_except29
global _isr_except30
global _isr_except31

_isr_except0:
    cli
    push  0
    push  0
    jmp isr_except_stub

_isr_except1:
    cli
    push  0
    push  1
    jmp isr_except_stub

_isr_except2:
    cli
    push  0
    push  2
    jmp isr_except_stub

_isr_except3:
    cli
    push  0
    push  3
    jmp isr_except_stub

_isr_except4:
    cli
    push  0
    push  4
    jmp isr_except_stub

_isr_except5:
    cli
    push  0
    push  5
    jmp isr_except_stub

_isr_except6:
    cli
    push  0
    push  6
    jmp isr_except_stub

_isr_except7:
    cli
    push  0
    push  7
    jmp isr_except_stub

_isr_except8:
    cli
    push  8
    jmp isr_except_stub

_isr_except9:
    cli
    push  0
    push  9
    jmp isr_except_stub

_isr_except10:
    cli
    push  10
    jmp isr_except_stub

_isr_except11:
    cli
    push  11
    jmp isr_except_stub

_isr_except12:
    cli
    push  12
    jmp isr_except_stub

_isr_except13:
    cli
    push  13
    jmp isr_except_stub

_isr_except14:
    cli
    push  14
    jmp isr_except_stub

_isr_except15:
    cli
    push  0
    push  15
    jmp isr_except_stub

_isr_except16:
    cli
    push  0
    push  16
    jmp isr_except_stub

_isr_except17:
    cli
    push  0
    push  17
    jmp isr_except_stub

_isr_except18:
    cli
    push  0
    push  18
    jmp isr_except_stub

_isr_except19:
    cli
    push  0
    push  19
    jmp isr_except_stub

_isr_except20:
    cli
    push  0
    push  20
    jmp isr_except_stub

_isr_except21:
    cli
    push  0
    push  21
    jmp isr_except_stub

_isr_except22:
    cli
    push  0
    push  22
    jmp isr_except_stub

_isr_except23:
    cli
    push  0
    push  23
    jmp isr_except_stub

_isr_except24:
    cli
    push  0
    push  24
    jmp isr_except_stub

_isr_except25:
    cli
    push  0
    push  25
    jmp isr_except_stub

_isr_except26:
    cli
    push  0
    push  26
    jmp isr_except_stub

_isr_except27:
    cli
    push  0
    push  27
    jmp isr_except_stub

_isr_except28:
    cli
    push  0
    push  28
    jmp isr_except_stub

_isr_except29:
    cli
    push  0
    push  29
    jmp isr_except_stub

_isr_except30:
    cli
    push  0
    push  30
    jmp isr_except_stub

_isr_except31:
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
global _isr_hwd_irq0
global _isr_hwd_irq1
global _isr_hwd_irq2
global _isr_hwd_irq3
global _isr_hwd_irq4
global _isr_hwd_irq5
global _isr_hwd_irq6
global _isr_hwd_irq7
global _isr_hwd_irq8
global _isr_hwd_irq9
global _isr_hwd_irq10
global _isr_hwd_irq11
global _isr_hwd_irq12
global _isr_hwd_irq13
global _isr_hwd_irq14
global _isr_hwd_irq15

_isr_hwd_irq0:
	cli
	push  0
	push  32
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq1:
	cli
	push  0
	push  33
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq2:
	cli
	push  0
	push  34
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq3:
	cli
	push  0
	push  35
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq4:
	cli
	push  0
	push  36
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq5:
	cli
	push  0
	push  37
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq6:
	cli
	push  0
	push  38
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq7:
	cli
	push  0
	push  39
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq8:
	cli
	push  0
	push  40
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq9:
	cli
	push  0
	push  41
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq10:
	cli
	push  0
	push  42
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq11:
	cli
	push  0
	push  43
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq12:
	cli
	push  0
	push  44
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq13:
	cli
	push  0
	push  45
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq14:
	cli
	push  0
	push  46
	jmp isr_hwd_irq_stub
	
_isr_hwd_irq15:
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
global _isr48
global _isr49
global _isr50
global _isr51
global _isr52
global _isr53
global _isr54
global _isr55
global _isr56
global _isr57
global _isr58
global _isr59
global _isr60
global _isr61
global _isr62
global _isr63
global _isr64
global _isr65
global _isr66
global _isr67
global _isr68
global _isr69
global _isr70
global _isr71
global _isr72
global _isr73
global _isr74
global _isr75
global _isr76
global _isr77
global _isr78
global _isr79
global _isr80
global _isr81
global _isr82
global _isr83
global _isr84
global _isr85
global _isr86
global _isr87
global _isr88
global _isr89
global _isr90
global _isr91
global _isr92
global _isr93
global _isr94
global _isr95
global _isr96
global _isr97
global _isr98
global _isr99
global _isr100
global _isr101
global _isr102
global _isr103
global _isr104
global _isr105
global _isr106
global _isr107
global _isr108
global _isr109
global _isr110
global _isr111
global _isr112
global _isr113
global _isr114
global _isr115
global _isr116
global _isr117
global _isr118
global _isr119
global _isr120
global _isr121
global _isr122
global _isr123
global _isr124
global _isr125
global _isr126
global _isr127
global _isr128
global _isr129
global _isr130
global _isr131
global _isr132
global _isr133
global _isr134
global _isr135
global _isr136
global _isr137
global _isr138
global _isr139
global _isr140
global _isr141
global _isr142
global _isr143
global _isr144
global _isr145
global _isr146
global _isr147
global _isr148
global _isr149
global _isr150
global _isr151
global _isr152
global _isr153
global _isr154
global _isr155
global _isr156
global _isr157
global _isr158
global _isr159
global _isr160
global _isr161
global _isr162
global _isr163
global _isr164
global _isr165
global _isr166
global _isr167
global _isr168
global _isr169
global _isr170
global _isr171
global _isr172
global _isr173
global _isr174
global _isr175
global _isr176
global _isr177
global _isr178
global _isr179
global _isr180
global _isr181
global _isr182
global _isr183
global _isr184
global _isr185
global _isr186
global _isr187
global _isr188
global _isr189
global _isr190
global _isr191
global _isr192
global _isr193
global _isr194
global _isr195
global _isr196
global _isr197
global _isr198
global _isr199
global _isr200
global _isr201
global _isr202
global _isr203
global _isr204
global _isr205
global _isr206
global _isr207
global _isr208
global _isr209
global _isr210
global _isr211
global _isr212
global _isr213
global _isr214
global _isr215
global _isr216
global _isr217
global _isr218
global _isr219
global _isr220
global _isr221
global _isr222
global _isr223
global _isr224
global _isr225
global _isr226
global _isr227
global _isr228
global _isr229
global _isr230
global _isr231
global _isr232
global _isr233
global _isr234
global _isr235
global _isr236
global _isr237
global _isr238
global _isr239
global _isr240
global _isr241
global _isr242
global _isr243
global _isr244
global _isr245
global _isr246
global _isr247
global _isr248
global _isr249
global _isr250
global _isr251
global _isr252
global _isr253
global _isr254
global _isr255

_isr48:
	cli
	push  0
	push  48
	jmp isr_common_stub
	
_isr49:
	cli
	push  0
	push  49
	jmp isr_common_stub
	
_isr50:
	cli
	push  0
	push  50
	jmp isr_common_stub
	
_isr51:
	cli
	push  0
	push  51
	jmp isr_common_stub
	
_isr52:
	cli
	push  0
	push  52
	jmp isr_common_stub
	
_isr53:
	cli
	push  0
	push  53
	jmp isr_common_stub
	
_isr54:
	cli
	push  0
	push  54
	jmp isr_common_stub
	
_isr55:
	cli
	push  0
	push  55
	jmp isr_common_stub
	
_isr56:
	cli
	push  0
	push  56
	jmp isr_common_stub
	
_isr57:
	cli
	push  0
	push  57
	jmp isr_common_stub
	
_isr58:
	cli
	push  0
	push  58
	jmp isr_common_stub
	
_isr59:
	cli
	push  0
	push  59
	jmp isr_common_stub
	
_isr60:
	cli
	push  0
	push  60
	jmp isr_common_stub
	
_isr61:
	cli
	push  0
	push  61
	jmp isr_common_stub
	
_isr62:
	cli
	push  0
	push  62
	jmp isr_common_stub
	
_isr63:
	cli
	push  0
	push  63
	jmp isr_common_stub
	
_isr64:
	cli
	push  0
	push  64
	jmp isr_common_stub
	
_isr65:
	cli
	push  0
	push  65
	jmp isr_common_stub
	
_isr66:
	cli
	push  0
	push  66
	jmp isr_common_stub
	
_isr67:
	cli
	push  0
	push  67
	jmp isr_common_stub
	
_isr68:
	cli
	push  0
	push  68
	jmp isr_common_stub
	
_isr69:
	cli
	push  0
	push  69
	jmp isr_common_stub
	
_isr70:
	cli
	push  0
	push  70
	jmp isr_common_stub
	
_isr71:
	cli
	push  0
	push  71
	jmp isr_common_stub
	
_isr72:
	cli
	push  0
	push  72
	jmp isr_common_stub
	
_isr73:
	cli
	push  0
	push  73
	jmp isr_common_stub
	
_isr74:
	cli
	push  0
	push  74
	jmp isr_common_stub
	
_isr75:
	cli
	push  0
	push  75
	jmp isr_common_stub
	
_isr76:
	cli
	push  0
	push  76
	jmp isr_common_stub
	
_isr77:
	cli
	push  0
	push  77
	jmp isr_common_stub
	
_isr78:
	cli
	push  0
	push  78
	jmp isr_common_stub
	
_isr79:
	cli
	push  0
	push  79
	jmp isr_common_stub
	
_isr80:
	cli
	push  0
	push  80
	jmp isr_common_stub
	
_isr81:
	cli
	push  0
	push  81
	jmp isr_common_stub
	
_isr82:
	cli
	push  0
	push  82
	jmp isr_common_stub
	
_isr83:
	cli
	push  0
	push  83
	jmp isr_common_stub
	
_isr84:
	cli
	push  0
	push  84
	jmp isr_common_stub
	
_isr85:
	cli
	push  0
	push  85
	jmp isr_common_stub
	
_isr86:
	cli
	push  0
	push  86
	jmp isr_common_stub
	
_isr87:
	cli
	push  0
	push  87
	jmp isr_common_stub
	
_isr88:
	cli
	push  0
	push  88
	jmp isr_common_stub
	
_isr89:
	cli
	push  0
	push  89
	jmp isr_common_stub
	
_isr90:
	cli
	push  0
	push  90
	jmp isr_common_stub
	
_isr91:
	cli
	push  0
	push  91
	jmp isr_common_stub
	
_isr92:
	cli
	push  0
	push  92
	jmp isr_common_stub
	
_isr93:
	cli
	push  0
	push  93
	jmp isr_common_stub
	
_isr94:
	cli
	push  0
	push  94
	jmp isr_common_stub
	
_isr95:
	cli
	push  0
	push  95
	jmp isr_common_stub
	
_isr96:
	cli
	push  0
	push  96
	jmp isr_common_stub
	
_isr97:
	cli
	push  0
	push  97
	jmp isr_common_stub
	
_isr98:
	cli
	push  0
	push  98
	jmp isr_common_stub
	
_isr99:
	cli
	push  0
	push  99
	jmp isr_common_stub
	
_isr100:
	cli
	push  0
	push  100
	jmp isr_common_stub
	
_isr101:
	cli
	push  0
	push  101
	jmp isr_common_stub
	
_isr102:
	cli
	push  0
	push  102
	jmp isr_common_stub
	
_isr103:
	cli
	push  0
	push  103
	jmp isr_common_stub
	
_isr104:
	cli
	push  0
	push  104
	jmp isr_common_stub
	
_isr105:
	cli
	push  0
	push  105
	jmp isr_common_stub
	
_isr106:
	cli
	push  0
	push  106
	jmp isr_common_stub
	
_isr107:
	cli
	push  0
	push  107
	jmp isr_common_stub
	
_isr108:
	cli
	push  0
	push  108
	jmp isr_common_stub
	
_isr109:
	cli
	push  0
	push  109
	jmp isr_common_stub
	
_isr110:
	cli
	push  0
	push  110
	jmp isr_common_stub
	
_isr111:
	cli
	push  0
	push  111
	jmp isr_common_stub
	
_isr112:
	cli
	push  0
	push  112
	jmp isr_common_stub
	
_isr113:
	cli
	push  0
	push  113
	jmp isr_common_stub
	
_isr114:
	cli
	push  0
	push  114
	jmp isr_common_stub
	
_isr115:
	cli
	push  0
	push  115
	jmp isr_common_stub
	
_isr116:
	cli
	push  0
	push  116
	jmp isr_common_stub
	
_isr117:
	cli
	push  0
	push  117
	jmp isr_common_stub
	
_isr118:
	cli
	push  0
	push  118
	jmp isr_common_stub
	
_isr119:
	cli
	push  0
	push  119
	jmp isr_common_stub
	
_isr120:
	cli
	push  0
	push  120
	jmp isr_common_stub
	
_isr121:
	cli
	push  0
	push  121
	jmp isr_common_stub
	
_isr122:
	cli
	push  0
	push  122
	jmp isr_common_stub
	
_isr123:
	cli
	push  0
	push  123
	jmp isr_common_stub
	
_isr124:
	cli
	push  0
	push  124
	jmp isr_common_stub
	
_isr125:
	cli
	push  0
	push  125
	jmp isr_common_stub
	
_isr126:
	cli
	push  0
	push  126
	jmp isr_common_stub
	
_isr127:
	cli
	push  0
	push  127
	jmp isr_common_stub
	
_isr128:
	cli
	push  0
	push  128
	jmp isr_common_stub
	
_isr129:
	cli
	push  0
	push  129
	jmp isr_common_stub
	
_isr130:
	cli
	push  0
	push  130
	jmp isr_common_stub
	
_isr131:
	cli
	push  0
	push  131
	jmp isr_common_stub
	
_isr132:
	cli
	push  0
	push  132
	jmp isr_common_stub
	
_isr133:
	cli
	push  0
	push  133
	jmp isr_common_stub
	
_isr134:
	cli
	push  0
	push  134
	jmp isr_common_stub
	
_isr135:
	cli
	push  0
	push  135
	jmp isr_common_stub
	
_isr136:
	cli
	push  0
	push  136
	jmp isr_common_stub
	
_isr137:
	cli
	push  0
	push  137
	jmp isr_common_stub
	
_isr138:
	cli
	push  0
	push  138
	jmp isr_common_stub
	
_isr139:
	cli
	push  0
	push  139
	jmp isr_common_stub
	
_isr140:
	cli
	push  0
	push  140
	jmp isr_common_stub
	
_isr141:
	cli
	push  0
	push  141
	jmp isr_common_stub
	
_isr142:
	cli
	push  0
	push  142
	jmp isr_common_stub
	
_isr143:
	cli
	push  0
	push  143
	jmp isr_common_stub
	
_isr144:
	cli
	push  0
	push  144
	jmp isr_common_stub
	
_isr145:
	cli
	push  0
	push  145
	jmp isr_common_stub
	
_isr146:
	cli
	push  0
	push  146
	jmp isr_common_stub
	
_isr147:
	cli
	push  0
	push  147
	jmp isr_common_stub
	
_isr148:
	cli
	push  0
	push  148
	jmp isr_common_stub
	
_isr149:
	cli
	push  0
	push  149
	jmp isr_common_stub
	
_isr150:
	cli
	push  0
	push  150
	jmp isr_common_stub
_isr151:
	cli
	push  0
	push  151
	jmp isr_common_stub
	
_isr152:
	cli
	push  0
	push  152
	jmp isr_common_stub
	
_isr153:
	cli
	push  0
	push  153
	jmp isr_common_stub
	
_isr154:
	cli
	push  0
	push  154
	jmp isr_common_stub
	
_isr155:
	cli
	push  0
	push  155
	jmp isr_common_stub
	
_isr156:
	cli
	push  0
	push  156
	jmp isr_common_stub
	
_isr157:
	cli
	push  0
	push  157
	jmp isr_common_stub
	
_isr158:
	cli
	push  0
	push  158
	jmp isr_common_stub
_isr159:
	cli
	push  0
	push  159
	jmp isr_common_stub
	
_isr160:
	cli
	push  0
	push  160
	jmp isr_common_stub
	
_isr161:
	cli
	push  0
	push  161
	jmp isr_common_stub
	
_isr162:
	cli
	push  0
	push  162
	jmp isr_common_stub
	
_isr163:
	cli
	push  0
	push  163
	jmp isr_common_stub
	
_isr164:
	cli
	push  0
	push  164
	jmp isr_common_stub
	
_isr165:
	cli
	push  0
	push  165
	jmp isr_common_stub
	
_isr166:
	cli
	push  0
	push  166
	jmp isr_common_stub
	
_isr167:
	cli
	push  0
	push  167
	jmp isr_common_stub
	
_isr168:
	cli
	push  0
	push  168
	jmp isr_common_stub
	
_isr169:
	cli
	push  0
	push  169
	jmp isr_common_stub
	
_isr170:
	cli
	push  0
	push  170
	jmp isr_common_stub
	
_isr171:
	cli
	push  0
	push  171
	jmp isr_common_stub
	
_isr172:
	cli
	push  0
	push  172
	jmp isr_common_stub
	
_isr173:
	cli
	push  0
	push  173
	jmp isr_common_stub
	
_isr174:
	cli
	push  0
	push  174
	jmp isr_common_stub
	
_isr175:
	cli
	push  0
	push  175
	jmp isr_common_stub
	
_isr176:
	cli
	push  0
	push  176
	jmp isr_common_stub
	
_isr177:
	cli
	push  0
	push  177
	jmp isr_common_stub
	
_isr178:
	cli
	push  0
	push  178
	jmp isr_common_stub
	
_isr179:
	cli
	push  0
	push  179
	jmp isr_common_stub
	
_isr180:
	cli
	push  0
	push  180
	jmp isr_common_stub
_isr181:
	cli
	push  0
	push  181
	jmp isr_common_stub
	
_isr182:
	cli
	push  0
	push  182
	jmp isr_common_stub
	
_isr183:
	cli
	push  0
	push  183
	jmp isr_common_stub
	
_isr184:
	cli
	push  0
	push  184
	jmp isr_common_stub
	
_isr185:
	cli
	push  0
	push  185
	jmp isr_common_stub
	
_isr186:
	cli
	push  0
	push  186
	jmp isr_common_stub
	
_isr187:
	cli
	push  0
	push  187
	jmp isr_common_stub
	
_isr188:
	cli
	push  0
	push  188
	jmp isr_common_stub
	
_isr189:
	cli
	push  0
	push  189
	jmp isr_common_stub
	
_isr190:
	cli
	push  0
	push  190
	jmp isr_common_stub
	
_isr191:
	cli
	push  0
	push  191
	jmp isr_common_stub
	
_isr192:
	cli
	push  0
	push  192
	jmp isr_common_stub
	
_isr193:
	cli
	push  0
	push  193
	jmp isr_common_stub
	
_isr194:
	cli
	push  0
	push  194
	jmp isr_common_stub
	
_isr195:
	cli
	push  0
	push  195
	jmp isr_common_stub
	
_isr196:
	cli
	push  0
	push  196
	jmp isr_common_stub
	
_isr197:
	cli
	push  0
	push  197
	jmp isr_common_stub
	
_isr198:
	cli
	push  0
	push  198
	jmp isr_common_stub
	
_isr199:
	cli
	push  0
	push  199
	jmp isr_common_stub
	
_isr200:
	cli
	push  0
	push  200
	jmp isr_common_stub
	
_isr201:
	cli
	push  0
	push  201
	jmp isr_common_stub
	
_isr202:
	cli
	push  0
	push  202
	jmp isr_common_stub
	
_isr203:
	cli
	push  0
	push  203
	jmp isr_common_stub
	
_isr204:
	cli
	push  0
	push  204
	jmp isr_common_stub
	
_isr205:
	cli
	push  0
	push  205
	jmp isr_common_stub
	
_isr206:
	cli
	push  0
	push  206
	jmp isr_common_stub
	
_isr207:
	cli
	push  0
	push  207
	jmp isr_common_stub
	
_isr208:
	cli
	push  0
	push  208
	jmp isr_common_stub
	
_isr209:
	cli
	push  0
	push  209
	jmp isr_common_stub
	
_isr210:
	cli
	push  0
	push  210
	jmp isr_common_stub
	
_isr211:
	cli
	push  0
	push  211
	jmp isr_common_stub
	
_isr212:
	cli
	push  0
	push  212
	jmp isr_common_stub
	
_isr213:
	cli
	push  0
	push  213
	jmp isr_common_stub
	
_isr214:
	cli
	push  0
	push  214
	jmp isr_common_stub
	
_isr215:
	cli
	push  0
	push  215
	jmp isr_common_stub
	
_isr216:
	cli
	push  0
	push  216
	jmp isr_common_stub
	
_isr217:
	cli
	push  0
	push  217
	jmp isr_common_stub
	
_isr218:
	cli
	push  0
	push  218
	jmp isr_common_stub
	
_isr219:
	cli
	push  0
	push  219
	jmp isr_common_stub
	
_isr220:
	cli
	push  0
	push  220
	jmp isr_common_stub
	
_isr221:
	cli
	push  0
	push  221
	jmp isr_common_stub
	
_isr222:
	cli
	push  0
	push  222
	jmp isr_common_stub
	
_isr223:
	cli
	push  0
	push  223
	jmp isr_common_stub
	
_isr224:
	cli
	push  0
	push  224
	jmp isr_common_stub
	
_isr225:
	cli
	push  0
	push  225
	jmp isr_common_stub
	
_isr226:
	cli
	push  0
	push  226
	jmp isr_common_stub
	
_isr227:
	cli
	push  0
	push  227
	jmp isr_common_stub
	
_isr228:
	cli
	push  0
	push  228
	jmp isr_common_stub
	
_isr229:
	cli
	push  0
	push  229
	jmp isr_common_stub
	
_isr230:
	cli
	push  0
	push  230
	jmp isr_common_stub
	
_isr231:
	cli
	push  0
	push  231
	jmp isr_common_stub
_isr232:
	cli
	push  0
	push  232
	jmp isr_common_stub
	
_isr233:
	cli
	push  0
	push  233
	jmp isr_common_stub
_isr234:
	cli
	push  0
	push  234
	jmp isr_common_stub
_isr235:
	cli
	push  0
	push  235
	jmp isr_common_stub
	
_isr236:
	cli
	push  0
	push  236
	jmp isr_common_stub
	
_isr237:
	cli
	push  0
	push  237
	jmp isr_common_stub
	
_isr238:
	cli
	push  0
	push  238
	jmp isr_common_stub
	
_isr239:
	cli
	push  0
	push  239
	jmp isr_common_stub
	
_isr240:
	cli
	push  0
	push  240
	jmp isr_common_stub
	
_isr241:
	cli
	push  0
	push  241
	jmp isr_common_stub
_isr242:
	cli
	push  0
	push  242
	jmp isr_common_stub
	
_isr243:
	cli
	push  0
	push  243
	jmp isr_common_stub
	
_isr244:
	cli
	push  0
	push  244
	jmp isr_common_stub
_isr245:
	cli
	push  0
	push  245
	jmp isr_common_stub
	
_isr246:
	cli
	push  0
	push  246
	jmp isr_common_stub
	
_isr247:
	cli
	push  0
	push  247
	jmp isr_common_stub
	
_isr248:
	cli
	push  0
	push  248
	jmp isr_common_stub
	
_isr249:
	cli
	push  0
	push  249
	jmp isr_common_stub
	
_isr250:
	cli
	push  0
	push  250
	jmp isr_common_stub
	
_isr251:
	cli
	push  0
	push  251
	jmp isr_common_stub
	
_isr252:
	cli
	push  0
	push  252
	jmp isr_common_stub
	
_isr253:
	cli
	push  0
	push  253
	jmp isr_common_stub
	
_isr254:
	cli
	push  0
	push  254
	jmp isr_common_stub
	
_isr255:
	cli
	push  0
	push  255
	jmp isr_common_stub
	
extern _isr_default_handler
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
    mov eax, _isr_default_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret