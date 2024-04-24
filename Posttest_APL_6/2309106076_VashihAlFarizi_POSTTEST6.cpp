#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct User {
    string nama;
    string nim;
};

vector<User> databaseLogin = {};

// Manual sorting
void manualSortDatabaseLogin() {
    bool isOdd = (databaseLogin.size() % 2 == 1);
    if (isOdd) {
        for (size_t i = 0; i < databaseLogin.size(); ++i) {
            for (size_t j = i + 1; j < databaseLogin.size(); ++j) {
                if (databaseLogin[i].nim < databaseLogin[j].nim) {
                    swap(databaseLogin[i], databaseLogin[j]);
                } else if (databaseLogin[i].nim == databaseLogin[j].nim && databaseLogin[i].nama > databaseLogin[j].nama) {
                    swap(databaseLogin[i], databaseLogin[j]);
                }
            }
        }
    } else {
        for (size_t i = 0; i < databaseLogin.size(); ++i) {
            for (size_t j = i + 1; j < databaseLogin.size(); ++j) {
                if (databaseLogin[i].nim > databaseLogin[j].nim) {
                    swap(databaseLogin[i], databaseLogin[j]);
                } else if (databaseLogin[i].nim == databaseLogin[j].nim && databaseLogin[i].nama < databaseLogin[j].nama) {
                    swap(databaseLogin[i], databaseLogin[j]);
                }
            }
        }
    }
}

// Searching
int binarySearchAscending(const vector<User> &arr, const string &key) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].nim == key) {
            return mid;
        } else if (arr[mid].nim < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int binarySearchDescending(const vector<User> &arr, const string &key) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].nim == key) {
            return mid;
        } else if (arr[mid].nim > key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

bool registerasi();
bool login();
void tambahData();
void lihatData();
void hapusData();
void ubahData();
void waitForInput();
void showMenu();
void runMenu(char choice);
void menuLoop();
void showMenuLogin();
void runMenuLogin(char choice);
void menuLoginLoop();

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

struct SupplierInfo {
    string namaPemasok;
    string alamatPemasok;
};

struct DataPenjualan {
    string namaBarang;
    int jumlah;
    double hargaSatuan;
    SupplierInfo supplier;
};

vector<DataPenjualan> penjualanData;

void inputData(DataPenjualan* data) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Nama Barang: ";
    getline(cin, data->namaBarang);
    
    bool valid = false;
    while (!valid) {
        cout << "Masukkan Jumlah Barang/Perkilogram: ";
        if (!(cin >> data->jumlah)) {
            cout << "Input tidak valid. Masukkan angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            valid = true;
        }
    }
    
    valid = false;
    while (!valid) {
        cout << "Masukkan Harga Satuan: ";
        if (!(cin >> data->hargaSatuan)) {
            cout << "Input tidak valid. Masukkan angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            valid = true;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
    cout << "Masukkan Nama Pemasok: ";
    getline(cin, data->supplier.namaPemasok);

    cout << "Masukkan Alamat Pemasok: ";
    getline(cin, data->supplier.alamatPemasok);
}

void tambahData() {
    DataPenjualan data;
    inputData(&data);
    penjualanData.push_back(data);
    cout << "Data berhasil ditambahkan." << endl;
}

void lihatData() {
    if (penjualanData.empty()) {
        cout << "Tidak ada data penjualan." << endl;
        return;
    }
    
    cout << "Data Penjualan Sembako:" << endl;
    for (const auto& data : penjualanData) {
        cout << "Barang: " << data.namaBarang << ", Jumlah Barang/Perkilogram: " << data.jumlah
             << ", Harga Satuan: " << data.hargaSatuan << ", Nama Pemasok: " << data.supplier.namaPemasok
             << ", Alamat Pemasok: " << data.supplier.alamatPemasok << endl;
    }
}

void hapusData() {
    if (penjualanData.empty()) {
        cout << "Tidak ada data penjualan yang bisa dihapus." << endl;
        return;
    }
    
    cout << "Data Penjualan Sembako:" << endl;
    for (size_t i = 0; i < penjualanData.size(); ++i) {
        cout << "Indeks " << i << ": ";
        cout << "Barang: " << penjualanData[i].namaBarang << ", Jumlah: " << penjualanData[i].jumlah
             << ", Harga Satuan: " << penjualanData[i].hargaSatuan << ", Nama Pemasok: " << penjualanData[i].supplier.namaPemasok
             << ", Alamat Pemasok: " << penjualanData[i].supplier.alamatPemasok << endl;
    }
    
    size_t index;
    cout << "Masukkan indeks data yang ingin dihapus: ";
    if (!(cin >> index) || index >= penjualanData.size()) {
        cout << "Indeks tidak valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    penjualanData.erase(penjualanData.begin() + index);
    cout << "Data berhasil dihapus." << endl;
}

void ubahData() {
    if (penjualanData.empty()) {
        cout << "Tidak ada data penjualan yang bisa diubah." << endl;
        return;
    }
    
    cout << "Data Penjualan Sembako:" << endl;
    for (size_t i = 0; i < penjualanData.size(); ++i) {
        cout << "Indeks " << i << ": ";
        cout << "Barang: " << penjualanData[i].namaBarang << ", Jumlah Barang/Perkilogram: " << penjualanData[i].jumlah
             << ", Harga Satuan: " << penjualanData[i].hargaSatuan << ", Nama Pemasok: " << penjualanData[i].supplier.namaPemasok
             << ", Alamat Pemasok: " << penjualanData[i].supplier.alamatPemasok << endl;
    }
    
    size_t index;
    cout << "Masukkan indeks data yang ingin diubah: ";
    if (!(cin >> index) || index >= penjualanData.size()) {
        cout << "Indeks tidak valid." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    inputData(&penjualanData[index]);
    cout << "Data berhasil diubah." << endl;
}

void waitForInput() {
    cout << "Tekan tombol apapun untuk melanjutkan...";
    cin.ignore();
    cin.get(); 
}

void showMenu() {
    clearScreen();
    cout << "Menu:" << endl;
    cout << "1. Tambah Data Penjualan" << endl;
    cout << "2. Lihat Data Penjualan" << endl;
    cout << "3. Hapus Data Penjualan" << endl;
    cout << "4. Ubah Data Penjualan" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih menu: ";
}

void runMenu(char choice);

void menuLoop() {
    char choice;
    showMenu();
    cin >> choice;
    runMenu(choice);
}

void showMenuLogin() {
    clearScreen();
    cout << "Menu Login:" << endl;
    cout << "1. Login" << endl;
    cout << "2. Registrasi" << endl;
    cout << "3. Lihat Hasil Sorting Manual" << endl; // Menambahkan opsi baru
    cout << "4. Keluar" << endl;
    cout << "Pilih menu: ";
}

void runMenuLogin(char choice);

void menuLoginLoop() {
    char choice;
    showMenuLogin();
    cin >> choice;
    runMenuLogin(choice);
}

void runMenu(char choice) {
    switch (choice) {
        case '1':
            tambahData();
            break;
        case '2':
            lihatData();
            break;
        case '3':
            hapusData();
            break;
        case '4':
            ubahData();
            break;
        case '5':
            menuLoginLoop(); // Langsung kembali ke menu login
            return; // Keluar dari fungsi runMenu
        default:
            cout << "Menu tidak valid." << endl;
    }
    waitForInput();
    menuLoop();
}

void runMenuLogin(char choice) {
    switch (choice) {
        case '1':
            if (!login()) {
                return;
            }
            menuLoop();
            break;
        case '2':
            if (!registerasi()) {
                return;
            }
            menuLoop();
            break;
        case '3':
            clearScreen();
            cout << "Hasil Sorting Manual:" << endl;
            for (const auto& user : databaseLogin) {
                cout << "Nama: " << user.nama << ", NIM: " << user.nim << endl;
            }
            waitForInput();
            menuLoginLoop();
            break;
        case '4':
            cout << "Program selesai." << endl;
            exit(0); // Langsung keluar dari program
            break;
        default:
            cout << "Menu tidak valid." << endl;
    }
    if (choice != '4') {
        waitForInput();
        menuLoginLoop();
    }
}

bool login() {
    string nama, nim;
    int salah = 0;
    
    while (salah < 3) {
        cout << "Masukkan Nama: ";
        cin >> nama;
        cout << "Masukkan NIM: ";
        cin >> nim;
        
        for (const auto& user : databaseLogin) {
            if (user.nama == nama && user.nim == nim) {
                cin.ignore(); 
                return true;
            }
        }
        
        salah++;
        cout << "Nama atau NIM salah. Coba lagi." << endl;
    }
    
    cout << "Anda sudah salah memasukkan Nama atau NIM sebanyak 3 kali. Program berhenti." << endl;
    return false;
}

bool registerasi() {
    string nama, nim;
    cout << "Masukkan Nama: ";
    cin >> nama;
    cout << "Masukkan NIM: ";
    cin >> nim;
    
    // Cek apakah NIM sudah terdaftar
    for (const auto& user : databaseLogin) {
        if (user.nim == nim) {
            cout << "NIM sudah terdaftar." << endl;
            return false;
        }
    }
    
    // Tambahkan pengguna baru ke database
    databaseLogin.push_back({nama, nim});
    cout << "Registrasi berhasil." << endl;
    return true;
}

int main() {
    cout << "Selamat datang di program penjualan sembako." << endl;
    manualSortDatabaseLogin(); // Sorting saat program dimulai
    menuLoginLoop();
    return 0;
}
