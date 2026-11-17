#ifndef GUI_WINDOWS_FINDREPLACE_FINDREPLACEDIALOG_HPP
#define GUI_WINDOWS_FINDREPLACE_FINDREPLACEDIALOG_HPP

#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QTextDocument>

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace FindReplace {

/** Non-modal dialog for finding and replacing text in an editor. */
class FindReplaceDialog : public QDialog {
    Q_OBJECT

   public:
    FindReplaceDialog(QWidget* parent, QPlainTextEdit* textEdit);

   private slots:
    void OnFindNext();
    void OnFindPrev();
    void OnReplace();
    void OnReplaceAll();

   private:
    /** Searches with wrap-around. Returns false if nothing was found. */
    bool Find(QTextDocument::FindFlags flags);

    QPlainTextEdit* textEdit;
    QLineEdit* findText;
    QLineEdit* replaceText;
};

}  // namespace FindReplace
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_FINDREPLACE_FINDREPLACEDIALOG_HPP
