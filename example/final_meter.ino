
#include <VirtualWirem.h>


#define TRANS_ID 0x01

rgb_lcd lcd;

struct trans{
    int8_t _ID=0;
    uint8_t _msg[40]={'\0'};
    uint8_t _msg_len;
    uint8_t _ack=0;
    uint8_t _error=0;
  }trans1;

 void setup()
{
  Serial.begin(9600);	// Debugging only
  Serial.println("setup");

  vw_set_rx_pin(10);
  vw_setup(2000);
  vw_rx_start();
  trans1._ID=0x01;

}
uint8_t sender_id;

uint32_t sendMsgTimmer=0;
uint32_t sendMsgTimmer1=random(5)*500;

void loop()
{

   sender_id=vw_get_decoded_msg(msg_buf, &msg_buflen); // Non-blocking
    if (sender_id>0)
    {
      for (int i = 0; i < msg_buflen; i++)
  {
      Serial.print(msg_buf[i],HEX);
      Serial.print(" ");
  }
  Serial.println("");
       trans1._error=0;
       trans1._msg[0]='\0';


  }


if (trans1._error>0){
  if (millis()-sendMsgTimmer>=sendMsgTimmer1){

  //if (random(10)>backoff){
  tx_coded_msg(trans1._msg,trans1._msg_len,trans1._ID,trans1._ack);
  vw_wait_tx();
  for (int i=0;i<trans1._msg_len;i++){
  Serial.println(trans1._msg[i],HEX);
  }
//backoff=5;
sendMsgTimmer=millis();
sendMsgTimmer1=random(5)*800;
}
}
//else
//{
// backoff-=1;

}
