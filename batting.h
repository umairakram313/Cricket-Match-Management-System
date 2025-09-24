#include "impfiles.h"


class batsman
{
public:
    string name;
    int lineupNo;
    int runs;
    int balls;
    int fours;
    int sixes;
    bool inToBat;
    bool out;
    bool runout;

    string outbowler;
    batsman* next;

    batsman();
    ~batsman();
    double strike_rate();
};


class batsmanLineup
{
public:
    batsman* strike;
    batsman* nonstrike;
    batsman* head;

    batsmanLineup();

    ~batsmanLineup();

    void Loadbatsman(string bat);
    void openers();
    void dotball();
    void runs(int r);

    void wicket(string name);

    void runout(bool notaWideBall, int r);

    void changeStrike();

    void batting_scorecard();
    
};

