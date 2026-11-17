#include "findreplacedialog.hpp"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QTextCursor>
#include <QVBoxLayout>

using namespace Ez2note::Gui::Windows::FindReplace;

FindReplaceDialog::FindReplaceDialog(QWidget* parent, QPlainTextEdit* textEdit)
    : QDialog(parent),
      textEdit(textEdit),
      findText(new QLineEdit(this)),
      replaceText(new QLineEdit(this)) {
    setWindowTitle("Find and Replace");

    QVBoxLayout* layout = new QVBoxLayout(this);
    QFormLayout* form = new QFormLayout();
    form->addRow("Find:", findText);
    form->addRow("Replace with:", replaceText);
    layout->addLayout(form);

    QHBoxLayout* buttons = new QHBoxLayout();
    buttons->addStretch();
    QPushButton* prev = new QPushButton("Find previous", this);
    QPushButton* next = new QPushButton("Find next", this);
    QPushButton* replace = new QPushButton("Replace", this);
    QPushButton* replaceAll = new QPushButton("Replace All", this);
    QPushButton* cancel = new QPushButton("Cancel", this);
    for (QPushButton* b : {prev, next, replace, replaceAll, cancel}) {
        buttons->addWidget(b);
    }
    layout->addLayout(buttons);

    connect(prev, &QPushButton::clicked, this, &FindReplaceDialog::OnFindPrev);
    connect(next, &QPushButton::clicked, this, &FindReplaceDialog::OnFindNext);
    connect(replace, &QPushButton::clicked, this,
            &FindReplaceDialog::OnReplace);
    connect(replaceAll, &QPushButton::clicked, this,
            &FindReplaceDialog::OnReplaceAll);
    connect(cancel, &QPushButton::clicked, this, &QDialog::close);
}

bool FindReplaceDialog::Find(QTextDocument::FindFlags flags) {
    QString term = findText->text();
    if (textEdit->find(term, flags)) return true;

    // Wrap around
    QTextCursor original = textEdit->textCursor();
    QTextCursor cursor = original;
    cursor.movePosition(flags & QTextDocument::FindBackward
                            ? QTextCursor::End
                            : QTextCursor::Start);
    textEdit->setTextCursor(cursor);
    if (textEdit->find(term, flags)) return true;

    textEdit->setTextCursor(original);
    return false;
}

void FindReplaceDialog::OnFindNext() {
    if (findText->text().isEmpty()) return;
    if (!Find(QTextDocument::FindFlags())) {
        QMessageBox::information(this, "Find", "Text not found.");
    }
}

void FindReplaceDialog::OnFindPrev() {
    if (findText->text().isEmpty()) return;
    if (!Find(QTextDocument::FindBackward)) {
        QMessageBox::information(this, "Find", "Text not found.");
    }
}

void FindReplaceDialog::OnReplace() {
    if (findText->text().isEmpty()) return;

    QTextCursor cursor = textEdit->textCursor();
    if (cursor.selectedText() == findText->text()) {
        cursor.insertText(replaceText->text());
    }
    OnFindNext();
}

void FindReplaceDialog::OnReplaceAll() {
    QString term = findText->text();
    if (term.isEmpty()) return;

    int count = 0;
    QTextCursor cursor(textEdit->document());
    cursor.beginEditBlock();
    QTextCursor found = textEdit->document()->find(term, 0);
    while (!found.isNull()) {
        found.insertText(replaceText->text());
        ++count;
        found = textEdit->document()->find(term, found);
    }
    cursor.endEditBlock();

    QMessageBox::information(this, "Replace All",
                             QString("Replaced %1 occurrences.").arg(count));
}
