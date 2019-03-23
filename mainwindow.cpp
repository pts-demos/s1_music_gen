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
	ui->voice_enable->setChecked(voices[cur_voice].enabled);
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

void MainWindow::on_voice_enable_toggled(bool checked)
{
	voices[cur_voice].enabled = checked;
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
	QSettings settings;
	QString def_path = settings.value("prev_save_path", QCoreApplication::applicationDirPath()).toString();

	QString fpath = QFileDialog::getSaveFileName(this, "Save file", def_path, ".bin");
	if (fpath.length() == 0)
		return;

	settings.setValue("prev_save_path", fpath);

	QFile fout;
	if (fout.open(QIODevice::WriteOnly) == false) {
		qDebug() << "Failed saving to file: " << fpath;
		return;
	}

	unsigned int voices_enabled = 0;
	for (int i = 0; i < FM_VOICES; i++) {
		voices_enabled += voices[i].enabled ? 1 : 0;
	}

	const int voice_size = 25;
	unsigned int voice_table_size = voices_enabled * voice_size;
	char* fm_table_data = new char[voice_table_size];
	memset(fm_table_data, 0, voice_table_size);

	for (int i = 0; i < FM_VOICES; i++) {
		char* ptr = &fm_table_data[i * voice_size];
		Smps_voice& v = voices[i];

		// $0: --XXXYYY where
		//	XXX is feedback
		//	YYY is algorithm
		ptr[0] = (v.feedback << 3) + v.algorithm;

		// $1-$4: XXXXYYYY where
		//	XXXX is Detune of operator n
		//	YYYY is coarse-frequency multiplier of operator n
		ptr[1] = (v.detune_op1 << 4) + v.coarse_frequency_multiplier_op1;
		ptr[2] = (v.detune_op2 << 4) + v.coarse_frequency_multiplier_op2;
		ptr[3] = (v.detune_op3 << 4) + v.coarse_frequency_multiplier_op3;
		ptr[4] = (v.detune_op4 << 4) + v.coarse_frequency_multiplier_op4;

		// $5-$8: -XXYYYYY where
		//	XX is rate scaling of operator n
		//	YYYYY is attack rate of operator n
		ptr[5] = (v.rate_scale_op1 << 5) + v.attack_rate_op1;
		ptr[6] = (v.rate_scale_op2 << 5) + v.attack_rate_op2;
		ptr[7] = (v.rate_scale_op3 << 5) + v.attack_rate_op3;
		ptr[8] = (v.rate_scale_op4 << 5) + v.attack_rate_op4;

		// $9-$C: --XYYYYY where
		//	X: LFO enabled
		//	YYYYY: First decay rate of operator n
		ptr[9] = (v.lfo_enabled_op1 << 5) + v.first_decay_rate_op1;
		ptr[10] = (v.lfo_enabled_op2 << 5) + v.first_decay_rate_op2;
		ptr[11] = (v.lfo_enabled_op3 << 5) + v.first_decay_rate_op3;
		ptr[12] = (v.lfo_enabled_op4 << 5) + v.first_decay_rate_op4;

		// $D-10: Second delay rate/sustain rate of operator n
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

		// $15-$18: Total level of operator n
		ptr[21] = v.total_level_op1;
		ptr[22] = v.total_level_op2;
		ptr[23] = v.total_level_op3;
		ptr[24] = v.total_level_op4;
	}

	fout.write(fm_table_data, voice_table_size);
	delete[] fm_table_data;

	fout.close();
}

