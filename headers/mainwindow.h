#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "sellerpage.h"
#include "forwarderpage.h"
#include "clientbroker.h"
#include "driverpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class hold the logic of the main window before the user has logged in.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow Constructor.
     * @param parent The parent object for QT Framework.
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /**
     * @brief Sets up the user type combo box of the registraion page with all the user types in string form.
     */
    void setupUserTypeComboBox();

private slots:
    /**
     * @brief Sends a login attempt to the server with the users inputted infomation.
     */
    void on_loginBtn_clicked();

    /**
     * @brief Signs into a spesific user page such as shipper, forwarder and driver.
     * @param pageName The name of the page to be signed into.
     */
    void signIntoPage(const QString& pageName);

    /**
     * @brief Opens up and displays the error message dialog box.
     * @param errorMessage The error message to be displayed.
     */
    void onErrorRecived(const QString& errorMessage);

    /**
     * @brief Opens up and displays the message dialog box.
     * @param message The message to be displayed.
     */
    void onMessageRecived(const QString& message);

    /**
     * @brief Opens up the register screen.
     */
    void on_registerBtn_clicked();

    /**
     * @brief Returns back to the login screen from the register screen.
     */
    void on_backRegisterBtn_clicked();

    /**
     * @brief Sends a register attempt to the server with the users inputted infomation.
     */
    void on_confirmRegisterBtn_clicked();

    /**
     * @brief Logs user out of the system and returns back to the login screen.
     */
    void on_actionLog_out_triggered();

private:
    Ui::MainWindow *ui;
    Page* mainPage = nullptr;
    ClientBroker* broker;

    const int loginIndex = 0;
    const int registerIndex = 1;
    const int mainPageIndex = 2;
};
#endif // MAINWINDOW_H
