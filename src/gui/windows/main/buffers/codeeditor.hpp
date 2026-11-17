#ifndef GUI_WINDOWS_MAIN_BUFFERS_CODEEDITOR_HPP
#define GUI_WINDOWS_MAIN_BUFFERS_CODEEDITOR_HPP

#include <QPlainTextEdit>
#include <QSize>
#include <QWidget>

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {
namespace Buffers {

/** Plain text editor with an optional line number gutter. */
class CodeEditor : public QPlainTextEdit {
    Q_OBJECT

   public:
    explicit CodeEditor(QWidget* parent = nullptr);

    /** Shows or hides the line number gutter. */
    void SetShowLineNumbers(bool show);
    /** Enables or disables word wrapping. */
    void SetWordWrap(bool wrap);

    /** Paints the gutter. Called by the gutter widget. */
    void PaintLineNumbers(QPaintEvent* event);
    /** Returns the width needed by the gutter (0 when hidden). */
    int LineNumberAreaWidth() const;

   protected:
    void resizeEvent(QResizeEvent* event) override;

   private slots:
    void UpdateGutterWidth();
    void UpdateGutter(const QRect& rect, int dy);

   private:
    QWidget* lineNumberArea;
    bool showLineNumbers = false;
};

/** Gutter widget which delegates painting to the editor. */
class LineNumberArea : public QWidget {
   public:
    explicit LineNumberArea(CodeEditor* editor)
        : QWidget(editor), editor(editor) {}
    QSize sizeHint() const override {
        return QSize(editor->LineNumberAreaWidth(), 0);
    }

   protected:
    void paintEvent(QPaintEvent* event) override {
        editor->PaintLineNumbers(event);
    }

   private:
    CodeEditor* editor;
};

}  // namespace Buffers
}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_BUFFERS_CODEEDITOR_HPP
