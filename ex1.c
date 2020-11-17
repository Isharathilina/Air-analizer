

GetsensorVal(){
	
	
	val=(1024-ReadADC(1)); // adc 1 pin connect mq 135
	val += 100;
	
	if (val>1023){
		val=1023;  //callibarate
	}
	aq=val;
	
	
	//-----------------
	
	val=ReadADC(0);   // adc 0 mq2 lpg pin connect
	val -=150;
	
	if (val<0){
		val=0;  //callibarate
	}
	lpg= val;
	
	//-----------------------------------------------------------------------------------------------------------------------------
	
	val=ReadADC(4);   // adc 4 pin connect mq 7
	val -=450;
	
	if (val<0){
		val=0;  //callibarate
	}
	co=val;
	
	//--------------------
	
	
	
	val = ReadADC(5);  // a5 connect to n2 sensor
	val +=592;
	if (val<0){
		val=0;  //callibarate
	}
	if (val>737)
	{ val= 737;
	}
	if (val<720)
	{ val = 720;
	}
	n2=val;
	
	//--------------------
	
		val = (ReadADC(2)-d1);
		if (val<0){
			val=0;  //callibarate
		}
		dust1= val;
		
	//---------------
	
	
	val = (ReadADC(3)-d2);
	if (val<0){
		val=0;  //callibarate
	}
	
	dust2=val;
	
		
	
	
	
	
	
	
}

char getkey(){
	st:
	char a = scan_for_key();
	if (a=='N')
	{
		goto:st;
	}else{
		return a;
	}
	
	
}