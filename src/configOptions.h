//--------------------------------
// configOptions,h
//--------------------------------

#pragma once

#include "configSystem.h"


#define OPTION_TYPE_FACTORY_RESET   0x8000
    // triggers confirmDialog, and is the return value from
    // win->getId() in configSystem::onEndModal() when the user
    // confirms they want to do a factory reseet.

#define OPTION_TYPE_SPOOF_FTP_CHANGED 0x4000
    // similarly, changing the PREF_SPOOF_FTP tiggers a confirmDialog,
    // ans is the return value from win->getId() in configSystem::onEndModal()
    // if the user confirms they want to change this setting.
    //
    // The pref shall have already been changed before the dialog, so,
    // if the user confirms they want to change it, ANY PENDING
    // CONFIG changes will be written to EEPROM, and the system
    // will be rebooted.
    //
    // Because there is an associated value, if the user does not
    // confirm, onEndModal() will RESET THE PREF to it's saved value.

#define OPTION_TYPE_STREAM_CHANGED  0x2000
    // an option changed the debug/output stream settings, so
    // initDebugStreams() will be called when any options having
    // this setting are changed.




typedef void (*setterFxn)(int i);
    // a pointer to a function that will be called on options with prefs
    //      when the value changes i.e. setLEDBrightness(value)
    // or a function that will be called (with i=0) on non-pref options
    //      with no children (i.e. startFtpTuner() or startFTPSensitivity()
    //      dialogs;


class configOption
    // items with pref_nums >=0 are tightly bound to prefs,
    // calling getPref() and setPref() for value manipulation,
    // assuming that if the max is > 254 it's a uint16.
{
    public:

        configOption();
        configOption(
            configOption *parent,
            const char *title,
            int type=0,                 // zero, or one of the OPTION_TYPE defines above
            int pref_num=-1,            // items with pref_nums >=0 are tightly bound to prefs
            setterFxn setter=0);        // will be called for pref options with the changed value

    protected:

        friend class configSystem;
        void init();    // recursively called at configSystem::begin(!warm)

        int   getNum()                { return option_num; }
        bool  needsValueDisplay()     { return display_value != getValue(); }
        void  clearDisplayValue()     { display_value = getValue(); }
        const char *getTitle()        { return title; }
        int   getPrefNum()            { return m_pref_num; }
        bool  hasValue()              { return m_pref_num >= 0 ? 1 : 0; }
        void  clearSelected()         { selected =0; display_selected=0; }

        void  setValue(int i);        // enforces min/max
        void  incValue(int inc_dec);  // wraps
        const char *getValueString();

        virtual bool  isEnabled()             { return 1; }

        int           num_children;
        configOption *pParent;
        configOption *pNextOption;
        configOption *pPrevOption;
        configOption *pFirstChild;
        configOption *pLastChild;

        setterFxn   m_setter_fxn;

    private:

        const char *title;
        int         type;
        int         option_num;
        int         m_pref_num;

        int  display_value;
        int  selected;
        int  display_selected;
        int  display_enabled;

    private:

        int getValue();
        void init_cold(configOption *parent, const char *tit, int typ, int pref_num, setterFxn setter);
            // ctor initialization
};


#define ENABLED_CONFIG(class_name,condition)  \
    class class_name : public configOption    \
    {                                         \
    public:                                   \
                                              \
       class_name(                            \
            configOption *parent,             \
            const char *title,                \
            int type=0,                       \
            int pref_num=-1,                  \
            setterFxn setter=0) :             \
                configOption(                 \
                    parent,                   \
                    title,                    \
                    type,                     \
                    pref_num,                 \
                    setter) {}                \
                                              \
        virtual bool  isEnabled()             \
            { return (condition); }           \
    }

