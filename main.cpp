#include<iostream>
#include<string>
using namespace std;

class HotelRoom
{
protected:
    int room_id;
    string room_type;
    bool occupancy[30]= {false};
public:
    HotelRoom (int room_id, string room_type)
    {
        this->room_id=room_id;
        this->room_type=room_type;

    }

    void checkIn ( int star_data, int end_data)
    {
        for ( int i=star_data-1; i<end_data; i++ )
        {
            if (occupancy[i]) throw logic_error("The room is not available.");
            occupancy[i] = true;
        }
    }
    void checkOut ( int star_data, int end_data)
    {
        for ( int i=star_data-1; i<end_data; i++ )
        {
            occupancy[i] =false;
        }
    }
    void availability()
    {
        cout << "Available days: ";
        for (int i = 0; i < 30; ++i)
        {
            if (!occupancy[i]) cout << (i + 1) << " ";
        }
        cout << endl;
    }

    static double occupancyRate(HotelRoom* rooms[], int count)
    {
        int totalDays = count * 30, occupiedDays = 0;
        for (int i = 0; i < count; ++i)
        {
            for (bool day : rooms[i]->occupancy) occupiedDays += day;
        }
        return (double)occupiedDays / totalDays * 100;
    }

};
class LuxuryRoom : public HotelRoom
{
    string amenities;

public:
    LuxuryRoom(int room_id, const string room_type, const string amenities) : HotelRoom(room_id, room_type)
    {
        this->amenities = amenities;
    }

    void details()
    {
        cout << "Amenities: " << amenities << endl;
    }
};



int main()
{
    HotelRoom r1(101, "Single");
    LuxuryRoom r2(201, "Suite", "Ocean View, Spa Access");

    r1.checkIn(1, 5);
    r2.checkIn(10, 15);

    r1.checkOut(3, 4);

    cout << "Room 101: ";
    r1.availability();

    cout << "Room 201: ";
    r2.availability();
    r2.details();

    HotelRoom* rooms[] = {&r1, &r2};
    cout << "Overall occupancy rate: " << HotelRoom::occupancyRate(rooms, 2) << "%" << endl;

    return 0;
}


