#include "impfiles.h"


class batsman
{
public:
    string name = "";
    int lineupNo = 0;
    int runs = 0;
    int balls = 0;
    int fours = 0;
    int sixes = 0;
    bool inToBat = false;
    bool out = false;
    bool runout = false;

    string outbowler = "";
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

