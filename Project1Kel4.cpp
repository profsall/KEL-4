#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

struct Pasien {
    int noRekamMedis;
    string namaRS;
    string namaPasien;
};

const int MAX_DATA = 100;
Pasien daftarPasien[MAX_DATA];
int jumlahData = 0;

void tampil(Pasien daftarPasien[], int n);
void swapPasien(Pasien &a, Pasien &b);
void bubbleSort(Pasien data[], int n);
void selectionSort(Pasien data[], int n);
void insertionSort(Pasien data[], int n);
void tampilkanDaftarFile();
void sorting();
void mergingSambung();

void swapPasien(Pasien &a, Pasien &b) {
    Pasien temp = a;
    a = b;
    b = temp;
}

void bubbleSort(Pasien data[], int n) {
    for (int k = 0; k < n - 1; k++) {
        for (int j = 0; j < n - 1 - k; j++) {
            if (data[j].noRekamMedis > data[j + 1].noRekamMedis) {
                swapPasien(data[j], data[j + 1]);
            }
        }
    }
}

void selectionSort(Pasien data[], int n) {
    for (int k = 0; k < n - 1; k++) {
        int min_idx = k;
        for (int j = k + 1; j < n; j++) {
            if (data[j].noRekamMedis < data[min_idx].noRekamMedis) {
                min_idx = j;
            }
        }
        swapPasien(data[min_idx], data[k]);
    }
}

void insertionSort(Pasien data[], int n) {
    for (int k = 1; k < n; k++) {
        Pasien temp = data[k];
        int j = k - 1;
        while (j >= 0 && data[j].noRekamMedis > temp.noRekamMedis) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = temp;
    }
}

void tampilkanDaftarFile() {
    cout << "Daftar file .txt di direktori:\n";
    cout << "----------------------------------\n";
    system("dir /b *.txt");
    cout << "----------------------------------\n";
}

void tampil(Pasien daftarPasien[], int n) {
    if (n == 0) {
        cout << "Data Kosong!\n";
    } else {
        cout << setw(10) << left << "NO RM" << setw(20) << left << "Nama RS" << "Nama Pasien" << endl;
        cout << "------------------------------------------------------------\n";
        for (int i = 0; i < n; i++) {
            cout << setw(10) << left << daftarPasien[i].noRekamMedis 
                 << setw(20) << left << daftarPasien[i].namaRS 
                 << daftarPasien[i].namaPasien << endl;
        }
    }
}

void sorting() {
    string fileSumber, fileHasil;
    tampilkanDaftarFile();
    cout << "Pilih file sumber: "; 
    cin >> fileSumber;
    
    ifstream inFile(fileSumber);
    if (!inFile) {
        cout << "File tidak ditemukan!\n";
    } else {
        int n = 0;
        while (inFile >> daftarPasien[n].noRekamMedis) {
            inFile.ignore();
            getline(inFile, daftarPasien[n].namaRS, '|');
            getline(inFile, daftarPasien[n].namaPasien);
            n++;
        }
        inFile.close();

        if (n == 0) {
            cout << "File kosong!\n";
        } else {
            int opsi;
            cout << "\nPilih Algoritma:\n1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\nOpsi: "; 
            cin >> opsi;
            
            if (opsi == 1) {
                bubbleSort(daftarPasien, n);
            } else if (opsi == 2) {
                selectionSort(daftarPasien, n);
            } else if (opsi == 3) {
                insertionSort(daftarPasien, n);
            }

            cout << "Masukkan nama file baru untuk hasil: "; 
            cin >> fileHasil;

            ofstream outFile(fileHasil);
            for (int i = 0; i < n; i++) {
                outFile << daftarPasien[i].noRekamMedis << "|" << daftarPasien[i].namaRS << "|" << daftarPasien[i].namaPasien << endl;
            }
            outFile.close();
            cout << "Data berhasil disimpan ke file baru: " << fileHasil << endl;
        }
    }
}

void mergingSambung() {
    string fileHasil, fileInput;
    int jml;
    system("cls");
    cout << "MERGING SAMBUNG\n";
    tampilkanDaftarFile();
    
    cout << "Nama file baru hasil gabungan: "; 
    cin >> fileHasil;
    cout << "Jumlah file yang akan digabung (Max 4): "; 
    cin >> jml;
    
    if (jml > 4) {
        jml = 4;
    }
    
    ofstream outFile(fileHasil);
    for(int i = 0; i < jml; i++) {
        cout << "Masukkan nama file ke-" << i+1 << ": "; 
        cin >> fileInput;
        ifstream inFile(fileInput);
        if (!inFile) {
            cout << "File tidak ada!\n";
        } else {
            string baris;
            while(getline(inFile, baris)) {
                outFile << baris << endl;
            }
            inFile.close();
        }
    }
    outFile.close();
    cout << "Merge Selesai!\n";
}

int main() {
    int pilihan;
    char lanjut = 'y';
    do {
        system("cls");
        cout << "SISTEM INFORMASI PASIEN (0708)\n";
        cout << "==================================\n";
        cout << "1. INPUT DATA KE FILE BARU\n";
        cout << "2. TAMPIL DATA DARI FILE\n";
        cout << "3. SORTING KE FILE BARU\n";
        cout << "4. MERGING SAMBUNG\n";
        cout << "5. EXIT\n";
        cout << "==================================\n";
        cout << "Pilih : "; 
        cin >> pilihan;

        if (pilihan == 1) {
            string fn;
            cout << "Nama file: "; 
            cin >> fn;
            ofstream out(fn);
            cout << "Jumlah data: "; 
            cin >> jumlahData;
            for (int i = 0; i < jumlahData; i++) {
                cout << "Data ke-" << i+1 << endl;
                cout << "No RM: "; 
                cin >> daftarPasien[i].noRekamMedis; 
                cin.ignore();
                cout << "RS   : "; 
                getline(cin, daftarPasien[i].namaRS);
                cout << "Nama : "; 
                getline(cin, daftarPasien[i].namaPasien);
                out << daftarPasien[i].noRekamMedis << "|" << daftarPasien[i].namaRS << "|" << daftarPasien[i].namaPasien << endl;
            }
            out.close();
        } else if (pilihan == 2) {
            string fn;
            tampilkanDaftarFile();
            cout << "Pilih file: "; 
            cin >> fn;
            ifstream in(fn);
            if (!in) {
                cout << "Gagal buka file!\n";
            } else {
                int n = 0;
                while (in >> daftarPasien[n].noRekamMedis) {
                    in.ignore();
                    getline(in, daftarPasien[n].namaRS, '|');
                    getline(in, daftarPasien[n].namaPasien);
                    n++;
                }
                tampil(daftarPasien, n);
                in.close();
            }
        } else if (pilihan == 3) {
            sorting();
        } else if (pilihan == 4) {
            mergingSambung();
        } else if (pilihan == 5) {
            lanjut = 't';
        } else {
            cout << "Menu tidak ada!\n";
        }

        if (pilihan != 5) {
            cout << "\nKembali ke Menu Utama(y/t)? "; 
            cin >> lanjut;
        }
    } while (lanjut == 'y' || lanjut == 'Y');
    
    system("cls");
    cout << "Program dihentikan\n";
    return 0;
}