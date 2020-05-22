#include "mbed.h"

AnalogIn analog_value(A0);
#include "stdio.h"
#include "Serial.h"
#include "CMPS03.h"

/////////////////////motor///////////////////////
DigitalOut dir3(PB_9);
DigitalOut dir4(PB_8);
DigitalOut dir5(PC_5);
DigitalOut dir6(PC_8);
DigitalOut dir1(PA_12);
DigitalOut dir2(PB_12);
DigitalOut dir7(PB_14);
DigitalOut dir8(PB_15);
PwmOut pwm4(PB_1);
PwmOut pwm3(PC_9);
PwmOut pwm2(PC_6);
PwmOut pwm1(PA_11);

////////////////////////////////////////////////





float roda1, roda2, roda3, roda4;
float pw1,pw2,pw3, pw4;
float abs_pwm1, abs_pwm2, abs_pwm3, abs_pwm4;
double dx, dy, dz;

//////////////////////inverse///////////////////////


void atur(float x, float  y, float z)
{
  roda1 = x - z;
  roda2 = y - z;
  roda3 = y + z;
  roda4 = x + z;

  if (roda1 < 0)
  {
    abs_pwm1 = abs(roda1);
    pw1=(float) abs_pwm1/255;
    dir1 = 1;
    dir2 = 0;
  }
  else
  {
    abs_pwm1 = roda1;
    pw1=(float) abs_pwm1/255;
    dir1 = 0;
    dir2 = 1;
  }
  if (roda2 < 0)
  {
    abs_pwm2 = abs(roda2);
    pw2=(float) abs_pwm2/255;
    dir3 = 1;
    dir4 = 0;
  }
  else
  {
    abs_pwm2 = roda2;
    pw2=(float) abs_pwm2/255;
    dir3 = 0;
    dir4 = 1;
  }
  if (roda3 < 0)
  {
    abs_pwm3 = abs(roda3);
    pw3=(float) abs_pwm3/255;
    dir5 = 1;
    dir6 = 0;
  }
  else
  {
    abs_pwm3 = roda3;
    pw3=(float) abs_pwm3/255;
    dir5 = 0;
    dir6 = 1;
  }
  if (roda4 < 0) {
    abs_pwm4 = abs(roda4);
    pw4=  ((float) abs_pwm4/255);
    dir7 = 1;
    dir8 = 0;
  }
  else
  {
    abs_pwm4 = roda4;
    pw4=((float) abs_pwm4/255);
    dir7 = 0;
    dir8 = 1;
  }
    pwm1.write(pw1);
    pwm2.write(pw2);
    pwm3.write(pw3);
    pwm4.write(pw4);
}

////////////////////////////////////////////////


Serial pc(USBTX, USBRX);
CMPS03 compass(PB_4,PA_8 , CMPS03_DEFAULT_I2C_ADDRESS);
Serial device(PB_6, PB_7);
PinName pin_SERVO0  = PB_0;
PinName pin_SERVO1  = PB_3;
PinName pin_SERVO2  = PA_0;
PinName pin_SERVO3  = PA_10;
PinName pin_SERVO4  = PA_5;
PinName pin_SERVO5  = PA_7;
PinName pin_SERVO6  = PA_1;
PinName pin_SERVO7  = PB_10;





 DigitalOut relay1(PA_13);
PwmOut Servo0(pin_SERVO0);
PwmOut Servo1(pin_SERVO1);
PwmOut Servo2(pin_SERVO2);
PwmOut Servo3(pin_SERVO3);
PwmOut Servo4(pin_SERVO4);
PwmOut Servo5(pin_SERVO5);
PwmOut Servo6(pin_SERVO6);
PwmOut Servo7(pin_SERVO7);

void Servo_angle(int16_t angle)
{
    int16_t Angle = 600 + (angle * 10);
    Servo0.pulsewidth_us(Angle);
    Servo1.pulsewidth_us(Angle);
    Servo2.pulsewidth_us(Angle);
    Servo3.pulsewidth_us(Angle);
    Servo4.pulsewidth_us(Angle);
    Servo5.pulsewidth_us(Angle);
    Servo6.pulsewidth_us(Angle);
    Servo7.pulsewidth_us(Angle);

}



int inputdata;
int data;
int data2;
double posisi;
int main()
{
    device.baud(38400);
    pc.baud(38400);
    Servo0.period_ms(20);
    Servo1.period_ms(20);
    Servo2.period_ms(20);
    Servo3.period_ms(20);
    Servo4.period_ms(20);
    Servo5.period_ms(20);
    Servo6.period_ms(20);
    Servo7.period_ms(20);

    while(1) {



        if(device.readable()>0)
        {
        inputdata = device.getc();
        data=inputdata;
        pc.putc(inputdata);
        {




                //penanaman
                if(data == 'i') //tutup
                {

                    // 180 ~ 0
                    for(int i=180; i>=0; i--)
                    {
                        int16_t Angle = 600 + (i * 10);
                        Servo2.pulsewidth_us(Angle);
                        Servo3.pulsewidth_us(Angle);
                        Servo4.pulsewidth_us(Angle);
                        Servo7.pulsewidth_us(Angle);

                    }
                }
                if(data == 'h') //buka
                {

                    // 180 ~ 0
                    for(int i=0; i<=110; i++)
                    {
                        int16_t Angle = 600 + (i * 10);
                        Servo2.pulsewidth_us(Angle);
                        Servo3.pulsewidth_us(Angle);
                        Servo4.pulsewidth_us(Angle);
                        Servo7.pulsewidth_us(Angle);

                    }
                }


                if(data == 'g') //arm naik
                {

                    // 180 ~ 0
                    for(int i=180; i>=100; i--)
                    {
                        int16_t Angle = 600 + (i * 10);
                        Servo0.pulsewidth_us(Angle);
                        Servo1.pulsewidth_us(Angle);
                        Servo5.pulsewidth_us(Angle);
                        Servo6.pulsewidth_us(Angle);

                    }
                }

                if(data == 'f') //arm turun
                {
                    // 0 ~ 180
                    for(int i=100; i<=180; i++)
                    {
                        int16_t Angle = 600 + (i * 10);
                        Servo0.pulsewidth_us(Angle);
                        Servo1.pulsewidth_us(Angle);
                        Servo5.pulsewidth_us(Angle);
                        Servo6.pulsewidth_us(Angle);


                    }
                }
                // penyiangan
                if(data == 'b') //arm turun
                {
                    // 0 ~ 180
                    for(int i=100; i<=180; i++)
                    {
                        int16_t Angle = 600 + (i * 10);
                        Servo0.pulsewidth_us(Angle);
                        //Servo1.pulsewidth_us(Angle);
                        Servo5.pulsewidth_us(Angle);

                    }
                }
                if(data == 'c') //arm naik
                {

                    // 180 ~ 0
                    for(int i=180; i>=100; i--)
                    {
                        int16_t Angle = 600 + (i * 10);
                        Servo0.pulsewidth_us(Angle);
                        //Servo1.pulsewidth_us(Angle);
                        Servo5.pulsewidth_us(Angle);
                    }
                }
                if(data == 'e') //tutup
                {

                    // 180 ~ 0
                    for(int i=180; i>=0; i--)
                    {
                        int16_t Angle = 600 + (i * 10);
                        Servo2.pulsewidth_us(Angle);
                        //Servo3.pulsewidth_us(Angle);
                        Servo4.pulsewidth_us(Angle);

                    }
                }
                if(data == 'd') //buka
                {

                    // 180 ~ 0
                    for(int i=0; i<=110; i++)
                    {
                        int16_t Angle = 600 + (i * 10);
                        Servo2.pulsewidth_us(Angle);
                        //Servo3.pulsewidth_us(Angle);
                        Servo4.pulsewidth_us(Angle);

                    }
                }


                switch(data){
                    case'2':
                        atur(100,0,0); //maju
                        break;
                    case'3':
                        atur(-100,0,0); //mundur
                        break;
                    case'7':
                        atur(0,-100,0); //kanan
                        break;
                    case'1':
                        atur(0,100,0); //kiri
                        break;
                    case'5':
                        atur(0,0,100); //muter kanan
                        break;
                    case'8':
                        atur(0,0,-100); //muter kiri
                        break;
                    case'9':
                    {
                    for(double posisi=0; posisi<=329.700012; posisi++)
                            {
                            posisi=compass.readBearing()/10.0;
                            printf("Bearing is: %f\n", posisi);
                            atur(0,0,100);
                            if(posisi==329.700012);
                    }
                    atur(0,0,0);


                    default:
                    dir1 = 1;
                    dir2 = 1;
                    dir3 = 1;
                    dir4 = 1;
                    dir5 = 1;
                    dir6 = 1;
                    dir7 = 1;
                    dir8 = 1;
                    ;

                }

                // untuk mode pemotong menggunakan relay
                 if(data == 'a'){
                relay1=1;

                }
                if(data == 'z') {
                    relay1=0;
                    }

                }


}}}}
