// From DHT11 Program
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
static const int DHT_SENSOR_PIN = 7;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

// From LCD Program
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup( )
{
  // From DHT11 Program
  Serial.begin( 9600);

  // From LCD Program
  lcd.begin(16, 2);
  lcd.print("Hello, World!");
}

// From DHT11 Program
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

void loop( )
{
  float temperature;
  float humidity;
  float temp_f;

  if( measure_environment( &temperature, &humidity ) == true )
  {
    temp_f = (temperature * 9 / 5) + 32;
    Serial.print( "T = " );
    Serial.print( temp_f, 1 );
    Serial.print( " deg. F, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );

    
    // From LCD Program
    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);
  }
}
