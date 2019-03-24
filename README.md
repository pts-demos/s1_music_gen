# Sonic 1 Music Gen

Tool for importing and exporting Sonic 1 SMPS music files, as well as ideally composing new music. No playback features are planned.

Sonic 1 stores its music in a format which has been labeled by romhackers as "SMPS", Sample Music Playback System. This format contains the following information:

* A general song header
* Specifics about which channels are in use. These channels are:
    * 6x FM (frequency modulation) and DAC (PCM playback?) on Yamaha YM2612
    * 3x PSG (Programmable Sound Generator) on SN76489
* Header for each channel
* Pattern information, much like in most music tracker formats
* FM voice synthesis table data

Details about the format can be found in the following places:
    * https://segaretro.org/SMPS/Headers
    * https://segaretro.org/SMPS/Voices_and_samples
    * http://info.sonicretro.org/SCHG:Music_Hacking/Pointer_and_Header_Format
    * http://info.sonicretro.org/SCHG:Music_Hacking/Voice_and_Note_Editing
    
### Compiling

* Get Qt Creator, version 5 or later
* Get a working modern compiler
    * qmake sonic1_music_gen.pro && make
    * alternatively open the .pro with Qt Creator, run qmake, compile