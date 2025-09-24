#include "impfiles.h"
#include "innings.h"

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
