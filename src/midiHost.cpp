//-----------------------------------------
// midiHost.cpp
//-----------------------------------------
// simple one uni-directional midi host
// forwards everything from the HOST port
// to the 1st USB midi port

#include "midiHost.h"

#if WITH_MIDI_HOST

    #include <myDebug.h>
    #include "midiQueue.h"
    #include "expSystem.h"


    USBHost myusb;
    midiHost midi_host;
    midiHost::midiHost() : MIDIDevice(myusb) {}

    void midiHost::init()
    {
        myusb.begin();
    }


    void midiHost::rx_data(const Transfer_t *transfer)
        // made virtual in USBHost_t36.h
    {
        uint32_t len = (transfer->length - ((transfer->qtd.token >> 16) & 0x7FFF)) >> 2;
        if (len)
        {
            bool any = 0;
            for (uint32_t i=0; i < len; i++)
            {
                uint32_t msg32 = rx_buffer[i];
                if (msg32)
                {
                    #if DEBUG_RAW_MIDI
                        if (msg32 !=  0x0000fe1f)     // dont show annoying active sense messages
                            display_level(0,0,"host:  0x%08x",msg32);
                    #endif

                    // we allow for any midi device to be plugged into the host port,
                    // but handle input from the FTP specially.

                    #if 1
                        any = 1;
                        usb_midi_write_packed(msg32);
                        theSystem.midiActivity(ACTIVITY_INDICATOR_USB_OUT);
                    #endif



                    // convert 0x00, 0x10 cable numbers to HOST 0x40, 0x50 equivilants
                    // and send it to the ftp processor if it's the FTP port

                    #if 1
                        int port = (msg32 & MIDI_PORT_NUM_MASK) + MIDI_PORT_HOST1;
                        if (port == FTP_ACTIVE_PORT)
                            enqueueFTPIn(port, msg32);
                        theSystem.midiActivity(ACTIVITY_INDICATOR_HOST_IN);
                    #endif
               }
            }

            if (any)
                usb_midi_flush_output();
        }

        queue_Data_Transfer(rxpipe, rx_buffer, rx_size, this);
    }

#endif  // WITH_MIDI_HOST


