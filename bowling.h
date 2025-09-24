#include "impfiles.h"

class bowler
{
public:
    string name;
    int lineUpNo;
    int balls;
    int overs;
    int runs;
    int wickets;
    int dots;
    int fours;
    int sixes;
    int wides;
    int noballs;
    bool bowled;
    bowler* next;
    bowler();
    ~bowler();
    float economy();
};

class bowlerlineup
{
public:
    bowler* bowl;
    bowler* lastbowl;
    bowler* head;
    bowlerlineup();
    ~bowlerlineup();

    void loadbowlers(string bowlers);

    void runs(int ru);
    void wicket();
    void wide(int rw);
    void noball(int rn);

    void dotball();

    void openingbowler();
    void endOfOver();
    void bowling_scorecard();
};

