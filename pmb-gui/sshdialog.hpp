#ifndef SSH_DIALOG_H
#define SSH_DIALOG_H

#include <QDialog>

namespace Ui {
class SshDialog;
}

class SshDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SshDialog(QWidget *parent = 0);
    ~SshDialog();

    std::string get_host();
    std::string get_host_path();

private:
    Ui::SshDialog *ui;
};

#endif // SSH_DIALOG_H
