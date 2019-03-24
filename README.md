# Sonic 1 Music Gen

Tool for importing and exporting Sonic 1 SMPS music files, as well as ideally composing new music. No playback features are planned.

Sonic 1 stores in a format which has been labeled by romhackers as "SMPS", Sample Music Playback System. This format contains the following information:

* A general song header
* Specifics about which channels are in use. These channels are:
    * 6x FM (frequency modulation) and DAC (PCM playback?) on Yamaha YM2612
    * 3x PSG (Programmable Sound Generator) on SN76489
* Pattern information, much like in most music tracker formats
* FM voice synthesis table data

Details about the format can be found in the following places:
    * https://segaretro.org/SMPS/Headers
    * https://segaretro.org/SMPS/Voices_and_samples
    * http://info.sonicretro.org/SCHG:Music_Hacking/Pointer_and_Header_Format
    * http://info.sonicretro.org/SCHG:Music_Hacking/Voice_and_Note_Editing