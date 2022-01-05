    #include <stdio.h>
    #include <setjmp.h>
    jmp_buf buf;
    void F2(void)
    {
        printf("F2()\n");
        longjmp(buf,1);
    }
    void F1(void)
    {
        F2();
        printf("F1()\n");
    }
    int main(void)
    {
        int jmpret = setjmp(buf);
        if(!jmpret)
        {
            F1();
        }
        else
        {
            printf("继续执行main\n");
        }
        return 0;
    }
