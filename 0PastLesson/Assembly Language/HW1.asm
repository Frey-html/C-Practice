data segment
s db 100 dup(0)
t db 100 dup(0)
data ends

code segment
assume cs:code, ds:data
main:
   mov si, 0
   mov di, 0
   mov ah, 01h ;准备调用INT 21h 01h读入单个字符
   mov bl, 0dh ;0dh为回车ascii码，每次读入与之比较判断是否停止读入

input:
   int 21h
   mov s[si], al 
   add si, 1   ;读入一个字符，数组s 长度加1
   cmp al, bl
   jne input   ;输入字符为回车时，停止读入

mov bx, 0      ;bl作为从s取值时数组s下标
transform:
   cmp bx, si 
   je next   ;如果数组s读完，则进行输出
   mov al, s[bx]
   add bx, 1   ;已经取出一个数，s的数组下标递增
   cmp al, 020h;如果字符是空格，则不读入t，直接进入下一次读入
   je transform
   cmp al, 041h 
   jb readint  ;如果字符值小于a，则直接读入t
   cmp al, 07ah 
   ja readint  ;如果字符值大于z，则直接读入t
   sub al, 020h;小写字母转为大写
readint:   
   mov t[di], al;将字符读入数组t
   add di, 1    ;数组t下标自增
   jmp transform   

next:
   mov ah, 02h
   mov bx, 0    ;bl记录数组t输出时下标
   mov dl, 0dh
   int 21h
   mov dl, 0ah
   int 21h      ;回车换行，若不换行则会覆盖输入数据的显示
   
output:
   cmp bx, di
   je exit
   mov dl, t[bx]
   int 21h
   add bx, 1
   jmp output

exit:
   mov dl, 0dh
   int 21h
   mov dl, 0ah
   int 21h      ;输出完成后回车换行
pause:          ;程序完成后进入循环，卡住程序防止闪退以看到运行结果
   jmp pause

code ends
end main