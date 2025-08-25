#include "pattern_edit_box.h"
#include <QDebug>
#include <sstream>

QString PatternEditBox::allowed_chars = "0123456789ABCDEF ";

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
		// Keep cursor position after modifying text
		int pos = textCursor().position();
		setText(modded_text);
		QTextCursor cursor = textCursor();
		cursor.setPosition(pos);
		setTextCursor(cursor);
	}
}

std::vector<uint8_t> PatternEditBox::getBytes() {
	std::string text = toPlainText().toUpper().replace(" ", "").toStdString();
	std::vector<uint8_t> out;

	for (int i = 1; i < (int)text.size(); i += 2) {
		std::stringstream ss;
		ss << text.at(i-1) << text.at(i);
		std::string one_hex = ss.str();
		ss.str("");
		ss << std::hex << one_hex;
		uint16_t hex = 0;
		ss >> hex;
		out.push_back(hex);
	}

	return out;
}

void PatternEditBox::addPattern(std::vector<std::vector<uint8_t> >& patterns) {
	std::vector<uint8_t> data = getBytes();
	patterns.push_back(data);
}
