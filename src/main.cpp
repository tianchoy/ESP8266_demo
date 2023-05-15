#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int LED_Green = 13;  // D7
int LED_Red = 15;    // D8
int LED_Yellow = 12; // D6
int GuangOu = 2;     // D4

int light = 0;

int GuangOuState = 0;

const char *ssid = "online";       // 连接WIFI名(SSID)
const char *password = "51810543"; // WIFI密码

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void OLED_DISPLAY()
{
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(WHITE); // 开像素点发光
  oled.clearDisplay();      // 清屏

  oled.setTextSize(1);   // 设置字体大小
  oled.setCursor(15, 5); // 设置显示位置
  oled.println("WiFi Information");
  oled.setCursor(2, 20); // 设置显示位置

  WiFi.begin(ssid, password); // 启动网络连接

  while (WiFi.status() != WL_CONNECTED) // 检测网络是否连接成功
  {
    delay(500);
    oled.print("."); // 设置显示位置
    oled.display();  // 开显示
  }

  oled.setTextSize(1);   // 设置字体大小
  oled.setCursor(2, 35); // 设置显示位置
  oled.println("Connected,IP address:");
  oled.println();
  oled.println(WiFi.localIP());
  oled.display(); // 开显示
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  /*
    红绿灯设置输出
  */
  pinMode(LED_Green, OUTPUT);
  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Yellow, OUTPUT);

  // OLED显示设置
  OLED_DISPLAY();

  // 红绿灯设置低电平为熄灭状态
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Red, LOW);
  digitalWrite(LED_Yellow, LOW);
}

void lightFun(int LightType)
{
  digitalWrite(LightType, HIGH);
  delay(10000); // 灯亮10秒
  // 开始闪烁
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED_Yellow, HIGH);
    delay(500);
    digitalWrite(LED_Yellow, LOW);
    delay(500);
  }
  digitalWrite(LightType, LOW);
}

void loop()
{
  // put your main code here, to run repeatedly:

  if (light == 0)
  {
    lightFun(LED_Green);
    light = 1;
  }
  else
  {
    lightFun(LED_Red);
    light = 0;
  }

  GuangOuState = digitalRead(GuangOu);

  if (GuangOuState == 0)
  {
    digitalWrite(GuangOu, LOW);
  }
  else
  {
    digitalWrite(GuangOu, HIGH);
  }
}
