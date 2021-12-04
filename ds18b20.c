/*
 *
 * DS18B20 one wire temp --- PA3 stm8
 *
 */




#include "stm8.h"
#include <string.h>
#include <stdio.h>
#include "PID.h"
#include <stdbool.h>
#define SET(x, y)   (x) |= (y)
#define UNSET(x, y) (x) &= ~(y)
#define READ(x, y)  ((x) & (y))



//http://www.cnblogs.com/chenlidong/articles/1823542.html
#define DS18B20_DQ_OUT          PA_DDR |= (1<<3)   //??
#define DS18B20_DQ_IN           PA_DDR &= ~(1<<3)   //??
#define DS18B20_DQ_HIGH         PA_ODR |= (1<<3)   //??
#define DS18B20_DQ_LOW          PA_ODR &= ~(1<<3)    //??
#define DS18B20_DQ_PULL_UP      PA_CR1 |= (1<<3)   //??
#define DS18B20_DQ_FLOATING     PA_CR1 &=  ~(1<<3)  //??
#define DS18B20_DQ_PUSH_PULL    PA_CR1 |= (1<<3)   //??
#define DS18B20_DQ_OPEN_DRAIN   PA_CR1 &= ~(1<<3)   //??
#define DS18B20_DQ_VALUE        PA_IDR & (1<<3)      //DQ?

/* PID Controller parameters */
#define PID_KP  1.0f
#define PID_KI  1.0f
#define PID_KD  1.0f

#define PID_TAU 0.02f


//#define PID_LIM_MIN -10.0f
#define PID_LIM_MIN 0.0f
#define PID_LIM_MAX  10.0f

//#define PID_LIM_MIN_INT -5.0f
#define PID_LIM_MIN_INT 0.0f
#define PID_LIM_MAX_INT  5.0f

//#define SAMPLE_TIME_S 0.01f
#define SAMPLE_TIME_S 20.0f //iedere 20 seconden

/* Maximum run-time of simulation */
#define SIMULATION_TIME_MAX 4.0f
PIDController pid = { PID_KP, PID_KI, PID_KD,
	PID_TAU,
	PID_LIM_MIN, PID_LIM_MAX,
	PID_LIM_MIN_INT, PID_LIM_MAX_INT,
	SAMPLE_TIME_S };



typedef unsigned char UCHAR;
void delayTenMicro (void) {
	char a;
	for (a = 0; a < 50; ++a)
		__asm__("nop");
}
void heater_on();
void heater_off();

void InitializeSystemClock() {
	CLK_ICKR = 0;                       //  Reset the Internal Clock Register.
	CLK_ICKR = CLK_HSIEN;               //  Enable the HSI.
	CLK_ECKR = 0;                       //  Disable the external clock.
	while ((CLK_ICKR & CLK_HSIRDY) == 0);       //  Wait for the HSI to be ready for use.
	CLK_CKDIVR = 0;                     //  Ensure the clocks are running at full speed.
	CLK_PCKENR1 = 0xff;                 //  Enable all peripheral clocks.
	CLK_PCKENR2 = 0xff;                 //  Ditto.
	CLK_CCOR = 0;                       //  Turn off CCO.
	CLK_HSITRIMR = 0;                   //  Turn off any HSIU trimming.
	CLK_SWIMCCR = 0;                    //  Set SWIM to run at clock / 2.
	CLK_SWR = 0xe1;                     //  Use HSI as the clock source.
	CLK_SWCR = 0;                       //  Reset the clock switch control register.
	CLK_SWCR = CLK_SWEN;                //  Enable switching.
	while ((CLK_SWCR & CLK_SWBSY) != 0);        //  Pause while the clock switch is busy.
}
void delay (int time_ms) {
	volatile long int x;
	for (x = 0; x < 1036*time_ms; ++x)
		__asm__("nop");
}


void UARTPrintF (char *message) {
	char *ch = message;
	while (*ch) {
		UART1_DR = (unsigned char) *ch;     //  Put the next character into the data transmission register.
		while ((UART1_SR & SR_TXE) == 0);   //  Wait for transmission to complete.
		ch++;                               //  Grab the next character.
	}
}




//
//  Send a message to the debug port (UART1).
//

void print_byte_hex (unsigned char buffer) {
	unsigned char message[8];
	int a, b;
	a = (buffer >> 4);
	if (a > 9)
		a = a + 'a' - 10;
	else
		a += '0'; 
	b = buffer & 0x0f;
	if (b > 9)
		b = b + 'a' - 10;
	else
		b += '0'; 
	message[0] = a;
	message[1] = b;
	message[2] = 0;
	UARTPrintF (message);
}




void InitializeUART() {
	//
	//  Clear the Idle Line Detected bit in the status register by a read
	//  to the UART1_SR register followed by a Read to the UART1_DR register.
	//
	unsigned char tmp = UART1_SR;
	tmp = UART1_DR;
	//
	//  Reset the UART registers to the reset values.
	//
	UART1_CR1 = 0;
	UART1_CR2 = 0;
	UART1_CR4 = 0;
	UART1_CR3 = 0;
	UART1_CR5 = 0;
	UART1_GTR = 0;
	UART1_PSCR = 0;
	//
	//  Now setup the port to 115200,n,8,1.
	//
	UNSET (UART1_CR1, CR1_M);        //  8 Data bits.
	UNSET (UART1_CR1, CR1_PCEN);     //  Disable parity.
	UNSET (UART1_CR3, CR3_STOPH);    //  1 stop bit.
	UNSET (UART1_CR3, CR3_STOPL);    //  1 stop bit.
	UART1_BRR2 = 0x0a;      //  Set the baud rate registers to 115200 baud
	UART1_BRR1 = 0x08;      //  based upon a 16 MHz system clock.
	//
	//  Disable the transmitter and receiver.
	//
	UNSET (UART1_CR2, CR2_TEN);      //  Disable transmit.
	UNSET (UART1_CR2, CR2_REN);      //  Disable receive.
	//
	//  Set the clock polarity, lock phase and last bit clock pulse.
	//
	SET (UART1_CR3, CR3_CPOL);
	SET (UART1_CR3, CR3_CPHA);
	SET (UART1_CR3, CR3_LBCL);
	//
	//  Turn on the UART transmit, receive and the UART clock.
	//
	SET (UART1_CR2, CR2_TEN);
	SET (UART1_CR2, CR2_REN);
	UART1_CR3 = CR3_CLKEN;
}


// DISPLAY




void _tm1637Start(void);
void _tm1637Stop(void);
void _tm1637ReadResult(void);
void _tm1637WriteByte(unsigned char b);

void _tm1637ClkHigh(void);
void _tm1637ClkLow(void);
void _tm1637DioHigh(void);
void _tm1637DioLow(void);
void tm1637SetBrightness(char brightness);

const char segmentMap[] = {
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
	0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
	0x00
};



void tm1637Init(void)
{
	tm1637SetBrightness(4);
}



void tm1637DisplayDecimal(long TT,unsigned int displaySeparator)
{ unsigned int ii;
	unsigned int v = TT & 0x0000FFFF;
	unsigned char digitArr[4];



	//  unsigned char digitArr[4];
	for (ii = 0; ii < 4; ++ii) {
		digitArr[ii] = segmentMap[v % 10];
		if (ii == 2 && displaySeparator) {
			digitArr[ii] |= 1 << 7;
		}
		v /= 10;
	}

	_tm1637Start();
	_tm1637WriteByte(0x40);
	_tm1637ReadResult();
	_tm1637Stop();

	_tm1637Start();
	_tm1637WriteByte(0xc0);
	_tm1637ReadResult();

	for (ii = 0; ii < 4; ++ii) {
		_tm1637WriteByte(digitArr[3 - ii]);
		_tm1637ReadResult();
	}

	_tm1637Stop();
}

// Valid brightness values: 0 - 8.
// 0 = display off.
void tm1637SetBrightness(char brightness)
{
	// Brightness command:
	// 1000 0XXX = display off
	// 1000 1BBB = display on, brightness 0-7
	// X = don't care
	// B = brightness
	_tm1637Start();
	_tm1637WriteByte(0x87 + brightness);
	_tm1637ReadResult();
	_tm1637Stop();
}

void _tm1637Start(void)
{
	_tm1637ClkHigh();
	_tm1637DioHigh();
	delay(5);
	_tm1637DioLow();
}

void _tm1637Stop(void)
{
	_tm1637ClkLow();
	delay(5);
	_tm1637DioLow();
	delay(5);
	_tm1637ClkHigh();
	delay(5);
	_tm1637DioHigh();
}

void _tm1637ReadResult(void)
{
	_tm1637ClkLow();
	delay(5);
	// while (dio); // We're cheating here and not actually reading back the response.
	_tm1637ClkHigh();
	delay(5);
	_tm1637ClkLow();
}

void _tm1637WriteByte(unsigned char b)
{int ii;
	for (ii = 0; ii < 8; ++ii) {
		_tm1637ClkLow();
		if (b & 0x01) {
			_tm1637DioHigh();
		}
		else {
			_tm1637DioLow();
		}
		delay(15);
		b >>= 1;
		_tm1637ClkHigh();
		delay(15);
	}
}



void _tm1637ClkHigh(void)
{ 
	//PB_ODR_bit.ODR5 = 1; //      _tm1637ClkHigh(); 

	//  GPIO_WriteHigh(GPIOD,GPIO_PIN_2);
	PD_ODR |= 1 << 2;
}

void _tm1637ClkLow(void)
{ 
	// GPIO_WriteLow(GPIOD,GPIO_PIN_2);

	PD_ODR &= ~(1 << 2);

	//    PB_ODR_bit.ODR5 = 0; //      _tm1637ClkHigh(); 

}

void _tm1637DioHigh(void)
{
	//PB_ODR_bit.ODR4 = 1; //  _tm1637DioHigh(); 
	// GPIO_WriteHigh(GPIOD,GPIO_PIN_3);
	PD_ODR |= 1 << 3;

}

void _tm1637DioLow(void)
{
	PD_ODR &= ~(1 << 3);

	//GPIO_WriteLow(GPIOD,GPIO_PIN_3);
	//PB_ODR_bit.ODR4 = 0; //  _tm1637DioHigh(); 

}


void _delay_us(unsigned int i)
{
	i *= 3; 
	while(--i);
}

void _delay_ms(unsigned int i)
{
	while(i--)
	{
		_delay_us(1000);
	}
}



void DS18B20_Init(void)
{
	DS18B20_DQ_OUT;   
	DS18B20_DQ_PUSH_PULL;    
	DS18B20_DQ_HIGH;   
	_delay_us(10);
	DS18B20_DQ_LOW;   
	_delay_us(600);     //????

	DS18B20_DQ_IN;   
	DS18B20_DQ_PULL_UP;    
	_delay_us(100);     
	while(DS18B20_DQ_VALUE == 1);
	_delay_us(400);
}


void DS18B20_WriteByte(unsigned char _data)
{
	unsigned char i = 0;

	DS18B20_DQ_OUT;
	for (i = 0; i < 8; i++)
	{
		DS18B20_DQ_LOW;
		_delay_us(2);
		if (_data & 0x01)
		{
			DS18B20_DQ_HIGH;
		}
		_data >>= 1;
		_delay_us(60);
		DS18B20_DQ_HIGH;
	}
}

unsigned char DS18B20_ReadByte(void)
{
	unsigned char i = 0, _data = 0;

	for (i = 0; i < 8; i++)
	{
		DS18B20_DQ_OUT;
		DS18B20_DQ_LOW;
		_delay_us(5);
		_data >>= 1;
		DS18B20_DQ_HIGH;
		DS18B20_DQ_IN;
		if (DS18B20_DQ_VALUE)
		{
			_data |= 0x80;
		}
		DS18B20_DQ_OUT; 
		DS18B20_DQ_HIGH;
		_delay_us(60);
	}

	return _data;
}

float DS18B20_ReadTemperature(void)
{
	unsigned char temp = 0;
	float t = 0;
	/*
	 *
	 *  
	 *  0x44 is the command to calculate the temperature and save it in the scratchpad.  This takes up to 750 milliseconds.
	 *
	 *  0xBE is the command to send the contents of of the scratchpad.
	 *
	 *  What you are sending is "Everybody: Send your Scratchpad".  This only works if you only have one device.  
	 *
	 */
	DS18B20_Init();
	DS18B20_WriteByte(0xcc);
	DS18B20_WriteByte(0x44);

	DS18B20_Init();
	DS18B20_WriteByte(0xcc);
	DS18B20_WriteByte(0xbe);

	temp = DS18B20_ReadByte();
	t = (((temp & 0xf0) >> 4) + (temp & 0x07) * 0.125); 
	temp = DS18B20_ReadByte();
	t += ((temp & 0x0f) << 4);
	return t;
}

typedef unsigned char u8;

typedef struct {        // real time information field structure 
	u8 second;  
	u8 minute;  
	u8 heat;
	//	u8 hour;  
	//	u8 day;  
	//	long ticker; 
} st_time; 

st_time real_time;
bool fast=true; //to heat cold water to starttemp (overshoot is less important)
u8 alarmset; 
#define BEEP_ISR 6 // port D


unsigned int internteller;


void read_display_temp(float temp1) //every second called by interrupt
{
	unsigned int utemp;
	float objTemp; 
	char boodsch[12]="temp=\r\n";
	int eerste, tweede, derde, vierde;
	//float temp1=29.2, measurement;
	float measurement;
	measurement = DS18B20_ReadTemperature() ; //multiply with 100 to get everything on the 4 digit display 
	objTemp = measurement*100;
	eerste=0;tweede=0;derde=0;vierde=0;
	//make measurement suitable for display
	while (objTemp > 1000) {
		vierde+=1;
		objTemp-=1000;
	}
	while (objTemp > 100) {
		derde+=1;
		objTemp-=100;
	}
	while (objTemp > 10) {
		tweede+=1;
		objTemp-=10;
	}
	while (objTemp > 0)
	{
		eerste+=1;
		objTemp-=1;
	}

	utemp=vierde*1000+derde*100+tweede*10+eerste;

	tm1637DisplayDecimal(utemp, 1); // eg 37:12
	//sprintf(boodsch,"T*100:%d\r\n", utemp);
	//UARTPrintF (boodsch); 


	PIDController_Update(&pid, temp1, measurement); 
	sprintf(boodsch,"pid :%d\r\n", (int)(pid.out*10)); //todo dit moet SSD sturen of wel LED
	UARTPrintF (boodsch); 

}


void rt_one_second_increment (st_time *t) {
	//++t->ticker; //  todo constant definition 
	//
	// heating takes place in 20 second interval 100% means heating during 20 seconds
	// 50% means heating during 10 second and do nothing during 10 seconds
	//
	//char boodsch[12]="temp=\r\n";
	int targettemp;
	t->second +=1;
	if ((t->second==1)  | (t->second==21) | (t->second==41))
	{ 
		t->heat=0;
		//		read_display_temp(); //sample temp every second
	}
	t->heat+=1;
        if (fast) targettemp=(int)(pid.out*2);
	else
	targettemp=(int)(pid.out);	
	//if(t->heat > ((int)(pid.out*2)))
	//if(t->heat > ((int)(pid.out)))
	if(t->heat > targettemp)
	{
		heater_off();
	}
	else
	{
		heater_on();
	}


	if(t->second > 59) {
		t->second= 0;
		/*UARTPrintF ("min\r\n"); 
		  if(t->minute < 1) {
		  UARTPrintF ("alarm\r\n");
		  t->minute= 0;
		  }
		  else t->minute -=1;*/
		t->minute -=1;
	}
}


void timer_isr(void) __interrupt(BEEP_ISR) {
	if (++internteller > 500) {
		internteller=0;
		rt_one_second_increment(&real_time);
		//read_display_temp(); //sample temp every second
		//		++seconden;
	}

}



void heater_on(void)
{
	PC_ODR = (1<<3) ; //C8 connected to SSD
	PB_ODR = (0<<5) ; //onboard LED
}

void heater_off(void)
{
	PC_ODR = (0<<3) ;
	PB_ODR = (1<<5) ; //onboard LED
}

int main () {
	//	alarmset=2; //this should trigger sampleperiod
	/***parameters***/
	int temp2=55, temp3=68, temp4=78;
	int tijd1=30, tijd2=15, tijd3=15, tijd4=15;
	int phase=0;
	float tempera=40;
	/***/
	char boodsch[12]="temp=\r\n";
        
	real_time.minute=15;
	InitializeSystemClock();

	BEEP_CSR = (0<<7) | (0<<6) | (1<<5) | 0x1E;
	//display on PD2 PD3
	PD_DDR = (1 << 3) | (1 << 2); // output mode

	PD_DDR &=  ~(1 << 4); //PD4 input for beep?

	PD_CR1 = (1 << 3) | (1 << 2); // push-pull
	PD_CR1 &= ~(1 << 4); // input with float beep?
	//	PD_CR2 = (1 << 3) | (1 << 2); // up to 10MHz speed
	PD_CR2 = (1 << 3) | (1 << 2) | (1<< 4); // up to 10MHz speed + interrupt enabled

	EXTI_CR1 = (1<<7); //Port D external sensitivity bits7:6 10: Falling edge only
	EXTI_CR1 &= ~(1<<6); //Port D external sensitivity bits7:6 10: Falling edge only
	//LED
	//PB_DDR = (1<<5) | (1<<4);
	PC_DDR = (1<<3) ;
	PB_DDR = (1<<5) ;
	//PB_CR1 = (1<<5) | (1<<4);
	PC_CR1 = (1<<3) ;
	PB_CR1 = (1<<5) ;
	//PB_CR2 = (1<<4);

	tm1637Init();

	InitializeUART();
	/* Enable interrupts */
	__asm__("rim");


	/* Initialise PID controller */

	PIDController_Init(&pid);
	//	heater_on();
	phase=1;
	while (1) {

		//sprintf(boodsch,"%d%d,%d%d\r\n",vierde,derde,tweede,eerste); //print temperature serial port
		//		delayTenMicro();
		switch (phase){

			case 1: 
				read_display_temp(45); //sample temp
				if (real_time.minute<1) {phase =2; real_time.minute=45;
					fast=false;
					sprintf(boodsch,"to phase2\r\n"); 
					UARTPrintF (boodsch); 
				}
				break;

			case 2: 
				read_display_temp(62); //sample temp
				if (real_time.minute<1) {phase =3; real_time.minute=20;
					sprintf(boodsch,"to phase3\r\n"); 
					UARTPrintF (boodsch); 

				}
				break;
			case 3: 
				read_display_temp(71); //end no heating, no timer, overshoot 1degree, hence target is 72
				if (real_time.minute<1) {phase =4; real_time.minute=6;

					sprintf(boodsch,"to phase4\r\n"); 
					UARTPrintF (boodsch); 
				}
				break;
			case 4: 
				read_display_temp(78); //end no heating, no timer
				if (real_time.minute<1) {phase =5; real_time.minute=60; //end
					sprintf(boodsch,"to phase5\r\n"); 
					UARTPrintF (boodsch); 
				}

				break;
			case 5:
				read_display_temp(0); //end no heating, no timer
				sprintf(boodsch,"end\r\n"); 
				UARTPrintF (boodsch); 
				break;

			default:
				break;
		}
	}
}
