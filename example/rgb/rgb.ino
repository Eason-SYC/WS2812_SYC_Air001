#include "WS2812_SYC_Air001.h"

#define ws2812_number 64      // 使用的灯珠数量(默认为64)
#define ws2812_brightness 10  // 灯珠亮度(默认为10)
#define ws2812_type RGB       // 颜色类型(默认为GRB)

WS2812_COLOR color[] = {RGB_RED, RGB_GREEN, RGB_BLUE, RGB_YELLOW, RGB_WHITE, RGB_SKY_BLUE};

SYC_WS2812 syc = SYC_WS2812(ws2812_number, ws2812_brightness, ws2812_type); // 声明对象

void setup() {
  // put your setup code here, to run once:
  syc.setup();	        // 彩灯初始化
}

void loop() {
  for(int i = 0;i < 6;i++)
  {
    syc.setAllWs2812Color(ws2812_number, color[i]);
    syc.Ws2812_show();
    delay(1000);
  }
}