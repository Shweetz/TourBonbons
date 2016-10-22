#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QCursor>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /******************************** Initialize everything (check #define in .h) ********************************/
    ui->setupUi(this);    

    ui->fond->setGeometry(0, 0, game_width, game_height); // Sets playable area

    ui->win->hide();    
    ui->play_again->setGeometry(710, 480, 100, 30);
    ui->play_again->setText("Restart");
    connect(ui->play_again, SIGNAL(clicked()), this, SLOT(play_again()));

    // Timers
    timeout = false;
    ui->progressBar->setRange(0, time_level_1);
    ui->progressBar->setValue(time_level_1);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(progress_bar_update()));
    timer->start(1000);

    // Variables and tables of variables (woohoo)
    for (int i=0; i<nbBonbons; ++i)
    {
        xred[i]=0;
        yred[i]=0;
        xblue[i]=0;
        yblue[i]=0;
        xyellow[i]=0;
        yyellow[i]=0;
    }
    for (int i=0; i<3; ++i)
    {
        nbmanges[i] = 0;
    }
    rayonCurseur = 10;
    couleur = Aucune;
    nbBonbonsPile = 0;
    scorePotentiel = 0;
    score = 0;

    // EventFilter to call the event to refresh screen when needed
    qApp->installEventFilter(this);
    ui->progressBar->installEventFilter(this);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (timeout == false) // You don't want to paint if you ran out of time
    {
        QPainter painter(this);

        // Sets the nice green circle around the cursor
        QPoint p = QCursor::pos();
        p = mapFromGlobal(p);

        painter.setBrush(Qt::green);
        painter.drawEllipse(p, 10, 10);

        // Sets text information for the player
        ui->progression->setText("Niveau 1 : " + QString::number(time_level_1) + "sec max\nRouges : "
                                 + QString::number(nbmanges[0]) + "/" + QString::number(nbBonbons)
                                 + " - Bleus : " + QString::number(nbmanges[1]) + "/" + QString::number(nbBonbons)
                                 + " - Jaunes : " + QString::number(nbmanges[2]) + "/" + QString::number(nbBonbons));

        ui->score->setText("SCORE : " + QString::number(score) + " (+" + QString::number(scorePotentiel) + ")");

        // Draws sweeties in the background
        painter.setBrush(Qt::red);
        for (int i=0; i<nbBonbons; ++i)
        {
            if (xred[i]==0) // Initialize at a random position
            {
                int x = (randInt(21, game_width-21));
                int y = (randInt(21, game_height-21));
                painter.drawEllipse(x, y, 20, 20);
                xred[i]=x;
                yred[i]=y;
                tabCentres[i][0]=x;
                tabCentres[i][1]=y;
            }
            else if (xred[i]>2) // Repaint in at the same place
            {
                painter.drawEllipse(xred[i], yred[i], 20, 20);
            }
        }
        painter.setBrush(Qt::blue);
        for (int i=0; i<nbBonbons; ++i)
        {
            if (xblue[i]==0)
            {
                int x = (randInt(21, game_width-21));
                int y = (randInt(21, game_height-21));
                painter.drawEllipse(x, y, 20, 20);
                xblue[i]=x;
                yblue[i]=y;
                tabCentres[i+nbBonbons][0]=x;
                tabCentres[i+nbBonbons][1]=y;
            }
            else if (xblue[i]>2)
            {
                painter.drawEllipse(xblue[i], yblue[i], 20, 20);
            }
        }
        painter.setBrush(Qt::yellow);
        for (int i=0; i<nbBonbons; ++i)
        {
            if (xyellow[i]==0)
            {
                int x = (randInt(21, game_width-21));
                int y = (randInt(21, game_height-21));
                painter.drawEllipse(x, y, 20, 20);
                xyellow[i]=x;
                yyellow[i]=y;
                tabCentres[i+2*nbBonbons][0]=x;
                tabCentres[i+2*nbBonbons][1]=y;
            }
            else if (xyellow[i]>2)
            {
                painter.drawEllipse(xyellow[i], yyellow[i], 20, 20);
            }
        }

        // Draws sweeties above your cursor (sweeties in the pile), it will also draw them over background because they are painted after
        if (couleur == Rouge)
        {
            painter.setBrush(Qt::red);
        }
        else if (couleur == Bleu)
        {
            painter.setBrush(Qt::blue);
        }
        else if (couleur == Jaune)
        {
            painter.setBrush(Qt::yellow);
        }

        for (int i=0; i<nbBonbonsPile; ++i)
        {
            p.setY(p.y()-5);

            painter.drawEllipse(p, 10, 10);
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove)
    {
        checkDistance();
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        valid();
    }
    update();

    return false;
}

void MainWindow::checkDistance()
{
    // Get cursor position
    QPoint curs = QCursor::pos();
    curs = mapFromGlobal(curs);

    for (int i = 0; i<3*nbBonbons; ++i)
    {
        QPoint *p = new QPoint(tabCentres[i][0]+10, tabCentres[i][1]+10);
        QPoint dist = curs-*p;
        if (dist.manhattanLength() < 10 + rayonCurseur) // Si on est à portée d'un bonbon
        {
            // On marque le bonbon
            if (i<nbBonbons)
            {
                xred[i]=1;
                yred[i]=1;
            }
            else if (i<2*nbBonbons)
            {
                xblue[i-nbBonbons]=1;
                yblue[i-nbBonbons]=1;
            }
            else if (i<3*nbBonbons)
            {
                xyellow[i-2*nbBonbons]=1;
                yyellow[i-2*nbBonbons]=1;
            }

            // Ne pas le repeindre dans la fenêtre
            tabCentres[i][0]=-50;
            tabCentres[i][1]=-50;

            if (nbBonbonsPile == 0) // Si pile vide, elle prend la couleur du bonbon
            {
                if (i<nbBonbons)
                {
                    couleur = Rouge;
                }
                else if (i<2*nbBonbons)
                {
                    couleur = Bleu;
                }
                else if (i<3*nbBonbons)
                {
                    couleur = Jaune;
                }
                nbBonbonsPile++;
                scorePotentiel = 1;
            }
            // Si non vide et le bonbon est de la couleur, on l'ajoute
            else if ((i<nbBonbons && couleur == Rouge) || (i>=nbBonbons && i<2*nbBonbons && couleur == Bleu) || (i>=2*nbBonbons && couleur == Jaune))
            {
                nbBonbonsPile++;

                for (int j=nbBonbonsPile; j>0; --j)
                {
                    scorePotentiel += j;
                }
            }
            else // Sinon, on recrée tous les bonbons de la pile et le bonbon de l'autre couleur
            {
                // La pile
                if (couleur == Rouge)
                {
                    for (int j=0; j<nbBonbons; ++j)
                    {
                        if (xred[j]==1)
                        {
                            xred[j]=0;
                            yred[j]=0;
                        }
                    }
                }
                else if (couleur == Bleu)
                {
                    for (int j=0; j<nbBonbons; ++j)
                    {
                        if (xblue[j]==1)
                        {
                            xblue[j]=0;
                            yblue[j]=0;
                        }
                    }
                }
                else if (couleur == Jaune)
                {
                    for (int j=0; j<nbBonbons; ++j)
                    {
                        if (xyellow[j]==1)
                        {
                            xyellow[j]=0;
                            yyellow[j]=0;
                        }
                    }
                }
                // Le bonbon intrus
                if (i<nbBonbons)
                {
                    xred[i]=0;
                    yred[i]=0;
                }
                else if (i<2*nbBonbons)
                {
                    xblue[i-nbBonbons]=0;
                    yblue[i-nbBonbons]=0;
                }
                else if (i<3*nbBonbons)
                {
                    xyellow[i-2*nbBonbons]=0;
                    yyellow[i-2*nbBonbons]=0;
                }

                nbBonbonsPile = 0;
                scorePotentiel = 0;
            }
        }
    }
}

void MainWindow::valid()
{
    // Mark the sweeties on cursor as eaten when the player clicked
    if (couleur == Rouge)
    {
        nbmanges[0] += nbBonbonsPile;
        for (int i=0; i<nbBonbons; ++i)
        {
            if (xred[i]==1)
            {
                xred[i]=2;
                yred[i]=2;
            }
        }
    }
    else if (couleur == Bleu)
    {
        nbmanges[1] += nbBonbonsPile;
        for (int i=0; i<nbBonbons; ++i)
        {
            if (xblue[i]==1)
            {
                xblue[i]=2;
                yblue[i]=2;
            }
        }
    }
    else if (couleur == Jaune)
    {
        nbmanges[2] += nbBonbonsPile;
        for (int i=0; i<nbBonbons; ++i)
        {
            if (xyellow[i]==1)
            {
                xyellow[i]=2;
                yyellow[i]=2;
            }
        }
    }

    score += scorePotentiel;
    scorePotentiel = 0;

    couleur = Aucune;
    nbBonbonsPile = 0;

    if (nbmanges[0]+nbmanges[1]+nbmanges[2] == 3*nbBonbons) // You ate all sweeties !
    {
        ui->score->hide();

        // Calculate optimal score
        scoreMax = 0;
        for (int i=1; i<nbBonbons+1; ++i)
        {
            for (int j=i; j>0; --j)
            {
                scoreMax += j;
            }
        }

        timer->stop();

        ui->win->setText("YOU WIN !!!\nScore : " + QString::number(score) + "pts\nScore max : " + QString::number(3*scoreMax) + "pts\n" +
                         "Time needed : " + QString::number(time_level_1 - ui->progressBar->value()) + "sec");

        ui->win->show();
        ui->play_again->show();
    }
}

int MainWindow::randInt (int min, int max)
{
    return qrand() % ((max + 1) - min) + min;
}

void MainWindow::progress_bar_update()
{
    ui->progressBar->setValue(ui->progressBar->value()-1); // Decrease the value once per second

    if (ui->progressBar->value() == 0)
    {
        time_out();
    }
}

void MainWindow::time_out()
{
    timeout = true;
    ui->win->setText("Time out, you lost.");
    ui->win->show();

    ui->play_again->setGeometry(330, 350, 150, 50);
    ui->play_again->setText("Play Again");

    timer->stop();
}

void MainWindow::play_again()
{
    timeout = false;
    timer->stop(); // If Restart
    MainWindow *mw = new MainWindow(this);
    mw->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
