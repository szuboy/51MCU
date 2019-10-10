;
; @time: 2019-10-10 
; @author: Jeremy.Zhang
; @function: LED blinks based on assemble program
;


; pins redifine, low works(引脚重命名, 低电平有效)
LED1 BIT P2.4
LED2 BIT P2.5
LED3 BIT P2.6
LED4 BIT P2.7
BEEP BIT P1.0


; EQU(Equal) assign(赋值)
DelayTimes_100MS EQU 6FH


; program start(主程序开始) 
ORG 0000H                           ;定义程序起始运行地址 
LJMP START                          ;跳转到'START'标记符处程序运行 


ORG 0100H
START:
    MOV SP, #70H                    ;设置堆栈, 目的: 保存局部变量和中断返回 
START1:
    LCALL LEDRUN                    ;调用LED函数 
    LJMP  START1                    ;跳回'START1'标记符, 类似于while(1)循环 


; Delay 100Ms function(延时100MS函数)
Delay100MS:
    MOV R7, DelayTimes_100MS
    
    Delay100MS_1:  MOV R6, #10
    Delay100MS_2:  MOV R5, #150
    Delay100MS_3:  MOV R4, #200
    Delay100MS_4:  DJNZ R4, Delay100MS_4
                   DJNZ R5, Delay100MS_3
                   DJNZ R6, Delay100MS_2
                   DJNZ R7, Delay100MS_1
RET                                 


; LED blinks function(LED跑马灯函数)
LEDRUN: 
    CLR   LED1                       ;设置低电平 
    SETB  LED2                       ;设置高电平 
    SETB  LED3
    SETB  LED4
    CLR   BEEP
    MOV   DelayTimes_100MS, #10      ;设置需要10个延时100MS 
    LCALL Delay100MS                 ;调用Delay100MS函数
   
    SETB  LED1                       
    CLR   LED2
    SETB  LED3
    SETB  LED4 
    SETB  BEEP                     
    MOV   DelayTimes_100MS, #10       
    LCALL Delay100MS 

    SETB  LED1                       
    SETB  LED2
    CLR   LED3
    SETB  LED4
    CLR   BEEP                      
    MOV   DelayTimes_100MS, #10       
    LCALL Delay100MS 

    SETB  LED1                       
    SETB  LED2
    SETB  LED3
    CLR   LED4
    SETB  BEEP                      
    MOV   DelayTimes_100MS, #10       
    LCALL Delay100MS 
                 
RET                                  ;函数结束标记符 
    
END 