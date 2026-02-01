#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_ORDERS = 100;
const int BASE_PRICE = 5000;

struct LaundryOrder
{
  int id;
  string customerName;
  string clothingType;
  float weight;
  string serviceType; // Express, Fast, Normal
  int priority;       // 1-5
  double totalPrice;
  string status;               // Waiting, Washing, Drying, Ironing, Finished
  int estimatedCompletionTime; // in hours
};

string timelineStatus[MAX_ORDERS][5];
LaundryOrder database[MAX_ORDERS];

int orderQty = 0;

double calculatePrice(float weight, const string &serviceType, const string &clothingType, const string &customerName)
{
  double serviceMultiplier = 1.0;
  double clothingMultiplier = 1.0;

  if (serviceType == "Express")
    serviceMultiplier = 2.0;
  else if (serviceType == "Fast")
    serviceMultiplier = 1.5;

  if (clothingType == "Pants")
    clothingMultiplier = 1.2;
  else if (clothingType == "Jacket")
    clothingMultiplier = 1.5;
  else if (clothingType == "Blanket")
    clothingMultiplier = 2.0;
  else if (clothingType == "Other")
    clothingMultiplier = 1.3;

  double total = BASE_PRICE * weight * serviceMultiplier * clothingMultiplier;

  // 10% discount for weight over 10 kg
  if (weight > 10.0)
    total *= 0.9;

  int count = 0;

  // Apply 15% discount for customers with more than 2 orders
  for (int i = 0; i < orderQty; i++)
  {
    if (database[i].customerName == customerName)
      count++;
  }

  cout << "Order count for " << customerName << ": " << count << endl;

  if (count > 1)
    total *= 0.85;

  return total;
}

void inputOrder()
{
  if (orderQty >= MAX_ORDERS)
  {
    cout << "Order is full. Cannot add new order.\n";
    return;
  }

  LaundryOrder newOrder;
  newOrder.id = orderQty + 1;

reEnterName:

  cout << "\n--- New Input Order ---" << endl;

  cout << "Customer Name: ";
  cin.ignore();
  getline(cin, newOrder.customerName);

  if (newOrder.customerName.empty())
  {
    cout << "Customer name cannot be empty. Order not added.\n";
    goto reEnterName;
  }

  if (newOrder.customerName.length() > 50)
  {
    cout << "Customer name is too long. Maximum 50 characters allowed. Order not added.\n";
    goto reEnterName;
  }

reEnterClothing:
  cout << "Clothing Type (Shirt/Pants/Jacket/Blanket/Other): ";
  getline(cin, newOrder.clothingType);

  if (newOrder.clothingType.empty())
  {
    cout << "Clothing type cannot be empty. Order not added.\n";
    goto reEnterClothing;
  }

reEnterWeight:
  cout << "Weight (0.5 - 20 kg): ";
  cin >> newOrder.weight;

  if (newOrder.weight < 0.5 || newOrder.weight > 20.0)
  {
    cout << "Invalid weight. Must be between 0.5 and 20 kg. Order not added.\n";
    goto reEnterWeight;
  }

reEnterService:
  cout << "Service Type (Express/Fast/Normal): ";
  cin >> newOrder.serviceType;

  if (newOrder.serviceType != "Express" && newOrder.serviceType != "Fast" && newOrder.serviceType != "Normal")
  {
    cout << "Invalid service type. Order not added.\n";
    goto reEnterService;
  }

reEnterPriority:
  cout << "Priority (1-5, 1 is highest): ";
  cin >> newOrder.priority;

  if (newOrder.priority < 1 || newOrder.priority > 5)
  {
    cout << "Invalid priority. Must be between 1 and 5. Order not added.\n";
    goto reEnterPriority;
  }

  newOrder.totalPrice = calculatePrice(newOrder.weight, newOrder.serviceType, newOrder.clothingType, newOrder.customerName);

  newOrder.status = "Waiting";
  database[orderQty] = newOrder;

  timelineStatus[orderQty][0] = "v"; // Waiting
  timelineStatus[orderQty][1] = "-"; // Washing
  timelineStatus[orderQty][2] = "-"; // Drying
  timelineStatus[orderQty][3] = "-"; // Ironing
  timelineStatus[orderQty][4] = "-"; // Finished

  orderQty++;
  cout << "Order added successfully!\n"
       << newOrder.totalPrice << endl;
}

void showDashboard()
{
  cout << "\n======================== DASHBOARD LAUNDRY EXPRESS PRO ========================" << endl;

  cout << left << setw(4) << "ID"
       << " | " << setw(15) << "Name"
       << " | " << setw(8) << "Weight"
       << " | " << setw(12) << "Status"
       << " | " << setw(5) << "Prio"
       << " | " << "Timeline" << endl;

  cout << string(79, '-') << endl;

  for (int i = 0; i < orderQty; i++)
  {
    cout << left << setw(4) << database[i].id
         << " | " << setw(15) << (database[i].customerName.length() > 14 ? database[i].customerName.substr(0, 12) + ".." : database[i].customerName)
         << " | " << setw(5) << fixed << setprecision(1) << database[i].weight << " kg"
         << " | " << setw(12) << database[i].status
         << " | " << setw(5) << database[i].priority
         << " | ";

    for (int j = 0; j < 5; j++)
    {
      cout << timelineStatus[i][j] << " ";
    }
    cout << endl;
  }
  cout << string(79, '-') << endl;
}

void sort_by_priority(LaundryOrder *orders, int size)
{
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = 0; j < size - i - 1; j++)
    {
      if ((orders + j)->priority > (orders + j + 1)->priority)
      {
        swap(*(orders + j), *(orders + j + 1));
      }
    }
  }
}