/*

 This example generates a square wave based tone at a specified frequency
 and sample rate. Then outputs the data using the I2S interface to a
 AW88298 I2S Amp.

 An I2S bus that follows the Philips standard is made up of at least three wires:
  1) SCK (Serial Clock): is the clock signal also referred as BCLK (Bit Clock Line);
  2) FS (Frame Select): used to discriminate Right or Left Channel data also referred WS (Word Select);
  3) SD (Serial Data): the serial data to be transmitted;
  
 */

#include <I2S.h>
const int frequency = 440; // frequency of square wave in Hz
const int amplitude = 500; // amplitude of square wave
const int sampleRate = 8000; // sample rate in Hz
const int halfWavelength = (sampleRate / frequency); // half wavelength of square wave
short sample = amplitude; // current sample value
int count = 0;

// AW88298 ADDR	0x36
// https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/K128%20CoreS3/AW88298.PDF
int sckPin = 11;    // I2C_SYS_SCL
int inSdPin = 12;   // I2C_SYS_SDA	

void setup() {
  
  I2S.setSckPin(sckPin);
  I2S.setDataInPin(inSdPin);

  Serial.println("I2S Clock GPIO");
  Serial.println(I2S.getSckPin());
  Serial.println("I2S Data GPIO");
  Serial.println(I2S.getDataInPin());

  Serial.begin(9600);
  Serial.println("Playting I2S simple tone");
  
  // start I2S at the sample rate with 16-bits per sample
  if (!I2S.begin(I2S_PHILIPS_MODE, sampleRate, 16)) {
    Serial.println("Failed to initialize I2S!");
    while (1); // do nothing
  }
}

void loop() {
  if (count % halfWavelength == 0) {
    // invert the sample every half wavelength count multiple to generate square wave
    sample = -1 * sample;
  }

  // write the same sample twice, once for left and once for the right channel
  I2S.write(sample);
  I2S.write(sample);

  // increment the counter for the next sample
  count++;
}
