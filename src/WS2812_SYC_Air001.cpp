/*
 * WS2812_SYC_Air001 - 基于Air001的ws2812驱动库
 * Created by 沈已成, 2025-04-13
 * Version: 1.0.1
 * License: MIT
 * GitHub: https://github.com/Eason-SYC/WS2812_SYC_Air001
 * 
 * 功能：
 * - 支持显示多种颜色
 * - 支持显示图片
 * - 支持彩虹灯效果
 */
#include "WS2812_SYC_Air001.h"

// 彩灯基础配置(参数后的注释是默认值)
SYC_WS2812::SYC_WS2812(uint16_t num /* 64 */, uint8_t brightness /* 255 */, WS2812_TYPE type /* GRB */)
{
    WS2812_Counts = num;              //获取彩灯数量
    WS2812_brightness = brightness;   //获取彩灯亮度
    WS2812_type = type;               //获取彩灯颜色类型
} 

// 初始化函数
void SYC_WS2812::setup()
{   
  // SPI 初始化配置
  SPI.begin();                          //初始化SPI
  SPI.setBitOrder(MSBFIRST);            //高位在前，低位在后
  SPI.setDataMode(SPI_MODE1);           //设置spi为模式1
  SPI.setClockDivider(SPI_CLOCK_DIV2);  //芯片设置16M，SPI配置为2分频，确保为8Mhz
  
  // 设置彩灯颜色模式
  setType();
}

// 设置彩灯颜色模式
void SYC_WS2812::setType()
{
  r = (WS2812_type >> 4) & 0x03;
  g = (WS2812_type >> 2) & 0x03;
  b = WS2812_type & 0x03;
}

// 设置彩灯亮度
void SYC_WS2812::setBrightness(uint8_t brightness)
{
  WS2812_brightness = constrain(brightness, 0, 255);// 约束亮度范围在0~255
}

// 设置彩灯颜色
void SYC_WS2812::setWs2812Color(int ws2812_num, uint32_t rgb)
{
    uint8_t color_rgb[3];

    color_rgb[r] = rgb >> 16;
    color_rgb[g] = rgb >> 8;
    color_rgb[b] = rgb;

    color_rgb[r] = color_rgb[r] * WS2812_brightness / 255;
    color_rgb[g] = color_rgb[g] * WS2812_brightness / 255;
    color_rgb[b] = color_rgb[b] * WS2812_brightness / 255;
  
    uint32_t color = (color_rgb[r] << 16) | (color_rgb[g] << 8) | (color_rgb[b]); 

    led_data[ws2812_num] = color;
}

// 设置全部彩灯颜色
void SYC_WS2812::setAllWs2812Color(int ws2812_num, uint32_t rgb)
{
    for (int i = 0; i < ws2812_num; i++)
    {
        setWs2812Color(i, rgb);
    }
}

// 显示彩灯颜色
void SYC_WS2812::Ws2812_show()
{
  uint32_t value = 0;
  for (int i = 0; i < WS2812_Counts; i++){
    value = led_data[i];
    for(int j = 0; j < 24; j++){
      if ((value & 0x800000) != LOW) {
        SPI.transfer(0xF8);//1
        asm("nop");
        asm("nop");
      } 
      else {
        SPI.transfer(0xC0);//0
      }
      value <<= 1;
    }
  }
  delayMicroseconds(60);
}

// 清除所有彩灯的颜色
void SYC_WS2812::clearWs2812()
{
  for (int i = 0; i < MAX_NUM; i++)
  {
      setWs2812Color(i, 0);
  }
  Ws2812_show();
}

// 绘制彩灯数组
void SYC_WS2812::Draw(uint32_t *pic)
{
  uint8_t j = 2;
  uint32_t k = pic[1];
  // clearWs2812();
  for(uint8_t i = 63; i > 31;i--)
  {
    if((k & 1) == 0)
      setWs2812Color(i, 0);
    else
    {
      setWs2812Color(i, pic[j]);
      j++;
    }
    k = k >> 1;
  }
  k = pic[0];
  for(uint8_t i = 31; i > 1;i--)
  {
    if((k & 1) == 0)
      setWs2812Color(i, 0);
    else
    {
      setWs2812Color(i, pic[j]);
      j++;
    }
    k = k >> 1;
  }
  Ws2812_show();
}

uint32_t SYC_WS2812::Wheel(byte pos) 
{
    uint32_t WheelPos = pos % 0xff;
    if (WheelPos < 85) {
        return ((255 - WheelPos * 3) << 16) | ((WheelPos * 3) << 8);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return (((255 - WheelPos * 3) << 8) | (WheelPos * 3));
    }
    WheelPos -= 170;
    return ((WheelPos * 3) << 16 | (255 - WheelPos * 3));
}

/* 使用示例 */
void SYC_WS2812::Rainbow(uint8_t Rainbow_speed) 
{
  for (int j = 0; j < 255; j += Rainbow_speed) {
    for (int i = 0; i < 64; i++) {
      setWs2812Color(i, Wheel((i * 256 / 64 + j) & 255));
    }
    Ws2812_show();
  }  
}