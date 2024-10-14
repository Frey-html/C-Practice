;计算程序
;功能：读入一行字符串，由最大位65535的无符号数与+-*/组成，从左到右不考虑优先级及余数，每次保留32位二进制运算结果
;计算完成后输出结果的十进制数与8位16进制数

;总结
;(1)注意操作中位数，灵活使用movsx与movzx进行扩充
;(2)函数注意ret以及压栈出栈避免需要使用的寄存器值被破坏
;(3)使用乘除法注意位数与操作所需寄存器，尤其是64位除32位除法edx:eax，若只用32位则需将edx置0
.386
data segment use16
s db 1000 dup(0) ;存放读入的字符串
crlf db 0Dh, 0Ah, '$';字符串 意味回车换行，用于输出
data ends

stk segment stack use16
dw 200h dup(0)
stk ends

code segment use16
assume cs:code, ds:data, ss:stk
;ok
;input函数，用于读入一个字符串放入s中，调用时di = offset array
input:
   mov ah, 1
   int 21h
   cmp al, 0Dh; 判断AL是否为回车键
   je input_done
   mov [di], al
   inc di; add di, 1
   jmp input
input_done:
   mov byte ptr [di], 0;添加数值0作为字符串结尾
   mov ah, 9
   mov dx, offset crlf
   int 21h
   ret

;calculae计算函数，从字符串取出一个操作符和一个操作数进行相应计算
;读入 数组下标 被操作数eax
;输出 运算结果eax
calculate:
    cmp byte ptr [di], 02Bh ;加法
    je cal_add
    cmp byte ptr [di], 02Dh ;减法
    je cal_sub
    cmp byte ptr [di], 02Ah ;乘法
    je cal_mul
    jmp cal_div  ;否则为除法
cal_add:
    inc di
    call number
    add eax, ebx
    jmp cal_done
cal_sub:
    inc di
    call number
    sub eax, ebx
    jmp cal_done
cal_mul:
    inc di
    call number
    mul ebx
    jmp cal_done
cal_div:
    inc di
    call number
    div ebx
    jmp cal_done
cal_done:
    ret

;number取操作数函数，从字符串取出一个操作数放在ebx中
number:
    push eax
    push ecx
    mov eax, 0;存储已得到的十进制值
    mov ecx, 0;存放要取出的数字的ascii码并转换为对应数值
    mov ebx, 10
read_next:
    cmp byte ptr [di], 030h
    jb read_done
    cmp byte ptr [di], 039h
    ja read_done  ;若当前下标对应的值不是再数字，则结束
    mul ebx;已得到结果乘10加上当前位，为字符表示的十进制数读入方法
    movzx ecx, byte ptr [di] ;将当前数字ascii码移入ecx
    sub ecx, 030h ;转化ascii码为对应数字的值
    add eax, ecx
    inc di        ;下标自增
    jmp read_next
read_done:
    mov ebx, eax  ;当前读完的操作数从ecx放入ebx中
    pop ecx       ;恢复ecx的值
    pop eax       ;恢复eax的值
    ret

;10进制输出函数，向屏幕上输出结果的十进制表示
;不断除10取余数压栈
output1:
    push eax;保存eax的值
    mov ecx, 0;cx记录压栈次数
    mov ebx, 10;被除数
    cmp eax, 0;若结果为0
    ja output1_push
    mov ah, 2;eax为0即最后结果为0，直接输出0
    mov dl, 030h
    int 21h
    jmp output1_end
output1_push:
    mov edx, 0;64位除32位除法，被除数为edx：eax
    div ebx
    add edx, 030h;余数从数值转换为对应的ascii码
    push edx ;余数ascii码压栈
    inc ecx ;压栈次数自增1
    cmp eax, 0
    ja output1_push
output1_pop:
    cmp ecx, 0
    je output1_end
    pop edx ;此时，一位的十位数字存储在edx低八位中，即dl，可以使用21h 2号功能直接输出
    mov ah, 2
    int 21h
    sub ecx, 1
    jmp output1_pop
output1_end:
    mov ah, 9
    mov dx, offset crlf
    int 21h   ;回车换行
    pop eax
    ret

;16进制输出函数，向屏幕上输出结果的8位16进制表示
;不断除16取余数压栈
output2:
    push eax;保存eax的值
    mov ecx, 0;cx记录压栈次数
    mov ebx, 16;被除数
    mov di, 0;di记录输出时前面补0次数
    cmp eax, 0;若结果为0
    ja output2_push
    jmp output2_print0;计算补0的个数并输出
output2_push:
    mov edx, 0
    div ebx
    add edx, 030h;余数从数值转换为对应的ascii码
    cmp edx, 039h;如果数值大于9，则需要转换为对应的16进制字母编码
    jb  output2_push_next
    add edx, 7;上方已经加过030h，则10以上变为x+030h，需额外加上7变为大写字母对应的ascii
output2_push_next:
    push edx ;余数ascii码压栈
    inc ecx ;压栈次数自增1
    cmp eax, 0
    ja output2_push
output2_print0: ;补0
    mov di, 8
    sub di, cx
    mov ah, 2
    mov dl, 030h
print0_next:
    cmp di, 0
    je output2_pop
    int 21h ;输出一个0
    sub di, 1;di自减
    jmp print0_next
output2_pop:
    cmp cx, 0
    je output2_end
    pop edx ;此时，一位的十位数字存储在edx低八位中，即dl，可以使用21h 2号功能直接输出
    mov ah, 2
    int 21h
    sub cx, 1
    jmp output2_pop
output2_end:
    mov ah, 2
    mov edx, 068h
    int 21h ;在结尾补上h表示16进制
    mov ah, 9
    mov dx, offset crlf
    int 21h   ;回车换行
    pop eax
    ret

main:
    mov ax, data
    mov ds, ax  ;对数据段寄存器赋值，代码和堆栈段寄存器自动赋值
    mov di, offset s
    call input  ;调用输入函数，将结果放入s中
    mov di, 0   ;bx为当前数组下标
    call number ;取出第一个操作数，eax同时作为被操作数和运算结果的存储空间
    mov eax, ebx;number函数的结果放在ebx中，但此时需要第一个操作数进入eax作为后续被操作数
compute:
    cmp byte ptr [di], 0 ;运算已经结束
    je output
    call calculate ;取出一个符和下一个操作数与已得到的结果进行下一次运算
    jmp compute
output:
    call output1 ;输出10进制数
    call output2 ;输出16进制数
    mov ah, 4Ch
    int 21h      ;程序结束
code ends
end main



    


