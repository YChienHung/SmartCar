/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/

//���̵��뵽����֮��Ӧ��ѡ�й���Ȼ����refreshˢ��һ��֮���ٱ���
//����Ĭ������Ϊ�ر��Ż��������Լ��һ�����ѡ��properties->C/C++ Build->Setting
//Ȼ�����Ҳ�Ĵ������ҵ�C/C++ Compiler->Optimization->Optimization level�������Ż��ȼ�
//һ��Ĭ���½����Ĺ��̶���Ĭ�Ͽ�2���Ż�����˴��Ҳ��������Ϊ2���Ż�

//����TCϵ��Ĭ���ǲ�֧���ж�Ƕ�׵ģ�ϣ��֧���ж�Ƕ����Ҫ���ж���ʹ��enableInterrupts();�������ж�Ƕ��
//�򵥵�˵ʵ���Ͻ����жϺ�TCϵ�е�Ӳ���Զ�������disableInterrupts();���ܾ���Ӧ�κε��жϣ������Ҫ�����Լ��ֶ�����enableInterrupts();�������жϵ���Ӧ��

//ͷ�ļ�����
#include "headfile.h"       //��ɵķ�װ��
#include "Binarization.h"   //��ֵ������

#pragma section all "cpu0_dsram"    //���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

//�������
int *LeftLine,*CentreLine,*RightLine;   //����������

int core0_main(void)
{
    int i;
    uint8 *p;
	get_clk();//��ȡʱ��Ƶ��  ��ر���
	//�û��ڴ˴����ø��ֳ�ʼ��������

	uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);//��ʼ������0�������λ��ͨѶ
	mt9v03x_init();//��ʼ������ͷ


    //�ȴ����к��ĳ�ʼ�����
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
	enableInterrupts();

	while (TRUE)
	{
		//�û��ڴ˴���д�������

	    if(mt9v03x_finish_flag)
	    {

	        ImageBinary();
	        p = BinaryImage[0];
            uart_putchar(UART_0,0x00);uart_putchar(UART_0,0xff);uart_putchar(UART_0,0x01);uart_putchar(UART_0,0x01);//��������
            for(i=0; i<MT9V03X_W*MT9V03X_H; i++)
            {
                if(p[i]==255)
                    uart_putchar(UART_0,0xff);
                else
                    uart_putchar(UART_0,0x00);
            }

            mt9v03x_finish_flag = 0;//��ͼ��ʹ����Ϻ�  ��������־λ�����򲻻Ὺʼ�ɼ���һ��ͼ��
	    }
	}
}

#pragma section all restore

