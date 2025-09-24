#include "innings.h"

ball::ball()
{
    next = NULL;
}
ball::~ball()
{
    delete next;
}
innings::innings(batsmanLineup* batLine, bowlerlineup* bow)
{
    top = NULL;
    batlineup = batLine;
    bowlineup = bow;
}
innings::~innings()
{
    delete top;
    delete batlineup;
    delete bowlineup;
}
void innings::deleteball()
{
    ball* ptr = top;
    top = top->next;
    delete ptr;
}
void innings::firstball(int r)
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
void innings::firstballout()
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
void innings::firstballrunout(int legalrun)
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
void innings::firstballnoballrun(int r)
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
void innings::firstballnoballrunout(int legalrun)
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
void innings::firstballwiderun(int r)
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
void innings::firstballwiderunout(int legalrun)
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
void innings::scoredball(int x)
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
void innings::wicket()
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
void innings::runout(int legalrun)
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
void innings::noballrun(int r)
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
void innings::widerun(int r)
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
void innings::noballrunout(int legalrun)
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
void innings::widerunout(int legalrun)
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
int innings::readballs()
{
    return top->ballno;
}
int innings::readtotal()
{
    return top->total;
}
int innings::readwickets()
{
    return top->wickets;
}
int innings::readextras()
{
    return top->extras;
}
int innings::readovers()
{
    int c = (top->ballno / 6);
    return c;
}
int innings::readoverball()
{
    int c = top->ballno % 6;
    return c;
}
void innings::firstballprocess()
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
void innings::anyotherball()
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
void innings::showscoreboard()
{
    if (readwickets() != 4) {
        cout << "Team Score: " << readtotal() << "-" << readwickets() << endl;
        cout << "Overs: " << readovers() << "." << readoverball() << "     " << "Extras: " << readextras() << endl;
        cout << endl << "* " << batlineup->strike->name << ": " << batlineup->strike->runs << " (" << batlineup->strike->balls << ") " << endl;
        cout << batlineup->nonstrike->name << ": " << batlineup->nonstrike->runs << " (" << batlineup->nonstrike->balls << ") " << endl;
        cout << bowlineup->bowl->name << ": " << bowlineup->bowl->wickets << "/" << bowlineup->bowl->runs << " (" << bowlineup->bowl->balls / 6 << "." << bowlineup->bowl->balls % 6 << ") " << endl << endl;
    }
}
