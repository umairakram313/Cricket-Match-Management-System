#include <iostream>
#include <string>
#include <fstream>
#include <limits>
using namespace std;

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
const char* path = "D:/EME content/semester 3/DSOOP/Project/Submission";
ofstream file(path);
string winstate;

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
    bowler()
    {
        next = NULL;
    }
    ~bowler()
    {
        delete next;
    }
    float economy()
    {

        float x = static_cast<float>(runs);
        float y1 = 6.00;
        float y2 = static_cast<float>(balls % 6);
        float y = static_cast<float>(balls / 6) + static_cast<float>(y2 / y1);
        return (x / y);
    }
};

class bowlerlineup
{
public:
    bowler* bowl;
    bowler* lastbowl;
    bowler* head;
    bowlerlineup()
    {
        bowl = NULL;
        lastbowl = NULL;
        head = NULL;
    }
    ~bowlerlineup()
    {
        delete bowl;
        delete lastbowl;
        delete head;
    }

    void loadbowlers(string bowlers)
    {
        bowler* ptr = new bowler;     //creating a bowler class pointer ptr which points to a new memory location called bowler
        if (head == NULL)    //checking if the head (pointing to the 1st bowler in lineup) is null?
        {
            head = ptr;     //if it's null, then head should be equal to new 1st  bowler (first time case)
            ptr->lineUpNo = 1;  //lineupno updated to 1 for user visual ease 0 -> 1 of 1st bowler
        }
        else if (head->next == NULL)  //else checking if the 1st bowler is only existent
        {
            head->next = ptr;  //
            ptr->lineUpNo = 2;
        }
        else
        {
            bowler* temp = head; //  ---> head = p1 position = temp
            while (temp->next != NULL)
            {
                temp = temp->next;  //let temp go to 2nd position (last non null pos of head)
            }
            temp->next = ptr;  //add next node (player ) using temp
            ptr->lineUpNo = temp->lineUpNo + 1;
        }
        ptr->name = bowlers;

    }

    void runs(int ru)
    {
        bowl->balls++;
        bowl->runs += ru;
        if (ru % 4 == 0) bowl->fours++;
        if (ru % 6 == 0) bowl->sixes++;
    }
    void wicket()
    {
        bowl->balls++;
        bowl->wickets++;
    }
    void wide(int rw)
    {
        bowl->runs = bowl->runs + rw + 1;
        bowl->wides++;
        if (rw % 4 == 0) bowl->fours++;
        if (rw % 6 == 0) bowl->sixes++;
    }

    void noball(int rn)
    {
        bowl->runs = bowl->runs + rn + 1;
        bowl->noballs++;
        if (rn % 4 == 0) bowl->fours++;
        if (rn % 6 == 0) bowl->sixes++;
    }

    void dotball()
    {
        bowl->balls++;
        bowl->dots++;
    }

    void openingbowler()
    {
        cout << "Which bowler will bowl the first over (enter the number before the number): " << endl;
        bowler* search = head;  //head is pointing towards the head of bowling line up (populated by loadbowlers)
        while (search != NULL)  //traverse through bowling line up linked list
        {
            cout << search->lineUpNo << ". " << search->name << endl;
            if (search->next) { search = search->next; }
            else break;

        }

        int t;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true)
        {
            try {

                cin >> t;
                if (t > 5 || t < 1) throw invalid_argument("Invalid input");
                break;
            }
            catch (const invalid_argument& e) {   //error handling for invalid entry of bowler number
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        //  cout << "testing head-value at openbowler() function" << head->name << endl;
        bowler* temp1 = head;
        while (t != (temp1->lineUpNo))
        {
            temp1 = temp1->next;
        }
        bowl = temp1;
        bowl->bowled = true;
    }
    void endOfOver()
    {
        int s = bowl->lineUpNo;
        bowl->overs++;
        cout << "Which bowler will bowl next over (enter the number before the number): " << endl;
        bowler* search = head;
        while (search != NULL)
        {
            if (search->lineUpNo != s) cout << search->lineUpNo << ". " << search->name << endl;
            search = search->next;
        }
        int t;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true)
        {
            try {

                cin >> t;
                if ((t > 5 || t < 1) || t == s) throw invalid_argument("Invalid input");
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        bowler* temp1 = head;
        while (t != temp1->lineUpNo)
        {
            temp1 = temp1->next;
        }
        bowler* temp2 = bowl;
        bowl = temp1;
        lastbowl = temp2;
        bowl->bowled = true;
    }

    void bowling_scorecard()
    {
        cout << "Bowling: " << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        bowler* temp = head;
        while (temp != NULL)
        {
            if (temp->bowled == true)
            {


                cout << temp->name << "      " << temp->balls / 6 << "." << temp->balls % 6 << " overs, " << temp->runs << " runs conceeded,    economy of " << temp->economy() << temp->dots << ",  dotballs, " << temp->fours << " fours conceeded, " << temp->sixes << " sixes conceeded, " << temp->wides << " wides and " << temp->noballs << " noballs." << endl;
                file << temp->name << "      " << temp->balls / 6 << "." << temp->balls % 6 << " overs, " << temp->runs << " runs conceeded,    economy of " << temp->economy() << temp->dots << ",  dotballs, " << temp->fours << " fours conceeded, " << temp->sixes << " sixes conceeded, " << temp->wides << " wides and " << temp->noballs << " noballs. \n";

            }
            temp = temp->next;
        }
        cout << "---------------------------------------------------------------------------------" << endl;
    }
};




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

    batsman()
    {
        next = NULL;

    }
    ~batsman()
    {
        delete next;
    }
    double strike_rate() {

        if (runs == 0 && balls == 0)
        {
            return 0;
        }
        else
        {
            double x = static_cast<double>(runs);
            double y = static_cast<double>(balls);
            return((x / y) * 100.00);
        }
    }

};


class batsmanLineup
{
public:
    batsman* strike;
    batsman* nonstrike;
    batsman* head;

    batsmanLineup()
    {
        strike = NULL;
        nonstrike = NULL;
        head = NULL;
    }

    ~batsmanLineup()
    {
        delete strike;
        delete nonstrike;
        delete head;
    }

    void Loadbatsman(string bat)
    {
        batsman* ptr = new batsman;
        if (head == NULL)
        {
            head = ptr;
            ptr->lineupNo = 1;
        }
        else if (head->next == NULL)
        {
            head->next = ptr;
            ptr->lineupNo = 2;
        }
        else
        {
            batsman* temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = ptr;
            ptr->lineupNo = temp->lineupNo + 1;
        }
        ptr->name = bat;
    }
    void openers()
    {
        int s;
        batsman* search = head;
        cout << "Choose the first opening batsman for the team (this batsman will take strike): " << endl;
        while (search != NULL)
        {
            cout << search->lineupNo << ". " << search->name << endl;
            search = search->next;
        }
        bool valid = true;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true)
        {
            try {

                cin >> s;

                if (s > 5 || s < 1) { throw invalid_argument("Invalid input"); }


                break;
            }
            catch (const invalid_argument& e) {

                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        batsman* temp = head;

        while (temp != NULL)
        {
            if (temp->lineupNo == s) strike = temp;
            temp = temp->next;

        }
        strike->inToBat = true;

        int t;
        batsman* search1 = head;
        cout << "Choose the second opening batsman for the team (this batsman will be the non-striker): " << endl;
        while (search1 != NULL)
        {
            if (search1->inToBat == false) cout << search1->lineupNo << ". " << search1->name << endl;
            search1 = search1->next;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true)
        {
            try {

                cin >> t;
                if ((t > 5 || t < 1) || t == s) throw invalid_argument("Invalid input");
                break;
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        batsman* temp1 = head;
        while (temp1 != NULL)
        {
            if (temp1->lineupNo == t) {
                nonstrike = temp1;
                break;
            }
            temp1 = temp1->next;
        }


        nonstrike->inToBat = true;



    }
    void dotball()
    {
        strike->balls++;
    }
    void runs(int r)
    {
        strike->balls++;
        strike->runs += r;
        if (r % 4 == 0)
        {
            strike->fours++;
        }
        else if (r % 6 == 0)
        {
            strike->sixes++;
        }
        if (r % 2 == 1)
        {
            batsman* temp = strike;
            strike = nonstrike;
            nonstrike = temp;
        }
    }

    void wicket(string name)
    {
        int noOfnotouts = 0;
        batsman* check = head;
        while (check != NULL)
        {
            if (check->out == false)   //check if 
            {
                noOfnotouts++;
            }
            check = check->next;
        }


        if (strike != NULL && nonstrike != NULL)
        {
            batsman* temp2 = NULL;
            batsman* temp1 = head;
            strike->balls++;
            strike->out = true;
            strike->outbowler = name;
            if (noOfnotouts > 2)
            {
                cout << "Choose a new batsman from the following (enter the number before the name): " << endl;
                batsman* temp = head;
                while (temp != NULL)
                {
                    if (!temp->inToBat)
                    {
                        cout << temp->lineupNo << ". " << temp->name << endl;
                    }
                    temp = temp->next;
                }

                int x;
                bool found = false;
                temp1 = head;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (true)
                {
                    try {
                        cout << "Enter the number to choose (the numbers may not be in order since the current order represents the preferred batting lineup): " << endl;
                        cin >> x;

                        temp1 = head;
                        while (temp1 != NULL)
                        {

                            if (temp1->lineupNo == x)
                            {

                                if (temp1->inToBat == false)
                                {
                                    found = true;
                                    break;
                                }
                            }
                            temp1 = temp1->next;
                        }

                        if (found == false) throw invalid_argument("Invalid input");
                        break;
                    }
                    catch (const invalid_argument& e) {
                        cout << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }

                temp2 = head;
                while (temp2->lineupNo != x)
                {
                    temp2 = temp2->next;
                }


                strike = temp2;
                strike->inToBat = true;

            }
        }

    }


    void runout(bool notaWideBall, int r)
    {


        int noOfnotouts = 0;
        batsman* check = head;

        while (check != NULL)
        {
            if (check->out == false)   //check if innings finished by confirming notouts
            {
                noOfnotouts++;
            }
            check = check->next;
        }



        batsman* temp2 = NULL;
        batsman* safe = NULL;
        if (notaWideBall)
        {
            if (r > 0) runs(r);
            else dotball();
        }


        int a;
        while (true)
        {
            try {
                cout << "which of the two batsmen got runout?" << endl << "1. " << strike->name << endl << "2. " << nonstrike->name << endl;
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
            strike->out = true;
            strike->runout = true;
            strike = NULL;
            safe = nonstrike;
        }
        else
        {
            nonstrike->out = true;
            nonstrike->runout = true;
            nonstrike = NULL;
            safe = strike;
        }
        if (noOfnotouts > 2)
        {
            cout << "Choose a new batsman from the following (enter the number before the name): " << endl;
            batsman* temp = head;
            while (temp != NULL)
            {
                if (!temp->inToBat)
                {
                    cout << temp->lineupNo << ". " << temp->name << endl;
                }
                temp = temp->next;
            }

            int b;
            bool found = false;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            batsman* temp1 = head;
            while (true)
            {
                try {
                    cout << "Enter the number to choose (the numbers may not be in order since the current order represents the preferred batting lineup): " << endl;
                    cin >> b;

                    temp1 = head;
                    while (temp1 != NULL)
                    {

                        if (temp1->lineupNo == b)
                        {

                            if (temp1->inToBat == false)
                            {
                                found = true;
                                break;
                            }
                        }
                        temp1 = temp1->next;
                    }

                    if (found == false) throw invalid_argument("Invalid input");
                    break;
                }
                catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            temp2 = head;
            while (temp2->lineupNo != b)
            {
                temp2 = temp2->next;
            }
            temp2->inToBat = true;

            int f;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (true)
            {
                try {
                    cout << "who should face the next ball? (enter the number before the name)" << endl << "1. " << temp2->name << endl << "2. " << safe->name << endl;
                    cin >> f;
                    if (f != 1 && f != 2) throw invalid_argument("Invalid input");
                    break;
                }
                catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            if (f == 1)
            {
                strike = temp2;
                nonstrike = safe;
            }
            else
            {
                strike = safe;
                nonstrike = temp2;
            }
        }
    }

    void changeStrike()
    {
        batsman* temp = strike;
        strike = nonstrike;
        nonstrike = temp;
    }
    void batting_scorecard()
    {
        cout << "Batting " << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        batsman* temp = head;
        while (temp != NULL)
        {
            if (temp->inToBat == true)
            {
                if (temp->out == true && temp->runout == false)
                {
                    cout << temp->name << "          b " << temp->outbowler << "          " << temp->runs << "runs off " << temp->balls << " balls,  " << temp->fours << " fours and  " << temp->sixes << " sixes at a strike rate of  " << temp->strike_rate() << " " << endl;
                    file << temp->name << "          b " << temp->outbowler << "          " << temp->runs << "runs off " << temp->balls << " balls,  " << temp->fours << " fours and  " << temp->sixes << " sixes at a strike rate of  " << temp->strike_rate() << " \n";

                }
                else if (temp->out == true && temp->runout == true)
                {
                    cout << temp->name << "           run-out          " << temp->runs << "runs off " << temp->balls << " balls,  " << temp->fours << " fours and  " << temp->sixes << " sixes at a strike rate of  " << temp->strike_rate() << " " << endl;
                    file << temp->name << "           run-out          " << temp->runs << "runs off " << temp->balls << " balls,  " << temp->fours << " fours and  " << temp->sixes << " sixes at a strike rate of  " << temp->strike_rate() << " \n";

                }
                else
                {
                    cout << temp->name << "          not out                " << temp->runs << "runs off " << temp->balls << " balls,  " << temp->fours << " fours and  " << temp->sixes << " sixes at a strike rate of  " << temp->strike_rate() << " " << endl;
                    file << temp->name << "          not out                " << temp->runs << "runs off " << temp->balls << " balls,  " << temp->fours << " fours and  " << temp->sixes << " sixes at a strike rate of  " << temp->strike_rate() << " \n";

                }
            }
            temp = temp->next;
        }
        batsman* temp1 = head;
        cout << endl << "Did not bat:" << endl;
        while (temp1 != NULL)
        {
            if (temp1->inToBat == false)
            {
                cout << temp1->name << endl;
            }
            temp1 = temp1->next;
        }
        cout << "---------------------------------------------------------------------------------" << endl;
    }

};

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
