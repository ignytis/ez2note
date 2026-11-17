#include "aboutwindow.hpp"

#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>

#include "../../../constants.hpp"

using namespace Ez2note::Gui::Windows::About;

namespace {

/** Creates a centered label which can contain clickable links. */
QLabel* createLabel(const QString& html, QWidget* parent) {
    QLabel* label = new QLabel(html, parent);
    label->setAlignment(Qt::AlignCenter);
    label->setTextFormat(Qt::RichText);
    label->setOpenExternalLinks(true);
    return label;
}

}  // namespace

AboutWindow::AboutWindow(QWidget* parent) : QDialog(parent) {
    setWindowTitle(QString("About %1").arg(EZ2NOTE_APP_NAME));

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(10);

    layout->addWidget(createLabel(
        QString("%1 %2").arg(EZ2NOTE_APP_NAME, EZ2NOTE_APP_VERSION), this));
    layout->addWidget(createLabel(EZ2NOTE_APP_DESCRIPTION, this));
    layout->addWidget(createLabel(
        QString("<a href=\"%1\">%1</a>").arg(EZ2NOTE_APP_HOMEPAGE), this));
    layout->addWidget(createLabel(
        "<a href=\"https://github.com/ignytis/ez2note/blob/main/LICENSE\">"
        "Licensed under GNU GPL v3</a>",
        this));

    layout->addSpacing(10);
    layout->addWidget(createLabel("Libraries used:", this));
    layout->addWidget(createLabel(
        QString("<a href=\"https://www.qt.io/licensing/\">Qt %1</a>")
            .arg(QT_VERSION_STR),
        this));
    layout->addWidget(
        createLabel("<a href=\"https://github.com/nlohmann/json/blob/develop/"
                    "LICENSE.MIT\">nlohmann/json</a>",
                    this));

    QDialogButtonBox* buttons =
        new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::close);
    layout->addWidget(buttons);
}
