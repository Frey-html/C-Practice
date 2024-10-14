data segment
s db 100 dup(0)
t db 100 dup(0)
data ends

code segment
assume cs:code, ds:data
main:
   mov si, 0
   mov di, 0
   mov ah, 01h ;׼������INT 21h 01h���뵥���ַ�
   mov bl, 0dh ;0dhΪ�س�ascii�룬ÿ�ζ�����֮�Ƚ��ж��Ƿ�ֹͣ����

input:
   int 21h
   mov s[si], al 
   add si, 1   ;����һ���ַ�������s ���ȼ�1
   cmp al, bl
   jne input   ;�����ַ�Ϊ�س�ʱ��ֹͣ����

mov bx, 0      ;bl��Ϊ��sȡֵʱ����s�±�
transform:
   cmp bx, si 
   je next   ;�������s���꣬��������
   mov al, s[bx]
   add bx, 1   ;�Ѿ�ȡ��һ������s�������±����
   cmp al, 020h;����ַ��ǿո��򲻶���t��ֱ�ӽ�����һ�ζ���
   je transform
   cmp al, 041h 
   jb readint  ;����ַ�ֵС��a����ֱ�Ӷ���t
   cmp al, 07ah 
   ja readint  ;����ַ�ֵ����z����ֱ�Ӷ���t
   sub al, 020h;Сд��ĸתΪ��д
readint:   
   mov t[di], al;���ַ���������t
   add di, 1    ;����t�±�����
   jmp transform   

next:
   mov ah, 02h
   mov bx, 0    ;bl��¼����t���ʱ�±�
   mov dl, 0dh
   int 21h
   mov dl, 0ah
   int 21h      ;�س����У�����������Ḳ���������ݵ���ʾ
   
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
   int 21h      ;�����ɺ�س�����
pause:          ;������ɺ����ѭ������ס�����ֹ�����Կ������н��
   jmp pause

code ends
end main