Copied from:

* http://info.sonicretro.org/SCHG:Music_Hacking/DAC_Samples,_Coordination_Flags,_Game_Specifics,_and_Real-Time_Music_Editing
* http://info.sonicretro.org/SCHG:Music_Hacking/Voice_and_Note_Editing

### Hex ranges

$00-$7F: Note duration (How long a note is held for)
$80-$DF: Notes (80 is a rest)
$E0-$FF: Coordination flags

### Note Value Equivalents

$81	C
$82	C♯/D♭
$83	D
$84	D♯/E♭
$85	E
$86	F
$87	F♯/G♭
$88	G
$89	G♯/A♭
$8A	A
$8B	A♯/B♭
$8C	B
$8D	1C
$8E	1C♯/D♭
$8F	1D
$90	1D♯/E♭
$91	1E
$92	1F
$93	1F♯/G♭
$94	1G
$95	1G♯/A♭
$96	1A
$97	1A♯/B♭
$98	1B
$99	2C
$9A	2C♯/D♭
$9B	2D
$9C	2D♯/E♭
$9D	2E
$9E	2F
$9F	2F♯/G♭
$A0	2G
$A1	2G♯/A♭
$A2	2A
$A3	2A♯/B♭
$A4	2B
$A5	3C
$A6	3C♯/D♭
$A7	3D
$A8	3D♯/E♭
$A9	3E
$AA	3F
$AB	3F♯/G♭
$AC	3G
$AD	3G♯/A♭
$AE	3A
$AF	3A♯/B♭
$B0	3B
$B1	4C
$B2	4C♯/D♭
$B3	4D
$B4	4D♯/E♭
$B5	4E
$B6	4F
$B7	4F♯/G♭
$B8	4G
$B9	4G♯/A♭
$BA	4A
$BB	4A♯/B♭
$BC	4B
$BD	5C
$BE	5C♯/D♭
$BF	5D
$C0	5D♯/E♭
$C1	5E
$C2	5F
$C3	5F♯/G♭
$C4	5G
$C5	5G♯/A♭
$C6	5A
$C7	5A♯/B♭
$C8	5B
$C9	6C
$CA	6C♯/D♭
$CB	6D
$CC	6D♯/E♭
$CD	6E
$CE	6F
$CF	6F♯/G♭
$D0	6G
$D1	6G♯/A♭
$D2	6A
$D3	6A♯/B♭
$D4	6B
$D5	7C
$D6	7C♯/D♭
$D7	7D
$D8	7D♯/E♭
$D9	7E
$DA	7F
$DB	7F♯/G♭
$DC	7G
$DD	7G♯/A♭
$DE	7A
$DF	7A♯/B♭

### Coordinate flags

Flag Parameters Purpose
$E0	%[l][r][aaa]0[ff]	Alter panning. Does not work for PSG tracks. The flag can be used to alter AMS and FMS, but it is not meant to; it can only set those bits if they were zero to begin with — you can never clear them. Has one parameter byte.
$E1	$[ff]	Set the channel frequency displacement to the parameter byte (signed).
$E2	$[vv]	Sets RAM variable at $FFFFF007 to the parameter byte. Useless
$E3	none	Return from subroutine. See also coord. flag $F8. No parameters.
$E4	none	Stops the track and initiates a fade-in to previous song. Has no parameters (not that it matters...). Can be in any channel; since the DAC channel is the first to be run, this prevents note artifacts from the other channels if placed on it.
$E5	$[tt]	Set dividing timing for the current track to the parameter byte.
$E6	$[vv]	Add parameter byte to volume attenuation, effective immediately. This is not intended for PSG tracks, and will wreak havoc on unrelated FM tracks if used on a PSG track. (This flag is designed for FM channels)
$E7	none	Prevent note from attacking. This is reset after every note expires; so to keep it going, you must put this coordination flag before each note you wish to effect. No parameters.
$E8	$[ff]	Sets note fill to the parameter byte. The note fill is a timeout: the number of frames during which the note will be allowed to play. After that, the note will be killed and will stay dead until it is time for another note.
$E9	$[ff]	Adds (signed) parameter to channel key displacement.
$EA	$[tt]	Set main tempo to the parameter byte. Only affects music, not SFX. Has immediate effect, and may shorten the currently playing notes on all tracks.
$EB	$[dd]	Sets dividing timing to be equal to the parameter byte for all *music* tracks — it does not effect SFX.
$EC	$[vv]	Changes channel volume by adding the parameter byte (signed) to the track's volume. For FM channels, only takes effect on the next voice change. (This flag is designed for PSG channels)
$ED	none	Clears 'pushing block' flag. This flag is set when SFX $A7 is played, and prevents it from playing again. No parameters.
$EE	none	Stops a track. This coordination flag assumes that the track in question is channel FM4 for a sound effect with index $D0-$DF, so don't use it for anything else. If the FM4 channel was being overridden by a normal sound effect, nothing else happens; otherwise, it will upload the current FM4 instrument for the currently playing music. No parameters.
$EF	$[vv]	Change FM instrument to parameter byte. Uploads the corresponding instrument to the YM2612, which means: NOT for PSG or DAC.
$F0	$[ww][mm][cc][ss]	Sets modulation parameters and enables it. Takes 4 1-byte parameters, which are, in order: wait speed before modulation starts, modulation speed, change per step, number of steps. Using this flag will clear accumulated modulation. A wait of zero means no wait; compare with equivalent Sonic 3+ flag.
$F1	none	Enables modulation. Can be safely used only after coord. flag $F0 has been used for the current track. No parameters.
$F2	none	Stop track. FM voices and PSG noise tones are updated if needed.
$F3	$[nn]	Sets PSG track to noise and sets PSG noise to parameter byte, which should be from $E0 to $E7 (inclusive). The transformation into a noise channel is irreversible.
$F4	none	Disable modulation. No parameters.
$F5	$[tt]	Change PSG tone (index into flutter table) to parameter byte.
$F6	$[dddd]	Jump to target location. Parameter is 2-byte Big Endian offset to target location that points to one more than the offset says.
$F7	$[ll][cc][dddd]	Repeat section of music. Has 4 bytes of parameters: a 1-byte loop index, a 1-byte repeat count and a 2-byte target for jump. Jump target is 2-byte Big Endian offset to target location that points to one more than the offset says.
$F8	$[dddd]	Call subroutine. Stores current location for use with coord. flag $E3. Parameter is 2-byte Big Endian, signed, relative offset to target location that points to one more than the offset says.
$F9	none	Sets D1L to maximum volume (minimum attenuation) and RR to maximum for operators 3 and 4 of FM1. Does not have parameters.
