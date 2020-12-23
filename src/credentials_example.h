const char* ssid = "SSID";
const char* password = "PASSWORD";

const char* project_id = "GCP-PROJECT-ID";
const char* location = "us-central1";
const char* registry_id = "water-pump";
const char* device_id = "water-pump";

const char* private_key_str = "";

// Time (seconds) to expire token += 20 minutes for drift
const int jwt_exp_secs = 3600; // Maximum 24H (3600*24)