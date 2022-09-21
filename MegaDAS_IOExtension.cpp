#include"MegaDAS_IOExtension.h"               


IOExtension::IOExtension(int SH_CP,int DS,int ST_CP,int IN_P)
{	
				
	shift_clock=SH_CP;
	data=DS;
	store_clock=ST_CP;
	this->IN_P=IN_P;
	commandePinOM=0x00;
	commandePinOL=0x00;
	commandePinI=0x00;
	
				
	pinMode(shift_clock,OUTPUT);
	pinMode(data,OUTPUT);
	pinMode(store_clock,OUTPUT);
	pinMode(IN_P,INPUT);
	
			
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	SPI.begin();
}

IOExtension::~IOExtension()
{
	
}
  
void IOExtension::DigitalWrite(int pin,bool state)
{
	if(pin<9)                               
	  if(state!=0)                          
	  {
		bitWrite(commandePinOL,pin-1,1);    
	  }
	  else                                  
	  {
		bitWrite(commandePinOL,pin-1,0);    
	  }
  }
  else                                      
  {
	if(state!=0)
	{
		bitWrite(commandePinOM,pin-9,1);
	}
	else
	{
		bitWrite(commandePinOM,pin-9,0);
	}  
  }
                                        
	SPI.transfer(commandePinOM);          
	SPI.transfer(commandePinOL);            
	SPI.transfer(commandePinI);           
	SPI.transfer(commandePinI);            
	digitalWrite(store_clock,HIGH);        
	digitalWrite(store_clock,LOW);
}

{
										
	SPI.transfer(commandePinOM);            
	SPI.transfer(commandePinOL);            
	digitalWrite(store_clock,HIGH);         
	digitalWrite(store_clock,LOW);
	
	if(pin<9)                               
  {
    SPI.transfer(commandePinI);             
    digitalWrite(store_clock,HIGH);         
    digitalWrite(store_clock,LOW);
    bitWrite(commandePinI,pin-1,1);
    SPI.transfer(commandePinI);             
    digitalWrite(store_clock,HIGH);         
    digitalWrite(store_clock,LOW);
  }
  else                                      
  {
    bitWrite(commandePinI,pin-9,1);
    SPI.transfer(commandePinI);
    digitalWrite(store_clock,HIGH);
    digitalWrite(store_clock,LOW);
	commandePinI=0x00;
    SPI.transfer(commandePinI);
    digitalWrite(store_clock,HIGH);
    digitalWrite(store_clock,LOW);
  }
  commandePinI=0x00;                        
  delayMicroseconds(500);                  
  if(digitalRead(IN_P))                    
    return true;                            
  else
    return false;                           
}
