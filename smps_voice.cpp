#include "smps_voice.h"
#include <QDebug>

Smps_voice::Smps_voice()
{
	feedback = 0;
	algorithm = 0;
	detune_op1 = 0;
	detune_op2 = 0;
	detune_op3 = 0;
	detune_op4 = 0;
	coarse_frequency_multiplier_op1 = 0;
	coarse_frequency_multiplier_op2 = 0;
	coarse_frequency_multiplier_op3 = 0;
	coarse_frequency_multiplier_op4 = 0;
	rate_scale_op1 = 0;
	rate_scale_op2 = 0;
	rate_scale_op3 = 0;
	rate_scale_op4 = 0;
	attack_rate_op1 = 0;
	attack_rate_op2 = 0;
	attack_rate_op3 = 0;
	attack_rate_op4 = 0;
	lfo_enabled_op1 = false;
	lfo_enabled_op2 = false;
	lfo_enabled_op3 = false;
	lfo_enabled_op4 = false;
	first_decay_rate_op1 = 0;
	first_decay_rate_op2 = 0;
	first_decay_rate_op3 = 0;
	first_decay_rate_op4 = 0;
	second_decay_rate_op1 = 0;
	second_decay_rate_op2 = 0;
	second_decay_rate_op3 = 0;
	second_decay_rate_op4 = 0;
	first_decay_level_op1 = 0;
	first_decay_level_op2 = 0;
	first_decay_level_op3 = 0;
	first_decay_level_op4 = 0;
	release_rate_op1 = 0;
	release_rate_op2 = 0;
	release_rate_op3 = 0;
	release_rate_op4 = 0;
	total_level_op1 = 0;
	total_level_op2 = 0;
	total_level_op3 = 0;
	total_level_op4 = 0;
	enabled = false;
}


void Smps_voice::writeInFile(QFile &f)
{
	if (!f.isOpen()) {
		qDebug() << "Error: Cannot write smps voice in file: File is not open";
		return;
	}
}
