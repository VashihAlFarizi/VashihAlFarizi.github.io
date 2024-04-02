#include <iostream>
#include <vector>
#include <limits>

using namespace std;

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

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

bool login() {
    string nama, nim;
    int salah = 0;
    
    while (salah < 3) {
        cout << "Masukkan Nama: ";
        cin >> nama;
        cout << "Masukkan NIM: ";
        cin >> nim;
        
        if (nama == "vashih" && nim == "2309106076") {
            cin.ignore(); 
            return true;
        } else {
            salah++;
            cout << "Nama atau NIM salah. Coba lagi." << endl;
        }
    }
    
    cout << "Anda sudah salah memasukkan Nama atau NIM sebanyak 3 kali. Program berhenti." << endl;
    return false;
}

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
            cout << "Program selesai." << endl;
            break;
        default:
            cout << "Menu tidak valid." << endl;
    }
}

void menuLoop() {
    char choice;
    showMenu();
    cin >> choice;
    runMenu(choice);
    if (choice != '5') {
        waitForInput();
        menuLoop();
    }
}

int main() {
    if (!login()) {
        return 0;
    }
    
    menuLoop();
    return 0;
}
