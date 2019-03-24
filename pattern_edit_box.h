#ifndef PATTERN_EDIT_BOX_H
#define PATTERN_EDIT_BOX_H

#include <QTextEdit>

class PatternEditBox : public QTextEdit
{
public:
	PatternEditBox(QWidget* parent = NULL);
	static QString allowed_chars;

	/**
	 * Returns the contents of this pattern as hexes turned into bytes
	 */
	std::vector<uint8_t> getBytes();

	/**
	 * Adds this pattern's data into container containing all patterns
	 * If this pattern is empty, nothing is added
	 */
	void addPattern(std::vector<std::vector<uint8_t> >& patterns);
private slots:
	void handleTextChanged();
};

#endif // PATTERN_EDIT_BOX_H
