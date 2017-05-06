#include "mbed.h"
#include "tinysh.h"
#include <inttypes.h>


Serial *dpc = new Serial(SERIAL_TX, SERIAL_RX);  // tx, rx

SPI *AD9833_SPI = new SPI(SPI_MOSI, SPI_MISO, SPI_SCK); //mosi, miso, sclk --> don't need MISO
DigitalOut fSync(SPI_CS); //use p8 as FSync data pin (same as chip select)

DigitalOut led(B1);

float brightness = 0.0;

Thread thread1;
Thread thread2;

//custom function
void foo_fnt(int argc, char **argv)
{
  dpc->printf("foo command called\r\n");
    for(int i=0; i<argc; i++) {
      dpc->printf("argv[%d]=\"%s\"\r\n",i,argv[i]);
    }
    dpc->printf("\r\n");
}
//custom command
tinysh_cmd_t myfoocmd= {0,"foo","foo command","[args]",foo_fnt,0,0,0};



//mandatory tiny shell output function
void tinysh_char_out(unsigned char c)
{
    dpc->putc(c);
}

void SPI_INITIALIZATION()
{

    //Setup the spi for 16 bit data, with ... hz clock rate, mode 2
    // Note: mBed is MSB first SPI protocol
    AD9833_SPI->format(16,2);
    AD9833_SPI->frequency(12000000);
    
    fSync = 1;
    wait_ms(10);
}


void write_SPI(short dat)
{
    fSync = 0;
    AD9833_SPI->write(dat);
    fSync = 1;
}


void setFreq(long desired_frequency)
{

    int phase0command = 0x4000;

    float steps_per_Hz = (pow(2, 28)) / 25000000;

    unsigned long int steps_per_clk = desired_frequency * steps_per_Hz;

    unsigned int high14 = (steps_per_clk & 0xFFFC000) >> 14;
    unsigned int low14 = steps_per_clk & 0x3FFF;

    int freq_LSB =  low14 | phase0command;
    int freq_MSB =  high14 | phase0command;

    write_SPI(0x2100);      //write control reg - apply reset
    write_SPI(freq_LSB);    //write freq reg - LSB
    write_SPI(freq_MSB);    //write freq reg - MSB
    write_SPI(0xC000);      //write phase reg - 0 for now
    write_SPI(0x2000);      //write control reg - disable reset
}



class Counter {
public:
    Counter(PinName pin) : _interrupt(pin) {        // create the InterruptIn on the pin specified to Counter
        _interrupt.rise(callback(this, &Counter::increment)); // attach increment function of this counter instance
       
    }

    void increment() {
        _count++;
    }

    int read() {
        _freq = _count;
        _count = 0;
    }

    int freq() {
        return _freq;
    }

private:
    InterruptIn _interrupt;
    volatile long int _count;
    volatile long int _freq;
};

Counter counter(B0);

void led1_thread(void const *args) {
    while (true) {
      led = !led;
      Thread::wait(1000);
    }
}

void led2_thread(void const *args) {
    while (true) {
      counter.read();
      Thread::wait(1000);
    }
}


void AD9833_set_freq(int argc, char **argv)
{

  if (argc > 0)
  {

    long freq = atoi(argv[1]);
    setFreq(freq);
    dpc->printf("set new Freq=%d\r\n",freq);
  }

  dpc->printf("\r\n");
}

tinysh_cmd_t cmd_freq= {0,"freq","set AD9833 freq.","[args]",AD9833_set_freq,0,0,0};


int main() {

    dpc->baud(115200);
    dpc->printf("tiny shell build %s %s\r\n",__DATE__,__TIME__);

    //set prompt
    tinysh_set_prompt("$ ");

    //add custom commands here
    tinysh_add_command(&myfoocmd);
    tinysh_add_command(&cmd_freq);

    SPI_INITIALIZATION(); // initialized the SPI

    thread1.start(callback(led1_thread, &led));
    thread2.start(callback(led2_thread, &led));

    
    while(1) {
        tinysh_char_in( dpc->getc() );
    }
}
