//To install the required E-Ink library goto https://github.com/HelTecAutomation/e-ink, download a zipfile from github
//using the "Download ZIP" button and install it using the IDE "Sketch" -> "Include Library" -> "Add .ZIP Library..."

//https://resource.heltec.cn/download/WiFi_LoRa_32/WIFI_LoRa_32_V2.pdf

#include "DEPG0154BxS800FxX_BW.h"
#include "picture.h"
#include "e_ink_display.h"

#define RST_PIN         12
#define DC_PIN          22 //  D/C: Data / Command
#define CS_PIN          18
#define BUSY_PIN        23
#define CLK_PIN         5

DEPG0154BxS800FxX_BW epd154bw(RST_PIN, DC_PIN, CS_PIN, BUSY_PIN, CLK_PIN);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin

unsigned char img[1024];
Paint pt(img, 0, 0);

unsigned long time_start_ms;
unsigned long time_now_s;

#define COLORED     0
#define UNCOLORED   1

void setup() {
  Serial.begin(115200);
  epd154bw.EPD_Init(); //Electronic paper initialization
  
  delay(100);
  epd154bw.EPD_ALL_image(gImage_152); //Refresh the picture in full screen
  
  delay(5000);
  epd154bw.Clear();
  
  pt.SetWidth(152);
  pt.SetHeight(24);
  
  Serial.println("e-Paper Paint");
  pt.Clear(COLORED);
  pt.DrawStringAt(10, 4, "Yes", &Font16, UNCOLORED);
  epd154bw.SetFrameMemory(pt.GetImage(), 0, 10, pt.GetWidth(), pt.GetHeight());
  delay(100);
  
  pt.Clear(UNCOLORED);
  pt.DrawStringAt(10, 4, "it works!", &Font16, COLORED);
  epd154bw.SetFrameMemory(pt.GetImage(), 0, 30, pt.GetWidth(), pt.GetHeight());
  delay(100);

  pt.SetWidth(64);
  pt.SetHeight(64);

  pt.Clear(UNCOLORED);
  pt.Clear(COLORED);
  pt.DrawRectangle(0, 0, 40, 50, COLORED);
  pt.DrawLine(0, 0, 40, 50, COLORED);
  pt.DrawLine(40, 0, 0, 50, COLORED);
  epd154bw.SetFrameMemory(pt.GetImage(), 16, 60, pt.GetWidth(), pt.GetHeight());
  delay(100);

  epd154bw.HalLcd_Partial_Update();
  delay(2000);

  Serial.println("done");
}

void loop() {

}
