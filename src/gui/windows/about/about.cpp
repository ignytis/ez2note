#include "about.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QtGlobal>
#include <QUrl>
#include <QDesktopServices>

About::About(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("About ez2note"));

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *appName = new QLabel("<b>ez2note</b>", this);
    appName->setAlignment(Qt::AlignCenter);
    layout->addWidget(appName);

    QLabel *appDescription = new QLabel(tr("A simple and easy-to-use note-taking application."), this);
    appDescription->setAlignment(Qt::AlignCenter);
    layout->addWidget(appDescription);

    QLabel *homepage = new QLabel(this);
    homepage->setText(tr("Project Homepage: <a href=\"https://github.com/ignytis/ez2note\">https://github.com/ignytis/ez2note</a>"));
    homepage->setAlignment(Qt::AlignCenter);
    homepage->setOpenExternalLinks(true);
    layout->addWidget(homepage);

    QLabel *qtVersion = new QLabel(tr("Built with Qt %1").arg(QT_VERSION_STR), this);
    qtVersion->setAlignment(Qt::AlignCenter);
    layout->addWidget(qtVersion);

    QLabel *license = new QLabel(tr("Licensed under GNU GPL v3"), this);
    license->setAlignment(Qt::AlignCenter);
    layout->addWidget(license);

    layout->addStretch();

    QPushButton *closeButton = new QPushButton(tr("Close"), this);
    connect(closeButton, &QPushButton::clicked, this, &About::accept);
    layout->addWidget(closeButton, 0, Qt::AlignCenter);
}
