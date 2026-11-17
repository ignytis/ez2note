#ifndef GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTBUFFER_HPP
#define GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTBUFFER_HPP

#include <QString>
#include <QWidget>

#include "../../../../config.hpp"
#include "codeeditor.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {
namespace Buffers {

/** Base class for buffers: a widget wrapping a text editor. */
class AbstractBuffer : public QWidget {
    Q_OBJECT

   public:
    AbstractBuffer(QWidget* parent, Ez2note::Config& config);
    virtual ~AbstractBuffer() = default;

    virtual void Undo();
    virtual void Redo();
    virtual void SetShowLineNumbers(bool show);
    virtual void SetWordWrap(bool wrap);
    virtual bool IsModified() const;
    virtual QString GetTitle() const = 0;

    CodeEditor* GetTextEdit() const { return textEdit; }

   protected:
    CodeEditor* textEdit;
    Ez2note::Config& config;
};

}  // namespace Buffers
}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTBUFFER_HPP
