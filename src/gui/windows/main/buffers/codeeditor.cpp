#include "codeeditor.hpp"

#include <QPainter>
#include <QTextBlock>

using namespace Ez2note::Gui::Windows::Main::Buffers;

CodeEditor::CodeEditor(QWidget* parent)
    : QPlainTextEdit(parent), lineNumberArea(new LineNumberArea(this)) {
    connect(this, &QPlainTextEdit::blockCountChanged, this,
            &CodeEditor::UpdateGutterWidth);
    connect(this, &QPlainTextEdit::updateRequest, this,
            &CodeEditor::UpdateGutter);
    lineNumberArea->setVisible(false);
    UpdateGutterWidth();
}

void CodeEditor::SetShowLineNumbers(bool show) {
    showLineNumbers = show;
    lineNumberArea->setVisible(show);
    UpdateGutterWidth();
}

void CodeEditor::SetWordWrap(bool wrap) {
    setLineWrapMode(wrap ? QPlainTextEdit::WidgetWidth
                         : QPlainTextEdit::NoWrap);
}

int CodeEditor::LineNumberAreaWidth() const {
    if (!showLineNumbers) return 0;
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    return 8 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
}

void CodeEditor::UpdateGutterWidth() {
    setViewportMargins(LineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::UpdateGutter(const QRect& rect, int dy) {
    if (dy != 0) {
        lineNumberArea->scroll(0, dy);
    } else {
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(),
                               rect.height());
    }
    if (rect.contains(viewport()->rect())) UpdateGutterWidth();
}

void CodeEditor::resizeEvent(QResizeEvent* event) {
    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(
        QRect(cr.left(), cr.top(), LineNumberAreaWidth(), cr.height()));
}

void CodeEditor::PaintLineNumbers(QPaintEvent* event) {
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), palette().alternateBase());
    painter.setPen(palette().color(QPalette::PlaceholderText));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top =
        qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            painter.drawText(0, top, lineNumberArea->width() - 4,
                             fontMetrics().height(), Qt::AlignRight,
                             QString::number(blockNumber + 1));
        }
        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}
