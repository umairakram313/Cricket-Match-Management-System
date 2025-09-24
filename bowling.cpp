#include "bowling.h"
#include "impfiles.h"


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
bowler::bowler()
{
    next = NULL;
}
bowler::~bowler()
{
    delete next;
}
float bowler::economy()
{
    float x = static_cast<float>(runs);
    float y1 = 6.00;
    float y2 = static_cast<float>(balls % 6);
    float y = static_cast<float>(balls / 6) + static_cast<float>(y2 / y1);
    return (x / y);
}

bowler* bowl;
bowler* lastbowl;
bowler* head;
bowlerlineup::bowlerlineup()
{
    bowl = NULL;
    lastbowl = NULL;
    head = NULL;
}
bowlerlineup::~bowlerlineup()
{
    delete bowl;
    delete lastbowl;
    delete head;
}
void bowlerlineup::loadbowlers(string bowlers)
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
void bowlerlineup::runs(int ru)
{
    bowl->balls++;
    bowl->runs += ru;
    if (ru % 4 == 0) bowl->fours++;
    if (ru % 6 == 0) bowl->sixes++;
}
void bowlerlineup::wicket()
{
    bowl->balls++;
    bowl->wickets++;
}
void bowlerlineup::wide(int rw)
{
    bowl->runs = bowl->runs + rw + 1;
    bowl->wides++;
    if (rw % 4 == 0) bowl->fours++;
    if (rw % 6 == 0) bowl->sixes++;
}
void bowlerlineup::noball(int rn)
{
    bowl->runs = bowl->runs + rn + 1;
    bowl->noballs++;
    if (rn % 4 == 0) bowl->fours++;
    if (rn % 6 == 0) bowl->sixes++;
}
void bowlerlineup::dotball()
{
    bowl->balls++;
    bowl->dots++;
}
void bowlerlineup::openingbowler()
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
void bowlerlineup::endOfOver()
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
void bowlerlineup::bowling_scorecard()
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