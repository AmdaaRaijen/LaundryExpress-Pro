#include <iostream>
#include <string>
#include "LaundryExpress.cpp"

using namespace std;

int main()
{
    int pilihan;
    do
    {
        cout << "\n--- LAUNDRYEXPRESS PRO SYSTEM ---";
        cout << "\n1. New Order\n2. Dashboard Status\n3. Optimize Queue\n4. Search Customer\n5. Business Report\n6. Exit";
        cout << "\nPilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            inputOrder();
            break;
        case 2:
            showDashboard();
            break;
        case 3:
            sort_by_priority(database, orderQty);
            break;
        case 4:
        {
            string q;
            cout << "Search Name: ";
            cin >> q;
            searchCustomer(q);
            break;
        }
        case 5:
            cout << "\n--- Business Report ---";
            break;
        }
    } while (pilihan != 6);

    return 0;
}