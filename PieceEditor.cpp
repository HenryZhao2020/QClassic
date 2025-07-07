#include "PieceEditor.h"

#include "AppData.h"
#include "IPieceView.h"
#include "Library.h"
#include "LibraryView.h"
#include "Piece.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QShortcut>

PieceEditFrame::PieceEditFrame(IPieceView *pieceView, Piece *piece) :
    QFrame{pieceView},
    nameField{new QLineEdit{piece->getName(), this}},
    composerBox{new QComboBox{this}} {

    constexpr int FIELD_WIDTH{280};
    composerBox->setMinimumWidth(FIELD_WIDTH);
    composerBox->setEditable(true);
    composerBox->addItems(AppData::instance().getLibrary()->getComposers());
    composerBox->setCurrentText(piece->getComposer());

    auto gridLayout = new QGridLayout{this};
    gridLayout->setHorizontalSpacing(30);
    gridLayout->addWidget(new QLabel{tr("Name:"), this}, 0, 0);
    gridLayout->addWidget(nameField, 0, 1);
    gridLayout->addWidget(new QLabel{tr("Composer:"), this}, 1, 0);
    gridLayout->addWidget(composerBox, 1, 1);
}

QString PieceEditFrame::getName() const {
    return nameField->text();
}

QString PieceEditFrame::getComposer() const {
    return composerBox->currentText();
}

IPieceDialog::IPieceDialog(IPieceView *pieceView, Piece *piece) :
    pieceView{pieceView}, piece{piece},
    editFrame{new PieceEditFrame{pieceView, piece}},
    doneButton{new QPushButton{this}} {

    connect(doneButton, &QPushButton::clicked, this,
            &IPieceDialog::done);

    auto cancelButton = new QPushButton{tr("Cancel"), this};
    connect(cancelButton, &QPushButton::clicked, this,
            &IPieceDialog::close);

    auto buttonFrame = new QFrame{this};
    auto buttonLayout = new QHBoxLayout{buttonFrame};
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->addWidget(doneButton);
    buttonLayout->addWidget(cancelButton);

    auto dialogLayout = new QVBoxLayout{this};
    dialogLayout->addWidget(editFrame);
    dialogLayout->addStretch();
    dialogLayout->setSpacing(30);
    dialogLayout->addWidget(buttonFrame);

    // Use <Cmd+W> to close window in macOS
    auto closeShortcut = new QShortcut{QKeySequence::Close, this};
    connect(closeShortcut, &QShortcut::activated, this, &QWidget::close);
}

void IPieceDialog::updatePieceInfo() {
    piece->setName(editFrame->getName());
    piece->setComposer(editFrame->getComposer());
}

PieceImportDialog::PieceImportDialog(IPieceView *pieceView, const QUrl &url) :
    IPieceDialog{pieceView, new Piece{url}} {

    doneButton->setText(tr("Import"));
}

PieceImportDialog::~PieceImportDialog() {
    delete piece;
}

void PieceImportDialog::done() {
    updatePieceInfo();
    pieceView->addPiece(new Piece{*piece}, true);
    close();
}

PieceEditDialog::PieceEditDialog(IPieceView *pieceView, Piece *piece) :
    IPieceDialog{pieceView, piece} {

    doneButton->setText(tr("Save"));
}

void PieceEditDialog::done() {
    updatePieceInfo();
    pieceView->updatePiece(piece);
    close();
}
