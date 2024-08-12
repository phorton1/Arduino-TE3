The vGuitar System is a [Foot
Pedal](https://github.com/phorton1/Arduino-TE3), [USB Audio and
Midi](https://github.com/phorton1/Arduino-TE3_hub) interface, and a
built in [Looper](https://github.com/phorton1/circle-prh-apps-Looper)
that connects to an **iPad** which provides Guitar Effects and a
Synthesizer for a \`[Fishman Triple
Play](https://www.fishman.com/tripleplay/) (FTP) guitar synthesizer
pickup, all in a single box.

Table of Contents

[1 Overview [1](#overview)](#overview)

[2 Requirements [1](#requirements)](#requirements)

[2.1 External Connections
[1](#external-connections)](#external-connections)

[2.2 Built in UI and Controls
[1](#built-in-ui-and-controls)](#built-in-ui-and-controls)

[2.3 For Makers [1](#for-makers)](#for-makers)

[2.4 For my own Sanity [1](#for-my-own-sanity)](#for-my-own-sanity)

[3 Architecture [1](#architecture)](#architecture)

[3.1 Architectural Overview
[1](#architectural-overview)](#architectural-overview)

[3.2 TE3_hub -- the teensy 4.0 USB Audio and Midi device with Host
[2](#te3_hub-the-teensy-4.0-usb-audio-and-midi-device-with-host)](#te3_hub-the-teensy-4.0-usb-audio-and-midi-device-with-host)

[3.3 TE3 - the teensy 4.1 Foot Pedal MIDI controller
[2](#te3---the-teensy-4.1-foot-pedal-midi-controller)](#te3---the-teensy-4.1-foot-pedal-midi-controller)

[3.4 Looper -- the circle rPi 3B+ application
[2](#looper-the-circle-rpi-3b-application)](#looper-the-circle-rpi-3b-application)

[4 Design [2](#design)](#design)

[5 Implementation [2](#implementation)](#implementation)

[6 Topics [2](#topics)](#topics)

[6.1 Recap of Midi Protocol
[2](#recap-of-midi-protocol)](#recap-of-midi-protocol)

[6.2 [2](#section)](#section)

[7 Appendices [2](#appendices)](#appendices)

This some text after the TOC

# Overview

The vGuitar rig is a [Foot
Pedal](https://github.com/phorton1/Arduino-TE3), [USB Audio and
Midi](https://github.com/phorton1/Arduino-TE3_hub) interface, and a
built in [Looper](https://github.com/phorton1/circle-prh-apps-Looper)
that connects to an **iPad** which provides Guitar Effects and a
Synthesizer for a \`[Fishman Triple
Play](https://www.fishman.com/tripleplay/) (FTP) guitar synthesizer
pickup.

It has many features, including:

-   Blah

-   Blah

-   Blah

It is totally 3D printed, and this repository and related repositories
include all of the source code, 3D printing and Circuit Board schematics
and design materials necessary for anyone to make one.

# Requirements

## External Connections

Provides the following

-   a single USBC power in plug that powers everything

-   a single USBC cable to the iPad

-   MIDI host port for the FTP

-   Guitar-In 1/4\" jack

-   1/8\" jack or RCA-pair that connects to an external amplifier (PA)

-   Four 1/4\" jacks for Expression Pedals

-   Micro USB port to the teensy 4.1

after

## Built in UI and Controls

## For Makers

## For my own Sanity

### Synthesizer

### Guitar Effects

# Architecture

## Architectural Overview

## TE3_hub -- the teensy 4.0 USB Audio and Midi device with Host

## TE3 - the teensy 4.1 Foot Pedal MIDI controller

## Looper -- the circle rPi 3B+ application

# Design

# Implementation

# Topics

## Recap of Midi Protocol

## 

# Appendices
