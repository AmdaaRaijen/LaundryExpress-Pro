#include <string>

using namespace std;

const int MAX_ORDERS = 100;
const int BASE_PRICE = 5000;

struct LaundryOrder
{
  int id;
  string customerName;
  string clothingType;
  float weight;
  string serviceType;
  int priority; // 1-5
  double totalPrice;
  string status; // Waiting, Washing, Drying, Ironing, Finished
  int estimatedCompletionTime; // in hours
};

string timelineStatus[MAX_ORDERS];
LaundryOrder database[MAX_ORDERS];

int jumlahOrder = 0;
