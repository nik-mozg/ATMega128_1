#include <avr/io.h>
#define F_CPU 14745600UL //14.7456MHz
#include <avr/interrupt.h>


volatile uint8_t receive = 0;
volatile uint8_t rx_data = 0;
volatile uint8_t rx_flag = 0;

volatile uint8_t first_b;
volatile uint8_t second_b;
volatile uint8_t three_b;

static void UARTInit(void) {//настройка COM порта
	UBRR0H = 0;
	UBRR0L = 95; //baud rate 9600
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); //8 bit, 1 stop bit
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
}
void UARTSend(uint8_t data) {//отправить байт в комп
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}
unsigned char UARTGet() {//принять байт от компа
	while(!rx_flag);
	rx_flag = 0;
	return rx_data;
}

/* Функция инициализация АЦП */
static void ADC_Init(void){
	ADCSRA |= (1 << ADEN) // Включаем АЦП
	|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0); // устанавливаем предделитель преобразователя на 128
	ADMUX |= (0 << REFS1)|(1 << REFS0)|(0 << ADLAR) //выставляем опорное напряжение, как внешний ИОН
	|(0 << MUX0)|(0 << MUX1)|(0 << MUX2)|(0 << MUX3)|(0 << MUX4); // ацп подключен в GND
}

int AD_Converter ()
	{ ADCSRA |= (1 << ADSC);// Начинаем преобразование 
	second_b= ADCL;
	three_b=ADCH;
	}
	


int main(void) {//основная программа
	ADC_Init();
	DDRB=0xFF; 
	DDRE=0xFC;
	uint8_t PRD_VKL_FLAG=0;
	PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(0<<PE5);
	DDRB=0xFF;PORTB= 0x00;
	DDRD = 0x43; PORTD = (1<<PD0)|(1<<PD1)|(1<<PD6);
	UARTInit();// настройка COm порта

	while(1) {
		
			sei();//разрешаем прерывания
		first_b= UARTGet();
		second_b= UARTGet();
		three_b= UARTGet();
		cli(); //запрещаем прерывания
		switch (first_b) {
			case 0b00000001 : //Идентификация приспособления
			{				
			first_b=0b10000001; second_b=0; three_b =0;
			DDRA=0xFF;
			DDRC=0xFF;
			PORTA=0x00;
			PORTC=0x00;
			if (PRD_VKL_FLAG==0){
			PORTD = (1<<PD0)|(1<<PD1)|(1<<PD6);
			PORTB =(0<<PB4)|(0<<PB5)|(0<<PB6)|(0<<PB7);
		
			PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
			PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
			PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
			PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
			PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
			PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
			PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(0<<PE5);
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(0<<PE5);
			}
			else {
				//PORTB =(0<<PB4)|(0<<PB5)|(0<<PB6)|(0<<PB7);
				
				PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
				PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
				PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
				PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
				PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
				PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
				PORTE =(1<<PE3)|(0<<PE4)|(1<<PE2)|(0<<PE5);
				PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(0<<PE5);
				PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(0<<PE5);
			}
			break;
			}
			case 0b00000101 :{ //От ВГ6 в ПК - прием
			DDRA=0x00;
			DDRC=0x00;
			PORTA=0xFF;
			PORTC=0xFF;
			uint8_t povtor=0;
			first_b=0b10001111;
			{
			//sei();//разрешаем прерывания
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			uint8_t second_b_1= PINA;
			uint8_t three_b_1= PINC;
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			uint8_t second_b_2= PINA;
			uint8_t three_b_2= PINC;
			if( (second_b_1==second_b_2)&&(three_b_1==three_b_2))
			{
				//three_b_2>>=6;
				//if (three_b_2!=0)
					{//if (three_b_2!=CNK)
					{
						povtor=1;
						//CNK=three_b_2;
						second_b=second_b_1;three_b=three_b_1;
						first_b=0b10000101;
						
					}
					
				}
				}
			
			}
			
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			break;
			}
			//
			case 0b00001111://остановить считывание с вг6
			{
				first_b=0b10001111;
				second_b=0b10001111;three_b=0b10001111;
				break;
			}
			
			case 0b11001100 : {//От ВГ6 в ПК - прием без фильтрации
			
			DDRA=0x00;
			DDRC=0x00;
			PORTA=0xFF;
			PORTC=0xFF;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(0<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			first_b=0b11101100;
			second_b=PINA; three_b =PINC;
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			break;
			}
			
			case 0b00001001 :{ 	//От ПК в ВГ6 - передача
				
			DDRA=0xFF; PORTA=second_b;
			DDRC=0xFF; PORTC=three_b;
			first_b=0b10001001;
			PORTE =(1<<PE3)|(1<<PE4)|(0<<PE2)|(0<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(0<<PE2)|(0<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(0<<PE2)|(0<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(0<<PE2)|(0<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(0<<PE2)|(0<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(0<<PE2)|(0<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(0<<PE2)|(0<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			PORTE =(1<<PE3)|(1<<PE4)|(1<<PE2)|(1<<PE5) ;
			break;}
			
			
			case 0b11011101 :{ //ВКЛ ПРД осн лу
			first_b=0b11111101; second_b=0;three_b =0;
			PORTB =0x10 ;
			PORTD = (0<<PD0)|(1<<PD1)|(1<<PD6);
			PORTB =0x10 ;
			PRD_VKL_FLAG=1;
			break;}

			case 0b11010001 :{ //ВКЛ ПРД осн рез
			first_b=0b10000111; second_b=0;three_b =0;
			PORTB =0x20 ;
			PORTD = (1<<PD0)|(0<<PD1)|(1<<PD6);
			PORTB =0x20 ;
			PRD_VKL_FLAG=1;
			break;}

			case 0b11010011 :{ //ВКЛ ПРД регламент осн
			first_b=0b10010000; second_b=0;three_b =0;
			PORTB =0x40 ;
			PORTD = (1<<PD0)|(1<<PD1)|(0<<PD6);
			PORTB =0x40 ;
			PRD_VKL_FLAG=1;
			break;}

			case 0b11010010 :{ //ВКЛ ПРД регламент рез
			first_b=0b10001000; second_b=0;three_b =0;
			//PRD_VKL_FLAG=1;
			PORTB =0x80 ;
			PORTD = (1<<PD0)|(1<<PD1)|(0<<PD6);
			PORTB =0x80 ;
			PRD_VKL_FLAG=1;
			break;}
			
			case 0b11010000 :{ //ОТКЛ ПРД
			first_b=0b11110000; second_b=0;three_b =0;
			PORTB =(0<<PB4)|(0<<PB5)|(0<<PB6)|(0<<PB7);
			PORTD = (1<<PD0)|(1<<PD1)|(1<<PD6);
			PRD_VKL_FLAG =0;
			break;}
			
			case  0b00001010 :{ //оцифровать +5 вольт
			first_b=0b10001010;
			ADMUX |= (0 << MUX0)|(0 << MUX1)|(0 << MUX2)|(0 << MUX3)|(0 << MUX4); //
			AD_Converter ();
			break;}

			case  0b00001011 :{ //оцифровать +9 вольт
			first_b=0b10001011;
			ADMUX |= (1 << MUX0)|(0 << MUX1)|(0 << MUX2)|(0 << MUX3)|(0 << MUX4); //
			AD_Converter ();
			break;}

			case  0b00001100 :{ //оцифровать +16 вольт
			first_b=0b10001100;
			ADMUX |= (0 << MUX0)|(1 << MUX1)|(0 << MUX2)|(0 << MUX3)|(0 << MUX4); //
			AD_Converter ();
			break;}

				case  0b00001101 :{ //оцифровать --16 вольт
			first_b=0b10001101;
			ADMUX |= (1 << MUX0)|(1 << MUX1)|(0 << MUX2)|(0 << MUX3)|(0 << MUX4); //
			AD_Converter ();
			break;}

			default :first_b=first_b; second_b=second_b;three_b =three_b;
			}



		UARTSend(first_b);
		UARTSend(second_b);
		UARTSend(three_b);
	}
}

ISR(USART0_RX_vect) {
	rx_data = UDR0;
	rx_flag = 1;}
