#include "pattern_edit_box.h"
#include <QDebug>

QString PatternEditBox::allowed_chars = "0123456789ABCDEF ";
uint8_t PatternEditBox::char_to_byte[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

PatternEditBox::PatternEditBox(QWidget* parent)
	: QTextEdit(parent)
{
	QObject::connect(this, &PatternEditBox::textChanged, this, &PatternEditBox::handleTextChanged);

}

void PatternEditBox::handleTextChanged()
{
	QString text = toPlainText();

	// filter to only hexes
	QString modded_text = "";
	for (auto& c : text)
	{
		QChar c2 = c.toUpper();
		if (PatternEditBox::allowed_chars.indexOf(c2.toLatin1()) >= 0) {
			modded_text += c2;
		}
	}

	if (text.compare(modded_text) != 0) {
		setText(modded_text);
	}
}

std::vector<uint8_t> PatternEditBox::getBytes() {
	QString text = toPlainText().toUpper().replace(" ", "");
	std::vector<uint8_t> out;

	for (auto& c : text) {
		int ind = allowed_chars.indexOf(c);
		if (ind < 0 || ind > 15) {
			qDebug() << "error: cannot find byte mapping for hex: " << c;
			continue;
		}

		out.push_back(PatternEditBox::char_to_byte[ind]);
	}

	return out;
}

void PatternEditBox::addPattern(std::vector<std::vector<uint8_t> >& patterns) {
	std::vector<uint8_t> data = getBytes();
	if (data.size() == 0)
		return;
	patterns.push_back(data);
}
