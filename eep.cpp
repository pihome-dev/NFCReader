#include "nfcreader.h"

void init_eeprom() {
  
  if (EEPROM.read(EESIZE) != 10) {
    for (int i=0; i<EESIZE-1; i++) {
      EEPROM.write(i, 0);
    }
    EEPROM.write(EESIZE, 10);
  }

  // Read KeyTag Data

  int tc = 0;

  for (int i=(TAGS_COUNT-EESIZE); i<EESIZE; i++) {
    //keyTagID[tc].id0 = EEPROM.read(i);
    //keyTagID[tc].id1 = EEPROM.read(i);
    //keyTagID[tc].id2 = EEPROM.read(i);
    //keyTagID[tc].id3 = EEPROM.read(i);
    //keyTagID[tc].en = EEPROM.read(i);
    //keyTagID[tc].mode = EEPROM.read(i);
    tc++;
  }
}
