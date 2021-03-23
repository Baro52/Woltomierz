/*
 * _7_seg.c
 *
 * Created: 31.01.2021 12:29:36
 * Author: Bartlomiej Berling
 *
 *	Odczyt wartosci 0-5V i wyswietlenie jej na wysiwtlaczu 7-seg
 *
 * Ustawienia SimulIDE: max natezenie 7seg ustawione na 0.005A, taktowanie na 16MHz
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

uint8_t konwerter_na_7_seg(uint8_t cyferka);
uint8_t konwersja_ADC_na_cyfry(uint8_t bit_8_read, uint8_t nr_cyfry);

int main(void)
{
	uint8_t volt;
	
	ADMUX |= 0x01;					//deklaracja ADC na pinie A1 (ADC1), napiecie odniesienia AREF
	ADMUX |= 0x01 << ADLAR;			//wyrownanie do lewej wartosci 10-bitowych	
	ADCSRA = 0xe7;					//wlaczenie odczyty z przetwornika
	
	DDRA=0xF0;
	DDRC=0xFF;
	DDRD=0xFF;
    while(1)
    {	
			ADCSRA |= 0x01 << ADSC;		
			volt=ADCH;
			for(uint8_t i=0;i<50;i++)
			{
				PORTD=0x7E;			//port  d7 do masy piersza cyfra
				PORTC = 0x01;		//dodanie 1 na ostatni bit, jako DP
				PORTC |= konwerter_na_7_seg(konwersja_ADC_na_cyfry(volt, 0));
				_delay_ms(5);
				PORTD=0xBF;		//port d6 do masy druga cyfra	
				PORTC = konwerter_na_7_seg(konwersja_ADC_na_cyfry(volt, 1));
				_delay_ms(5);
				PORTD=0xDF;		//port d5 do masy trzecia cyfra
				PORTC = konwerter_na_7_seg(konwersja_ADC_na_cyfry(volt, 2));
				_delay_ms(5);
				PORTD=0xEF;		//port d4 do masy czwarta cyfra
				PORTC = konwerter_na_7_seg(konwersja_ADC_na_cyfry(volt, 3));
				_delay_ms(5);
			}
    }
	return 0;
}

//funkcja zmianiajaca cyfry dziesietne na wysiwtlane cyfry
uint8_t konwerter_na_7_seg(uint8_t cyferka)
{
	uint16_t kodhex;
	switch(cyferka)
	{
	case 0:
	{
		kodhex=0xFC;
	}
	break;
	case 1:
	{
		kodhex=0x60;
	}
	break;
	case 2:
	{
		kodhex=0xDA;
	}
	break;
	case  3:
	{
		kodhex=0xF2;
	}
	break;
	case 4:
	{
		kodhex=0x66;
	}
	break;
	case 5:
	{
		kodhex=0xB6;
	}
	break;
	case 6:
	{
		kodhex=0xBE;
	}
	break;
	case 7:
	{
		kodhex=0xE0;
	}
	break;
	case 8:
	{
		kodhex=0xFE;
	}
	break;
	case 9:
	{
		kodhex=0xF6;
	}
	break;
	default:
	{
		kodhex =0xFF;
	}
	}
	return kodhex;
}
	
//funkcja zamieniajaca odczyt z ADC na posczegolne 4 cyfry, przy okazji mapowanie 8bitow na warosc 0-5000
uint8_t konwersja_ADC_na_cyfry(uint8_t bit_8_read, uint8_t nr_cyfry)
{
	uint8_t rozbity_odczyt;
	uint32_t analog_read=(uint32_t)bit_8_read*5000UL/255UL;			//dodaje wszedzie typ UL bo nie rozumiem dlaczego kompilator wyrzuca blad, pomimo ze zmienna ma 4Bajty
	switch(nr_cyfry)
	{
		case 0:return rozbity_odczyt=analog_read/1000UL; break;
		case 1:return rozbity_odczyt=analog_read%1000UL/100UL; break;
		case 2:return rozbity_odczyt=analog_read%100UL/10UL; break;
		case 3:return rozbity_odczyt=analog_read%10UL/1UL; break;
		default:return 0;
	}
	
}