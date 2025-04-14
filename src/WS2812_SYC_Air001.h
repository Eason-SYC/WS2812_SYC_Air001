#ifndef _WS2812_H__
#define _WS2812_H__

#include <Arduino.h>
#include <SPI.h>

#define MAX_NUM 128

// 使用枚举定义彩灯颜色模式
enum WS2812_TYPE
{                //R  G  B
    GRB = 0x06,  //00 01 10
    RBG = 0x09,  //00 10 01
    RGB = 0x12,  //01 00 10
    GBR = 0x21,  //10 00 01
    BRG = 0x18,  //01 10 00
    BGR = 0x24   //10 01 00
};

// 使用枚举定义彩灯颜色模式
enum WS2812_COLOR
{                         
    RGB_RED = 0xff0000,     
    RGB_GREEN = 0x00ff00, 
    RGB_BLUE = 0x0000ff,  
    RGB_YELLOW = 0xffff00,
    RGB_WHITE = 0xffffff, 
    RGB_SKY_BLUE = 0x00ffff,
};

class SYC_WS2812
{
  public:

    SYC_WS2812(uint16_t num = 64, uint8_t brightness = 20, WS2812_TYPE type = GRB);
    void setup();
    void setType();
    void setBrightness(uint8_t brightness);
    void clearWs2812();
    bool setWs2812Color(int ws2812_num, uint32_t rgb);
    bool setAllWs2812Color(int ws2812_num, uint32_t rgb);
    bool Ws2812_show();
    void Draw(uint32_t *pic);
  private:
  
    uint16_t WS2812_Counts;     // 彩灯数量
    uint8_t  WS2812_brightness; // 彩灯亮度
    uint8_t r, g, b;            // 彩灯颜色模式参数
    WS2812_TYPE WS2812_type;    // 彩灯颜色模式
    uint32_t led_data[MAX_NUM];
};

#endif