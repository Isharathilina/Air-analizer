/*
a0= mq2 h2/ lpg
a1= mq 135 with ground 47k
a2 dust sensor 1 ground with 1k
a3 and dust sensor 2 ground with 1k
a4 =mq7 Carbon Monoxide
a5 = n2 sensor

b0 preparing cancel btn g 47k
b1 mode change button g4 47k

c0 red led
c1 green led

min reset 9 + avcc 30 +




*/

# define F_CPU 1000000UL

#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include "lcd.h"


int i,val, d1,d2,fd1,fd2;
int aq,n2,co,lpg,o2,dust1,dust2;
int co2,ch4;
char str[4];
// adc funfion ***************************************

void InitADC()
{
	ADMUX=(1<<REFS0);									// For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	// Prescalar div factor =128
}

uint16_t ReadADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX&=0b11100000;
	ADMUX|=ch;

	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA|=(1<<ADIF);

	return(ADC);
}

//end adc funtion ************************************
//welcome text 
void welcome(){
	    Lcd4_Set_Cursor(1,1);
	    Lcd4_Write_String("....WELCOME....");
	    _delay_ms(2000);
	    Lcd4_Set_Cursor(2,1);
	    Lcd4_Write_String(".Air Analyzer.");
	    _delay_ms(3000);
	    
		initdust();    // start dust sensor
		
	    Lcd4_Clear();
	    Lcd4_Set_Cursor(1,2);
	    Lcd4_Write_String("GROUP 16 (ITM)");
	    _delay_ms(2000);
	    Lcd4_Clear();
	    
	    
	    
	    Lcd4_Set_Cursor(1,1);
	    Lcd4_Write_String("Preparing Gas Sensors");
	    Lcd4_Set_Cursor(2,4);
	    Lcd4_Write_String("Please wait..");
	    for(i=0;i<6;i++)
	    {
		    _delay_ms(300);
		    Lcd4_Shift_Left();
	    }
	    for(i=0;i<6;i++)
	    {
		    _delay_ms(300);
		    Lcd4_Shift_Right();
	    }
	    
	    Lcd4_Clear();
	    
	    for(i=0; i<101;i++){   //shoud be change to 101
		    itoa(i,str,10);     // int to string
		    Lcd4_Write_String("Preparing Sensors");
		    Lcd4_Set_Cursor(2,6);
		    Lcd4_Write_String("(");
		    Lcd4_Write_String(str);
		    Lcd4_Write_String(")%");
		    _delay_ms(2000);        // time ajust
		    Lcd4_Clear();
			
			if (PINB & 0x01)                           //if  press button
			{
				Lcd4_Set_Cursor(1,3);
				Lcd4_Write_String("preparing");
				Lcd4_Set_Cursor(2,4);
				Lcd4_Write_String("Canceled");
				 _delay_ms(1000);
				 break;
			}
			
	    }
	   
}  
//analyze text
void analyze(){
	
	//analize

	Lcd4_Clear();
	Lcd4_Set_Cursor(1,3);
	Lcd4_Write_String("Analyzing");
	Lcd4_Set_Cursor(2,0);
	for(i=0; i<16;i++){
		Lcd4_Write_Char('*');
		_delay_ms(300);
	}
	Lcd4_Clear();
	
}

void convertstr(int a){
	unsigned int b;
	b=((float)a/1023)*100;
	itoa(b,str,10);	
}

void s1s2(){
	// sensor 1 and air quality
	for(i=0;i<4;i++){ // i for display timing
		
		
		Lcd4_Write_String("Air Quality =");
		val=(1024-ReadADC(1)); // adc 1 pin connect mq 135
		val -= 70;	
		
		if (val>1023){
			val=1023;  //callibarate
		}	
		convertstr(val);  //add 100 string value to str
		Lcd4_Write_String(str);
		Lcd4_Write_String("%");
		
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String("LPG/H2 =");
		val=ReadADC(0);   // adc 0 mq2 pin connect
		val -=200;    
		
		if (val<0){
			val=0;  //callibarate
		}
		   
		convertstr(val);  //add 100 string value to str
		Lcd4_Write_String(str);
		Lcd4_Write_String("%");
		
		
		
		_delay_ms(500);
		Lcd4_Clear();
		i++;
	}
	
	
	
}

void displayco(){
	// sensor 1 and air quality
	for(i=0;i<3;i++){ // i for display timing
		
		
		Lcd4_Write_String("CO =");
		val=ReadADC(4);   // adc 4 pin connect mq 7
		val -=450;
		
		if (val<0){
			val=0;  //callibarate
		}
		
		convertstr(val);  //add 100 string value to str
		//itoa(val,str,10);
		Lcd4_Write_String(str);
		Lcd4_Write_String("%");
		
		
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String("N2 =");
		
		
		val = ReadADC(5);  // a5 connect to n2 sensor
		val +=592;
		if (val<0){
			val=0;  //callibarate
		}
		if (val>808)
		{ val= 808;
		}
		if (val<788)
		{ val = 788;
		}
		
		convertstr(val);  //add 100 string value to str
		Lcd4_Write_String(str);
		Lcd4_Write_String("%");
		
		
		
		
		_delay_ms(500);
		Lcd4_Clear();
		i++;
	}
	
	
	
}



void displayco2me(){
	// sensor 1 and air quality
	for(i=0;i<3;i++){ // i for display timing
		
		
		Lcd4_Write_String("CO2 =");
		//val=ReadADC(4);   // adc 4 pin connect mq 7
		//val -=450;
		
		//if (val<0){
		//	val=0;  //callibarate
		//}
		
		convertstr(co2);  //add 100 string value to str
		//itoa(val,str,10);
		Lcd4_Write_String(str);
		Lcd4_Write_String("%");
		
		
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String("O2 =");
		
		/*
		val = ReadADC(5);  // a5 connect to n2 sensor
		val +=592;
		if (val<0){
			val=0;  //callibarate
		}
		if (val>808)
		{ val= 808;
		}
		if (val<788)
		{ val = 788;
		}
		*/
	itoa(o2,str,10);
		//convertstr(o2);  //add 100 string value to str
		Lcd4_Write_String(str);
		Lcd4_Write_String("%");
		
		
		
		
		_delay_ms(500);
		Lcd4_Clear();
		i++;
	}
	
	
	
}


void displaydust(){    // display dust levels
	
		//for (i=0;i<7;i++){
			
		Lcd4_Write_String("Dust condition");
		_delay_ms(300);
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String("D1 level:- ");
		val = (d1-ReadADC(2));
		if (val<0){
			val=0;  //callibarate
		}
		itoa(dust1,str,10);	
		Lcd4_Write_String(str);
		_delay_ms(500);
		Lcd4_Clear();
		// end d1
		
		Lcd4_Write_String("Dust condition");
		_delay_ms(300);
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String("D2 level:- ");
		val = (d2-ReadADC(3));
		if (val<0){
			val=0;  //callibarate
		}
		itoa(dust2,str,10);
		Lcd4_Write_String(str);
		_delay_ms(500);
		Lcd4_Clear();
		
	/*	Lcd4_Clear();
		Lcd4_Write_String("Dust condition");
		_delay_ms(300);
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String("S2 level:- ");
		convertstr(d2-ReadADC(3));
		Lcd4_Write_String(str);
		_delay_ms(3000);
		
		*/
			
		//}
}
void initdust(){
	d1=ReadADC(2); // read dust sensror vales 
	d2=ReadADC(3);
	
}

void transmeet(){
	
	char valaq[3], vallpg[3], valco[3], valds1[4], valds2[4], valn2[3], pr[]="%";
	char airdata[55]=">";
	char linebreak[]="\n\r";


	val=(1024-ReadADC(1)); // adc 1 pin connect mq 135
	val -= 70;

	if (val>1023){
		val=1023;  //callibarate
	}
	aq=((float)val/1023)*100;
	itoa(aq,valaq,10);
	
	char aq1[]="AQ:";
	strcat(aq1,valaq);
	strcat(airdata,aq1);



	val=ReadADC(0);   // adc 0 pin connect mq2 lpg
	val -=200;

	if (val<0){
		val=0;  //callibarate
	}
	lpg=((float)val/1023)*100;
	itoa(lpg,vallpg,10);
	char lpg1[]=" LPG:";
	strcat(lpg1,vallpg);
	strcat(lpg1,pr);
	strcat(airdata,lpg1);
	
	
	val=ReadADC(4);   // adc 4 pin connect mq 7 co
	val -=450;

	if (val<0){
		val=0;  //callibarate
	}
	co=((float)val/1023)*100;
	itoa(co,valco,10);
	char co1[]=" CO:";
	strcat(co1,valco);
	strcat(co1,pr);
	strcat(airdata,co1);
	
	
	
	val = ReadADC(5);  // a5 connect to n2 sensor
	val +=592;
	if (val<0){
		val=0;  //callibarate
	}
	if (val>808)
	{ val= 808;
	}
	if (val<788)
	{ val = 788;
	}
	n2=((float)val/1023)*100;
	itoa(n2,valds1,10);
	char ds11[]=" N2:";
	strcat(ds11,valds1);
	strcat(ds11,pr);
	strcat(airdata,ds11);

//---------------o2 calculation

	int a,b;
	a=co+lpg;
	b=n2+a;
	o2= (100-b);

	
	itoa(o2,valds1,10);
	char ds1s[]=" O2:";
	strcat(ds1s,valds1);
	strcat(airdata,ds1s);

//------------------------------

	val = (ReadADC(3)-d2);  //d1 dust 1
	if (val<0){
		val=0;  //callibarate
	}
	dust1=val;
	itoa(val,valds1,10);
	char ds1[]=" D1:";
	strcat(ds1,valds1);
	strcat(airdata,ds1);


//-------------------------------


	val = (ReadADC(3)-d2); //2 dust 2
	if (val<0){
		val=0;  //callibarate
	}
	dust2=val;
	itoa(val,valds2,10);
	char ds2[]=" D2:";
	strcat(ds2,valds2);
	strcat(airdata,ds2);
//-------------------------------------

val=ReadADC(1);   // adc 4 pin connect mq 7 co2 //f1


if (val<0){
	val=0;  //callibarate
}
if (val>1)
{val=1;
	o2=o2-1;
}
co2=0;
itoa(val,valco,10);


char co2[]=" CO2:";
strcat(co2,valco);
strcat(co2,"%");
strcat(airdata,co2);


//----------------------------
	strcat(airdata,linebreak);
	BtString(airdata);
	
	


	
}


void USARTInit(uint16_t ubrr_value)
{
	//Set Baud rate
	UBRRL = ubrr_value;
	UBRRH = (ubrr_value>>8);
	UCSRA = (1<<U2X); // its double
	UCSRC=(1<<URSEL)|(3<<UCSZ0);
	//Enable The receiver and transmitter
	UCSRB=(1<<RXEN)|(1<<TXEN);
}

char BtReadChar(){
	while(!(UCSRA & (1<<RXC)))
	{
	}
	return UDR;
}


void BtWriteChar(char data){
	while(!(UCSRA & (1<<UDRE)))
	{
	}
	UDR=data;
}

void BtString(char *str){
	int i;
	for(i=0; ; i++){
		if(str[i]=='\0')
		break;
		BtWriteChar(str[i]);
	}
}

void onled(){
	if(co>1||dust1>100||dust2>100||lpg>1){
		
		//printf("red");
		PORTC = (1<<PC0)|(0<<PC1);
		
		
		}else{
		//printf("green");
		PORTC = (0<<PC0)|(1<<PC1);
	}
	
	
	
}

int main(void){
    
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0x00;  //for get cansel butten inputs
	PORTB = 0x00;  // pb0 pull down for button
Lcd4_Init();
InitADC();
USARTInit(12);
	
	 welcome(); 
	 analyze();
	 //initdust();
	// _delay_ms(3000);
	 
	 int mode = 0;

	while(1){
		
		transmeet();
		onled();
		
		if (PINB & 0x02)
		{
			if (mode==0)
			{
				Lcd4_Write_String("System change to");
				Lcd4_Set_Cursor(2,5);
				Lcd4_Write_String("Gas mode");
				_delay_ms(2000);
				 Lcd4_Clear();
			}
			s1s2();
			displayco();
			displayco2me();
			mode =1;
		}else{
			
			if (mode==1)
			{
				Lcd4_Write_String("System change to");
				Lcd4_Set_Cursor(2,3);
				Lcd4_Write_String("Dust mode");
				_delay_ms(2000);
				Lcd4_Clear();
			}
			
			displaydust();
			mode = 0;
		}
	
	
	
	
		 
		
		
		}
		
		
	//  itoa(val,str,10); 	
	//	Lcd4_Set_Cursor(1,1);
	//	Lcd4_Write_Char('5');
	//  Lcd4_Clear();
	//	_delay_ms(2000);
	//Lcd4_Write_String("Adc is =");
	}
  