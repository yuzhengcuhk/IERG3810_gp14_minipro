#include "rtc.h"
#include "usart.h"

_calendar_obj calendar;
u8 rtc_data[7],rtc_bit=0;

void RTC_NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void RTC_IRQHandler()
{
	if(RTC_GetITStatus(RTC_IT_SEC)!= RESET)
	{
		RTC_Get();
		rtc_bit=1;		
	}
	if(RTC_GetITStatus(RTC_IT_ALR)!= RESET)
	{
		RTC_ClearITPendingBit(RTC_IT_ALR);
	  	RTC_Get();
  		printf("Alarm Time:%d-%d-%d %d:%d:%d\n",calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);	
  	} 				  								 
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);
	RTC_WaitForLastTask();	
}


u8 rtc_init()
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP|RCC_APB1Periph_PWR,ENABLE);
	PWR_BackupAccessCmd(ENABLE); 
	if(BKP_ReadBackupRegister(BKP_DR1)!=0x5050)
	{
		BKP_DeInit();
		RCC_LSEConfig(RCC_LSE_ON);

		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		RTC_WaitForLastTask();
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IT_SEC,ENABLE);
		RTC_WaitForLastTask();
		RTC_EnterConfigMode();
		RTC_SetPrescaler(32767);
		RTC_WaitForLastTask();
		RTC_Set(2015,10,30,13,59,56);
		RTC_ExitConfigMode();
		BKP_WriteBackupRegister(BKP_DR1,0x5050);
	}
	else
	{
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IT_SEC,ENABLE);
		RTC_WaitForLastTask();			
	}
	RTC_NVIC_Config();
	RTC_Get();
	return 0;		
}




u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0)
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;   
			else return 0;   
		}else return 1;   
	}else return 0;	
}	 		


u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5};
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
u8 RTC_Set(u16 year,u8 month,u8 day,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(year<1970||year>2099)
	{
		return 1;
	}
	for(t=1970;t<year;t++)
	{
		if(Is_Leap_Year(t))
		{
			seccount+=31622400;
		}
		else
		{
			seccount+=31536000;
		}	
	}
	month-=1;
	for(t=0;t<month;t++)
	{
		seccount+=(u32)mon_table[t]*86400;
		if(Is_Leap_Year(year)&&t==1)
		{
			seccount+=86400;
		}			
	}
	seccount+=(u32)(day-1)*86400;
	seccount+=(u32)hour*3600;
	seccount+=(u32)min*60;
	seccount+=(u32)sec;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP|RCC_APB1Periph_PWR,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	RTC_SetCounter(seccount);
	RTC_WaitForLastTask();
	return 0;		
}


u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	
	{
		if(Is_Leap_Year(t))seccount+=31622400;
		else seccount+=31536000;
	}
	smon-=1;
	for(t=0;t<smon;t++)
	{
		seccount+=(u32)mon_table[t]*86400;
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;
	}
	seccount+=(u32)(sday-1)*86400;
	seccount+=(u32)hour*3600;
    seccount+=(u32)min*60;
	seccount+=sec;    

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE);

	
	RTC_SetAlarm(seccount);
 
	RTC_WaitForLastTask();
	
	return 0;	    
}





u8 RTC_Get_Week(u16 year,u8 month,u8 day)
{	
	u16 temp2;
	u8 yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 

	if (yearH>19)yearL+=100;

	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}			  


u8 RTC_Get()
{
	static u16 daycnt=0;
	u32 timecount=0;
	u32 temp=0;
	u16 temp1=0;
	timecount=RTC_GetCounter();
	temp=timecount/86400;
	if(daycnt!=temp)
	{
		daycnt=temp;
		temp1=1970;
		while(temp>=365)
		{
			if(Is_Leap_Year(temp1))
			{
				if(temp>=366)
				{
					temp-=366;
				}
				else 
				{
					temp1++;
					break;
				}
						
			}
			else temp-=365;
			temp1++;
		}
		calendar.w_year=temp1;
		temp1=0;
		while(temp>=28)
		{
			if(Is_Leap_Year(calendar.w_year)&&temp1==1)
			{
				if(temp>=29)temp-=29;
				else break;
			}
			else
			{ 
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];
				else break;
			}
			temp1++;	
		}
		calendar.w_month=temp1+1;
		calendar.w_date=temp+1;
	}
	temp=timecount%86400;
	calendar.hour=temp/3600;
	calendar.min=(temp%3600)/60;
	calendar.sec=(temp%3600)%60;
	calendar.week=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);

	return 0;	
}
