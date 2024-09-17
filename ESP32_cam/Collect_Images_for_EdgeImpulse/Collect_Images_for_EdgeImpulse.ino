/**
 * Collect images for Edge Impulse image
 * classification / object detection
 *
 * BE SURE TO SET "TOOLS > CORE DEBUG LEVEL = INFO"
 * to turn on debug messages
 */

// if you define WIFI_SSID and WIFI_PASS before importing the library,
// you can call connect() instead of connect(ssid, pass)
//
// If you set HOSTNAME and your router supports mDNS, you can access
// the camera at http://{HOSTNAME}.local

// 进行摄像头拍照采集样本训练

#define WIFI_SSID "vivo S1"     // your wifi username
#define WIFI_PASS "zzj55555"    // your wifi password
#define HOSTNAME "esp32cam"
#define LED_PIN 4


// in host: http://192.168.43.239
#include <eloquent_esp32cam.h>
#include <eloquent_esp32cam/extra/esp32/wifi/sta.h>
#include <eloquent_esp32cam/viz/image_collection.h>

using eloq::camera;
using eloq::wifi;
using eloq::viz::collectionServer;

/*
返回报文格式: [0xAA,0xAA,0x01,x,y,w,h,0x01,0x00] 9字节
    防止其余HC设备发送相同频率的信号串台，加入一个简易的双重验证

1: head: 2字节      判断0xAA == 0xAA
2: data: 5字节      { 1:是否有人体; x,y,w,h: 人体相对的坐标 }
3: tail: 2字节      (0x01) && (!0x00)
*/
struct content {
  int header[2];
  int data[5];
  int tail[2];
};

void encapsulation_content(int *data) {
  struct content content1;
  content1.header[0] = 0xAA;
  content1.header[1] = 0xAA;

  for (int i = 0; i < 5; i++) {
    content1.data[i] = data[i];
  }

  content1.tail[0] = 0x01;
  content1.tail[1] = 0x00;

  send_to_stm32(content1);
}

void send_to_stm32(struct content content1) {
  for (int i = 0; i < 2; i++) {
    Serial.write(content1.header[i]);
    Serial.
  }
  for (int i = 0; i < 5; i++) {
    Serial.write(content1.data[i]);
  }
  for (int i = 0; i < 2; i++) {
    Serial.write(content1.tail[i]);
  }
}

void setup() {
  delay(3000);
  Serial.begin(115200);
  Serial.println("___IMAGE COLLECTION SERVER___");
  pinMode(LED_PIN, OUTPUT);
  //digitalWrite(LED_PIN, HIGH);

  // camera settings
  // replace with your own model!
  camera.pinout.aithinker();
  camera.brownout.disable();
  // Edge Impulse models work on square images
  // cif resolution : 400 x 296
  camera.resolution.cif();
  camera.quality.high();

  // init camera
  while (!camera.begin().isOk())
    Serial.println(camera.exception.toString());

  // connect to WiFi
  while (!wifi.connect().isOk())
    Serial.println(wifi.exception.toString());

  // init face detection http server
  while (!collectionServer.begin().isOk())
    Serial.println(collectionServer.exception.toString());

  Serial.println("Camera OK");
  Serial.println("WiFi OK");
  Serial.println("Image Collection Server OK");
  Serial.println(collectionServer.address());
}


void loop() {
  // server runs in a separate thread, no need to do anything here
}
