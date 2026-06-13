#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Pasien {
    int noRekamMedis;
    string namaRS;
    string namaPasien;
};

const int MAX_DATA = 10;
Pasien daftarPasien[MAX_DATA];
int jumlahData = 0;

void menuUtama();
void tampil(Pasien daftarPasien[], int n);
void searching();
void sorting();
void swapPasien(Pasien &a, Pasien &b);
void bubbleSort(Pasien data[], int n);
void selectionSort(Pasien data[], int n);
void insertionSort(Pasien data[], int n);
void shellSort(Pasien data[], int n);
int partition(Pasien data[], int awal, int akhir);
void quickSort(Pasien data[], int awal, int akhir);
void merge(Pasien data[], int awal, int tengah, int akhir);
void mergeSort(Pasien data[], int awal, int akhir);
void operasifile();
void mergesambung();
void simpanlist(string filename);
void tampillist();

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
            j = j - 1;
        }
        data[j + 1] = temp;
    }
}

void shellSort(Pasien data[], int n) {
    for (int p = n / 2; p > 0; p = p / 2) {
        for (int j = p; j < n; j++) {
            Pasien temp = data[j];
            int k;
            for (k = j; k >= p && data[k - p].noRekamMedis > temp.noRekamMedis; k -= p) {
                data[k] = data[k - p];
            }
            data[k] = temp;
        }
    }
}

int partition(Pasien data[], int awal, int akhir) {
    int pivot = data[akhir].noRekamMedis;
    int ip = awal;
    for (int j = awal; j < akhir; j++) {
        if (data[j].noRekamMedis <= pivot) {
            swapPasien(data[j], data[ip]);
            ip++;
        }
    }
    swapPasien(data[akhir], data[ip]);
    return ip;
}

void quickSort(Pasien data[], int awal, int akhir) {
    if (awal < akhir) {
        int ip = partition(data, awal, akhir);
        quickSort(data, awal, ip - 1);
        quickSort(data, ip + 1, akhir);
    }
}

void merge(Pasien data[], int awal, int tengah, int akhir) {
    int lenkiri = tengah - awal + 1;
    int lenkanan = akhir - tengah;

    Pasien* arrayKiri = new Pasien[lenkiri];
    Pasien* arrayKanan = new Pasien[lenkanan];

    for (int i = 0; i < lenkiri; i++) {
        arrayKiri[i] = data[awal + i];
    }
    for (int j = 0; j < lenkanan; j++) {
        arrayKanan[j] = data[tengah + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = awal;

    while(i < lenkiri && j < lenkanan){
        if (arrayKiri[i].noRekamMedis <= arrayKanan[j].noRekamMedis){
            data[k] = arrayKiri[i];
            i++;
        } else {
            data[k] = arrayKanan[j];
            j++;
        }
        k++;
    }

    while (i < lenkiri) {
        data[k] = arrayKiri[i];
        i++;
        k++;
    }
    while (j < lenkanan) {
        data[k] = arrayKanan[j];
        j++;
        k++;
    }
    
    delete[] arrayKiri;
    delete[] arrayKanan;
}

void mergeSort(Pasien data[], int awal, int akhir) {
    if (awal >= akhir) {
        return;
    }
    int tengah = awal + (akhir - awal)/2;
    mergeSort(data, awal, tengah);
    mergeSort(data, tengah + 1, akhir);
    merge(data, awal, tengah, akhir);
}

void tampil(Pasien daftarPasien[], int n) {
    for (int i = 0; i < n; i++) {
        cout<<setw(10)<<left<<daftarPasien[i].noRekamMedis<<setw(20)<<left<<daftarPasien[i].namaRS<<daftarPasien[i].namaPasien<<"\n";
    }
}

void sorting() {
    string filesumber, filehasil;
    int pilihan;
    char ulang = 'y';
    char simpan = 'y';
    do {
        system("cls");
        cout<<"\nSORTING MENU\n";
        cout<<"==================================\n";
        cout<<"1. Bubble Sort\n";
        cout<<"2. Selection Sort\n";
        cout<<"3. Insertion Sort\n";
        cout<<"4. Quick Sort\n";
        cout<<"5. Shell Sort\n";
        cout<<"6. Merge Sort\n";
        cout<<"7. Kembali Ke Menu\n";
        cout<<"==================================\n";
        cout<<"Opsi(1-7): "; 
        cin>>pilihan;

        int jml = 0;
        if (pilihan >= 1 && pilihan <= 6) {
            tampillist();
            bool fileValid = false;
            
            do {
                cout<<"\nSorting data dari FILE : "; 
                cin>>filesumber;
                ifstream infile(filesumber);
                if (!infile.is_open()){
                    cout<<"Peringatan: File sumber tidak ditemukan! Silakan masukkan nama file yang benar.\n";
                } else {
                    fileValid = true;
                    while (jml < MAX_DATA && infile >> daftarPasien[jml].noRekamMedis) {
                        infile.ignore();
                        getline(infile, daftarPasien[jml].namaRS, '|');
                        getline(infile, daftarPasien[jml].namaPasien);
                        jml++;
                    }
                    infile.close();
                }
            } while (!fileValid);

            cout<<"\nData Sebelum Diurutkan\n";
            cout<<"==================================\n";
            cout<<setw(10)<<left<<"NO"<<setw(20)<<left<<"Nama RS"<<"Pasien\n";
            cout<<"==================================\n";
            tampil(daftarPasien, jml);
            cout<<"==================================\n\n";

            switch (pilihan) {
                case 1: bubbleSort(daftarPasien, jml); break;
                case 2: selectionSort(daftarPasien, jml); break;
                case 3: insertionSort(daftarPasien, jml); break;
                case 4: quickSort(daftarPasien, 0, jml - 1); break;
                case 5: shellSort(daftarPasien, jml); break;
                case 6: mergeSort(daftarPasien, 0, jml - 1); break;
            }

            cout<<"\nData Setelah Diurutkan\n";
            cout<<"==================================\n";
            cout<<setw(10)<<left<<"NO"<<setw(20)<<left<<"Nama RS"<<"Pasien\n";
            cout<<"==================================\n";
            tampil(daftarPasien, jml);
            cout<<"==================================\n";
            
            cout<<"\nSimpan Data Hasil Sorting(y/t)? "; 
            cin>>simpan;
            
            if (simpan == 'y' || simpan == 'Y') {
                bool namaValid = false;
                do {
                    cout<<"Simpan di FILE (wajib nama file baru) : "; 
                    cin>>filehasil;
                    ifstream cekFile(filehasil);
                    if (cekFile.is_open()) {
                        cout<<"Peringatan: File '"<<filehasil<<"' sudah ada! Cari nama lain agar data lama tidak hilang tertimpa.\n";
                        cekFile.close();
                    } else {
                        namaValid = true;
                    }
                } while (!namaValid);

                simpanlist(filehasil);
                ofstream outfile(filehasil);
                if (outfile.is_open()) {
                    for (int n = 0; n < jml; n++){
                        outfile<<daftarPasien[n].noRekamMedis<<"|"<<daftarPasien[n].namaRS<<"|"<<daftarPasien[n].namaPasien<<"\n";
                    }
                    outfile.close();
                } else {
                    cout<<"Error!!!\n";
                }
            }
        } else if (pilihan == 7) {
            return;
        } else {
            cout<<"\nPilihan tidak valid!\n";
        }
        cout<<"\nUlang(y/t)? : "; 
        cin>>ulang;
    } while (ulang == 'y' || ulang == 'Y');    
}

void searching() {
    string filename;
    int pilihan, cari;
    char ulang = 'y';
    
    do {
        system("cls");
        cout<<"SEARCHING\n";
        cout<<"================================\n";
        cout<<"1. Sequential Search\n";
        cout<<"2. Binary Search\n";
        cout<<"3. Kembali ke Menu Utama\n";
        cout<<"==================================\n";
        cout<<"Opsi: "; 
        cin>>pilihan;
        
        int n = 0;
        bool ditemukan = false;
        
        if (pilihan == 1 || pilihan == 2) {
            tampillist();
            bool fileValid = false;
            
            do {
                cout<<"\nCari Data dari FILE : "; 
                cin>>filename;
                ifstream infile(filename);
                if (!infile.is_open()){
                    cout<<"Peringatan: File tidak ditemukan! Silakan masukkan nama file yang benar.\n";
                } else {
                    fileValid = true;
                    while (n < MAX_DATA && infile >> daftarPasien[n].noRekamMedis){
                        infile.ignore();
                        getline(infile, daftarPasien[n].namaRS, '|');
                        getline(infile, daftarPasien[n].namaPasien);
                        n++;
                    }
                    infile.close();
                }
            } while (!fileValid);
                
            cout<<"Masukkan No Rekam Medis yang dicari: "; 
            cin>>cari;

            switch (pilihan) {
                case 1:
                    for (int i = 0; i < n; i++) {
                        if (daftarPasien[i].noRekamMedis == cari) {
                            ditemukan = true; 
                            cout<<"\nData ditemukan\n";
                            cout<<"==================================\n";
                            cout<<"No Rekam Medis     : "<<daftarPasien[i].noRekamMedis<<"\n";
                            cout<<"Nama Rumah Sakit   : "<<daftarPasien[i].namaRS<<"\n";
                            cout<<"Nama Pasien        : "<<daftarPasien[i].namaPasien<<"\n";
                            cout<<"==================================\n";
                        } 
                    }
                    break;
                case 2:
                    quickSort(daftarPasien, 0, n - 1);
                    int low = 0, high = n - 1;
                    while (low <= high) {
                        int mid = low + (high - low) / 2;
                        if (daftarPasien[mid].noRekamMedis == cari) {
                            ditemukan = true; 
                            int indexKiri = mid;
                            while (indexKiri >= 0 && daftarPasien[indexKiri].noRekamMedis == cari) {
                                cout<<"\nData ditemukan\n";
                                cout<<"=================================\n";
                                cout<<"No Rekam Medis     : "<<daftarPasien[indexKiri].noRekamMedis<<"\n";
                                cout<<"Nama Rumah Sakit   : "<<daftarPasien[indexKiri].namaRS<<"\n";
                                cout<<"Nama Pasien        : "<<daftarPasien[indexKiri].namaPasien<<"\n";
                                cout<<"=================================\n";
                                indexKiri--;
                            }
                            int indexKanan = mid + 1;
                            while (indexKanan < n && daftarPasien[indexKanan].noRekamMedis == cari) {
                                cout<<"\nData ditemukan\n";
                                cout<<"=================================\n";
                                cout<<"No Rekam Medis     : "<<daftarPasien[indexKanan].noRekamMedis<<"\n";
                                cout<<"Nama Rumah Sakit   : "<<daftarPasien[indexKanan].namaRS<<"\n";
                                cout<<"Nama Pasien        : "<<daftarPasien[indexKanan].namaPasien<<"\n";
                                cout<<"=================================\n";
                                indexKanan++;
                            }
                            break;
                        } else if (daftarPasien[mid].noRekamMedis < cari) {
                            low = mid + 1;
                        } else {
                            high = mid - 1;
                        }
                    }
                    break;
            }

            if (!ditemukan) {
                cout<<"\nData Tidak Ditemukan\n";
            }
            
        } else if (pilihan == 3) {
            return;
        } else {
            cout<<"\nPilihan Tidak Tersedia\n";
        }
        cout<<"\nUlang(y/t)? "; 
        cin>>ulang;
    } while (ulang == 'y' || ulang == 'Y');
}

void operasifile() {
    int operasi;
    char ulang = 'y';

    do{
        system("cls");
        cout<<"OPERASI FILE\n";
        cout<<"==================================\n";
        cout<<"1. MERGING SAMBUNG\n";
        cout<<"2. Kembali ke Menu Utama\n";
        cout<<"==================================\n";
        cout<<"Opsi : "; 
        cin>>operasi;
        cout<<"\n";
        tampillist();

        switch (operasi) {
            case 1: 
                mergesambung(); 
                break;
            case 2: 
                return;
            default: 
                cout<<"\nPilihan Tidak valid\n"; 
                break;
        }
        cout<<"\nUlang(y/t)? "; 
        cin>>ulang;
    } while (ulang == 'y' || ulang == 'Y');
}

void mergesambung() {
    string result;
    const int maxfile = 4;
    int jmlfile = 0;
    string filedipilih[maxfile];
    string baris;

    cout<<"\nMERGING SAMBUNG\n";
    cout<<"==================================\n";
    cout<<"Jumlah FILE yang ingin dioperasikan (max 4): "; 
    cin>>jmlfile;
    
    if (jmlfile < 1) {
        cout<<"FILE minimal 1\n";
    } else if (jmlfile > 4) {
        cout<<"FILE maksimal 4\n";
    } else {
        for (int i = 0; i < jmlfile; i++) {
            bool fileValid = false;
            do {
                cout<<"Nama File ke-"<<i + 1<<": "; 
                cin>>filedipilih[i];
                ifstream infile(filedipilih[i]);
                if (!infile.is_open()) {
                    cout<<"Peringatan: File tidak ditemukan! Masukkan nama file yang benar.\n";
                } else {
                    fileValid = true;
                    infile.close();
                }
            } while (!fileValid);
        }
        
        bool namaValid = false;
        do {
            cout<<"Simpan Hasil merge di FILE (wajib nama file baru) : "; 
            cin>>result;
            ifstream cekFile(result);
            if (cekFile.is_open()) {
                cout<<"Peringatan: File '"<<result<<"' sudah ada! Cari nama lain agar data tidak tertimpa.\n";
                cekFile.close();
            } else {
                namaValid = true;
            }
        } while (!namaValid);
        
        for (int j = 0; j < jmlfile; j++ ) {
            ifstream infile(filedipilih[j]);
            int n = 0;
            cout<<"==================================\n";
            cout<<setw(10)<<left<<"NO"<<setw(20)<<left<<"Nama RS"<<"Pasien\n";
            cout<<"==================================\n";
            while (n < MAX_DATA && infile >> daftarPasien[n].noRekamMedis) {
                infile.ignore();
                getline(infile, daftarPasien[n].namaRS, '|');
                getline(infile, daftarPasien[n].namaPasien);
                n++;
            }
            tampil(daftarPasien, n);
            cout<<"\n";
            infile.close();
        }
        
        ofstream outfile(result);
        for (int k = 0; k < jmlfile; k++) {
            ifstream infile(filedipilih[k]);
            while (getline(infile, baris)) {
                outfile<<baris<<"\n";
            }
            infile.close();
        }
        outfile.close();

        int m = 0;
        ifstream infile(result);
        cout<<"==================================\n";
        cout<<setw(10)<<left<<"NO"<<setw(20)<<left<<"Nama RS"<<"Pasien\n";
        cout<<"==================================\n";
        while (m < MAX_DATA && infile >> daftarPasien[m].noRekamMedis) {
            infile.ignore();
            getline(infile, daftarPasien[m].namaRS, '|');
            getline(infile, daftarPasien[m].namaPasien);
            m++;
        }
        tampil(daftarPasien, m);
        cout<<"==================================\n";
        infile.close();

        simpanlist(result);
    }
}

void simpanlist(string filename) {
    ofstream listfile("daftarfile.txt", ios::app);
    if (listfile.is_open()) {
        listfile<<filename<<"\n";
    } else {
        cout<<"ERROR\n";
    }
    listfile.close();
}

void tampillist() {
    ifstream listfile("daftarfile.txt");
    cout<<"LIST FILE\n";
    cout<<"==================================\n";
    if (!listfile.is_open()) {
        cout<<"Belum ada File\n";
    } else {
        string filename;
        while (getline(listfile, filename)) {
            cout<<filename<<"\n";
        }
    }
    listfile.close();
}

void menuUtama() {
    string namafile;
    int pilihan;
    char lanjut = 'y';
    do {
        system("cls");
        cout<<"MENU :\n";
        cout<<"==================================\n";
        cout<<"1. INPUT DATA\n";
        cout<<"2. TAMPIL DATA\n";
        cout<<"3. SEARCHING\n";
        cout<<"4. SORTING\n";
        cout<<"5. OPERASI FILE\n";
        cout<<"6. EXIT\n";
        cout<<"==================================\n";
        cout<<"Pilih : ";
        cin>>pilihan;
        system("cls");

        switch(pilihan) {
            case 1:
                tampillist();
                cout<<"\nINPUT DATA\n";
                cout<<"==================================\n";
                cout<<"Disimpan di file : "; 
                cin>>namafile;
                cout<<"Jumlah Data (MAX 10): "; 
                cin>>jumlahData;
                cout<<"==================================\n";
                simpanlist(namafile);
                
                if (jumlahData < 1) {
                    cout<<"Jumlah Data Minimal 1\n";
                } else if (jumlahData > 10) {
                    cout<<"Jumlah Data Maksimal 10\n";
                } else {
                    ofstream outfile(namafile, ios::app); 
                    if (outfile.is_open()){
                        for (int i = 0; i < jumlahData; i++) {
                            cout<<"Data ke-"<<i+1<<"\n";
                            cout<<"   No Rekam Medis      : "; 
                            cin>>daftarPasien[i].noRekamMedis; 
                            cin.ignore();
                            cout<<"   Nama Rumah Sakit    : "; 
                            getline(cin, daftarPasien[i].namaRS);
                            cout<<"   Nama Pasien         : "; 
                            getline(cin, daftarPasien[i].namaPasien);
                            outfile<<daftarPasien[i].noRekamMedis<<"|"<<daftarPasien[i].namaRS<<"|"<<daftarPasien[i].namaPasien<<"\n";
                        }
                        outfile.close();
                    } else {
                        cout<<"FILE Gagal!\n";
                    }
                }
                break;
            case 2: {
                int n = 0;
                tampillist();
                bool fileValid = false;
                
                do {
                    cout<<"\nNama FILE : "; 
                    cin>>namafile;
                    ifstream infile(namafile);
                    if (!infile.is_open()) {
                        cout<<"Peringatan: File gagal dibuka atau tidak ditemukan! Coba lagi.\n";
                    } else { 
                        fileValid = true;
                        cout<<"\nTAMPIL DATA\n";
                        cout<<"==================================\n";
                        cout<<setw(10)<<left<<"NO"<<setw(20)<<left<<"Nama RS"<<"Pasien\n";
                        cout<<"==================================\n";
                        while (n < MAX_DATA && infile >> daftarPasien[n].noRekamMedis){
                            infile.ignore();
                            getline(infile, daftarPasien[n].namaRS, '|');
                            getline(infile, daftarPasien[n].namaPasien);
                            n++;
                        }
                        tampil(daftarPasien, n);
                        infile.close();
                    }
                } while (!fileValid);
                break;
            }
            case 3:
                searching();
                break;
            case 4:
                sorting();
                break;
            case 5:
                operasifile();
                break;
            case 6:
                lanjut = 't';
                break;
            default:
                cout<<"\nPilihan Menu Tidak Tersedia\n";
                break;
        }
        if (pilihan != 6) {
            cout<<"==================================\n";
            cout<<"\nKembali ke Menu Utama(y/t)? "; 
            cin>>lanjut;
        }
    } while (lanjut == 'y' || lanjut == 'Y');
}

int main() {
    menuUtama();
    system("cls");
    cout<<"Program dihentikan\n";
    return 0;
}
