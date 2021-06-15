# ControleRemotoPS2

Este código é referente a uma implementação utilizando um controle remoto de PS2 sem fio. Eu escrevi o codigo para automatizar uma miniatura de carro, fazendo tambem a parte eletrica. Fique a vontade para utilizar ou alterar o código!                                        
OBS: Pesquise por "receptor de ps2 ligacoes" no google imagens para saber as conexoes feitas no receptor da manete.                
OBS: Baixe a biblioteca "PS2X_lib", disponivel no github e tambem pelo IDE arduino.                                     
pasta no Drive com imagens e videos do projeto: https://drive.google.com/drive/folders/1Jz0_6uhuww3sN2ksaLPnXASJQ5mmSpGX?usp=sharing               

Descrição das saidas:                                               
REVERSAO --> saida digital (aciona um relé responsavel pela ré)                                            
DIRECAO --> saida digital (controla o servo motor responsavel pela posição das rodas dianteiras)                            
VELOCIDADE --> saida pwm (controla um mosfet responsavel pela velocidade)                                 
RELE_SETA --> saida digital (aciona um relé para imitar o som de um carro dando seta)                             
FAROL_DIANTEIRO --> saida pwm (controla o farol dianteiro em 3 posições: desligado, baixo e alto)                           
FAROL_TRASEIRO --> saida digital (aciona o farol traseiro)                              
SETA_DIREITA --> saida digital (aciona a seta direita)                           
SETA_ESQUERDA --> saida digital (aciona a seta esquerda)  

