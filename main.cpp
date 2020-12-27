
#include "mbed.h"
#if defined(TARGET_NUCLEO_F303RE) || defined (TARGET_NUCLEO_F746ZG)
#include "BMP180Wrapper.h"
#endif
#include "HTS221Sensor.h"
#include "OLEDDisplay.h"

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

static DevI2C devI2c( MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL );
#if defined(TARGET_NUCLEO_F303RE) || defined (TARGET_NUCLEO_F746ZG)
static BMP180Wrapper hum_temp( &devI2c );
#else
static HTS221Sensor hum_temp(&devI2c);
#endif

int main()
{
    uint8_t id;
    float value1, value2;
    
    oled.clear();
    oled.printf( "Temp/Hum Sensor\n" );
    
    /* Init all sensors with default params */
    hum_temp.init(NULL);
    hum_temp.enable();
    
    hum_temp.read_id(&id);
    printf("HTS221  humidity & temperature    = 0x%X\r\n", id);

    while (true) 
    {
        hum_temp.get_temperature(&value1);
        hum_temp.get_humidity(&value2);
        printf("HTS221:  [temp] %.2f C, [hum]   %.2f%%\r\n", value1, value2);
        oled.cursor( 1, 0 );
        oled.printf( "temp: %3.2f\nhum : %3.2f", value1, value2 );
        thread_sleep_for( 1000 );
    }
}