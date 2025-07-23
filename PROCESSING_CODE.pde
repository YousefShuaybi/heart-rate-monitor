import processing.serial.*;
import processing.sound.*;

// Serial & Sound
Serial myPort;
Sound sound;
SinOsc oscillator;

// ECG Configuration
final int BUFFER_SIZE = 1000;
ArrayList<Float> ecgBuffer = new ArrayList<Float>();
float[] waveTemplate = {0, 0, -10, 0, 50, -25, 0, 20, 10, 0, 0, 5, 2, 0};
ArrayList<Float> currentWave = new ArrayList<Float>();

// Colors
color bgColor = color(0);
color gridColor = color(0, 100, 0);
color lineColor = color(0, 255, 0);
color bpmTextColor = color(0, 255, 0);

// Animation and BPM
float currentBPM = 0;
boolean playingWave = false;
int waveIndex = 0;
int frameDelay = 1;
int delayCounter = 0;

void setup() {
  size(1200, 500);
  frameRate(60);
  
  println("Available serial ports:");
  println(Serial.list());
  // Change index if needed
  myPort = new Serial(this, Serial.list()[2], 115200);
  myPort.bufferUntil('\n');
  
  for (int i = 0; i < BUFFER_SIZE; i++) {
    ecgBuffer.add(0.0);
  }

  sound = new Sound(this);
  oscillator = new SinOsc(this);
}

void draw() {
  background(bgColor);
  drawGrid();
  drawECGSignal();
  drawBPM();
}

void drawGrid() {
  stroke(gridColor);
  strokeWeight(1);
  int spacing = 40;

  for (int x = 0; x < width; x += spacing)
    line(x, 0, x, height);
    
  for (int y = 0; y < height; y += spacing)
    line(0, y, width, y);
}

void drawECGSignal() {
  if (playingWave) {
    delayCounter++;
    if (delayCounter >= frameDelay && waveIndex < currentWave.size()) {
      ecgBuffer.add(currentWave.get(waveIndex));
      ecgBuffer.remove(0);
      waveIndex++;
      delayCounter = 0;
    } else if (waveIndex >= currentWave.size()) {
      playingWave = false;
    }
  } else {
    ecgBuffer.add(0.0);
    ecgBuffer.remove(0);
  }

  stroke(lineColor);
  strokeWeight(2);
  noFill();
  beginShape();
  for (int i = 0; i < ecgBuffer.size(); i++) {
    float x = map(i, 0, ecgBuffer.size(), 0, width * 0.75);
    float y = height / 2 - ecgBuffer.get(i);
    vertex(x, y);
  }
  endShape();
}

void drawBPM() {
  fill(bpmTextColor);
  textAlign(RIGHT, TOP);
  textSize(32);
  text("BPM", width - 30, 20);

  textSize(64);
  String bpmStr = (currentBPM < 100) ? nf(int(currentBPM), 2) : nf(int(currentBPM), 3);
  text(bpmStr, width - 30, 70);
}

void serialEvent(Serial port) {
  String input = port.readStringUntil('\n');
  if (input != null) {
    input = input.trim();
    println("Received BPM: " + input);
    
    try {
      float bpm = float(input);
      if (bpm > 20 && bpm < 200) {
        triggerHeartbeat(bpm);
      }
    } catch (Exception e) {
      println("⚠️ Invalid input: " + input);
    }
  }
}

void triggerHeartbeat(float bpm) {
  currentBPM = bpm;
  frameDelay = int(map(bpm, 40, 180, 4, 1));
  currentWave = new ArrayList<Float>();
  
  for (float value : waveTemplate)
    currentWave.add(value);
    
  waveIndex = 0;
  playingWave = true;
  playBeep();
}

void playBeep() {
  oscillator.freq(880);
  oscillator.amp(0.5);
  oscillator.play();
  delay(150);
  oscillator.stop();
}
