#include "impfiles.h"
#include "bowling.h"
#include "batting.h"


string Team1_name = "";
string Team2_name = "";
string Team1_lineup[5];
string Team2_lineup[5];
string firstbat_lineup[5];
string secondbat_lineup[5];
string TossWinner = "";
string TossLoser = "";
string firstbat = "";
string secondbat = "";
string winstate;


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

    ball()
    {
        next = NULL;
    }
    ~ball()
    {
        delete next;
    }
};
class innings
{
public:
    ball* top;
    batsmanLineup* batlineup;
    bowlerlineup* bowlineup;

    innings(batsmanLineup* batLine, bowlerlineup* bow)
    {
        top = NULL;
        batlineup = batLine;
        bowlineup = bow;
    }

    ~innings()
    {
        delete top;
        delete batlineup;
        delete bowlineup;
    }

    void deleteball()
    {
        ball* ptr = top;
        top = top->next;
        delete ptr;
    }
    void firstball(int r)
    {
        ball* ptr = new ball;
        top = ptr;
        top->ballno = 1;
        top->wickets = 0;
        top->runs = r;
        top->total = r;
        top->next = NULL;
        top->extras = 0;
        top->noballno = 0;
        top->wideno = 0;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        batlineup->runs(r);
        bowlineup->runs(r);
    }
    void firstballout()
    {
        ball* ptr = new ball;
        top = ptr;
        top->ballno = 1;
        top->wickets = 1;
        top->runs = 0;
        top->total = 0;
        top->next = NULL;
        top->extras = 0;
        top->noballno = 0;
        top->wideno = 0;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        batlineup->wicket(top->bowler);
        bowlineup->wicket();

    }
    void firstballrunout(int legalrun)
    {
        ball* ptr = new ball;
        top = ptr;
        top->ballno = 1;
        top->wickets = 1;
        top->runs = legalrun;
        top->total = legalrun;
        top->next = NULL;
        top->extras = 0;
        top->noballno = 0;
        top->wideno = 0;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        int a;
        while (true)
        {
            try {
                cout << "did the ball hit the bat?" << endl << "1. Yes " << endl << "2. No " << endl;
                cin >> a;
                if (a != 1 && a != 2) throw invalid_argument("Invalid input");
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        if (a == 1)
        {

            batlineup->runout(true, legalrun);
        }
        else
        {
            batlineup->runout(true, 0);
        }
        bowlineup->runs(legalrun);

    }

    void firstballnoballrun(int r)
    {
        ball* ptr = new ball;
        top = ptr;
        top->ballno = 0;
        top->wickets = 0;
        top->runs = r;
        top->total = 1 + r;
        top->next = NULL;
        top->extras = 1;
        top->noballno = 1;
        top->wideno = 0;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        batlineup->runs(r);
        bowlineup->noball(r);
    }
    void firstballnoballrunout(int legalrun)
    {
        ball* ptr = new ball;
        top = ptr;
        top->ballno = 0;
        top->wickets = 1;
        top->runs = legalrun;
        top->total = 1 + legalrun;
        top->next = NULL;
        top->extras = 1;
        top->noballno = 1;
        top->wideno = 0;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        int a;
        while (true)
        {
            try {
                cout << "did the ball hit the bat?" << endl << "1. Yes " << endl << "2. No " << endl;
                cin >> a;
                if (a != 1 && a != 2) throw invalid_argument("Invalid input");
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        if (a == 1)
        {
            batlineup->runout(true, legalrun);
        }
        else
        {
            batlineup->runout(true, 0);
        }
        bowlineup->noball(legalrun);
    }
    void firstballwiderun(int r)
    {
        ball* ptr = new ball;
        top = ptr;
        top->ballno = 0;
        top->wickets = 0;
        top->runs = r;
        top->total = 1 + r;
        top->next = NULL;
        top->extras = 1 + r;
        top->noballno = 0;
        top->wideno = 1;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        bowlineup->wide(r);
    }
    void firstballwiderunout(int legalrun)
    {
        ball* ptr = new ball;
        top = ptr;
        top->ballno = 0;
        top->wickets = 1;
        top->runs = 0;
        top->total = 1 + legalrun;
        top->next = NULL;
        top->extras = 1 + legalrun;
        top->noballno = 0;
        top->wideno = 1;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        batlineup->runout(false, 0);
        bowlineup->wide(legalrun);
    }
    void scoredball(int x)
    {
        ball* ptr = new ball;
        int t = top->total;
        int w = top->wickets;
        int b = top->ballno;
        int e = top->extras;
        int n = top->noballno;
        int wd = top->wideno;
        top->next = ptr;
        top = ptr;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        top->wickets = w;
        top->ballno = ++b;
        top->runs = x;
        top->total = t + x;
        top->extras = e;
        top->noballno = n;
        top->wideno = wd;
        top->next = NULL;
        batlineup->runs(x);
        bowlineup->runs(x);

    }
    void wicket()
    {
        ball* ptr = new ball;
        int t = top->total;
        int w = top->wickets;
        int b = top->ballno;
        int e = top->extras;
        int n = top->noballno;
        int wd = top->wideno;
        top->next = ptr;
        top = ptr;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        top->wickets = ++w;
        top->ballno = ++b;
        top->runs = 0;
        top->total = t;
        top->extras = e;
        top->noballno = n;
        top->wideno = wd;
        top->next = NULL;
        batlineup->wicket(top->bowler);
        bowlineup->wicket();
    }
    void runout(int legalrun)
    {
        ball* ptr = new ball;
        int t = top->total;
        int w = top->wickets;
        int b = top->ballno;
        int e = top->extras;
        int n = top->noballno;
        int wd = top->wideno;
        top->next = ptr;
        top = ptr;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        top->wickets = ++w;
        top->ballno = ++b;
        top->runs = legalrun;
        top->total = t + legalrun;
        top->extras = e;
        top->noballno = n;
        top->wideno = wd;
        top->next = NULL;

        int a;
        while (true)
        {
            try {
                cout << "did the ball hit the bat?" << endl << "1. Yes " << endl << "2. No " << endl;
                cin >> a;
                if (a != 1 && a != 2) throw invalid_argument("Invalid input");
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        if (a == 1)
        {
            batlineup->runout(true, legalrun);
        }
        else
        {
            batlineup->runout(true, 0);
        }
        bowlineup->runs(legalrun);
    }
    void noballrun(int r)
    {
        ball* ptr = new ball;
        int t = top->total;
        int w = top->wickets;
        int b = top->ballno;
        int e = top->extras;
        int n = top->noballno;
        int wd = top->wideno;
        top->next = ptr;
        top = ptr;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        top->wickets = w;
        top->ballno = b;
        top->runs = r;
        top->total = ++t + r;
        top->extras = ++e;
        top->noballno = ++n;
        top->wideno = wd;
        top->next = NULL;
        batlineup->runs(r);
        bowlineup->noball(r);
    }

    void widerun(int r)
    {
        ball* ptr = new ball;
        int t = top->total;
        int w = top->wickets;
        int b = top->ballno;
        int e = top->extras;
        int n = top->noballno;
        int wd = top->wideno;
        top->next = ptr;
        top = ptr;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        top->wickets = w;
        top->ballno = b;
        top->runs = 0;
        top->total = ++t + r;
        top->extras = ++e + r;
        top->noballno = n;
        top->wideno = ++wd;
        top->next = NULL;
        bowlineup->wide(r);
    }
    void noballrunout(int legalrun)
    {
        ball* ptr = new ball;
        int t = top->total;
        int w = top->wickets;
        int b = top->ballno;
        int e = top->extras;
        int n = top->noballno;
        int wd = top->wideno;
        top->next = ptr;
        top = ptr;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        top->wickets = ++w;
        top->ballno = b;
        top->runs = legalrun;
        top->total = ++t + legalrun;
        top->extras = ++e;
        top->noballno = ++n;
        top->wideno = wd;
        top->next = NULL;
        bowlineup->noball(legalrun);

        int a;
        while (true)
        {
            try {
                cout << "did the ball hit the bat?" << endl << "1. Yes " << endl << "2. No " << endl;
                cin >> a;
                if (a != 1 && a != 2) throw invalid_argument("Invalid input");
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        if (a == 1)
        {
            batlineup->runout(true, legalrun);
        }
        else
        {
            batlineup->runout(true, 0);
        }

    }
    void widerunout(int legalrun)
    {
        ball* ptr = new ball;
        int t = top->total;
        int w = top->wickets;
        int b = top->ballno;
        int e = top->extras;
        int n = top->noballno;
        int wd = top->wideno;
        top->next = ptr;
        top = ptr;
        top->striker = batlineup->strike->name;
        top->nonstriker = batlineup->nonstrike->name;
        top->bowler = bowlineup->bowl->name;
        top->wickets = ++w;
        top->ballno = b;
        top->runs = 0;
        top->total = ++t + legalrun;
        top->extras = ++e + legalrun;
        top->noballno = n;
        top->wideno = ++wd;
        top->next = NULL;
        batlineup->runout(false, 0);
        bowlineup->wide(legalrun);
    }
    int readballs()
    {
        return top->ballno;
    }
    int readtotal()
    {
        return top->total;
    }
    int readwickets()
    {
        return top->wickets;
    }
    int readextras()
    {
        return top->extras;
    }
    int readovers()
    {
        int c = (top->ballno / 6);
        return c;
    }
    int readoverball()
    {
        int c = top->ballno % 6;
        return c;
    }
    void firstballprocess()
    {
        string a;
        batlineup->openers();
        bowlineup->openingbowler();
        cout << "What happened on the first ball: run(r), wicket(w), wide(wd) or noball(n)?";
        while (true)
        {
            try {


                cin >> a;
                if (!(a == "r" || a == "w" || a == "wd" || a == "n")) throw invalid_argument("Invalid input");
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        if (a == "r")
        {
            int b;
            cout << "what were the amount of runs scored on this ball?";
            while (true)
            {
                try {

                    cin >> b;
                    if (b > 8 || b < 0) throw invalid_argument("Invalid input");
                    break;
                }
                catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            firstball(b);
        }
        else if (a == "w")
        {
            string b;
            cout << "Was there a runout? enter r for yes, any other alphabet or word for no:";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> b;
            if (b == "r")
            {
                int run;
                cout << "Legal runs made?";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (true)
                {
                    try {

                        cin >> run;

                        if (run > 5 || run < 0) { throw invalid_argument("Invalid input"); }


                        break;
                    }
                    catch (const invalid_argument& e) {

                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }

                firstballrunout(run);
            }
            else {
                firstballout();
            }
        }
        else if (a == "wd")
        {
            string c;
            cout << "Was there a runout on wide? enter y for yes, any other alphabet or word for no:";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> c;
            if (c == "y")
            {
                int run;
                cout << "What were the legal runs (runs excluding the no ball) made?";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (true)
                {
                    try {

                        cin >> run;

                        if (run > 5 || run < 0) { throw invalid_argument("Invalid input"); }


                        break;
                    }
                    catch (const invalid_argument& e) {

                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }

                firstballwiderunout(run);
            }
            else
            {
                int run;
                while (true)
                {
                    try {

                        cin >> run;

                        if (run > 5 || run < 0) { throw invalid_argument("Invalid input"); }


                        break;
                    }
                    catch (const invalid_argument& e) {

                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }

                firstballwiderun(run);
            }
        }
        else if (a == "n")
        {
            string c;
            cout << "Was there a runout on noball?? enter y for yes, any other alphabet or word for no:";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> c;
            if (c == "y")
            {
                int run;
                cout << "What were the legal runs (runs excluding the no ball) made?";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (true)
                {
                    try {

                        cin >> run;

                        if (run > 5 || run < 0) { throw invalid_argument("Invalid input"); }


                        break;
                    }
                    catch (const invalid_argument& e) {

                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                firstballnoballrunout(run);
            }
            else
            {
                int run;
                cout << "What were the legal runs (runs excluding the no ball) made?";
                while (true)
                {
                    try {

                        cin >> run;

                        if (run > 5 || run < 0) { throw invalid_argument("Invalid input"); }


                        break;
                    }
                    catch (const invalid_argument& e) {

                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                firstballnoballrun(run);
            }
        }
        cout << endl << endl;
    }

    void anyotherball()
    {
        string a;
        cout << endl << endl << "What happened on this ball: run(r), wicket(w), wide(wd) or noball(n)?";
        while (true)
        {
            try {

                cin >> a;
                if (a != "r" && a != "w" && a != "wd" && a != "n") throw invalid_argument("Invalid input");
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        if (a == "r")
        {
            int b;
            cout << "What were the amount of runs scored?";
            while (true)
            {
                try {

                    cin >> b;

                    if (b > 8 || b < 0) { throw invalid_argument("Invalid input"); }


                    break;
                }
                catch (const invalid_argument& e) {

                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            scoredball(b);
        }
        else if (a == "w")
        {
            string b;
            cout << "Was there a runout? enter r for yes, any other alphabet or word for no:";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> b;
            if (b == "r")
            {
                int run;
                cout << "What were the legal runs (runs excluding the no ball) made?";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (true)
                {
                    try {

                        cin >> run;

                        if (run > 5 || run < 0) { throw invalid_argument("Invalid input"); }


                        break;
                    }
                    catch (const invalid_argument& e) {

                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }

                runout(run);
            }
            else {
                wicket();
            }
        }
        else if (a == "wd")
        {
            string c;
            cout << "runout on wide?? enter y for yes, any other alphaber or word for no:";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> c;
            if (c == "y")
            {
                int run;
                cout << "legal runs made?";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (true)
                {
                    try {

                        cin >> run;

                        if (run > 5 || run < 0) { throw invalid_argument("Invalid input"); }


                        break;
                    }
                    catch (const invalid_argument& e) {

                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                widerunout(run);
            }
            else
            {
                int run;
                cout << "What were the legal runs (runs excluding the no ball) made?";
                while (true)
                {
                    try {

                        cin >> run;

                        if (run > 5 || run < 0) { throw invalid_argument("Invalid input"); }


                        break;
                    }
                    catch (const invalid_argument& e) {

                        cout << "testing" << endl;
                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                widerun(run);
            }

        }
        else if (a == "n")
        {
            string c;
            cout << "Was there a runout on noball? enter y for yes, any other alphabet or word for no:";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> c;
            if (c == "y")
            {
                int run;
                cout << "What were the legal runs (runs excluding the no ball) made?";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (true)
                {
                    try {

                        cin >> run;

                        if (run > 5 || run < 0) { throw invalid_argument("Invalid input"); }


                        break;
                    }
                    catch (const invalid_argument& e) {

                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                noballrunout(run);
            }
            else
            {
                int run;
                cout << "What were the legal runs (runs excluding the no ball) made?";
                while (true)
                {
                    try {

                        cin >> run;

                        if (run > 5 || run < 0) { throw invalid_argument("Invalid input"); }


                        break;
                    }
                    catch (const invalid_argument& e) {

                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                noballrun(run);
            }
        }
        cout << endl << endl;
    }

    void showscoreboard()
    {
        if (readwickets() != 4) {
            cout << "Team Score: " << readtotal() << "-" << readwickets() << endl;
            cout << "Overs: " << readovers() << "." << readoverball() << "     " << "Extras: " << readextras() << endl;
            cout << endl << "* " << batlineup->strike->name << ": " << batlineup->strike->runs << " (" << batlineup->strike->balls << ") " << endl;
            cout << batlineup->nonstrike->name << ": " << batlineup->nonstrike->runs << " (" << batlineup->nonstrike->balls << ") " << endl;
            cout << bowlineup->bowl->name << ": " << bowlineup->bowl->wickets << "/" << bowlineup->bowl->runs << " (" << bowlineup->bowl->balls / 6 << "." << bowlineup->bowl->balls % 6 << ") " << endl << endl;
        }

    }

};

batsmanLineup firstbatting;
bowlerlineup firstbowling;
batsmanLineup secondbatting;
bowlerlineup secondbowling;
innings firstinn(&firstbatting, &firstbowling);
innings secondinn(&secondbatting, &secondbowling);

void toss()
{
    int a;
    while (true)
    {
        try {
            cout << "who won the toss out of the two teams? Enter the number before the name of the team" << endl << "1. " << Team1_name << endl << "2. " << Team2_name << endl;
            cin >> a;
            if (a != 1 && a != 2) throw invalid_argument("Invalid input");
            break;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    if (a == 1)
    {
        int d;
        TossWinner = Team1_name;
        TossLoser = Team2_name;
        while (true)
        {
            try {
                cout << TossWinner << " won the toss. What would " << TossWinner << " like to elect? enter the correct option number: " << endl << "1. Bat" << endl << "2. Bowl" << endl;
                cin >> d;
                if (d != 1 && d != 2) throw invalid_argument("Invalid input");
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        if (d == 1)
        {
            firstbat = TossWinner;
            cout << TossWinner << " will bat first" << endl;
            for (int i = 0; i < 5; i++)
            {
                firstbatting.Loadbatsman(Team1_lineup[i]);
                secondbatting.Loadbatsman(Team2_lineup[i]);
                firstbowling.loadbowlers(Team2_lineup[i]);
                secondbowling.loadbowlers(Team1_lineup[i]);
                firstbat = Team1_name;
                secondbat = Team2_name;
            }

        }
        else
        {
            firstbat = TossLoser;
            cout << TossLoser << " will bat first" << endl;
            for (int i = 0; i < 5; i++)
            {
                firstbatting.Loadbatsman(Team2_lineup[i]);
                secondbatting.Loadbatsman(Team1_lineup[i]);
                firstbowling.loadbowlers(Team1_lineup[i]);
                secondbowling.loadbowlers(Team2_lineup[i]);
                firstbat = Team2_name;
                secondbat = Team1_name;
            }


        }

    }


    else
    {
        int d;
        TossWinner = Team2_name;
        TossLoser = Team1_name;
        while (true)
        {
            try {
                cout << TossWinner << " won the toss. What would " << TossWinner << " like to elect? enter the correct option number: " << endl << "1. Bat" << endl << "2. Bowl" << endl;
                cin >> d;
                if (d != 1 && d != 2) throw invalid_argument("Invalid input");
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        if (d == 1)
        {
            firstbat = TossWinner;
            cout << TossWinner << " will bat first" << endl;
            for (int i = 0; i < 5; i++)
            {
                firstbatting.Loadbatsman(Team2_lineup[i]);
                secondbatting.Loadbatsman(Team1_lineup[i]);
                firstbowling.loadbowlers(Team1_lineup[i]);
                secondbowling.loadbowlers(Team2_lineup[i]);
                firstbat = Team2_name;
                secondbat = Team1_name;
            }

        }


        else
        {
            firstbat = TossLoser;
            cout << TossLoser << " will bat first" << endl;
            for (int i = 0; i < 5; i++)
            {
                firstbatting.Loadbatsman(Team1_lineup[i]);
                secondbatting.Loadbatsman(Team2_lineup[i]);
                firstbowling.loadbowlers(Team2_lineup[i]);
                secondbowling.loadbowlers(Team1_lineup[i]);
                firstbat = Team1_name;
                secondbat = Team2_name;
            }
        }

    }

}


void match()
{
    cout << "welcome to the start of the match. This is a 5 a side 3 over cricket game. Please enter the team names:" << endl << "1: ";
    getline(cin, Team1_name);
    cout << "2: ";
    getline(cin, Team2_name);
    cout << endl << endl;
    cout << "Enter the player names of " << Team1_name << ": " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << i + 1 << ". ";
        getline(cin, Team1_lineup[i]);
    }
    cout << endl << endl;
    cout << "Enter the player names of " << Team2_name << ": " << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << i + 1 << ". ";
        getline(cin, Team2_lineup[i]);
    }
    cout << endl << endl;
    toss();
    cout << endl;


    firstinn.firstballprocess();


    firstinn.showscoreboard();

    while (firstinn.readballs() < 18)
    {


        if (firstinn.readwickets() != 4)
        {
            firstinn.anyotherball();
            firstinn.showscoreboard();
            if (firstinn.readballs() % 6 == 0)
            {
                cout << endl << "End of the over " << endl;
                firstbatting.changeStrike();
                firstinn.showscoreboard();
                firstbatting.changeStrike();
                cout << endl;
                if (firstinn.readovers() != 3)
                {
                    firstbowling.endOfOver();
                    firstbatting.changeStrike();
                    while (firstinn.readballs() % 6 == 0)
                    {
                        firstinn.anyotherball();
                        firstinn.showscoreboard();

                    }
                }
                else
                {
                    break;
                }

            }
            cout << endl;

        }
        else
        {
            break;
        }
    }
    cout << endl << endl << "----End of the first Innings----" << endl;
    cout << secondbat << " require " << firstinn.readtotal() + 1 << " to win." << endl << endl << endl;



    secondinn.firstballprocess();

    secondinn.showscoreboard();
    cout << (firstinn.readtotal() + 1) - secondinn.readtotal() << " required off " << 18 - secondinn.readballs() << " balls.";

    while (secondinn.readballs() <= 17)
    {


        if ((secondinn.readwickets() != 4) && (secondinn.readtotal() <= firstinn.readtotal()))
        {
            secondinn.anyotherball();
            secondinn.showscoreboard();
            cout << (firstinn.readtotal() + 1) - secondinn.readtotal() << " required off " << 18 - secondinn.readballs() << " balls.";

            if (secondinn.readballs() % 6 == 0)
            {
                cout << endl << "End of the over " << endl;
                secondbatting.changeStrike();
                secondinn.showscoreboard();
                secondbatting.changeStrike();
                cout << endl;
                if (secondinn.readovers() != 3)
                {
                    secondbowling.endOfOver();
                    secondbatting.changeStrike();
                    while (secondinn.readballs() % 6 == 0)
                    {
                        secondinn.anyotherball();
                        secondinn.showscoreboard();
                        cout << (firstinn.readtotal() + 1) - secondinn.readtotal() << " required off " << 18 - secondinn.readballs() << " balls.";
                    }
                }
                else
                {
                    break;
                }

            }
            cout << endl;
        }
        else
        {
            break;
        }

    }
    cout << endl;
    if (secondinn.readtotal() > firstinn.readtotal())
    {
        cout << secondbat << " wins the match by " << 4 - secondinn.readwickets() << " wickets. " << endl;
        int  val = 4 - secondinn.readwickets();
        string s = to_string(val);
        winstate = secondbat + " wins the match by " + s + " wickets. \n";
        file << winstate;
    }
    else if (secondinn.readtotal() < firstinn.readtotal())
    {
        cout << firstbat << " wins the match by " << firstinn.readtotal() - secondinn.readtotal() << " runs. " << endl;
        int  val = firstinn.readtotal() - secondinn.readtotal();
        string s = to_string(val);
        winstate = firstbat + " wins the match by " + s + " runs. \n";
        file << winstate;

    }
    else
    {
        cout << "The match has been tied. " << endl;
        winstate = "The match has been tied. \n \n";
        file << winstate;
    }

    //firstinn.showscoreboard();
}

void final_scorecard()
{
    file.open("scorecard.txt");
    file << winstate << "\n \n";
    cout << "Scorecard: " << endl << endl;
    file << "Scorecard: \n \n";
    cout << "First Batting: " << endl << endl;
    file << "First Batting: \n \n";
    cout << firstbat << ": " << endl;
    file << firstbat << ": \n \n";
    cout << firstinn.readtotal() << "-" << firstinn.readwickets() << "         Overs: " << firstinn.readovers() << "." << firstinn.readoverball() << endl;
    file << firstinn.readtotal() << "-" << firstinn.readwickets() << "         Overs: " << firstinn.readovers() << "." << firstinn.readoverball() << "";
    firstbatting.batting_scorecard();
    firstbowling.bowling_scorecard();
    cout << "Second Batting: " << endl << endl;
    file << "Second Batting: \n \n";
    cout << secondbat << ": " << endl;
    file << secondbat << ": \n";
    cout << secondinn.readtotal() << "-" << secondinn.readwickets() << "         Overs: " << secondinn.readovers() << "." << secondinn.readoverball() << endl;
    file << secondinn.readtotal() << "-" << secondinn.readwickets() << "         Overs: " << secondinn.readovers() << "." << secondinn.readoverball() << "\n";
    secondbatting.batting_scorecard();
    secondbowling.bowling_scorecard();
    file.close();
}





int main()
{

    match();
    final_scorecard();


}
