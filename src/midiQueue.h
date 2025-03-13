//----------------------------------------------
// midiQueue.h
//----------------------------------------------
#pragma once

#include "defines.h"
#include "prefs.h"
#include <teMIDI.h>
    // for common definition of msgUnion
    

//------------------------------------------------
// generic sendMidi() methods (in midiQueue.cpp)
//------------------------------------------------

// extern void sendMidiSysex(uint8_t port, int length, const uint8_t *buf);
extern void sendMidiProgramChange(uint8_t port, uint8_t channel, uint8_t prog_num);
extern void sendMidiControlChange(uint8_t port, uint8_t channel, uint8_t cc_num, uint8_t value);



//-------------------------------------
// FTP Midi Handling (in midiQueue.cpp)
//-------------------------------------

extern int FTP_ACTIVE_PORT;
    // Port to which FTP commands will be sent, and which will be monitored
    // for FTP information. Based on PREF_FTP_PORT and PREF_SPOOF_FTP.
    //
    //      Off => -1
    //      Host | PREF_SPOOF_FTP => MIDI_PORT_HOST1
    //      Remote => MIDI_PORT_USB1

extern void setFTPActivePort();
    // Called after prefs loaded in TE3.ino, or when value of PREF_FTP_PORT
    // changes in configSystem.  Note that it is not called when SPOOF_FTP
    // changes, as this causes a system reboot.


extern void enqueueFTPIn(int port, uint32_t msg32);
    // enqueue incoming messages from USB (critical_timer_handler())
    // or MIDI_HOST (interrupt) for processing from timer_handler()
extern void dequeueFTPIn();
    // dequeue FTP messages from slower timer_handler() and process
    // them for information and/or pending commands.

extern void sendFTPCommandAndValue(uint8_t cmd, uint8_t val);
    // enqueue an outgoing FTP CommandAndValue for
    // reply processing and retries
extern bool pendingFTPCount();
    // used to serialize multiple successive FTP commands
    // withouit overlaps
extern void processOutgoingFTPCommands();
    // handle the outgoing FTP command queue by either
    // sending a new command, waiting for a reply
    // or doing a retry
    

//------------------------------------------------
// MIDI Monitoring (in MidiMonitor.cpp)
//------------------------------------------------

extern void enqueuMonitor(int port, bool output, uint32_t msg32);
    // enqueue a completely setup msgUnion for monitoring
extern void dequeueMonitor();
    // dequeue and display monitor messages



// end of midiQueue.h