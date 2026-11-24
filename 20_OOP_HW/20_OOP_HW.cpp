#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Time
{
    int h, m, s;
    Time() :h(0), m(0), s(0) {}
    Time(int h, int m, int s)
    {
        int time = h * 3600 + m * 60 + s;
        time %= 86400;

        this->h = time / 3600;
        this->m = (time % 3600) / 60;
        this->s = time % 60;
    }
};

class Train
{
    int number;
    Time departureTime;
    string destination;
public:
    Train() :number(0), destination("none") {}
    Train(int num, int h, int m, int s, string des) :number(num), departureTime(h, m, s), destination(des) {};
    void Show()const
    {
        cout << "Train " << "No " << number << " departures at " 
            << departureTime.h << ":" << departureTime.m << ":" << departureTime.s << " and is going to " << destination << endl;
    }
    int getNumber()const { return number; }
    void ChangeTime(int h, int m, int s)
    {
        departureTime = Time(h, m, s);
    }
    void ShowDestination()const
    {
        cout << "Train" << " No" << number << " destination : " << destination << endl;
    }
    int getTime()
    {
        return departureTime.h * 3600 + departureTime.m * 60 + departureTime.s;
    }

    friend ostream& operator <<(ostream& out, const Train& t);
    friend istream& operator >>(istream& in, Train& t);
};

ostream& operator <<(ostream& out, const Train& t)
{
    out << t.number << " " << t.departureTime.h << ":" << t.departureTime.m << ":" << t.departureTime.s << " " << t.destination << " " << endl;
    return out;
}
istream& operator >>(istream& in, Train& t)
{
    in >> t.number;
    in >> t.departureTime.h;
    in >> t.departureTime.m;
    in >> t.departureTime.s;
    in >> t.destination;
    return in;
}

class Railway
{
    vector<Train> trains;
public:
    Railway() = default;
    void AddTrain(Train t) { trains.push_back(t); }
    void DeleteTrain() 
    { 
        if (trains.empty())
            throw exception("Railway is already empty");
        else
            trains.pop_back();
    }
    void DeleteTrainByNumber(int num)
    {
        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getNumber() == num)
            {
                trains.erase(trains.begin() + i);
                return;
            }
        }
        throw exception("Couldn't find the train");
    }
    void ShowAll()const
    {
        for (int i = 0; i < trains.size(); i++)
        {
            trains[i].Show();
            cout << "----------------------------------------------------" << endl;
        }
        cout << endl;
    }
    void ShowByNumber(int num)const
    {
        if (num < 0)throw out_of_range("Number is less than 0");
        else
        {
            for (int i = 0; i < trains.size(); i++)
            {
                if (trains[i].getNumber() == num)
                {
                    trains[i].Show();
                    cout << endl;
                    return;
                }
            }
            throw out_of_range("Number is bigger than railways train count");
        }
    }
    void ChangeTimeByNumber(int num, int h, int m, int s)
    {
        if (num < 0)throw out_of_range("Number is less than 0");
        else
        {
            for (int i = 0; i < trains.size(); i++)
            {
                if (trains[i].getNumber() == num)
                {
                    trains[i].ChangeTime(h, m, s);
                    return;
                }
            }
            throw out_of_range("Number is bigger than railways train count");
        }
    }
    void ShowDestinations()const
    {
        for (int i = 0; i < trains.size(); i++)
        {
            trains[i].ShowDestination();
            cout << "--------------------------" << endl;
        }
        cout << endl;
    }
    void Sort()
    {
        Train temp;
        for (int i = 0; i < trains.size(); i++)
        {
            for (int j = trains.size() - 1; j > i; j--)
            {
                if (trains[j - 1].getTime() > trains[j].getTime())
                {
                    temp = trains[j - 1];
                    trains[j - 1] = trains[j];
                    trains[j] = temp;
                }
            }
        }
    }
    void Save()
    {
        ofstream out("File");
        for (int i = 0; i < trains.size(); i++)
        {
            out << trains[i];
        }
        out.close();
    }
    void Read()
    {
        ifstream in("File");
        char bnum[250], bdtH[250], bdtM[250], bdtS[250], bdes[250];
        while (!in.eof())
        {
            in.getline(bnum, 250, ' ');
            if (in.eof())break;
            in.getline(bdtH, 250, ':');
            in.getline(bdtM, 250, ':');
            in.getline(bdtS, 250, ' ');
            in.getline(bdes, 250);
            int num = atoi(bnum);
            int h = atoi(bdtH);
            int m = atoi(bdtM);
            int s = atoi(bdtS);
            string des = bdes;
            Train t(num, h, m, s, des);
            trains.push_back(t);
        }
        in.close();
    }
};

int main()
{ 
    try
    {
        Railway railway;
        railway.AddTrain({ 1,25,40,23,"Rivne" });
        railway.AddTrain({ 12,4,20,32,"Lviv" });
        railway.AddTrain({ 3,18,56,61,"Kyiv" });
        railway.ShowAll();
        railway.ChangeTimeByNumber(3, 2, 1, 1);
        railway.ShowAll();
        //railway.ChangeTimeByNumber(4, 2, 2, 2);
        railway.Sort();
        railway.ShowAll();
        railway.ShowDestinations();
        railway.ShowByNumber(12);
        railway.Save();
        Railway newRailway;
        newRailway.Read();
        newRailway.ShowAll();
        newRailway.DeleteTrain();
        newRailway.DeleteTrain();
        //newRailway.DeleteTrain();
        //newRailway.DeleteTrain();
        newRailway.ShowAll();
        newRailway.AddTrain({ 15,23,36,31,"Zhytomur" });
        newRailway.AddTrain({ 2,14,20,20,"Rivne" });
        newRailway.AddTrain({ 3,18,17,16,"Rivne2" });
        newRailway.ShowAll();
        newRailway.DeleteTrainByNumber(15);
        newRailway.DeleteTrainByNumber(2);
        //newRailway.DeleteTrainByNumber(16);
        newRailway.ShowAll();
    }
    catch (exception ex)
    {
        cout << ex.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown error" << endl;
    }
}