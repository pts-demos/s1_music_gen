#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSettings>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	cur_voice = 0;

	QCoreApplication::setOrganizationName("pts-demos");
	QCoreApplication::setOrganizationDomain("pts.com");
	QCoreApplication::setApplicationName("sonic_smps_gen");
	QSettings settings;
	settings.setValue("last_run", QDateTime::currentSecsSinceEpoch());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::update_ui_controls() {
	ui->voice_label->setText(QString("FM Voice #") + QString::number(cur_voice+1));
	ui->voice_feedback->setValue(voices[cur_voice].feedback);
	ui->voice_algorithm->setValue(voices[cur_voice].algorithm);
	ui->voice_detune_op1->setValue(voices[cur_voice].detune_op1);
	ui->voice_detune_op2->setValue(voices[cur_voice].detune_op2);
	ui->voice_detune_op3->setValue(voices[cur_voice].detune_op3);
	ui->voice_detune_op4->setValue(voices[cur_voice].detune_op4);
	ui->voice_ratescale_op1->setValue(voices[cur_voice].rate_scale_op1);
	ui->voice_ratescale_op2->setValue(voices[cur_voice].rate_scale_op2);
	ui->voice_ratescale_op3->setValue(voices[cur_voice].rate_scale_op3);
	ui->voice_ratescale_op4->setValue(voices[cur_voice].rate_scale_op4);
	ui->voice_attack_rate_op_1->setValue(voices[cur_voice].attack_rate_op1);
	ui->voice_attack_rate_op_2->setValue(voices[cur_voice].attack_rate_op2);
	ui->voice_attack_rate_op_3->setValue(voices[cur_voice].attack_rate_op3);
	ui->voice_attack_rate_op_4->setValue(voices[cur_voice].attack_rate_op4);
	ui->voice_first_decay_rate_op1->setValue(voices[cur_voice].first_decay_rate_op1);
	ui->voice_first_decay_rate_op2->setValue(voices[cur_voice].first_decay_rate_op2);
	ui->voice_first_decay_rate_op3->setValue(voices[cur_voice].first_decay_rate_op3);
	ui->voice_first_decay_rate_op4->setValue(voices[cur_voice].first_decay_rate_op4);
	ui->voice_first_decay_level_op1->setValue(voices[cur_voice].first_decay_level_op1);
	ui->voice_first_decay_level_op2->setValue(voices[cur_voice].first_decay_level_op2);
	ui->voice_first_decay_level_op3->setValue(voices[cur_voice].first_decay_level_op3);
	ui->voice_first_decay_level_op4->setValue(voices[cur_voice].first_decay_level_op4);
	ui->voice_second_decay_rate_op1->setValue(voices[cur_voice].second_decay_rate_op1);
	ui->voice_second_decay_rate_op2->setValue(voices[cur_voice].second_decay_rate_op2);
	ui->voice_second_decay_rate_op3->setValue(voices[cur_voice].second_decay_rate_op3);
	ui->voice_second_decay_rate_op4->setValue(voices[cur_voice].second_decay_rate_op4);
	ui->voice_release_rate_op1->setValue(voices[cur_voice].release_rate_op1);
	ui->voice_release_rate_op2->setValue(voices[cur_voice].release_rate_op2);
	ui->voice_release_rate_op3->setValue(voices[cur_voice].release_rate_op3);
	ui->voice_release_rate_op4->setValue(voices[cur_voice].release_rate_op4);
	ui->voice_total_level_op1->setValue(voices[cur_voice].total_level_op1);
	ui->voice_total_level_op2->setValue(voices[cur_voice].total_level_op2);
	ui->voice_total_level_op3->setValue(voices[cur_voice].total_level_op3);
	ui->voice_total_level_op4->setValue(voices[cur_voice].total_level_op4);
	ui->voice_lfo_enabled_op1->setChecked(voices[cur_voice].lfo_enabled_op1);
	ui->voice_lfo_enabled_op2->setChecked(voices[cur_voice].lfo_enabled_op2);
	ui->voice_lfo_enabled_op3->setChecked(voices[cur_voice].lfo_enabled_op3);
	ui->voice_lfo_enabled_op4->setChecked(voices[cur_voice].lfo_enabled_op4);
}

void MainWindow::on_voice_next_clicked()
{
	cur_voice++;
	if (cur_voice >= FM_VOICES) {
		cur_voice = 0;
	}

	update_ui_controls();
}

void MainWindow::on_voice_previous_clicked()
{
	cur_voice--;
	if (cur_voice < 0) {
		cur_voice = FM_VOICES-1;
	}

	update_ui_controls();
}

void MainWindow::on_voice_feedback_valueChanged(int arg1)
{
	voices[cur_voice].feedback = (int32_t)arg1;
}

void MainWindow::on_voice_algorithm_valueChanged(int arg1)
{
	voices[cur_voice].algorithm = (int32_t)arg1;
}

void MainWindow::on_voice_detune_op1_valueChanged(int arg1)
{
	voices[cur_voice].detune_op1 = (int32_t)arg1;
}

void MainWindow::on_voice_detune_op3_valueChanged(int arg1)
{
	voices[cur_voice].detune_op3 = (int32_t)arg1;
}

void MainWindow::on_voice_detune_op2_valueChanged(int arg1)
{
	voices[cur_voice].detune_op2 = (int32_t)arg1;
}

void MainWindow::on_voice_detune_op4_valueChanged(int arg1)
{
	voices[cur_voice].detune_op4 = (int32_t)arg1;
}

void MainWindow::on_voice_ratescale_op1_valueChanged(int arg1)
{
	voices[cur_voice].rate_scale_op1 = (int32_t)arg1;
}

void MainWindow::on_voice_ratescale_op3_valueChanged(int arg1)
{
	voices[cur_voice].rate_scale_op3 = (int32_t)arg1;
}

void MainWindow::on_voice_ratescale_op2_valueChanged(int arg1)
{
	voices[cur_voice].rate_scale_op2 = (int32_t)arg1;
}

void MainWindow::on_voice_ratescale_op4_valueChanged(int arg1)
{
	voices[cur_voice].rate_scale_op4 = (int32_t)arg1;
}

void MainWindow::on_voice_attack_rate_op_1_valueChanged(int arg1)
{
	voices[cur_voice].attack_rate_op1 = (int32_t)arg1;
}

void MainWindow::on_voice_attack_rate_op_3_valueChanged(int arg1)
{
	voices[cur_voice].attack_rate_op3 = (int32_t)arg1;
}

void MainWindow::on_voice_attack_rate_op_2_valueChanged(int arg1)
{
	voices[cur_voice].attack_rate_op2 = (int32_t)arg1;
}

void MainWindow::on_voice_attack_rate_op_4_valueChanged(int arg1)
{
	voices[cur_voice].attack_rate_op4 = (int32_t)arg1;
}

void MainWindow::on_voice_first_decay_rate_op1_valueChanged(int arg1)
{
	voices[cur_voice].first_decay_rate_op1 = (int32_t)arg1;
}

void MainWindow::on_voice_first_decay_rate_op2_valueChanged(int arg1)
{
	voices[cur_voice].first_decay_rate_op2 = (int32_t)arg1;
}

void MainWindow::on_voice_first_decay_rate_op3_valueChanged(int arg1)
{
	voices[cur_voice].first_decay_rate_op3 = (int32_t)arg1;
}

void MainWindow::on_voice_first_decay_rate_op4_valueChanged(int arg1)
{
	voices[cur_voice].first_decay_rate_op4 = (int32_t)arg1;
}

void MainWindow::on_voice_first_decay_level_op1_valueChanged(int arg1)
{
	voices[cur_voice].first_decay_level_op1 = (int32_t)arg1;
}

void MainWindow::on_voice_first_decay_level_op2_valueChanged(int arg1)
{
	voices[cur_voice].first_decay_level_op2 = (int32_t)arg1;
}

void MainWindow::on_voice_first_decay_level_op3_valueChanged(int arg1)
{
	voices[cur_voice].first_decay_level_op3 = (int32_t)arg1;
}

void MainWindow::on_voice_first_decay_level_op4_valueChanged(int arg1)
{
	voices[cur_voice].first_decay_level_op4 = (int32_t)arg1;
}

void MainWindow::on_voice_second_decay_rate_op1_valueChanged(int arg1)
{
	voices[cur_voice].second_decay_rate_op1 = (int32_t)arg1;
}

void MainWindow::on_voice_second_decay_rate_op2_valueChanged(int arg1)
{
	voices[cur_voice].second_decay_rate_op2 = (int32_t)arg1;
}

void MainWindow::on_voice_second_decay_rate_op3_valueChanged(int arg1)
{
	voices[cur_voice].second_decay_rate_op3 = (int32_t)arg1;
}

void MainWindow::on_voice_second_decay_rate_op4_valueChanged(int arg1)
{
	voices[cur_voice].second_decay_rate_op4 = (int32_t)arg1;
}

void MainWindow::on_voice_total_level_op1_valueChanged(int arg1)
{
	voices[cur_voice].total_level_op1 = (int32_t)arg1;
}

void MainWindow::on_voice_total_level_op2_valueChanged(int arg1)
{
	voices[cur_voice].total_level_op2 = (int32_t)arg1;
}

void MainWindow::on_voice_total_level_op3_valueChanged(int arg1)
{
	voices[cur_voice].total_level_op3 = (int32_t)arg1;
}

void MainWindow::on_voice_total_level_op4_valueChanged(int arg1)
{
	voices[cur_voice].total_level_op4 = (int32_t)arg1;
}

void MainWindow::on_voice_lfo_enabled_op1_toggled(bool checked)
{
	voices[cur_voice].lfo_enabled_op1 = checked;
}

void MainWindow::on_voice_lfo_enabled_op2_toggled(bool checked)
{
	voices[cur_voice].lfo_enabled_op2 = checked;
}

void MainWindow::on_voice_lfo_enabled_op3_toggled(bool checked)
{
	voices[cur_voice].lfo_enabled_op3 = checked;
}

void MainWindow::on_voice_lfo_enabled_op4_toggled(bool checked)
{
	voices[cur_voice].lfo_enabled_op4 = checked;
}

void MainWindow::on_voice_release_rate_op1_valueChanged(int arg1)
{
	voices[cur_voice].release_rate_op1 = (int32_t)arg1;
}

void MainWindow::on_voice_release_rate_op2_valueChanged(int arg1)
{
	voices[cur_voice].release_rate_op2 = (int32_t)arg1;
}

void MainWindow::on_voice_release_rate_op3_valueChanged(int arg1)
{
	voices[cur_voice].release_rate_op3 = (int32_t)arg1;
}

void MainWindow::on_voice_release_rate_op4_valueChanged(int arg1)
{
	voices[cur_voice].release_rate_op4 = (int32_t)arg1;
}

void MainWindow::on_voice_coarse_frequency_mult_op1_valueChanged(int arg1)
{
	voices[cur_voice].coarse_frequency_multiplier_op1 = (int32_t)arg1;
}

void MainWindow::on_voice_coarse_frequency_mult_op2_valueChanged(int arg1)
{
	voices[cur_voice].coarse_frequency_multiplier_op2 = (int32_t)arg1;
}

void MainWindow::on_voice_coarse_frequency_mult_op3_valueChanged(int arg1)
{
	voices[cur_voice].coarse_frequency_multiplier_op3 = (int32_t)arg1;
}

void MainWindow::on_voice_coarse_frequency_mult_op4_valueChanged(int arg1)
{
	voices[cur_voice].coarse_frequency_multiplier_op4 = (int32_t)arg1;
}

void MainWindow::on_write_song_clicked()
{
	// https://segaretro.org/SMPS/Headers

	QSettings settings;
	QString def_path = settings.value("prev_save_path", QCoreApplication::applicationDirPath()).toString();

	QString fpath = QFileDialog::getSaveFileName(this, "Save file", def_path, ".bin");
	if (fpath.length() == 0)
		return;

	settings.setValue("prev_save_path", fpath);

	QFile fout;
	fout.setFileName(fpath);
	if (fout.open(QIODevice::WriteOnly) == false) {
		qDebug() << "Failed saving to file: " << fpath;
		return;
	}

	// Convert text hex into bytes
	ui->fm_channel_1->addPattern(fm_patterns);
	ui->fm_channel_2->addPattern(fm_patterns);
	ui->fm_channel_3->addPattern(fm_patterns);
	ui->fm_channel_4->addPattern(fm_patterns);
	ui->fm_channel_5->addPattern(fm_patterns);
	ui->fm_channel_6->addPattern(fm_patterns);
	ui->psg_channel_1->addPattern(psg_patterns);
	ui->psg_channel_2->addPattern(psg_patterns);
	ui->psg_channel_3->addPattern(psg_patterns);
	ui->psg_channel_4->addPattern(psg_patterns);

	if (fm_patterns.size() == 0 || psg_patterns.size() == 0) {
		qDebug() << "Need at least one FM and PSG pattern";
		return;
	}

	qDebug() << "Writing " << fm_patterns.size() << " FM patterns and " << psg_patterns.size() << " psg patterns";

	// Write main SMPS header
	const int smps_header_size = 6;
	const int fm_channel_header_size = 4;
	const int psg_header_size = 6;

	char* smps_header = new char[smps_header_size];
	memset(smps_header, 0, smps_header_size);

	unsigned int patterns_length = 0;
	for (const auto& p : fm_patterns) {
		patterns_length += p.size();
	}

	// $0-$1: Voice table pointer, offset to where the FM synthesis data is located
	// TODO: DAC channels

	unsigned int headers_size = smps_header_size +
			fm_patterns.size()*fm_channel_header_size +
			psg_patterns.size()*psg_header_size;

	unsigned int vac_t_offset = headers_size + patterns_length;
	int16_t* smps_ptr_1 = (int16_t*)smps_header;
	smps_ptr_1[0] = (int16_t)vac_t_offset;

	// Number of FM+DAC channels. There must always be a DAC channel defined
	// Megadrive supports 6 FM+1DAC channels. If 6 FM channels are used,
	// write 7 in this field
	smps_header[2] = (uint8_t)(fm_patterns.size()+1);

	// Number of PSG tracks
	smps_header[3] = (uint8_t)psg_patterns.size();

	/*
	 * From sonicretro.org:
	 * Dividing timing: in all drivers I analyzed (Sonic 1, Sonic 2, Sonic 3, Sonic & Knuckles, Sonic 3D Blast, Ristar, Outrunners)
	 * this works by multiplying note duration by this value. This can lead to broken notes, as the final duration is stored in a
	 * single byte; thus, the maximum note duration you can use without problems is $FF/dividing timing (round down, maximum of $7F).
	 * Sonic 3 or K specific: a dividing timing of $00 multiplies the note duration by 256, making all notes have a duration of $00
	 * and last for 256 frames.
	 */
	smps_header[4] = 1;

	/*
	 * Main tempo modifier. From sonicretro.org:
	 * Main tempo modifier. This works as follows: Sonic 1 specific: if main tempo is nn, the song runs for nn-1 frames and is delayed
	 * by 1 frame. A main tempo of $01 runs for 0 frames and is delayed by 1 frame, hence is broken; a main tempo of $00 will overflow
	 * and run for $FF frames and be delayed by 1 frame. Sonic 2 specific: a main tempo of nn runs on nn out of 256 frames, as evenly
	 * spaced as possible. A main tempo of $00 does not run at all. Sonic 3 or K specific: a main tempo of nn runs on (256 - nn) out
	 * of 256 frames, as evenly spaced as possible. All tempo values are valid.
	 */
	smps_header[5] = 6;

	fout.write(smps_header, smps_header_size);
	delete[] smps_header;

	// Write headers for all FM and DAC channels

	char* fm_headers = new char[fm_channel_header_size * fm_patterns.size()];
	memset(fm_headers, 0, fm_channel_header_size * fm_patterns.size());

	int pattern_offset = 0;

	for (unsigned int i = 0; i < fm_patterns.size(); i++) {
		char* off_p = &fm_headers[i * fm_channel_header_size];

		// Track data pointer
		int16_t* write_track_data_addr = (int16_t*)&fm_headers[i * fm_channel_header_size];

		// Pattern data begins when all headers and previous patterns are done
		int track_data_ptr = headers_size + pattern_offset;
		write_track_data_addr[0] = (int16_t)track_data_ptr;
		pattern_offset += fm_patterns[i].size();

		/*
		 * Initial channel key displacement. From sonicretro.org
		 * Initial channel key displacement (signed, ignored on DAC). This is added to the note before it is converted
		 * to a frequency. Sonic 3 or K specific: In the alternate SMPS parsing mode, the channel key displacement is
		 * added to the *frequency* instead.
		 */
		off_p[1] = 0;

		// Initial track volume. 0 is max, 7F is total silence.
		off_p[2] = 0;
	}

	fout.write(fm_headers, fm_channel_header_size * fm_patterns.size());
	delete[] fm_headers;

	// Write PSG channel headers
	char* psg_headers = new char[6 * psg_patterns.size()];
	memset(psg_headers, 0, psg_header_size * psg_patterns.size());

	for (unsigned int i = 0; i < psg_patterns.size(); i++) {
		char* psg_ptr = &psg_headers[i * psg_header_size];
		int16_t* track_d_ptr = (int16_t*)&psg_headers[i * psg_header_size];

		track_d_ptr[0] = headers_size + pattern_offset;
		pattern_offset += psg_patterns[i].size();

		// Initial channel key displacement. This is added to the note before it is
		// converted to a frequency
		psg_ptr[2] = 0;

		// Initial track volume attenuation: $0 is max volume, $f is total silence
		psg_ptr[3] = 0;

		// Sonic 2 specific
		psg_ptr[4] = 0;

		// Default PSG tone (index in lookup table)
		psg_ptr[5] = 0;
	}

	fout.write(psg_headers, psg_header_size * psg_patterns.size());
	delete[] psg_headers;

	// Write pattern data

	for (const auto& pattern : fm_patterns) {
		for (unsigned int i = 0; i < pattern.size(); i++) {
			uint8_t data = pattern[i];
			fout.write((char*)&data, sizeof(uint8_t));
		}
	}

	for (const auto& pattern : psg_patterns) {
		for (unsigned int i = 0; i < pattern.size(); i++) {
			uint8_t data = pattern[i];
			fout.write((char*)&data, sizeof(uint8_t));
		}
	}

	// Write voice table
	const int voice_size = 25;
	unsigned int voice_table_size = FM_VOICES * voice_size;
	char* fm_table_data = new char[voice_table_size];
	memset(fm_table_data, 0, voice_table_size);

	// Write all FM voices into a buffer
	// https://segaretro.org/SMPS/Voices_and_samples
	for (unsigned int i = 0; i < FM_VOICES; i++) {
		Smps_voice& v = voices[i];

		char* ptr = &fm_table_data[i * voice_size];

		// $0: --XXXYYY where
		//	XXX is feedback
		//	YYY is algorithm
		ptr[0] = (v.feedback << 3) + v.algorithm;

		// $1-$4: -XXXYYYY where
		//	XXX is Detune of operator n
		//	YYYY is coarse-frequency multiplier of operator n
		ptr[1] = (v.detune_op1 << 3) + v.coarse_frequency_multiplier_op1;
		ptr[2] = (v.detune_op2 << 3) + v.coarse_frequency_multiplier_op2;
		ptr[3] = (v.detune_op3 << 3) + v.coarse_frequency_multiplier_op3;
		ptr[4] = (v.detune_op4 << 3) + v.coarse_frequency_multiplier_op4;

		// $5-$8: XX-YYYYY where
		//	XX is rate scaling of operator n
		//	YYYYY is attack rate of operator n
		ptr[5] = (v.rate_scale_op1 << 6) + v.attack_rate_op1;
		ptr[6] = (v.rate_scale_op2 << 6) + v.attack_rate_op2;
		ptr[7] = (v.rate_scale_op3 << 6) + v.attack_rate_op3;
		ptr[8] = (v.rate_scale_op4 << 6) + v.attack_rate_op4;

		// $9-$C: X--YYYYY where
		//	X: LFO enabled
		//	YYYYY: First decay rate of operator n
		ptr[9] = (v.lfo_enabled_op1 << 7) + v.first_decay_rate_op1;
		ptr[10] = (v.lfo_enabled_op2 << 7) + v.first_decay_rate_op2;
		ptr[11] = (v.lfo_enabled_op3 << 7) + v.first_decay_rate_op3;
		ptr[12] = (v.lfo_enabled_op4 << 7) + v.first_decay_rate_op4;

		// $D-10: ---XXXXX where
		//	XXXXX: Second delay rate/sustain rate of operator n
		ptr[13] = v.second_decay_rate_op1;
		ptr[14] = v.second_decay_rate_op2;
		ptr[15] = v.second_decay_rate_op3;
		ptr[16] = v.second_decay_rate_op4;

		// $11-$14: XXXXYYYY where
		//	XXXX is first decay level/sutain level of operator n
		//	YYYY is release rate of operator n
		ptr[17] = (v.first_decay_rate_op1 << 4) + v.release_rate_op1;
		ptr[18] = (v.first_decay_rate_op2 << 4) + v.release_rate_op2;
		ptr[19] = (v.first_decay_rate_op3 << 4) + v.release_rate_op3;
		ptr[20] = (v.first_decay_rate_op4 << 4) + v.release_rate_op4;

		// $15-$18: -XXXXXXX where
		//	XXXXXXX is total level of operator n
		ptr[21] = v.total_level_op1;
		ptr[22] = v.total_level_op2;
		ptr[23] = v.total_level_op3;
		ptr[24] = v.total_level_op4;
	}

	fout.write(fm_table_data, voice_table_size);
	delete[] fm_table_data;

	// TODO: Write PSG / DAC data

	fout.close();
}
