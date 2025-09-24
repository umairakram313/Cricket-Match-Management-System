#include "impfiles.h"

class bowler
{
public:
    string name = "";
    int lineUpNo = 0;
    int balls = 0;
    int overs = 0;
    int runs = 0;
    int wickets = 0;
    int dots = 0;
    int fours = 0;
    int sixes = 0;
    int wides = 0;
    int noballs = 0;
    bool bowled = false;
    bowler* next = 0;
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

