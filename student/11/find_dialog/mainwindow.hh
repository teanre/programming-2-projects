#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool openFile(const QString &filename, QStringList &content);
    void searchForWord(const QString &word, const QStringList &content);

private slots:
    void on_fileLineEdit_textChanged(const QString &arg1);

    void on_keyLineEdit_textChanged(const QString &arg1);

    void on_findPushButton_clicked();

private:
    Ui::MainWindow *ui;

    QString filename_ = "";
    QString word_ =  "";

};
#endif // MAINWINDOW_HH
