#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int count;
int multi;

int read_LCD_buttons()
{
  adc_key_in = analogRead(0);
  
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT;
  
  return btnNONE;
  
}

void setup()
{
  // Declare the name here
  char name[] = "Deoxys";
  
  // If you want to change what count value you start with
  count = 0;
  
  // If you want to change what multiplier you start with
  multi = 1;
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print(name);
  lcd.setCursor(14,0);
  char t = multi + '0';
  lcd.print(t);
  lcd.print('x');
  lcd.setCursor(0,1);
  lcd.print(count);
}

void updateMulti(int n)
{
  if (n == 1 && multi < 9)
  {
    multi += 1; 
  } else if (n == 2 & multi > 1)
  {
    multi -= 1;
  } 
  
  lcd.setCursor(14,0);
  char t = multi + '0';
  lcd.print(t);
  lcd.print('x');
}

void updateCount(int n)
{
  int num = 1 * multi;
  
  if (n == 1)
  {
    count += num;
  } else if (count - num >= 0)
  {
    count -= num;
  } else {
    count = 0;
  }
  
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print(count);
}

void save()
{
  // Add some day, https://www.arduino.cc/en/Reference/EEPROM
  // Becareful because the memory only has ~100,000 read/write cycles
}

void loop()
{
  int lcdkey = read_LCD_buttons();
  
  lcd.setCursor(0,1);
  
  switch(lcdkey)
  {
    case btnUP:
    {
      updateCount(1);
      break;
    }
    case btnDOWN:
    {
      updateCount(2);
      break;
    }
    case btnLEFT:
    {
      updateMulti(2);
      break;
    }
    case btnRIGHT:
    {
      updateMulti(1);
      break;
    }
    case btnSELECT:
    {
      save();
      break;
    }
    case btnNONE:
    {
      break;
    }
  }
  
  // Makes the buttons much more manageable. Instead they'd be going up way too fast for normal people.
  delay(100);
}
