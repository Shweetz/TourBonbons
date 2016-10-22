/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *progression;
    QLabel *win;
    QPushButton *play_again;
    QLabel *score;
    QProgressBar *progressBar;
    QLabel *fond;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(850, 530);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        progression = new QLabel(centralWidget);
        progression->setObjectName(QStringLiteral("progression"));
        progression->setGeometry(QRect(10, 480, 291, 41));
        win = new QLabel(centralWidget);
        win->setObjectName(QStringLiteral("win"));
        win->setGeometry(QRect(10, 110, 801, 241));
        QFont font;
        font.setPointSize(30);
        win->setFont(font);
        win->setAlignment(Qt::AlignCenter);
        play_again = new QPushButton(centralWidget);
        play_again->setObjectName(QStringLiteral("play_again"));
        play_again->setGeometry(QRect(330, 350, 150, 50));
        QFont font1;
        font1.setPointSize(16);
        play_again->setFont(font1);
        score = new QLabel(centralWidget);
        score->setObjectName(QStringLiteral("score"));
        score->setGeometry(QRect(320, 470, 181, 51));
        score->setAlignment(Qt::AlignCenter);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(580, 490, 118, 23));
        progressBar->setStyleSheet(QLatin1String("QProgressBar {\n"
"border: 1px solid black;\n"
"text-align: center;\n"
"padding: 1px;\n"
"border-radius: 7px;\n"
"background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,\n"
"stop: 0 #fff,\n"
"stop: 0.4999 #eee,\n"
"stop: 0.5 #ddd,\n"
"stop: 1 #eee );\n"
"width: 15px;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,\n"
"stop: 0 #78d,\n"
"stop: 0.4999 #46a,\n"
"stop: 0.5 #45a,\n"
"stop: 1 #238 );\n"
"border-radius: 7px;\n"
"border: 1px solid black;\n"
"}"));
        progressBar->setValue(24);
        fond = new QLabel(centralWidget);
        fond->setObjectName(QStringLiteral("fond"));
        fond->setGeometry(QRect(0, 0, 850, 475));
        fond->setAutoFillBackground(false);
        fond->setStyleSheet(QStringLiteral("border:3px solid red;"));
        MainWindow->setCentralWidget(centralWidget);
        fond->raise();
        progression->raise();
        win->raise();
        play_again->raise();
        score->raise();
        progressBar->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        progression->setText(QApplication::translate("MainWindow", "Niveau - Nombre rouges\n"
"Nombre bleus - Nombre jaunes", 0));
        win->setText(QApplication::translate("MainWindow", "YOU WIN !!!\n"
"Score : 30pts\n"
"Score max\n"
"Time needed", 0));
        play_again->setText(QApplication::translate("MainWindow", "Play Again", 0));
        score->setText(QApplication::translate("MainWindow", "Score :", 0));
        fond->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
