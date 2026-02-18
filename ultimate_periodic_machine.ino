#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <avr/pgmspace.h>

//Defines the size of the screen
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int powerPin = 12;
const int resetPin = 11;

const int countPin1 = 4;
const int countPin5 = 3;
const int countPin10 = 2;

//Starts off with Hydrogen, not 0 :D
int atomic = 1;

//Starts the system with off
bool state = 0;
bool lastPowerState = 0;

//Makes all the states off when starting
int lastState1 = HIGH;
int lastState5 = HIGH;
int lastState10 = HIGH;
int lastStateR = HIGH;


struct Element { //Short for structure, telling the Arduino how this array is structured like {name, group} rather than {group, name} 
  const char* name; //Now that it is stored in Flash memory, it uses a different variable ;D
  const char* group;
};

// Index matches Atomic Number exactly
const Element table[] PROGMEM = {
  {"None",          "Filler"},             // 0
  {"Hydrogen",      "Nonmetal"},           // 1
  {"Helium",        "Noble Gas"},          // 2
  {"Lithium",       "Alkali Metal"},       // 3
  {"Beryllium",     "Alkaline Earth"},     // 4
  {"Boron",         "Metalloid"},          // 5
  {"Carbon",        "Nonmetal"},           // 6
  {"Nitrogen",      "Nonmetal"},           // 7
  {"Oxygen",        "Nonmetal"},           // 8
  {"Fluorine",      "Halogen"},            // 9
  {"Neon",          "Noble Gas"},          // 10
  {"Sodium",        "Alkali Metal"},       // 11
  {"Magnesium",     "Alkaline Earth"},     // 12
  {"Aluminum",      "Post-Transition"},    // 13
  {"Silicon",       "Metalloid"},          // 14
  {"Phosphorus",    "Nonmetal"},           // 15
  {"Sulfur",        "Nonmetal"},           // 16
  {"Chlorine",      "Halogen"},            // 17
  {"Argon",         "Noble Gas"},          // 18
  {"Potassium",     "Alkali Metal"},       // 19
  {"Calcium",       "Alkaline Earth"},     // 20
  {"Scandium",      "Transition Metal"},   // 21
  {"Titanium",      "Transition Metal"},   // 22
  {"Vanadium",      "Transition Metal"},   // 23
  {"Chromium",      "Transition Metal"},   // 24
  {"Manganese",     "Transition Metal"},   // 25
  {"Iron",          "Transition Metal"},   // 26
  {"Cobalt",        "Transition Metal"},   // 27
  {"Nickel",        "Transition Metal"},   // 28
  {"Copper",        "Transition Metal"},   // 29
  {"Zinc",          "Transition Metal"},   // 30
  {"Gallium",       "Post-Transition"},    // 31
  {"Germanium",     "Metalloid"},          // 32
  {"Arsenic",       "Metalloid"},          // 33
  {"Selenium",      "Nonmetal"},           // 34
  {"Bromine",       "Halogen"},            // 35
  {"Krypton",       "Noble Gas"},          // 36
  {"Rubidium",      "Alkali Metal"},       // 37
  {"Strontium",     "Alkaline Earth"},     // 38
  {"Yttrium",       "Transition Metal"},   // 39
  {"Zirconium",     "Transition Metal"},   // 40
  {"Niobium",       "Transition Metal"},   // 41
  {"Molybdenum",    "Transition Metal"},   // 42
  {"Technetium",    "Transition Metal"},   // 43
  {"Ruthenium",     "Transition Metal"},   // 44
  {"Rhodium",       "Transition Metal"},   // 45
  {"Palladium",     "Transition Metal"},   // 46
  {"Silver",        "Transition Metal"},   // 47
  {"Cadmium",       "Transition Metal"},   // 48
  {"Indium",        "Post-Transition"},    // 49
  {"Tin",           "Post-Transition"},    // 50
  {"Antimony",      "Metalloid"},          // 51
  {"Tellurium",     "Metalloid"},          // 52
  {"Iodine",        "Halogen"},            // 53
  {"Xenon",         "Noble Gas"},          // 54
  {"Cesium",        "Alkali Metal"},       // 55
  {"Barium",        "Alkaline Earth"},     // 56
  {"Lanthanum",     "Lanthanoids"},         // 57
  {"Cerium",        "Lanthanoids"},         // 58
  {"Praseodymium",  "Lanthanoids"},         // 59
  {"Neodymium",     "Lanthanoids"},         // 60
  {"Promethium",    "Lanthanoids"},         // 61
  {"Samarium",      "Lanthanoids"},         // 62
  {"Europium",      "Lanthanoids"},         // 63
  {"Gadolinium",    "Lanthanoids"},         // 64
  {"Terbium",       "Lanthanoids"},         // 65
  {"Dysprosium",    "Lanthanoids"},         // 66
  {"Holmium",       "Lanthanoids"},         // 67
  {"Erbium",        "Lanthanoids"},         // 68
  {"Thulium",       "Lanthanoids"},         // 69
  {"Ytterbium",     "Lanthanoids"},         // 70
  {"Lutetium",      "Lanthanoids"},         // 71
  {"Hafnium",       "Transition Metal"},   // 72
  {"Tantalum",      "Transition Metal"},   // 73
  {"Tungsten",      "Transition Metal"},   // 74
  {"Rhenium",       "Transition Metal"},   // 75
  {"Osmium",        "Transition Metal"},   // 76
  {"Iridium",       "Transition Metal"},   // 77
  {"Platinum",      "Transition Metal"},   // 78
  {"Gold",          "Transition Metal"},   // 79
  {"Mercury",       "Transition Metal"},   // 80
  {"Thallium",      "Post-Transition"},    // 81
  {"Lead",          "Post-Transition"},    // 82
  {"Bismuth",       "Post-Transition"},    // 83
  {"Polonium",      "Metalloid"},          // 84
  {"Astatine",      "Halogen"},            // 85
  {"Radon",         "Noble Gas"},          // 86
  {"Francium",      "Alkali Metal"},       // 87
  {"Radium",        "Alkaline Earth"},     // 88
  {"Actinium",      "Actinoids"},           // 89
  {"Thorium",       "Actinoids"},           // 90
  {"Protactinium",  "Actinoids"},           // 91
  {"Uranium",       "Actinoids"},           // 92
  {"Neptunium",     "Actinoids"},           // 93
  {"Plutonium",     "Actinoids"},           // 94
  {"Americium",     "Actinoids"},           // 95
  {"Curium",        "Actinoids"},           // 96
  {"Berkelium",     "Actinoids"},           // 97
  {"Californium",   "Actinoids"},           // 98
  {"Einsteinium",   "Actinoids"},           // 99
  {"Fermium",       "Actinoids"},           // 100
  {"Mendelevium",   "Actinoids"},           // 101
  {"Nobelium",      "Actinoids"},           // 102
  {"Lawrencium",    "Actinoids"},           // 103
  {"Rutherford.", "Transition Metal"},     // 104 (No offense to the guy, but geez, can't fit on the 16 row w/ number)
  {"Dubnium",       "Transition Metal"},   // 105
  {"Seaborgium",    "Transition Metal"},   // 106
  {"Bohrium",       "Transition Metal"},   // 107
  {"Hassium",       "Transition Metal"},   // 108
  {"Meitnerium",    "Transition Metal"},   // 109
  {"Darmstadtium",  "Transition Metal"},   // 110
  {"Roentgenium",   "Transition Metal"},   // 111
  {"Copernicium",   "Transition Metal"},   // 112
  {"Nihonium",      "Post-Transition"},    // 113
  {"Flerovium",     "Post-Transition"},    // 114
  {"Moscovium",     "Post-Transition"},    // 115
  {"Livermorium",   "Post-Transition"},    // 116
  {"Tennessine",    "Halogen"},            // 117
  {"Oganesson",     "Noble Gas"}             // 118
};


//Note: I didn't like Unknown, so a category was assigned based on position on the periodic table :D



void setup() {
  lcd.init();
  lcd.noBacklight();
  //Tells the Arduino to lock in
  
  pinMode(powerPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);

  pinMode(countPin1, INPUT_PULLUP);
  pinMode(countPin5, INPUT_PULLUP);
  pinMode(countPin10, INPUT_PULLUP);
}

void loop() {
  bool change = false;
  //Change, the only constant in this universe
  
  int powerState = digitalRead(powerPin);

  if (powerState == LOW && lastPowerState == HIGH) { state = !state; lcd.clear();
    //Flips the state to save that state now
    
    if(state) { lcd.backlight(); lcd.display(); change = true;  //Turns on
    } else { lcd.noBacklight(); lcd.noDisplay(); } //And now turns off
    delay(100);
  }
  
  lastPowerState = powerState;
  //Retains previous state for next time it is pressed

   if (state == true) {
     int readState1 = digitalRead(countPin1);
     int readState5 = digitalRead(countPin5);
     int readState10 = digitalRead(countPin10);
     int readStateR = digitalRead(resetPin);
     //Reads all of the digital pins so the Arduino can understand it

     //Organized into single lines for maximum readability
      if (readState1 == LOW && lastState1 == HIGH) { atomic += 1; change = true; delay(150); } 
       lastState1 = readState1;
      //If pressed and the previous state was a different state, add the increment, but holding it will only go up by increment
      if (readState5 == LOW && lastState5 == HIGH) { atomic += 5; change = true; delay(150);}
       lastState5 = readState5;

      if (readState10 == LOW && lastState10 == HIGH) { atomic += 10; change = true; delay(150); }
       lastState10 = readState10;
  
      if (readStateR == LOW && lastStateR == HIGH) { atomic = 1; change = true; delay(150); }
       lastStateR = readStateR;

     
     //Makes sure that the atomic number is restricted from 1 to 118 :D
        if(atomic > 118){ atomic = 1; }
        if(atomic < 1){ atomic = 118; }
    }

        //If change is allowed, change it instead of constant updates
           if(change == true) {
            const char* namePtr = (const char*)pgm_read_ptr(&(table[atomic].name));
            const char* groupPtr = (const char*)pgm_read_ptr(&(table[atomic].group));

             //Run down:
             //&(table[atomic].group) is what we are trying to find in the Flash Memory of the Arduino
             //pgm_read_ptr makes it so we actually look into the flash memory
             // (const char*) tells the Arduino that it is a string
             //const char* groupPtr makes it an ACTUAL usable variable to use for later purposes ie. printing it out


             //The actual display itself
            lcd.setCursor(0, 0);
            lcd.print(atomic);
            lcd.print(F(" ")); //If wondering, F is used in Flash Memory, allowing this space to be stored nicely with more room
            lcd.print(namePtr); 
            lcd.print(F("                ")); //Better than using lcd.clear(); to not have a flickering which is slightly annoying
        
            lcd.setCursor(0, 1);
            lcd.print(groupPtr); 
            lcd.print(F("                "));
            change = false;
         }
}
//February 18th, 2026
//This is a periodic table machine
//This will take in an atomic number and tell you
//1. The element name (104 is shortened, ends in -ium, I'll tell you that)
//2. The group it is assigned to, nonmetals, halogens, noble gases, etc
//This was a fun project to switch from Dr.Racket to C++ :D
//Huge double ++ ;)
