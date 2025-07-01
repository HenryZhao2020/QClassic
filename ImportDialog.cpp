#include "ImportDialog.h"
#include "LibraryView.h"
#include "Composition.h"
#include "AppData.h"
#include "Library.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QFileInfo>
#include <QShortcut>
#include <QMessageBox>

ImportDialog::ImportDialog(LibraryView *libView, const QUrl &source) :
    QDialog{libView}, libView{libView}, source{source},
    titleField{new QLineEdit{QFileInfo{source.path()}.fileName(), this}},
    composerBox{new QComboBox{this}},
    playlistBox{new QComboBox{this}} {

    setModal(true);
    setMinimumSize(450, 250);

    composerBox->setEditable(true);
    playlistBox->setEditable(true);

    auto gridLayout = new QGridLayout{this};
    gridLayout->setHorizontalSpacing(30);
    gridLayout->addWidget(new QLabel{tr("Title:"), this}, 0, 0);
    gridLayout->addWidget(titleField, 0, 1);
    gridLayout->addWidget(new QLabel{tr("Composer:"), this}, 1, 0);
    gridLayout->addWidget(composerBox, 1, 1);
    gridLayout->addWidget(new QLabel{tr("Add To Playlist:"), this}, 2, 0);
    gridLayout->addWidget(playlistBox, 2, 1);
    gridLayout->setRowStretch(3, 1);

    auto importButton = new QPushButton{tr("Import"), this};
    connect(importButton, &QPushButton::clicked, this, &ImportDialog::import);

    auto cancelButton = new QPushButton{tr("Cancel"), this};
    connect(cancelButton, &QPushButton::clicked, this, &ImportDialog::close);

    auto buttonFrame = new QFrame{this};
    auto buttonLayout = new QHBoxLayout{buttonFrame};
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->addWidget(importButton);
    buttonLayout->addWidget(cancelButton);
    gridLayout->addWidget(buttonFrame, 4, 0, 1, 2);

    // Use <Cmd+W> to close window in macOS
    auto closeShortcut = new QShortcut{QKeySequence::Close, this};
    connect(closeShortcut, &QShortcut::activated, this, &QWidget::close);
}

void ImportDialog::import() {
    QString title{titleField->text().trimmed()};
    QString composer{composerBox->currentText().trimmed()};

    auto lib = AppData::instance().getLibrary();
    auto composition = new Composition{source, title, composer};
    if (!lib->containsComposition(composition)) {
        libView->addComposition(composition, true);
    } else {
        QMessageBox::critical(this, "Duplicate Item",
                              "Composition already exists in the library!");
        delete composition;
    }

    close();
}
