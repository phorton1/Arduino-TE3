//-------------------------------------------
// te3_wifi.cpp
//-------------------------------------------

#include "defines.h"
#include <myDebug.h>


#if WITH_WIFI

    #define WIFI_CONNECT_TIMEOUT        10000
    #define WIFI_DISCONNECT_TIMEOUT     10000

	void connectWifi(const String &ssid, const String &pass)
    {
        display(0,"connectWiFi() started",0);
        proc_entry();

        wifi_mode_t mode = WiFi.getMode();
        if (mode != WIFI_AP_STA)
        {
            WiFi.mode(WIFI_STA);
            delay(400);
        }

        #if WITH_TELNET
            if (telnet_started)
            {
                display(0,"telnet stopped",0);
                telnet.stop();
                telnet_started = false;
            }
        #endif

        if (WiFi.status() == WL_CONNECTED)
        {
            WiFi.disconnect();
            display(0,"disconnecting station ...",0);
            uint32_t start = millis();
            while (WiFi.status() == WL_CONNECTED)
            {
                if (millis() > start + WIFI_DISCONNECT_TIMEOUT)
                {
                    my_error("could not discconnect station!!",0);
                    break;
                }
                delay(500);
            }
        }

        if (ssid != "" && pass != "")
        {
            display(0,"Connecting to (%s:%s)",ssid.c_str(),pass.c_str());

            bool timeout = false;
            uint32_t start = millis();
            WiFi.begin(ssid.c_str(),pass.c_str());

            // delay(400);

            while (WiFi.status() != WL_CONNECTED)
            {
                delay(500);
                if (millis() > start + WIFI_CONNECT_TIMEOUT)
                {
                    timeout = true;
                    break;
                }
            }

            if (timeout)
            {
                my_error("Could not connect to %s",ssid.c_str());
            }
            else
            {
                String ip = WiFi.localIP().toString();
                warning(0,"Connected to %s at IP=%s",ssid.c_str(),ip.c_str());

                #if WITH_TELNET
                    telnet.begin();
                    telnet_started = true;
                    display(0,"telnet started",0);
                #endif
            }
        }

        proc_leave();
        display(0,"connectWifi() finished",0);
    }

#endif

