#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "smps_voice.h"

#define FM_VOICES 6

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void update_ui_controls();

private:
	Smps_voice voices[FM_VOICES];
	int cur_voice;
	std::vector<std::vector<uint8_t> > fm_patterns;
	std::vector<std::vector<uint8_t> > psg_patterns;

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
private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
