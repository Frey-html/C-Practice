.386
data segment use16
a db 0 ;当前进行到的ascii值，从0到255
i db 0 ;行
j db 0 ;列
colorchar db 0Ch ;背景黑色，前景亮红色
colornum db 0Ah  ;背景黑色，前景亮绿色
data ends

code segment use16
assume cs:code, ds:data
main:
    mov ax, data
    mov ds, ax
    mov ax, 0B800h
    mov es, ax
    mov ax, 03h
    int 10h     ;设置80*25的文本模式

;向屏幕输出字符
linecycle:
    mov bx, 0
    mov al, j
    mov bl, 14
    mul bl
    mov bx, ax     ;计算当前列偏移地址
    mov i, 0       ;重置当前所在的行数
rowcycle:
    mov ah, a
    mov es:[bx], ah ;输出当前字符
    mov ah, colorchar
    mov es:[bx+1], ah;设置字符背景色及前景色
    mov ah, a
    shr ah, 4
    add ah, 30h      ;加上‘0’的值，转换为该数值数字对应的ascii码
    cmp ah, 3Ah
    jb  continue1    ;如果对应数值大于9，则额外加上7使其变成对应16进制字母的ascii值
    add ah, 07h
continue1:
    mov es:[bx+2], ah
    mov ah, colornum
    mov es:[bx+3], ah;输出2位16进制数a的高位，设置数字背景色及前景色
    mov ah, a
    shl ah, 4
    shr ah, 4
    add ah, 30h      ;加上‘0’的值，转换为该数值数字对应的ascii码
    cmp ah, 3Ah
    jb  continue2    ;如果对应数值大于9，则额外加上7使其变成对应16进制字母的ascii值
    add ah, 07h
continue2:
    mov es:[bx+4], ah
    mov ah, colornum
    mov es:[bx+5], ah;输出2位16进制数a的低位，设置数字背景色及前景色
    add a, 1                 ;a自增准备输出下一个ascii码及对应十六进制编码
    cmp a, 0
    je exit                  ;输出0~255，如果a自增后为0即从0xFF编程0x00，输出结束
    add bx, 160              ;坐标转为同一列下一行
    add i, 1
    cmp i, 25                ;行坐标为0~25，若为25则换列，否则继续执行
    jb rowcycle
    add j, 1
    jmp linecycle

exit:
    mov ah, 0
    int 16h
code ends
end main

