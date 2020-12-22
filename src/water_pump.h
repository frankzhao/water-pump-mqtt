void setupPump();

// power is a percentage
void pump(int pumpTimeMs);

// read power for pump using analog in
float readPower();   // normalize power between 0-1

void loopPump();
