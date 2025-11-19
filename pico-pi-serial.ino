// =====================================================================
// MANUAL RAW IR TEST + UART0 (GP0/GP1) COMMAND INPUT
// Commands come from UART0 (Serial1), like RS232->TTL or Arduino UNO.
// =====================================================================

#include <Arduino.h>

// ========== IR DEFINITIONS ==========
const int IR_PIN = 29;
const unsigned int CARRIER_KHZ = 36;

//Phillps Commands

uint16_t rawPowerOffP[] = {
  888, 896, 1760, 876, 880, 876, 880, 876, 876, 880, 884, 872, 884, 872,
  860, 900, 856, 1776, 884, 872, 1760, 876, 856, 24164, 912, 876, 1756,
  876, 880, 876, 884, 872, 884, 876, 880, 876, 880, 876, 856, 900, 856,
  1776, 884, 872, 1736, 900, 856, 24164, 916, 872, 1760, 872, 860, 900,
  856, 900, 856, 900, 880, 876, 856, 900, 856, 900, 856, 1780, 880, 876,
  1736, 896, 860
};

uint16_t rawPowerOnP[] = {
  888, 896, 1760, 876, 880, 876, 880, 876, 876, 880, 884, 872, 884, 872,
  860, 900, 856, 1776, 884, 872, 1760, 876, 856, 24164, 912, 876, 1756,
  876, 880, 876, 884, 872, 884, 876, 880, 876, 880, 876, 856, 900, 856,
  1776, 884, 872, 1736, 900, 856, 24164, 916, 872, 1760, 872, 860, 900,
  856, 900, 856, 900, 880, 876, 856, 900, 856, 900, 856, 1780, 880, 876,
  1736, 896, 860
};

uint16_t rawVolUpP[] = {
  888, 888, 888, 888, 1776, 888, 888, 888, 888, 888, 888, 888, 888, 888, 
  888, 1776, 1776, 888, 888, 888, 888, 888, 888
};

uint16_t rawVolDownP[] = {
  888, 888, 1776, 888, 888, 888, 888, 888, 888, 888, 888, 888, 888, 888, 
  888,  1776, 1776, 888, 888, 888, 888, 1776, 888
};

uint16_t rawVolMuteP[] = {
  888, 888, 1776, 888, 888, 888, 888, 888, 888, 888, 888, 888, 888, 888,
  888, 888, 888, 1776, 888, 888, 1776, 1776, 888
};

//Samsung Commands

uint16_t rawPowerOffS[] = {
  4464, 4488, 600, 1632, 576, 1628, 576, 1628, 576, 540, 
  576, 540, 576, 540, 576, 540, 576, 540, 572, 1632, 
  576, 1628, 576, 1628, 552, 564, 576, 540, 576, 540, 
  552, 564, 576, 540, 576, 540, 572, 544, 572, 544, 
  572, 1632, 572, 1632, 576, 540, 576, 540, 576, 1628, 
  576, 1628, 580, 1628, 576, 1628, 552, 564, 576, 540, 
  576, 1628, 576, 1628, 552, 568, 548, 47572, 4444, 4508, 
  604, 1628, 576, 1628, 576, 1632, 552, 564, 576, 540, 
  572, 544, 576, 536, 576, 540, 576, 1628, 580, 1628, 
  576, 1628, 576, 540, 576, 540, 580, 536, 576, 540, 
  576, 540, 576, 536, 580, 536, 580, 536, 580, 1624, 
  584, 1624, 580, 536, 580, 536, 576, 1628, 580, 1624, 
  584, 1620, 584, 1600, 604, 536, 580, 536, 580, 1596, 
  608, 1596, 608, 536, 584, 47540, 4476, 4472, 612, 1596, 
  608, 1596, 612, 1592, 612, 532, 584, 532, 608, 508, 
  580, 536, 580, 536, 584, 1592, 612, 1592, 632, 1576, 
  608, 508, 608, 508, 628, 488, 604, 512, 604, 512, 
  608, 504, 608, 508, 608, 508, 604, 1600, 604, 1604, 
  604, 508, 604, 512, 604, 1600, 604, 1604, 600, 1604, 
  604, 1600, 604, 512, 600, 516, 600, 1608, 596, 1608, 
  600, 516, 600
};

uint16_t rawPowerOnS[] = {
	4472, 4484, 600, 1628, 576, 1628, 580, 1628, 576, 540,
	576, 540, 576, 540, 576, 540, 572, 540, 576, 1628,
	576, 1632, 576, 1628, 576, 540, 576, 540, 576, 540,
	576, 540, 576, 540, 560, 1644, 576, 540, 576, 540,
	552, 1652, 580, 1628, 576, 540, 576, 540, 576, 1624,
	580, 540, 576, 1628, 580, 1624, 580, 536, 580, 536,
	580, 1596, 608, 1600, 608, 536, 580, 47544, 4472, 4476,
	612, 1592, 612, 1596, 632, 1572, 608, 512, 604, 508,
	608, 508, 608, 508, 628, 488, 604, 1600, 604, 1600,
	608, 1596, 608, 512, 600, 516, 600, 512, 604, 512,
	604, 512, 604, 1600, 604, 512, 604, 512, 600, 1604,
	604, 1604, 600, 516, 600, 516, 596, 1608, 600, 516,
	596, 1608, 600, 1604, 600, 520, 596, 520, 596, 1604,
	600, 1608, 596, 520, 596, 47552, 4468, 4484, 600, 1608,
	596, 1608, 596, 1608, 596, 524, 592, 524, 592, 524,
	592, 520, 596, 524, 592, 1608, 596, 1608, 596, 1612,
	596, 544, 568, 548, 572, 540, 572, 544, 572, 544,
	572, 1612, 592, 544, 572, 544, 572, 1612, 592, 1612,
	592, 548, 568, 548, 568, 1612, 592, 548, 568, 1616,
	588, 1616, 592, 548, 568, 544, 572, 1612, 592, 1612,
	592, 548, 568
};

uint16_t rawVolUpS[] = {
	4507, 4507, 573, 1694, 573, 1694, 573, 1694, 573, 573,
	573, 573, 573, 573, 573, 573, 573, 573, 573, 1694,
	573, 1694, 573, 1694, 573, 573, 573, 573, 573, 573,
	573, 573, 573, 573, 573, 1694, 573, 1694, 573, 1694,
	573, 573, 573, 573, 573, 573, 573, 573, 573, 573,
	573, 573, 573, 573, 573, 573, 573, 1694, 573, 1694,
	573, 1694, 573, 1694, 573, 1694, 573
};

uint16_t rawVolDownS[] = {
	4507, 4507, 573, 1694, 573, 1694, 573, 1694, 573, 573,
	573, 573, 573, 573, 573, 573, 573, 573, 573, 1694,
	573, 1694, 573, 1694, 573, 573, 573, 573, 573, 573,
	573, 573, 573, 573, 573, 1694, 573, 1694, 573, 573,
	573, 1694, 573, 573, 573, 573, 573, 573, 573, 573,
	573, 573, 573, 573, 573, 1694, 573, 573, 573, 1694,
	573, 1694, 573, 1694, 573, 1694, 573
};

uint16_t rawVolMuteS[] = {
  4507, 4507, 573, 1694, 573, 1694, 573, 1694, 573, 573, 573, 573, 573, 573, 573,
  573, 573, 573, 573, 1694, 573, 1694, 573, 1694, 573, 573, 573, 573, 573, 573,
  573, 573, 573, 573, 573, 1694, 573, 1694, 573, 1694, 573, 1694, 573, 573, 573,
  573, 573, 573, 573, 573, 573, 573, 573, 573, 573, 573
};

// ========== IR LOW-LEVEL FUNCTIONS ==========
inline unsigned int halfPeriodMicros(unsigned int khz) {
  return (unsigned int)(500.0 / khz + 0.5);
}

void sendCarrierBlocking(unsigned long duration_us, unsigned int khz, int pin) {
  if (duration_us <= 0) return;

  unsigned int half = halfPeriodMicros(khz);
  unsigned long start = micros();

  while ((unsigned long)(micros() - start) < duration_us) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(half);
    digitalWrite(pin, LOW);
    delayMicroseconds(half);
  }
}

void sendRawManual(const uint16_t *data, size_t length, unsigned int khz, int pin) {
  for (size_t i = 0; i < length; i++) {
    unsigned long dur = data[i];

    if ((i & 1) == 0) {
      sendCarrierBlocking(dur, khz, pin);
      digitalWrite(pin, LOW);
    } else {
      unsigned long t0 = micros();
      while ((unsigned long)(micros() - t0) < dur) {
        digitalWrite(pin, LOW);
      }
    }

    yield();
  }
}

void printRaw(const uint16_t *data, size_t length) {
  Serial.print("RAW [");
  Serial.print(length);
  Serial.println("]:");
  for (size_t i = 0; i < length; i++) {
    Serial.print(data[i]);
    if (i < length - 1) Serial.print(", ");
  }
  Serial.println();
  Serial.println("-----------------------------------");
}

// =====================================================================
// SETUP
// =====================================================================
void setup() {
  // USB Serial for debug
  Serial.begin(115200);
  
  Serial.println("Pico IR Receiver-Executor ready.");
  Serial.println("Waiting commands on UART0 (GP1 RX)...");

  // UART0 on GP0/GP1
  Serial1.begin(9600);
  //pinMode(1, INPUT_PULLUP);
  pinMode(IR_PIN, OUTPUT);
  digitalWrite(IR_PIN, LOW);

}

// =====================================================================
// LOOP
// =====================================================================
void loop() {
  // ---------- READ from UART0 (GP1) ----------
  if (Serial1.available()) {
    String cmd = Serial1.readStringUntil('\n');
    cmd.trim();
    cmd.toLowerCase();

    if (cmd.length() == 0) return;

    // Show on USB Serial monitor
    Serial.print("Received on UART0: ");
    Serial.println(cmd);

    
    // ---------- EXECUTE ----------
    if (cmd.indexOf("ofp") >= 0) {
      Serial.println("Sending IR: PHILLIPS POWER OFF");
      printRaw(rawPowerOffP, sizeof(rawPowerOffP)/sizeof(rawPowerOffP[0]));
      sendRawManual(rawPowerOffP, sizeof(rawPowerOffP)/sizeof(rawPowerOffP[0]), CARRIER_KHZ, IR_PIN);
      Serial.println("Done.");

    } else if (cmd.indexOf("onp") >= 0) {
      Serial.println("Sending IR: PHILLIPS POWER ON");
      printRaw(rawPowerOnP, sizeof(rawPowerOnP)/sizeof(rawPowerOnP[0]));
      sendRawManual(rawPowerOnP, sizeof(rawPowerOnP)/sizeof(rawPowerOnP[0]), CARRIER_KHZ, IR_PIN);
      Serial.println("Done.");

    } else if (cmd.indexOf("upp") >= 0) {
      Serial.println("Sending IR: PHILLIPS VOL UP");
      printRaw(rawVolUpP, sizeof(rawVolUpP)/sizeof(rawVolUpP[0]));
      sendRawManual(rawVolUpP, sizeof(rawVolUpP)/sizeof(rawVolUpP[0]), CARRIER_KHZ, IR_PIN);
      Serial.println("Done."); 

    } else if (cmd.indexOf("dop") >= 0) {
      Serial.println("Sending IR: PHILLIPS VOL DOWN");
      printRaw(rawVolDownP, sizeof(rawVolDownP)/sizeof(rawVolDownP[0]));
      sendRawManual(rawVolDownP, sizeof(rawVolDownP)/sizeof(rawVolDownP[0]), CARRIER_KHZ, IR_PIN);
      Serial.println("Done.");    

    } else if (cmd.indexOf("mup") >= 0) {
      Serial.println("Sending IR: PHILLIPS VOL MUTE");
      printRaw(rawVolMuteP, sizeof(rawVolMuteP)/sizeof(rawVolMuteP[0]));
      sendRawManual(rawVolMuteP, sizeof(rawVolMuteP)/sizeof(rawVolMuteP[0]), CARRIER_KHZ, IR_PIN);
      Serial.println("Done."); 

    } else if (cmd.indexOf("ofs") >= 0) {
      Serial.println("Sending IR: SAMSUNG POWER OFF");
      printRaw(rawPowerOffS, sizeof(rawPowerOffS)/sizeof(rawPowerOffS[0]));
      sendRawManual(rawPowerOffS, sizeof(rawPowerOffS)/sizeof(rawPowerOffS[0]), CARRIER_KHZ, IR_PIN);
      Serial.println("Done.");

    } else if (cmd.indexOf("ons") >= 0) {
      Serial.println("Sending IR: SAMSUNG POWER ON");
      printRaw(rawPowerOnS, sizeof(rawPowerOnS)/sizeof(rawPowerOnS[0]));
      sendRawManual(rawPowerOnS, sizeof(rawPowerOnS)/sizeof(rawPowerOnS[0]), CARRIER_KHZ, IR_PIN);
      Serial.println("Done.");

    } else if (cmd.indexOf("ups") >= 0) {
      Serial.println("Sending IR: SAMSUNG VOL UP");
      printRaw(rawVolUpS, sizeof(rawVolUpS)/sizeof(rawVolUpS[0]));
      sendRawManual(rawVolUpS, sizeof(rawVolUpS)/sizeof(rawVolUpS[0]), CARRIER_KHZ, IR_PIN);
      Serial.println("Done.");

    } else if (cmd.indexOf("dos") >= 0) {
      Serial.println("Sending IR: SAMSUNG VOL DOWN");
      printRaw(rawVolDownS, sizeof(rawVolDownS)/sizeof(rawVolDownS[0]));
      sendRawManual(rawVolDownS, sizeof(rawVolDownS)/sizeof(rawVolDownS[0]), CARRIER_KHZ, IR_PIN);
      Serial.println("Done.");

    } else if (cmd.indexOf("mus") >= 0) {
      Serial.println("Sending IR: SAMSUNG VOL MUTE");
      printRaw(rawVolMuteS, sizeof(rawVolMuteS)/sizeof(rawVolMuteS[0]));
      sendRawManual(rawVolMuteS, sizeof(rawVolMuteS)/sizeof(rawVolMuteS[0]), CARRIER_KHZ, IR_PIN);
      Serial.println("Done.");
      
    } else {
      Serial.println("UNKNOWN COMMAND.");
    }
    Serial.println();
  }
}


