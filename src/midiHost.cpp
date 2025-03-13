//-----------------------------------------
// midiHost.cpp
//-----------------------------------------
// To the degree that I am ONLY using this for the FTP,
// AND coupled with the fact that unless we are spoofing
// the FTP, we generally DON'T want to forward every damn
// message from the FTP to the usb midi port, but rather,
// only those that are used in "pefformances", like note_on,
// note_off, and so on.
//
// Furthermore, since the stupid FTP sends everything out
// twice, on both HOST ports, we generally want to limit
// superflous traffic by only accepting the stuff from the
// designated FTP_PORT (whehter it be MIDI_HOST1 || MIDI_HOST2).
//

#define ACCEPT_ONLY_FTP_ACTIVE_PORT     1
    // entirely LIMITS the midi_host to accepting messages that are
    // FROM THE FTP as indicated by the FTP_ACTIVE_PORT.

// The FTP is so weird.  It sends out almost everything twice
// on both HOST1 and HOST2 ports, EXCEPT active_sense, which it
// only sends on HOST2.  I can't remember how I'm supposed to
// talk to it correctly.

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


    bool performanceFilter(uint32_t msg32)
    {
        // get the message type dirctly from the uint32_t

        uint8_t type = msg32 & 0x0f;

        // only accept note on, note off,
        // or pitchbends if the bend_filter is off

        bool allow_bends = !getPref8(PREF_PERF_FILTER_BENDS);

        //  #define MIDI_TYPE_NOTE_OFF		0x08
        //  #define MIDI_TYPE_NOTE_ON		0x09
        //  #define MIDI_TYPE_VELOCITY		0x0A    // not passed at this time
        //  #define MIDI_TYPE_PGM_CHG		0x0C    // not passed
        //  #define MIDI_TYPE_AFTERTOUCH	0x0D    // not passed at this time
        //  #define MIDI_TYPE_PITCHBEND		0x0E

        if (type == MIDI_TYPE_NOTE_OFF ||
            type == MIDI_TYPE_NOTE_ON || (
            type == MIDI_TYPE_PITCHBEND && allow_bends))
        {
            return 1;
        }

        return 0;
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
                    // show DEBUG_RAW_MIDI before anything else
                    // but dont show annoying active sense messages

                    bool is_active_sense = msg32 == 0x0000fe1f;

                    #if DEBUG_RAW_MIDI
                        if (!is_active_sense)
                            display_level(0,0,"host:  0x%08x",msg32);
                    #endif

                    // convert 0x00, 0x10 raw_port to host_port 0x40, 0x50 equivilants

                    int raw_port = (msg32 & MIDI_PORT_NUM_MASK);
                    int host_port = raw_port | MIDI_PORT_HOST1;

                #if ACCEPT_ONLY_FTP_ACTIVE_PORT
                    if (host_port == FTP_ACTIVE_PORT)
                    {
                #endif
                        // enqueue the input message for FTP processing if appropriate,
                        // enqueue the input message to the MIIDI_MONITOR in all cases
                        // and light up the HOST activity indicator

                        #if !ACCEPT_ONLY_FTP_ACTIVE_PORT
                             if (host_port == FTP_ACTIVE_PORT)
                        #endif
                        enqueueFTPIn(host_port, msg32);
                        enqueuMonitor(host_port,false,msg32);
                        theSystem.midiActivity(ACTIVITY_INDICATOR_HOST_IN);

                        // only forward the message to the USB port if SPOOF_FTP, or
                        // if it is not active_sense based on the performance filter

                        bool forward_it = getPref8(PREF_SPOOF_FTP) || (
                            !is_active_sense && (
                            !getPref8(PREF_PERF_FILTER) || performanceFilter(msg32) ));

                        if (forward_it)
                        {
                            any = 1;
                            usb_midi_write_packed(msg32);
                            theSystem.midiActivity(ACTIVITY_INDICATOR_USB_OUT);
                            enqueuMonitor(raw_port,true,msg32);
                        }


                #if ACCEPT_ONLY_FTP_ACTIVE_PORT
                    }
                #endif
               }
            }

            if (any)
                usb_midi_flush_output();
        }

        queue_Data_Transfer(rxpipe, rx_buffer, rx_size, this);
    }


#endif  // WITH_MIDI_HOST


