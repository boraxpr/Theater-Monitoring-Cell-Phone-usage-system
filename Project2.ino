#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_AUTH "Nb3ljs2TZwgIcNWxQeZ864vns0GAqk4_" //Blynk Authentication Token
#define SSID "Memee" //WiFi SSID
#define PASS "afkplease" //WiFi Password


WiFiClient espClient;

// Attach virtual serial terminal to Virtual Pin V1
//WidgetTerminal terminal(V1);
BlynkTimer timer;

//variable for seat 1 in a theater
int seat_1 = 0;

int a =  32;// define the digital interface to connect a seven segment LED
int b =  33;// define the connection b Digital Interface 6-segment LED
int c =  25;// define paragraph (c) Digital Interface 5 digital connection
int d =  26;// define the digital interface 11 is connected to d-segment digital tube
int e =  27;// define the digital interface 10 is connected to e-segment digital tube
int f =  14;// define the digital interface 8 digital tube connection f
int g =  12;// define the digital interface 9 g of the digital control connection
int dp = 13;// define the digital interface 4 digital tube connecting dp

void setup_wifi();

void digital_0 (void) // display the number 0
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  digitalWrite(dp, LOW);
}

void digital_1 (void) // display the number 1
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, LOW);
}

void digital_2 (void) // display number 2
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
}

void digital_3 (void) // display the number 3
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
}

void digital_4 (void) // show 4
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
}

void digital_5 (void) // display the number 5
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
}

void digital_6(void) // display the number 6
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
}

void digital_7(void) // display the number 7
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, LOW);
}

void digital_8 (void) // display the number 8
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
}

void digital_9 (void) // display the number 9
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(dp, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);
  //Test 7segments before long connection to wifi
  digital_0();
  delay(500);
  //Check all system before wifi
  Serial.println(77);
  setup_wifi();
  Blynk.config(BLYNK_AUTH);
}

void loop() {
  Blynk.run();
  //Read LDR value
  seat_1 = analogRead(34);
  //Print LDR value
  Serial.println(seat_1);
  //Val for count lighted seats
  int seat_count = 0;
  if (seat_1 > 2500){ 
    // LDR will be placed behind every seats in a theater. 
    // By testing, If LDR is placed this way even when there is a light from the cinema screen, the LDR value will still be 0.
    // If any light is detected by LDR, It's probably someone plays a mobile phone
    // For demo, it's set to 500

    //seat_count = 1 when LDR is lighted
    seat_count=1;
    //seat_count+=1;
  } else{
    seat_count=0;
    //seat_count+=0; or get rid of else{}
  }
  // in real scenario, there will be seat_num variables equal to the number of seat in a theater
  // when no seat plays cell phone
  if(seat_count == 0){
    //Print 0 on 7 segments
    digital_0();
    //Print 0 on Serial
    Serial.println(0);
    //Write 0 on Blynk virtual 6 pin
    Blynk.virtualWrite(V6, 0);
  }
  else if(seat_count == 1){
    digital_1();
    Serial.println(1);
    Blynk.virtualWrite(V6, 1);
  }
  delay(1000);
}


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
//
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
