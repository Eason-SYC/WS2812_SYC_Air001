/*
 * 跳动的心示例 - 基于Air001的ws2812驱动库
 * Created by 沈已成, 2025-04-17
 * Version: 1.0.1
 * 注意：需要选择HSI -> 16M, HCLK -> 16M
 */


#include "WS2812_SYC_Air001.h"

#define ws2812_number 64      // 使用的灯珠数量(默认为64)
#define ws2812_brightness 20  // 灯珠亮度(默认为10)
#define ws2812_type RGB       // 颜色类型(默认为GRB)

SYC_WS2812 strip = SYC_WS2812(ws2812_number, ws2812_brightness, ws2812_type); // 声明对象

// 跳动的心第一张图
uint32_t heart_red1[] = 
{
  0x00669981, 0x81422418, RGB_RED, RGB_RED, RGB_RED, RGB_RED, 
  RGB_RED, RGB_RED, RGB_RED, RGB_RED, RGB_RED, RGB_RED,
  RGB_RED, RGB_RED, RGB_RED, RGB_RED, RGB_RED, RGB_RED, 
  RGB_RED, RGB_RED
};

// 跳动的心第一张图
uint32_t heart_red2[] = 
{
  0x0000245A, 0x42241800, RGB_RED, RGB_RED, RGB_RED, RGB_RED, 
  RGB_RED, RGB_RED, RGB_RED, RGB_RED, RGB_RED, RGB_RED,
  RGB_RED, RGB_RED
};

void setup() {
  // put your setup code here, to run once:
  strip.setup();	        // 彩灯初始化
}

void loop() {
  strip.Draw(heart_red1); // 显示红色图片1
  delay(200);
  strip.Draw(heart_red2); // 显示红色图片1
  delay(200);
}