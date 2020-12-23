void setupPump();

// Pump time in ms, power is 0-255
void pump(int pumpTimeMs, int pumpPower);

// read power for pump using analog in
float readPower();   // normalize power between 0-1
