// أرجل الحساسات الأربعة (عدّل الأرقام إذا شبكت على رجل مختلفة)
const int TRIG_FRONT = 5,  ECHO_FRONT = 18;
const int TRIG_LEFT  = 19, ECHO_LEFT  = 21;
const int TRIG_RIGHT = 27, ECHO_RIGHT = 23;
const int TRIG_DOWN  = 25, ECHO_DOWN  = 26;

// مؤشرات الحالة
const int LED_SAFE   = 2;
const int LED_AVOID  = 4;

// عتبات الأمان بالسنتيمتر
const float FRONT_LIMIT_CM = 50.0;
const float SIDE_LIMIT_CM  = 60.0;
const float LOW_ALT_CM     = 25.0;

float readDist(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 999.0;
  return (duration * 0.0343f) / 2.0f;
}

void setup() {
  Serial.begin(115200);

  int trigs[] = {TRIG_FRONT, TRIG_LEFT, TRIG_RIGHT, TRIG_DOWN};
  int echos[] = {ECHO_FRONT, ECHO_LEFT, ECHO_RIGHT, ECHO_DOWN};

  for (int i = 0; i < 4; i++) {
    pinMode(trigs[i], OUTPUT);
    pinMode(echos[i], INPUT);
  }

  pinMode(LED_SAFE, OUTPUT);
  pinMode(LED_AVOID, OUTPUT);
}

void loop() {
  float f = readDist(TRIG_FRONT, ECHO_FRONT);
  float l = readDist(TRIG_LEFT,  ECHO_LEFT);
  float r = readDist(TRIG_RIGHT, ECHO_RIGHT);
  float d = readDist(TRIG_DOWN,  ECHO_DOWN);

  Serial.print("F:");
  Serial.print(f, 1);
  Serial.print(" | L:");
  Serial.print(l, 1);
  Serial.print(" | R:");
  Serial.print(r, 1);
  Serial.print(" | D:");
  Serial.print(d, 1);
  Serial.print(" cm -> ");

  if (d < LOW_ALT_CM) {
    digitalWrite(LED_SAFE, LOW);
    digitalWrite(LED_AVOID, HIGH);
    Serial.println("DECISION: Too low / bottom obstacle -> CLIMB UP");
  } else if (f < FRONT_LIMIT_CM) {
    digitalWrite(LED_SAFE, LOW);
    digitalWrite(LED_AVOID, HIGH);

    if (l > r && l > SIDE_LIMIT_CM) {
      Serial.println("DECISION: Front blocked -> TURN LEFT");
    } else if (r >= l && r > SIDE_LIMIT_CM) {
      Serial.println("DECISION: Front blocked -> TURN RIGHT");
    } else {
      Serial.println("DECISION: Sides tight -> CLIMB UP / HOVER");
    }
  } else {
    digitalWrite(LED_SAFE, HIGH);
    digitalWrite(LED_AVOID, LOW);
    Serial.println("DECISION: Clear path -> MAINTAIN COURSE");
  }

  delay(200);
}