# 🧺 LaundryExpress Pro System

**Sistem Manajemen Laundry Digital dengan Algoritma Optimasi**

LaundryExpress Pro adalah aplikasi manajemen laundry berbasis konsol yang dirancang untuk menangani kompleksitas operasional bisnis laundry modern. Program ini mengintegrasikan validasi data yang ketat, perhitungan harga cerdas, dan algoritma optimasi antrian.

---

## 📝 INFORMASI TUGAS

| Keterangan        | Detail                              |
| :---------------- | :---------------------------------- |
| **TUGAS**         | Tugas Pertemuan 14 (Proyek Mandiri) |
| **Mata Kuliah**   | Algoritma dan Pemrograman           |
| **Kelas**         | IF107                               |
| **Program Studi** | PJJ Informatika S1                  |
| **Nama**          | Bintang Triadmaja                   |
| **NIM**           | 250401010075                        |

---

## 🚀 Fitur Utama & Implementasi Konsep

Program ini mengimplementasikan seluruh konsep fundamental C++ sesuai spesifikasi:

### 1. Sistem Manajemen Order (Tipe Data & Variabel)

- Menggunakan **Struct** untuk pengelompokan data order.
- Validasi input menggunakan **Percabangan (If-Else)** dan **Goto** untuk penanganan error input (maksimal nama 50 karakter, berat 0.5-20 kg).
- Menggunakan lebih dari 5 tipe data berbeda (`int`, `float`, `double`, `string`, `bool`).

### 2. Kalkulator Cerdas (Logika Bisnis)

- Perhitungan biaya otomatis berdasarkan multiplier jenis pakaian (Selimut 2.0x, Jaket 1.5x, dll) dan jenis layanan (Express 2.0x).
- **Sistem Diskon Bertingkat**: Diskon 10% untuk berat > 10kg dan diskon loyalitas 15% untuk order berulang.

### 3. Dashboard Tracking (Array 2D & Nested Loop)

- Menggunakan **Array 2D** `timelineStatus[MAX][5]` untuk melacak progres pengerjaan:
  `Menunggu` → `Dicuci` → `Dikeringkan` → `Disetrika` → `Selesai`.
- Visualisasi tabel menggunakan **Nested Loop** untuk hasil yang rapi.

### 4. Algoritma Optimasi (Pointer & Sort)

- **Priority Sorting**: Menggunakan **Pointer** untuk mengurutkan antrian berdasarkan tingkat urgensi (Prioritas 1-5).
- **Machine Suggestion**: Logika otomatis penentuan mesin (Industri vs Reguler) berdasarkan beban kerja.

### 5. Prediksi Waktu (Fungsi Rekursif)

- Menggunakan **Fungsi Rekursif** untuk menghitung estimasi waktu penyelesaian berdasarkan jumlah tahapan yang tersisa secara akurat.

### 6. Sistem Pencarian & Laporan

- **Search Engine**: Pencarian nama pelanggan bersifat _case-insensitive_ dan _partial match_.
- **Business Report**: Laporan pendapatan harian dan rata-rata berat dengan kontrol alur `continue` dan `break`.

---

## 🛠️ Struktur Logika (Flowchart)

---

## 🖥️ Cara Menjalankan Program

1.  **Kompilasi**:
    Gunakan kompiler C++ (g++) di terminal Anda:
    ```bash
    g++ main.cpp -o /build/LaundryExpress
    ```
2.  **Eksekusi**:
    Jalankan file binary yang dihasilkan:
    ```bash
    ./build/LaundryExpress
    ```

---

## 📜 Lisensi

© 2026 Bintang Triadmaja - IF107 PJJ Informatika S1
