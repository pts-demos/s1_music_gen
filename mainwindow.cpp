#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSettings>
#include <QDateTime>
#include <QDebug>
#include <QByteArray>

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

	// Figure out if the program runs in little endian environment
	int num = 1;
	if (*(char*)&num == 1) {
		endianess = LittleEndian;
	} else {
		endianess = BigEndian;
	}

	voices.push_back(Smps_voice());
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::toHostEndian(int16_t* data) {
	if (endianess == LittleEndian) {
		int16_t x = (int16_t)((*data >> 8) | ( *data << 8));
		*data = x;
	}
}

void MainWindow::toHostEndian(uint16_t* data) {
	// Cast to int32 to avoid left shifting unsigned ints
	int32_t temp = *data;
	if (endianess == LittleEndian) {
		int32_t temp2 = (temp >> 8) | ( temp << 8);
		*data = (uint16_t)temp2;
	}
}

void MainWindow::toBigEndian(int16_t* data) {
	if (endianess == LittleEndian) {
		int16_t x = (int16_t)((*data >> 8) | ( *data << 8));
		*data = x;
	}
}

void MainWindow::toBigEndian(uint16_t* data) {
	// cast to int32 to avoid left shifting unsigned ints
	int32_t temp = *data;
	if (endianess == LittleEndian) {
		int32_t temp2 = (temp >> 8) | (temp << 8);
		*data = (uint16_t)temp2;
	}
}

QString MainWindow::byteToHex(uint8_t t) {
	QByteArray arr;
	arr.append((char)t);
	return arr.toHex();
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
	if (cur_voice >= voices.size()) {
		cur_voice = 0;
	}

	update_ui_controls();
}

void MainWindow::on_voice_previous_clicked()
{
	cur_voice--;
	if (cur_voice < 0) {
		cur_voice = (int)voices.size()-1;
	}

	update_ui_controls();
}

void MainWindow::on_voice_create_clicked()
{
	voices.push_back(Smps_voice());
	cur_voice = (int)voices.size()-1;
	update_ui_controls();
}

void MainWindow::on_voice_delete_clicked()
{
	if (voices.size() == 1) {
		qDebug() << "cannot erase last FM voice";
		return;
	}

	voices.erase(voices.begin() + cur_voice);
	if (cur_voice >= (int)voices.size()) {
		cur_voice = (int)voices.size()-1;
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

	std::vector<std::vector<uint8_t> > fm_patterns;
	std::vector<std::vector<uint8_t> > psg_patterns;

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

	qDebug() << "Writing " << fm_patterns.size() << " FM patterns and " << psg_patterns.size() << " psg patterns";

	// Write main SMPS header
	const int smps_header_size = 6;
	const int fm_channel_header_size = 4;
	const int psg_header_size = 6;

	char* smps_header = new char[smps_header_size];
	memset(smps_header, 0, smps_header_size);

	// Solve how much space pattern data requires
	uint16_t patterns_length = 0;

	for (int i = 0; i < fm_patterns.size(); i++) {
		qDebug() << "fm pattern " << i << " size: " << fm_patterns[i].size();
		patterns_length += (uint16_t)fm_patterns[i].size();
	}

	for (int i = 0; i < psg_patterns.size(); i++) {
		qDebug() << "psg pattern " << i << " size: " << psg_patterns[i].size();
		patterns_length += (uint16_t)psg_patterns[i].size();
	}

	// $0-$1: Voice table pointer, offset to where the FM synthesis data is located
	// It starts immediately after last pattern data
	uint16_t headers_size = smps_header_size +
		(uint16_t)fm_patterns.size()*fm_channel_header_size +
		(uint16_t)psg_patterns.size()*psg_header_size;

	uint16_t vac_t_offset = headers_size + patterns_length;
	toBigEndian(&vac_t_offset);
	uint16_t* smps_ptr_1 = (uint16_t*)smps_header;
	smps_ptr_1[0] = vac_t_offset;

	// Number of FM+DAC channels. There must always be a DAC channel defined
	// Megadrive supports 6 FM+1DAC channels. If 6 FM channels are used,
	// write 7 in this field
	// TODO: eh... verify what this means
	smps_header[2] = (uint8_t)(fm_patterns.size());

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
	smps_header[4] = (uint8_t)ui->song_dividing_timing->value();

	/*
	 * Main tempo modifier. From sonicretro.org:
	 * Main tempo modifier. This works as follows: Sonic 1 specific: if main tempo is nn, the song runs for nn-1 frames and is delayed
	 * by 1 frame. A main tempo of $01 runs for 0 frames and is delayed by 1 frame, hence is broken; a main tempo of $00 will overflow
	 * and run for $FF frames and be delayed by 1 frame. Sonic 2 specific: a main tempo of nn runs on nn out of 256 frames, as evenly
	 * spaced as possible. A main tempo of $00 does not run at all. Sonic 3 or K specific: a main tempo of nn runs on (256 - nn) out
	 * of 256 frames, as evenly spaced as possible. All tempo values are valid.
	 */
	smps_header[5] = (uint8_t)ui->song_tempo->value();

	fout.write(smps_header, smps_header_size);
	delete[] smps_header;

	// Write headers for all FM and DAC channels

	char* fm_headers = new char[fm_channel_header_size * fm_patterns.size()];
	memset(fm_headers, 0, fm_channel_header_size * fm_patterns.size());

	uint16_t pattern_offset = 0;

	for (unsigned int i = 0; i < fm_patterns.size(); i++) {
		qDebug() << "Writing FM channel " << i;
		uint8_t* off_p = (uint8_t*)&fm_headers[i * fm_channel_header_size];

		// Track data pointer
		uint16_t* write_track_data_addr = (uint16_t*)off_p;

		// Pattern data begins when all headers and previous patterns are done
		uint16_t track_data_ptr = headers_size + pattern_offset;
		toBigEndian(&track_data_ptr);
		write_track_data_addr[0] = track_data_ptr;
		pattern_offset += (uint16_t)fm_patterns[i].size();

		uint8_t key_disp = 0;
		uint8_t vol_att = 0;

		switch (i) {
		case 0:
			key_disp = ui->fm_chan1_key_displacement->value();
			vol_att = ui->fm_chan1_volume_attenuation->value();
			break;
		case 1:
			key_disp = ui->fm_chan2_key_displacement->value();
			vol_att = ui->fm_chan2_volume_attenuation->value();
			break;
		case 2:
			key_disp = ui->fm_chan3_key_displacement->value();
			vol_att = ui->fm_chan3_volume_attenuation->value();
			break;
		case 3:
			key_disp = ui->fm_chan4_key_displacement->value();
			vol_att = ui->fm_chan4_volume_attenuation->value();
			break;
		case 4:
			key_disp = ui->fm_chan5_key_displacement->value();
			vol_att = ui->fm_chan5_volume_attenuation->value();
			break;
		case 5:
			key_disp = ui->fm_chan6_key_displacement->value();
			vol_att = ui->fm_chan6_volume_attenuation->value();
			break;
		}

		/*
		 * Initial channel key displacement. From sonicretro.org
		 * Initial channel key displacement (signed, ignored on DAC). This is added to the note before it is converted
		 * to a frequency. Sonic 3 or K specific: In the alternate SMPS parsing mode, the channel key displacement is
		 * added to the *frequency* instead.
		 */
		off_p[2] = key_disp;

		// Initial track volume. 0 is max, 7F is total silence.
		off_p[3] = vol_att;
	}

	fout.write(fm_headers, fm_channel_header_size * fm_patterns.size());
	delete[] fm_headers;

	// Write PSG channel headers
	char* psg_headers = new char[6 * psg_patterns.size()];
	memset(psg_headers, 0, psg_header_size * psg_patterns.size());

	for (unsigned int i = 0; i < psg_patterns.size(); i++) {
		qDebug() << "writing PSG channel " << i;
		uint8_t* psg_ptr = (uint8_t*)&psg_headers[i * psg_header_size];
		uint16_t* track_d_ptr = (uint16_t*)psg_ptr;

		uint16_t track_d_ptr_val = headers_size + pattern_offset;
		toBigEndian(&track_d_ptr_val);
		track_d_ptr[0] = track_d_ptr_val;
		pattern_offset += (uint16_t)psg_patterns[i].size();

		uint8_t key_disp = 0;
		uint8_t vol_att = 0;
		uint8_t tone = 0;

		switch (i) {
		case 0:
			tone = ui->psg_chan1_tone->value();
			key_disp = ui->psg_chan1_key_displacement->value();
			vol_att = ui->psg_chan1_volume_attenuation->value();
			break;
		case 1:
			tone = ui->psg_chan2_tone->value();
			key_disp = ui->psg_chan2_key_displacement->value();
			vol_att = ui->psg_chan2_volume_attenuation->value();
			break;
		case 2:
			tone = ui->psg_chan3_tone->value();
			key_disp = ui->psg_chan3_key_displacement->value();
			vol_att = ui->psg_chan3_volume_attenuation->value();
			break;
		}

		// Initial channel key displacement. This is added to the note before it is
		// converted to a frequency
		psg_ptr[2] = key_disp;

		// Initial track volume attenuation: $0 is max volume, $f is total silence
		psg_ptr[3] = vol_att;

		// Sonic 2 specific
		psg_ptr[4] = 0;

		// Default PSG tone (index in lookup table)
		psg_ptr[5] = key_disp;
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
	unsigned int voice_table_size = (unsigned int)voices.size() * voice_size;
	char* fm_table_data = new char[voice_table_size];
	memset(fm_table_data, 0, voice_table_size);
	qDebug() << "writing " << voice_table_size << " bytes of voices";

	// Write all FM voices into a buffer
	// https://segaretro.org/SMPS/Voices_and_samples
	for (unsigned int i = 0; i < voices.size(); i++) {
		Smps_voice& v = voices[i];

		uint8_t* ptr = (uint8_t*)&fm_table_data[i * voice_size];

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

	fout.close();
}

void MainWindow::on_import_button_clicked()
{
	QSettings settings;
	QString def_path = settings.value("prev_import_path", QCoreApplication::applicationDirPath()).toString();

	QString fpath = QFileDialog::getOpenFileName(this, "Open file", def_path, "Any files (*)");
	if (fpath.length() == 0)
		return;

	QFileInfo finfo(fpath);
	if (finfo.exists() == false) {
		qDebug() << "File does not exist: fpath";
		return;
	}

	qint64 fsize = finfo.size();

	settings.setValue("prev_import_path", fpath);

	ui->fm_channel_1->clear();
	ui->fm_channel_2->clear();
	ui->fm_channel_3->clear();
	ui->fm_channel_4->clear();
	ui->fm_channel_5->clear();
	ui->fm_channel_6->clear();
	ui->psg_channel_1->clear();
	ui->psg_channel_2->clear();
	ui->psg_channel_3->clear();

	QFile f;
	f.setFileName(fpath);
	f.open(QIODevice::ReadOnly);

	// TODO: bounds checking
	QByteArray arr = f.readAll();
	f.close();

	char* rawbuf = arr.data();

	uint16_t fm_voice_array_ptr = 0;
	memcpy((char*)&fm_voice_array_ptr, rawbuf, sizeof(uint16_t));
	toHostEndian(&fm_voice_array_ptr);

	qDebug() << "voice array ptr: " << fm_voice_array_ptr;

	uint8_t num_of_fm_channels = 0;
	uint8_t num_of_psg_channels = 0;

	memcpy(&num_of_fm_channels, &rawbuf[2], sizeof(uint8_t));
	memcpy(&num_of_psg_channels, &rawbuf[3], sizeof(uint8_t));

	// There are number+1 FM channels because there must always be a DAC channel
	// TODO: What does the wiki mean by this? Is the DAC channel not in the file,
	// but it must be included in the total number?

	qDebug() << "fm channels: " << num_of_fm_channels << ", psg channels: " << num_of_psg_channels;

	uint8_t dividing_timing = 0;
	uint8_t main_tempo = 0;

	memcpy(&dividing_timing, &rawbuf[4], sizeof(uint8_t));
	memcpy(&main_tempo, &rawbuf[5], sizeof(uint8_t));

	qDebug() << "dividing timing: " << dividing_timing << ", main tempo: " << main_tempo;
	ui->song_dividing_timing->setValue(dividing_timing);
	ui->song_tempo->setValue(main_tempo);

	std::vector<PatternHeader> pattern_headers;
	int offset = 6;

	for (int i = 0; i < num_of_fm_channels; i++) {
		qDebug() << "reading FM channel " << i << " header";
		PatternHeader pattern_header;
		memset(&pattern_header, 0, sizeof(pattern_header));

		uint16_t pattern_data_ptr = 0;
		memcpy((char*)&pattern_data_ptr, &rawbuf[offset], sizeof(uint16_t));
		toHostEndian(&pattern_data_ptr);
		pattern_header.pattern_offset = pattern_data_ptr;
		pattern_header.pattern_number = (int8_t)i;
		qDebug() << "FM channel " << i << " offset: " << pattern_header.pattern_offset;

		bool is_dac = false;

		if (i == 0) {
			// First FM channel can be a DAC channel if the next two bytes are zero
			int16_t maybe_dac = 0;
			memcpy((char*)&maybe_dac, &rawbuf[offset + 3], sizeof(int16_t));
			toHostEndian(&maybe_dac);
			if (maybe_dac == 0) {
				qDebug() << "FM channel 0 is used as DAC";
				is_dac = true;
			}
		}

		if (is_dac == false) {
			memcpy((char*)&pattern_header.initial_channel_key_displacement, &rawbuf[offset + 3], sizeof(int8_t));
			memcpy((char*)&pattern_header.initial_channel_volume, &rawbuf[offset + 4], sizeof(int8_t));
			pattern_header.voice_type = SMPS_FM;
		} else {
			pattern_header.voice_type = SMPS_DAC;
		}

		QSpinBox* target_key = NULL;
		QSpinBox* target_att = NULL;

		switch (i) {
		case 0:
			target_key = ui->fm_chan1_key_displacement;
			target_att = ui->fm_chan1_volume_attenuation;
			break;
		case 1:
			target_key = ui->fm_chan2_key_displacement;
			target_att = ui->fm_chan2_volume_attenuation;
			break;
		case 2:
			target_key = ui->fm_chan3_key_displacement;
			target_att = ui->fm_chan3_volume_attenuation;
			break;
		case 3:
			target_key = ui->fm_chan4_key_displacement;
			target_att = ui->fm_chan4_volume_attenuation;
			break;
		case 4:
			target_key = ui->fm_chan5_key_displacement;
			target_att = ui->fm_chan5_volume_attenuation;
			break;
		case 5:
			target_key = ui->fm_chan6_key_displacement;
			target_att = ui->fm_chan6_volume_attenuation;
			break;
		}

		target_key->setValue(pattern_header.initial_channel_key_displacement);
		target_att->setValue(pattern_header.initial_channel_volume);

		pattern_headers.push_back(pattern_header);
		offset += 4;
	}

	for (int i = 0; i < num_of_psg_channels; i++) {
		qDebug() << "reading PSG channel " << i << " header";
		PatternHeader pattern_header;
		memset(&pattern_header, 0, sizeof(pattern_header));

		uint16_t pattern_data_ptr = 0;
		memcpy((char*)&pattern_data_ptr, &rawbuf[offset], sizeof(uint16_t));
		toHostEndian(&pattern_data_ptr);

		pattern_header.pattern_offset = pattern_data_ptr;
		pattern_header.voice_type = SMPS_PSG;
		pattern_header.pattern_number = i;

		qDebug() << "PSG channel " << i << " offset: " << pattern_header.pattern_offset;

		memcpy((char*)&pattern_header.initial_channel_key_displacement, &rawbuf[offset + 2], sizeof(uint8_t));
		memcpy((char*)&pattern_header.initial_channel_volume, &rawbuf[offset + 3], sizeof(uint8_t));
		memcpy((char*)&pattern_header.unknown, &rawbuf[offset + 4], sizeof(int8_t));
		memcpy((char*)&pattern_header.initial_voice_num, &rawbuf[offset + 5], sizeof(int8_t));

		QSpinBox* target_tone = NULL;
		QSpinBox* target_key = NULL;
		QSpinBox* target_att = NULL;

		switch (i) {
		case 0:
			target_tone = ui->psg_chan1_tone;
			target_key = ui->psg_chan1_key_displacement;
			target_att = ui->psg_chan1_volume_attenuation;
			break;
		case 1:
			target_tone = ui->psg_chan2_tone;
			target_key = ui->psg_chan1_key_displacement;
			target_att = ui->psg_chan2_volume_attenuation;
			break;
		case 2:
			target_tone = ui->psg_chan3_tone;
			target_key = ui->psg_chan3_key_displacement;
			target_att = ui->psg_chan3_volume_attenuation;
			break;
		}

		target_tone->setValue(pattern_header.initial_voice_num);
		target_key->setValue(pattern_header.initial_channel_key_displacement);
		target_att->setValue(pattern_header.initial_channel_volume);

		pattern_headers.push_back(pattern_header);
		offset += 6;
	}

	// Solve the size of each pattern by figuring out when next pattern begins
	std::sort(pattern_headers.begin(), pattern_headers.end(),
		[&](const PatternHeader& a, const PatternHeader& b) {
			return a.pattern_offset < b.pattern_offset;
		}
	);

	for (int i = 0; i < (int)pattern_headers.size()-1; i++) {
		pattern_headers[i].pattern_size = pattern_headers[i+1].pattern_offset - pattern_headers[i].pattern_offset;
	}

	// Sort the patterns back to original order
	// Not necessary, but makes debugging easier
	std::sort(pattern_headers.begin(), pattern_headers.end(),
		[&](const PatternHeader& a, const PatternHeader& b) {

			// Sort FM patterns before PSG channels
			int temp_a = a.pattern_number;
			int temp_b = b.pattern_number;
			if (a.voice_type == SMPS_PSG) temp_a += 10;
			if (b.voice_type == SMPS_PSG) temp_b += 10;

			return temp_a < temp_b;
		}
	);

	qDebug() << "There are a total of " << pattern_headers.size() << " pattern headers";

	for (int i = 0; i < (int)pattern_headers.size(); i++) {
		QString chantype = pattern_headers[i].voice_type == SMPS_PSG ? "PSG" : "FM or DAC";
		qDebug() << "pattern header " << i << " type: " << chantype << ", offset: " << pattern_headers[i].pattern_offset << " length: " << pattern_headers[i].pattern_size;
	}

	// last pattern size can be solved by seeing when fm_voice_array_ptr begins
	pattern_headers[pattern_headers.size()-1].pattern_size = fm_voice_array_ptr - pattern_headers[pattern_headers.size()-1].pattern_offset;

	// read pattern data

	for (int i = 0; i < (int)pattern_headers.size(); i++) {
		PatternHeader& p = pattern_headers[i];

		QString pattern_text = "";

		for (int c = 0; c < p.pattern_size; c++) {
			uint8_t hex = rawbuf[p.pattern_offset + c];
			pattern_text += byteToHex(hex);
			pattern_text += " ";
		}

		PatternEditBox* target = NULL;
		if (p.voice_type == SMPS_FM || p.voice_type == SMPS_DAC) {
			switch (p.pattern_number) {
			case 0: target = ui->fm_channel_1; break;
			case 1: target = ui->fm_channel_2; break;
			case 2: target = ui->fm_channel_3; break;
			case 3: target = ui->fm_channel_4; break;
			case 4: target = ui->fm_channel_5; break;
			case 5: target = ui->fm_channel_6; break;
			}
		} else {
			switch (p.pattern_number) {
			case 0: target = ui->psg_channel_1; break;
			case 1: target = ui->psg_channel_2; break;
			case 2: target = ui->psg_channel_3; break;
			}
		}

		if (target == NULL) {
			qDebug() << "Did not find pattern to edit: " << p.voice_type << ", " << p.pattern_number;
			continue;
		}

		target->setText(pattern_text);
		offset += pattern_headers[i].pattern_size;
	}

	// read FM voice table data
	const int voice_size = 25;

	size_t table_size = fsize - fm_voice_array_ptr;
	qDebug() << "table size: " << table_size;
	qDebug() << "divided into 25 bytes:" << table_size / 25.0f;
	uint16_t voices_to_read = (uint16_t)table_size / 25;
	int out_of_bounds = fsize - (int)(fm_voice_array_ptr + table_size);
	if (out_of_bounds != 0) {
		qDebug() << "error: After reading FM voice table, file read pointer is "
			<< out_of_bounds << " bytes from the file end. Something is not read correctly";
	}

	voices.clear();
	cur_voice = 0;

	for (int i = 0; i < voices_to_read; i++) {
		voices.push_back(Smps_voice());

		uint8_t b1 = (uint8_t)rawbuf[fm_voice_array_ptr + (i*voice_size)];

		// 00111000
		uint8_t feedback = 0x38 & b1;

		// 00000111
		uint8_t algorithm = 0x07 & b1;

		uint8_t b2 = (uint8_t)rawbuf[fm_voice_array_ptr + 1];
		uint8_t b3 = (uint8_t)rawbuf[fm_voice_array_ptr + 2];
		uint8_t b4 = (uint8_t)rawbuf[fm_voice_array_ptr + 3];
		uint8_t b5 = (uint8_t)rawbuf[fm_voice_array_ptr + 4];

		// 01110000
		uint8_t op1_detune = 0x70 & b2;
		uint8_t op3_detune = 0x70 & b3;
		uint8_t op2_detune = 0x70 & b4;
		uint8_t op4_detune = 0x70 & b5;

		// 00001111
		uint8_t op1_mult = 0x0F & b2;
		uint8_t op3_mult = 0x0F & b3;
		uint8_t op2_mult = 0x0F & b4;
		uint8_t op4_mult = 0x0F & b5;

		uint8_t b6 = (uint8_t)rawbuf[fm_voice_array_ptr + 5];
		uint8_t b7 = (uint8_t)rawbuf[fm_voice_array_ptr + 6];
		uint8_t b8 = (uint8_t)rawbuf[fm_voice_array_ptr + 7];
		uint8_t b9 = (uint8_t)rawbuf[fm_voice_array_ptr + 8];

		// 11000000
		uint8_t rate_scale_op1 = 0xC0 & b6;
		uint8_t rate_scale_op2 = 0xC0 & b7;
		uint8_t rate_scale_op3 = 0xC0 & b8;
		uint8_t rate_scale_op4 = 0xC0 & b9;

		// 00011111
		uint8_t attack_rate_op1 = 0x1F & b6;
		uint8_t attack_rate_op2 = 0x1F & b7;
		uint8_t attack_rate_op3 = 0x1F & b8;
		uint8_t attack_rate_op4 = 0x1F & b9;

		uint8_t b10 = (uint8_t)rawbuf[fm_voice_array_ptr + 9];
		uint8_t b11 = (uint8_t)rawbuf[fm_voice_array_ptr + 10];
		uint8_t b12 = (uint8_t)rawbuf[fm_voice_array_ptr + 11];
		uint8_t b13 = (uint8_t)rawbuf[fm_voice_array_ptr + 12];

		// 10000000
		uint8_t lfo_enabled_op_1 = 0x80 & b10;
		uint8_t lfo_enabled_op_2 = 0x80 & b11;
		uint8_t lfo_enabled_op_3 = 0x80 & b12;
		uint8_t lfo_enabled_op_4 = 0x80 & b13;

		// 00011111
		uint8_t first_decay_rate_op_1 = 0x1F & b10;
		uint8_t first_decay_rate_op_2 = 0x1F & b11;
		uint8_t first_decay_rate_op_3 = 0x1F & b12;
		uint8_t first_decay_rate_op_4 = 0x1F & b13;

		uint8_t b14 = (uint8_t)rawbuf[fm_voice_array_ptr + 13];
		uint8_t b15 = (uint8_t)rawbuf[fm_voice_array_ptr + 14];
		uint8_t b16 = (uint8_t)rawbuf[fm_voice_array_ptr + 15];
		uint8_t b17 = (uint8_t)rawbuf[fm_voice_array_ptr + 16];

		// 00011111
		uint8_t second_decay_rate_op1 = b14 & 0x1F;
		uint8_t second_decay_rate_op2 = b15 & 0x1F;
		uint8_t second_decay_rate_op3 = b16 & 0x1F;
		uint8_t second_decay_rate_op4 = b17 & 0x1F;

		uint8_t b18 = (uint8_t)rawbuf[fm_voice_array_ptr + 17];
		uint8_t b19 = (uint8_t)rawbuf[fm_voice_array_ptr + 18];
		uint8_t b20 = (uint8_t)rawbuf[fm_voice_array_ptr + 19];
		uint8_t b21 = (uint8_t)rawbuf[fm_voice_array_ptr + 20];

		// 1111000
		uint8_t first_decay_level_op1 = 0x1F & b18;
		uint8_t first_decay_level_op2 = 0x1F & b19;
		uint8_t first_decay_level_op3 = 0x1F & b20;
		uint8_t first_decay_level_op4 = 0x1F & b21;

		// 00001111
		uint8_t release_rate_op1 = 0x0F & b18;
		uint8_t release_rate_op2 = 0x0F & b19;
		uint8_t release_rate_op3 = 0x0F & b20;
		uint8_t release_rate_op4 = 0x0F & b21;

		uint8_t b22 = (uint8_t)rawbuf[fm_voice_array_ptr + 21];
		uint8_t b23 = (uint8_t)rawbuf[fm_voice_array_ptr + 22];
		uint8_t b24 = (uint8_t)rawbuf[fm_voice_array_ptr + 23];
		uint8_t b25 = (uint8_t)rawbuf[fm_voice_array_ptr + 24];

		// 01111111
		uint8_t total_level_op1 = 0x7F & b22;
		uint8_t total_level_op2 = 0x7F & b23;
		uint8_t total_level_op3 = 0x7F & b24;
		uint8_t total_level_op4 = 0x7F & b25;

		Smps_voice& target = voices[i];

		target.feedback = feedback;
		target.algorithm = algorithm;
		target.detune_op1 = op1_detune;
		target.detune_op2 = op2_detune;
		target.detune_op3 = op3_detune;
		target.detune_op4 = op4_detune;
		target.coarse_frequency_multiplier_op1 = op1_mult;
		target.coarse_frequency_multiplier_op2 = op2_mult;
		target.coarse_frequency_multiplier_op3 = op3_mult;
		target.coarse_frequency_multiplier_op4 = op4_mult;
		target.rate_scale_op1 = rate_scale_op1;
		target.rate_scale_op2 = rate_scale_op2;
		target.rate_scale_op3 = rate_scale_op3;
		target.rate_scale_op4 = rate_scale_op4;
		target.attack_rate_op1 = attack_rate_op1;
		target.attack_rate_op2 = attack_rate_op2;
		target.attack_rate_op3 = attack_rate_op3;
		target.attack_rate_op4 = attack_rate_op4;
		target.lfo_enabled_op1 = lfo_enabled_op_1;
		target.lfo_enabled_op2 = lfo_enabled_op_2;
		target.lfo_enabled_op3 = lfo_enabled_op_3;
		target.lfo_enabled_op4 = lfo_enabled_op_4;
		target.first_decay_rate_op1 = first_decay_rate_op_1;
		target.first_decay_rate_op2 = first_decay_rate_op_2;
		target.first_decay_rate_op3 = first_decay_rate_op_3;
		target.first_decay_rate_op4 = first_decay_rate_op_4;
		target.second_decay_rate_op1 = second_decay_rate_op1;
		target.second_decay_rate_op2 = second_decay_rate_op2;
		target.second_decay_rate_op3 = second_decay_rate_op3;
		target.second_decay_rate_op4 = second_decay_rate_op4;
		target.first_decay_level_op1 = first_decay_level_op1;
		target.first_decay_level_op2 = first_decay_level_op2;
		target.first_decay_level_op3 = first_decay_level_op3;
		target.first_decay_level_op4 = first_decay_level_op4;
		target.release_rate_op1 = release_rate_op1;
		target.release_rate_op2 = release_rate_op2;
		target.release_rate_op3 = release_rate_op3;
		target.release_rate_op4 = release_rate_op4;
		target.total_level_op1 = total_level_op1;
		target.total_level_op2 = total_level_op2;
		target.total_level_op3 = total_level_op3;
		target.total_level_op4 = total_level_op4;
	}

	update_ui_controls();
}
