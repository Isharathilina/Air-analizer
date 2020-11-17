void transmeet(){
	
	char valaq[4], vallpg[3], valco[3], valds1[4], valds2[4];
	char airdata[]="Airdata::"
	char linebreak[]="\n\r";


	val=(1024-ReadADC(1)); // adc 1 pin connect mq 135
	val -= 70;

	if (val>1023){
		val=1023;  //callibarate
	}
	itoa(val,valaq,10);
	char aq[]=" AQ:";
	strcat(aq,valaq);
	strcat(airdata,aq);





	val=ReadADC(0);   // adc 0 pin connect mq2 lpg
	val -=240;

	if (val<0){
		val=0;  //callibarate
	}
	val=((float)val/1023)*100;
	itoa(val,vallpg,10);
	char lpg[]=" LPG:";
	strcat(lpg,vallpg);
	strcat(airdata,lpg);





	val=ReadADC(4);   // adc 4 pin connect mq 7 co
	val -=450;

	if (val<0){
		val=0;  //callibarate
	}
	val=((float)val/1023)*100;
	itoa(val,valco,10);
	char co[]=" CO:";
	strcat(co,valco);
	strcat(airdata,co);




	val = (d1-ReadADC(2));  //d1
	if (val<0){
		val=0;  //callibarate
	}
	itoa(val,valds1,10);
	char ds1[]=" D1:";
	strcat(ds1,valds1);
	strcat(airdata,ds1);




	val = (d2-ReadADC(3));
	if (val<0){
		val=0;  //callibarate
	}
	itoa(val,valds2,10);
	char ds2[]=" D2:";
	strcat(ds2,valds2);
	strcat(airdata,ds2);
	//-------------------------------------
	
	//--------------------------------

	strcat(airdata,linebreak);

	BtString(airdata);


	
}


void onled(){
	if(co>1||dust1>20||dust2>20||lpg>1){
		
		//printf("red");
		PORTC = (1<<PC0)|(0<<PC1);
		
		
	}else{
		//printf("green");
		PORTC = (0<<PC0)|(1<<PC1);
	}
	
	
	
}


void displayco2(){
	// sensor 1 and air quality
	for(i=0;i<3;i++){ // i for display timing
		
		
		Lcd4_Write_String("CO2  =");
		
		//convertstr(co2);  //add 100 string value to str
		itoa(co2,str,10);
		Lcd4_Write_String(str);
		Lcd4_Write_String("%");
		
		
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String("NH3 =");
		
		
		
		
		
		
		//itoa(ReadADC(5),str,10);
		itoa(co2,str,10);
		convertstr(me);  //add 100 string value to str
		Lcd4_Write_String(str);
		Lcd4_Write_String("%");
		
		
		
		
		_delay_ms(500);
		Lcd4_Clear();
		i++;
	}
	
	
	
}