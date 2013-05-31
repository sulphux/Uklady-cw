#define RS 0b00000001
#define E 0b00000010
#define UNUSED 0b00001100
#define F_CPU 16000000UL

#include <avr/io.h>
#include <delay.h>

void SendLoByte ( uint8_t data )
{
    PORTA |= E;
    PORTA = (PORTA&(RS|UNUSED)) | E | (data<<4 & 0xF0);
    PORTA &= ~E;

}
void SendHiByte ( uint8_t data )
{
    PORTA |= E;
    PORTA = (PORTA&(RS|UNUSED)) | E | (data & 0xF0);
    PORTA &= ~E;
}

void SendByte ( uint8_t data )
{
	_delay_ms(1);
    SendHiByte(data);
    SendLoByte(data);
}

void SendDataByte (uint8_t data)
{
    PORTA |= 1;
    SendByte(data);
}

void SendCmdByte( uint8_t data )
{
    PORTA &= ~RS;
    SendByte(data);
}


void InitScreen()
{
        _delay_ms(50);
        PORTA = PORTA & (~RS);
        int i;
        for(i = 0; i<3;i++)
        {
            SendLoByte(0x03);
            _delay_ms(5);
        }
        SendLoByte(0x02);
        _delay_ms(5);
        SendCmdByte(40);
        SendCmdByte(0x08);
        SendCmdByte(0x01);
        _delay_ms(5);
        SendCmdByte(0x06);
        _delay_ms(50);
        SendCmdByte(0x0F);
        SendCmdByte(0x80);
}

void WriteText(char * napis)
{
    while(*napis){
                SendDataByte(*napis);
                napis++;
        }
}



int main(void)
{
	DDRA = 0xFF;
	InitScreen();
    while(1)
    {
        //TODO:: Please write your application code
    }
}
