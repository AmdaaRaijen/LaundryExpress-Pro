#include "LaundryExpress.cpp"

int main()
{
    int choice;
    do
    {
        cout << "\n=============================================" << endl;
        cout << "       LAUNDRY EXPRESS PRO - SYSTEM V1.0      " << endl;
        cout << "=============================================" << endl;
        cout << "1. Input Order Baru" << endl;
        cout << "2. Process Order (Update Status)" << endl;
        cout << "3. Search & Show Detail" << endl;
        cout << "4. Calculate Estimated Time & Cost" << endl;
        cout << "5. Generate Daily Report" << endl;
        cout << "6. Optimize Laundry Order (Pointer)" << endl;
        cout << "7. Analyze Customer Data" << endl;
        cout << "8. Reset Daily Data" << endl;
        cout << "9. Exit" << endl;
        cout << "=============================================" << endl;
        cout << "Pilih Menu (1-9): ";
        cin >> choice;
        cin.ignore(); // Membersihkan buffer enter

        switch (choice)
        {
        case 1:
            inputOrder();
            break;
        case 2:
            processOrder();
            break;
        case 3:
            searchOrder();
            break;
        case 4:
            calculateEstimate();
            break;
        case 5:
            generateReport();
            break;
        case 6:
            optimizeOrder();
            break;
        case 7:
            showDashboard();
            break;
        case 8:
            resetData();
            break;
        case 9:
            cout << "Terima kasih telah menggunakan LaundryExpress Pro!";
            break;
        default:
            cout << "Input salah!" << endl;
        }
    } while (choice != 9);

    return 0;
}