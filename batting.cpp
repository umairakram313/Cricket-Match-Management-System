#include "batting.h"


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

    batsman::batsman()
    {
        next = NULL;

    }
    batsman::~batsman()
    {
        delete next;
    }
    batsman::double strike_rate() {

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



    batsman* strike;
    batsman* nonstrike;
    batsman* head;

    batsmanLineup::batsmanLineup()
    {
        strike = NULL;
        nonstrike = NULL;
        head = NULL;
    }

    batsmanLineup::~batsmanLineup()
    {
        delete strike;
        delete nonstrike;
        delete head;
    }

    void batsmanLineup::Loadbatsman(string bat)
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
    void batsmanLineup::openers()
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
    void batsmanLineup::dotball()
    {
        strike->balls++;
    }
    void batsmanLineup::runs(int r)
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

    void batsmanLineup::wicket(string name)
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


    void batsmanLineup::runout(bool notaWideBall, int r)
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

    void batsmanLineup::changeStrike()
    {
        batsman* temp = strike;
        strike = nonstrike;
        nonstrike = temp;
    }
    void batsmanLineup::batting_scorecard()
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


