#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

// Game window size
#define game_height 450
#define game_width 850

// Difficulty
#define nbBonbons 20
#define time_level_1 (15+nbBonbons)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum couleur_enum {
        Aucune,
        Rouge,
        Bleu,
        Jaune,
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *);
    bool eventFilter(QObject *obj, QEvent *event);
    void checkDistance();
    void valid();
    int randInt (int min, int max);

    ~MainWindow();

private slots:
    void progress_bar_update();
    void time_out();
    void play_again();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int xred[nbBonbons];
    int yred[nbBonbons];
    int xblue[nbBonbons];
    int yblue[nbBonbons];
    int xyellow[nbBonbons];
    int yyellow[nbBonbons];
    int tabCentres[3*nbBonbons][2];
    couleur_enum couleur;
    int nbBonbonsPile;
    int rayonCurseur;
    int nbmanges[3];
    int scorePotentiel;
    int score;
    int scoreMax;
    bool timeout;
};

#endif // MAINWINDOW_H
