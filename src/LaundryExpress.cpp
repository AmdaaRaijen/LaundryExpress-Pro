#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

const int MAX_ORDERS = 100;
const int BASE_PRICE = 5000;

struct Order
{
  int id;
  string customerName;
  string clothesType; // Baju, Celana, Jaket, dll.
  float weight;
  string serviceType; // Express, Fast, Normal
  int priority;       // 1 (Urgent) - 5 (Relaxed)
  double finalPrice;
  string status;     // Menunggu, Dicuci, Dikeringkan, Disetrika, Selesai
  int estimatedTime; // Dalam jam
};

Order orders[MAX_ORDERS];
string timelineStatus[MAX_ORDERS][5];
int orderCount = 0;
int nextId = 1;

const string STAGES[5] = {"Menunggu", "Dicuci", "Dikeringkan", "Disetrika", "Selesai"};

void inputOrder();
void processOrder();
void searchOrder();
void calculateEstimate();
void generateReport();
void optimizeOrder();
void showDashboard();
void resetData();
double calculatePrice(float weight, string type, string service, string name);
void predictTimeRecursive(int timeLeft);
void sort_by_priority(int *order_indices, int size);
void suggest_machine(string type, float weight, int *machine_id);

string toLowerCase(string str)
{
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

void inputOrder()
{
  if (orderCount >= MAX_ORDERS)
  {
    cout << "Kapasitas penuh!" << endl;
    return;
  }

  Order newOrder;
  newOrder.id = nextId++;
  newOrder.status = "Menunggu";

  cout << "\n--- INPUT ORDER BARU ---" << endl;

  do
  {
    cout << "Nama Pelanggan (Max 50 char): ";
    getline(cin, newOrder.customerName);
  } while (newOrder.customerName.length() > 50 || newOrder.customerName.empty());

  cout << "Jenis: 1.Baju, 2.Celana, 3.Jaket, 4.Selimut, 5.Lainnya" << endl;
  int typeChoice;
  cout << "Pilih Jenis (1-5): ";
  cin >> typeChoice;
  switch (typeChoice)
  {
  case 1:
    newOrder.clothesType = "Baju";
    break;
  case 2:
    newOrder.clothesType = "Celana";
    break;
  case 3:
    newOrder.clothesType = "Jaket";
    break;
  case 4:
    newOrder.clothesType = "Selimut";
    break;
  default:
    newOrder.clothesType = "Lainnya";
    break;
  }

  do
  {
    cout << "Berat (0.5 - 20 kg): ";
    cin >> newOrder.weight;
    if (newOrder.weight < 0.5 || newOrder.weight > 20)
    {
      cout << "Berat tidak valid! ";
    }
  } while (newOrder.weight < 0.5 || newOrder.weight > 20);

  cout << "Layanan: 1.Express (3jam), 2.Fast (6jam), 3.Normal (24jam)" << endl;
  int servChoice;
  cout << "Pilih Layanan: ";
  cin >> servChoice;
  switch (servChoice)
  {
  case 1:
    newOrder.serviceType = "Express";
    newOrder.estimatedTime = 3;
    break;
  case 2:
    newOrder.serviceType = "Fast";
    newOrder.estimatedTime = 6;
    break;
  default:
    newOrder.serviceType = "Normal";
    newOrder.estimatedTime = 24;
    break;
  }

  do
  {
    cout << "Prioritas (1 Tertinggi - 5 Terendah): ";
    cin >> newOrder.priority;
  } while (newOrder.priority < 1 || newOrder.priority > 5);

  newOrder.finalPrice = calculatePrice(newOrder.weight, newOrder.clothesType, newOrder.serviceType, newOrder.customerName);

  timelineStatus[orderCount][0] = "[Active]";
  for (int j = 1; j < 5; j++)
  {
    timelineStatus[orderCount][j] = "[ ]";
  }

  orders[orderCount] = newOrder;
  orderCount++;
  cout << "Order berhasil ditambahkan! Total Biaya: Rp " << (long)newOrder.finalPrice << endl;
}

double calculatePrice(float weight, string type, string service, string name)
{
  double price = weight * BASE_PRICE;

  if (type == "Celana")
    price *= 1.2;
  else if (type == "Jaket")
    price *= 1.5;
  else if (type == "Selimut")
    price *= 2.0;
  else if (type == "Lainnya")
    price *= 1.3;

  if (service == "Express")
    price *= 2.0;
  else if (service == "Fast")
    price *= 1.5;

  if (weight > 10)
  {
    price *= 0.9; // Diskon 10%
    cout << "[Info] Mendapat diskon berat 10%!" << endl;
  }

  int customerOrderCount = 0;
  for (int i = 0; i < orderCount; i++)
  {
    if (orders[i].customerName == name)
      customerOrderCount++;
  }
  if (customerOrderCount == 2)
  {
    price *= 0.85; // Diskon 15%
    cout << "[Info] Lucky! Order ke-3 diskon 15%!" << endl;
  }

  return price;
}

void processOrder()
{
  showDashboard();

  int idToUpdate;
  cout << "\nMasukkan ID Order untuk update status (0 kembali): ";
  cin >> idToUpdate;

  if (idToUpdate == 0)
    return;

  for (int i = 0; i < orderCount; i++)
  {
    if (orders[i].id == idToUpdate)
    {

      // Cek status saat ini ada di index mana
      int currentStageIndex = -1;
      for (int s = 0; s < 5; s++)
      {
        if (orders[i].status == STAGES[s])
        {
          currentStageIndex = s;
          break;
        }
      }

      if (currentStageIndex != -1 && currentStageIndex < 4)
      {
        orders[i].status = STAGES[currentStageIndex + 1];

        timelineStatus[i][currentStageIndex] = "[Done]  ";
        timelineStatus[i][currentStageIndex + 1] = "[Active]";

        cout << "Status berhasil diupdate ke: " << orders[i].status << endl;
      }
      else
      {
        cout << "Order sudah selesai atau status tidak valid." << endl;
      }
      return;
    }
  }
  cout << "ID tidak ditemukan." << endl;
}

void sort_by_priority(int *order_indices, int size)
{
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = 0; j < size - i - 1; j++)
    {
      if (orders[order_indices[j]].priority > orders[order_indices[j + 1]].priority)
      {
        int temp = *(order_indices + j);
        *(order_indices + j) = *(order_indices + j + 1);
        *(order_indices + j + 1) = temp;
      }
    }
  }
}

void suggest_machine(string type, float weight, int *machine_id)
{
  if (type == "Selimut" || weight > 8.0)
  {
    *machine_id = 1; // Heavy Duty
  }
  else
  {
    *machine_id = 2; // Standard
  }
}

void optimizeOrder()
{
  if (orderCount == 0)
  {
    cout << "Data kosong.\n";
    return;
  }

  int *indices = new int[orderCount];
  for (int i = 0; i < orderCount; i++)
    indices[i] = i;

  sort_by_priority(indices, orderCount);

  cout << "\n--- SARAN URUTAN PENCUCIAN (PRIORITAS) ---" << endl;
  cout << "No. \t ID \t Prio \t Mesin Rekomendasi" << endl;

  for (int i = 0; i < orderCount; i++)
  {
    int idx = indices[i];
    if (orders[idx].status == "Selesai")
      continue;

    int recommendedMachine;
    suggest_machine(orders[idx].clothesType, orders[idx].weight, &recommendedMachine);

    cout << (i + 1) << ".\t " << orders[idx].id << "\t "
         << orders[idx].priority << "\t "
         << (recommendedMachine == 1 ? "Mesin Besar (1)" : "Mesin Std (2)") << endl;
  }

  delete[] indices; // Hapus memory dinamis
}

void searchOrder()
{
  cout << "\n--- CARI ORDER ---" << endl;
  cout << "1. Berdasarkan Nama" << endl;
  cout << "2. Berdasarkan Status" << endl;
  int method;
  cin >> method;
  cin.ignore();

  if (method == 1)
  {
    string keyword;
    cout << "Masukkan nama: ";
    getline(cin, keyword);
    keyword = toLowerCase(keyword);

    bool found = false;
    for (int i = 0; i < orderCount; i++)
    {
      string nameLower = toLowerCase(orders[i].customerName);
      if (nameLower.find(keyword) != string::npos)
      {
        cout << "Order ID: " << orders[i].id << " | " << orders[i].customerName
             << " | " << orders[i].status << endl;
        found = true;
      }
    }
    if (!found)
      cout << "Tidak ditemukan." << endl;
  }
  else if (method == 2)
  {
    string statKey;
    cout << "Masukkan Status (Menunggu/Dicuci/dll): ";
    getline(cin, statKey);

    cout << "Hasil Status '" << statKey << "': ";
    for (int i = 0; i < orderCount; i++)
    {
      if (toLowerCase(orders[i].status) == toLowerCase(statKey))
      {
        cout << orders[i].id << ", ";
      }
    }
    cout << endl;
  }
}

void predictTimeRecursive(int timeLeft)
{
  if (timeLeft <= 0)
  {
    cout << "Selesai sekarang!" << endl;
    return;
  }
  cout << "T-" << timeLeft << " jam... ";
  predictTimeRecursive(timeLeft - 1);
}

void calculateEstimate()
{
  int idCari;
  cout << "Masukkan ID Order: ";
  cin >> idCari;

  for (int i = 0; i < orderCount; i++)
  {
    if (orders[i].id == idCari)
    {
      cout << "Estimasi Biaya: Rp " << (long)orders[i].finalPrice << endl;
      cout << "Estimasi Waktu Total: " << orders[i].estimatedTime << " Jam" << endl;
      cout << "Countdown Simulasi: ";
      predictTimeRecursive(3); // Simulasi hitung mundur 3 jam terakhir
      cout << endl;
      return;
    }
  }
  cout << "ID tidak ditemukan." << endl;
}

void generateReport()
{
  if (orderCount == 0)
  {
    cout << "[ERROR] Tidak ada data transaksi untuk dianalisis." << endl;
  }

  double totalRevenue = 0;
  float totalWeight = 0;
  int expressCount = 0;

  cout << "\n--- LAPORAN HARIAN ---" << endl;

  for (int i = 0; i < orderCount; i++)
  {
    if (orders[i].weight <= 0)
      continue;

    totalRevenue += orders[i].finalPrice;
    totalWeight += orders[i].weight;
    if (orders[i].serviceType == "Express")
      expressCount++;

    if (i == 50)
      break;
  }

  cout << "1. Total Pendapatan: Rp " << (long)totalRevenue << endl;
  cout << "2. Rata-rata Berat: " << (totalWeight / orderCount) << " kg/order" << endl;
  cout << "3. Order Express: " << expressCount << endl;

  cout << "4. Analisis selesai." << endl;
  return;
}

void showDashboard()
{
  if (orderCount == 0)
  {
    cout << "\n[Info] Belum ada data order." << endl;
    return;
  }

  cout << "\n======================== DASHBOARD LAUNDRY EXPRESS PRO ========================" << endl;

  // Header
  cout << left << setw(4) << "ID"
       << " | " << setw(15) << "Name"
       << " | " << setw(8) << "Weight"
       << " | " << setw(12) << "Status"
       << " | " << setw(5) << "Prio"
       << " | " << "Timeline (Mng-Cuci-Krg-Str-Sls)" << endl;

  cout << string(95, '-') << endl;

  for (int i = 0; i < orderCount; i++)
  {
    if (orders[i].id == 0)
      continue;

    string displayName = (orders[i].customerName.length() > 14) ? orders[i].customerName.substr(0, 12) + ".." : orders[i].customerName;

    cout << left << setw(4) << orders[i].id
         << " | " << setw(15) << displayName
         << " | " << setw(5) << fixed << setprecision(1) << orders[i].weight << " kg"
         << " | " << setw(12) << orders[i].status
         << " | " << setw(5) << orders[i].priority
         << " | ";

    for (int j = 0; j < 5; j++)
    {
      cout << timelineStatus[i][j] << " ";
    }
    cout << endl;
  }
  cout << string(95, '-') << endl;
}

void resetData()
{
  char confirm;
  cout << "Reset semua data hari ini? (y/n): ";
  cin >> confirm;
  if (confirm == 'y' || confirm == 'Y')
  {
    orderCount = 0;
    nextId = 1;
    cout << "Data berhasil direset!" << endl;
  }
}