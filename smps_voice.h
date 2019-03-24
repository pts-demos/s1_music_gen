#ifndef SMPS_VOICE_H
#define SMPS_VOICE_H

#include <QFile>

typedef enum
{
	SMPS_FM = 0,
	SMPS_DAC = 1
} VoiceType;

class Smps_voice
{
public:
	Smps_voice();

	void writeInFile(QFile& f);

	VoiceType voice_type;

	int32_t feedback;
	int32_t algorithm;
	int32_t detune_op1;
	int32_t detune_op2;
	int32_t detune_op3;
	int32_t detune_op4;
	int32_t coarse_frequency_multiplier_op1;
	int32_t coarse_frequency_multiplier_op2;
	int32_t coarse_frequency_multiplier_op3;
	int32_t coarse_frequency_multiplier_op4;
	int32_t rate_scale_op1;
	int32_t rate_scale_op2;
	int32_t rate_scale_op3;
	int32_t rate_scale_op4;
	int32_t attack_rate_op1;
	int32_t attack_rate_op2;
	int32_t attack_rate_op3;
	int32_t attack_rate_op4;
	bool lfo_enabled_op1;
	bool lfo_enabled_op2;
	bool lfo_enabled_op3;
	bool lfo_enabled_op4;
	int32_t first_decay_rate_op1;
	int32_t first_decay_rate_op2;
	int32_t first_decay_rate_op3;
	int32_t first_decay_rate_op4;
	int32_t second_decay_rate_op1;
	int32_t second_decay_rate_op2;
	int32_t second_decay_rate_op3;
	int32_t second_decay_rate_op4;
	int32_t first_decay_level_op1;
	int32_t first_decay_level_op2;
	int32_t first_decay_level_op3;
	int32_t first_decay_level_op4;
	int32_t release_rate_op1;
	int32_t release_rate_op2;
	int32_t release_rate_op3;
	int32_t release_rate_op4;
	int32_t total_level_op1;
	int32_t total_level_op2;
	int32_t total_level_op3;
	int32_t total_level_op4;
};

#endif // SMPS_VOICE_H
