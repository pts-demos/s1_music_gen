#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "smps_voice.h"

typedef enum {
	LittleEndian = 0,
	BigEndian = 1
} HostEndianess;

namespace Ui {
class MainWindow;
}

typedef struct {
	VoiceType voice_type;
	uint16_t pattern_offset;
	uint16_t pattern_size;
	uint8_t pattern_number;
	uint8_t initial_channel_key_displacement;
	uint8_t initial_channel_volume;
	uint8_t unknown;
	uint8_t initial_voice_num;
} PatternHeader;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void update_ui_controls();

	// Switches the endianess of the given int16_t if the host
	// system does not use big endian
	void toHostEndian(int16_t* data);
	void toHostEndian(uint16_t* data);

	// turns the data into big endian if the host uses little endian
	void toBigEndian(int16_t* data);
	void toBigEndian(uint16_t* data);

	QString byteToHex(uint8_t);

private:
	std::vector<Smps_voice> voices;
	int cur_voice;
	HostEndianess endianess;

private slots:
	void on_voice_next_clicked();
	void on_voice_previous_clicked();
	void on_voice_feedback_valueChanged(int arg1);
	void on_voice_algorithm_valueChanged(int arg1);
	void on_voice_detune_op1_valueChanged(int arg1);
	void on_voice_detune_op3_valueChanged(int arg1);
	void on_voice_detune_op2_valueChanged(int arg1);
	void on_voice_detune_op4_valueChanged(int arg1);
	void on_voice_ratescale_op1_valueChanged(int arg1);
	void on_voice_ratescale_op3_valueChanged(int arg1);
	void on_voice_ratescale_op2_valueChanged(int arg1);
	void on_voice_ratescale_op4_valueChanged(int arg1);
	void on_voice_attack_rate_op_1_valueChanged(int arg1);
	void on_voice_attack_rate_op_3_valueChanged(int arg1);
	void on_voice_attack_rate_op_2_valueChanged(int arg1);
	void on_voice_attack_rate_op_4_valueChanged(int arg1);
	void on_voice_first_decay_rate_op1_valueChanged(int arg1);
	void on_voice_first_decay_rate_op2_valueChanged(int arg1);
	void on_voice_first_decay_rate_op3_valueChanged(int arg1);
	void on_voice_first_decay_rate_op4_valueChanged(int arg1);
	void on_voice_first_decay_level_op1_valueChanged(int arg1);
	void on_voice_first_decay_level_op2_valueChanged(int arg1);
	void on_voice_first_decay_level_op3_valueChanged(int arg1);
	void on_voice_first_decay_level_op4_valueChanged(int arg1);
	void on_voice_second_decay_rate_op1_valueChanged(int arg1);
	void on_voice_second_decay_rate_op2_valueChanged(int arg1);
	void on_voice_second_decay_rate_op3_valueChanged(int arg1);
	void on_voice_second_decay_rate_op4_valueChanged(int arg1);
	void on_voice_total_level_op1_valueChanged(int arg1);
	void on_voice_total_level_op2_valueChanged(int arg1);
	void on_voice_total_level_op3_valueChanged(int arg1);
	void on_voice_total_level_op4_valueChanged(int arg1);
	void on_voice_lfo_enabled_op1_toggled(bool checked);
	void on_voice_lfo_enabled_op2_toggled(bool checked);
	void on_voice_lfo_enabled_op3_toggled(bool checked);
	void on_voice_lfo_enabled_op4_toggled(bool checked);
	void on_voice_release_rate_op1_valueChanged(int arg1);
	void on_voice_release_rate_op2_valueChanged(int arg1);
	void on_voice_release_rate_op3_valueChanged(int arg1);
	void on_voice_release_rate_op4_valueChanged(int arg1);
	void on_write_song_clicked();
	void on_voice_coarse_frequency_mult_op1_valueChanged(int arg1);
	void on_voice_coarse_frequency_mult_op2_valueChanged(int arg1);
	void on_voice_coarse_frequency_mult_op3_valueChanged(int arg1);
	void on_voice_coarse_frequency_mult_op4_valueChanged(int arg1);
	void on_import_button_clicked();
	void on_voice_create_clicked();

	void on_voice_delete_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
