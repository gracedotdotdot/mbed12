#include "mbed.h"


#define CENTER_BASE 1500


PwmOut servo(D11);
DigitalIn encoder(D10);
Serial pc(USBTX, USBRX);

Timer t;

Ticker encoder_ticker;

volatile int steps;

volatile int last;

void encoder_control(){

    int value = encoder;

    if(!last && value) steps++;

    last = value;

}


void servo_control(int speed){

    if (speed > 200)       speed = 200;

    else if (speed < -200) speed = -200;


    servo = (CENTER_BASE + speed)/20000.0f;

}


int main() {

    pc.baud(9600);

    encoder_ticker.attach(&encoder_control, .001);
    servo.period(.02);

    float total_t = 0;
    while(total_t<5) {
        servo_control(-30.33);

        steps = 0;

        t.reset();

        t.start();

        wait(1);

        float time = t.read();

        total_t += time;

        pc.printf("%1.3f\r\n", (float)steps*6.5*3.14/32/time);

    }
    total_t=0;
    while(total_t<5) {

        servo_control(37.33);

        steps = 0;

        t.reset();

        t.start();

        wait(1);

        float time = t.read();

        total_t += time;

        pc.printf("%1.3f\r\n", (float)steps*6.5*3.14/32/time);

    }
    servo_control(0);

}