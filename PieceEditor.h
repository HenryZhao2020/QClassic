#pragma once

#include <QDialog>
#include <QFrame>
#include <QList>
#include <QUrl>

class IPieceView;
class Piece;

class QComboBox;
class QLineEdit;
class QPushButton;

class PieceEditFrame : public QFrame {
    Q_OBJECT

    QLineEdit *nameField;
    QComboBox *composerBox;

public:
    PieceEditFrame(IPieceView *pieceView, Piece *piece);

    QString getName() const;
    QString getComposer() const;
};

class IPieceDialog : public QDialog {
    Q_OBJECT

protected:
    IPieceView *pieceView;
    Piece *piece;
    PieceEditFrame *editFrame;
    QPushButton *doneButton;

    IPieceDialog(IPieceView *pieceView, Piece *piece);

    void updatePieceInfo();
    virtual void done() = 0;
};

class PieceImportDialog : public IPieceDialog {
    Q_OBJECT

    void done() override;

public:
    PieceImportDialog(IPieceView *pieceView, const QUrl &url);
    ~PieceImportDialog() override;
};

class PieceEditDialog : public IPieceDialog {
    Q_OBJECT

    void done() override;

public:
    PieceEditDialog(IPieceView *pieceView, Piece *piece);
};
