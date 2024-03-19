#include <iostream>
#include <vector>

using namespace std;

struct DataPenjualan {
    string namaBarang;
    int jumlah;
    double hargaSatuan;
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
            return true;
        } else {
            salah++;
            cout << "Nama atau NIM salah. Coba lagi." << endl;
        }
    }
    
    cout << "Anda sudah salah memasukkan Nama atau NIM sebanyak 3 kali. Program berhenti." << endl;
    return false;
}

void tambahData() {
    DataPenjualan data;
    cin.ignore();
    cout << "Masukkan Nama Barang: ";
    getline(cin, data.namaBarang);
    cout << "Masukkan Jumlah Barang/Perkilogram: ";
    cin >> data.jumlah;
    cout << "Masukkan Harga Satuan: ";
    cin >> data.hargaSatuan;
    
    penjualanData.push_back(data);
    cout << "Data berhasil ditambahkan." << endl;
}

void lihatData() {
    if (penjualanData.empty()) {
        cout << "Tidak ada data penjualan." << endl;
        return;
    }
    
    cout << "Data Penjualan Sembako:" << endl;
    for (std::vector<DataPenjualan>::size_type i = 0; i < penjualanData.size(); ++i) { // Perbaikan pada baris 78
        cout << "Barang: " << penjualanData[i].namaBarang << ", Jumlah Barang/Perkilogram: " << penjualanData[i].jumlah
             << ", Harga Satuan: " << penjualanData[i].hargaSatuan << endl;
    }
}

void hapusData() {
    if (penjualanData.empty()) {
        cout << "Tidak ada data penjualan yang bisa dihapus." << endl;
        return;
    }
    
    cout << "Data Penjualan Sembako:" << endl;
    for (std::vector<DataPenjualan>::size_type i = 0; i < penjualanData.size(); ++i) {
        cout << "Indeks " << i << ": ";
        cout << "Barang: " << penjualanData[i].namaBarang << ", Jumlah: " << penjualanData[i].jumlah
             << ", Harga Satuan: " << penjualanData[i].hargaSatuan << endl;
    }
    
    std::vector<DataPenjualan>::size_type index;
    cout << "Masukkan indeks data yang ingin dihapus: ";
    cin >> index;
    
    if (index >= penjualanData.size()) {
        cout << "Indeks tidak valid." << endl;
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
    for (std::vector<DataPenjualan>::size_type i = 0; i < penjualanData.size(); ++i) {
        cout << "Indeks " << i << ": ";
        cout << "Barang: " << penjualanData[i].namaBarang << ", Jumlah Barang/Perkilogram: " << penjualanData[i].jumlah
             << ", Harga Satuan: " << penjualanData[i].hargaSatuan << endl;
    }
    
    std::vector<DataPenjualan>::size_type index;
    cout << "Masukkan indeks data yang ingin diubah: ";
    cin >> index;
    
    if (index >= penjualanData.size()) {
        cout << "Indeks tidak valid." << endl;
        return;
    }
    
    cout << "Masukkan Nama Barang: ";
    cin.ignore();
    getline(cin, penjualanData[index].namaBarang);
    cout << "Masukkan Jumlah Barang/Perkilogram: ";
    cin >> penjualanData[index].jumlah;
    cout << "Masukkan Harga Satuan: ";
    cin >> penjualanData[index].hargaSatuan;
    
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
