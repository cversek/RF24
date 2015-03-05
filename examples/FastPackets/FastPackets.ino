#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#define CE 14
#define CS 15
#define IRQ 16
#define BUFFER_SIZE 32
#define PACKET_SIZE 32

byte buff[BUFFER_SIZE];
 
RF24 radio(CE,CS);

const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void){
  //initialize buffer
  for (int i=0;i<BUFFER_SIZE;i++){
    buff[i] = 0x00;
  } 
  Serial.begin(230400);
  radio.begin();
  radio.setDataRate(RF24_2MBPS);
  
  radio.setAutoAck(true);
  radio.setCRCLength(RF24_CRC_8);
  radio.setRetries(0,15);   //First Arg :: 0 is 250us delay 2 &.is 750us; Second.Arg :: #retries 
  radio.setPayloadSize(PACKET_SIZE);
  radio.openWritingPipe(pipe);
}

unsigned long time_us;

void loop(void){
  time_us = micros();
  memcpy(buff, &time_us, sizeof(unsigned long));
  radio.writeFast(&buff,PACKET_SIZE);
}

