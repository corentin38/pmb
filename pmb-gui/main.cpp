#include "interface/mainwindow.hpp"
#include <QApplication>

#ifndef Q_MOC_RUN
#include "utils/simple_logger.hpp"
#endif

int main(int argc, char *argv[])
{
    int log_level = 2;
    std::string log_folder_path = "";

    if (argc > 1) {
        if (std::string(argv[1]) == "--log=warn") {
            log_level = 3;
        }
        else {
            if (std::string(argv[1]) == "--log=error") {
                log_level = 4;
            }
            else {
                if (std::string(argv[1]) == "--logfile") {
                    log_folder_path = std::string(getenv("HOME")) + "/.pmb/";
                }
            }
        }
    }

    basics::Simple_logger logger(log_level, log_folder_path);
    QApplication a(argc, argv);
    MainWindow w(logger);
    w.show();

    return a.exec();
}
