#pragma once

#include <QFrame>
#include <QDialog>
#include <QList>
#include <QUrl>

class Piece;
class IPieceView;
class QLineEdit;
class QComboBox;
class QHBoxLayout;

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
    QHBoxLayout *buttonLayout;

    IPieceDialog(IPieceView *pieceView, Piece *piece);

public:
    virtual ~IPieceDialog() = 0;
};

class PieceImportDialog : public IPieceDialog {
    Q_OBJECT

    void import();

public:
    PieceImportDialog(IPieceView *pieceView, const QUrl &url);
    ~PieceImportDialog() override;
};
