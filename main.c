#include "include.h"

void myshow(void)
{
  char spring_oled[20];
  OLED_Clear();
  sprintf(spring_oled,"R:%hd--L:%hd",RightCadence,LeftCadence);
  OLED_ShowString_1608(40,30,spring_oled,0);
  OLED_Refresh_Gram();
}
void wheel(int right_up, int right_down, int left_up, int left_down) //右正,右反,左正,左反
{
  FTM_PWM_ChangeDuty(HW_FTM0,HW_FTM_CH4,right_up); //右正
  FTM_PWM_ChangeDuty(HW_FTM0,HW_FTM_CH5,right_down); //右反
          
  FTM_PWM_ChangeDuty(HW_FTM0,HW_FTM_CH7,left_up); //左正
  FTM_PWM_ChangeDuty(HW_FTM0,HW_FTM_CH6,left_down); //左反
}


int main()
{
	DisableInterrupts;
	init();
	EnableInterrupts;
	while(1)
	{
          final_control();
          wheel(2000,0,2000,0);
          Speed_Measure();
          get_mpu6050();
          printf("R:%hd--L:%hd ax:%f ay:%f az:%f dx:%f dy:%f dz:%f\n",RightCadence,LeftCadence,acc[0],acc[1],acc[2],gra[0],gra[1],gra[2]);
          DWT_DelayMs(100);
          
          
          //myshow();
          //DWT_DelayMs(1000);
          //dispimage();//OLED显示图像 
          //supermonitor();//名优科创上位机
          //vcan_sendimg(imgadd,row_num*col_num);山外上位机传输图像
        //保护程序
         if(RightCadence > 2000 || LeftCadence > 2000)
        {
        wheel(0,0,0,0);
        printf("Speed Erro!!! STOP the Car!");
        break;
        }
        }
}

