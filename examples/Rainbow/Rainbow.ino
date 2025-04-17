/*
 * 彩虹灯示例 - 基于Air001的ws2812驱动库
 * Created by 沈已成, 2025-04-17
 * Version: 1.0.1
 * 注意：需要选择HSI -> 16M, HCLK -> 16M
 */

#include "WS2812_SYC_Air001.h"

#define ws2812_number 64      // 使用的灯珠数量(默认为64)
#define ws2812_brightness 20  // 灯珠亮度(默认为10)
#define ws2812_type RGB       // 颜色类型(默认为GRB)

SYC_WS2812 syc = SYC_WS2812(ws2812_number, ws2812_brightness, ws2812_type); // 声明对象

void setup() {
  // put your setup code here, to run once:
  syc.setup();	        // 彩灯初始化
}

void loop() {
  syc.Rainbow();
}