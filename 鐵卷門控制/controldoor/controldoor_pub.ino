#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial I2CBT(2,4);//定義PIN2及PIN4分別為RX及TX腳位

int LED1 = 7;
int LED2 = 8;

void setup() {
  Serial.begin(9600);
  I2CBT.begin(9600);//bluetooth baud rate
  pinMode(7, OUTPUT);  //設定 pin7 為輸出，LED1就接在這（開門）
  pinMode(8, OUTPUT);  //設定 pin8 為輸出，LED2就接在這（關門）
}

//＊＊＊＊＊＊＊＊＊＊＊＊＊＊main＊＊＊＊＊＊＊＊＊＊＊＊＊＊//

void loop() {

  byte cmmd[20];
  int insize;
 
 
  while(1){
/*
read message from bluetooth
*/
    if ((insize=(I2CBT.available()))>0){  //讀取藍牙訊息
       Serial.print("input size = "); 
       Serial.println(insize);
       for (int i=0; i<insize; i++){
         Serial.print(cmmd[i]=char(I2CBT.read()));
         Serial.print(" "); 
       }
       Serial.println("  "); 
    }  
///* 開門   
      if (cmmd[0]==49) {               //ASCII CODE   passwd:"1123" 識別碼   
        if (cmmd[1]==50) {
          if (cmmd[2]==51) {
            digitalWrite(LED1, HIGH);
            cmmd[0]=96;               //取代"1123"的暫存字元,才能off LED1
            delay(500);
            digitalWrite(LED1, LOW);   //熄滅LED1
            }
          }
         }//if
  //  關門       
  else if (cmmd[0]==50) {              //ASCII CODE    passwd:"2213"  識別碼        
          if (cmmd[1]==49) {
           if (cmmd[2]==51) {
             digitalWrite(LED2, HIGH);
             cmmd[0]=96;               //取代"2213"的暫存字元,才能off LED2   
             delay(500);
             digitalWrite(LED2, LOW);   //熄滅LED2 
            }
           }
          }//if
      
  } //while

}
