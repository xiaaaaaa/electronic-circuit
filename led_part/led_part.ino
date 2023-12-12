#include <BluetoothSerial.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 		//設定OLED螢幕的寬度像素
#define SCREEN_HEIGHT 64  		//設定OLED螢幕的寬度像素
#define OLED_RESET -1 			 //Reset pin如果OLED上沒有RESET腳位,將它設置為-1
#define NUMFLAKES     10 // Number of snowflakes in the animation example
BluetoothSerial SerialBT; 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);   	//OLED顯示器使用2C連線並宣告名為display物件
bool OLEDStatus = true;
int welcomeState = 0;//welcome
int levelState = 1;//LEVEL

/*恭*/
static const unsigned char PROGMEM str_1[]={
0x01,0xC3,0x80,0x01,0xC3,0x80,0x01,0xC3,0x80,0x01,0xC3,0x80,0x1F,0xFF,0xFC,0x1F,
0xFF,0xFC,0x01,0xC3,0x80,0x01,0xC3,0x80,0x01,0xC3,0x80,0x7F,0xFF,0xFE,0x7F,0xFF,
0xFE,0x01,0xC3,0x80,0x03,0x99,0xC0,0x07,0x18,0xF0,0x1E,0x18,0x7C,0x3C,0x18,0x3E,
0x79,0x1E,0x6E,0x23,0x9F,0x70,0x03,0x1B,0x38,0x07,0x19,0xB8,0x0E,0x19,0x9C,0x1C,
0x19,0xDC,0x04,0x78,0x00,0x00,0x78,0x00,
};
/*喜*/
static const unsigned char PROGMEM str_2[]={		
0x00,0x1C,0x00,0x00,0x1C,0x00,0x3F,0xFF,0xFE,0x3F,0xFF,0xFE,0x00,0x1C,0x00,0x00,
0x1C,0x00,0x1F,0xFF,0xF8,0x1F,0xFF,0xF8,0x00,0x00,0x00,0x07,0xFF,0xE0,0x07,0xFF,
0xE0,0x07,0x00,0xE0,0x07,0xFF,0xE0,0x07,0xFF,0xE0,0x01,0x81,0x80,0x7F,0xFF,0xFE,
0x7F,0xFF,0xFE,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x0F,0xFF,0xF0,0x0E,0x00,0x70,0x0E,
0x00,0x70,0x0F,0xFF,0xF0,0x0F,0xFF,0xF0,
};
/*解*/
static const unsigned char PROGMEM str_5[]={
0x04,0x00,0x00,0x0E,0x00,0x00,0x0E,0x0F,0xFC,0x1F,0xEF,0xFC,0x1F,0xE1,0x8C,0x38,
0xC1,0x8C,0x71,0x83,0x8C,0x7F,0xF3,0x0C,0x7F,0xF7,0x3C,0x7B,0x7E,0x38,0x3B,0x74,
0x00,0x3B,0x72,0x70,0x3F,0xF3,0x70,0x3F,0xF7,0xFE,0x3B,0x77,0xFE,0x3B,0x7E,0x70,
0x3F,0xFC,0x70,0x3F,0xF0,0x70,0x33,0x77,0xFE,0x33,0x77,0xFE,0x33,0x70,0x70,0x73,
0x70,0x70,0x60,0xF0,0x70,0x60,0xF0,0x70,
};
/*密*/
static const unsigned char PROGMEM str_6[]={
0x00,0x1C,0x00,0x00,0x1C,0x00,0x7F,0xFF,0xFE,0x7F,0xFF,0xFE,0x70,0x60,0x0E,0x70,
0x70,0x8E,0x70,0x39,0xCE,0x00,0x1D,0xC0,0x0D,0xC3,0x90,0x0D,0xC7,0x38,0x1D,0xDE,
0x1C,0x19,0xF8,0xCE,0x09,0xF0,0xE4,0x07,0xFF,0xC0,0x7F,0xFF,0xC0,0x7C,0xFF,0x00,
0x20,0x1C,0x00,0x0E,0x1C,0x38,0x0E,0x1C,0x38,0x0E,0x1C,0x38,0x0E,0x1C,0x38,0x0F,
0xFF,0xF8,0x0F,0xFF,0xF8,0x0E,0x00,0x38,
};
/*成*/
static const unsigned char PROGMEM str_7[]={
0x00,0x0E,0x20,0x00,0x0E,0x70,0x00,0x0E,0x38,0x00,0x06,0x30,0x0F,0xFF,0xFE,0x0F,
0xFF,0xFE,0x0F,0xFF,0xFE,0x0C,0x06,0x00,0x0C,0x06,0x30,0x0C,0x06,0x38,0x0F,0xF7,
0x38,0x0F,0xF7,0x70,0x1C,0x77,0x70,0x1C,0x73,0x60,0x1C,0x73,0xE0,0x1C,0x63,0xE0,
0x1C,0x61,0xC0,0x1B,0xE3,0xC0,0x39,0xE3,0xC4,0x39,0x8F,0xE6,0x70,0x1E,0x7E,0x70,
0x7C,0x3E,0x60,0x38,0x1E,0x00,0x00,0x00,
};
/*功*/
static const unsigned char PROGMEM str_8[]={
0x00,0x03,0x80,0x00,0x03,0x80,0x00,0x03,0x80,0x00,0x03,0x80,0x3F,0xE3,0x80,0x3F,
0xE3,0x80,0x3F,0xFF,0xFE,0x07,0x1F,0xFE,0x07,0x1F,0xFE,0x07,0x03,0x8E,0x07,0x03,
0x8C,0x07,0x03,0x8C,0x07,0x03,0x8C,0x07,0x03,0x8C,0x07,0x03,0x0C,0x07,0x03,0x0C,
0x07,0xE7,0x1C,0x0F,0xE7,0x1C,0x7F,0xCE,0x1C,0x7E,0x0E,0x1C,0x30,0x1C,0x1C,0x00,
0x3C,0xFC,0x00,0xF8,0xF8,0x00,0xF0,0xF8
};
void showWelcome(){
  display.clearDisplay();   		//清除緩衝區資料
  display.setCursor(0,0);     			//設定起始點位置(50,35)
  display.setTextColor(WHITE); 			//設定文字顏色為白色(亮點)
  display.setTextSize(3);      				//設定文字尺寸為2
  display.println("Welcome");    			//將"0.0"存入RAM
  display.display();   					//顯示所設定的文字
}
void showLevel1(){
  display.clearDisplay();   		//清除緩衝區資料
  display.setCursor(0,0);     			//設定起始點位置(50,35)
  display.setTextColor(WHITE); 			//設定文字顏色為白色(亮點)
  display.setTextSize(3);      				//設定文字尺寸為2
  display.println("Level 1");    			//將"0.0"存入RAM
  display.display();   					//顯示所設定的文字
}
void showLevel2(){
  display.clearDisplay();   		//清除緩衝區資料
  display.setCursor(0,0);     			//設定起始點位置(50,35)
  display.setTextColor(WHITE); 			//設定文字顏色為白色(亮點)
  display.setTextSize(3);      				//設定文字尺寸為2
  display.println("Level 2");    			//將"0.0"存入RAM
  display.display();   					//顯示所設定的文字
}
void showLevel3(){
  display.clearDisplay();   		//清除緩衝區資料
  display.setCursor(0,0);     			//設定起始點位置(50,35)
  display.setTextColor(WHITE); 			//設定文字顏色為白色(亮點)
  display.setTextSize(3);      				//設定文字尺寸為2
  display.println("Level 3");    			//將"0.0"存入RAM
  display.display();   					//顯示所設定的文字
}
void showLevel4(){
  display.clearDisplay();   		//清除緩衝區資料
  display.setCursor(0,0);     			//設定起始點位置(50,35)
  display.setTextColor(WHITE); 			//設定文字顏色為白色(亮點)
  display.setTextSize(3);      				//設定文字尺寸為2
  display.println("Level 4");    			//將"0.0"存入RAM
  display.display();   					//顯示所設定的文字
}
void showLevel5(){
  display.clearDisplay();   		//清除緩衝區資料
  display.setCursor(0,0);     			//設定起始點位置(50,35)
  display.setTextColor(WHITE); 			//設定文字顏色為白色(亮點)
  display.setTextSize(3);      				//設定文字尺寸為2
  display.println("Level 5");    			//將"0.0"存入RAM
  display.display();   					//顯示所設定的文字
}
void showcongrat(){
  display.clearDisplay();   		//清除緩衝區資料
  //恭喜解密成功
  display.drawBitmap(0,	0,	str_1,	24,	24,	WHITE);		//恭,位置(  0,0)字型大小24*24顏色白色
  display.drawBitmap(25,	0,	str_2,	24,	24,	WHITE);		//喜,位置(18,32)字型大小24*24顏色白色
  display.drawBitmap(50,	0,	str_5,	24,	24,	WHITE);		//解,位置(36,32),字型大小24*24顏色自色
  display.drawBitmap(75,	0,	str_6,	24,	24,	WHITE);		//密,位置(54,32),字型大小24*24,顏色白色
  display.drawBitmap(0,26,	str_7,	24,	24,	WHITE);		//成,位置(36,32),字型大小24*24顏色自色
  display.drawBitmap(25, 26,	str_8,	24,	24,	WHITE);		//功,位置(54,32),字型大小24*24,顏色白色
  //0.0
  display.setCursor(50,35);     			//設定起始點位置(50,26)
  display.setTextColor(WHITE); 			//設定文字顏色為白色(亮點)
  display.setTextSize(2);      				//設定文字尺寸為3
  display.println("0.0");    			//將"0.0"存入RAM
  display.display();   					//顯示所設定的文字
}
void showWrong(){
  display.clearDisplay();   		//清除緩衝區資料
  display.setCursor(0,0);     			//設定起始點位置(50,35)
  display.setTextColor(WHITE); 			//設定文字顏色為白色(亮點)
  display.setTextSize(3);      				//設定文字尺寸為2
  display.println("YOU'RE");    			//將"0.0"存入RAM
  display.setCursor(0,35);     			//設定起始點位置(50,35)
  display.setTextColor(WHITE); 			//設定文字顏色為白色(亮點)
  display.setTextSize(3);      				//設定文字尺寸為2
  display.println("WRONG!!");    			//將"0.0"存入RAM
  display.display();   					//顯示所設定的文字
}
void showWelldone(){
  display.clearDisplay();   		//清除緩衝區資料
  display.setCursor(0,0);     			//設定起始點位置(50,35)
  display.setTextColor(WHITE); 			//設定文字顏色為白色(亮點)
  display.setTextSize(2);      				//設定文字尺寸為2
  display.println("Welldone!");    			//將"0.0"存入RAM
  display.display();   					//顯示所設定的文字
}
//星星動畫
#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}


void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");//更改為設定的藍牙顯示名稱
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3c)) {     	 //設定位址為 0x3c
    Serial.println(F("SSD1306 allocation falled"));		  	 //F(字串):將字串儲存在fash並非在RAM
    OLEDStatus = false;  								 //開啟OLED失敗
  }
}

void loop() {
  String value;
  if(OLEDStatus==true) {
    if(welcomeState==0){//遊戲開始
      showWelcome();
      delay(5000);
      welcomeState = 1;
    }
    //Level1
    if(levelState==1){
      showLevel1();
      if (SerialBT.available()) {//判斷儲存格是否有字串
        value = SerialBT.readString();//讀值
        if(value == "sus"){//正確
          if(OLEDStatus==true) {
            showcongrat();
            levelState = 2;
            delay(3000);
            }
        }
        else{//錯誤
          if(OLEDStatus==true) {
            showWrong();
            delay(3000);
          }
        }
        Serial.flush();//清空目前儲存格內容
      }
    }
    //Level2
    if(levelState==2){
      showLevel2();
      if (SerialBT.available()) {
        value = SerialBT.readString();
        if(value == "meiji"){//正確
          if(OLEDStatus==true) {
            showcongrat();
            levelState = 3;
            delay(3000);
          }
        }
        else{//錯誤
          if(OLEDStatus==true) {
            showWrong();
            delay(3000);
          }
        }
        Serial.flush();
      }
    }
    //Level3
    if(levelState==3){
      showLevel3();
      if (SerialBT.available()) {
        value = SerialBT.readString();
        if(value == "ikea"){//正確
          if(OLEDStatus==true) {
            showcongrat();
            levelState = 4;
            delay(3000);
          }
        }
        else{//錯誤
          if(OLEDStatus==true) {
            showWrong();
            delay(3000);
          }
        }
        Serial.flush();
      }
    }
    //Level4--gay
    if(levelState==4){
      showLevel4();
      if (SerialBT.available()) {
        value = SerialBT.readString();
        if(value == "gay"){//正確
          if(OLEDStatus==true) {
            showcongrat();
            levelState = 5;
            delay(3000);
          }
        }
        else{//錯誤
          if(OLEDStatus==true) {
            showWrong();
            delay(3000);
          }
        }
        Serial.flush();
      }
    }
    //Level5
    if(levelState==5){
      showLevel5();
      if (SerialBT.available()) {
        value = SerialBT.readString();
        if(value == "cloc"){//成功
          if(OLEDStatus==true) {
            showcongrat();
            levelState = 6;
            delay(3000);
          }
        }
        else{//錯誤
          if(OLEDStatus==true) {
            showWrong();
            delay(3000);
          }
        }
        Serial.flush();
      }
    }
    if(levelState == 6){//遊戲結束
      showWelldone();
      delay(3000);
      display.clearDisplay();
      testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // 星星動畫
    }
  delay(1000);
  }
}