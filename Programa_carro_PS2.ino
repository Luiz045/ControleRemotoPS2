#include <PS2X_lib.h>

PS2X ps2x; 

//VARIAVEIS DO RECEPTOR
int error = 0; 
byte type = 0;
byte vibrate = 0;


//VARIAVEIS DE SAIDA
int REVERSAO = 4;
int DIRECAO = 5;
int VELOCIDADE = 6;
int RELE_SETA = 7;
int FAROL_DIANTEIRO = 10;
int FAROL_TRASEIRO = 11;
int SETA_DIREITA = 12;
int SETA_ESQUERDA = 13;


//VARIAVEIS AUXILIARES
int SETA_ESQUERDA_AUX = 0;
int SETA_DIREITA_AUX = 0;
int FAROL_DIANTEIRO_AUX = 0;
int FAROL_TRASEIRO_AUX = 0;
int PISCA_ALERTA_AUX = 0;
int RELE_SETA_AUX = 0;
int VELOCIDADE_AUX = 0;
int ANGULO_DA_DIRECAO;
int ANGULO_DA_DIRECAO_ANTERIOR;
int TEMPO_DE_ALTA;
unsigned long DELAY = 0;


void setup(){
 
 //PINOS DO RECEPTOR (CLOCK,COMMAND,ATTENTION,DATA,PRESSOES?,RUMBLE?), VERIFICACAO DE ERRO
 error = ps2x.config_gamepad(A3,A4,A5,A2, true, true); 


 //PINOS DE SAIDA
 pinMode(REVERSAO,OUTPUT);
 pinMode(RELE_SETA,OUTPUT);
 pinMode(SETA_ESQUERDA,OUTPUT);
 pinMode(SETA_DIREITA,OUTPUT);
 pinMode(FAROL_DIANTEIRO,OUTPUT);
 pinMode(FAROL_TRASEIRO,OUTPUT);
 pinMode(VELOCIDADE,OUTPUT);
 pinMode(DIRECAO,OUTPUT);
 Serial.begin(9600);
}

void loop()
{
   ps2x.read_gamepad(false, vibrate);


   //ATUALIZACAO DOS BOTOES
   if (ps2x.NewButtonState())  
   {    
      if(ps2x.Button(PSB_PINK))
      RELE_SETA_AUX++;
         
      if(ps2x.Button(PSB_BLUE))
      FAROL_DIANTEIRO_AUX++;
         
      if(ps2x.Button(PSB_L1)&&(SETA_DIREITA_AUX%2==0)&&(PISCA_ALERTA_AUX%2==0))
      SETA_ESQUERDA_AUX++;
         
      if(ps2x.Button(PSB_R1)&&(SETA_ESQUERDA_AUX%2==0)&&(PISCA_ALERTA_AUX%2==0))
      SETA_DIREITA_AUX++; 
         
      if(ps2x.Button(PSB_GREEN)&&(SETA_DIREITA_AUX%2==0)&&(SETA_ESQUERDA_AUX%2==0))
      PISCA_ALERTA_AUX++;   
   } 


   //RELE DA SETA
   if(((RELE_SETA_AUX%2==0)&&(digitalRead(SETA_ESQUERDA)==1))||((RELE_SETA_AUX%2==0)&&(digitalRead(SETA_DIREITA)==1)))
      digitalWrite(RELE_SETA,1);
   else
      digitalWrite(RELE_SETA,0);


   // SETA ESQUERDA
   if(SETA_ESQUERDA_AUX%2==1)   
   {
      if(millis()-DELAY<650)
         digitalWrite(SETA_ESQUERDA,1);
   
      if(millis()-DELAY>=650)
         digitalWrite(SETA_ESQUERDA,0); 
   
      if(millis()-DELAY>=1300)
         DELAY = millis();
   }

   else if((PISCA_ALERTA_AUX%2==0)&&(SETA_ESQUERDA_AUX%2==0))
      digitalWrite(SETA_ESQUERDA,0);


   // SETA DIREITA     
   if(SETA_DIREITA_AUX%2==1)   
   {
      if(millis()-DELAY<650)
         digitalWrite(SETA_DIREITA,1);
   
      if(millis()-DELAY>=650)
         digitalWrite(SETA_DIREITA,0); 
   
      if(millis()-DELAY>=1300)
         DELAY = millis();
   }
      
   else if((PISCA_ALERTA_AUX%2==0)&&(SETA_DIREITA_AUX%2==0))
      digitalWrite(SETA_DIREITA,0);
   

   // PISCA ALERTA
   if(PISCA_ALERTA_AUX%2==1) 
   {
      if(millis()-DELAY<650)     
      {
         digitalWrite(SETA_ESQUERDA,1);
         digitalWrite(SETA_DIREITA,1);
      }
         
      if(millis()-DELAY>=650)
      {
         digitalWrite(SETA_ESQUERDA,0);
         digitalWrite(SETA_DIREITA,0);
      }
   
      if(millis()-DELAY>=1300)
         DELAY = millis();
   }


   //FAROL DIANTEIRO
   if((FAROL_DIANTEIRO_AUX%3)==0)
      analogWrite(FAROL_DIANTEIRO,0);

   if((FAROL_DIANTEIRO_AUX%3)==1)
      analogWrite(FAROL_DIANTEIRO,50);
   
   if((FAROL_DIANTEIRO_AUX%3)==2)
      analogWrite(FAROL_DIANTEIRO,255);
      

   //FAROL TRASEIRO
   if(ps2x.Button(PSB_RED))
      digitalWrite(FAROL_TRASEIRO,1);

   else
      digitalWrite(FAROL_TRASEIRO,0);


   //VELOCIDADE
   analogWrite(VELOCIDADE,VELOCIDADE_AUX);

   if(ps2x.Analog(PSS_LY)>127)
      VELOCIDADE_AUX=((((ps2x.Analog(PSS_LY))-127)*2)-1);

   if(ps2x.Analog(PSS_LY)<=127)
      VELOCIDADE_AUX=((127-(ps2x.Analog(PSS_LY)))*2);


   //REVERSÃO
   if(ps2x.Analog(PSS_LY)>127)
      digitalWrite( REVERSAO,1);

   else
      digitalWrite( REVERSAO,0);


   //DIRECAO
   ANGULO_DA_DIRECAO=(((ps2x.Analog(PSS_RX))/3.2)+56);

   TEMPO_DE_ALTA=(600+(ANGULO_DA_DIRECAO*10));

   if(ANGULO_DA_DIRECAO!=ANGULO_DA_DIRECAO_ANTERIOR)
   {
      digitalWrite(DIRECAO, 1);
      delayMicroseconds(TEMPO_DE_ALTA); 
      digitalWrite(DIRECAO, 0);
      delayMicroseconds(20000-TEMPO_DE_ALTA); 
      ANGULO_DA_DIRECAO_ANTERIOR=ANGULO_DA_DIRECAO;
   }

   delay(50);
}
