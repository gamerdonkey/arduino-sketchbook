int leds[] = {
  4, // white tree
  5, // big green window
  6, // green pole
  7, // red pole
  8, // upper green window
  9, // blue-green bushes
  10, // red trim
  11 // white icicles
};

#define NUMBER_OF_LEDS (sizeof(leds)/sizeof(int))

boolean allOn[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
boolean allWhite[] = {HIGH, LOW, LOW, LOW, LOW, LOW, LOW, HIGH};
boolean allGreen[] = {LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW, LOW};
boolean allRed[] = {LOW, LOW, LOW, HIGH, LOW, LOW, HIGH, LOW};
boolean redGreen[] = {LOW, HIGH, LOW, HIGH, HIGH, HIGH, HIGH, LOW};

boolean allOff[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

boolean* standingConfigs[] = { allOn, allWhite, allGreen, allRed, redGreen };

boolean larson[][NUMBER_OF_LEDS] = {
  { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW },
  { LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW },
  { LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW },
  { LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW },
  { LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW },
  { LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW },
  { LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW },
  { LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH },
  { LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW },
  { LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW },
  { LOW, LOW, LOW, LOW, HIGH, LOW, LOW, LOW },
  { LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW },
  { LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW },
  { LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW },
  { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW },
};

boolean rise[][NUMBER_OF_LEDS] = {
  { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW },
  { HIGH, HIGH, LOW, LOW, LOW, LOW, LOW, LOW },
  { HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW },
  { HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW },
  { HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW },
  { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW },
  { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW },
  { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH },
  { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW },
  { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW },
  { HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW },
  { HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW },
  { HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW },
  { HIGH, HIGH, LOW, LOW, LOW, LOW, LOW, LOW },
  { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW },
};

#define FRAMES (sizeof(larson)/(sizeof(larson[0])))
#define NUM_CONFIGS sizeof(standingConfigs)

void setup() {
  for (int led=0; led<NUMBER_OF_LEDS; led++) {
    pinMode(leds[led], OUTPUT);
  }
}

void loop(){
  for (int config=0; config<5; config++){
    if(config%2==0) {
      runDisplay(larson);
    }
    else {
      runDisplay(rise);
    }
    
    applyLightConfig(allOff);
    
    delay(500);
    
    fadeToConfig(allOff, standingConfigs[config]);
    
    delay(30000);
    
    fadeToConfig(standingConfigs[config], allOff);
  }
}

void runDisplay(boolean displayArray[][8]) {
  for (int frame=0; frame<FRAMES; frame++) {
    applyLightConfig(displayArray[frame]);
    delay(300);
  }
}

void applyLightConfig(boolean lightConfig[8]) {
  for (int led=0; led<NUMBER_OF_LEDS; led++) {
    digitalWrite(leds[led], lightConfig[led]);
  }
}

void fadeToConfig(boolean fromConfig[8], boolean toConfig[8]) {
  int millisLeft = 500;
  int millisForSixtyHz = 8;
  int millisOn = millisForSixtyHz;
  while(millisLeft > 0) {
    applyLightConfig(fromConfig);
    delay(millisForSixtyHz);
    applyLightConfig(toConfig);
    delay(millisOn);
    millisLeft = millisLeft - (millisForSixtyHz + millisOn);
    millisOn += millisForSixtyHz;
  }
  applyLightConfig(toConfig);
}
