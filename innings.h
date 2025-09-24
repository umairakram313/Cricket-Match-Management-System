#include "impfiles.h"
#include "batting.h"
#include "bowling.h"

class ball
{
public:
    int ballno = 0;
    int runs = 0;
    int total = 0;
    int wickets = 0;
    int extras = 0;
    int noballno = 0;
    int wideno = 0;
    string striker = "";
    string nonstriker = "";
    string bowler = "";
    ball* next;

    ball();
    ~ball();
};

class innings
{
public:
    ball* top;
    batsmanLineup* batlineup;
    bowlerlineup* bowlineup;

    innings(batsmanLineup* batLine, bowlerlineup* bow);
    ~innings();
    void deleteball();
    void firstball(int r);
    void firstballout();
    void firstballrunout(int legalrun);
    void firstballnoballrun(int r);
    void firstballnoballrunout(int legalrun);
    void firstballwiderun(int r);
    void firstballwiderunout(int legalrun);
    void scoredball(int x);
    void wicket();
    void runout(int legalrun);
    void noballrun(int r);
    void widerun(int r);
    void noballrunout(int legalrun);
    void widerunout(int legalrun);
    int readballs();
    int readtotal();
    int readwickets();
    int readextras();
    int readovers();
    int readoverball();
    void firstballprocess();
    void anyotherball();
    void showscoreboard();
};

